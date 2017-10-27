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

#include "frame.h"
#include "timelinelayer.h"
#include <typeinfo>

void Frame::setItemsFrameNumber( int pos )
{
    for( int i = 0; i < items.size(); i ++ )
    {
        items.at( i )->setFrameNumber( pos );
    }

}

Frame::Frame( TimelineLayer* parent_layer )
{
    frame_type = EmptyFrame;
    script = new QPlainTextEdit();
    //items = QList<GraphicItem*>();
    this->duration = 0;

    this->parent_layer = parent_layer;
    /*min_depth = 1;
    max_depth = 100;*/
    next_depth = 1;
}

Frame::Frame( FrameType type )
{
    this->frame_type = type;
}

Frame::Frame( Frame* copy )
{
    if( copy )
    {
        this->frame_type = copy->type();
        //include script
        for( int i = 0; i < copy->getItemsCount(); i ++ )
        {
            this->items.append( copy->getItem( i ) );
        }
        this->duration = 0;
    }
}

Frame::~Frame()
{

}

void Frame::addItem( QGraphicsItem* item )
{
    if( item )
    {
        items.append( dynamic_cast<GraphicItem*>( item ) );
        item->setZValue( this->next_depth );

        next_depth ++;
    }
}

void Frame::removeItem( QGraphicsItem* item )
{
    items.removeOne( dynamic_cast<GraphicItem*>( item ) );
}

void Frame::hideItems()
{
    for( int i = 0; i< items.size(); i ++ )
    {
        items.at( i )->hide();
    }
}

void Frame::showItems()
{
    for( int i = 0; i< items.size(); i ++ )
    {
        items.at( i )->show();
    }
}

void Frame::blockItems()
{
    for( int i = 0; i< items.size(); i ++ )
    {
        items.at( i )->setEnabled( false );
    }
}

void Frame::unBlockItems()
{
    for( int i = 0; i< items.size(); i ++ )
    {
        items.at( i )->setEnabled( true );
    }
}

Frame* Frame::clone()
{
    Frame* frame_clone = new Frame( this->frame_type );

    for( int i = 0; i < items.size(); i ++ )
    {
        GraphicItem* temp = items.at( i );
        GraphicItem* clone = temp->clone();        
        frame_clone->addItem( clone );
    }

    return frame_clone;
}

void Frame::setType( FrameType type )
{
    frame_type = type;
}

FrameType Frame::type()
{
    return frame_type;
}

int Frame::getDuration()
{
    return this->duration;
}

void Frame::setDuration( int duration )
{
    this->duration = duration;
}


QTextDocument* Frame::getScript()
{
    return script->document();
}
/*
int Frame::getMinDepth()
{
    return this->min_depth;
}

int Frame::getMaxDepth()
{
    return this->max_depth;
}
*/
int Frame::getNextDepth()
{
    return this->next_depth;
}
/*
int Frame::setMinDepth( int depth )
{
    this->min_depth = depth;
}

int Frame::setMaxDepth( int depth )
{
    this->max_depth = depth;
}
*/
int Frame::setNextDepth( int depth )
{
    this->next_depth = depth;
}

void Frame::updateItemsDepthValues()
{
    //Sort the items by depth
    //qSort( items.begin(), items.end() );

    /* qSort does not work for me, sort this way */
    for( int j = 0; j < items.size() - 1; j ++ )
    {
        for( int k = j + 1; k < items.size(); k ++ )
        {
            if( items.at( k )->zValue() < items.at( j )->zValue() )
            {
                items.swap( j, k );
            }
        }
    }

    //At this point items should be already ordered by depth
    for( int i = 0; i < items.size(); i ++ )
    {
        items.at( i )->setZValue( next_depth );
        this->next_depth ++;
    }
}


