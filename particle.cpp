/*****************************************************************************
 * Particle.cpp                                                              *
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

#include "particle.h"
#include <cmath>

#define c 2.99792458e10

Particle::Particle(double m, double q, Vector r, Vector v,
        double t, double t0, double dt, unsigned n_dt)
{
    _m = m; _q = q; _r = r; set_v(v);
    _t = t; _t0 = t0; _n_dt = n_dt; _dt = dt;
}

Vector Particle::v() const
{
    return (c*c / E_k()) * _p;
}

double Particle::E_k() const
{
    return c * sqrt(_p.sq() + _m*_m*c*c);
}

void Particle::set_v(Vector v)
{
    _p = (_m/sqrt(1.0 - (v/c).sq())) * v;
}

Vector Particle::F() const
{
    return _q * (E_current() + (1.0/c) * Vector::vectMult(v(), H_current()));
}

void Particle::move()
{
    for (unsigned i = 0; i < _n_dt; ++i) {
        Vector _v = v();
        _r += _dt * _v;
        _t0 += sqrt(1.0 - (_v/c).sq()) * _dt;
        _p += F() * _dt;
    }
    _t += _n_dt * _dt;
}

void Particle::add_E(VectorField *E)
{
    if (E != 0)
        _E.insert(E);
}

void Particle::add_H(VectorField *H)
{
    if (H != 0)
        _H.insert(H);
}

void Particle::remove_H(VectorField *H)
{
    _H.remove(H);
}

void Particle::remove_E(VectorField *E)
{
    _E.remove(E);
}

Vector Particle::E_current() const
{
    Vector res;
    for (QSet<VectorField*>::const_iterator i = _E.begin(); i != _E.end(); ++i)
        res += (*i)->value(_r, _t);
    return res;
}

Vector Particle::H_current() const
{
    Vector res;
    for (QSet<VectorField*>::const_iterator i = _H.begin(); i != _H.end(); ++i)
        res += (*i)->value(_r, _t);
    return res;
   
}

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent

