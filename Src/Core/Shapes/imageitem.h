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

#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QGraphicsPixmapItem>
#include "graphicitem.h"

class ImageItem : public GraphicItem
{
public:
    ImageItem( const QPixmap& pixmap, QGraphicsItem* parent = 0 );    
    QString path();
    void setPath( const QString& resourcepath );
    QString getId();
    void setId( QString newid );
    void setMyFlag(bool f) {flag = f;}
    void setImage( QGraphicsPixmapItem* image );

    //Reimplemented from GraphicItem
    void changeGeometry( QPointF topLeft, QPointF bottomRight );
    void setFillColor( const QColor& fillColor );
    void setPenColor( const QColor& penColor );

    //Reimplemented from QGraphicsItem
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    QPainterPath shape() const;
    QRectF boundingRect() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event );

private:
    ImageItem* createClone();

    QGraphicsPixmapItem* image;
    QString imagePath;
    QString id;
    bool flag;
    bool selected;
};

#endif // IMAGEITEM_H
