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

#include "lineitem.h"

LineItem::LineItem( QPen& pen )
{
    setFlag( QGraphicsItem::ItemIsMovable );
    setFlag( QGraphicsItem::ItemIsSelectable );

    line = new QGraphicsLineItem();
    line->setPen( pen );
    item_type = LineType;
}

void LineItem::changeGeometry( QPointF topLeft, QPointF bottomRight )
{
    QLineF newLine( topLeft, bottomRight );
    line->setLine( newLine );
}

void LineItem::setFillColor( const QColor& fillColor )
{
    QPen pen = line->pen();
    pen.setColor( fillColor );
    line->setPen( pen );
}

void LineItem::setPenColor( const QColor& penColor )
{

}

QLineF LineItem::getLine()
{
    QPointF p1 = mapToScene( line->line().x1(), line->line().y1() );
    QPointF p2 = mapToScene( line->line().x2(), line->line().y2() );

    QLineF line( p1, p2 );

    return line;
}

void LineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    line->paint( painter, option, widget );
}

QPainterPath LineItem::shape() const
{
    return line->shape();
}

QRectF LineItem::boundingRect() const
{
    return line->boundingRect();
}

LineItem* LineItem::createClone()
{
    QLineF newLine = line->line();
    QPen pen = line->pen();
    LineItem* aClone = new LineItem( pen );
    aClone->changeGeometry( line->line().p1(), line->line().p2() );
    aClone->setPos( pos() );
    aClone->setZValue( this->zValue() );
    aClone->setLayerNumber( this->getLayerNumber() );

    return aClone;
}
