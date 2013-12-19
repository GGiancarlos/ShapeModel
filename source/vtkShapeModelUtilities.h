/*============================================================================

  Library:  Image Segmentation Using Statistical Shape Models
  File:     vtkShapeModelUtilities.h

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

// .NAME vtkShapeModelUtilities - utility functions

#ifndef __vtkShapeModelUtilities_h
#define __vtkShapeModelUtilities_h

#include "vtkEigen.h" // For type definitions.
#include "vtkShapeModelModule.h" // For export macro.

#include <vtkSetGet.h>

class vtkPointSet;
class vtkPolyData;

class VTKSHAPEMODEL_EXPORT vtkShapeModelUtilities
{
public:
  // Description:
  // Compute the sum of squared distances between closest points in two point
  // sets.
  static double Distance2BetweenPointSets(vtkPointSet *pointSet0,
    vtkPointSet *pointSet1);

  // Description:
  // Convert a point set with N points to an vtkVectorXd of length 3N.
  static vtkVectorXd PointSetToVectorXd(vtkPointSet *pointSet);

  // Description:
  // Convert an vtkVectorXd of length 3N to a polydata with N points.
  static void VectorXdToPolyData(const vtkVectorXd &vector,
    vtkPolyData *polyData);

protected:
  vtkShapeModelUtilities(); // Not implemented.
  ~vtkShapeModelUtilities(); // Not implemented.

private:
  vtkShapeModelUtilities(const vtkShapeModelUtilities &other); // Not implemented.
  vtkShapeModelUtilities &operator=(const vtkShapeModelUtilities &other); // Not implemented.
};

#endif
