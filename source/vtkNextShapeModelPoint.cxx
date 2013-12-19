/*============================================================================

  Library:  Image Segmentation Using Statistical Shape Models
  File:     vtkNextShapeModelPoint.cxx

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

#include "vtkNextShapeModelPoint.h"

#include "vtkShapeModelPoint.h"

#include <vtkDoubleArray.h>
#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkObjectFactory.h>
#include <vtkMath.h>
#include <vtkMinimalStandardRandomSequence.h>
#include <vtkPointLocator.h>
#include <vtkPointSet.h>

vtkStandardNewMacro(vtkNextShapeModelPoint)

//----------------------------------------------------------------------------
vtkNextShapeModelPoint::vtkNextShapeModelPoint()
{
  this->PointLocator = NULL;
  this->RandomSequence = NULL;
  this->RandomSequenceSeed = 1;
  this->SquaredDistance = 0.0;

  this->SetNumberOfInputPorts(2);
}

//----------------------------------------------------------------------------
vtkNextShapeModelPoint::~vtkNextShapeModelPoint()
{
  if(PointLocator != NULL)
    {
    this->PointLocator->Delete();
    }

  if(RandomSequence != NULL)
    {
    this->RandomSequence->Delete();
    }
}

//----------------------------------------------------------------------------
vtkShapeModelPoint *vtkNextShapeModelPoint::GetOutput()
{
  return vtkShapeModelPoint::SafeDownCast(
    vtkDataObjectAlgorithm::GetOutput());
}

//----------------------------------------------------------------------------
void vtkNextShapeModelPoint::PrintSelf(ostream &os, vtkIndent indent)
{
  vtkDataObjectAlgorithm::PrintSelf(os, indent);

  os << indent << "Point Locator: "
     << (this->PointLocator == NULL ? "(null)" : "") << "\n";
  os << indent << "Random Sequence: "
     << (this->RandomSequence == NULL ? "(null)" : "") << "\n";
  os << indent << "Random Sequence Seed: " << this->RandomSequenceSeed
     << "\n";
  os << indent << "Squared Distance: " << this->SquaredDistance << "\n";
}

//----------------------------------------------------------------------------
int vtkNextShapeModelPoint::FillInputPortInformation(int port,
  vtkInformation *information)
{
  if(!vtkDataObjectAlgorithm::FillInputPortInformation(port, information))
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
    information->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkPointSet");
    return 1;
    }

  vtkErrorMacro(<< "Invalid input port");
  return 0;
}

//----------------------------------------------------------------------------
int vtkNextShapeModelPoint::FillOutputPortInformation(int port,
  vtkInformation *information)
{
  if(!vtkDataObjectAlgorithm::FillOutputPortInformation(port, information))
    {
    return 0;
    }

  information->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkShapeModelPoint");
  return 1;
}

//----------------------------------------------------------------------------
int vtkNextShapeModelPoint::RequestData(vtkInformation *vtkNotUsed(request),
  vtkInformationVector **inputVector, vtkInformationVector *outputVector)
{
  if(this->PointLocator == NULL)
    {
    this->PointLocator = vtkPointLocator::New();
    }

  if(this->RandomSequence == NULL)
    {
    this->RandomSequence = vtkMinimalStandardRandomSequence::New();
    this->RandomSequence->SetSeed(this->RandomSequenceSeed);
    }

  vtkInformation *const inputInformation0
    = inputVector[0]->GetInformationObject(0);
  vtkInformation *const inputInformation1
    = inputVector[1]->GetInformationObject(0);
  vtkInformation *const outputInformation
    = outputVector->GetInformationObject(0);

  vtkPointSet *const input0 = vtkPointSet::SafeDownCast(
    inputInformation0->Get(vtkDataObject::DATA_OBJECT()));
  vtkPointSet *const input1 = vtkPointSet::SafeDownCast(
    inputInformation1->Get(vtkDataObject::DATA_OBJECT()));
  vtkShapeModelPoint *const output = vtkShapeModelPoint::SafeDownCast(
    outputInformation->Get(vtkDataObject::DATA_OBJECT()));

  if(input0 == NULL || input1 == NULL || output == NULL || input0->GetNumberOfPoints() == 0)
    {
    vtkErrorMacro(<< "Invalid input(s) or output");
    return 0;
    }

  this->PointLocator->SetDataSet(input1);
  this->PointLocator->BuildLocator();

  double point[3];
  this->SquaredDistance = 0.0;

  for(vtkIdType i = 0; i < input0->GetNumberOfPoints(); ++i)
    {
    double point0[3];
    input0->GetPoint(i, point0);
    const vtkIdType pointId = this->PointLocator->FindClosestPoint(point0);
    double point1[3];
    input1->GetPoint(pointId, point1);
    const double squaredDistance = vtkMath::Distance2BetweenPoints(point0, point1);

    if(squaredDistance > this->SquaredDistance)
      {
      for(vtkIdType j = 0; j < 3; ++j)
        {
        point[j] = point0[j];
        }

      this->SquaredDistance = squaredDistance;
      }
    }

  output->SetData(point);
  return 1;
}
