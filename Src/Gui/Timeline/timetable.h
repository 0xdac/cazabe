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


#ifndef __TIMETABLE_H__
#define __TIMETABLE_H__

#include <qwidget.h>
#include <qtablewidget.h>
#include <qscrollbar.h>
//Added by qt3to4:
#include <QMouseEvent>
#include <QPaintEvent>
#include <QHeaderView>
#include "../../Core/timeline.h"
#include "../../Core/enumFrameType.h"
#include "../../Core/frame.h"

//! This class creates a table where each cell represents a frame. Upper layers are the upper rows, and the left columns are the first frames in timeline. It should be only created by CTimeWidget
class CTimeTable : public QTableWidget 
{
    Q_OBJECT


    public:
	CTimeTable(int iNumR, int iNumC, QWidget *iParent = 0);
        inline void setCoreTimeline( Timeline* tl, bool button )
        {
             int fixed_number;
             if( button )
                 fixed_number = 50;
             else
                 fixed_number = 8;

            core_timeline = tl;
            for( int i = 0; i < columnCount(); i++ )
                horizontalHeader()->resizeSection( i, fixed_number );
            updateColors( 0 );
        }

	// overloaded methods
	virtual void keyPressEvent ( QKeyEvent * );
	virtual void listKeyEvent ( QKeyEvent * );
        virtual void mousePressEvent( QMouseEvent* iEvt);

    public slots:
        void insertEmptyKeyFrame( int num_layer = -1, int framepos = -1 );
        void insertKeyFrame( int num_layer = -1, int framepos = -1 );
        void insertEmptyFrame( int num_layer = -1, int framepos = -1 );
        void removeFrame(int num_layer = -1, int framepos = -1);
	void SlotClearFrame(int iLayer = -1, int iFrame = -1);
        void SlotCopyFrame();
        void SlotCutFrame();
        void SlotPasteFrame();
        void SlotAddAS();

    signals:
        void changeScene( int layer, int frame );

    public :
        int GetFrameCount() const;

	void InsertLayer(int iInitialPosition = 0);
	void RemoveLayer(int iLayer);
        void ClearLayer();
	bool HasAnyFrameBefore(int iLayer, int iFrame) const;
	bool HasAnyFrameAfter(int iLayer, int iFrame) const;
	void SwapRows(int iRow1, int iRow2);
        void updateColors(int iRow);
        void drawLayer( int pos );

    protected:
	virtual void mouseMoveEvent(QMouseEvent * iEvt);
	
	void _CreateActions(void);

	int m_ClipboardCol;        //!< When you copy or cut a frame, its column number will be kept here until you paste it, or copy or cut another frame.
	int m_ClipboardRow;     //!< When you copy or cut a frame, its row number will be kept here until you paste it, or copy or cut another frame.

	bool m_Cut; 		//!< This boolean indicates if you have copied (0) or cut (1) the cell in (m_ClipboadRow, m_clipboardCol). It is useful in Sl otPasteFrame().


        QAction* m_InsertKeyAct;  //! Inserts a new key frame
        QAction* m_InsertEmptyFrameAct;    //! Inserts a new frame if possible
        QAction* m_InsertEmptyKeyFrameAct;
        QAction* m_RemoveAct;    //! Removes the selected frame
        QAction* m_ClearAct;     //! Clears the current frame (removes all the items in it)
        QAction* m_CutAct;       //! Stores the column and row number of the selected frame in m_ClipboadRow, m_clipboardCol, so it will be ready to be pasted
        QAction* m_CopyAct;      //! Stores the column and row number of the selected frame in m_ClipboadRow, m_clipboardCol, so it will be ready to be pasted
        QAction* m_PasteAct;     //! Pastes the frame stored in m_ClipboadRow, m_clipboardCol
        QAction* m_ASAct;        //! Launches the ActionScript dialog to directly edit the AS in the current frame

        Timeline* core_timeline;


}; // class CTimeTable

#endif // __TIMETABLE_H__
