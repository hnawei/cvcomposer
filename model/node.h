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

#pragma once

#include <QObject>

#include "global/properties.h"
#include "model/plugdefinition.h"

#include <opencv2/core/core.hpp>

class Plug;

class Node : public QObject
{
    Q_OBJECT

    public:
        explicit Node(const QString &name,
                             const QString &userReadableName,
                             QObject *parent = NULL);

        const QString &getName() const;

        const QString &getUserReadableName() const;

        const QList<Plug *> &getInputs() const;

        bool hasInput(Plug *input) const;

        const QList<Plug *> &getOutputs() const;

        bool hasOutput(Plug *output) const;

        void signalProcessDone(const Properties &outputs, const Properties &inputs);

        void signalProcessUnavailable();

        const Properties &getProperties() const;

    public slots:
        void setProperty(const QString &name, const QVariant &value);

    signals:
        void propertyChanged(const QString &name, const QVariant &value);

        void processDone(const Properties &outputs, const Properties &inputs);

        void processUnavailable();

    private:
        const QString _name;
        const QString _userReadableName;
        QList<Plug *> _inputs;
        QList<Plug *> _outputs;
        Properties _properties;
};