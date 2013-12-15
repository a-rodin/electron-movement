/*****************************************************************************
 * oscfield.h                                                                *
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

#ifndef OSCFIELD_H
#define OSCFIELD_H

#include "vectorfield.h"

class OscField: public VectorField
{
    public:
        OscField(const Vector &A0 = Vector::null(),
                double w = 0.0, double phi = 0.0, const Vector &k = Vector::null());

        void set_A0(const Vector &A0)
        { _A0 = A0; }
        void set_w(double w)
        { _w = w; }
        void set_phi(double phi)
        { _phi = phi; }
        void set_k(const Vector &k) { _k = k; }

        Vector A0() const { return _A0; }
        double w() const { return _w; }
        double phi() const { return _phi; }
        Vector k() const { return _k; }

        virtual Vector value(const Vector &r, double t) ;

    private:
        Vector _A0, _k;
        double _w, _phi;
};

#endif // OSCFIELD_H

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent
