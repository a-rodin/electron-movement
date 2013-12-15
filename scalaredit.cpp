/*****************************************************************************
 * scalaredit.cpp                                                            *
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

#include "scalaredit.h"

#include <QHBoxLayout>
#include <QDoubleValidator>

ScalarEdit::ScalarEdit(QWidget *parent)
    : QWidget(parent)
{
    setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *hl = new QHBoxLayout(this);
    hl->setContentsMargins(0, 0, 0, 0);
    _name = new QLabel(this);
    hl->addWidget(_name);
    _val = new QLineEdit(this);
    _val->setMinimumWidth(70);
    _val->setMaximumWidth(70);
    _val->setValidator(new QDoubleValidator(_val));
    hl->addWidget(_val);
    _units = new QLabel(this);
    hl->addWidget(_units);
    setLayout(hl);   
}

double ScalarEdit::value() const
{
    return _val->text().toDouble();
}

void ScalarEdit::setName(const QString &name)
{
    _sName = name;
    _name->setText(name + " =");
}

void ScalarEdit::setUnits(const QString &units)
{
    _sUnits = units;
    _units->setText(units);
}

void ScalarEdit::setValue(double v)
{
    _val->setText(QString().sprintf("%.3lg", v));
}

void ScalarEdit::setReadOnly(bool ro)
{
    _val->setReadOnly(ro);
}

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent

