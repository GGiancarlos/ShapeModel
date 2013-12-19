/*============================================================================

  Library:  Image Segmentation Using Statistical Shape Models
  File:     vtkShapeModelUtilities.cxx

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

#include "vtkShapeModelUtilities.h"

#include <vtkMath.h>
#include <vtkPointSet.h>
#include <vtkPolyData.h>

//----------------------------------------------------------------------------
double vtkShapeModelUtilities::Distance2BetweenPointSets(
  vtkPointSet *pointSet0, vtkPointSet *pointSet1)
{
  double distance2 = 0.0;

  for(vtkIdType i = 0; i < pointSet0->GetNumberOfPoints(); ++i)
    {
    double point0[3];
    pointSet0->GetPoints()->GetPoint(i, point0);

    const vtkIdType pointId = pointSet1->FindPoint(point0);

    double point1[3];
    pointSet1->GetPoints()->GetPoint(pointId, point1);

    distance2 += vtkMath::Distance2BetweenPoints(point0, point1);
    }

  return distance2 /= pointSet0->GetNumberOfPoints();
}

//----------------------------------------------------------------------------
vtkVectorXd vtkShapeModelUtilities::PointSetToVectorXd(vtkPointSet *pointSet)
{
  vtkVectorXd vector(pointSet->GetNumberOfPoints() * 3);

  for(vtkIdType i = 0; i < pointSet->GetNumberOfPoints(); ++i)
    {
    double point[3];
    pointSet->GetPoint(i, point);

    for(vtkIdType j = 0; j < 3; ++j)
      {
      vector(i * 3 + j) = point[j];
      }
    }

  return vector;
}

//----------------------------------------------------------------------------
void vtkShapeModelUtilities::VectorXdToPolyData(const vtkVectorXd &vector,
  vtkPolyData *polyData)
{
  const vtkIdType numberOfPoints = static_cast<vtkIdType>(vector.size()) / 3;
  vtkPoints *const points = vtkPoints::New();
  points->SetDataTypeToDouble();
  points->Allocate(numberOfPoints);

  for(vtkIdType i = 0; i < numberOfPoints; ++i)
    {
    double point[3];

    for(vtkIdType j = 0; j < 3; ++j)
      {
      point[j] = vector(i * 3 + j);
      }

    points->InsertNextPoint(point);
    }

  points->Squeeze();
  polyData->SetPoints(points);
  points->Delete();
}
