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

#include "movie.h"

Movie::Movie()
{
    width = 400;
    height = 300;
    framerate = 12.0;
    backgroundcolor = QColor( Qt::white );
}

Movie::~Movie()
{

}

void Movie::setWidth( int w )
{
    if( w > 0 )
        this->width = w;
}
void Movie::setHeight( int h )
{
    if( h > 0 )
        this->height = h;
}
void Movie::setFramerate( int fr )
{
    if( fr > 0 )
        this->framerate = fr;
}
void Movie::setBackgroundColor( QColor b_color )
{
    this->backgroundcolor = b_color;
}

int Movie::getWidth()
{
    return width;
}

int Movie::getHeight()
{
    return height;
}

int Movie::getFramerate()
{
    return framerate;
}

QColor Movie::getBackgroundColor()
{
    return backgroundcolor;
}

