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
    Description: This class delegates GUI's events to specific/corresponding object and decouples
                 application's logic from user interface
*/

#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H
#include <QColor>
#include "enumMode.h"
#include "movie.h"
#include "timeline.h"
#include "paintsettings.h"
#include "enumFrameType.h"

class EventDispatcher
{
public:
    EventDispatcher();
    //Paint settings
    QColor getFillColor();
    void setFillColor( QColor color );
    QColor getPenColor();
    void setPenColor( QColor color );
    int getPenWidth();
    void setPenWidth( int width );
    Mode getMode();
    void setMode( Mode mode );
    //TODO Gradients

    //Movie
    Movie getMovie(){ return movie; }
    QColor getBackgroundColor();
    void setBackgroundColor( QColor color );
    int getMovieWidth();
    void setMovieWidth( int width );
    int getMovieHeight();
    void setMovieHeight( int height );
    int getMovieFramerate();
    void setMovieFramerate( int framerate );

    //Timeline
    Timeline* getTimeline();

    Timeline* getCurrentTimeline();
    void setCurrentTimeline( Timeline* timeline );
    //Frame* getFrameAt( int framepos );
    void setFrameType( FrameType type, int layer, int framepos );

    //Library
    QList<Symbol*> getAllSymbols();
    void addSymbolToLibrary( Symbol* s );

private:
    Timeline* main_timeline;

    //Point to the main timeline or a symbol timeline
    Timeline* current_timeline;

    Movie movie;

    QList<Symbol*> library;
};

#endif // EVENTDISPATCHER_H
