/*****************************************************************************
 * scalaredit.h                                                              *
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

#ifndef SCALAREDIT_H
#define SCALAREDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>

class ScalarEdit: public QWidget {
    Q_OBJECT

    public:
        ScalarEdit(QWidget *parent = 0);

        double value() const;
        QString name() const { return _sName; } 
        QString units() const { return _sUnits; }

        void setName(const QString &name);
        void setUnits(const QString &units);
        void setNameAndUnits(const QString &name, const QString &units)
        { setName(name); setUnits(units); }

    public slots:
        void setValue(double v);
        void setReadOnly(bool ro);

    private:
        double _s;
        QString _sName, _sUnits;
        QLabel *_name, *_units;
        QLineEdit *_val;
};

#endif // SCALAREDIT_H

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent
