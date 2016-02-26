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

#ifndef COMPOSERSCENE_H
#define COMPOSERSCENE_H

#include <QGraphicsScene>

#include <QGraphicsSceneDragDropEvent>

#include "model/plug.h"

class Node;
class Connection;
class ComposerModel;
class ConnectionItem;
class GenericNodeItem;

class ComposerScene : public QGraphicsScene
{
    Q_OBJECT
    public:
        explicit ComposerScene(QObject *parent = NULL);

    protected:
        virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event);

        virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event);

        virtual void dropEvent(QGraphicsSceneDragDropEvent *event);

        virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

        virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    private slots:
        void onConnectionAdded(Connection *connection);

        void onConnectionRemoved(Connection *connection);

        void onPlugItemPositionChanged();

    private:
        typedef struct
        {
            ConnectionItem *item;
            bool fromOutput;
            Plug *plugInput;
            Plug *plugOutput;
            Node *baseNode;
        } EditedConnection;

        typedef struct
        {
            GenericNodeItem *item;
            QPointF initClickPos;
            QPointF initNodePose;
        } EditedNode;

    private:
        ComposerModel *_model;
        EditedConnection _editedConnection;
        EditedNode _editedNode;
        QList<ConnectionItem *> _connections;
        QList<GenericNodeItem *> _nodes;
};

#endif // COMPOSERSCENE_H