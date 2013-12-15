/*****************************************************************************
 * oscfield.cpp                                                              *
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

#include "oscfield.h"
#include <cmath>

OscField::OscField(const Vector &A0, double w, double phi, const Vector &k)
    : VectorField()
{
    _A0 = A0;
    _w = w;
    _phi = phi;
    _k = k;
}

Vector OscField::value(const Vector &r, double t)
{
    return _A0 * sin(_w * t + _k * r + _phi);
}

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent

