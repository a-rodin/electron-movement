/*****************************************************************************
 * linfield.h                                                                *
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

#ifndef LINFIELD_H
#define LINFIELD_H

#include "vectorfield.h"
#include "tensior.h"

class LinField: public VectorField
{
    public:
        LinField(double A0 = 0.0, const Vector &r0 = Vector::null(),
                const Tensior &k = Tensior());
        void set_A0(double A0) { _A0 = A0; }
        void set_r0(const Vector &r0) { _r0 = r0; }
        void set_k(const Tensior &k) { _k = k; }
        double A0() { return _A0; }
        const Vector & r0() { return _r0; }
        const Tensior & k() { return _k; }

        Vector value(const Vector &r, double t);

    private:
        Vector _r0;
        double _A0;
        Tensior _k;
};

#endif // LINFIELD_H

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent
