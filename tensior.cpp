/*****************************************************************************
 * tensior.cpp                                                               *
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

#include "tensior.h"

Tensior::Tensior()
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            _a[i][j] = 0.0;
}


Vector operator * (const Tensior &t, const Vector &v)
{
    return Vector(t._a[0][0]*v.x + t._a[0][1]*v.y + t._a[0][2]*v.z,
            t._a[1][0]*v.x + t._a[1][1]*v.y + t._a[1][2]*v.z,
            t._a[2][0]*v.x + t._a[2][1]*v.y + t._a[2][2]*v.z);
}

Tensior operator * (double a, const Tensior &t)
{
    Tensior _t;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            _t._a[i][j] = t._a[i][j] * a;
    return _t;
}

Tensior operator + (const Tensior &a, const Tensior &b)
{
    Tensior _t;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            _t._a[i][j] = a._a[i][j] + b._a[i][j];
    return _t;
}

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent

