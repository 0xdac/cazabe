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

#include "symbol.h"

Symbol::Symbol()
{
    //QGraphicsItem
    setFlag( QGraphicsItem::ItemIsMovable );
    setFlag( QGraphicsItem::ItemIsSelectable );

    timeLine = new Timeline();
    item_type = SymbolInstanceType;
}

string Symbol::name()
{
    return symbolName;
}

void Symbol::setName( string name )
{
    symbolName = name;
}

SymbolType Symbol::symbolType()
{
    return this->symbol_type;
}

void Symbol::setFacade( GraphicItem* facade )
{
    symbolFacade = facade;
    setPos( symbolFacade->pos() );
}

GraphicItem* Symbol::getFacade()
{
    return symbolFacade;
}

Timeline* Symbol::timeline()
{
    return timeLine;
}

void Symbol::setTimeline( Timeline* timeline )
{
    timeLine = timeline;
}

void Symbol::changeGeometry( QPointF topLeft, QPointF bottomRight )
{
    //do nothing, for the moment
}

bool Symbol::isSymbol()
{
    return true;
}

void Symbol::setFillColor( const QColor& fillColor )
{
    symbolFacade->setFillColor( fillColor );
}
void Symbol::setPenColor( const QColor& penColor )
{
    symbolFacade->setPenColor( penColor );
}

double Symbol::xToDraw()
{
    return symbolFacade->pos().x();
}

double Symbol::yToDraw()
{
    return symbolFacade->pos().y();
}


//Reimplemented from QGraphicsItem
QRectF Symbol::boundingRect() const
{
    return symbolFacade->boundingRect();
}

QPainterPath Symbol::shape() const
{
    return symbolFacade->shape();
}

void Symbol::paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget )
{
    symbolFacade->paint( painter, option, widget );
}


