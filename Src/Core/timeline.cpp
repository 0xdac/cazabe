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

#include "timeline.h"
#include <QMessageBox>

Timeline::Timeline()
{
  layers = QList<TimelineLayer*>();
  layers.append( new TimelineLayer() );
  //scenes = QList<Scene*>();
  this->current_layer = 0;
  //this->depth_inc = 50;
}

/*void Timeline::incScenesSize( int pos )
{
    if( pos >= scenes.size() )
    {
        for( int i = scenes.size(); i <= pos; i ++ )
        {
            scenes.append( 0 );
        }
    }
}*/

Timeline::~Timeline() 
{

}

void Timeline::addLayer()
{
    TimelineLayer* new_layer = new TimelineLayer();
    //new_layer->min_depth set to zero in TimelineLayer constructor
    //new_layer->max_depth set to 100 in TimelineLayer constructor
    layers.append( new_layer );
    this->updateAllDepth();
}

//Remove the current layer specified by current_layer member variable
void Timeline::removeLayer()
{
    layers.removeAt( this->current_layer );
    //TODO
    //this->updateAllDepth();
}

void Timeline::addLayer( TimelineLayer* new_layer )
{
    layers.append( new_layer );
}

TimelineLayer* Timeline::getLayer( int layer )
{
    return layers.at( layer );
}

void Timeline::setCurrentLayer( int new_pos )
{
    if( new_pos >= 0 )
    {
        current_layer = new_pos;
    }
}

void Timeline::hideCurrentLayer()
{
    layers.at( current_layer )->hide();
}

void Timeline::showCurrentLayer()
{
    layers.at( current_layer )->show();
}

void Timeline::blockCurrentLayer()
{
    layers.at( current_layer )->block();
}

void Timeline::unBlockCurrentLayer()
{
    layers.at( current_layer )->unBlock();
}

void Timeline::swapLayersDepth( int layer1, int layer2 )
{
    //TimelineLayer* l1 = layers.at( layer1 );
    //TimelineLayer* l2 = layers.at( layer2 );
    //TODO
}

void Timeline::moveLayerUp( int layer_number )
{
    /*if( layer_number > 0 )  //Move up layer_number = 0 don't have sense
    {
        layers.swap( layer_number, layer_number - 1 );
        //this->manageItemsDepth( layer, frame );
    }*/
    //TODO
}

void Timeline::moveLayerDown( int layer_number )
{

}

void Timeline::setFrameType( FrameType type, int layer, int frame_pos )
{
    /*incScenesSize( frame_pos );

    if( !scenes.at( frame_pos ) )
    {
        Scene* s = new Scene();
        connect( s, SIGNAL( itemInserted(QGraphicsItem*) ), this, SLOT( addItemToCurrentFrame(QGraphicsItem*) ) );
        connect( s, SIGNAL( itemRemoved(QGraphicsItem*) ), this, SLOT( removeItemFromCurrentFrame(QGraphicsItem*) ) );
        scenes.insert( frame_pos, s );
    }*/

    layers.at( layer )->setFrameType( type, frame_pos );

    /*if( type == KeyFrame )      //Only key frames contains items
    {
        this->manageItemsDepthByColumn( frame_pos );
    }*/

    /*if( type == KeyFrame )
    {
        Scene* corresponding_scene = scenes.at( frame_pos );        
        corresponding_scene->clear();
        Frame* just_changed = layers.at( layer )->getFrame( frame_pos );
        for( int i = 0; i < just_changed->getItemsCount(); i ++ )
        {
            corresponding_scene->addItem( just_changed->getItem( i ) );
        }
    }*/
}

Frame* Timeline::getFrame( int layer, int frame, bool prevKeyFrame )
{
    return layers.at( layer )->getFrame( frame, prevKeyFrame );
}

void Timeline::setFrameScript( char* code, int layer, int frame )
{

}

void Timeline::deleteFrame( int framepos )
{
//TODO
}

/*Scene* Timeline::getScene( int pos )
{
    Scene* s = 0;
    if( pos >= 0 && pos < scenes.size() )
    {
        for( int i = pos; i >= 0; i -- )
        {
            if( scenes.at( i ) != 0 )
            {
                s = scenes.at( i );
                i = -1;
            }
        }
    }

    return s;
}*/
/*
Scene* Timeline::justGetScene( int pos )
{
    return scenes.at( pos );
}*/

Timeline* Timeline::clone()
{
    //return new Timeline( frames );
}

void Timeline::updateAllDepth()
{
    TimelineLayer* layer = 0;
    int min_depth = 0;
    int max_depth = 100;

    if( !layers.empty() )
    {
        max_depth = layers.at( 0 )->getMaxDepth();
    }

    for( int i = layers.size() - 1; i >= 0; i -- )
    {
        layer = layers.at( i );
        layer->setMinDepth( min_depth );
        layer->setMaxDepth( max_depth );
        layer->updateFramesDepth();
        min_depth += layer->getMaxDepth() + 1;
        max_depth += layer->getMaxDepth();
    }
}

void Timeline::manageItemsDepthByColumn( int frame_pos )
{
                /* Necessary to keep items inside its layer */

    if( layers.size() > 1 )     //If we have only one layer this is unnecessary
    {
        Frame* current_frame = 0;//layers.at( layer_pos )->getFrame( frame_pos );
        //Frame* temp_frame = 0;
        //Frame* prev_frame = 0;
        int min_depth = 1;
        int max_depth = 100;

        /*
            Down-top search looking for the others key frames in column "frame_pos"
         */
        for( int i = layers.size() - 1; i >= 0; i -- )
        {
            current_frame = layers.at( i )->getFrame( frame_pos );

            //If current_frame is a valid pointer and a KeyFrame
            if( current_frame && current_frame->type() == KeyFrame )
            {
                //Sets the items depths current_frame can manage now
                //current_frame->setMinDepth( min_depth );
                current_frame->setNextDepth( min_depth );
                //current_frame->setMaxDepth( max_depth );

                //Keep the same items stack order but with new depth values
                current_frame->updateItemsDepthValues();

                min_depth += 100;
                max_depth = min_depth + 99;
            }
        }
    }
}

//Slots
void Timeline::addItemToCurrentFrame( QGraphicsItem* item )
{
    TimelineLayer* cur_layer = 0;    

    if( layers.size() > current_layer )
    {
        cur_layer = layers.at( current_layer );
    }

    if( item && cur_layer )
    {
        (dynamic_cast<GraphicItem*>( item ))->setLayerNumber( this->current_layer );

        /*if( !cur_layer->getFrame( cur_layer->getCurrentFrame() ) )
        {
            cur_layer->setFrameType( KeyFrame, cur_layer->getCurrentFrame() );
        }*/

        if( cur_layer->checkCurFrameDepth() )
        {
            this->updateAllDepth();            
        }
        cur_layer->addItem( item );
    }
}

void Timeline::removeItemFromCurrentFrame( QGraphicsItem* item )
{
    layers.at( current_layer )->removeItem( item );
}

QList<QGraphicsItem*> Timeline::getItemsAt( int column )
{
    //To add all the items in a column of frames, i.e. items to show in the scene
    QList<QGraphicsItem*> all_items;

    int layers_count = layers.size();
    Frame* frame = 0;                   //Temp Frame pointer
    GraphicItem* item = 0;              //Temp GraphicItem pointer

    for( int i = 0; i < layers_count; i ++ )
    {
         /* The "true" param shows items of the previous key frame
            when "column" is the pos of an EmptyFrame
          */
         frame = layers.at( i )->getFrame( column, true );

         if( frame )
         {
             for( int j = 0; j < frame->getItemsCount(); j ++ )
             {
                 item = frame->getItem( j );
                 if( item )
                 {
                    all_items.append( item );
                 }
             }
         }
    }

    return all_items;
}



