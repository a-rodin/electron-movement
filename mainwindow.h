/*****************************************************************************
 * mainwindow.h                                                              *
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "modelwidget.h"
#include "particle.h"
#include "fieldedit.h"
#include "ui_mainwindow.h"

class MainWindow: public QMainWindow, private Ui::MainWindow {
    Q_OBJECT
    
    public:
        MainWindow(QWidget *parent = 0);
        virtual ~MainWindow();

    private slots:
        void on_button_start_toggled(bool checked);
        void on_button_add_field_clicked();
        void realToUser();
        void userToReal();
        void zoomChanged();
        void updateZoom();
        void fieldEditClosed();
        void fieldEditPaused(bool p);
        void on_action_save_triggered();
        void on_action_open_triggered();

    private:
        void loadFromFile(const QString &fileName);
        void saveToFile(const QString &fileName);
        ModelWidget *w;
        Particle *particle;
        QVector<FieldEdit*> fieldEdits;
        FieldEdit *addFieldEdit(int classId);
};

#endif // MAINWINDOW_H

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent
