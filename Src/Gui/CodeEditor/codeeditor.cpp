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

#include <QtGui>
#include "codeeditor.h"


 CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
 {
     lineNumberArea = new LineNumberArea(this);

     connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
     connect(this, SIGNAL(updateRequest(const QRect &, int)), this, SLOT(updateLineNumberArea(const QRect &, int)));
     connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

     updateLineNumberAreaWidth(0);
     highlightCurrentLine();

     completer = 0;
 }



 int CodeEditor::lineNumberAreaWidth()
 {
     int digits = 1;
     int max = qMax(1, blockCount());
     while (max >= 10) {
         max /= 10;
         ++digits;
     }

     int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

     return space;
 }



 void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
 {
     setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
 }



 void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
 {
     if (dy)
         lineNumberArea->scroll(0, dy);
     else
         lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

     if (rect.contains(viewport()->rect()))
         updateLineNumberAreaWidth(0);
 }



 void CodeEditor::resizeEvent(QResizeEvent *e)
 {
     QPlainTextEdit::resizeEvent(e);

     QRect cr = contentsRect();
     lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
 }



 void CodeEditor::highlightCurrentLine()
 {
     QList<QTextEdit::ExtraSelection> extraSelections;

     if (!isReadOnly()) {
         QTextEdit::ExtraSelection selection;

         QColor lineColor = QColor(Qt::yellow).lighter(160);

         selection.format.setBackground(lineColor);
         selection.format.setProperty(QTextFormat::FullWidthSelection, true);
         selection.cursor = textCursor();
         selection.cursor.clearSelection();
         extraSelections.append(selection);
     }

     setExtraSelections(extraSelections);
 }



 void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
 {
     QPainter painter(lineNumberArea);
     painter.fillRect(event->rect(), Qt::lightGray);


     QTextBlock block = firstVisibleBlock();
     int blockNumber = block.blockNumber();
     int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
     int bottom = top + (int) blockBoundingRect(block).height();

     while (block.isValid() && top <= event->rect().bottom()) {
         if (block.isVisible() && bottom >= event->rect().top()) {
             QString number = QString::number(blockNumber + 1);
             painter.setPen(Qt::black);
             painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                              Qt::AlignRight, number);
         }

         block = block.next();
         top = bottom;
         bottom = top + (int) blockBoundingRect(block).height();
         ++blockNumber;
     }
 }
void CodeEditor::setCompleter( QCompleter* _completer )
{
    if( completer )
        QObject::disconnect( completer, 0, this, 0 );

     completer = _completer;

     if ( !completer )
         return;

     completer->setWidget( this );
     completer->setCompletionMode( QCompleter::PopupCompletion );
     completer->setCaseSensitivity( Qt::CaseInsensitive );
     QObject::connect( completer, SIGNAL( activated(const QString&)),
                      this, SLOT(insertCompletion(const QString&)));
}
void CodeEditor::insertCompletion( const QString& completion )
{
    if( completer->widget() != this )
        return;
    QTextCursor tc = textCursor();
    int extra = completion.length() - completer->completionPrefix().length();
    tc.movePosition( QTextCursor::Left );
    tc.movePosition( QTextCursor::EndOfWord );
    tc.insertText( completion.right( extra ) );
    setTextCursor( tc );
}
QString CodeEditor::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}
void CodeEditor::keyPressEvent( QKeyEvent* e )
{
     if ( completer && completer->popup()->isVisible())
     {
        // The following keys are forwarded by the completer to the widget
        switch ( e->key() )
        {
            case Qt::Key_Enter:
            case Qt::Key_Return:
            case Qt::Key_Escape:
            case Qt::Key_Tab:
            case Qt::Key_Backtab:
                e->ignore();
                return; // let the completer do default behavior
            default:
                break;
        }
     }

     bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_Space); // CTRL+E     
     if( !completer)
     {
         setPlainText("asdasfda");
     }
     if (!completer || !isShortcut) // dont process the shortcut when we have a completer
         QPlainTextEdit::keyPressEvent(e);

     const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
     if (!completer || (ctrlOrShift && e->text().isEmpty()))
         return;

     static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
     bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
     QString completionPrefix = textUnderCursor();

     if (!isShortcut && (hasModifier || e->text().isEmpty()|| completionPrefix.length() < 3
                       || eow.contains(e->text().right(1))))
     {
         completer->popup()->hide();
         return;
     }

     if (completionPrefix != completer->completionPrefix())
     {
         completer->setCompletionPrefix(completionPrefix);
         completer->popup()->setCurrentIndex(completer->completionModel()->index(0, 0));
     }
     QRect cr = cursorRect();
     cr.setWidth(completer->popup()->sizeHintForColumn(0)
                 + completer->popup()->verticalScrollBar()->sizeHint().width());
     completer->complete(cr); // popup it up!    
}
 void CodeEditor::focusInEvent(QFocusEvent *e)
 {     
     if ( completer )
         completer->setWidget( this );
     QPlainTextEdit::focusInEvent(e);
 }
