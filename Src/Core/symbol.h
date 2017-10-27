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

#ifndef SYMBOL_H
#define SYMBOL_H

#include "Shapes/graphicitem.h"
#include "cloneable.h"
#include "timeline.h"
#include <string>
using namespace std;

class Symbol : public GraphicItem
{
public:
    Symbol();
    string name();
    void setName( string name );
    SymbolType symbolType();

    void setFacade( GraphicItem* facade );
    GraphicItem* getFacade();
    Timeline* timeline();
    void setTimeline( Timeline* timeline );

    //Reimplemented from GraphicItem
    virtual void changeGeometry( QPointF topLeft, QPointF bottomRight );
    void setFillColor( const QColor& fillColor );
    void setPenColor( const QColor& penColor );
    bool isSymbol();
    double xToDraw();
    double yToDraw();

    //Reimplemented from QGraphicsItem
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0 );

protected:
    GraphicItem* symbolFacade;
    Timeline* timeLine;
    string symbolName;
    SymbolType symbol_type;

private:
    virtual Symbol* createClone() = 0;
};

#endif // SYMBOL_H
