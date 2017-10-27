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


#ifndef __TIMETABLEITEM_H__
#define __TIMETABLEITEM_H__

#include <qtablewidget.h>

class CTimeTableItem : public QTableWidgetItem  
{
    public : 
	CTimeTableItem(QTableWidget * iParent);
	//   void paintEvent ( QPaintEvent * p);

    protected :
	bool m_Ready;	//!< This flag is set to 1 if the frame is ready to paint on it
	bool m_Effect;	//!< Has the frame any effect?
	bool m_Effect2;	//!< Has the frame a second effect?
	bool m_Start;	//!< This flag is set to 1 if the frame is the start of a frame row
	bool m_End;	//!< This flag is set to 1 if the frame is the end of a frame row
	bool m_Morphing;//!< Has the frame a "morphing" effect?
	bool m_Choosen;	//!< Is the frame the choosen one?

    public :
	
        CTimeTableItem* Copy();

	//! return the content of m_Ready
	//
	//! \return the content of m_Ready
	inline bool IsReady(void) {return m_Ready; }

	//! Set the ready flag
	//
	//! \param iReady : value to set
	inline void SetReady(bool iReady = true) { m_Ready = iReady; }


	//! Set the start flag
	//
	//! \param iStart : value to set
	inline void SetStart(bool iStart = true) { m_Start = iStart; }

	//! get the start flag
	//
	//! \return start flag
	inline bool IsStart(void) const { return m_Start; }

	//! set the end flag
	//
	//! \param iEnd : flag to be set default true
	inline void SetEnd(bool iEnd = true) { m_End = iEnd; }

	//! Get the end flag
	//
	//! \return end flag
	inline bool IsEnd(void) { return m_End; }

}; // class CTimeTableItem

#endif // __TIMETABLEITEM_H__
