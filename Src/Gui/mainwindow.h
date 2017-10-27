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
    Description: This class is the app's main window
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QFileInfo>
#include "newdialog.h"
#include "GraphicsEditor/visualeditormdichild.h"
#include "CodeEditor/codeeditormdichild.h"
#include "Toolbox/toolbox.h"
#include "../Core/scene.h"
#include "../Core/eventdispatcher.h"
#include "../Core/paintsettings.h"
#include "../Core/symbol.h"
#include "../Core/button.h"
#include "Dialogs/converttosymbol.h"
#include "Timeline/guitimeline.h"
#include "Dialogs/aboutdialog.h"
#include "PropertyEditor/propertyeditor.h"
#include "Library/librarydockwidget.h"
#include "../cz/czmanip.h"

#include <QXmlStreamWriter>

class MainWindow : public QMainWindow
{
     Q_OBJECT

 public:
     MainWindow();

 protected:
     void closeEvent( QCloseEvent* event );

 private slots:
     void newModel();
     void open();
     void save();
     void saveAs();
     void print();
     void undo();
     void about();
     void convertToSymbol();
     void enterToSymbol();
     void createEmptyFrame();
     void createEmptyKeyFrame();
     void createKeyFrame();
     void mainTimeline();

     void addFromFileToScene();
     void testMovie();
     void setSceneFrame( int layer, int frame );
     void showSceneProperties();
     void showItemProperties( QGraphicsItem* item );
     void changeWidth( int );
     void changeHeight( int );
     void changeFramerate( int );
     void changeColor( const QColor & color );
     void setActionEnabled();
     void insertItem( QGraphicsItem* item );

 private:
     void createActions();
     void createMenus();
     void createToolBars();
     void createStatusBar();
     void createDockWindows();
     bool maybeSave();
     void updateGui();

     Toolbox* toolbox;
     QToolButton* pressedToolButton;
     QTextEdit* textEdit;
     QMdiArea* mdiArea;
     QListWidget* libraryList;
     VisualEditorMdiChild* editionWindow;
     CodeEditorMdiChild* codeEditorWindow;
     EventDispatcher dispatcher;
     GuiTimeline* timelineDockWidget;
     PropertyEditor* propertyDockWidget;
     LibraryDockWidget* library_widget;

     Timeline* current_timeline;

     int columnOne;
     //Becomes true when we save the project the first time
     bool saved;
     //Holds the path of the saved project, the .cz file
     QString file_path;

     QGraphicsView* view;

     QMenu* fileMenu;
     QMenu* editMenu;
     QMenu* viewMenu;
     QMenu* modifyMenu;     
     QMenu* timelineMenu;
     QMenu* importMenu;
     QMenu* controlMenu;
     QMenu* helpMenu;

     QAction* newAct;
     QAction* openAct;
     QAction* saveAct;
     QAction* saveAsAct;     
     QAction* importToSceneAct;
     QAction* importToLibraryAct;
     QAction* quitAct;
     QAction* convertSymbolAct;
     QAction* enterToSymbolAct;
     QAction* createEmptyFrameAct;
     QAction* createEmptyKeyFrameAct;
     QAction* createKeyFrameAct;
     QAction* mainTimelineAct;

     QAction* previousAct;
     QAction* pauseAct;
     QAction* goAct;
     QAction* nextAct;
     QAction* aboutAct;
     QAction* testMovieAct;     
     QAction* exportLibraryAct;
     QAction* aboutQtAct;
};

#endif // MAINWINDOW_H

