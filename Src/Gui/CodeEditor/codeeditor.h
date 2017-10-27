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

#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QCompleter>
#include <QObject>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class LineNumberArea;


 class CodeEditor : public QPlainTextEdit
 {
     Q_OBJECT

 public:
     CodeEditor(QWidget *parent = 0);

     void lineNumberAreaPaintEvent(QPaintEvent *event);
     int lineNumberAreaWidth();
     void setCompleter( QCompleter* completer );

 protected:
     void resizeEvent(QResizeEvent *event);
     void keyPressEvent(QKeyEvent *e);
     void focusInEvent(QFocusEvent *e);

 private slots:
     void updateLineNumberAreaWidth(int newBlockCount);
     void highlightCurrentLine();
     void updateLineNumberArea(const QRect &, int);
     void insertCompletion(const QString& completion);

 private:
     QString textUnderCursor() const;
     QWidget *lineNumberArea;
     QCompleter* completer;     
 };


 class LineNumberArea : public QWidget
 {
 public:
     LineNumberArea(CodeEditor *editor) : QWidget(editor) {
         codeEditor = editor;
     }

     QSize sizeHint() const {
         return QSize(codeEditor->lineNumberAreaWidth(), 0);
     }

 protected:
     void paintEvent(QPaintEvent *event) {
         codeEditor->lineNumberAreaPaintEvent(event);
     }

 private:
     CodeEditor *codeEditor;
 };

#endif // CODEEDITOR_H
