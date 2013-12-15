/*****************************************************************************
 * fieldedit.h                                                               *
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

#ifndef FIELDEDIT_H
#define FIELDEDIT_H

#include <QWidget>
#include <QSettings>
#include "ui_fieldedit.h"
#include "vectorfield.h"

class FieldEdit: public QWidget, private Ui::FieldEdit
{
    Q_OBJECT

    public:
        enum Type
        {
            Electric,
            Magnetic,
        };
        FieldEdit(Type t, QWidget *parent = 0);
        virtual ~FieldEdit() {}

        virtual VectorField *field() const = 0;
        virtual void readParams() = 0;
        bool paused() const;
        bool minimized() const;
        QString fieldName() const;
        Type type() const { return _t; }
        virtual void setReadOnly(bool);
        virtual void loadSettings(QSettings &s) = 0;
        virtual void saveSettings(QSettings &s) = 0;
    public slots:
        void setPaused(bool paused);
        void setMinimized(bool minimized);
    protected:
        QWidget *centralWidget();
        void setFieldName(const QString &name);
    private slots:
        void on_h_button_pause_toggled(bool t);
        void on_h_button_close_clicked();
    signals:
        void paused(bool p);
        void closed();
    private:
        Type _t;
};

#endif // FIELDEDIT_H

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent
