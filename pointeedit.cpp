/*****************************************************************************
 * pointeedit.cpp                                                            *
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

#include "pointeedit.h"
#include <QVBoxLayout>

PointEEdit::PointEEdit(QWidget *parent)
    : FieldEdit(FieldEdit::Electric, parent)
{
    setFieldName(QString::fromUtf8("ЭП точечного заряда"));
    _E = new LaplasField(4.8e-10, Vector(0.0, 0.0, 0.0));
    QVBoxLayout *v = new QVBoxLayout(centralWidget());
    q_edit = new ScalarEdit(this);
    q_edit->setName("q");
    q_edit->setUnits(QString::fromUtf8("ед. СГС"));
    q_edit->setValue(_E->c());
    v->addWidget(q_edit);
    r0_edit = new VectorEdit(this);
    r0_edit->setName("<b>r<sub><font style=\"font-weight:normal;\">0</font></sub></b>");
    r0_edit->setUnits(QString::fromUtf8("см"));
    r0_edit->setValue(_E->r0());
    v->addWidget(r0_edit);
}

PointEEdit::~PointEEdit()
{
    delete _E;
}

void PointEEdit::readParams()
{
    _E->set_c(q_edit->value());
    _E->set_r0(r0_edit->value());
}

void PointEEdit::setReadOnly(bool ro)
{
    q_edit->setReadOnly(ro);
    r0_edit->setReadOnly(ro);
    FieldEdit::setReadOnly(ro);
}

void PointEEdit::loadSettings(QSettings &s)
{
    _E->set_r0(Vector(s.value("r0x").toDouble(), s.value("r0y").toDouble(), s.value("r0z").toDouble()));
    _E->set_c(s.value("c").toDouble());
    r0_edit->setValue(_E->r0());
    q_edit->setValue(_E->c());
}

void PointEEdit::saveSettings(QSettings &s)
{
    s.setValue("r0x", _E->r0().x);
    s.setValue("r0y", _E->r0().y);
    s.setValue("r0z", _E->r0().z);
    s.setValue("c", _E->c());
}



// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent

