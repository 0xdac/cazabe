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

#ifndef RECTITEM_H
#define RECTITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsWidget>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include "graphicitem.h"
#include "../enumMode.h"
#include "../scene.h"

class RectItem : public GraphicItem
{
public:
    RectItem( QPen& pen, QBrush& brush );

    void initializePoints();
    int containsControlPoint( QPointF point );
    void updateControlPoints( QPointF point, int control_point_pos );
    QVector<QPointF> getControlPoints();
    void setControlPoints( QVector<QPointF> points ) { this->control_points = points; }
    //void testFunction( QPointF point );

    //Reimplemented from GraphicItem
    void changeGeometry( QPointF topLeft, QPointF bottomRight );
    void setFillColor( const QColor& fillColor );
    QColor getFillColor();
    void setPenColor( const QColor& penColor );
    QColor getPenColor();
    int getPenWidth() { return this->rect->pen().width(); }
    void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );
    QPainterPath shape() const;
    QRectF boundingRect() const;

    void mousePressEvent( QGraphicsSceneMouseEvent* event );
    void mouseMoveEvent( QGraphicsSceneMouseEvent* event );
    void mouseReleaseEvent( QGraphicsSceneMouseEvent* event );
    void hoverMoveEvent ( QGraphicsSceneHoverEvent * event );
    void hoverLeaveEvent( QGraphicsSceneHoverEvent * event );

private:
    RectItem* createClone();    
    QPainterPath getPath() const;
    void calcControlPoints( QRectF r );

    QGraphicsRectItem* rect;
    QVector<QPointF> control_points;
    bool override_cursor;
    bool scale_rotate;
    int control_point_selected;
    QPointF itemCoord;
    Mode temp_mode;
};

#endif // RECTITEM_H
