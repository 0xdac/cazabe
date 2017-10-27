/***************************************************************************
 *   Cazabe is a free vector animation IDE                                 *
 *   Copyright (C) 2009 Darien Alonso Camacho                              *
 *   Copyright (C) 2010,2011 Joven Club de Computacion y Electronica V.C   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.           *
 **************************************************************************/

/*********************** File Info *****************************************
    Written by Darien Alonso Camacho darienad030111@vcl.jovenclub.cu
    Date: 2010
    Description:
*/

#ifndef CMDICHILD_H
#define CMDICHILD_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QCompleter>
#include "../../Core/scene.h"
#include "highlighter.h"
#include "codeeditor.h"


 class CodeEditorMdiChild : public QWidget
 {
     Q_OBJECT

 public:     
     CodeEditorMdiChild();

     void newFile();
     bool loadFile(const QString &fileName);
     bool save();
     bool saveAs();
     bool saveFile();
     QString userFriendlyCurrentFile();
     void insertSceneItem( const QString& path );
     void setDocument( QTextDocument* newDocument );

 protected:
     void closeEvent(QCloseEvent *event);

 private slots:
     void documentWasModified();

 private:
    bool maybeSave();
    void setCurrentFile(const QString &fileName);
    QString strippedName();
    QAbstractItemModel* modelFromFile( const QString& fileName );
    QGraphicsView* graphicsView;
    CodeEditor* editor;
    Highlighter* highLighter;
    QCompleter* completer;
    QString currentFile;
};

 #endif
