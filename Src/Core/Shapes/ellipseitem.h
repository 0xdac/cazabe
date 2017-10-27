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


#ifndef ELLIPSEITEM_H
#define ELLIPSEITEM_H

#include <QGraphicsEllipseItem>
#include <QPen>
#include <QBrush>
#include "graphicitem.h"

class EllipseItem : public GraphicItem
{
public:
    EllipseItem( QPen& pen, QBrush& fillColor );

    //Reimplemented from GraphicItem
    void changeGeometry( QPointF topLeft, QPointF bottomRight );
    void setFillColor( const QColor& fillColor );
    QColor getFillColor();
    void setPenColor( const QColor& penColor );
    QColor getPenColor();
    int getPenWidth() { return this->ellipse->pen().width(); }
    double xToDraw();
    double yToDraw();

    void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );
    QPainterPath shape() const;
    QRectF boundingRect() const;

private:
    EllipseItem* createClone();

    QGraphicsEllipseItem* ellipse;
};

#endif // ELLIPSEITEM_H
