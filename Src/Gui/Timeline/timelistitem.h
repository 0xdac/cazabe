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

#ifndef __TIMELISTITEM_H__
#define __TIMELISTITEM_H__

#include <QTreeWidgetItem>


//! This class represents a layer in QTimeList. The layer properties should be here.
class CTimeListItem : public QTreeWidgetItem  
{
    public: 
	CTimeListItem(QTreeWidget * iParent, int);
	
	//! return m_View
	//
	//! \return m_View
	inline int GetView(void) const {return m_View; }

	//! set the value of m_View
	//
	//! \param iView : the value to set
	inline void SetView(int iView) { m_View = iView; }

    protected:	
	
	int m_View;	//!< m_View will be 1 by default. If the items on this layer are hidden, it will be 0

	

}; // class CTimeListItem

#endif // __TIMELISTITEM_H__
