/*============================================================================

  Library:  Image Segmentation Using Statistical Shape Models
  File:     vtkShapeModelPoint.h

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

// .NAME vtkShapeModelPoint - wrapper for a point in a statistical shape model

#ifndef __vtkShapeModelPoint_h
#define __vtkShapeModelPoint_h

#include "vtkShapeModelModule.h" // For export macro.

#include <vtkDataObject.h>

class VTKSHAPEMODEL_EXPORT vtkShapeModelPoint : public vtkDataObject
{
public:
  // Description:
  // Create a new object instance.
  static vtkShapeModelPoint *New();

  vtkTypeMacro(vtkShapeModelPoint,vtkDataObject);

  // Description:
  // Set/get the coordinates of this wrapped point.
  vtkSetVector3Macro(Data,double);
  vtkGetVector3Macro(Data,double);

  // Description:
  // Print information about this object instance.
  void PrintSelf(ostream &os, vtkIndent indent);

protected:
  vtkShapeModelPoint();
  ~vtkShapeModelPoint();

  double Data[3];

private:
  vtkShapeModelPoint(const vtkShapeModelPoint &other); // Not implemented.
  vtkShapeModelPoint &operator=(const vtkShapeModelPoint &other); // Not implemented.
};

#endif
