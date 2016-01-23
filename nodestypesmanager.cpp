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

#include "nodestypesmanager.h"

#include <QDebug>

#include "nodesviews/blurwidget.h"
#include "nodesviews/dockableimageviewerwidget.h"
#include "nodesviews/gaussianblurwidget.h"
#include "nodesviews/imagefromfilewidget.h"
#include "nodesviews/imagepreviewerwidget.h"
#include "nodesviews/medianblurwidget.h"
#include "processors/blurprocessor.h"
#include "processors/gaussianblurprocessor.h"
#include "processors/imagefromfileprocessor.h"
#include "processors/imagepreviewerprocessor.h"
#include "processors/dockableimageviewerprocessor.h"
#include "processors/medianblurprocessor.h"


QList<QTreeWidgetItem *> NodesTypesManager::getTreeItems()
{
    #warning Do this somewhere else
    qRegisterMetaType<BlurProcessor>();
    qRegisterMetaType<BlurWidget>();
    qRegisterMetaType<ImageFromFileProcessor>();
    qRegisterMetaType<ImageFromFileWidget>();
    qRegisterMetaType<ImagePreviewerProcessor>();
    qRegisterMetaType<ImagePreviewerWidget>();
    qRegisterMetaType<DockableImageViewerProcessor>();
    qRegisterMetaType<DockableImageViewerWidget>();
    qRegisterMetaType<GaussianBlurProcessor>();
    qRegisterMetaType<GaussianBlurWidget>();
    qRegisterMetaType<MedianBlurProcessor>();
    qRegisterMetaType<MedianBlurWidget>();

    QList<QTreeWidgetItem *> result;

    QTreeWidgetItem *inputs = new QTreeWidgetItem(QStringList() << "Inputs");
    inputs->setFlags(inputs->flags() & ~Qt::ItemIsDragEnabled);
    QTreeWidgetItem *itemFile = new QTreeWidgetItem(inputs, QStringList() << "Image from file");
    itemFile->setData(0, Qt::UserRole, "ImageFromFile");
    result << inputs;

    QTreeWidgetItem *viewers = new QTreeWidgetItem(QStringList() << "Viewers");
    viewers->setFlags(viewers->flags() & ~Qt::ItemIsDragEnabled);
    QTreeWidgetItem *itemDockableViewer = new QTreeWidgetItem(viewers, QStringList() << "Dockable image viewer");
    itemDockableViewer->setData(0, Qt::UserRole, "DockableImageViewer");
    QTreeWidgetItem *itemPreviewer = new QTreeWidgetItem(viewers, QStringList() << "Image previewer");
    itemPreviewer->setData(0, Qt::UserRole, "ImagePreviewer");
    result << viewers;

    QTreeWidgetItem *filters = new QTreeWidgetItem(QStringList() << "Filters");
    filters->setFlags(viewers->flags() & ~Qt::ItemIsDragEnabled);
    QTreeWidgetItem *itemBlur = new QTreeWidgetItem(filters, QStringList() << "Blur");
    itemBlur->setData(0, Qt::UserRole, "Blur");
    QTreeWidgetItem *itemGaussianBlur = new QTreeWidgetItem(filters, QStringList() << "Gaussian blur");
    itemGaussianBlur->setData(0, Qt::UserRole, "GaussianBlur");
    QTreeWidgetItem *itemMedianBlur = new QTreeWidgetItem(filters, QStringList() << "Median blur");
    itemMedianBlur->setData(0, Qt::UserRole, "MedianBlur");
    result << filters;

    return result;
}
