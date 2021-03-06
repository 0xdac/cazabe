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


#include "timelistitem.h"

//! Constructor. Sets m_View to 1.
//
//! \param iParent : the parent of the list item
//! \param \todo : document this
CTimeListItem::CTimeListItem( QTreeWidget* iParent, int iType )
: QTreeWidgetItem( iParent, iType )
{
    m_View = 1;     //By default, the items are not hidden
    setTextAlignment( 0, Qt::AlignLeft );
    setFont( 0, QFont( "Helvetica", 10 ) );


    //Este es el icono de al lado de las capas.
    //QPixmap px = QPixmap( ":/images/logo_32.png" );
    //setIcon(1, QIcon( px.scaled( 15, 15 ) ) );
}
