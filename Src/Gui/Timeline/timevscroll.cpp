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

#include "timevscroll.h"
#include "timewidget.h" 


//! \param iMinValue : The minimum value the scrollBar can have
//! \param iMaxValue : The maximum value the scrollBar can have
CTimeVScroll::CTimeVScroll(int iMinValue, int iMaxValue, QWidget * iParent)
    : QScrollBar(Qt::Vertical, iParent)
{
    setMinimum(iMinValue);
    setMaximum(iMaxValue); 
    show();
    connect( this, SIGNAL(valueChanged(int)), this, SLOT(SlotUpdateListAndTable()));
}

//! [slot] It updates list and table view, when the ScrollBar position is changed.
void CTimeVScroll::SlotUpdateListAndTable (void)
{

    //When the scrollBar valued is Change, list and table should also change

    ((CTimeWidget* )parent())->ScrollTableToItem(value(), QAbstractItemView::PositionAtBottom);
    ((CTimeWidget* )parent())->ScrollListToItem(value(), QAbstractItemView::PositionAtBottom);

}




