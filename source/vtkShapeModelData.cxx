/*============================================================================

  Library:  Image Segmentation Using Statistical Shape Models
  File:     vtkShapeModelData.cxx

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

#include "vtkShapeModelData.h"

#include <vtkObjectFactory.h>

vtkStandardNewMacro(vtkShapeModelData)

//----------------------------------------------------------------------------
const double vtkShapeModelData::EPSILON = 1.0e-6;

//----------------------------------------------------------------------------
vtkShapeModelData::vtkShapeModelData()
{
}

//----------------------------------------------------------------------------
vtkShapeModelData::~vtkShapeModelData()
{
}

//----------------------------------------------------------------------------
void vtkShapeModelData::SetBasis(const vtkMatrixXd &basis)
{
  if(this->Basis != basis)
    {
    this->Basis = basis;
    this->Modified();
    }
}

//----------------------------------------------------------------------------
const vtkMatrixXd &vtkShapeModelData::GetBasis() const
{
  return this->Basis;
}

//----------------------------------------------------------------------------
void vtkShapeModelData::SetMean(const vtkVectorXd &mean)
{
  if(this->Mean != mean)
    {
    this->Mean = mean;
    this->Modified();
    }
}

//----------------------------------------------------------------------------
const vtkVectorXd &vtkShapeModelData::GetMean() const
{
  return this->Mean;
}

//----------------------------------------------------------------------------
void vtkShapeModelData::SetVariance(const vtkVectorXd &variance)
{
  if(this->Variance != variance)
    {
    this->Variance = variance;
    this->Modified();
    }
}

//----------------------------------------------------------------------------
const vtkVectorXd &vtkShapeModelData::GetVariance() const
{
  return this->Variance;
}

//----------------------------------------------------------------------------
void vtkShapeModelData::PrintSelf(ostream &os, vtkIndent indent)
{
  vtkDataObject::PrintSelf(os, indent);

  os << indent << "Basis: " << this->Basis << "\n";
  os << indent << "Mean: " << this->Mean << "\n";
  os << indent << "Variance: " << this->Variance << "\n";
}
