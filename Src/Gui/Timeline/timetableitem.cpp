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


#include "timetableitem.h"
#include <qpainter.h>


//! Constructor. All flags are set to 0 by default. It also initializes some Qt::ItemFlag properties.
//
//! \param iParent : Parent widget, should be CTimeTable object.
CTimeTableItem::CTimeTableItem(QTableWidget * iParent)
:QTableWidgetItem(1)
{
    //By default all the flags are 0
    m_Ready = m_Effect = m_Effect2 = m_Start = m_End = m_Morphing = m_Choosen = 0;

    //it sets some flags with the properties of the item
    QFlags<Qt::ItemFlag> f = Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsTristate;
    setFlags(f);

}


//! It copies CTimeTableItem and returns a new item with the same flags and properties.
//! \return : A new item with the same properties is returned.
CTimeTableItem* CTimeTableItem::Copy()
{

    //Each property is copied to a new item and returned

    CTimeTableItem* newItem = new CTimeTableItem( tableWidget() );
    newItem->m_Ready = m_Ready;
    newItem->m_Effect = m_Effect;
    newItem->m_Effect2 = m_Effect2;
    newItem->m_Start = m_Start;
    newItem->m_End = m_End;
    newItem->m_Morphing = m_Morphing;
    newItem->m_Choosen = m_Choosen;
    newItem->setBackgroundColor( backgroundColor() );

    return newItem;
}

