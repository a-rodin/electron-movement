/*****************************************************************************
 * Vector.h                                                                  *
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

#ifndef VECTOR_H
#define VECTOR_H

class Vector {
    public:
        Vector(double _x = 0.0, double _y = 0.0, double _z = 0.0);
        Vector(const Vector &a);

        double x, y, z;
 
        double len() const;
        double sq() const;
        const Vector norm() const;
        bool isNull() const;

        static const Vector null() { return Vector(); }
        static const Vector i() { return Vector(1., 0., 0.); }
        static const Vector j() { return Vector(0., 1., 0.); }
        static const Vector k() { return Vector(0., 0., 1.); }

        const Vector & operator = (const Vector &a);
        const Vector & operator += (const Vector &a);
        const Vector & operator -= (const Vector &a);
        const Vector & operator *= (double c);
        friend bool operator == (const Vector &a, const Vector &b);
        friend const Vector operator + (const Vector &a, const Vector &b);
        friend const Vector operator - (const Vector &a, const Vector &b);
        friend const Vector operator * (double c, const Vector &a);
        friend const Vector operator * (const Vector &a, double c);
        friend double operator * (const Vector &a, const Vector &b);
        friend const Vector operator / (const Vector &a, double c);
        static const Vector vectMult (const Vector &a, const Vector &b);
        friend const Vector operator - (const Vector &a);
};

bool operator == (const Vector &a, const Vector &b);
const Vector operator + (const Vector &a, const Vector &b);
const Vector operator - (const Vector &a, const Vector &b);
const Vector operator * (double c, const Vector &a);
inline const Vector operator * (const Vector &a, double c)
{ return c * a; }
double operator * (const Vector &a, const Vector &b);
inline const Vector operator / (const Vector &a, double c)
{ return (1.0 / c) * a; }
inline const Vector operator - (const Vector &a)
{ return -1.0 * a; }

#endif // VECTOR_H

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent
