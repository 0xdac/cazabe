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


#include "timetable.h"
#include "timetableitem.h"
#include "timewidget.h"
#include <qpainter.h>
//Added by qt3to4:
#include <QMouseEvent>
#include <QEvent>
#include <QPaintEvent>

#include <QFlags>
#include <QMenu>
#include <QSizePolicy>

 
//! Constructor. All items are initialized, properties are set, and some frames are created.
//
//! \param iLayersNum : Number of layers we need.
//! \param iFramesNum : Number of frames we need.
//! \param iParent : Parent Widget, , should be CTimeWidget.
CTimeTable::CTimeTable(int iLayersNum, int iFramesNum, QWidget* iParent )
  :QTableWidget( iLayersNum, iFramesNum, iParent )
{
    setFocusPolicy( Qt::StrongFocus );

    //ScrollBars are hidden
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    //rows are resized to 22 pixels height
    for( int i = 0; i < rowCount(); i++ )
        verticalHeader()->resizeSection( i, 20 );

    //columns are resized to 10 px width
    for( int i = 0; i < columnCount(); i++ )
        horizontalHeader()->resizeSection( i, 8 );

    //first item is created, and ready to draw on it
    CTimeTableItem* tempItem = new CTimeTableItem(this);
    tempItem->SetReady();
    tempItem->SetStart();
    setItem( 0, 0, tempItem );

    //other items are also created, but not ready
    for (int i = 1; i < columnCount(); i++)
    {
        CTimeTableItem* tempItem = new CTimeTableItem( this );
	setItem(0,i,tempItem);
    }

    //headers shouldn't be visible
    horizontalHeader()->hide();
    verticalHeader()->hide();
    _CreateActions();

    //The first item is selected and the frame colors are updated ( see UpdateColors() )
    setCurrentItem( item( 0, 0 ) );
    //updateColors( 0 ); //core_timeline does not exists yet
}

//! This replaces QTableWidget::mouseMoveEvent(QMouseEvent * ). If the layer is changed, the layer list is also updated, and if the frame is changed, the ruler is updated.
//
//! \param iEvt : Has info about the move event.
void CTimeTable::mouseMoveEvent(QMouseEvent * iEvt)
{
    if(!iEvt)
      return;

    QTableWidget::mouseMoveEvent(iEvt);  //First, the event is treated as usual

    CTimeWidget* time = (CTimeWidget*) parentWidget()->parentWidget()->parentWidget()->parentWidget();
    int i = (iEvt->pos()).x();
    int j = (iEvt->pos()).y();

    if( !(i>width()) && !(i<0) &&  !(j>20*rowCount()) && !(j<0) )  //If the pointer is IN the table area, the event iEvt is sent to the ruler
	time->SendRulerMousePressEvent(iEvt);

    time->SetListCurrentItem( time->GetListTopLevelItem( currentRow() ));  //The list is updated with the new selected layer index (row)

    this->mousePressEvent( iEvt );
}


//! This replaces QTableWidget::mousePressEvent(QMouseEvent * ). If the layer is changed, the layer list is also updated, and if the frame is changed, the ruler is updated. It also show a menu to copy, paste, and other basic frame functions.
//
//! \param iEvt : Has info about the press event.
void CTimeTable::mousePressEvent( QMouseEvent* iEvt )
{
    if (!iEvt) return;

    setCurrentItem( itemAt(iEvt->pos() ));  //clicked item is new current item
    QTableWidget::mousePressEvent(iEvt);  //the event is treated as usual

    CTimeWidget* time = (CTimeWidget*) parentWidget()->parentWidget()->parentWidget()->parentWidget();
    time->SetListCurrentItem( time->GetListTopLevelItem( currentRow() ));  //The list is updated with the new selected layer index (row)

    int i = (iEvt->pos()).x();
    int j = (iEvt->pos()).y();    

    if( !(i>width()) && !(i<0) &&  !(j>20*rowCount()) && !(j<0) )  //if the pointer is IN the table area...
    {
	time->SendRulerMousePressEvent(iEvt);   // ...the event is sent to the ruler...

        if ( iEvt->button()  == Qt::RightButton )   //... and the menu is created!
	{
	    QMenu* frameMenu = new QMenu (this);

            frameMenu->addAction( m_InsertKeyAct );
            frameMenu->addAction( m_InsertEmptyKeyFrameAct );
            frameMenu->addAction( m_InsertEmptyFrameAct );
	    frameMenu->addSeparator();
	    frameMenu->addAction(m_RemoveAct);  
	    frameMenu->addAction(m_ClearAct); 
	    frameMenu->addSeparator();
	    frameMenu->addAction(m_CutAct); 
	    frameMenu->addAction(m_CopyAct); 
	    frameMenu->addAction(m_PasteAct); 
	    frameMenu->addSeparator();
	    frameMenu->addAction(m_ASAct); 
            frameMenu->popup(mapToGlobal(iEvt->pos()));
            frameMenu->exec();
	    delete frameMenu;
	}
    }

    emit changeScene( currentRow(), currentColumn() );
}

//! Creates QActions and connects them with their slots.
void CTimeTable::_CreateActions()
{

     m_InsertKeyAct = new QAction( tr( "Insert key frame" ), this );
     m_InsertKeyAct->setStatusTip( tr("Insert an editable frame where you have clicked"));
     connect( m_InsertKeyAct, SIGNAL( triggered() ), this, SLOT( insertKeyFrame() ) );
     
     m_InsertEmptyKeyFrameAct = new QAction( tr( "Insert empty key frame" ), this );
     m_InsertEmptyKeyFrameAct->setStatusTip( tr("Insert an empty key frame where you have clicked"));
     connect( m_InsertEmptyKeyFrameAct, SIGNAL( triggered() ), this, SLOT( insertEmptyKeyFrame() ) );

     m_InsertEmptyFrameAct = new QAction( tr( "Insert empty frame" ), this );
     m_InsertEmptyFrameAct->setStatusTip( tr("Insert a frame where you have clicked"));
     connect( m_InsertEmptyFrameAct, SIGNAL( triggered() ), this, SLOT( insertEmptyFrame() ) );
     
     m_RemoveAct = new QAction( tr( "Remove frame" ), this );
     m_RemoveAct->setStatusTip( tr( "Remove the frame" ) );
     connect(m_RemoveAct, SIGNAL(triggered()), this, SLOT( removeFrame() ) );
     
     m_ClearAct = new QAction( tr( "Clear frame" ), this);
     m_ClearAct->setStatusTip( tr( "Remove the items in the frame" ) );
     connect(m_ClearAct, SIGNAL(triggered()), this, SLOT(SlotClearFrame()));

     m_CutAct = new QAction(tr("Cut frame"), this);
     m_CutAct->setStatusTip(tr("Cut the selected frames"));
     connect(m_CutAct, SIGNAL(triggered()), this, SLOT(SlotCutFrame()));
     
     m_CopyAct = new QAction(tr("Copy frame"), this);
     m_CopyAct->setStatusTip(tr("Copy the selected frame"));
     connect(m_CopyAct, SIGNAL(triggered()), this, SLOT(SlotCopyFrame()));
     
     m_PasteAct = new QAction(tr("Paste frame"), this);
     m_PasteAct->setStatusTip(tr("Paste the frames from the m_Clipboard"));
     connect(m_PasteAct, SIGNAL(triggered()), this, SLOT(SlotPasteFrame()));
     
     m_ASAct = new QAction(tr("Add ActionScript"), this);
     m_ASAct->setStatusTip(tr("Add or edit the ActionScript"));
     connect(m_ASAct, SIGNAL(triggered()), this, SLOT(SlotAddAS()));

}


//! [slot] Inserts a keyframe into the choosen frame, or into iLayer, iFrame. \todo This class is not useful yet
//! \param iLayer : If iLayer is provided, the new frame will be inserted at this position.
//! \param iFrame : If iFrame is provided, the new frame will be inserted at this position.
void CTimeTable::insertKeyFrame( int layer, int frame )
{
    int i = currentRow();
    int j = currentColumn();

    if( layer != -1 && frame != -1 )
    {
        i = layer;
        j = frame;
    }

    core_timeline->setFrameType( KeyFrame, i, j );
    updateColors( i );
    //SlotInsertFrame(iLayer, iFrame);
    //DebugLog("insertKeyFrame will be same as insertFrame until we have the render system ready");

}

void CTimeTable::insertEmptyFrame( int layer, int frame )
{
    int i = currentRow();
    int j = currentColumn();
    if( layer != -1 && frame != -1 )
    {
        i = layer;
        j = frame;
    }
    core_timeline->setFrameType( EmptyFrame, i, j );
    updateColors( i );
}

//! [slot] Inserts a frame into the choosen frame, or into iLayer, iFrame.
//
//! \param iLayer : If iLayer is provided, the new frame will be inserted at this position.
//! \param iFrame : If iFrame is provided, the new frame will be inserted at this position.
void CTimeTable::insertEmptyKeyFrame( int layer, int frame )
{
    int i = currentRow();
    int j = currentColumn();
    if( layer != -1 && frame != -1 )
    {
        i = layer;
        j = frame;
    }

    core_timeline->setFrameType( EmptyKeyFrame, i, j );
    updateColors( i );
}

//! [slot] Removes the choosen frame, or frame into iLayer, iFrame.
//
//! \param iLayer : If iLayer is provided, the frame at this position will be removed.
//! \param iFrame :  If iFrame is provided, the frame at this position will be removed.
void CTimeTable::removeFrame(int iLayer, int iFrame)
{

}

//Removes all items in the frame
void CTimeTable::SlotClearFrame(int iF, int iL)
{

}


// Pastes m_ClipboardRow, m_ClipboardCol frame in the current position.
void CTimeTable::SlotPasteFrame()
{

}
//! [slot] Copies current frame position into m_ClipboardRow, m_ClipboardCol and sets m_Cut to 1.
void CTimeTable::SlotCutFrame()
{

}
  
// Copies current frame position into m_ClipboardRow, m_ClipboardCol.
void CTimeTable::SlotCopyFrame(void)
{

}



//! Looks in each row (layer) to find which row has a ready frame with a higher index.
//
//! \return : Number of frames the animation should have.
int CTimeTable::GetFrameCount(void) const 
{
    int t=0;

    for (int a=rowCount()-1;a>=0;a--)   //it looks each row (layer) to find which one has a useful frame with a higher index.
    {

	for (int i=columnCount()-1; i>=0; i--)
	{
	    CTimeTableItem* ti = (CTimeTableItem*) item(a,i); 
	    if (ti->IsEnd() )
	    {
		if (i+1>t) t = i + 1;
		i = -1;           //quite bad, but we need to go next layer
	    }
	} 

    }
    return t;
}

//!Inserts a new layer.
//
//! \param iInitialPosition : when a new layer is created, the first frame is usually the one needed. But if we were reading a saved project, we could need to specify where to create the first frame.
void CTimeTable::InsertLayer(int iInitialPosition) 
{
   setRowCount(rowCount()+1);  //creates a new layer

    //Prepares a new "ready item":
   CTimeTableItem* tempItem = new CTimeTableItem(this);
   tempItem->SetReady();
   tempItem->SetStart();
   setItem( rowCount()-1, iInitialPosition, tempItem );

    //The other items in the frame are also initialised, but not ready
   for (int i = 1; i < columnCount(); i++)
   {
      CTimeTableItem* tempItem = new CTimeTableItem( this );
      setItem(rowCount()-1,i,tempItem);
   } 

   //The header is resized
   verticalHeader()->resizeSection( rowCount()-1, 20 );//20: altura de un fotograma
   core_timeline->addLayer();
}

void CTimeTable::drawLayer(int iInitialPosition)
{
   setRowCount(rowCount()+1);  //creates a new layer

    //Prepares a new "ready item":
   CTimeTableItem* tempItem = new CTimeTableItem(this);
   tempItem->SetReady();
   tempItem->SetStart();
   setItem( rowCount()-1, iInitialPosition, tempItem );

    //The other items in the frame are also initialised, but not ready
   for (int i = 1; i < columnCount(); i++)
   {
      CTimeTableItem* tempItem = new CTimeTableItem( this );
      setItem(rowCount()-1,i,tempItem);
   }

   //The header is resized
   verticalHeader()->resizeSection( rowCount()-1, 20 );//20: altura de un fotograma
   //core_timeline->addLayer();
}

//! Removes layer in iIndex
//
//! \param iIndex : The index of the layer will be removed.
void CTimeTable::RemoveLayer(int iIndex)
{
    removeRow(iIndex);
    core_timeline->removeLayer();
}
  
//! Clears the current layer. \todo Code it when render system is available.
void CTimeTable::ClearLayer(void)
{
}

//! This function is used to know if there is a frame before the given frame.
//
//! \param iLayer : Layer index of the given frame.
//! \param iFrame : Column of the given frame.
//! \return : Returns 1 if finds a ready frame before, else returns 0.
bool CTimeTable::HasAnyFrameBefore(int iLayer, int iFrame) const
{
    for (int i=iFrame;i>0;i--)
    {
	CTimeTableItem* it = ( CTimeTableItem*) item(iLayer, i-1); 
	if (it->IsReady()) return 1;  //if finds a ready frame before, returns 1
    }
    return 0;               //if not, 0
}

//! This function is used to know if there is a frame after the given frame.
//
//! \param iLayer : Layer index of the given frame.
//! \param iFrame : Column of the given frame.
//! \return : Returns 1 if finds a ready frame after, else returns 0.
bool CTimeTable::HasAnyFrameAfter(int iLayer, int iFrame) const
{ 
   for (int i = iFrame ; i < columnCount() - 1 ; i++)
   {
      CTimeTableItem* ti = ( CTimeTableItem*) item(iLayer, i+1); 
     if (ti->IsReady()) return 1;  //if founds a ready frame after, returns 1
   }
   return 0;               //if not, 0
}

//! Explores all the items in the row iRow and paint each frame with different colors.
//
//! \param iRow : Only iRow row will be updated.
void CTimeTable::updateColors( int layer )
{
    int count = core_timeline->getLayer( layer )->getFramesCount();

    for( int i = 0; i< count; i ++ )
    {
        CTimeTableItem* ti = (CTimeTableItem*) item( layer, i );
        if(!ti)
        {
            ti = new CTimeTableItem( this );
            setItem( layer, i, ti );
        }
        Frame* frame = core_timeline->getLayer( layer )->getFrame( i );
        switch( frame->type() )
        {
            case EmptyKeyFrame:
                ti->setBackgroundColor( Qt::blue );
            break;

            case EmptyFrame:
                ti->setBackgroundColor( Qt::white );
            break;

            case KeyFrame:
                ti->setBackgroundColor( Qt::black );
            break;
        }
    }

    for( int j = count; j < columnCount(); j ++ )
    {
        CTimeTableItem* ti = (CTimeTableItem*) item( layer, j );
        if( !ti )
        {
            ti = new CTimeTableItem( this );
            setItem( layer, j, ti );
        }
        ti->setBackgroundColor( QColor( 215, 215, 215 ) );
    }
}


//! Opens an ActionScript dialog to add AS code into the current frame.
void CTimeTable::SlotAddAS()
{
    //DebugLog("Not ready yet");
//   CTimeWidget* ti = (CTimeWidget*) parentWidget()->parentWidget()->parentWidget()->parentWidget();
}

//! Swaps iRowUp and iRowDown rows.
//
//! \param iRowUp : index of the first row you want to swap.
//! \param iRowDown : index of the second row you want to swap.
void CTimeTable::SwapRows(int iRowUp, int iRowDown)
{

    for (int i = 0 ; i < columnCount(); i++)  //This will swap the frames from iRowUp and iRowDown. Very useful to move a layer up and down.
    {
	CTimeTableItem* itemUp = ((CTimeTableItem*) item(iRowUp, i))->Copy(); 
	CTimeTableItem* itemDown = ((CTimeTableItem*) item(iRowDown, i))->Copy(); 
	setItem(iRowUp,i,itemDown);
	setItem(iRowDown,i,itemUp);
    }

}

//! Selects the new item and updates layer list.
void CTimeTable::keyPressEvent ( QKeyEvent * iEvt )
{
    QTableWidget::keyPressEvent(iEvt);  //This uses the event as usual

    CTimeWidget* time = (CTimeWidget*) parentWidget()->parentWidget()->parentWidget()->parentWidget();
    time->SendListTableKeyEvent(iEvt);  //This will send the event to the list, because we want the table and the list synchronised.

}

//! Updates the table with list QKeyEvent.
//
//! \param iEvt : QKeyEvent from the list.
void CTimeTable::listKeyEvent(QKeyEvent * iEvt )
{
    QTableWidget::keyPressEvent(iEvt);  //It makes use of the list qkeyevent
}

