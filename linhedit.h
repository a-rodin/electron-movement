/*****************************************************************************
 * linhedit.h                                                                *
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

#ifndef LINHEDIT_H
#define LINHEDIT_H

#include "fieldedit.h"
#include "vectoredit.h"
#include "linfield.h"
#include "scalaredit.h"
#include "tensioredit.h"

class LinHEdit: public FieldEdit
{
    Q_OBJECT
    public:
        LinHEdit(QWidget *parent = 0);
        ~LinHEdit();

        VectorField *field() const { return _H; }
        void readParams();
        void setReadOnly(bool ro);

        void loadSettings(QSettings &s);
        void saveSettings(QSettings &s);
    private:
        LinField *_H;
        VectorEdit *r0_edit;
        ScalarEdit *a0_edit;
        TensiorEdit *k_edit;
};

#endif // LINHEDIT_H

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent
