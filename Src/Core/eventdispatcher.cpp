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

#include "eventdispatcher.h"

EventDispatcher::EventDispatcher()
{
    main_timeline = new Timeline();
    this->current_timeline = this->main_timeline;

    movie = Movie();
}

//Paint settings
QColor EventDispatcher::getFillColor()
{
    return PaintSettings::getFillColor();
}

void EventDispatcher::setFillColor( QColor color )
{
    PaintSettings::setFillColor( color );
}

QColor EventDispatcher::getPenColor()
{
    return PaintSettings::getPenColor();
}

void EventDispatcher::setPenColor( QColor color )
{
    PaintSettings::setPenColor( color );
}

int EventDispatcher::getPenWidth()
{
    return PaintSettings::getPenWidth();
}

void EventDispatcher::setPenWidth( int width )
{
    PaintSettings::setPenWidth( width );
}

Mode EventDispatcher::getMode()
{
    return PaintSettings::getMode();
}

void EventDispatcher::setMode( Mode mode )
{
    PaintSettings::setMode( mode );

}

//Movie
QColor EventDispatcher::getBackgroundColor()
{
    return movie.getBackgroundColor();
}

void EventDispatcher::setBackgroundColor( QColor color )
{
    movie.setBackgroundColor( color );
}

int EventDispatcher::getMovieWidth()
{
    return movie.getWidth();
}

void EventDispatcher::setMovieWidth( int width )
{
    movie.setWidth( width );
}

int EventDispatcher::getMovieHeight()
{
    return movie.getHeight();
}

void EventDispatcher::setMovieHeight( int height )
{
    movie.setHeight( height );
}

int EventDispatcher::getMovieFramerate()
{
    return movie.getFramerate();
}

void EventDispatcher::setMovieFramerate( int framerate )
{
    movie.setFramerate( framerate );
}

//Timeline
Timeline* EventDispatcher::getTimeline()
{
    return this->main_timeline;
}

Timeline* EventDispatcher::getCurrentTimeline()
{
    return this->current_timeline;
}

void EventDispatcher::setCurrentTimeline( Timeline* timeline )
{
    this->current_timeline = timeline;
}

void EventDispatcher::setFrameType( FrameType type, int layer, int framepos )
{
    if( current_timeline )
        current_timeline->setFrameType( type, framepos, layer );
}

//Library
QList<Symbol*> EventDispatcher::getAllSymbols()
{
    return this->library;
}

void EventDispatcher::addSymbolToLibrary( Symbol* s )
{
    this->library.append( s );
}















