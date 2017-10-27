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

#include "timelinelayer.h"

TimelineLayer::TimelineLayer()
{
    current_frame = 0;
    frames = QList<Frame*>();
    name = "";
    this->min_depth = 0;
    this->max_depth = 100;
}

void TimelineLayer::hide()
{
    for( int i = 0; i< frames.size(); i ++ )
    {
        frames.at( i )->hideItems();
    }
}

void TimelineLayer::show()
{
    for( int i = 0; i< frames.size(); i ++ )
    {
        frames.at( i )->showItems();
    }
}

void TimelineLayer::block()
{
    for( int i = 0; i< frames.size(); i ++ )
    {
        frames.at( i )->blockItems();
    }
}

void TimelineLayer::unBlock()
{
    for( int i = 0; i< frames.size(); i ++ )
    {
        frames.at( i )->unBlockItems();
    }
}
//-------------------------------------------------------------------------------------------
int TimelineLayer::getFramesCount()
{
    return frames.size();
}

//-------------------------------------------------------------------------------------------
bool TimelineLayer::checkCurFrameDepth()
{
    Frame* f = frames.at( this->current_frame );
    if( f )
    {
        if( f->getNextDepth() == this->max_depth )
        {
            //this->max_depth must be set to a higher value
            this->max_depth += 50;
            return true;
        }
    }

    return false;
}

//-------------------------------------------------------------------------------------------
void TimelineLayer::updateFramesDepth()
{
    Frame* f = 0;

    for( int i = 0; i< frames.size(); i ++ )
    {
        f = frames.at( i );
        f->setNextDepth( this->min_depth );
        f->updateItemsDepthValues();
    }
}

//-------------------------------------------------------------------------------------------
int TimelineLayer::getMinDepth()
{
    return this->min_depth;
}

//-------------------------------------------------------------------------------------------
int TimelineLayer::getMaxDepth()
{
    return this->max_depth;
}

int TimelineLayer::setMinDepth( int depth )
{
    this->min_depth = depth;
}

int TimelineLayer::setMaxDepth( int depth )
{
    this->max_depth = depth;
}

//-------------------------------------------------------------------------------------------
Frame* TimelineLayer::previousKeyFrame( int pos, int&  prev_keyframe_pos )
{
    Frame* frame = 0;
    Frame* prev_frame = 0;
	
    for( int i = pos - 1; i >= 0; i -- )
    {
        frame = frames.at( i );                                                 
        if( frame->type() == KeyFrame || frame->type() == EmptyKeyFrame )
        {
            prev_frame = frame;
            prev_keyframe_pos = i;
            i = -1;
        }
    }	
    return prev_frame;
}

void TimelineLayer::setFrameType( FrameType type, int frame )
{
  Frame* f = 0;

  if( frame >= 0 )
  {
      if( frame >= frames.size() )
      {
        for( int i = frames.size(); i<= frame; i ++ )
        {
            //Frame constructor creates an empty frame by default
            Frame* emptyFrame = new Frame();
            frames.append( emptyFrame );
        }
      }

      f = frames.at( frame );
      f->setType( type );
      int prev_keyframe_pos = -1;
      Frame* prev_frame = previousKeyFrame( frame, prev_keyframe_pos );
      if( prev_frame != 0 )
      {
        int duration = ( frame - prev_keyframe_pos ) - 1;
        prev_frame->setDuration( duration );
      }
      if( type == KeyFrame )
      {
           Frame* current = frames.at( frame );
           if( current && prev_frame )
           {
               delete current;
               current = new Frame( prev_frame->clone() );               
               //Bug fix
               frames.at( frame )->setType( type );
               frames.at( frame )->setItemsFrameNumber( frame );
           }
      }
  }    
}

Frame* TimelineLayer::getFrame( int frame, bool prevKeyFrame )
{
    Frame* f = 0;
    //Just for "previousKeyFrame" function sintax
    int nothing;

    if( frame >= 0 && frame < frames.size() )
    {
        f = frames.at( frame );

        if( prevKeyFrame && f->type() == EmptyFrame )
            f = previousKeyFrame( frame, nothing );
    }

    return f;
}

void TimelineLayer::addItem( QGraphicsItem* item )
{
    Frame* cur_frame = 0;

    if( frames.size() > current_frame )
    {
        cur_frame = frames.at( current_frame );
    }

    if( item && cur_frame )
    {
        (dynamic_cast<GraphicItem*>( item ))->setFrameNumber( this->current_frame );
        cur_frame->addItem( item );
    }
}

void TimelineLayer::removeItem( QGraphicsItem* item )
{
    frames.at( current_frame )->removeItem( item );
}

void TimelineLayer::setCurrentFrame( int new_pos )
{
    if( new_pos >= 0 )
    {
        current_frame = new_pos;
    }
}

QString TimelineLayer::getName()
{
    return this->name;
}

void TimelineLayer::setName( QString new_name )
{
    this->name = new_name;
}
