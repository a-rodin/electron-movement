/*****************************************************************************
 * linhedit.cpp                                                              *
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

#include "linhedit.h"
#include <QVBoxLayout>

LinHEdit::LinHEdit(QWidget *parent)
    : FieldEdit(FieldEdit::Magnetic, parent)
{
    setFieldName(QString::fromUtf8("Линейное МП: <b>H</b> = H<sub>0</sub> "
        "k̂(<b>r</b> - <b>r<sub><font-style=\"font-weight:"
        "normal;\">0</font></sub></b>)"));
    _H = new LinField();
    QVBoxLayout *l = new QVBoxLayout(centralWidget());
    a0_edit = new ScalarEdit(this);
    a0_edit->setName("H<sub><font style=\"font-weight:normal;\">0</font></sub>");
    a0_edit->setUnits(QString::fromUtf8("Гс"));
    a0_edit->setValue(_H->A0());
    l->addWidget(a0_edit);
    r0_edit = new VectorEdit(this);
    r0_edit->setName("r<sub><font style=\"font-weight:normal;\">0</font></sub>");
    r0_edit->setUnits(QString::fromUtf8("см"));
    r0_edit->setValue(_H->r0());
    l->addWidget(r0_edit);
    k_edit = new TensiorEdit(this);
    k_edit->setName("k");
    k_edit->setUnits(QString::fromUtf8("см<sup>-1</sup>"));
    k_edit->setValue(_H->k());
    l->addWidget(k_edit);
}

LinHEdit::~LinHEdit()
{
    delete _H;
}

void LinHEdit::readParams()
{
    _H->set_A0(a0_edit->value());
    _H->set_r0(r0_edit->value());
    _H->set_k(k_edit->value());
}

void LinHEdit::setReadOnly(bool ro)
{
    a0_edit->setReadOnly(ro);
    r0_edit->setReadOnly(ro);
    k_edit->setReadOnly(ro);
    FieldEdit::setReadOnly(ro);
}

void LinHEdit::loadSettings(QSettings &s)
{
    _H->set_A0(s.value("A0").toDouble());
    _H->set_r0(Vector(s.value("r0x").toDouble(), s.value("r0y").toDouble(), s.value("r0z").toDouble()));
    Tensior t;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            t.at(i, j) = s.value(QString().sprintf("k%d%d", i, j)).toDouble();
    _H->set_k(t);
    a0_edit->setValue(_H->A0());
    r0_edit->setValue(_H->r0());
    k_edit->setValue(_H->k());
}

void LinHEdit::saveSettings(QSettings &s)
{
    s.setValue("A0", _H->A0());
    s.setValue("r0x", _H->r0().x);
    s.setValue("r0y", _H->r0().y);
    s.setValue("r0z", _H->r0().z);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            s.setValue(QString().sprintf("k%d%d", i, j), _H->k().constAt(i, j));
}

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent

