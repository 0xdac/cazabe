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


#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H

#include <QDockWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include "propertydelegate.h"
#include "../../Core/movie.h"
#include "../../Core/symbol.h"

class PropertyEditor : public QDockWidget
{
    Q_OBJECT
public:
    PropertyEditor();
    void showSceneProperties( Movie mainMovie );
    void takeItem( QGraphicsItem* item );

private slots:
    void setItemWidth( int );
    void setItemHeight( int );
    void setItemColor( const QColor& color );

private:
    //Item to be editing
    QGraphicsItem* currentItem;

    QStandardItemModel* sceneModel;
    QStandardItemModel* itemModel;

    //Only for the main movie
    QStandardItem* widthValue;
    QStandardItem* heightValue;
    QStandardItem* width;
    QStandardItem* height;    
    QStandardItem* frameRateValue;
    ScenePropertyDelegate* movieDelegate;

    //Only for items
    QStandardItem* itemWidthValue;
    QStandardItem* itemHeightValue;
    QStandardItem* itemWidth;
    QStandardItem* itemHeight;
    QStandardItem* itemColor;
    QStandardItem* xPos;
    QStandardItem* yPos;
    QStandardItem* xPosValue;
    QStandardItem* yPosValue;
    QStandardItem* instanceName;
    QStandardItem* instanceNameValue;
    QStandardItem* itemLineColor;
    QStandardItem* itemBoder;
    QStandardItem* itemBorderValue;
    ItemPropertyDelegate* itemDelegate;


    QTableView* propertyEditor;

    bool flagModel;

signals:    
     void widthChanged( int );
     void heightChanged( int );
     void framerateChanged( int );
     void colorChanged( const QColor& color );
};

#endif // PROPERTYEDITOR_H
