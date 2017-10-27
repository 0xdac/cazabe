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

#ifndef TIMELINELAYER_H
#define TIMELINELAYER_H
#include <QDebug>
#include <QList>
#include "frame.h"
#include "Shapes/graphicitem.h"

/*
 Esta clase representa una capa de la linea de tiempo del nucleo de la aplicacion,
 no de la linea de tiempo de la interfaz grafica.


*/

class TimelineLayer
{
public:
    TimelineLayer();
    //Add item at current_frame
    void addItem( QGraphicsItem* item );
    void removeItem( QGraphicsItem* item );
    void hide();
    void show();
    void block();
    void unBlock();
    int getFramesCount();
    void setFrameType( FrameType type, int frame );
    Frame* getFrame( int frame, bool prevKeyFrame = false );
    void setCurrentFrame( int new_pos );
    int getCurrentFrame() { return this->current_frame; }
    QString getName();
    void setName( QString new_name );

    //Checks if next_depth value of current_frame is thesame of this->max_depth
    bool checkCurFrameDepth();
    void updateFramesDepth();
    int getMinDepth();
    int getMaxDepth();
    int setMinDepth( int depth );
    int setMaxDepth( int depth );

    //void incrementZValues();

private:
    //Returns the previous EmptyKeyFrame or KeyFrame
    //At function end "prev_keyframe_pos" holds the previous key frame pos
    Frame* previousKeyFrame( int pos, int&  prev_keyframe_pos );

    int current_frame;
    QList<Frame*> frames;
    QString name;

    //Min depth this layer can manage
    int min_depth;

    //Max depth this layer can manage
    int max_depth;
};

#endif // TIMELINELAYER_H
