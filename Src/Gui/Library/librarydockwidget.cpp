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

#include "librarydockwidget.h"
#include <QListWidgetItem>

LibraryDockWidget::LibraryDockWidget()
{
    setWindowTitle( tr( "Library" ) );
    setAllowedAreas( Qt::RightDockWidgetArea );
    setFixedWidth( 209 );    

    //library_scene = QGraphicsScene();
    library_view = new QGraphicsView( &library_scene );
    library_view->setFixedHeight( 130 );

    symbols_list = new QListWidget();    
    //symbols_list->addItem( "First symbol" );
    symbols_list->setSelectionMode( QAbstractItemView::SingleSelection );
    symbols_list->setDragEnabled( true );

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget( library_view );
    layout->addWidget( symbols_list );

    QWidget* aux = new QWidget;
    aux->setLayout( layout );

    setWidget( aux );
    connect( symbols_list, SIGNAL( itemClicked(QListWidgetItem*) ), this, SLOT( showItemPreview(QListWidgetItem*) ) );
}

void LibraryDockWidget::updateSymbolsList( QList<Symbol*> symbols )
{
    symbols_list->clear();

    for( int i = 0; i < symbols.size(); i ++ )
    {
        LibrarySymbolsItem* item = new LibrarySymbolsItem();
        Symbol* s = dynamic_cast<Symbol*>( symbols.at( i )->clone() );

        item->setSymbol( s );
        item->setText( QString( s->name().c_str() ) );

        if( s->symbolType() == MovieClipSymbol )
        {
            QIcon icon( ":/images/testmovie.png" );
            item->setIcon( icon );
        }
        else if( s->symbolType() == GraphicSymbol )
        {
            QIcon icon( ":/images/colors.png" );
            item->setIcon( icon );
        }
        else if( s->symbolType() == ButtonSymbol )
        {
            QIcon icon( ":/images/pointer.png" );
            item->setIcon( icon );
        }
        symbols_list->addItem( item );
    }
}

//Slots
void LibraryDockWidget::showItemPreview( QListWidgetItem* item )
{
    LibrarySymbolsItem* x_item = dynamic_cast<LibrarySymbolsItem*>( item );
    Symbol* s = dynamic_cast<Symbol*>( x_item->getSymbol()->clone() );
    //s->changeGeometry( QPointF( 0.0, 0.0 ), QPointF( 5.0, 5.0 ) );
    library_scene.clear();
    library_scene.addItem( s );
}

/*
void LibraryDockWidget::showSceneProperties( Movie mainMovie )
{
    widthValue->setData( QVariant( mainMovie.getWidth()), Qt::DisplayRole );
    heightValue->setData( QVariant( mainMovie.getHeight()), Qt::DisplayRole );
    frameRateValue->setData( QVariant( mainMovie.getFramerate()), Qt::DisplayRole );

    propertyEditor->setModel( sceneModel );
    propertyEditor->setItemDelegate( movieDelegate );
}

void LibraryDockWidget::takeItem( QGraphicsItem* item )
{
    if( !flagModel )
    {
        //Only for items
        itemWidth = new QStandardItem( tr( "Width" ) );
        itemHeight = new QStandardItem( tr( "Height" ) );
        itemWidthValue = new QStandardItem;
        itemHeightValue = new QStandardItem;
        itemColor = new QStandardItem( tr( "Color" ) );
        xPos = new QStandardItem( tr( "X" ) );
        yPos = new QStandardItem( tr( "Y" ) );
        xPosValue = new QStandardItem;
        yPosValue = new QStandardItem;
        instanceName = new QStandardItem( tr( "Instance" ) );
        instanceNameValue = new QStandardItem;
        itemBoder = new QStandardItem( tr( "Border" ) );
        itemBorderValue = new QStandardItem;

        //Item model
        itemModel = new QStandardItemModel( 7, 2 );
        itemModel->setItem( 0, 0, itemWidth );
        itemModel->setItem( 0, 1, itemWidthValue );
        itemModel->setItem( 1, 0, itemHeight );
        itemModel->setItem( 1, 1, itemHeightValue );
        itemModel->setItem( 2, 0, xPos );
        itemModel->setItem( 2, 1, xPosValue );
        itemModel->setItem( 3, 0, yPos );
        itemModel->setItem( 3, 1, yPosValue );
        itemModel->setItem( 4, 0, itemColor );
        itemModel->setItem( 5, 0, itemBoder );
        itemModel->setItem( 5, 1, itemBorderValue );
        itemModel->setItem( 6, 0, instanceName );
        itemModel->setItem( 6, 1, instanceNameValue );

        itemDelegate = new ItemPropertyDelegate;

        connect( itemDelegate, SIGNAL( widthChanged(int) ), this, SLOT( setItemWidth(int) ) );
        connect( itemDelegate, SIGNAL( heightChanged(int) ), this, SLOT( setItemHeight(int) ) );
        connect( itemDelegate, SIGNAL( colorChanged(QColor) ), this, SLOT( setItemColor(QColor) ) );

        flagModel = true;
    }

    propertyEditor->setModel( itemModel );
    propertyEditor->setItemDelegate( itemDelegate );

    itemWidthValue->setData( QVariant( item->boundingRect().width() ), Qt::DisplayRole );
    itemHeightValue->setData( QVariant( item->boundingRect().height() ), Qt::DisplayRole );

    if( typeid( *item ) != typeid( TextItem ) )
    {
        GraphicItem* gItem = dynamic_cast<GraphicItem*>(item);
        if( gItem->isSymbol() )
        {
            Symbol* symbol = (Symbol*) gItem;
            QString name = QString( symbol->name().c_str() );
            instanceNameValue->setData( QVariant( name ), Qt::DisplayRole );
        }
        else
        {
            instanceNameValue->setData( QVariant( "" ), Qt::DisplayRole );
        }

        int x = item->mapToScene( item->boundingRect().topLeft() ).x();
        int y = item->mapToScene( item->boundingRect().topLeft() ).y();

        xPosValue->setData( QVariant( x ), Qt::DisplayRole );
        yPosValue->setData( QVariant( y ), Qt::DisplayRole );        
    }
    currentItem = item;
}

//Slots
void LibraryDockWidget::setItemWidth( int value )
{
    if( currentItem != 0 )
    {
        if( typeid( *currentItem ) == typeid( QGraphicsRectItem )  )
        {
            QRectF rect( ((QGraphicsRectItem*)currentItem)->rect() );
            rect.setWidth( value );
            ((QGraphicsRectItem*)currentItem)->setRect( rect );
        }
        else if( typeid( *currentItem ) == typeid( QGraphicsEllipseItem ) )
        {
            QRectF rect( ((QGraphicsEllipseItem*)currentItem)->rect() );
            rect.setWidth( value );
            rect.setHeight( value );
            ((QGraphicsEllipseItem*)currentItem)->setRect( rect );
        }
        if( typeid( *currentItem ) == typeid( EllipseItem )  )
        {
            /*QRectF rect( ((EllipseItem*)currentItem)->rect() );
            rect.setWidth( value );
            ((EllipseItem*)currentItem)->setRect( rect );
        }
    }
}

void LibraryDockWidget::setItemHeight( int value )
{
    if( currentItem != 0 )
    {
        if( typeid( *currentItem ) == typeid( QGraphicsRectItem )  )
        {
            QRectF rect( ((QGraphicsRectItem*)currentItem)->rect() );
            rect.setHeight( value );
            ((QGraphicsRectItem*)currentItem)->setRect( rect );
        }
        else if( typeid( *currentItem ) == typeid( QGraphicsEllipseItem ) )
        {
            QRectF rect( ((QGraphicsEllipseItem*)currentItem)->rect() );
            rect.setWidth( value );
            rect.setHeight( value );
            ((QGraphicsEllipseItem*)currentItem)->setRect( rect );
        }
        if( typeid( *currentItem ) == typeid( EllipseItem )  )
        {
            /*QRectF rect( ((EllipseItem*)currentItem)->rect() );
            rect.setHeight( value );
            ((EllipseItem*)currentItem)->setRect( rect );
        }
    }
}

void LibraryDockWidget::setItemColor( const QColor& color )
{
    if( currentItem != 0 )
    {
        /*if( typeid( *currentItem ) == typeid( TextItem ) )
        {
            ((QGraphicsTextItem*)currentItem)->setDefaultTextColor( color );
            currentItem->update();
        }
        else
        {
            (dynamic_cast<GraphicItem*>(currentItem))->setFillColor( color );
            currentItem->update();
        //}

    }
}
*/















