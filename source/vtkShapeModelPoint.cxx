/*============================================================================

  Library:  Image Segmentation Using Statistical Shape Models
  File:     vtkShapeModelPoint.cxx

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

#include "vtkShapeModelPoint.h"

#include <vtkObjectFactory.h>

vtkStandardNewMacro(vtkShapeModelPoint)

//----------------------------------------------------------------------------
vtkShapeModelPoint::vtkShapeModelPoint()
{
  for(vtkIdType i = 0; i < 3; ++i)
    {
    this->Data[i] = 0.0;
    }
}

//----------------------------------------------------------------------------
vtkShapeModelPoint::~vtkShapeModelPoint()
{
}

//----------------------------------------------------------------------------
void vtkShapeModelPoint::PrintSelf(ostream &os, vtkIndent indent)
{
  vtkDataObject::PrintSelf(os, indent);

  os << indent << "Data: (" << this->Data[0] << ", " << this->Data[1] << ", "
     << this->Data[2] << ")\n";
}
