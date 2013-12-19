/*============================================================================

  Library:  Image Segmentation Using Statistical Shape Models
  File:     vtkBuildShapeModel.h

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

// .NAME vtkBuildShapeModel - build a statistical shape model

#ifndef __vtkBuildShapeModel_h
#define __vtkBuildShapeModel_h

#include "vtkShapeModelModule.h" // For export macro.

#include <vtkPolyDataAlgorithm.h>

class vtkMultiBlockDataSet;

class VTKSHAPEMODEL_EXPORT vtkBuildShapeModel : public vtkPolyDataAlgorithm
{
public:
  // Description:
  // Create a new algorithm instance.
  static vtkBuildShapeModel *New();

  vtkTypeMacro(vtkBuildShapeModel,vtkPolyDataAlgorithm);

  // Description:
  // Get the output of this algorithm instance. This method is not recommended
  // for use, but many old-style filters use it.
  vtkMultiBlockDataSet *GetInput();

  // Description:
  // Print information about this algorithm instance.
  void PrintSelf(ostream &os, vtkIndent indent);

protected:
  vtkBuildShapeModel();
  ~vtkBuildShapeModel();

  // Description:
  // Fill the input port information objects for this algorithm.
  // PORT 0 - vtkMultiBlockDataSet containing vtkPointSet.
  int FillInputPortInformation(int port, vtkInformation *information);

  // Description:
  // Fill the output port information objects for this algorithm.
  // PORT 0 - vtkPolyData containing the mean shape.
  // PORT 1 - vtkShapeModelData containing the model.
  int FillOutputPortInformation(int port, vtkInformation *information);

  // Description:
  // Implement the algorithm.
  int RequestData(vtkInformation *request, vtkInformationVector **inputVector,
    vtkInformationVector *outputVector);

private:
  vtkBuildShapeModel(const vtkBuildShapeModel &other); // Not implemented.
  vtkBuildShapeModel &operator=(const vtkBuildShapeModel &other); // Not implemented.
};

#endif
