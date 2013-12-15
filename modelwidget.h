/*****************************************************************************
 * modelwidget.h                                                             *
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

#ifndef MODELWIDGET_H
#define MODELWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QTimerEvent>
#include <QVector>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QResizeEvent>
#include "particle.h"

class ModelWidget: public QWidget {
    Q_OBJECT

    public:
        ModelWidget(QWidget *parent = 0, Particle *particle = 0);
        virtual ~ModelWidget();

        Particle *particle() { return _particle; }
        void setParticle(Particle *particle) { _particle = particle; }

        void setZoom(double zoom);
        double zoom() const { return k; }

        bool show_f() const { return _show_f; }
        bool show_v() const { return _show_v; }

    public slots:
        void start();
        void stop();
        void clearTrack();
        void set_show_f(bool s);
        void set_show_v(bool s);
        void update() { render(); }

    signals:
        void updated();
        void zoomUpdated();

    protected:
        void paintEvent(QPaintEvent *event);
        void timerEvent(QTimerEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void wheelEvent(QWheelEvent *event);
        void resizeEvent(QResizeEvent *event);

    private:
        QPointF toScreen(const Vector &a, const QPointF &r0);
        QPointF toScreen(const Vector &a)
        { return toScreen(a, QPointF(width() / 2.0, height() / 2.0)); }
        QPoint toScreenI(const Vector &a);
        QPointF screenNormal(const Vector &a);

        void paintVector(QPainter &painter, const Vector &a,
                const QPointF &r0, const QColor &color, const QString &name);
        void paintAxis(QPainter &painter, const Vector &i, const QString &name);

        void paint_EH(QPainter &painter);
        void paint_axis(QPainter &painter, bool before);
        void paint_particle(QPainter &painter);
        void paint_track(QPainter &painter);
        void render_track();
        void addLastTrackPoint();
        void render(bool track = false);

        Particle *_particle;
        Vector e1, e2, n;
        double l, k;
        int timer;
        QPoint lastMousePos;
        QVector<Vector> trackPoints;
        bool _show_f, _show_v;
        QImage *buf_track;
};

#endif // MODELWIDGET_H

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent
