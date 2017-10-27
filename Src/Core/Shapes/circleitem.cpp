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

#include "circleitem.h"

CircleItem::CircleItem( QPen& pen, QBrush& fillColor )
{
    setFlag( QGraphicsItem::ItemIsMovable );
    setFlag( QGraphicsItem::ItemIsSelectable );
    circle = new QGraphicsEllipseItem();
    circle->setPen( pen );
    circle->setBrush( fillColor );

    //Inherited from GraphicItem
    item_type = CircleType;
}

void CircleItem::changeGeometry( QPointF topLeft, QPointF bottomRight )
{
    QRectF rect( topLeft, bottomRight );

    if( topLeft.x() != bottomRight.x() )
        rect.setHeight( rect.width() );

        circle->setRect( rect );
}

void CircleItem::setFillColor( const QColor& fillColor )
{
    circle->setBrush( fillColor );
}

void CircleItem::setPenColor( const QColor& penColor )
{
    circle->setPen( penColor );
}

QColor CircleItem::getFillColor()
{
    return this->circle->brush().color();
}

QColor CircleItem::getPenColor()
{
    return this->circle->pen().color();
}

void CircleItem::paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget )
{
    circle->paint( painter, option, widget );
}

QPainterPath CircleItem::shape() const
{
    return circle->shape();
}

QRectF CircleItem::boundingRect() const
{
    return circle->boundingRect();
}

CircleItem* CircleItem::createClone()
{
    QRectF rect = circle->rect();
    QPen pen = circle->pen();
    QBrush brush = circle->brush();
    CircleItem* aClone = new CircleItem( pen, brush );
    aClone->changeGeometry( rect.topLeft(), rect.bottomRight() );
    aClone->setPos( pos() );
    aClone->setZValue( this->zValue() );
    aClone->setLayerNumber( this->getLayerNumber() );

    return aClone;
}

double CircleItem::xToDraw()
{
    QPointF center =  circle->rect().center();
    center = mapToScene( center );

    return center.x();
}

double CircleItem::yToDraw()
{
    QPointF center =  circle->rect().center();
    center = mapToScene( center );

    return center.y();
}

















