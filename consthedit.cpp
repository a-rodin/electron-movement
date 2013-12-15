/*****************************************************************************
 * consthedit.cpp                                                            *
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

#include "consthedit.h"
#include <QHBoxLayout>

ConstHEdit::ConstHEdit(QWidget *parent)
    : FieldEdit(FieldEdit::Magnetic, parent)
{
    setFieldName(QString::fromUtf8("Постоянное МП"));
    _H = new ConstField(Vector(0.0, 0.0, 5e-8));
    QHBoxLayout *l = new QHBoxLayout(centralWidget());
    a_edit = new VectorEdit(this);
    a_edit->setName("H");
    a_edit->setUnits(QString::fromUtf8("Гс"));
    a_edit->setValue(_H->A());
    l->addWidget(a_edit);
}

ConstHEdit::~ConstHEdit()
{
   delete _H; 
}

void ConstHEdit::readParams()
{
    _H->set_A(a_edit->value());
}

void ConstHEdit::setReadOnly(bool ro)
{
    a_edit->setReadOnly(ro);
    FieldEdit::setReadOnly(ro);
}

void ConstHEdit::loadSettings(QSettings &s)
{    
    _H->set_A(Vector(s.value("Ax").toDouble(), s.value("Ay").toDouble(), s.value("Az").toDouble()));
    a_edit->setValue(_H->A());
}

void ConstHEdit::saveSettings(QSettings &s)
{    
    s.setValue("Ax", _H->A().x);
    s.setValue("Ay", _H->A().y);
    s.setValue("Az", _H->A().z);
}   


// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent

