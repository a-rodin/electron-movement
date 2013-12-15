/*****************************************************************************
 * fieldedits.cpp                                                            *
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

#include "fieldedits.h"
#include "consteedit.h"
#include "consthedit.h"
#include "osceedit.h"
#include "oschedit.h"
#include "pointeedit.h"
#include "linhedit.h"
#include <QHash>

const QString & FieldEdits::fieldEditName(int classId)
{
    static QString names[] = {
        QString::fromUtf8("Постоянное ЭП"),
        QString::fromUtf8("Постоянное МП"),
        QString::fromUtf8("Гармоническое ЭП"),
        QString::fromUtf8("Гармоническое МП"),
        QString::fromUtf8("ЭП точечного заряда"),
        QString::fromUtf8("Линейное МП"),
        QString::fromUtf8("Неизвестное поле")
    };
    if (classId >= 0 && classId < fieldEditsCount())
        return names[classId];
    else
        return names[fieldEditsCount()];
}

FieldEdit * FieldEdits::newFieldEdit(int classId)
{
    switch (classId) {
        case 0: return new ConstEEdit;
        case 1: return new ConstHEdit;
        case 2: return new OscEEdit;
        case 3: return new OscHEdit;
        case 4: return new PointEEdit;
        case 5: return new LinHEdit;
        default: return 0;
    }
}

int FieldEdits::fieldEditsCount()
{
    return 6;
}

int FieldEdits::fieldEditClassId(const QString &className)
{
    static QHash<QString, int> id;
    if (id.isEmpty()) {
        id["ConstEEdit"] = 0;
        id["ConstHEdit"] = 1;
        id["OscEEdit"] = 2;
        id["OscHEdit"] = 3;
        id["PointEEdit"] = 4;
        id["LinHEdit"] = 5;
    }
    if (id.contains(className))
        return id[className];
    else
        return -1;
}

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent

