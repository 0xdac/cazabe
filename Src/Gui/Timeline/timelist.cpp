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

#include "timelist.h"


#include <QMouseEvent>
#include <QPaintEvent>
#include <QHeaderView>
#include <QMenu>
#include <QInputDialog>

#include "timewidget.h"
#include <qlineedit.h>

//! Constructor. Initializes members, and set default properties. 
//
//! \param iParent : Parent widget, should be CTimeWidget.
CTimeList::CTimeList( QWidget * iParent )
: QTreeWidget(iParent)
{

    //Scrollbars should be hidden
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  
    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setColumnCount( 3 );  //How many colums should the list have? At least 2, one for the name and one for the icon

    setColumnWidth( 0, 85 );
    setColumnWidth( 1, 50 );
    //The name of the columns:
    headerItem()->setText( 0, tr( "Layer" ) );
    headerItem()->setText( 1, tr( "View" ) );
    headerItem()->setText( 2, tr( "Block" ) );

    //The first item is created
    CTimeListItem* firstItem = new CTimeListItem(this, CTimeListItem::UserType);
    firstItem->setText(0, tr("layer")+" 1");

    QCheckBox* view = new QCheckBox();    
    view->setToolTip( tr( "Show or hide layer" ) );
    connect( view, SIGNAL( clicked(bool) ), this, SLOT( hideShowLayer(bool) ) );

    QCheckBox* block = new QCheckBox();
    block->setToolTip( tr( "Block or unblock layer" ) );
    connect( block, SIGNAL( clicked(bool) ), this, SLOT( blockUnBlockLayer(bool) ) );

    setItemWidget( firstItem, 1, view );
    view->setChecked( true );
    setItemWidget( firstItem, 2, block );

    m_Layers = 1;  //Number of layers? 1

    _CreateActions();  //The actions are created

    setCurrentItem(  itemAt( QPoint(1,1 )   )  ); //And the only item is set to current

}

void CTimeList::setCoreTimeline( Timeline* tl )
{
    if( tl )
    {
        core_timeline = tl;
    }
}


//! Synchronises the event with the frame table
//
//! \param iEvt : Qt runtime sent event
void CTimeList::mouseMoveEvent( QMouseEvent* iEvt )
{
   QTreeWidget::mouseMoveEvent( iEvt );

   CTimeWidget* time = (CTimeWidget*) parent();
   time->SelectTableRow( indexOfTopLevelItem( currentItem() ) );
}

//! Synchronises the event with the frame table and shows a menu if needed.
//
//! \param iEvt : Qt runtime sent event
void CTimeList::mousePressEvent(QMouseEvent *iEvt)
{
    QTreeWidget::mousePressEvent( iEvt );

    //First, the row where you clicked is selected in the table

    CTimeWidget* time = (CTimeWidget*) parent();
    int current_layer = indexOfTopLevelItem(  currentItem() );
    time->SelectTableRow( current_layer );
    core_timeline->setCurrentLayer( current_layer );

    //The menu appears
    if (iEvt->button() == Qt::RightButton)
    {
        QMenu* layerMenu = new QMenu( this );

	layerMenu->addAction(m_InsertAct);
	layerMenu->addAction(m_RemoveAct);  
	layerMenu->addAction(m_ClearAct); 
	layerMenu->addSeparator();
	layerMenu->addAction(m_CopyAct); 
	layerMenu->addAction(m_CutAct); 
	layerMenu->addAction(m_PasteAct); 
	layerMenu->addSeparator();
        //layerMenu->addAction(m_MoveupAct);
        //layerMenu->addAction(m_MovedownAct);
	layerMenu->addSeparator();

	CTimeListItem* tempItem = (CTimeListItem*) currentItem();

        //uncomment this and you will get a seg fault
        //m_HideshowAct->setChecked(tempItem->GetView());    //if the layer items are hidden, the checkbox won't be checked

        //layerMenu->addAction(m_HideshowAct);
        //layerMenu->addAction(m_OnionAct);
	layerMenu->addSeparator();
	layerMenu->addAction(m_NameAct); 
	layerMenu->popup (mapToGlobal(QPoint(  iEvt->pos().x(), iEvt->pos().y()+header()->height()  )));
        layerMenu->exec();
	
	delete layerMenu;

    }


}


//! Creates needed actions. \todo use an array initializer?
void CTimeList::_CreateActions(void)
{

     m_InsertAct = new QAction(tr("Insert layer"), this);
     m_InsertAct->setStatusTip(tr("Insert a layer where you have clicked"));
     connect(m_InsertAct, SIGNAL(triggered()), this, SLOT(SlotInsertLayer()));

     m_RemoveAct = new QAction(tr("Remove layer"), this);
     m_RemoveAct->setStatusTip(tr("Remove the layer"));
     connect(m_RemoveAct, SIGNAL(triggered()), this, SLOT(SlotRemoveLayer()));

     m_ClearAct = new QAction(tr("Clear layer"), this);
     m_ClearAct->setStatusTip(tr("Remove the items in the layer"));
     connect(m_ClearAct, SIGNAL(triggered()), this, SLOT(SlotClearLayer()));

     m_CopyAct = new QAction(tr("Copy layer"), this);
     m_CopyAct->setStatusTip(tr("Copy the selected layer"));
     connect(m_CopyAct, SIGNAL(triggered()), this, SLOT(SlotCopyLayer()));

     m_CutAct = new QAction(tr("Cut layer"), this);
     m_CutAct->setStatusTip(tr("Cut the selected m_Layers"));
     connect(m_CutAct, SIGNAL(triggered()), this, SLOT(SlotCutLayer()));

     m_PasteAct = new QAction(tr("Paste layer"), this);
     m_PasteAct->setStatusTip(tr("Paste the m_Layers from the clipboard"));
     connect(m_PasteAct, SIGNAL(triggered()), this, SLOT(SlotPasteLayer()));

     m_MoveupAct = new QAction(tr("Move up"), this);
     m_MoveupAct->setStatusTip(tr("Move the choosen layer up"));
     connect(m_MoveupAct, SIGNAL(triggered()), this, SLOT(SlotMoveUp()));

     m_MovedownAct = new QAction(tr("Move down"), this);
     m_MovedownAct->setStatusTip(tr("Move the choosen layer down"));
     connect(m_MovedownAct, SIGNAL(triggered()), this, SLOT(SlotMoveDown()));

     /*m_HideshowAct = new QAction(tr("View layer"), this);
     m_HideshowAct->setStatusTip(tr("Hide or show the selected layer"));
     //connect(m_HideshowAct, SIGNAL(triggered()), this, SLOT(SlotHideShowLayer()));
     m_HideshowAct->setCheckable(true);
     m_HideshowAct->setChecked(true);*/

     /*m_OnionAct = new QAction(tr("Onion skin"), this);
     m_OnionAct->setStatusTip(tr("View the layer as onion skin"));
     connect(m_OnionAct, SIGNAL(triggered()), this, SLOT(SlotOnionSkinLayer()));
     m_OnionAct->setCheckable(true);
     m_OnionAct->setChecked(false);*/

     m_NameAct = new QAction(tr("Change name"), this);
     m_NameAct->setStatusTip(tr("Change the name of the layer"));
     connect(m_NameAct, SIGNAL(triggered()), this, SLOT(SlotChangeName()));

}

//! Inserts a new layer at the bottom of current layers
void CTimeList::SlotInsertLayer()
{
    //Adds a new list item

    m_Layers ++;
    CTimeListItem* newItem = new CTimeListItem( this, CTimeListItem::UserType );
    newItem->setText( 0, tr( "layer" ) + " " + QString::number( m_Layers ) );

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

    //Adds a new row in time->table

    CTimeWidget* time = (CTimeWidget*) parent();
    time->InsertTableLayer();
    int layerCount = topLevelItemCount();

    //Updates the scrollBar max value

    int max = 0;
    /*if (layerCount>4) max = layerCount-1;
    time->SetMaxVScroll(max);*/
}

//! Removes the current layer.
void CTimeList::SlotRemoveLayer()
{

    //Removes the row in time->table

    int layerNum = indexOfTopLevelItem(  currentItem()  );
    CTimeWidget* time = (CTimeWidget*) parent();
    time->RemoveTableLayer( layerNum );

    //Removes the current item on the list and updates layerCount

    delete currentItem();
    int layerCount = topLevelItemCount();

    //Updates the scrollBar max value

    int max = 0;

}

//! Clears the current layer (removes all items in the  layer)
void CTimeList::SlotClearLayer(void)
{

}

//! Copies the current layer
void CTimeList::SlotCopyLayer(void)
{

}

//! Cuts the current layer
void CTimeList::SlotCutLayer()
{

}

//! Pastes the copied or cut layer.
void CTimeList::SlotPasteLayer()
{

}

//! Moves the current layer up.
void CTimeList::SlotMoveUp()
{

    // Gets the index of the item, and the new index. If the new position is negative, it doesn't continue

   int layerNum = indexOfTopLevelItem(  currentItem()  );
   int layerNumUp = layerNum - 1;
   if (layerNumUp < 0) return;

    //Changes the name of the layers

   QString tmpName =  topLevelItem(layerNumUp)->text(0);
   topLevelItem(layerNumUp)->setText(0, topLevelItem(layerNum)->text(0));
   topLevelItem(layerNum)->setText(0, tmpName );

    //Swaps the rows of the time->table

   CTimeWidget* time = (CTimeWidget*) parent();
   time->SwapTableRows(layerNumUp, layerNum);

    //Selects the item that was selected before

   setCurrentItem(  topLevelItem(layerNumUp) );
   time->SelectTableRow(  indexOfTopLevelItem(  currentItem()  )   );

    core_timeline->moveLayerUp( layerNum );

}

//! Moves the current layer down.
void CTimeList::SlotMoveDown(void)
{

    // Gets the index of the item, and the new index. If the current item is the last item, it doesn't continue

   int layerNum = indexOfTopLevelItem(  currentItem()  );
   int layerNumDown = layerNum + 1;
   if (layerNumDown >=  topLevelItemCount () ) return;

    //Swaps the name of the layers

   QString tmpName =  topLevelItem(layerNum)->text(0);
   topLevelItem(layerNum)->setText(0, topLevelItem(layerNumDown)->text(0)  );
   topLevelItem(layerNumDown)->setText(0, tmpName );

    //Swaps the rows of the time->table

   CTimeWidget* time = (CTimeWidget*) parent();
   time->SwapTableRows(layerNum, layerNumDown);

    //Selects the item that was selected before

   setCurrentItem( topLevelItem(layerNumDown) );
   time->SelectTableRow(  indexOfTopLevelItem(  currentItem()  )   );

   core_timeline->moveLayerDown( layerNum );

}

//! Shows or hides items in current layer.
void CTimeList::hideShowLayer( bool checked )
{
    if( checked )
    {
        core_timeline->showCurrentLayer();
    }
    else
    {
        core_timeline->hideCurrentLayer();
    }
}

void CTimeList::blockUnBlockLayer( bool block )
{
    if( block )
    {
        core_timeline->blockCurrentLayer();
    }
    else
    {
        core_timeline->unBlockCurrentLayer();
    }
}

//! Sets current layer view to OnionSkin, so only borders lines will be shown.
void CTimeList::SlotOnionSkinLayer(void)
{

}

//! Changes the name of the current layer.
void CTimeList::SlotChangeName(void)
{

    bool ok;  // "ok" is used to return the dialog button the user clicks

    //Launches a dialog to get the new name

    QString text = QInputDialog::getText(this, tr("New layer name"),
                                         tr("Write the new name:"), QLineEdit::Normal,
                                         currentItem()->text(0), &ok);

    //If the user clicked "ok" and the new name is valid, the name is changed

    if (ok && !text.isEmpty())
        currentItem()->setText(0, text);

}

//! Updates list and frame table with new info.
//
//! \param iEvt : Info about key press.
void CTimeList::keyPressEvent ( QKeyEvent * iEvt )
{

   QTreeWidget::keyPressEvent(iEvt);                      // It uses the QKeyEvent as usual

   CTimeWidget* time = (CTimeWidget*) parent();  // and sends it to CTimeWidget time, where it will be synchronised with the table
   time->SendTableListKeyEvent(iEvt);

}

//! Updates list and frame table with new info.
//
//! \param iEvt : Table info about key press.
void CTimeList::tableKeyEvent(QKeyEvent * iEvt )
{
    QTreeWidget::keyPressEvent(iEvt);  // it synchronises the keyevents with the table (see timelist.h)

}

