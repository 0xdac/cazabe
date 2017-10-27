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

#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "Shapes/textitem.h"
#include "Shapes/ellipseitem.h"
#include "Shapes/circleitem.h"
#include "Shapes/imageitem.h"
#include "Shapes/lineitem.h"
#include "Shapes/rectitem.h"
#include "paintsettings.h"
#include "cloneable.h"
#include "enumMode.h"
#include "enumSymbolType.h"
#include <string>
#include <QObject>
#include <QGraphicsSceneDragDropEvent>
using namespace std;

class Symbol;

class Scene : public QGraphicsScene//, public Cloneable
{
    Q_OBJECT

public:
    Scene( QObject *parent = 0 );
    void insertSceneItem( const QString& path );
    void convertItemToSymbol( SymbolType type, string name, Symbol* &result );
    Symbol* selectedSymbol();
    //deprecated
    //Scene* clone();


public slots:
    void editorLostFocus( TextItem *item );

signals:    
    void textInserted( QGraphicsTextItem* item );
    void itemSelected( QGraphicsItem* item );
    void itemInserted( QGraphicsItem* item );
    void itemRemoved( QGraphicsItem* item );
    void sceneSelected();

protected:
    void mousePressEvent( QGraphicsSceneMouseEvent* mouseEvent );
    void mouseMoveEvent( QGraphicsSceneMouseEvent* mouseEvent );
    void mouseReleaseEvent( QGraphicsSceneMouseEvent* mouseEvent );
    void keyPressEvent( QKeyEvent* keyEvent );
    void dragEnterEvent( QGraphicsSceneDragDropEvent* event );
    void dragMoveEvent( QGraphicsSceneDragDropEvent* event );
    //void dragLeaveEvent( QGraphicsSceneDragDropEvent* event );
    void dropEvent( QGraphicsSceneDragDropEvent* event );

private:
    bool isItemChange( int type );
    void deselectAll();

    QMenu* myItemMenu;
    bool leftButtonDown;
    QPointF startPoint;
    QString myItemPath;    
    QPointF myEndPoint;
    bool leftMouseButton;
    QGraphicsItem* auxItem;    
    QGraphicsItem* auxSymbol;

    QGraphicsItem* dropped_item;

    GraphicItem* test_item;
    int control_point_pos;
};

#endif //SCENE_H
