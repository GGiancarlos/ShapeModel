/*============================================================================

  Library:  Image Segmentation Using Statistical Shape Models
  File:     vtkEigen.h

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

// .NAME vtkEigen - convenience header relating to the Eigen library

#ifndef __vtkEigen_h
#define __vtkEigen_h

#ifdef __GNUC__
#pragma GCC system_header
#endif

#include <Eigen/Eigen>

typedef Eigen::DiagonalMatrix<double, Eigen::Dynamic> vtkDiagonalMatrixXd;
typedef Eigen::MatrixXd vtkMatrixXd;
typedef Eigen::RowVectorXd vtkRowVectorXd;
typedef Eigen::VectorXd vtkVectorXd;

#endif
