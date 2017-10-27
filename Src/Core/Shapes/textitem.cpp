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

#include <QtGui>

#include "textitem.h"
#include "../scene.h"


TextItemPrivate::TextItemPrivate(QGraphicsItem *parent, QGraphicsScene *scene)
{
    //setFlag( QGraphicsItem::ItemIsMovable );
    //setFlag( QGraphicsItem::ItemIsSelectable );
    /*setFlag( QGraphicsItem::ItemIsFocusable );

    text = new QGraphicsTextItem;
   // text->setTextInteractionFlags(  );
    //text->setDefaultTextColor( Qt::red );

    text->setPlainText("fuck");*/
    //setTextInteractionFlags( Qt::TextEditorInteraction );
}

TextItem::TextItem(QGraphicsItem *parent, QGraphicsScene *scene)
{
    setFlag( QGraphicsItem::ItemIsMovable );
    setFlag( QGraphicsItem::ItemIsSelectable );
    setFlag( QGraphicsItem::ItemIsFocusable );

    text = new QGraphicsTextItem();
    //text->setFlag( QGraphicsItem::ItemIsFocusable );
    text->setTextInteractionFlags( Qt::TextEditorInteraction );
    //text->setTextInteractionFlags(  );
    //text->setDefaultTextColor( Qt::red );

    //text->setPlainText("fuck");
    //connect( text, SIGNAL(lostFocus(TextItem *)), this, SLOT(editorLostFocus(TextItem *)));
}

QVariant TextItem::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    /*if ( change == QGraphicsItem::ItemSelectedHasChanged ){
        emit selectedChange( this );
    }*/

    switch ( change )
    {
        case ItemSelectedHasChanged:
            if (value.toBool())// selected
            {
                text->setTextInteractionFlags( Qt::TextEditorInteraction );
                //update();

                    std::cout<< " Null..." << std::endl;
            }
            else // deselected
            {
                text->setTextInteractionFlags( Qt::NoTextInteraction );
            }
        break;

        default:
            break;
    }

    //text->itemChange( change, value );

    return value;

    //return text->itemChange( change, value );
}

void TextItem::focusOutEvent(QFocusEvent *event)
{
    text->setTextInteractionFlags( Qt::NoTextInteraction );
     emit lostFocus( this );
    //QGraphicsTextItem::focusOutEvent(event);

    //text->focusOutEvent( event );
}

void TextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    if ( text->textInteractionFlags() == Qt::NoTextInteraction )
    {
        text->setTextInteractionFlags( Qt::TextEditorInteraction );
      // update();
        //text->mouseDoubleClickEvent( event );
        /*QTextCursor cursor = textCursor();
        cursor.clearSelection();
        setTextCursor( cursor );*/
        //text->update();
    }
    //QGraphicsTextItem::mouseDoubleClickEvent(event);
    //text->mouseDoubleClickEvent( event );
}

QVariant TextItemPrivate::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    if ( change == QGraphicsItem::ItemSelectedHasChanged ){
        emit selectedChange( this );
    }
    return value;
}

void TextItemPrivate::focusOutEvent(QFocusEvent *event)
{
    setTextInteractionFlags( Qt::NoTextInteraction );
     emit lostFocus( this );
    QGraphicsTextItem::focusOutEvent(event);
}

void TextItemPrivate::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    if ( textInteractionFlags() == Qt::NoTextInteraction )
        setTextInteractionFlags( Qt::TextEditorInteraction );

    QGraphicsTextItem::mouseDoubleClickEvent(event);
}

