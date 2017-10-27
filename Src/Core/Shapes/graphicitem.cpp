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

#include "graphicitem.h"

GraphicItem::GraphicItem()
{
    selected = false;
    this->layer_number = 0;
    this->frame_number = 0;
}

void GraphicItem::mousePressEvent( QGraphicsSceneMouseEvent* event )
{
    selected = true;
    QGraphicsItem::mousePressEvent( event );
}

bool GraphicItem::isSymbol()
{
    return false;
}

GraphicItem* GraphicItem::clone()
{
    GraphicItem* aClone = createClone();

    return aClone;
}

double GraphicItem::xToDraw()
{
    return pos().x();
}

double GraphicItem::yToDraw()
{
    return pos().y();
}

void GraphicItem::setItemType( GraphicItemType new_type )
{
    this->item_type = new_type;
}

GraphicItemType GraphicItem::getItemType()
{
    return this->item_type;
}

QColor GraphicItem::getFillColor()
{
    return QColor();
}

QColor GraphicItem::getPenColor()
{
    return QColor();
}

int GraphicItem::getLayerNumber()
{
    return this->layer_number;
}

void GraphicItem::setLayerNumber( int layer_number )
{
    this->layer_number = layer_number;
}

int GraphicItem::getFrameNumber()
{
    return this->frame_number;
}

void GraphicItem::setFrameNumber( int frame_number )
{
    this->frame_number = frame_number;
}

//Used to sort the list of items by the depth for layers support
/*bool GraphicItem::operator<( const GraphicItem* i2 ) const
{std::cout<< " menor..." << std::endl;
    if( this->zValue() < i2->zValue() )
        return true;

    return false;
}*/


