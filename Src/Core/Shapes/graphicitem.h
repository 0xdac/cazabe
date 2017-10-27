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

#ifndef GRAPHICITEM_H
#define GRAPHICITEM_H

#include <QGraphicsItem>
#include <mingpp.h>
#include "../cloneable.h"
#include "../enumGraphicItemType.h"


/*
  This is the base class for all items in the scene, including
  symbols (graphics, buttons, movie clips)
  */

class Scene;

class GraphicItem : public QGraphicsItem, public Cloneable
{

public:
    GraphicItem();
    virtual GraphicItem* clone();
    virtual void changeGeometry( QPointF topLeft, QPointF bottomRight ) {}
    virtual void setFillColor( const QColor& fillColor ) {}
    virtual QColor getFillColor();
    virtual void setPenColor( const QColor& penColor ){}
    virtual QColor getPenColor();
    virtual int getPenWidth() { return 0; }
    virtual bool isSymbol();
    virtual double xToDraw();
    virtual double yToDraw();

    void setItemType( GraphicItemType new_type );
    GraphicItemType getItemType();

    int getLayerNumber();
    void setLayerNumber( int layer_number );
    int getFrameNumber();
    void setFrameNumber( int frame_number );

    //Used to sort the list of items by the depth for layers support
    //bool operator<( const GraphicItem* i2 ) const;

    //Reimplemented from QGraphicsItem
    virtual QRectF boundingRect() const {}
    virtual QPainterPath shape() const {}
    virtual void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0 ) {}
    virtual void mousePressEvent( QGraphicsSceneMouseEvent* event );
    bool selected;

protected:
    GraphicItemType item_type;

private:
    virtual GraphicItem* createClone() = 0;

    //The layer number this item belongs to
    int layer_number;
    //The frame number this item belongs to
    int frame_number;
};

#endif // GRAPHICITEM_H
