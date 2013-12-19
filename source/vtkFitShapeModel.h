/*============================================================================

  Library:  Image Segmentation Using Statistical Shape Models
  File:     vtkFitShapeModel.h

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

// .NAME vtkFitShapeModel - fit a statistical shape model

#ifndef __vtkFitShapeModel_h
#define __vtkFitShapeModel_h

#include "vtkShapeModelModule.h" // For export macro.

#include <vtkPolyDataAlgorithm.h>

class VTKSHAPEMODEL_EXPORT vtkFitShapeModel : public vtkPolyDataAlgorithm
{
public:
  // Description:
  // Create a new algorithm instance.
  static vtkFitShapeModel *New();

  vtkTypeMacro(vtkFitShapeModel,vtkPolyDataAlgorithm);

  // Description:
  // Get the mean squared error of the model fit.
  vtkGetMacro(MeanSquaredError,double);

  // Description:
  // Print information about this algorithm instance.
  void PrintSelf(ostream &os, vtkIndent indent);

protected:
  vtkFitShapeModel();
  ~vtkFitShapeModel();

  // Description:
  // Fill the input port information objects for this algorithm.
  // PORT 0 - vtkPointSet containing the points to fit.
  // PORT 1 - vtkShapeModelData containing the model.
  // PORT 2 - vtkPointSet last model fit or mean shape initially.
  int FillInputPortInformation(int port, vtkInformation *information);

  // Description:
  // Implement the algorithm.
  int RequestData(vtkInformation *request, vtkInformationVector **inputVector,
    vtkInformationVector *outputVector);

  double MeanSquaredError;

private:
  vtkFitShapeModel(const vtkFitShapeModel &other); // Not implemented.
  vtkFitShapeModel &operator=(const vtkFitShapeModel &other); // Not implemented.
};

#endif
