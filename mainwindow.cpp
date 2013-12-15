/*****************************************************************************
 * mainwindow.cpp                                                            *
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

#include "mainwindow.h"
#include <QHBoxLayout>
#include <QSettings>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <cmath>
#include "vectoredit.h"
#include "scalaredit.h"
#include "fieldedits.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    sedit_m->setNameAndUnits("m", QString::fromUtf8("г"));
    sedit_q->setNameAndUnits("q", QString::fromUtf8("ед. СГС"));
    vedit_r->setNameAndUnits("r", QString::fromUtf8("см"));
    vedit_v->setNameAndUnits("v", QString::fromUtf8("см/с"));
    sedit_t->setNameAndUnits("t", QString::fromUtf8("с"));
    sedit_t0->setNameAndUnits("t<sub>0</sub>", QString::fromUtf8("с"));
    sedit_dt->setNameAndUnits(QString::fromUtf8("Δt<sub>i</sub>"), QString::fromUtf8("с"));
    sedit_n->setNameAndUnits("n<sub>i</sub>", "");
    particle = new Particle(
            9.11e-28, 4.80e-10,
            Vector(0.0, 0.6, 0.0), Vector(0.5, 0.0, 0.0),
            0.0, 0.0, 1e-3, 40);
    w = new ModelWidget(this, particle);
    new QHBoxLayout(frame);
    frame->layout()->addWidget(w);
    realToUser();
    updateZoom();
    check_show_f->setChecked(w->show_f());
    check_show_v->setChecked(w->show_v());
    connect(w, SIGNAL(updated()), this, SLOT(realToUser()));
    connect(w, SIGNAL(zoomUpdated()), this, SLOT(updateZoom()));
    connect(spin_zoom_m, SIGNAL(valueChanged(double)), this, SLOT(zoomChanged()));
    connect(spin_zoom_e, SIGNAL(valueChanged(int)), this, SLOT(zoomChanged()));
    connect(button_clear, SIGNAL(clicked()), w, SLOT(clearTrack()));
    connect(check_show_f, SIGNAL(toggled(bool)), w, SLOT(set_show_f(bool)));
    connect(check_show_v, SIGNAL(toggled(bool)), w, SLOT(set_show_v(bool)));
    for (int i = 0, n = FieldEdits::fieldEditsCount(); i < n; ++i)
        combo_fields->addItem(FieldEdits::fieldEditName(i));
}

FieldEdit * MainWindow::addFieldEdit(int id)
{
    FieldEdit *f = FieldEdits::newFieldEdit(id);
    if (f) {
        fieldEdits.append(f);
        connect(f, SIGNAL(paused(bool)), SLOT(fieldEditPaused(bool)));
        connect(f, SIGNAL(closed()), SLOT(fieldEditClosed()));
        fields_layout->addWidget(f);
        switch (f->type()) {
            case FieldEdit::Electric:
                particle->add_E(f->field());
                break;
            case FieldEdit::Magnetic:
                particle->add_H(f->field());
                break;
        }
        f->show();
    }
    return f;
}

void MainWindow::on_button_add_field_clicked()
{
    addFieldEdit(combo_fields->currentIndex());
    w->update();
}

void MainWindow::fieldEditClosed()
{
    FieldEdit *f = qobject_cast<FieldEdit *>(sender());
    switch (f->type()) {
        case FieldEdit::Electric:
            particle->remove_E(f->field());
            break;
        case FieldEdit::Magnetic:
            particle->remove_H(f->field());
            break;
    }
    fieldEdits.remove(fieldEdits.indexOf(f));
    delete f;
}
void MainWindow::loadFromFile(const QString &fileName)
{
    QSettings file(fileName, QSettings::IniFormat);
    if (file.status() != QSettings::NoError) {
        QMessageBox::critical(this, QString::fromUtf8("Ошибка"),
                QString::fromUtf8("Не удалось загрузить файл ") + fileName);
        return;
    }
    for (QVector<FieldEdit*>::const_iterator i = fieldEdits.begin(); i != fieldEdits.end(); ++i) {
        switch ((*i)->type()) {
            case FieldEdit::Electric:
                particle->remove_E((*i)->field());
                break;
            case FieldEdit::Magnetic:
                particle->remove_H((*i)->field());
                break;
        }
        delete *i;
    }
    fieldEdits.clear();
    file.beginReadArray("particle");
    particle->set_m(file.value("m").toDouble());
    particle->set_q(file.value("q").toDouble());
    particle->set_r(Vector(file.value("rx").toDouble(), file.value("ry").toDouble(), file.value("rz").toDouble()));
    particle->set_v(Vector(file.value("vx").toDouble(), file.value("vy").toDouble(), file.value("vz").toDouble()));
    particle->set_t(file.value("t").toDouble());
    particle->set_t0(file.value("t0").toDouble());
    particle->set_dt(file.value("dt").toDouble());
    particle->set_ndt(file.value("ndt").toUInt());
    int n = file.value("fieldsCount", 0).toInt();
    file.endArray();
    file.beginReadArray("visualization");
    w->set_show_f(file.value("show_f").toBool());
    w->set_show_v(file.value("show_v").toBool());
    w->setZoom(file.value("zoom").toDouble());
    updateZoom();
    file.endArray();
    for (int i = 0; i < n; ++i) {
        file.beginReadArray("field" + QString::number(i));
        FieldEdit *f = addFieldEdit(FieldEdits::fieldEditClassId(file.value("className").toString()));
        if (! f)
            break;
        f->setMinimized(file.value("minimized").toBool());
        f->setPaused(file.value("paused").toBool());
        file.beginReadArray("fieldData");
        f->loadSettings(file);
        file.endArray();
        file.endArray();
    }
    realToUser();
    w->clearTrack();
    w->update();
}

void MainWindow::saveToFile(const QString &fileName)
{
    QSettings file(fileName, QSettings::IniFormat);
    if (file.status() != QSettings::NoError) {
        QMessageBox::critical(this, QString::fromUtf8("Ошибка"),
                QString::fromUtf8("Не удалось сохранить в файл ") + fileName);
        return;
    }
    userToReal();
    file.clear();
    file.beginWriteArray("particle");
    file.setValue("m", particle->m());
    file.setValue("q", particle->q());
    file.setValue("rx", particle->r().x);
    file.setValue("ry", particle->r().y);
    file.setValue("rz", particle->r().z);
    file.setValue("vx", particle->v().x);
    file.setValue("vy", particle->v().y);
    file.setValue("vz", particle->v().z);
    file.setValue("t", particle->t());
    file.setValue("t0", particle->t0());
    file.setValue("dt", particle->dt());
    file.setValue("ndt", particle->ndt());
    file.setValue("fieldsCount", fieldEdits.size());
    file.endArray();
    file.beginWriteArray("visualization");
    file.setValue("show_f", w->show_f());
    file.setValue("show_v", w->show_v());
    file.setValue("zoom", w->zoom());
    file.endArray();
    for (int i = 0; i < fieldEdits.size(); ++i) {
        file.beginWriteArray("field" + QString::number(i));
        file.setValue("className", fieldEdits[i]->metaObject()->className());
        file.setValue("minimized", fieldEdits[i]->minimized());
        file.setValue("paused", fieldEdits[i]->paused());
        file.beginWriteArray("fieldData");
        fieldEdits[i]->saveSettings(file);
        file.endArray();
        file.endArray();
    }
}

void MainWindow::on_action_open_activated()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            QString::fromUtf8("Открыть модель"),
            QDir::currentPath(), "*.model");
    if (! fileName.isEmpty())
        loadFromFile(fileName);
}

void MainWindow::on_action_save_activated()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            QString::fromUtf8("Сохранить модель"),
            QDir::currentPath(), "*.model");
    if (! fileName.isEmpty()) {
        if (! fileName.endsWith(".model", Qt::CaseInsensitive))
            fileName += ".model";
        saveToFile(fileName);
    }
}

void MainWindow::fieldEditPaused(bool p)
{
    FieldEdit *f = qobject_cast<FieldEdit *>(sender());
    switch (f->type()) {
        case FieldEdit::Electric:
            if (p)
                particle->remove_E(f->field());
            else
                particle->add_E(f->field());
            break;
        case FieldEdit::Magnetic:
            if (p)
                particle->remove_H(f->field());
            else
                particle->add_H(f->field());
            break;
    }
}

void MainWindow::updateZoom()
{
    double m, e;
    m = modf(log10(w->zoom()), &e);
    if (m < 0.0) {
        m += 1.0;
        e -= 1.0;
    }
    spin_zoom_m->setValue(pow(10.0, m));
    spin_zoom_e->setValue((int)e);
}

void MainWindow::realToUser() {
    sedit_m->setValue(particle->m());
    sedit_q->setValue(particle->q());
    vedit_r->setValue(particle->r());
    vedit_v->setValue(particle->v());
    sedit_t->setValue(particle->t());
    sedit_t0->setValue(particle->t0());
    sedit_dt->setValue(particle->dt());
    sedit_n->setValue((double)particle->ndt());
}

void MainWindow::userToReal() {
    particle->set_m(sedit_m->value());
    particle->set_q(sedit_q->value());
    particle->set_r(vedit_r->value());
    particle->set_v(vedit_v->value());
    particle->set_t(sedit_t->value());
    particle->set_t0(sedit_t0->value());
    particle->set_dt(sedit_dt->value());
    particle->set_ndt((unsigned)sedit_n->value());
    for (QVector<FieldEdit*>::const_iterator i = fieldEdits.begin(); i != fieldEdits.end(); ++i)
        (*i)->readParams();
}

void MainWindow::zoomChanged()
{
    w->setZoom(spin_zoom_m->value() * pow(10.0, (double)spin_zoom_e->value()));
}

MainWindow::~MainWindow()
{
    delete particle;
    for (QVector<FieldEdit *>::const_iterator i = fieldEdits.begin(); i != fieldEdits.end(); ++i) {
        delete *i;
    }
}

void MainWindow::on_button_start_toggled(bool checked)
{
    sedit_m->setReadOnly(checked);
    sedit_q->setReadOnly(checked);
    vedit_r->setReadOnly(checked);
    vedit_v->setReadOnly(checked);
    sedit_t->setReadOnly(checked);
    sedit_t0->setReadOnly(checked);
    sedit_dt->setReadOnly(checked);
    sedit_n->setReadOnly(checked);
    button_clear->setDisabled(checked);
    button_add_field->setDisabled(checked);
    combo_fields->setDisabled(checked);
    for (QVector<FieldEdit *>::const_iterator i = fieldEdits.begin(); i != fieldEdits.end(); ++i)
        (*i)->setReadOnly(checked);
    if (checked) {
        button_start->setText(QString::fromUtf8("Остановить"));
        userToReal();
        w->start();
    } else {
        w->stop();
        button_start->setText(QString::fromUtf8("Запустить"));
    }
}

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent

