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

#ifndef TIMELINE_H
#define TIMELINE_H
#include <QList>
#include <typeinfo>
#include "timelinelayer.h"
#include "frame.h"
#include "cloneable.h"
#include "enumFrameType.h"

class Timeline : public QObject, Cloneable
{
    Q_OBJECT

public:
    Timeline();
    ~Timeline();  

    void addLayer();

    //Remove the current layer specified by current_layer member variable
    void removeLayer();

    void clearLayersList() { layers.clear(); }
    void addLayer( TimelineLayer* new_layer );
    TimelineLayer* getLayer( int layer );
    void setCurrentLayer( int new_pos );
    int currentLayer() { return this->current_layer; }
    int currentFrame() { return layers.at( current_layer )->getCurrentFrame(); }
    int getLayerCount() { return this->layers.size(); }
    void hideCurrentLayer();
    void showCurrentLayer();
    void blockCurrentLayer();
    void unBlockCurrentLayer();
    void moveLayerUp( int layer_number );
    void moveLayerDown( int layer_number );

    QList<QGraphicsItem*> getItemsAt( int column );

    Frame* getFrame( int layer, int frame, bool prevKeyFrame = false );
    void setFrameType( FrameType type, int layer, int frame );
    void setFrameScript( char* code, int layer, int frame );
    void deleteFrame( int framepos );

    bool createKeyFrameNeeded()
    {
        TimelineLayer* cur_layer = 0;

        if( layers.size() > current_layer )
        {
            cur_layer = layers.at( current_layer );
            if( cur_layer )
            {
                if( !cur_layer->getFrame( cur_layer->getCurrentFrame() ) )
                {
                    return true;
                }
                else if( cur_layer->getFrame( cur_layer->getCurrentFrame() )->type() != KeyFrame )
                {
                    return true;
                }
            }
        }
        return false;
    }

    //Scene* getScene( int pos );
    //Scene* justGetScene( int pos );

    Timeline* clone();

    void updateAllDepth();
    //Keeps items inside its layer
    void manageItemsDepthByColumn( int frame_pos );

public slots:
    void addItemToCurrentFrame( QGraphicsItem* item );
    void removeItemFromCurrentFrame( QGraphicsItem* item );

private:
    //Swap item's depth of two layers
    void swapLayersDepth( int layer1, int layer2 );

    //void incScenesSize( int pos );
    QList<TimelineLayer*> layers;
    //QList<Scene*> scenes;
    int current_layer;
    //
    //int depth_inc;
};

#endif // TIMELINE_H
