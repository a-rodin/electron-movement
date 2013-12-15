/*****************************************************************************
 * modelwidget.c                                                             *
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

#include "modelwidget.h"
#include <QPainter>
#include <QBrush>
#include <QColor>
#include <cmath>

#define pi 3.1415926536

ModelWidget::ModelWidget(QWidget *parent, Particle *particle)
    : QWidget(parent),
    e1(-1.0, 1.0, 0.0),
    e2(-1.0, -1.0, 1.5)
{
    _particle = particle;
    timer = 0;
    k = 3.0; l = 7.5 / k;
    _show_f = true; _show_v = true;
    n = Vector::vectMult(e1, e2).norm();
    buf_track = 0;
}

ModelWidget::~ModelWidget()
{
    delete buf_track;
}

void ModelWidget::resizeEvent(QResizeEvent *)
{
    delete buf_track;
    buf_track = new QImage(size(), QImage::Format_ARGB32_Premultiplied);
    render(true);
}

void ModelWidget::setZoom(double zoom)
{
    if (zoom == k)
        return;
    l *= (k / zoom);
    k = zoom;
    render(true);
}

void ModelWidget::start()
{
    trackPoints.push_back(_particle->r());
    timer = startTimer((int)(_particle->dt() * _particle->ndt() * 1000.0));
}

void ModelWidget::stop()
{
    killTimer(timer);
    timer = 0;
}

void ModelWidget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer) {
        _particle->move();
        trackPoints.push_back(_particle->r());
        addLastTrackPoint();
        render(false);
        while (! QRectF(0.0, 0.0, width(), height()).contains(toScreen(_particle->r(), 
                        QPointF(width()/2.0, height()/2.0)))) {
            setZoom(zoom() * 0.33);;
            emit zoomUpdated();
        }
        emit updated();
    } else {
        QWidget::timerEvent(event);
    }
}

QPointF ModelWidget::toScreen(const Vector &a, const QPointF &r0)
{
    return QPointF(
            r0.x() + k * (e1 * a) / e1.len() / 2.54 * physicalDpiX(),
            r0.y() - k * (e2 * a) / e2.len() / 2.54 * physicalDpiY());
}

QPointF ModelWidget::screenNormal(const Vector &a)
{
    double sx = (e1 * a), sy = (e2 * a), n;
    n = sqrt(sx * sx + sy * sy);
    return QPointF(sy/n, sx/n);
}

void ModelWidget::paintAxis(QPainter &painter, const Vector &i, const QString &name)
{
    painter.setPen(QPen(Qt::SolidLine));
    QPointF e = toScreen(i * l);
    painter.drawLine(toScreen(Vector::null()), e);
    QPointF n = screenNormal(i);
    double j = log10(l * 0.8);
    if (j <= 0) j -= 1;
    QPointF p = toScreen(i * pow(10.0, trunc(j)));
    painter.drawLine(p - 4 * n, p + 4 * n);
    QFont f = painter.font();
    f.setBold(false);
    painter.setFont(f);
    painter.drawText(toScreen(0.96 * l * i) - 10 * n, name);
    painter.drawText(p - 10 * n, QString().sprintf("%.0e", pow(10.0, trunc(j))) +
            QString::fromUtf8(" см"));
}

void ModelWidget::addLastTrackPoint()
{
    QPoint scr = toScreenI(trackPoints.last());
    if (rect().contains(scr))
        buf_track->setPixel(scr, QColor(Qt::gray).rgb());
}

QPoint ModelWidget::toScreenI(const Vector &a)
{

    QPointF pf = toScreen(a);
    return QPoint((int)round(pf.x()), (int)round(pf.y()));
}

void ModelWidget::render_track()
{
    buf_track->fill(QColor(0, 0, 0, 0).rgba());
    QRgb c = QColor(Qt::gray).rgb();
    for (QVector<Vector>::const_iterator i = trackPoints.begin(); i != trackPoints.end(); ++i) {
        QPoint scr = toScreenI(*i);
        if (rect().contains(scr))
            buf_track->setPixel(scr, c);
    }
}

void ModelWidget::paint_track(QPainter &painter)
{
    painter.drawImage(rect(), *buf_track);
}

void ModelWidget::paint_EH(QPainter &painter)
{
    paintVector(painter, _particle->E_current(), QPointF(1.2 / 2.54 * physicalDpiX(), 1.2 / 2.54* physicalDpiY()),
            QColor(Qt::green), "E");
    paintVector(painter, _particle->H_current(), QPointF(1.2 / 2.54 * physicalDpiY(), 3.6 / 2.54* physicalDpiY()),
            QColor(Qt::blue), "H");
}

namespace {
inline bool notSameSgn(double a, double b) 
{
    return (a >= 0.0) != (b >= 0.0);
}
}

void ModelWidget::paint_axis(QPainter &painter, bool after)
{
    double nrn = _particle->r() * n / _particle->r().len();
    if ((nrn < n.x) != after)
        paintAxis(painter, Vector(1.0, 0.0, 0.0), "x");
    if ((nrn < n.y) != after)
        paintAxis(painter, Vector(0.0, 1.0, 0.0), "y");
    if ((nrn < n.z) != after)
        paintAxis(painter, Vector(0.0, 0.0, 1.0), "z");
}

void ModelWidget::paint_particle(QPainter &painter)
{
    if (_show_f)
        paintVector(painter, _particle->F(), toScreen(_particle->r()), QColor(Qt::red), "F");
    if (_show_v)
        paintVector(painter, _particle->v(), toScreen(_particle->r()), QColor(Qt::black), "v");
    painter.setPen(QColor(Qt::darkBlue));
    painter.setBrush(QColor(Qt::cyan));
    painter.drawEllipse(toScreen(_particle->r()), 4, 4);
}

void ModelWidget::render(bool track)
{
    if (track)
        render_track();
    repaint();
}

void ModelWidget::paintVector(QPainter &painter, const Vector &a,
        const QPointF &r0, const QColor &color, const QString &name)
{
    QPointF e, n;
    if (! a.isNull()) {
        painter.setPen(QPen(QBrush(color), 2.0));
        e = toScreen(a.norm() / k, QPointF(0.0, 0.0));
        n = screenNormal(a);
        double len = sqrt(e.x() * e.x() + e.y() * e.y());
        painter.drawLine(r0, r0 + e);
        painter.drawLine(r0 + e, r0 + e * 0.8 + 0.1 * n * len);
        painter.drawLine(r0 + e, r0 + e * 0.8 - 0.1 * n * len);
    }
    painter.setPen(QColor(Qt::black));
    QFont f = painter.font();
    f.setBold(true);
    painter.setFont(f);
    if (a.isNull())
        painter.drawText(r0, name + " = 0");
    else
        painter.drawText(r0 + e * 0.9 + 10 * n, name);
}

void ModelWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        int dx = event->x() - lastMousePos.x();
        int dy = lastMousePos.y() - event->y();
        Vector dphi = - e2.norm() * ((double)dx / width() * 2 * pi);
        e1 += Vector::vectMult(dphi, e1);
        dphi = e1.norm() * ((double)dy / height() * 2 * pi);
        e2 += Vector::vectMult(dphi, e2);
        n = Vector::vectMult(e1, e2).norm();
        lastMousePos = event->pos();
        render(true);
    }
}

void ModelWidget::clearTrack()
{
    trackPoints.clear();
    render_track();
    render();
}

void ModelWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
        lastMousePos = event->pos();
}

void ModelWidget::wheelEvent(QWheelEvent *event)
{
    double m, e;
    m = modf(log10(k), &e);
    if (m == 1.0)
        e -= 1.0;
    setZoom(k + pow(10.0, trunc(e))*0.1*((event->delta() > 0) ? 1.0 : -1.0));
    emit zoomUpdated();
}

void ModelWidget::set_show_v(bool s)
{
    _show_v = s;
    render();
}

void ModelWidget::set_show_f(bool s)
{
    _show_f = s;
    render();
}

void ModelWidget::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(rect(), QColor(Qt::white));
    paint_track(painter);
    paint_axis(painter, true);
    paint_particle(painter);
    paint_axis(painter, false);
    paint_EH(painter);
    painter.end();
} 

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent

