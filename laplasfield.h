/*****************************************************************************
 * laplasfield.h                                                             *
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

#ifndef LAPLASFIELD_H
#define LAPLASFIELD_H

#include "vectorfield.h"

class LaplasField: public VectorField
{
    public:
        LaplasField(double c, const Vector &r0);

        void set_c(double c) { _c = c; }
        void set_r0(const Vector &r0) { _r0 = r0; }
        double c() { return _c; }
        Vector r0() { return _r0; }
        Vector value(const Vector &r, double t);
    private:
        double _c;
        Vector _r0;
};

#endif // LAPLASFIELD_H

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent
