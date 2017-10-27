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

#ifndef __TIMEWIDGET_H__
#define __TIMEWIDGET_H__

#include <QScrollArea>
#include <QPushButton>
#include <QToolButton>
#include <QWidget>
#include <QHeaderView>
#include <QTreeWidget>
#include <QTableWidget>
#include <QLayout>
#include <QToolTip>
#include <QImage>
#include <QPixmap>
#include <QSplitter>
#include <QScrollBar>

#include "timelineruler.h"
#include "timetable.h"
#include "timetableitem.h"
#include "timelist.h"
#include "timevscroll.h"
#include "../../Core/timeline.h"

//! It creates a TimeLine widget, with a layer list and a frame table. The function of this widget is to store and synchronise them.
class CTimeWidget : public QWidget
{
    Q_OBJECT

    public:
        CTimeWidget( Timeline* timeline, QWidget* parent = 0 );
        ~CTimeWidget();

        void resizeEvent ( QResizeEvent* event );
        void resizeTimeWidget( QResizeEvent* event );

	//! select the item iItem in the m_Table
	//
	//! \param iItem : the item to select
        inline void SelectTableRow( int iItem ) { if (m_Table) m_Table->selectRow(iItem); }

	//! Insert a layer in the table
        inline void InsertTableLayer() { if (m_Table) m_Table->InsertLayer(); }

	//! Remove a layer in the table
	//
	//! \param iLayer the layer to remove
	inline void RemoveTableLayer(int iLayer) { if (m_Table) m_Table->RemoveLayer(iLayer); }
	
	//! Swap two rows of the table
	//
	//! \param iRow1 : the fist to swap
	//! \param iRow2 : the second to swap
	inline void SwapTableRows(int iRow1, int iRow2) { if (m_Table) m_Table->SwapRows(iRow1, iRow2); }

	//! Set the table current item
	//
	//! \param iItem : the item to make current
	inline void SetCurrentTableItem(QTableWidgetItem * iItem) { if (m_Table && iItem) m_Table->setCurrentItem(iItem); }

	//! get the current table item
	//
	//! \param iIdx : the index looked for in the row
	//! \return the current table row item
	inline QTableWidgetItem * GetCurrentTableItemAt(int iIdx) const 
	{ 
	    if (m_Table) return m_Table->item(m_Table->currentRow(), iIdx); 
	    else return NULL;
	}
	
	//! get the number of column in the table
	//
	//! \return the number of columns
	int GetTableColumnCount(void) const 
	{ 
	    if (m_Table) return (m_Table->columnCount()); 
	    else return -1;
	}

	//! get the number of rows (aka layers) in the table
	//
	//! \return the number of columns
        int GetTableRowCount() const
	{ 
	    if (m_Table) return (m_Table->rowCount()); 
	    else return -1; 
	}
	

	//! Scroll the table to the specified location
	//
	//! \param iHint : the position hint to scroll to
	//! \param iVal	 : the given value
	
	void ScrollTableToItem(int iVal, QAbstractItemView::ScrollHint iHint) 
	 { if (m_Table) m_Table->scrollToItem(m_Table->item(iVal, 1), iHint); }
	
	//! Scroll the list to the specified location
	//
	//! \param iHint : the position hint to scroll to
	//! \param iVal	 : the given value
	
	void ScrollListToItem(int iVal, QAbstractItemView::ScrollHint iHint) 
	 { if (m_List) m_List->scrollToItem(m_List->topLevelItem(iVal), iHint); }
	
	//! Send a listKeyEvent to the table
	//
	//! \param iEvt : the event to send
	inline void SendTableListKeyEvent(QKeyEvent * iEvt) { if (m_Table && iEvt) m_Table->listKeyEvent(iEvt); }

	//! Set the vertical maximum Scroll
	//
	//! \param iMax : the new maximim vscroll
	inline void SetMaxVScroll(int iMax) { if (m_VertScroll) m_VertScroll->setMaximum(iMax); }
	
	//! Send a mouse event to the ruler
	//
	//! \param iEvt, the event to send
        inline void SendRulerMousePressEvent( QMouseEvent* iEvt )
        {
            if( iEvt && m_Ruler )
               m_Ruler->mousePressEvent( iEvt );
        }

        inline void sendTimeTableMousePressEvent( QMouseEvent * event )
        {
            if( event && m_Table )
                m_Table->mousePressEvent( event );
        }

	//! get the top level item of the list
	//
	//! \param iIdx : the index to look for in the list
	//! \return the toplevel Item
	inline QTreeWidgetItem * GetListTopLevelItem(int iIdx) 
	{ 
	    if (m_List) return m_List->topLevelItem(iIdx); 
	    else return NULL;
	}
	
	//! Select the current item in the list
	//
	//! \param iItem : the item to select
	inline void SetListCurrentItem(QTreeWidgetItem * iItem) { if (iItem && m_List) m_List->setCurrentItem(iItem);}

	//! Send a tableKeyEvent to the list
	//
	//! \param iEvt : the event
	inline void SendListTableKeyEvent(QKeyEvent * iEvt) { if (iEvt && m_List) m_List->keyPressEvent(iEvt); }

        Timeline* coreTimeline()
        {
            return timeline;
        }
        void setTimeline( Timeline* t, bool button )
        {
            if( this->timeline->getLayerCount() > t->getLayerCount() )
            {
                count = this->timeline->getLayerCount() + 1;
            }
            else
            {
                count = t->getLayerCount() + 1;
            }

            this->timeline = t;
            m_List->setCoreTimeline( t );
            m_Table->setCoreTimeline( t, button );
            m_Ruler->button_ruler = button;
            m_Ruler->update();
            //this->repaintFrames();
        }
        void setFrameType( FrameType type )
        {            
            switch( type )
            {
                case KeyFrame:
                    m_Table->insertKeyFrame();
                break;

                case EmptyFrame:
                    m_Table->insertEmptyFrame();
                break;

                case EmptyKeyFrame:
                    m_Table->insertEmptyKeyFrame();
                break;
            }
        }

        void repaintFrames()
        {
            /*for( int j = 0; j < m_Table->rowCount(); j ++ )
            {
                this->RemoveTableLayer( j );
            }*/
            //cout<< "row count " << m_Table->rowCount() << endl;

            int layers_count = timeline->getLayerCount();
            //int count = layers_count + 10;

            for( int j = 0; j < count; j ++ )
            {
                //m_Table->removeRow( j );
                SetListCurrentItem( GetListTopLevelItem( j ) );
                m_List->removeLayer();
            }
            m_Table->setRowCount( 0 );


            //cout<< "layer count " << layers_count << endl;
            //m_Table->updateColors( 0 );
            for( int i = 0; i < layers_count; i ++ )
            {
                m_List->drawLayer( i );
                m_Table->drawLayer( i );
                m_Table->updateColors( i );
                //cout<< "i= "<< i << endl;
            }
            //cout<< "L= "<< timeline->currentLayer()<< "F= "<< timeline->currentFrame()<< endl;
            m_Table->setCurrentCell( 0, 0 );
        }

        void setCurrentFrame( int layer, int frame )
        {
            m_Table->setCurrentCell( layer, frame );
        }

    signals:
        void changeScene( int layer, int frame );
	
    protected:
	
	QWidget      * m_Layout;		//!< This Widget stores m_Table and m_Ruler, because they need to be synchronised
	QScrollArea  * m_ScrollArea;	//!< This QScrollArea stores m_layout, so the user can scroll to see all the frames
	CTimeList    * m_List;		//!< The layer list next to the m_Table. You can do some basic functions with layers with it.
	CTimeTable   * m_Table;		//!< The table which handles all the frames. Each row represents a layer and each column represents a frame in the timeline.
        TimeLineRuler   * m_Ruler;		//!< The ruler inside the m_Layout, to move around the timeline
	CTimeVScroll * m_VertScroll;  //!< This scrollbar can move the view of the list and the table, to make easier to move around the layer. It is also used to synchronise the list and the table

	QPushButton  * m_AddButton;	//!< This button adds a new layer
	QPushButton  * m_RemButton;	//!< This button removes the selected layer
	QPushButton  * m_UpButton;	//!< This button moves the current layer up
	QPushButton  * m_DownButton;	//!< This button moves the current layer down

        int m_Frames;			//!< The number of frames
        Timeline* timeline;
        int count;
};

#endif  //__TIMEWIDGET_H__
