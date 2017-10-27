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

#ifndef FRAME_H
#define FRAME_H
#include <QPlainTextEdit>
#include "cloneable.h"
#include "scene.h"
#include "enumMode.h"
#include "enumFrameType.h"

class TimelineLayer;

class Frame : public Cloneable
{
public:    
    Frame( TimelineLayer* parent_layer = 0 );
    Frame( FrameType type );//TODO Clone QPlainTextEdit
    Frame( Frame* copy );
    ~Frame();
    void addItem( QGraphicsItem* item );
    void removeItem( QGraphicsItem* item );
    void removeAllItems() { items.clear(); }
    void hideItems();
    void showItems();
    void blockItems();
    void unBlockItems();
    void setType( FrameType type );
    FrameType type();
    void setDuration( int duration );
    int getDuration();
    QTextDocument* getScript();
    GraphicItem* getItem( int pos ) { return this->items.at( pos ); }
    int getItemsCount() { return this->items.size(); }

    //int getMinDepth();
    //int getMaxDepth();
    int getNextDepth();    
    //int setMinDepth( int depth );
    //int setMaxDepth( int depth );
    int setNextDepth( int depth );
    void setItemsFrameNumber( int pos );

    /*
      When next_depth is equal to max_depth this function changes old depth values
      for new depth values and update items depth values for new ones between new_min_depth
      and new_max_depth param values
     */
    void updateItemsDepthValues();

    Frame* clone();
    
private:
    //How many empty frames follows this frame if it is KeyFrame or EmptyKeyFrame
    int duration;

    FrameType frame_type;
    QPlainTextEdit* script;

    //Items this frame holds
    QList<GraphicItem*> items;

            /* For layers support */
    TimelineLayer* parent_layer;

    //Min depth this frame can manage
    /*int min_depth;

    //Max depth this frame can manage
    int max_depth;*/

    //This is the depth of next item
    int next_depth;

};

#endif // FRAME_H
