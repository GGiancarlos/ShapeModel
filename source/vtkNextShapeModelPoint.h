/*============================================================================

  Library:  Image Segmentation Using Statistical Shape Models
  File:     vtkNextShapeModelPoint.h

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

// .NAME vtkNextShapeModelPoint - choose the next point

#ifndef __vtkNextShapeModelPoint_h
#define __vtkNextShapeModelPoint_h

#include "vtkShapeModelModule.h" // For export macro.

#include <vtkDataObjectAlgorithm.h>

class vtkMinimalStandardRandomSequence;
class vtkPointLocator;
class vtkShapeModelPoint;

class VTKSHAPEMODEL_EXPORT vtkNextShapeModelPoint
  : public vtkDataObjectAlgorithm
{
public:
  // Description:
  // Create a new algorithm instance.
  static vtkNextShapeModelPoint *New();

  vtkTypeMacro(vtkNextShapeModelPoint,vtkDataObjectAlgorithm);

  // Description:
  // Get the point locator object.
  vtkGetObjectMacro(PointLocator,vtkPointLocator);

  // Description:
  // Get the random sequence object used in part for selecting points.
  vtkGetObjectMacro(RandomSequence,vtkMinimalStandardRandomSequence);

  // Description:
  // Set/get the seed for the random sequence object.
  vtkSetMacro(RandomSequenceSeed,int);
  vtkGetMacro(RandomSequenceSeed,int);

  // Description:
  // Set/get the squared distance between the chosen point and its nearest
  // neighbor.
  vtkSetMacro(SquaredDistance,double);
  vtkGetMacro(SquaredDistance,double);

  // Description:
  // Get the output of this algorithm instance.
  vtkShapeModelPoint *GetOutput();

  // Description:
  // Print information about this algorithm instance.
  void PrintSelf(ostream &os, vtkIndent indent);

protected:
  vtkNextShapeModelPoint();
  ~vtkNextShapeModelPoint();

  // Description:
  // Fill the input port information objects for this algorithm.
  // PORT 0 - vtkPointSet containing points from which to choose next.
  // PORT 1 - vtkPointSet containing points previously chosen.
  int FillInputPortInformation(int port, vtkInformation *information);

  // Description:
  // Fill the output port information objects for this algorithm.
  // PORT 0 - vtkShapeModelPoint containing the point to choose next.
  int FillOutputPortInformation(int port, vtkInformation *information);

  // Description:
  // Implement the algorithm.
  int RequestData(vtkInformation *request, vtkInformationVector **inputVector,
    vtkInformationVector *outputVector);

  vtkPointLocator *PointLocator;
  vtkMinimalStandardRandomSequence *RandomSequence;
  int RandomSequenceSeed;
  double SquaredDistance;

private:
  vtkNextShapeModelPoint(const vtkNextShapeModelPoint &other); // Not implemented.
  vtkNextShapeModelPoint &operator=(const vtkNextShapeModelPoint &other); // Not implemented.
};

#endif
