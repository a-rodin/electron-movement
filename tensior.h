/*****************************************************************************
 * tensior.h                                                                 *
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

#ifndef TENSIOR_H
#define TENSIOR_H

#include "vector.h"

class Tensior
{
    public:
        Tensior();
        double & at(int i, int j)
        { return _a[i][j]; }
        double constAt(int i, int j) const
        { return _a[i][j]; }

        friend Vector operator * (const Tensior &t, const Vector &v);
        friend Tensior operator * (double a, const Tensior &t);
        friend Tensior operator * (const Tensior &t, double a);
        friend Tensior operator - (const Tensior &a);
        friend Tensior operator + (const Tensior &a, const Tensior &b);
        friend Tensior operator - (const Tensior &a, const Tensior &b);

    private:
        double _a[3][3];
};

Vector operator * (const Tensior &t, const Vector &v);
Tensior operator * (double a, const Tensior &t);
inline Tensior operator * (const Tensior &t, double a)
{ return a * t; }
inline Tensior operator - (const Tensior &a)
{ return (-1.0) * a; }
Tensior operator + (const Tensior &a, const Tensior &b);
inline Tensior operator - (const Tensior &a, const Tensior &b)
{ return a + (- b); }

#endif // TENSIOR_H

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent
