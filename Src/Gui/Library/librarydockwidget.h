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


#ifndef LIBRARYDOCKWIDGET_H
#define LIBRARYDOCKWIDGET_H

#include <QDockWidget>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QListWidget>
#include <QMouseEvent>
#include "../../Core/movie.h"
#include "../../Core/symbol.h"

class LibraryDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    LibraryDockWidget();
    void updateSymbolsList( QList<Symbol*> symbols );
    //void showSceneProperties( Movie mainMovie );
    //void takeItem( QGraphicsItem* item );



private slots:
    void showItemPreview(QListWidgetItem*);
    /*void setItemHeight( int );
    void setItemColor( const QColor& color );*/

private:
    //Item to be editing
    //QGraphicsItem* currentItem;

    QGraphicsScene library_scene;
    QGraphicsView* library_view;
    QListWidget* symbols_list;
/*
signals:    
     void widthChanged( int );
     void heightChanged( int );
     void framerateChanged( int );
     void colorChanged( const QColor& color );*/
};


class LibrarySymbolsItem : public QListWidgetItem
{
    public:
        LibrarySymbolsItem() : QListWidgetItem() {}

        Symbol* getSymbol()
        {
            return this->data_tobe_dropped;
        }

        void setSymbol( Symbol* s )
        {
            this->data_tobe_dropped = s;
        }

    private:
        Symbol* data_tobe_dropped;
};

#endif // LIBRARYDOCKWIDGET_H


