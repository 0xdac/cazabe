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

#ifndef TEXTITEM_H
#define TEXTITEM_H

#include <QGraphicsTextItem>
#include <QPen>
#include <QFont>
#include <QTextCursor>
#include "../cloneable.h"
#include "graphicitem.h"
#include <iostream>
#include <QTextDocument>

QT_BEGIN_NAMESPACE
class QFocusEvent;
class QGraphicsItem;
class QGraphicsScene;
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

//Deprecated class
class TextItemPrivate : public QGraphicsTextItem
{
    Q_OBJECT

public:
    enum { Type = UserType + 3 };

    TextItemPrivate(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    int type() const
        { return Type; }

    /*TextItem* clone()
    {
        TextItem* t = new TextItem();
        t->setHtml( this->toHtml() );
        t->setFont( this->font() );
        t->setDefaultTextColor( this->defaultTextColor() );
        t->setPos( this->pos() );

        return t;
    }*/

signals:
    void lostFocus(TextItemPrivate *item);
    void selectedChange(QGraphicsItem *item);

public:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void focusOutEvent(QFocusEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:

};



class TextItem : public QObject, public GraphicItem
{
    Q_OBJECT

public:
    enum { Type = UserType + 3 };

    TextItem(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    int type() const
        { return Type; }

    void setFont( const QFont& font )
    {
        text->setFont( font );
    }

    QTextCursor textCursor()
    {
        return text->textCursor();
    }

    void setTextCursor( const QTextCursor& cursor )
    {
        text->setTextCursor( cursor );
    }

    void setHtml( const QString& html )
    {
        text->setHtml( html );
    }

    QString toPlainText () const
    {
        return text->toPlainText();
    }

    void deleteLater()
    {
        text->deleteLater();
    }

    void setDefaultTextColor( const QColor& c )
    {
        text->setDefaultTextColor( c );
    }

    void setTextInteractionFlags( Qt::TextInteractionFlags flags )
    {
        text->setTextInteractionFlags( flags );
        //this->setFlags( text->flags() );
    }

    QRectF boundingRect() const
    {
        return text->boundingRect();
    }
    QPainterPath shape() const
    {
        return text->shape();
    }
    void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0 )
    {
        text->paint( painter, option, widget );
        text->document()->drawContents( painter );
    }

    TextItem* createClone()
    {
        TextItem* clone = new TextItem();
        clone->setHtml( this->text->toHtml() );
        clone->setFont( this->text->font() );
        clone->setDefaultTextColor( this->text->defaultTextColor() );
        clone->setPos( this->pos() );
        clone->setZValue( this->zValue() );

        return clone;
    }

signals:
    void lostFocus(TextItem *item);
    void selectedChange(QGraphicsItem *item);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void focusOutEvent( QFocusEvent* event );
    void mouseDoubleClickEvent( QGraphicsSceneMouseEvent* event );

private:
    QGraphicsTextItem* text;

};
#endif
