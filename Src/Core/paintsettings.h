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
    Description: This class holds all the paint settings.
                 With static members we can access it anywhere.

                 Update: 01/04/2011
                 This class will be removed in a future release because
                 we do not need access paint settings anywhere anymore.
                 Paint settings will be managed in Scene class.
*/

#ifndef PAINTSETTINGS_H
#define PAINTSETTINGS_H
#include <QColor>
#include <QFont>
#include "enumMode.h"


class PaintSettings
{
public:
    PaintSettings();
    static QColor getFillColor();
    static void setFillColor( QColor color );
    static QColor getPenColor();
    static void setPenColor( QColor color );
    static int getPenWidth();
    static void setPenWidth( int width );
    static Mode getMode();
    static void setMode( Mode m );
    static QFont getFont();
    static void setFont( QFont f );

private:
    static QColor fill_color;
    static QColor pen_color;
    static int pen_width;
    static Mode mode;
    static QFont font;
    //TODO Gradients
};


#endif // PAINTSETTINGS_H
