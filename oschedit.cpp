/*****************************************************************************
 * oschedit.cpp                                                              *
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

#include "oschedit.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

OscHEdit::OscHEdit(QWidget *parent)
    : FieldEdit(FieldEdit::Magnetic, parent)
{
    setFieldName(QString::fromUtf8("Переменное МП: <b>H</b> = <b>H"
                "<sub><font style=\"font-weght: normal;\">0</font></sub></b>sin"
                "(ωt + <b>kr</b> + φ)"));
    _H = new OscField(Vector(1e-13, 0.0, 0.0), 2.0*3.1415926536*10.0, 0.0);
    a0_edit = new VectorEdit(this);
    a0_edit->setName(QString::fromUtf8("<b>H<sub><font style=\"font-weght: normal;\">0</font></sub></b>"));
    a0_edit->setUnits(QString::fromUtf8("Гс"));
    a0_edit->setValue(_H->A0());
    k_edit = new VectorEdit(this);
    k_edit->setName("k");
    k_edit->setUnits(QString::fromUtf8("см<sup>-1</sup>"));
    k_edit->setValue(_H->k());
    w_edit = new ScalarEdit(this);
    w_edit->setName(QString::fromUtf8("ω"));
    w_edit->setUnits(QString::fromUtf8("с<sup>-1</sup>"));
    w_edit->setValue(_H->w());
    phi_edit = new ScalarEdit(this);
    phi_edit->setName(QString::fromUtf8("φ"));
    phi_edit->setValue(_H->phi());
    QVBoxLayout *v = new QVBoxLayout(centralWidget());
    v->addWidget(a0_edit);
    v->addWidget(k_edit);
    QHBoxLayout *h = new QHBoxLayout();
    v->addLayout(h);
    h->addWidget(w_edit);
    h->addWidget(phi_edit);
}

OscHEdit::~OscHEdit()
{
    delete _H;
}

void OscHEdit::readParams()
{
    _H->set_A0(a0_edit->value());
    _H->set_w(w_edit->value());
    _H->set_phi(phi_edit->value());
    _H->set_k(k_edit->value());
}

void OscHEdit::setReadOnly(bool ro)
{
    a0_edit->setReadOnly(ro);
    w_edit->setReadOnly(ro);
    phi_edit->setReadOnly(ro);
    k_edit->setReadOnly(ro);
    FieldEdit::setReadOnly(ro);
}

void OscHEdit::loadSettings(QSettings &s)
{
    _H->set_A0(Vector(s.value("A0x").toDouble(), s.value("A0y").toDouble(), s.value("A0z").toDouble()));
    _H->set_w(s.value("w").toDouble());
    _H->set_phi(s.value("phi").toDouble());
    _H->set_k(Vector(s.value("kx").toDouble(), s.value("ky").toDouble(), s.value("kz").toDouble()));
    a0_edit->setValue(_H->A0());
    w_edit->setValue(_H->w());
    phi_edit->setValue(_H->phi());
    k_edit->setValue(_H->k());
}

void OscHEdit::saveSettings(QSettings &s)
{
    s.setValue("A0x", _H->A0().x);
    s.setValue("A0y", _H->A0().y);
    s.setValue("A0z", _H->A0().z);
    s.setValue("kx", _H->k().x);
    s.setValue("ky", _H->k().y);
    s.setValue("kz", _H->k().z);
    s.setValue("w", _H->w());
    s.setValue("phi", _H->phi());
}


// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent

