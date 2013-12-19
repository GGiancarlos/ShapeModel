##############################################################################
#
#  Library:  Image Segmentation Using Statistical Shape Models
#  File:     CMakeLists.txt
#
#  Copyright 2013 Kitware, Inc. All rights reserved.
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
##############################################################################

include(GenerateExportHeader)

set(VTK_SHAPE_MODEL_HEADERS
  vtkBuildShapeModel.h
  vtkEigen.h
  vtkFitShapeModel.h
  vtkNextShapeModelPoint.h
  vtkShapeModel.h
  vtkShapeModelData.h
  vtkShapeModelPoint.h
  vtkShapeModelUtilities.h)

set(VTK_SHAPE_MODEL_SOURCES
  vtkBuildShapeModel.cxx
  vtkFitShapeModel.cxx
  vtkNextShapeModelPoint.cxx
  vtkShapeModelData.cxx
  vtkShapeModelPoint.cxx
  vtkShapeModelUtilities.cxx)

add_library(vtkShapeModel ${VTK_SHAPE_MODEL_HEADERS} ${VTK_SHAPE_MODEL_SOURCES})
generate_export_header(vtkShapeModel EXPORT_FILE_NAME vtkShapeModelModule.h)
target_link_libraries(vtkShapeModel ${VTK_LIBRARIES})

install(FILES ${VTK_SHAPE_MODEL_HEADERS} DESTINATION include)
install(TARGETS vtkShapeModel DESTINATION lib)
