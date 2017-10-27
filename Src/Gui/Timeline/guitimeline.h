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

#ifndef GUITIMELINE_H
#define GUITIMELINE_H

#include <QDockWidget>
#include "../../Core/timeline.h"
#include "../../Core/enumFrameType.h"
#include "timewidget.h"

class GuiTimeline : public QDockWidget
{
    Q_OBJECT
public:
    GuiTimeline( Timeline* timeline);
    QModelIndex getLastIndexClicked();
    void repaintFrames();
    void setTimeline( Timeline* timeline, bool button = false );
    Timeline* coreTimeline();
    void setFrameType( FrameType type );

public slots:
    //When an item is clicked its layer and frame is selected
    void selectLayerAndFrameOfItem( QGraphicsItem* item );

protected:
    void resizeEvent( QResizeEvent * event );

signals:
    void changeScene( int layer, int frame );
    void timelineLostFocus();

private:
    CTimeWidget* timeWidget;
    Timeline* timeline;

};

#endif // GUITIMELINE_H
