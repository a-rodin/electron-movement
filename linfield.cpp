/*****************************************************************************
 * linfield.cpp                                                              *
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

#include "linfield.h"

LinField::LinField(double A0, const Vector &r0, const Tensior &k)
{
    _A0 = A0;
    _r0 = r0;
    _k = k;
}

Vector LinField::value(const Vector &r, double)
{
    return _A0 * (_k * (r - _r0));
}

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent

