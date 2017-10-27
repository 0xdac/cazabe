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
#include "codeeditormdichild.h"

CodeEditorMdiChild::CodeEditorMdiChild()
{    
    editor = new CodeEditor();
    setWindowTitle( tr("Action Script") );    
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget( editor );
    setLayout( layout );

    highLighter = new Highlighter();
    completer = new QCompleter;
    completer->setModel( modelFromFile( "resources/wordlist.txt" ) );
    completer->setModelSorting( QCompleter::CaseInsensitivelySortedModel );
    completer->setCaseSensitivity( Qt::CaseInsensitive );
    completer->setWrapAround( false );
    editor->setCompleter( completer );
    currentFile = "";
}

 void CodeEditorMdiChild::newFile()
 {

 }

 bool CodeEditorMdiChild::loadFile( const QString &fileName )
 {
     QFile file(fileName);
     if (!file.open(QFile::ReadOnly | QFile::Text)) {
         QMessageBox::warning(this, tr("MDI"),
                              tr("Cannot read file %1:\n%2.")
                              .arg(fileName)
                              .arg(file.errorString()));
         return false;
     }

     QTextStream in(&file);
     QApplication::setOverrideCursor(Qt::WaitCursor);
     QApplication::restoreOverrideCursor();

     setCurrentFile(fileName);

     return true;
 }

 bool CodeEditorMdiChild::save()
 {
    return true;
 }

 bool CodeEditorMdiChild::saveAs()
 {
     return true;
 }

bool CodeEditorMdiChild::saveFile()
{
    if( currentFile.isEmpty() )
    {
        currentFile = QFileDialog::getSaveFileName(this,
                         tr("Choose a file name"), ".",
                         tr("ActionScript (*.hx)"));

        if ( currentFile.isEmpty() )
        return false;
    }

    QFile file( currentFile );
    if (!file.open( QFile::WriteOnly | QFile::Text) )
    {
         QMessageBox::warning(this, tr("MDI"),
                              tr("Cannot write file %1:\n%2.")
                              .arg(currentFile)
                              .arg(file.errorString()));
         return false;
     }

     QTextStream out( &file );
     QApplication::setOverrideCursor( Qt::WaitCursor );
     out << editor->toPlainText();
     QApplication::restoreOverrideCursor();

     setCurrentFile( currentFile );
     return true;
 }

 QString CodeEditorMdiChild::userFriendlyCurrentFile()
 {
     return strippedName();
 }

 void CodeEditorMdiChild::closeEvent( QCloseEvent* event )
 {
     event->ignore();
 }

 void CodeEditorMdiChild::documentWasModified()
 {

 }

 bool CodeEditorMdiChild::maybeSave()
 {
     if ( editor->document()->isModified() )
     {
         QMessageBox::StandardButton ret;
         ret = QMessageBox::warning(this, tr("Editor"),
                      tr("'%1' ha sido modificado.\n"
                         "Desea guardar los cambios?")
                      .arg(userFriendlyCurrentFile()),
                      QMessageBox::Save | QMessageBox::Discard
                      | QMessageBox::Cancel);
         if (ret == QMessageBox::Save)
             return saveFile();
         else if (ret == QMessageBox::Cancel)
             return false;
     }
     return true;
 }

 void CodeEditorMdiChild::setCurrentFile(const QString &/*fileName*/)
 {
     setWindowModified(false);
     setWindowTitle(userFriendlyCurrentFile() + "[*]");
 }

QString CodeEditorMdiChild::strippedName()
{
    return QFileInfo(currentFile).fileName();
}
void CodeEditorMdiChild::insertSceneItem( const QString& )
{

}
QAbstractItemModel *CodeEditorMdiChild::modelFromFile( const QString& fileName )
{
    QFile file( fileName );
    if ( !file.open( QFile::ReadOnly ) )
        return new QStringListModel( completer );

 #ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
 #endif
    QStringList words;

    while ( !file.atEnd() )
    {
        QByteArray line = file.readLine();
        if ( !line.isEmpty() )
            words << line.trimmed();
    }

 #ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
 #endif
    return new QStringListModel( words, completer );
}

void CodeEditorMdiChild::setDocument( QTextDocument* newDocument )
{    
    editor->setDocument( newDocument );
    highLighter->setDocument( newDocument );
}


