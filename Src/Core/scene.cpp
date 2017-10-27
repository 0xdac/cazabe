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
#include "scene.h"
#include "button.h"
#include "graphic.h"
#include "movieclip.h"
#include "../Gui/Library/librarydockwidget.h"
//#include <QMessageBox>

Scene::Scene( QObject* parent ): QGraphicsScene( parent )
{
    auxItem = 0;
    auxSymbol = 0;
    leftMouseButton = false;
    test_item = 0;
    control_point_pos = -1;
    dropped_item = 0;

}

void Scene::editorLostFocus( TextItem* item )
{
    /*QTextCursor cursor = item->textCursor();
    cursor.clearSelection();
    item->setTextCursor(cursor);

    if (item->toPlainText().isEmpty()) {
        removeItem( (QGraphicsTextItem*) item);
        item->deleteLater();
    }*/

    QTextCursor cursor = item->textCursor();
    cursor.clearSelection();
    item->setTextCursor( cursor );

    if (item->toPlainText().isEmpty())
    {
        removeItem( item);
        item->deleteLater();
    }
}

void Scene::mousePressEvent( QGraphicsSceneMouseEvent* mouseEvent )
{
    if( mouseEvent->button() != Qt::LeftButton )
       return;

    QPen pen;
    pen.setWidth( PaintSettings::getPenWidth() );
    pen.setColor( PaintSettings::getPenColor() );
    QBrush brush( PaintSettings::getFillColor() );
    
    QFont f;
    QLineF line;
    LineItem* lineItem = 0;
    RectItem* rectItem = 0;
    TextItem* textItem = 0;
    CircleItem* circleItem;
    EllipseItem* ellipseItem;

    Mode mode = PaintSettings::getMode();

    switch( mode )
    {    
        case InsertItem:
        break;
        case FreeDrawing:
        break;
        case InsertRoundRect:
        break;

        case FreeTransformItem:
            QGraphicsScene::mousePressEvent( mouseEvent );
            leftMouseButton = true;
            if( selectedItems().size() == 1 )
            {
                test_item = dynamic_cast<GraphicItem*>(selectedItems().at( 0 )) ;
                if( test_item->getItemType() == RectType || test_item->getItemType() == PathType )
                {
                    test_item->selected = true;
                    control_point_pos = ((RectItem*)test_item)->containsControlPoint( mouseEvent->scenePos() );
                }
            }
            else deselectAll();
        break;

        case InsertRect:
            leftMouseButton = true;
            startPoint = mouseEvent->scenePos(); 
            rectItem = new RectItem( pen, brush );
            auxItem = rectItem;
            addItem( rectItem );
            deselectAll();
            emit itemInserted( auxItem );
        break;

        case InsertLine:
            startPoint = mouseEvent->scenePos();
            leftMouseButton = true;
            lineItem = new LineItem( pen );
            auxItem = lineItem;
            addItem( lineItem );
            deselectAll();
            emit itemInserted( auxItem );
        break;

        case InsertText:
            textItem = new TextItem();
            // TODO fonts
            f = PaintSettings::getFont();
            f.setPixelSize( 20 );
            textItem->setFont( f );//std::cout<< "Pase..." << std::endl;
            //textItem->setTextInteractionFlags( Qt::TextEditorInteraction );
            //textItem->setZValue( 1000.0 );
            //connect(textItem, SIGNAL(lostFocus(TextItem *)), this, SLOT(editorLostFocus(TextItem *)));
            /*connect(textItem, SIGNAL(selectedChange(QGraphicsItem *)),
                    this, SIGNAL(itemSelected(QGraphicsItem *)));*/
            textItem->setDefaultTextColor( pen.color() );
            textItem->setPos( mouseEvent->scenePos() );
            auxItem = textItem;
            addItem( textItem );
            emit itemInserted( auxItem );
        break;

        case TransformItem:
            QGraphicsScene::mousePressEvent( mouseEvent );
            leftMouseButton = true;
            if( selectedItems().size() > 0 )
            {
                test_item = dynamic_cast<GraphicItem*>(selectedItems().at( 0 ));
                ((GraphicItem*)test_item)->selected = true;
                control_point_pos = ((RectItem*)test_item)->containsControlPoint( mouseEvent->scenePos() );
            }
            else deselectAll();
        break;

        case MoveItem:
            leftMouseButton = true;
            /*
             * The line above is necessary right here to avoid
             * seg. fault in TextItem editorLostFocus SLOT
             */
            QGraphicsScene::mousePressEvent( mouseEvent );
            if( selectedItems().size() == 1 )
            {
                emit itemSelected( selectedItems().at( 0 ) );
            }
            else
            {
                deselectAll();
                emit sceneSelected();                
            }
        break;

        case InsertCircle:
            leftMouseButton = true;
            startPoint = mouseEvent->scenePos();    
            circleItem = new CircleItem( pen, brush );
            auxItem = circleItem;
            addItem( circleItem );
            deselectAll();
            emit itemInserted( auxItem );
        break;

        case InsertEllipse:
            leftMouseButton = true;
            startPoint = mouseEvent->scenePos();
            ellipseItem = new EllipseItem( pen, brush );
            auxItem = ellipseItem;
            addItem( ellipseItem );
            deselectAll();
            emit itemInserted( auxItem );
        break;
    }
    update();    

    QGraphicsScene::mousePressEvent( mouseEvent );
}

void Scene::deselectAll()
{
    foreach( QGraphicsItem* i, items() )
    {
        if( typeid( *i ) != typeid( TextItem ) ){
        GraphicItem* it = dynamic_cast<GraphicItem*>(i);
         if( it->selected )
         {
            it->selected = false;
            it->update();
         }
     }
    }

}

void Scene::mouseMoveEvent( QGraphicsSceneMouseEvent* mouseEvent )
{
    GraphicItem* item = 0;

    Mode mode = PaintSettings::getMode();

    switch( mode )
    {
        case InsertLine:
            if( leftMouseButton )
            {
                item = dynamic_cast<GraphicItem*>(auxItem);
                item->changeGeometry( startPoint, mouseEvent->scenePos() );
                update();
            }
        break;

        case TransformItem:
            if( leftMouseButton && test_item )
            {
                RectItem* r_item = (RectItem*) test_item;
                r_item->updateControlPoints( mouseEvent->scenePos(), control_point_pos );
                update();
            }
        break;

        case MoveItem:
            QGraphicsScene::mouseMoveEvent( mouseEvent );
            update();
        break;

        case InsertCircle:
            if( leftMouseButton )
            {
                item = dynamic_cast<GraphicItem*>(auxItem);
                item->changeGeometry( startPoint, mouseEvent->scenePos() );
                update();
            }
        break;

        case InsertEllipse:
            if( leftMouseButton )
            { 
                item = dynamic_cast<GraphicItem*>(auxItem);
                item->changeGeometry( startPoint, mouseEvent->scenePos() );
                update();
            }
        break;

        case InsertRect:
            if( leftMouseButton )
            {
                item = dynamic_cast<GraphicItem*>(auxItem);
                item->changeGeometry( startPoint, mouseEvent->scenePos() );
                update();
            }
        break;

        case FreeTransformItem:
            if( leftMouseButton && test_item )
            {
                if( test_item->getItemType() == RectType || test_item->getItemType() == PathType )
                {
                    RectItem* r_item = (RectItem*) test_item;
                    r_item->updateControlPoints( mouseEvent->scenePos(), control_point_pos );
                    update();
                }
            }

        break;

        case InsertItem:
        break;
        case InsertText:
        break;
        case FreeDrawing:
        break;
        case InsertRoundRect:
        break;
    }
}

void Scene::mouseReleaseEvent( QGraphicsSceneMouseEvent* event )
{
    if( leftMouseButton )
    {
        leftMouseButton = false;
        control_point_pos = -1;
        auxItem = 0;
    }
    /*if( dropped_item )
    {
        dropped_item->setPos( event->scenePos() );
        dropped_item = 0;
    }*/

    QGraphicsScene::mouseReleaseEvent( event );
}

/************ Drag and Drop *************/

void Scene::dragEnterEvent( QGraphicsSceneDragDropEvent* event )
{
    //cout<< "dragEnterEvent" << endl;

    QGraphicsScene::dragEnterEvent( event );
}
void Scene::dragMoveEvent( QGraphicsSceneDragDropEvent* event )
{
     /*if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
         if (event->source() == this) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
         } else {
             event->acceptProposedAction();
         }
     } else {
         event->ignore();
     }*/
    event->accept();
}
/*
void Scene::dragLeaveEvent( QGraphicsSceneDragDropEvent* event )
{
    //cout<< "dragLeaveEvent" << endl;
    QGraphicsScene::dragLeaveEvent( event );
}*/

void Scene::dropEvent( QGraphicsSceneDragDropEvent* event )
{
    if( typeid( *( event->source() ) ) == typeid( QListWidget ) )
    {
      QListWidget* source = dynamic_cast<QListWidget*>( event->source() );
      LibrarySymbolsItem* dropped = dynamic_cast<LibrarySymbolsItem*>( source->item( source->currentRow() ) );
      Symbol* s = dynamic_cast<Symbol*>( dropped->getSymbol()->clone() );
      //dropped_item = s;
      //qreal x = event->scenePos().x();
      //qreal y = event->scenePos().y();
      s->setPos( event->scenePos() );
      addItem( s );
      //s->setParentItem( 0 );//Make a top-level item

      //s->getFacade()->setPos( event->scenePos() );

      emit itemInserted( s );
    }

    QGraphicsScene::dropEvent( event );
}
/************ End Drag and Drop *************/

bool Scene::isItemChange(int type)
{
    foreach (QGraphicsItem *item, selectedItems()) {
        if (item->type() == type)
            return true;
    }
    return false;
}

void Scene::insertSceneItem( const QString& path )
{
    ImageItem* imageItem = new ImageItem( QPixmap( path ) );
    imageItem->setPath( path );
    addItem( imageItem );

    emit itemInserted( imageItem );
}

void Scene::keyPressEvent ( QKeyEvent * keyEvent )
{
    if( selectedItems().size() > 0 )
    {
            QGraphicsItem* item;
            if( keyEvent->key() == Qt::Key_Delete )
            {
                foreach( item, selectedItems() )
                {
                    removeItem( item );
                }
            update();
            //Emited to remove "item" from the specific frame
            emit itemRemoved( item );
        }
    }
    QGraphicsScene::keyPressEvent( keyEvent );
}

void Scene::convertItemToSymbol( SymbolType type, string name, Symbol* &result )
{
    Symbol* symbol = 0;
    QGraphicsItem* item = selectedItems().at( 0 );
    GraphicItem* gItem = dynamic_cast<GraphicItem*>( item );
    GraphicItem* clone = 0;

    switch( type )
    {
        case GraphicSymbol:
           symbol = new Graphic();
           clone = gItem->clone();
           symbol->setFacade( clone );
           symbol->setName( name );
           addItem( symbol );
           removeItem( item );
        break;

        case ButtonSymbol:
            symbol = new Button();
            clone = gItem->clone();
            symbol->setFacade( clone );
            symbol->setName( name );
            removeItem( item );
            addItem( symbol );
        break;

        case MovieClipSymbol:
            symbol = new MovieClip();
            clone = gItem->clone();
            symbol->setFacade( clone );
            symbol->setName( name );
            removeItem( item );
            addItem( symbol );
        break;
    }

    //First frame of symbol's timeline have an item which is the same of the symbol facade
    //symbol->timeline()->setFrameType( KeyFrame, 0, 0 );
    //symbol->timeline()->addItemToCurrentFrame( symbol );//clone

    //The param "result" now holds the symbol
    result = symbol;
    //Inform current frame that "item" was removed
    emit itemRemoved( item );
    //Inform current frame that "symbol" was inserted
    emit itemInserted( symbol );
}

Symbol* Scene::selectedSymbol()
{
    //QGraphicsItem* item = selectedItems().first();
    GraphicItem* item = dynamic_cast<GraphicItem*>( selectedItems().first() );
    if( item->isSymbol() )
        return (Symbol*) item;

    //return dynamic_cast<Symbol*>( item );
    /*if( typeid( *item ) == typeid( Button ) ){
        s = dynamic_cast<Button*>( item );
    }
    else if( typeid( *item ) == typeid( MovieClip ) ){
        s = dynamic_cast<MovieClip*>( item );
    }

    else if( typeid( *item ) == typeid( Graphic ) ){
        s = dynamic_cast<Graphic*>( item );
    }

    if( s )
        cout<< "pointer ok" <<endl;*/
    return 0;
}

/*Scene* Scene::clone()
{
	Scene* aClone = new Scene();
	
	foreach( QGraphicsItem* item, this->items() )
	{
		if( typeid( *item ) == typeid( TextItem ) )
		{
                        /*TextItem* newitem = new TextItem();
			newitem->setDefaultTextColor( ((TextItem*)item)->defaultTextColor() );
			newitem->setPlainText( ((TextItem*)item)->toPlainText() );
			newitem->setFont( ((TextItem*)item)->font() );
			newitem->setFlag( QGraphicsItem::ItemIsMovable );
			newitem->setFlag( QGraphicsItem::ItemIsSelectable );
			newitem->setPos( item->pos() );
			
                        aClone->addItem( newitem );/*
		}
		else
		{
                        GraphicItem* gItem = dynamic_cast<GraphicItem*>(item);;
			aClone->addItem( gItem->clone() );
		}                 
	}

	return aClone;
}*/
