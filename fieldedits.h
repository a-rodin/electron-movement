/*****************************************************************************
 * fieldedits.h                                                              *
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

#ifndef FIELDEDITS_H
#define FIELDEDITS_H

#include "fieldedit.h"

class FieldEdits 
{
    public:
        static const QString & fieldEditName(int classId);
        static FieldEdit * newFieldEdit(int classId);
        static int fieldEditsCount();
        static int fieldEditClassId(const QString &name);
};

#endif // FIELDEDITS_H

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent
