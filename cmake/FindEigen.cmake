##############################################################################
#
#  Library:  Image Segmentation Using Statistical Shape Models
#  File:     FindEigen.cmake
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

find_package(PkgConfig)
pkg_check_modules(PC_Eigen QUIET eigen3)
find_path(Eigen_INCLUDE_DIR Eigen/Eigen
  HINTS ${PC_Eigen_INCLUDEDIR} ${PC_Eigen_INCLUDE_DIRS}
  PATH_SUFFIXES eigen3)
set(Eigen_INCLUDE_DIRS ${Eigen_INCLUDE_DIR})
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Eigen DEFAULT_MSG Eigen_INCLUDE_DIR)
mark_as_advanced(Eigen_INCLUDE_DIR)
