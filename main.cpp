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

#include <QApplication>

#include "gui/mainwidget.h"
#include "processor/input/cameraprocessor.h"
#include "gui/cvcomposerstyle.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setApplicationName("CvComposer");
    QCoreApplication::setOrganizationName("CvComposer");

    a.setStyle(new CvComposerStyle());

    MainWidget w;
    w.show();

    int result = a.exec();

    // We need to cleanup the camera resources at some point before exiting, or OpenCV will
    // keep a handle and not allow the application to exit
    CameraProcessor::cleanup();

    return result;
}
