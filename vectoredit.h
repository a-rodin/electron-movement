/*****************************************************************************
 * vectoredit.h                                                              *
 * Copyright (C) 2010 Alexander Rodin                                        *
 *                                                                           *
 * This program is free software: you can redistribute it and/or modify      *
 * it under the terms of the GNU General Public License as published by      *
 * the Free Software Foundation, either version 3 of the License, or         *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU General Public License for more details.                              *
 *                                                                           *
 * You should have received a copy of the GNU General Public License         *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.     *
 *****************************************************************************/

#ifndef VECTOREDIT_H
#define VECTOREDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include "vector.h"

class VectorEdit: public QWidget {
    Q_OBJECT

    public:
        VectorEdit(QWidget *parent = 0);

        Vector value() const;
        QString name() const { return _vectorName; } 
        QString units() const { return _vectorUnits; }

        void setName(const QString &name);
        void setUnits(const QString &units);
        void setNameAndUnits(const QString &name, const QString &units)
        { setName(name); setUnits(units); }

    public slots:
        void setValue(const Vector &v);
        void setReadOnly(bool ro);

    private:
        QString _vectorName, _vectorUnits;
        QLabel *_name, *_units;
        QLineEdit *_x, *_y, *_z;
};

#endif // VECTOREDIT_H

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent
