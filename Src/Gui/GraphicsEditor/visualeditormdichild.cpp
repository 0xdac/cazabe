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
#include "visualeditormdichild.h"

VisualEditorMdiChild::VisualEditorMdiChild()
{    
    graphicsView = new QGraphicsView;
    graphicsView->setFixedSize( 404, 304 );
    graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    graphicsView->setRenderHint(QPainter::Antialiasing);
    graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    graphicsView->setResizeAnchor(QGraphicsView::AnchorViewCenter);

    //graphicsView->setDragMode();
    graphicsView->setAcceptDrops( true );    

    Scene* scene = new Scene();
    scene->setSceneRect( QRectF( 0, 0, 400, 300 ) );
    graphicsView->setScene( scene );

    setWindowTitle( tr("Design") );

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget( graphicsView );

    setLayout(layout);
}


Symbol* VisualEditorMdiChild::selectedSymbol()
{
    Scene* current = (Scene*)graphicsView->scene();
    Symbol* symbol = 0;

    if( current != 0 )
    {
        symbol = current->selectedSymbol();
        return symbol;
    }
    else
        return 0;
}

void VisualEditorMdiChild::setItems( QList<QGraphicsItem*> all_items )
{    
    Scene* scene = (Scene*)graphicsView->scene();
    if( scene )
    {
        foreach( QGraphicsItem* item, scene->items() )
        {
            scene->removeItem( item );
        }

        foreach( QGraphicsItem* item, all_items )
        {           
            scene->addItem( item );
        }
    }
}


 void VisualEditorMdiChild::newFile()
 {

 }

 bool VisualEditorMdiChild::loadFile(const QString &fileName)
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

 bool VisualEditorMdiChild::save()
 {
    return true;
 }

 bool VisualEditorMdiChild::saveAs()
 {
     return true;
 }

 bool VisualEditorMdiChild::saveFile(const QString &fileName)
 {
     QFile file(fileName);
     if (!file.open(QFile::WriteOnly | QFile::Text)) {
         QMessageBox::warning(this, tr("MDI"),
                              tr("Cannot write file %1:\n%2.")
                              .arg(fileName)
                              .arg(file.errorString()));
         return false;
     }

     QTextStream out(&file);
     QApplication::setOverrideCursor( Qt::WaitCursor );
     QApplication::restoreOverrideCursor();

     setCurrentFile(fileName);
     return true;
 }

 QString VisualEditorMdiChild::userFriendlyCurrentFile()
 {
     return "asds";
 }

 void VisualEditorMdiChild::closeEvent( QCloseEvent* event )
 {
     event->ignore();
 }

 void VisualEditorMdiChild::documentWasModified()
 {
     //setWindowModified(document()->isModified());
 }

 bool VisualEditorMdiChild::maybeSave()
 {
     return true;
 }

 void VisualEditorMdiChild::setCurrentFile(const QString &/*fileName*/)
 {
     setWindowModified(false);
     setWindowTitle(userFriendlyCurrentFile() + "[*]");
 }

QString VisualEditorMdiChild::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void VisualEditorMdiChild::insertSceneItem( const QString& path )
{
    if( graphicsView->scene() )
    {
        Scene* mScene = (Scene*)graphicsView->scene();
        mScene->insertSceneItem( path );
    }
}

Scene* VisualEditorMdiChild::getScene()
{
    return (Scene*)graphicsView->scene();
}

void VisualEditorMdiChild::setScene( QGraphicsScene* newscene )
{
    graphicsView->setScene( newscene );
    QRectF s_rect = newscene->sceneRect();
    graphicsView->setFixedSize( s_rect.width() + 4, s_rect.height() + 4 );
}

QGraphicsView* VisualEditorMdiChild::getGraphicsView()
{
    return graphicsView;
}

void VisualEditorMdiChild::convertItemToSymbol( SymbolType type, string name, Symbol* &result )
{
    Scene* current = (Scene*)graphicsView->scene();
    if( current != 0 )
        current->convertItemToSymbol( type, name, result );
}








