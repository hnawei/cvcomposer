// Copyright 2016 Erwan MATHIEU <wawanbreton@gmail.com>
//
// This file is part of CvComposer.
//
// CvComposer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CvComposer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CvComposer.  If not, see <http://www.gnu.org/licenses/>.

#include "houghcircleprocessor.h"

#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>

#include "model/circle.h"
#include "global/cvutils.h"
#include "global/utils.h"


HoughCircleProcessor::HoughCircleProcessor()
{
    addInput("input image", PlugType::Image);

    QList<QPair<QString, QVariant> > methods;
    methods << QPair<QString, QVariant>("Standard", CV_HOUGH_STANDARD);
    methods << QPair<QString, QVariant>("Probabilistic", CV_HOUGH_PROBABILISTIC);
    methods << QPair<QString, QVariant>("Multi scale", CV_HOUGH_MULTI_SCALE);
    methods << QPair<QString, QVariant>("Gradient", CV_HOUGH_GRADIENT);
    addEnumerationInput("method", methods, 0);

    Properties ratioProperties;
    ratioProperties.insert("decimals", 0);
    ratioProperties.insert("minimum", 1);
    addInput("inverse resolution ratio", PlugType::Double, 1, ratioProperties);

    addInput("minimum centers distance", PlugType::Double, 2);
    addInput("specific parameter 1", PlugType::Double, 100);
    addInput("specific parameter 2", PlugType::Double, 100);

    Properties radiusProperties;
    radiusProperties.insert("decimals", 0);
    radiusProperties.insert("minimum", 0);
    addInput("minimum radius", PlugType::Double, 0, radiusProperties);
    addInput("maximum radius", PlugType::Double, 0, radiusProperties);

    addOutput("circles", PlugType::Circle, true);
}

Properties HoughCircleProcessor::processImpl(const Properties &inputs)
{
    cv::Mat inputImage = inputs["input image"].value<cv::Mat>();
    cv::vector<cv::Vec3f> circles;

    cv::HoughCircles(inputImage,
                     circles,
                     inputs["method"].toInt(),
                     inputs["inverse resolution ratio"].toDouble(),
                     inputs["minimum centers distance"].toDouble(),
                     inputs["specific parameter 1"].toDouble(),
                     inputs["specific parameter 2"].toDouble(),
                     inputs["minimum radius"].toDouble(),
                     inputs["maximum radius"].toDouble());

    Properties outputs;

    QList<QVariant> outputCircles;

    for(const cv::Vec3f &pseudoCircle : circles)
    {
        Circle circle;
        circle.center.x = pseudoCircle[0];
        circle.center.y = pseudoCircle[1];
        circle.radius = pseudoCircle[2];

        outputCircles << QVariant::fromValue(circle);
    }

    outputs.insert("circles", QVariant::fromValue(outputCircles));

    return outputs;
}

