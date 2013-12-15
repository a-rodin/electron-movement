/*****************************************************************************
 * vectoredit.cpp                                                            *
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

#include "vectoredit.h"
#include <QHBoxLayout>
#include <QDoubleValidator>

VectorEdit::VectorEdit(QWidget *parent)
    : QWidget(parent)
{
    setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *hl = new QHBoxLayout(this);
    hl->setContentsMargins(0, 0, 0, 0);
    _name = new QLabel(this);
    hl->addWidget(_name);
    _x = new QLineEdit(this);
    _x->setMinimumWidth(70);
    _x->setMaximumWidth(70);
    _x->setValidator(new QDoubleValidator(_x));
    hl->addWidget(_x);
    QLabel *l1 = new QLabel(",");//QLabel("<b>e<sub><font style=\"font-weight:normal;\">x</font><sub></b> +", this);
    hl->addWidget(l1);
    _y = new QLineEdit(this);
    _y->setMinimumWidth(70);
    _y->setMaximumWidth(70);
    _y->setValidator(new QDoubleValidator(_y));
    hl->addWidget(_y);
    QLabel *l2 = new QLabel(",");//QLabel("<b>e<sub><font style=\"font-weight:normal;\">y</font></sub></b> +", this);
    hl->addWidget(l2);
    _z = new QLineEdit(this);
    _z->setMinimumWidth(70);
    _z->setMaximumWidth(70);
    _z->setValidator(new QDoubleValidator(_z));
    hl->addWidget(_z);
    _units = new QLabel(this);
    hl->addWidget(_units);
    setLayout(hl);
}

Vector VectorEdit::value() const
{
    return Vector(_x->text().toDouble(), _y->text().toDouble(), _z->text().toDouble());
}

void VectorEdit::setName(const QString &name)
{
    _vectorName = name;
    _name->setText("<b>" + name + "</b> = {");
}

void VectorEdit::setUnits(const QString &units)
{
    _vectorUnits = units;
    _units->setText("} " + units);//("<b>e<sub><font style=\"font-weight: normal;\">z</font></sub></b> " + units);
}

void VectorEdit::setValue(const Vector &v)
{
    _x->setText(QString().sprintf("%.2lg", v.x));
    _y->setText(QString().sprintf("%.2lg", v.y));
    _z->setText(QString().sprintf("%.2lg", v.z));
}

void VectorEdit::setReadOnly(bool ro)
{
    _x->setReadOnly(ro);
    _y->setReadOnly(ro);
    _z->setReadOnly(ro);
}

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent

