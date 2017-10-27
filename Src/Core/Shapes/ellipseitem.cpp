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

#include "ellipseitem.h"

EllipseItem::EllipseItem( QPen& pen, QBrush& fillColor )
{    
    setFlag( QGraphicsItem::ItemIsMovable );
    setFlag( QGraphicsItem::ItemIsSelectable );
    ellipse = new QGraphicsEllipseItem();
    ellipse->setPen( pen );
    ellipse->setBrush( fillColor );

    //Inherited from GraphicItem
    item_type = EllipseType;
}

void EllipseItem::changeGeometry( QPointF topLeft, QPointF bottomRight )
{
    QRectF rect( topLeft, bottomRight );
    ellipse->setRect( rect );
}

void EllipseItem::setFillColor( const QColor& fillColor )
{
    ellipse->setBrush( fillColor );
}

QColor EllipseItem::getFillColor()
{
    return this->ellipse->brush().color();
}

void EllipseItem::setPenColor( const QColor& penColor )
{
    ellipse->setPen( penColor );
}

QColor EllipseItem::getPenColor()
{
    return this->ellipse->pen().color();
}

void EllipseItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    ellipse->paint( painter, option, widget );
}

QPainterPath EllipseItem::shape() const
{
    return ellipse->shape();
}

QRectF EllipseItem::boundingRect() const
{
    return ellipse->boundingRect();
}

EllipseItem* EllipseItem::createClone()
{
    QRectF rect = ellipse->rect();
    QPen pen = ellipse->pen();
    QBrush brush = ellipse->brush();
    EllipseItem* aClone = new EllipseItem( pen, brush );
    aClone->changeGeometry( rect.topLeft(), rect.bottomRight() );
    //newitem->setPen( ((EllipseItem*)item)->pen() );
    //newitem->setBrush( ((EllipseItem*)item)->brush() );
    aClone->setZValue( this->zValue() );
    aClone->setPos( pos() );
    aClone->setLayerNumber( this->getLayerNumber() );

    return aClone;
}

double EllipseItem::xToDraw()
{
    QPointF center =  ellipse->rect().center();
    center = mapToScene( center );

    return center.x();
}

double EllipseItem::yToDraw()
{
    QPointF center =  ellipse->rect().center();
    center = mapToScene( center );

    return center.y();
}



















