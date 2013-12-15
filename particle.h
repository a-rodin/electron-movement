/*****************************************************************************
 * Particle.h                                                                *
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

#ifndef PARTICLE_H
#define PARTICLE_H

#include "vector.h"
#include "vectorfield.h"
#include <QSet>

class Particle {
    public:
        Particle(double m = 0.0, double q = 0.0,
                Vector r = Vector::null(), Vector v = Vector::null(),
                double t = 0.0, double t0 = 0.0, double dt = 0.0, unsigned ndt = 1);

        double m() const { return _m; }
        double q() const { return _q; }
        Vector r() const { return _r; }
        Vector v() const;
        Vector p() const { return _p; }
        double t() const { return _t; }
        double t0() const { return _t0; }
        double dt() const { return _dt; }
        unsigned ndt() const { return _n_dt; }
        double E_k() const;
        const QSet<VectorField*> & E() const { return _E; } // ?
        const QSet<VectorField*> & H() const { return _H; } // ?
        Vector E_current() const;
        Vector H_current() const;
        Vector F() const;

        void set_m(double m) { _m = m; }
        void set_q(double q) { _q = q; }
        void set_r(Vector r) { _r = r; }
        void set_v(Vector v);
        void set_p(Vector p) { _p = p; }
        void set_t(double t) { _t = t; }
        void set_t0(double t0) { _t0 = t0; }
        void set_dt(double dt) { _dt = dt; }
        void set_ndt(double n_dt) { _n_dt = n_dt; }
        void add_E(VectorField *E);
        void add_H(VectorField *H);
        void remove_E(VectorField *E);
        void remove_H(VectorField *H);

        void move();

    private:
        double _m, _q, _t, _t0, _dt;
        unsigned _n_dt;
        Vector _r, _p;
        QSet<VectorField*> _E, _H;
};

#endif // PARTICLE_H

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent
