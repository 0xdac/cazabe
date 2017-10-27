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

#include "guitimeline.h"
#include <QTableView>
#include <QStandardItemModel>
#include <QListWidget>
#include <QHBoxLayout>
#include <QToolButton>

GuiTimeline::GuiTimeline( Timeline* tl )
{
    setWindowTitle( tr( "Timeline" ) );
    setAllowedAreas( Qt::TopDockWidgetArea );

    timeWidget = new CTimeWidget( tl );
    setWidget( timeWidget );
    timeline = tl;

    connect( timeWidget, SIGNAL( changeScene( int, int ) ), this, SIGNAL( changeScene( int, int ) ) );
}

void GuiTimeline::setTimeline( Timeline* timeline, bool button )
{
    timeWidget->setTimeline( timeline, button );
}

Timeline* GuiTimeline::coreTimeline()
{
    return timeline;
}

void GuiTimeline::setFrameType( FrameType type )
{
    timeWidget->setFrameType( type );
}

void GuiTimeline::resizeEvent ( QResizeEvent* event )
{
    timeWidget->resizeTimeWidget( event );

    //Default
    QDockWidget::resizeEvent( event );
}

QModelIndex GuiTimeline::getLastIndexClicked()
{

}

void GuiTimeline::repaintFrames()
{
    timeWidget->repaintFrames();
}

void GuiTimeline::selectLayerAndFrameOfItem( QGraphicsItem* item )
{
    GraphicItem* selected_item = dynamic_cast<GraphicItem*>( item );
    timeWidget->SetListCurrentItem( timeWidget->GetListTopLevelItem( selected_item->getLayerNumber() ) );
    timeWidget->setCurrentFrame( selected_item->getLayerNumber(), selected_item->getFrameNumber() );
}


