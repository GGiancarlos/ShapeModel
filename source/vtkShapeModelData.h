/*============================================================================

  Library:  Image Segmentation Using Statistical Shape Models
  File:     vtkShapeModelData.h

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

// .NAME vtkShapeModelData - statistical shape model data

#ifndef __vtkShapeModelData_h
#define __vtkShapeModelData_h

#include "vtkEigen.h" // For type definitions.
#include "vtkShapeModelModule.h" // For export macro.

#include <vtkDataObject.h>

class VTKSHAPEMODEL_EXPORT vtkShapeModelData : public vtkDataObject
{
public:
  // Description:
  // A small constant to account for uncertainty in a model.
  static const double EPSILON;

  // Description:
  // Create a new object instance.
  static vtkShapeModelData *New();

  vtkTypeMacro(vtkShapeModelData,vtkDataObject);

  // Description:
  // Set/get the basis of the modes of this model.
  void SetBasis(const vtkMatrixXd &basis);
  const vtkMatrixXd &GetBasis() const;

  // Description:
  // Set/get the mean of this model.
  void SetMean(const vtkVectorXd &mean);
  const vtkVectorXd &GetMean() const;

  // Description:
  // Set/get the variance of the modes of this model.
  void SetVariance(const vtkVectorXd &variance);
  const vtkVectorXd &GetVariance() const;

  // Description:
  // Print information about this object instance.
  void PrintSelf(ostream &os, vtkIndent indent);

protected:
  vtkShapeModelData();
  ~vtkShapeModelData();

  vtkMatrixXd Basis;
  vtkVectorXd Mean;
  vtkVectorXd Variance;

private:
  vtkShapeModelData(const vtkShapeModelData &other); // Not implemented.
  vtkShapeModelData &operator=(const vtkShapeModelData &other); // Not implemented.
};

#endif
