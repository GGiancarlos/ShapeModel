/*============================================================================

  Library:  Image Segmentation Using Statistical Shape Models
  File:     vtkBuildShapeModel.cxx

  Copyright 2013 Kitware, Inc. All rights reserved.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.


  This file contains source code adapted from statismo.

  Copyright (c) 2011, University of Basel.
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  * Neither the name of the University of Basel nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.

============================================================================*/

#include "vtkBuildShapeModel.h"

#include "vtkEigen.h"
#include "vtkShapeModelData.h"
#include "vtkShapeModelUtilities.h"

#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkObjectFactory.h>
#include <vtkPolyData.h>

vtkStandardNewMacro(vtkBuildShapeModel)

//----------------------------------------------------------------------------
vtkBuildShapeModel::vtkBuildShapeModel()
{
  this->SetNumberOfOutputPorts(2);
}

//----------------------------------------------------------------------------
vtkBuildShapeModel::~vtkBuildShapeModel()
{
}

//----------------------------------------------------------------------------
vtkMultiBlockDataSet *vtkBuildShapeModel::GetInput()
{
  return vtkMultiBlockDataSet::SafeDownCast(vtkPolyDataAlgorithm::GetInput());
}

//----------------------------------------------------------------------------
void vtkBuildShapeModel::PrintSelf(ostream &os, vtkIndent indent)
{
  vtkPolyDataAlgorithm::PrintSelf(os, indent);
}

//----------------------------------------------------------------------------
int vtkBuildShapeModel::FillInputPortInformation(int port,
  vtkInformation *information)
{
  if(!vtkPolyDataAlgorithm::FillInputPortInformation(port, information))
    {
    return 0;
    }

  information->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(),
    "vtkMultiBlockDataSet");
  return 1;
}

//----------------------------------------------------------------------------
int vtkBuildShapeModel::FillOutputPortInformation(int port,
  vtkInformation *information)
{
  if(!vtkPolyDataAlgorithm::FillOutputPortInformation(port, information))
    {
    return 0;
    }

  if(port == 0)
    {
    information->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkPolyData");
    return 1;
    }

  if(port == 1)
    {
    information->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkShapeModelData");
    return 1;
    }

  vtkErrorMacro(<< "Invalid output port");
  return 0;
}

//----------------------------------------------------------------------------
int vtkBuildShapeModel::RequestData(vtkInformation *vtkNotUsed(request),
  vtkInformationVector **inputVector, vtkInformationVector *outputVector)
{
  vtkInformation *const inputInformation
    = inputVector[0]->GetInformationObject(0);
  vtkInformation *const outputInformation0
    = outputVector->GetInformationObject(0);
  vtkInformation *const outputInformation1
    = outputVector->GetInformationObject(1);

  vtkMultiBlockDataSet *const input = vtkMultiBlockDataSet::SafeDownCast(
    inputInformation->Get(vtkDataObject::DATA_OBJECT()));
  vtkPolyData *const output0 = vtkPolyData::SafeDownCast(
    outputInformation0->Get(vtkDataObject::DATA_OBJECT()));
  vtkShapeModelData *const output1 = vtkShapeModelData::SafeDownCast(
    outputInformation1->Get(vtkDataObject::DATA_OBJECT()));

  if(input == NULL || output0 == NULL || output1 == NULL)
    {
    vtkErrorMacro(<< "Invalid input or output(s)");
    return 0;
    }

  if(input->GetNumberOfBlocks() == 0)
    {
    vtkErrorMacro(<< "Empty input");
    return 0;
    }

  vtkPolyData *const inputPolyData0
    = vtkPolyData::SafeDownCast(input->GetBlock(0));

  if(inputPolyData0 == NULL)
    {
    vtkErrorMacro(<< "Invalid block in input");
    return 0;
    }

  vtkMatrixXd matrix(input->GetNumberOfBlocks(),
    inputPolyData0->GetNumberOfPoints() * 3);
  matrix.row(0)
    = vtkShapeModelUtilities::PointSetToVectorXd(inputPolyData0);

  for(vtkIdType i = 1; i < input->GetNumberOfBlocks(); ++i)
    {
    vtkPolyData *const inputPolyData
      = vtkPolyData::SafeDownCast(input->GetBlock(i));

    if(inputPolyData != NULL)
      {
      if(inputPolyData->GetNumberOfPoints()
        != inputPolyData0->GetNumberOfPoints())
        {
        vtkErrorMacro(<< "Number of points in input blocks do not match");
        return 0;
        }

      matrix.row(i)
        = vtkShapeModelUtilities::PointSetToVectorXd(inputPolyData);
      }
    }

  const vtkRowVectorXd mean = matrix.colwise().mean();
  output1->SetMean(mean);
  const vtkMatrixXd demeaned = matrix.rowwise() - mean;

  if(matrix.rows() < matrix.cols())
    {
    const vtkMatrixXd covariance
      = demeaned * demeaned.transpose() * 1.0 / (matrix.rows() - 1.0);
    const Eigen::JacobiSVD<vtkMatrixXd> svd(covariance,
      Eigen::ComputeThinV);

    const unsigned int numberOfComponents
      = std::min((svd.singularValues().array()
      > vtkShapeModelData::EPSILON).count(), matrix.rows() - 1);

    if(numberOfComponents == 0)
      {
      vtkErrorMacro(<< "Invalid shape model computed");
      return 0;
      }

    const vtkVectorXd sqrtSingularValues
      = svd.singularValues().array().sqrt();
    vtkVectorXd pseudoInverse
      = vtkVectorXd::Zero(sqrtSingularValues.rows());

    for(unsigned int i = 0; i < numberOfComponents; ++i)
      {
      pseudoInverse(i) = 1.0 / sqrtSingularValues(i);
      }

    output1->SetVariance(svd.singularValues().topRows(numberOfComponents)
      - vtkVectorXd::Ones(numberOfComponents) * vtkShapeModelData::EPSILON);

    const vtkVectorXd diagonal = output1->GetVariance().array().sqrt();
    const vtkMatrixXd orthonormalBasis
      = (demeaned.transpose() * svd.matrixV() * pseudoInverse.asDiagonal()
      / std::sqrt(matrix.rows() - 1.0)).topLeftCorner(matrix.cols(),
      numberOfComponents);

    output1->SetBasis(orthonormalBasis * vtkDiagonalMatrixXd(diagonal));
    }
  else
    {
    const vtkMatrixXd covariance
      = demeaned.transpose() * demeaned * 1.0 / (matrix.rows() - 1.0);
    const Eigen::JacobiSVD<vtkMatrixXd> svd(covariance, Eigen::ComputeThinU);

    const unsigned int numberOfComponents = (svd.singularValues().array()
      > vtkShapeModelData::EPSILON).count();

    if(numberOfComponents == 0)
      {
      vtkErrorMacro(<< "Invalid shape model computed");
      return 0;
      }

    output1->SetVariance(svd.singularValues().topRows(numberOfComponents)
      - vtkVectorXd::Ones(numberOfComponents) * vtkShapeModelData::EPSILON);

    const vtkVectorXd diagonal = output1->GetVariance().array().sqrt();
    const vtkMatrixXd orthonormalBasis
      = svd.matrixU().topLeftCorner(matrix.cols(), vtkShapeModelData::EPSILON);

    output1->SetBasis(orthonormalBasis * vtkDiagonalMatrixXd(diagonal));
    }

  vtkShapeModelUtilities::VectorXdToPolyData(output1->GetMean(), output0);
  return 1;
}
