/*****************************************************************************
 * Vector.cpp                                                                *
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

#include "vector.h"
#include <cmath>

Vector::Vector(double _x, double _y, double _z)
{
    x = _x; y = _y; z = _z;
}

Vector::Vector(const Vector &a)
{
    x = a.x; y = a.y; z = a.z;
}

double Vector::len() const
{
    return sqrt(x*x + y*y + z*z);
}

double Vector::sq() const
{
    return x*x + y*y + z*z;
}

bool Vector::isNull() const
{
    return x == 0.0 && y == 0.0 && z == 0.0;
}

const Vector Vector::norm() const
{
    double l = len();
    if (l == 0.0)
        return null();
    else
        return (1.0/l) * (*this);
}

const Vector & Vector::operator = (const Vector &a)
{
    x = a.x; y = a.y; z = a.z;
    return *this;
}

const Vector & Vector::operator += (const Vector &a)
{
    x += a.x; y += a.y; z += a.z;
    return *this;
}

const Vector & Vector::operator -= (const Vector &a)
{
    x -= a.x; y -= a.y; z -= a.z;
    return *this;
}

const Vector & Vector::operator *= (double c)
{
    x *= c; y *= c; z *= c;
    return *this;
}

bool operator == (const Vector &a, const Vector &b)
{
    return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
}

const Vector operator + (const Vector &a, const Vector &b)
{
    return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
}

const Vector operator - (const Vector &a, const Vector &b)
{
    return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
}

const Vector operator * (double c, const Vector &a)
{
    return Vector (c * a.x, c * a.y, c * a.z);
}

double operator * (const Vector &a, const Vector &b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

const Vector Vector::vectMult (const Vector &a, const Vector &b)
{
    return Vector(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z,
            a.x*b.y - a.y*b.x);
}

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent

