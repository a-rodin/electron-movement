/*****************************************************************************
 * tensioredit.cpp                                                           *
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

#include "tensioredit.h"
#include <QGridLayout>
#include <QDoubleValidator>

TensiorEdit::TensiorEdit(QWidget *parent)
    : QWidget(parent)
{
    setContentsMargins(0, 0, 0, 0);
    QGridLayout *l = new QGridLayout(this);
    _name = new QLabel(this);
    l->addWidget(_name, 1, 0);
    _units = new QLabel(this);
    l->addWidget(_units, 1, 4);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            _edits[i][j] = new QLineEdit(this);
            _edits[i][j]->setMinimumWidth(70);
            _edits[i][j]->setMaximumWidth(70);
            _edits[i][j]->setValidator(new QDoubleValidator(_edits[i][j]));
            l->addWidget(_edits[i][j], i, j + 1);
        }
}

Tensior TensiorEdit::value() const
{
    Tensior _t;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            _t.at(i, j) = _edits[i][j]->text().toDouble();
    return _t;
}

void TensiorEdit::setName(const QString &name)
{
    _tName = name;
    _name->setText(name + QString::fromUtf8("̂") + " = [");
}

void TensiorEdit::setUnits(const QString &units)
{
    _tUnits = units;
    _units->setText("] " + units);
}

void TensiorEdit::setValue(const Tensior &t)
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            _edits[i][j]->setText(QString().sprintf("%.2lg", t.constAt(i, j)));
}

void TensiorEdit::setReadOnly(bool ro)
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            _edits[i][j]->setReadOnly(ro);
}

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent

