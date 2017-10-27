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

#include "timewidget.h"



//! Constructor. All it's members are initialized and slots and signals are connected.
//
//! \param iParent : Parent widget. Should be ...
CTimeWidget::CTimeWidget( Timeline* tl, QWidget * iParent )
    : QWidget( iParent )
{
   const int m_Frames = 800;  //How many frames do we need?

   int width = m_Frames * 8;  //Width for table and ruler, is 8 times the number of frames, but at least 1200.
   if ( width < 1200 )
       width = 1200;
   
   m_List = new CTimeList( this );  //Creates the layer list //
   m_List->setFixedWidth( 190 );
   m_List->setCoreTimeline( tl );
   
   m_Layout = new QWidget;  //Creates the layout to put the ruler and the table
   m_Layout->setGeometry( 0, 0, width, 200 );


   m_Ruler = new TimeLineRuler( m_Frames, m_Layout );  //Creates the ruler inside the layout
   m_Ruler->setGeometry( 0, 0, width, 25 ); //25 defines the height of the ruler

   m_Table = new CTimeTable( 1, m_Frames, m_Layout );  //Creates the table inside the layout
   m_Table->setGeometry( 0, 25, width, 200 );
   m_Table->setCoreTimeline( tl, false );
   this->timeline = tl;
   
   m_ScrollArea = new QScrollArea( this );  //Creates the scrollarea to store the m_layout//

   m_ScrollArea->setWidget( m_Layout );  //Puts the layout inside the scrollarea

   QToolButton* addLayer = new QToolButton( this );
   addLayer->setIcon( QIcon( ":/images/addlayer.png" ) );
   addLayer->setFixedSize( 23, 23 );
   addLayer->setToolTip( tr( "Insert layer" ) );

   QToolButton* removeLayer = new QToolButton( this );
   removeLayer->setIcon( QIcon( ":/images/removelayer.png" ) );
   removeLayer->setFixedSize( 23, 23 );
   removeLayer->setToolTip( tr( "Remove layer" ) );

   QHBoxLayout* layout = new QHBoxLayout;

   QHBoxLayout* buttonsLayout = new QHBoxLayout;
   buttonsLayout->addSpacing( 135 );
   buttonsLayout->addWidget( addLayer );
   buttonsLayout->addWidget( removeLayer );   

   QVBoxLayout* layersLayout = new QVBoxLayout;
   layersLayout->addWidget( m_List );
   layersLayout->addLayout( buttonsLayout );
   
   layout->addLayout( layersLayout );
   layout->addWidget( m_ScrollArea );

   setLayout( layout );
   
   connect( addLayer, SIGNAL( clicked()), m_List, SLOT( SlotInsertLayer() ) );
   connect( removeLayer, SIGNAL( clicked()), m_List, SLOT( SlotRemoveLayer() ) );

   connect( m_Table, SIGNAL( changeScene( int, int ) ), this, SIGNAL( changeScene( int, int ) ) );
   connect( m_Ruler, SIGNAL( changeScene( int, int ) ), this, SIGNAL( changeScene( int, int ) ) );
}

CTimeWidget::~CTimeWidget()
{
}

//! Resizes and moves objects depending on the new size.
//
//! \param iEvent : Provides info about resize event.
void CTimeWidget::resizeEvent ( QResizeEvent* iEvent )
{

}

void CTimeWidget::resizeTimeWidget( QResizeEvent* iEvent )
{
    //- 60: this value keeps the vertical scrollbar of the timewidget hidden
    m_Layout->setFixedHeight( iEvent->size().height() - 60 );
    m_Table->setFixedHeight( iEvent->size().height() - 60 );
}

