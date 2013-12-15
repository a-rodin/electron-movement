/*****************************************************************************
 * osceedit.cpp                                                              *
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

#include "osceedit.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

OscEEdit::OscEEdit(QWidget *parent)
    : FieldEdit(FieldEdit::Electric, parent)
{
    setFieldName(QString::fromUtf8("Переменное ЭП: <b>E</b> = <b>E"
                "<sub><font style=\"font-weght: normal;\">0</font></sub></b>sin"
                "(ωt + <b>kr</b>+ φ)"));
    _E = new OscField(Vector(0.0, 1e-16, 0.0), 2.0*3.1415926536*10.0, 0.0, Vector::null());
    a0_edit = new VectorEdit(this);
    a0_edit->setName(QString::fromUtf8("<b>E<sub><font style=\"font-weght: normal;\">0</font></sub></b>"));
    a0_edit->setUnits(QString::fromUtf8("ед. СГС"));
    a0_edit->setValue(_E->A0());
    k_edit = new VectorEdit(this);
    k_edit->setName("k");
    k_edit->setUnits(QString::fromUtf8("см<sup>-1</sup>"));
    k_edit->setValue(_E->k());
    w_edit = new ScalarEdit(this);
    w_edit->setName(QString::fromUtf8("ω"));
    w_edit->setUnits(QString::fromUtf8("с<sup>-1</sup>"));
    w_edit->setValue(_E->w());
    phi_edit = new ScalarEdit(this);
    phi_edit->setName(QString::fromUtf8("φ"));
    phi_edit->setValue(_E->phi());
    QVBoxLayout *v = new QVBoxLayout(centralWidget());
    v->addWidget(a0_edit);
    v->addWidget(k_edit);
    QHBoxLayout *h = new QHBoxLayout();
    v->addLayout(h);
    h->addWidget(w_edit);
    h->addWidget(phi_edit);
}

OscEEdit::~OscEEdit()
{
    delete _E;
}

void OscEEdit::readParams()
{
    _E->set_A0(a0_edit->value());
    _E->set_w(w_edit->value());
    _E->set_phi(phi_edit->value());
    _E->set_k(k_edit->value());
}

void OscEEdit::setReadOnly(bool ro)
{
    a0_edit->setReadOnly(ro);
    w_edit->setReadOnly(ro);
    phi_edit->setReadOnly(ro);
    k_edit->setReadOnly(ro);
    FieldEdit::setReadOnly(ro);
}

void OscEEdit::loadSettings(QSettings &s)
{    
    _E->set_A0(Vector(s.value("A0x").toDouble(), s.value("A0y").toDouble(), s.value("A0z").toDouble()));
    _E->set_w(s.value("w").toDouble());
    _E->set_phi(s.value("phi").toDouble());
    _E->set_k(Vector(s.value("kx").toDouble(), s.value("ky").toDouble(), s.value("kz").toDouble()));
    a0_edit->setValue(_E->A0());
    w_edit->setValue(_E->w());
    phi_edit->setValue(_E->phi());
    k_edit->setValue(_E->k());
}

void OscEEdit::saveSettings(QSettings &s)
{    
    s.setValue("A0x", _E->A0().x);
    s.setValue("A0y", _E->A0().y);
    s.setValue("A0z", _E->A0().z);
    s.setValue("kx", _E->k().x);
    s.setValue("ky", _E->k().y);
    s.setValue("kz", _E->k().z);
    s.setValue("w", _E->w());
    s.setValue("phi", _E->phi());
}   



// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent

