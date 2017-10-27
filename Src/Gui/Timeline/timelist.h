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


#ifndef __TIMELIST_H__
#define __TIMELIST_H__

#include "../../Core/timeline.h"
#include <QTreeWidget>
#include <QCheckBox>
#include "timelistitem.h"
#include <QMouseEvent>
#include <QPaintEvent>

//! Creates a list with the layers, where you can do some basic functions with them (add, remove, move up, move down, hide...). ONLY CTimeWidget class should create it.
class CTimeList: public QTreeWidget
{
    Q_OBJECT

    public:	
	CTimeList( QWidget * iParent = 0);
        void setCoreTimeline( Timeline* tl );

	virtual void keyPressEvent ( QKeyEvent * iEvt );  //!<This function uses the QKeyEvent and sends it to the parent (CTimeWidget) so the same QKeyEvent will be used in the table. When you select a layer, the same layer is selected in the table and viceversa.
	virtual void tableKeyEvent ( QKeyEvent * iEvt );  //!<When the QKeyEvent in the table is send to synchronise with the list

        void removeLayer()
        {
            //Removes the current item on the list and updates layerCount
            delete currentItem();
            int layerCount = topLevelItemCount();
            //Updates the scrollBar max value
            int max = 0;
        }

        void drawLayer( int m )
        {
            //Adds a new list item

            CTimeListItem* newItem = new CTimeListItem( this, CTimeListItem::UserType );
            newItem->setText( 0, tr( "layer" ) + " " + QString::number( m ) );

            QCheckBox* view = new QCheckBox();
            view->setChecked( true );
            view->setToolTip( tr( "Show or hide layer" ) );
            connect( view, SIGNAL( clicked(bool) ), this, SLOT( hideShowLayer(bool) ) );

            QCheckBox* block = new QCheckBox();
            block->setToolTip( tr( "Block or unblock layer" ) );
            connect( block, SIGNAL( clicked(bool) ), this, SLOT( blockUnBlockLayer(bool) ) );

            setItemWidget( newItem, 1, view );
            view->setChecked( true );
            setItemWidget( newItem, 2, block );
        }

    public slots:
        void SlotInsertLayer();
        void SlotRemoveLayer();
        void SlotClearLayer();
        void SlotCopyLayer();
        void SlotCutLayer();
        void SlotPasteLayer();
        void SlotMoveUp();
        void SlotMoveDown();
        void hideShowLayer( bool checked );
        void blockUnBlockLayer( bool block );
        void SlotOnionSkinLayer();
        void SlotChangeName();

    protected:
	// At overloaded events
	virtual void mouseMoveEvent( QMouseEvent * );
	virtual void mousePressEvent( QMouseEvent * );


	QAction* m_InsertAct;		//!<It inserts a new layer in the list, and calls CTimeWidget->InsertTableLayer(). It also updates the vertical scrollBar max value.
	QAction* m_RemoveAct;	//!< It removes the current layer and calls CTimeWidget->RemoveTableLayer(layer).  It also updates the vertical scrollBar max value.
	QAction* m_ClearAct;		//!< It removes all the items in the selected layer
	QAction* m_CopyAct;		//!< It copies the layer index, so you can paste it later
	QAction* m_CutAct;		//!< It copies the layer index, so you can paste it later
	QAction* m_PasteAct;		//!< It pastes the layer index you copied or cut before. If you cut the layer, it will remove the old one. If you only copied it, the old one will be still available
	QAction* m_MoveupAct;		//!< It moves the selected layer up and updates time->table rows
	QAction* m_MovedownAct;		//!< It moves the selected layer down, and updates time->table rows
	QAction* m_HideshowAct;		//!< It sets all the items in the layer as hidden, or visible if they were hidden
	QAction* m_OnionAct;		//!< All the items in this layers will be shown as "onion skin", so only the border lines are shown
	QAction* m_NameAct;		//!< It changes the name of the layer you have selected

	void _CreateActions(void);
	
	int m_Layers; //!< this value is only used to get the new layers's names. It shouldn't decrease.
        Timeline* core_timeline;
};



#endif // __TIMELIST_H__
