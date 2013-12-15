/*****************************************************************************
 * pointeedit.h                                                              *
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

#ifndef POINTEEDIT_H
#define POINTEEDIT_H

#include "fieldedit.h"
#include "laplasfield.h"
#include "scalaredit.h"
#include "vectoredit.h"

class PointEEdit: public FieldEdit
{
    Q_OBJECT
    public:
        PointEEdit(QWidget *parent = 0);
        ~PointEEdit();

        VectorField *field() const { return _E; }
        void readParams();
        void setReadOnly(bool ro);

        void loadSettings(QSettings &s);
        void saveSettings(QSettings &s);
    private:
        LaplasField *_E;
        VectorEdit *r0_edit;
        ScalarEdit *q_edit;
};

#endif // POINTEEDIT_H

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent
