/*****************************************************************************
 * laplasfield.cpp                                                           *
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

#include "laplasfield.h"
#include <cmath>

LaplasField::LaplasField(double c, const Vector &r0)
{
    _c = c;
    _r0 = r0;
}

Vector LaplasField::value(const Vector &r, double)
{
    Vector r1 = r - _r0;
    return _c * r1 / pow(r1.len(), 3.0);
}

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent

