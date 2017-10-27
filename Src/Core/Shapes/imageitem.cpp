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

#include "imageitem.h"
#include <QGraphicsSceneDragDropEvent>
#include <QMessageBox>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QStyle>

ImageItem::ImageItem( const QPixmap& pixmap, QGraphicsItem* )
{
    image = new QGraphicsPixmapItem( pixmap );
    setFlag( QGraphicsItem::ItemIsMovable );
    setFlag( QGraphicsItem::ItemIsSelectable );

    flag = false;
    selected = false;
    item_type = ImageType;
}

void ImageItem::changeGeometry( QPointF topLeft, QPointF bottomRight )
{

}

void ImageItem::setFillColor( const QColor&  )
{

}

void ImageItem::setPenColor( const QColor&  )
{

}

QString ImageItem::path()
{
    return imagePath;
}
void ImageItem::setPath( const QString& resourcepath )
{
    imagePath = resourcepath;
}
QString ImageItem::getId()
{
    return id;
}
void ImageItem::setId( QString newid )
{
    id = newid;
}
 void ImageItem::paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget )
 {
      image->paint( painter, option, widget );
 }

void ImageItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    selected = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}
void ImageItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    selected = false;
    QGraphicsItem::mouseReleaseEvent(event);
}



void ImageItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event )
{
    QRectF br = boundingRect();
    if( event->pos() == br.topLeft() )
    {
        setCursor( QCursor( Qt::SizeFDiagCursor ) );

    }

    setCursor( QCursor( Qt::SizeAllCursor ) );

    QGraphicsItem::mouseMoveEvent( event );
}

 QPainterPath ImageItem::shape() const
 {
     return image->shape();
 }

QRectF ImageItem::boundingRect() const
{
      return image->boundingRect();
}

ImageItem* ImageItem::createClone()
{
    ImageItem* aClone = new ImageItem( QPixmap( this->imagePath ) );
    aClone->setPos( this->pos() );
    aClone->setPath( this->imagePath );
    aClone->setZValue( this->zValue() );
    aClone->setLayerNumber( this->getLayerNumber() );

    return aClone;
}

void ImageItem::setImage( QGraphicsPixmapItem* _image )
{
    image = _image;
}


