/*****************************************************************************
 * fieldedit.cpp                                                             *
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

#include "fieldedit.h"

FieldEdit::FieldEdit(FieldEdit::Type t, QWidget *parent)
    : QWidget(parent)
{
    _t = t;
    setupUi(this);
}

void FieldEdit::setReadOnly(bool ro)
{
    h_button_close->setDisabled(ro);
    h_button_pause->setDisabled(ro);
}

bool FieldEdit::paused() const
{
    return h_button_pause->isChecked();
}

bool FieldEdit::minimized() const
{
    return h_button_minimize->isChecked();
}

void FieldEdit::on_h_button_pause_toggled(bool t)
{
    emit paused(t);
}

void FieldEdit::on_h_button_close_clicked()
{
    emit closed();
}

void FieldEdit::setMinimized(bool minimized)
{
    h_button_minimize->setChecked(minimized);
}

void FieldEdit::setPaused(bool paused)
{
    h_button_pause->setChecked(paused);
}

QWidget  * FieldEdit::centralWidget()
{
    return content_frame;
}

void FieldEdit::setFieldName(const QString &name)
{
    h_label->setText(name);
}

QString FieldEdit::fieldName() const
{
    return h_label->text();
}

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent

