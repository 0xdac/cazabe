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

#include "paintsettings.h"


PaintSettings::PaintSettings()
{

}

QColor PaintSettings::pen_color = QColor( Qt::black );
int PaintSettings::pen_width = 1;
QColor PaintSettings::fill_color = QColor( Qt::white );
Mode PaintSettings::mode = MoveItem;
QFont PaintSettings::font = QFont( "Arial" );


QColor PaintSettings::getFillColor()
{
    return fill_color;
}

void PaintSettings::setFillColor( QColor color )
{
    fill_color = color;
}

QColor PaintSettings::getPenColor()
{
    return pen_color;
}

void PaintSettings::setPenColor( QColor color )
{
    pen_color = color;
}

int PaintSettings::getPenWidth()
{
    return pen_width;
}

void PaintSettings::setPenWidth( int width )
{
    if( width >= 0 )
        pen_width = width;
}

Mode PaintSettings::getMode()
{
    return mode;
}

QFont PaintSettings::getFont()
{
    return font;
}

void PaintSettings::setFont( QFont f )
{
    font = f;
}

void PaintSettings::setMode( Mode m )
{
    mode = m;
}

