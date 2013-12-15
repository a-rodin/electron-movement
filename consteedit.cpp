/*****************************************************************************
 * consteedit.cpp                                                            *
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

#include "consteedit.h"
#include <QHBoxLayout>

ConstEEdit::ConstEEdit(QWidget *parent)
    : FieldEdit(FieldEdit::Electric, parent)
{
    setFieldName(QString::fromUtf8("Постоянное ЭП"));
    _E = new ConstField(Vector(0.0, 0.0, 3e-21));
    QHBoxLayout *l = new QHBoxLayout(centralWidget());
    a_edit = new VectorEdit(this);
    a_edit->setName("E");
    a_edit->setUnits(QString::fromUtf8("ед. СГС"));
    a_edit->setValue(_E->A());
    l->addWidget(a_edit);
}

ConstEEdit::~ConstEEdit()
{
   delete _E; 
}

void ConstEEdit::readParams()
{
    _E->set_A(a_edit->value());
}

void ConstEEdit::setReadOnly(bool ro)
{
    a_edit->setReadOnly(ro);
    FieldEdit::setReadOnly(ro);
}

void ConstEEdit::loadSettings(QSettings &s)
{
    _E->set_A(Vector(s.value("Ax").toDouble(), s.value("Ay").toDouble(), s.value("Az").toDouble()));
    a_edit->setValue(_E->A());
}

void ConstEEdit::saveSettings(QSettings &s)
{
    s.setValue("Ax", _E->A().x);
    s.setValue("Ay", _E->A().y);
    s.setValue("Az", _E->A().z);
}

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent

