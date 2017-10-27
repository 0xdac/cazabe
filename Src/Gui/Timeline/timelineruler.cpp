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


#include "timelineruler.h"
#include "timewidget.h"
#include "timetableitem.h"
#include <qpainter.h>
#include <qsize.h>
#include <qpixmap.h>

//Added by qt3to4:
#include <QMouseEvent>
#include <QPaintEvent>


//! This class creates a ruler to move around the frames
//
//! \param framesNumber : It should be used to set the initial value of frames, but this value is get with GetFrames(), and depends on the table.
TimeLineRuler::TimeLineRuler ( int framesNumber, QWidget* iParent )
   : QWidget ( iParent )
{
    currentFrame = 0;
    this->button_ruler = false;
} 

//! Paint the TimeLineRuler in the widget.
void TimeLineRuler::paintEvent( QPaintEvent* iEvt)
{
    if( !iEvt )
        return;

    int number = 8;
    if( button_ruler )
        number = 50;
    else
        number = 8;
    bool flag = true;

    QPainter p ( this );

    //What kind of font do we want for the frame number on the ruler?
    p.setPen( Qt::black );
    QFont f( "Courier", 9, QFont::Normal );
    p.setFont( f );

    //This paints the black lines on every frame on the ruler. Besides, in 1 of each 5 it paints a text with the frame number
    int j, i;
    for( i = 1, j = 1; i < GetFrames() * number; i = i + number , j ++ )
    {
        p.drawLine( i, 0, i, 2 );
        p.drawLine( i, height(), i, height() - 2 );

        if( button_ruler )
        {
            if( flag )
            {
                p.setPen( Qt::black );
                p.drawText( 17, height() - 5, tr( "Up" ) );
                p.drawText( 60, height() - 5, tr( "Over" ) );
                p.drawText( 110, height() - 5, tr( "Down" ) );
                p.drawText( 162, height() - 5, tr( "Hit" ) );
                flag = false;
            }
        }
        else
        {
         if( !( j % 5 ) )
         {
            p.setPen( Qt::black );
            p.drawText( i, height() - 5, QString::number( j ) );
         }
        }
    }

    //A red rectangle is painted in the current frame:

    QBrush brush( QColor( "red" ), Qt::SolidPattern );
    p.fillRect( ( currentFrame ) * number + 1, 0, number, height(), brush );
    p.setPen( QColor( 204, 0, 0 ) );
    p.drawRect( ( currentFrame ) * number + 1, 0, number, height() );
}

//! Updates currentFrame and frame table with new press event.
void TimeLineRuler::mousePressEvent( QMouseEvent* e )
{

    CTimeWidget* time = (CTimeWidget*) parentWidget()->parentWidget()->parentWidget()->parentWidget();

    int number = 8;
    if( button_ruler )
        number = 50;
    else
        number = 8;

    //When the ruler is pressed, the currentFrame is updated
    int i;
    i= (e->pos()).x();
    currentFrame = i / number;

    update();

    //The currentFrame needs to be the same in the frame table
    time->SetCurrentTableItem( time->GetCurrentTableItemAt( currentFrame ) );

    emit changeScene( 0, currentFrame );//ver el parametro 0
}

//! Updates currentFrame with new move event and calls TimeLineRuler::mousePressEvent.
void TimeLineRuler::mouseMoveEvent( QMouseEvent* iEvt )
{
  if(!iEvt)
      return;

  int i = ( iEvt->pos() ).x();
  int j = ( iEvt->pos() ).y();

    //if the pointer is IN the TimeLineRuler area, it does the same as if you had clicked it
    if( !(i>width()) && !(i<0) &&  !(j>height()) && !(j<0) )
    {
        CTimeWidget* time = (CTimeWidget*) parentWidget()->parentWidget()->parentWidget()->parentWidget();
        this->mousePressEvent( iEvt );
        time->sendTimeTableMousePressEvent( iEvt );
    }

    
    //update();
}
 

//! Counts the frames that need to be drawn.  \todo useless?
//
//! \return : The number of frames.
int TimeLineRuler::GetFrames() const
{
    //It gets the number of columns in the table, that MUST be the same number of frames.
    CTimeWidget* timeW = (CTimeWidget*) parentWidget()->parentWidget()->parentWidget()->parentWidget();
    return timeW->GetTableColumnCount();
}

//! Counts the layers. \todo useless?
//
//! \return : The number of layers.
int TimeLineRuler::GetLayers() const
{
    //It gets the number of rows in the table, that MUST be the same number of frames.
   CTimeWidget* timeW = (CTimeWidget*) parentWidget()->parentWidget()->parentWidget()->parentWidget();
   return timeW->GetTableRowCount();
}


