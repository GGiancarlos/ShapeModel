/*============================================================================

  Library:  Image Segmentation Using Statistical Shape Models
  File:     vtkFitShapeModel.cxx

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

============================================================================*/

#include "vtkFitShapeModel.h"

#include "vtkEigen.h"
#include "vtkShapeModelData.h"
#include "vtkShapeModelUtilities.h"

#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkObjectFactory.h>
#include <vtkPolyData.h>

vtkStandardNewMacro(vtkFitShapeModel)

//----------------------------------------------------------------------------
vtkFitShapeModel::vtkFitShapeModel()
{
  this->MeanSquaredError = VTK_DOUBLE_MAX;
  this->SetNumberOfInputPorts(3);
}

//----------------------------------------------------------------------------
vtkFitShapeModel::~vtkFitShapeModel()
{
}

//----------------------------------------------------------------------------
void vtkFitShapeModel::PrintSelf(ostream &os, vtkIndent indent)
{
  vtkPolyDataAlgorithm::PrintSelf(os, indent);

  os << indent << "Mean Squared Error: " << this->MeanSquaredError << "\n";
}

//----------------------------------------------------------------------------
int vtkFitShapeModel::FillInputPortInformation(int port,
  vtkInformation *information)
{
  if(!vtkPolyDataAlgorithm::FillInputPortInformation(port, information))
    {
    return 0;
    }

  if(port == 0)
    {
    information->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkPointSet");
    return 1;
    }

  if(port == 1)
    {
    information->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(),
      "vtkShapeModelData");
    return 1;
    }

  if(port == 2)
    {
    information->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkPointSet");
    return 1;
    }

  vtkErrorMacro(<< "Invalid input port");
  return 0;
}

//----------------------------------------------------------------------------
int vtkFitShapeModel::RequestData(vtkInformation *vtkNotUsed(request),
  vtkInformationVector **inputVector, vtkInformationVector *outputVector)
{
  vtkInformation *const inputInformation0
    = inputVector[0]->GetInformationObject(0);
  vtkInformation *const inputInformation1
    = inputVector[1]->GetInformationObject(0);
  vtkInformation *const inputInformation2
    = inputVector[2]->GetInformationObject(0);
  vtkInformation *const outputInformation
    = outputVector->GetInformationObject(0);

  vtkPointSet *const input0 = vtkPointSet::SafeDownCast(
    inputInformation0->Get(vtkDataObject::DATA_OBJECT()));
  vtkShapeModelData *const input1 = vtkShapeModelData::SafeDownCast(
    inputInformation1->Get(vtkDataObject::DATA_OBJECT()));
  vtkPointSet *const input2 = vtkPointSet::SafeDownCast(
    inputInformation2->Get(vtkDataObject::DATA_OBJECT()));
  vtkPolyData *const output = vtkPolyData::SafeDownCast(
    outputInformation->Get(vtkDataObject::DATA_OBJECT()));

  if(input0 == NULL || input1 == NULL || input2 == NULL || output == NULL)
    {
    vtkErrorMacro(<< "Invalid input(s) or output");
    return 0;
    }

  vtkMatrixXd basis(input0->GetNumberOfPoints() * 3,
    input1->GetBasis().cols());
  vtkVectorXd mean(basis.rows());
  vtkVectorXd vector(basis.rows());

  for(vtkIdType i = 0; i < input0->GetNumberOfPoints(); ++i)
    {
    double point0[3];
    input0->GetPoint(i, point0);

    const vtkIdType id = input2->FindPoint(point0);

    for(vtkIdType j = 0; j < 3; ++j)
      {
      basis.row(i * 3 + j) = input1->GetBasis().row(id * 3 + j);
      mean(i * 3 + j) = input1->GetMean()(id * 3 + j);
      vector(i * 3 + j) = point0[j];
      }
    }

  vtkMatrixXd matrix = basis.transpose() * basis;
  matrix.diagonal()
    += vtkShapeModelData::EPSILON * vtkVectorXd::Ones(basis.cols());
  const vtkVectorXd coefficients
    = matrix.inverse() * basis.transpose() * (vector - mean);

  vtkShapeModelUtilities::VectorXdToPolyData(
    input1->GetMean() + input1->GetBasis() * coefficients, output);
  this->MeanSquaredError
    = vtkShapeModelUtilities::Distance2BetweenPointSets(input0, output);

  return 1;
}
