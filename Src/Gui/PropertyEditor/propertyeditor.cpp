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

#include "propertyeditor.h"

PropertyEditor::PropertyEditor()
{
    setWindowTitle( tr( "Properties" ) );
    setAllowedAreas( Qt::RightDockWidgetArea );
    setFixedWidth( 209 );    

    //Only for the main movie
    QStandardItem* frameRate = new QStandardItem( tr( "Framerate" ) );
    QStandardItem* sceneColor = new QStandardItem( tr( "Background" ) );
    frameRateValue = new QStandardItem;

    //For both, main movie and items
    width = new QStandardItem( tr( "Width" ) );
    height = new QStandardItem( tr( "Height" ) );
    widthValue = new QStandardItem;
    heightValue = new QStandardItem;

    movieDelegate = new ScenePropertyDelegate;

    connect( movieDelegate, SIGNAL( widthChanged(int) ), this, SIGNAL( widthChanged(int) ) );
    connect( movieDelegate, SIGNAL( heightChanged(int) ), this, SIGNAL( heightChanged(int) ) );
    connect( movieDelegate, SIGNAL( framerateChanged(int) ), this, SIGNAL( framerateChanged(int) ) );
    connect( movieDelegate, SIGNAL( colorChanged(QColor) ), this, SIGNAL( colorChanged(QColor) ) );

    propertyEditor = new QTableView;
    propertyEditor->setItemDelegate( movieDelegate );
    propertyEditor->verticalHeader()->setVisible( false );
    propertyEditor->horizontalHeader()->setVisible( false );

    //Scene model
    sceneModel = new QStandardItemModel( 4, 2 );
    sceneModel->setItem( 0, 0, width );
    sceneModel->setItem( 0, 1, widthValue );
    sceneModel->setItem( 1, 0, height );
    sceneModel->setItem( 1, 1, heightValue );
    sceneModel->setItem( 2, 0, frameRate);
    sceneModel->setItem( 2, 1, frameRateValue);
    sceneModel->setItem( 3, 0, sceneColor);

    propertyEditor->setModel( sceneModel );

    setWidget( propertyEditor );

    currentItem = 0;
    flagModel = false;
}

void PropertyEditor::showSceneProperties( Movie mainMovie )
{
    widthValue->setData( QVariant( mainMovie.getWidth()), Qt::DisplayRole );
    heightValue->setData( QVariant( mainMovie.getHeight()), Qt::DisplayRole );
    frameRateValue->setData( QVariant( mainMovie.getFramerate()), Qt::DisplayRole );

    propertyEditor->setModel( sceneModel );
    propertyEditor->setItemDelegate( movieDelegate );
}

void PropertyEditor::takeItem( QGraphicsItem* item )
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
void PropertyEditor::setItemWidth( int value )
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
            ((EllipseItem*)currentItem)->setRect( rect );*/
        }
    }
}

void PropertyEditor::setItemHeight( int value )
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
            ((EllipseItem*)currentItem)->setRect( rect );*/
        }
    }
}

void PropertyEditor::setItemColor( const QColor& color )
{
    if( currentItem != 0 )
    {
        /*if( typeid( *currentItem ) == typeid( TextItem ) )
        {
            ((QGraphicsTextItem*)currentItem)->setDefaultTextColor( color );
            currentItem->update();
        }
        else
        {*/
            (dynamic_cast<GraphicItem*>(currentItem))->setFillColor( color );
            currentItem->update();
        //}

    }
}
















