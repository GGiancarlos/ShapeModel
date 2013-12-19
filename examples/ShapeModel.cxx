/*============================================================================

  Library:  Image Segmentation Using Statistical Shape Models
  File:     ShapeModel.cxx

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

#include <vtkShapeModel.h>

#include <vtkMultiBlockDataSet.h>
#include <vtkPolyData.h>
#include <vtkProcrustesAlignmentFilter.h>
#include <vtkSmartPointer.h>

int main()
{
  // Display image.

  vtkSmartPointer<vtkMultiBlockDataSet> data
    = vtkSmartPointer<vtkMultiBlockDataSet>::New();

  // Load training data.

  vtkSmartPointer<vtkProcrustesAlignmentFilter> procrustes
    = vtkSmartPointer<vtkProcrustesAlignmentFilter>::New();
  procrustes->SetInputData(data);

  vtkSmartPointer<vtkBuildShapeModel> build
    = vtkSmartPointer<vtkBuildShapeModel>::New();
  build->SetInputConnection(procrustes->GetOutputPort());
  build->Update();
  vtkSmartPointer<vtkPolyData> mean = build->GetOutput(0);

  // Create mesh of mean shape.

  // Display mean shape.

  // Rotate image if necessary.

  vtkSmartPointer<vtkPolyData> points
    = vtkSmartPointer<vtkPolyData>::New();

  // Choose some points on boundary of image.

  vtkSmartPointer<vtkFitShapeModel> fit
    = vtkSmartPointer<vtkFitShapeModel>::New();
  fit->SetInputData(0, points);
  fit->SetInputConnection(1, build->GetOutputPort(1));
  fit->SetInputConnection(2, build->GetOutputPort(0));
  fit->Update();
  vtkSmartPointer<vtkPolyData> segmentation = fit->GetOutput();

  // Create mesh of segmentation.

  // Display segmentation.

  // Rotate image if necessary.

  vtkSmartPointer<vtkNextShapeModelPoint> choose
    = vtkSmartPointer<vtkNextShapeModelPoint>::New();
  choose->SetInputData(0, segmentation);
  choose->SetInputData(1, points);

  const double THRESHOLD = 1.0e-12;

  while(fit->GetMeanSquaredError() < THRESHOLD)
    {
    choose->Update();

    vtkSmartPointer<vtkShapeModelPoint> next = choose->GetOutput();

    double point[3];
    next->GetData(point);

    // Display point.

    // Adjust position of point if necessary.

    points->GetPoints()->InsertNextPoint(point);

    fit->Update();
    segmentation = fit->GetOutput();

    // Create mesh of segmentation.

    // Display segmentation.

    // Rotate image if necessary.
    }

  return 0;
}
