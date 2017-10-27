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

#include "rectitem.h"

#include <QMessageBox>
#include <QApplication>
#include <QGraphicsSceneHoverEvent>

RectItem::RectItem( QPen& pen, QBrush& fillColor )
{
    setFlag( QGraphicsItem::ItemIsMovable );
    setFlag( QGraphicsItem::ItemIsSelectable );

    rect = new QGraphicsRectItem();
    rect->setPen( pen );
    rect->setBrush( fillColor );

    //How many control points
    const short n_control_points = 8;
    control_points = QVector<QPointF>( n_control_points );

    setAcceptHoverEvents( false );
    override_cursor = false;
    scale_rotate = false;
    item_type = RectType;
}

void RectItem::mousePressEvent( QGraphicsSceneMouseEvent* event )
{
    QGraphicsItem::mousePressEvent( event );
}

void RectItem::mouseReleaseEvent( QGraphicsSceneMouseEvent* event )
{
    QGraphicsItem::mouseReleaseEvent( event );
}

void RectItem::mouseMoveEvent( QGraphicsSceneMouseEvent* event )
{
    QGraphicsItem::mouseMoveEvent( event );
}

void RectItem::hoverLeaveEvent( QGraphicsSceneHoverEvent* event )
{
    if( override_cursor )
    {
        QApplication::restoreOverrideCursor();
        override_cursor = false;
    }
}

void RectItem::hoverMoveEvent( QGraphicsSceneHoverEvent* /*event*/ )
{
    if( !override_cursor )
    {
        QApplication::setOverrideCursor( Qt::WaitCursor );
        override_cursor = true;        
    }
}

void RectItem::initializePoints()
{
    QRectF b = rect->boundingRect();
    calcControlPoints( b );
}

void RectItem::calcControlPoints( QRectF b )
{
    control_points[ 0 ] = mapToScene( b.topLeft() );
    control_points[ 1 ] = mapToScene( b.topRight() );
    control_points[ 2 ] = mapToScene( b.bottomLeft() );
    control_points[ 3 ] = mapToScene( b.bottomRight() );
    //Middle left
    control_points[ 4 ] = mapToScene( QPointF( b.topLeft().x(), abs( b.topLeft().y() + b.bottomLeft().y() ) / 2 ));
    //Middle right
    control_points[ 5 ] = mapToScene( QPointF( b.topRight().x(), abs( b.topRight().y() + b.bottomRight().y() ) / 2 ));
    //Middle top
    control_points[ 6 ] = mapToScene( QPointF( abs( b.topLeft().x() + b.topRight().x() ) / 2, b.topLeft().y() ));
    //Middle bottom
    control_points[ 7 ] = mapToScene( QPointF( abs( b.bottomLeft().x() + b.bottomRight().x() ) / 2, b.bottomLeft().y() ));
}

void RectItem::updateControlPoints( QPointF point, int control_point_pos )
{
    int pos = control_point_pos;
    Mode mode = PaintSettings::getMode();
    QPointF p;

    if( pos != -1 ) //"point" is one of the control points
    {
        switch( mode )
        {
        case TransformItem:
            p = mapFromScene( point );
            if( pos == 4 )//Middle left
            {
                control_points[ 4 ].setX( p.x() );
                control_points[ 0 ].setX( p.x() );
                control_points[ 2 ].setX( p.x() );
                selected = true;
             }
             else if( pos == 5 )//Middle right
             {
                control_points[ 5 ].setX( p.x() );
                control_points[ 1 ].setX( p.x() );
                control_points[ 3 ].setX( p.x() );
                selected = true;
             }
             else if( pos == 6 )//Middle top
             {
                control_points[ 6 ].setY( p.y() );
                control_points[ 0 ].setY( p.y() );
                control_points[ 1 ].setY( p.y() );
                selected = true;
             }
             else if( pos == 7 )//Middle bottom
             {
                control_points[ 7 ].setY( p.y() );
                control_points[ 2 ].setY( p.y() );
                control_points[ 3 ].setY( p.y() );
                selected = true;
             }
        break;

        case FreeTransformItem:
            control_points[ pos ] = mapFromScene( point );
            item_type = PathType;
            selected = true;
        break;
        }
    }
}


int RectItem::containsControlPoint( QPointF point )
{
    int pos = -1;
    for( int i = 0; i< control_points.size(); i ++ )
    {
        QPointF temp = mapToScene( control_points[ i ] );
        if( point.x() > ( temp.x() - 3 ) && point.x() < ( temp.x() + 3 )
            && point.y() > ( temp.y() - 3 ) && point.y() < ( temp.y() + 3 ) )
        {
            pos = i;
            //Break searching
            i = control_points.size();            
        }
    }

    control_point_selected = pos;
    return pos;
}

QVector<QPointF> RectItem::getControlPoints()
{
    QVector<QPointF> points;

    for( int i = 0; i < control_points.size(); i ++ )
    {
        points.append( mapToScene( control_points.at( i ) ) );
    }

    return points;
}

void RectItem::changeGeometry( QPointF topLeft, QPointF bottomRight )
{
    QRectF theRect( topLeft, bottomRight );
    rect->setRect( theRect );
    initializePoints();
}

void RectItem::setFillColor( const QColor& fillColor )
{
    rect->setBrush( fillColor );
}

QColor RectItem::getFillColor()
{
    return this->rect->brush().color();
}

void RectItem::setPenColor( const QColor& penColor )
{
    rect->setPen( penColor );
}

QColor RectItem::getPenColor()
{
    return this->rect->pen().color();
}

void RectItem::paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget )
{
    // Construct the path
    QPainterPath my_path = getPath();

    // Draw the path
    QColor lg = Qt::red;

    painter->fillPath( my_path, rect->brush() );
    painter->strokePath( my_path, rect->pen() );

    if( selected )
    {
        Mode mode = PaintSettings::getMode();

        switch( mode )
        {
         case FreeTransformItem:
            painter->setPen( Qt::blue );
            painter->setBrush( Qt::blue );
            for( int i = 0; i< control_points.size(); i++ )
            {
                QPointF pos = control_points.at( i );      
                painter->drawEllipse( pos, 3, 3 );
            }
         break;

         case TransformItem:
            painter->setPen( Qt::blue );
            painter->setBrush( Qt::blue );
            for( int i = 4; i< 8; i++ )
            {
                QPointF pos = control_points.at( i );
                painter->drawRect( QRectF( pos.x() - 3,
                                       pos.y() - 3,
                                       3*2, 3*2 ) );
            }
            QPen bound_pen( Qt::DashLine );
            painter->setPen( bound_pen );
            painter->setBrush( Qt::transparent );
            painter->drawRect( boundingRect() );
         break;
        }
    }
}

QPainterPath RectItem::shape() const
{
    //return rect->shape();
    QPainterPath p = getPath();
    return p;
}

QPainterPath RectItem::getPath() const
{
    QPainterPath p;
    p.moveTo( control_points[ 0 ] );
    p.lineTo( control_points[ 6 ] );
    p.lineTo( control_points[ 1 ] );
    p.lineTo( control_points[ 5 ] );
    p.lineTo( control_points[ 3 ] );
    p.lineTo( control_points[ 7 ] );
    p.lineTo( control_points[ 2 ] );
    p.lineTo( control_points[ 4 ] );
    p.lineTo( control_points[ 0 ] );

    return p;
}

QRectF RectItem::boundingRect() const
{

    QPointF top_left = control_points[ 0 ];
    QPointF bottom_right = top_left;

    for( int i = 1; i < control_points.size(); i ++ )
    {
        qreal x = control_points[ i ].x();
        qreal y = control_points[ i ].y();

        if( x < top_left.x() )
            top_left.setX( x );
        if( y < top_left.y() )
            top_left.setY( y );
        if( x > bottom_right.x() )
            bottom_right.setX( x );
        if( y > bottom_right.y() )
            bottom_right.setY( y );
    }
    return QRectF( top_left, bottom_right );
}

RectItem* RectItem::createClone()
{    
    QPen pen = rect->pen();
    QBrush brush = rect->brush();
    RectItem* a_clone = new RectItem( pen, brush );
    a_clone->setPos( pos() );
    a_clone->setControlPoints( this->control_points );
    a_clone->setItemType( this->item_type );
    a_clone->setZValue( this->zValue() );

    return a_clone;
}

