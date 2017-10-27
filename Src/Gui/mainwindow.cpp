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

#include "mainwindow.h"
#include <QtGui>
#include <QProgressDialog>
#include <QColorDialog>

MainWindow::MainWindow()
{
    dispatcher = EventDispatcher();
    this->saved = false;
    this->current_timeline = dispatcher.getTimeline();
    timelineDockWidget = new GuiTimeline( this->current_timeline );

    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    mdiArea->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    setCentralWidget( mdiArea );

    textEdit = new QTextEdit;
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createDockWindows();

    convertSymbolAct->setEnabled( false );
    enterToSymbolAct->setEnabled( false );

    propertyDockWidget->showSceneProperties( dispatcher.getMovie() );

    setWindowTitle( tr( "Cazabe" ) );

    editionWindow = new VisualEditorMdiChild();
    connect( editionWindow->getScene(), SIGNAL( sceneSelected() ), this, SLOT( showSceneProperties()) );
    connect( editionWindow->getScene(), SIGNAL( itemSelected(QGraphicsItem*) ), this, SLOT( showItemProperties(QGraphicsItem*)) );
    connect( editionWindow->getScene(), SIGNAL( itemSelected(QGraphicsItem*) ), timelineDockWidget, SLOT( selectLayerAndFrameOfItem(QGraphicsItem*) ) );
    connect( editionWindow->getScene(), SIGNAL( itemInserted(QGraphicsItem*) ), this, SLOT( insertItem(QGraphicsItem*) ) );
    connect( editionWindow->getScene(), SIGNAL( itemRemoved(QGraphicsItem*) ), this->current_timeline, SLOT( removeItemFromCurrentFrame(QGraphicsItem*) ) );

    codeEditorWindow = new CodeEditorMdiChild();    

    mdiArea->addSubWindow( codeEditorWindow );
    codeEditorWindow->showMinimized();

    mdiArea->addSubWindow( editionWindow );
    mdiArea->cascadeSubWindows();

    editionWindow->show();

    showMaximized();
}

 void MainWindow::newModel()
 {

 }

 void MainWindow::print()
 {
 #ifndef QT_NO_PRINTER
     QTextDocument *document = textEdit->document();
     QPrinter printer;

     QPrintDialog *dlg = new QPrintDialog(&printer, this);
     if (dlg->exec() != QDialog::Accepted)
         return;

     document->print(&printer);

     statusBar()->showMessage(tr("Ready"), 2000);
 #endif
 }

void MainWindow::open()
{
     QString file = QFileDialog::getOpenFileName( this, tr( "Open File" ),
                                                      "/home",
                                                    tr( "Cazabe project (*.cz)"));
     if( file.isEmpty() )
         return;

     QFileInfo file_info( file );
     //Cz manip code here
     CzManip* cz_manipulator = new CzManip( &dispatcher );
     cz_manipulator->load( file_info );
     QStringList errors = cz_manipulator->getXmlParseErrors();

     for( int i = 0; i < errors.size(); i ++ )
     {
        cout<< errors.at( i ).toStdString() << endl;
     }
     this->updateGui();

     this->saved = true;
     file_path = file;

     delete cz_manipulator;
}

 void MainWindow::save()
 {
     if( !saved )
     {
        file_path = QFileDialog::getSaveFileName(this,
                         tr( "Choose a file name" ), ".",
                         tr( "XML based format (*.cz)" ) );

        if( file_path.isEmpty() )
          return;
     }

     QFileInfo file_info( file_path );
     CzManip* cz_manipulator = new CzManip( &dispatcher );
     cz_manipulator->save( file_info, this->saved );

     QApplication::setOverrideCursor(Qt::WaitCursor);

     QApplication::restoreOverrideCursor();
     this->saved = true;
     statusBar()->showMessage(tr("Saved '%1'").arg(file_info.baseName()), 2000);

     delete cz_manipulator;
 }

void MainWindow::saveAs()
{
    QString file = QFileDialog::getSaveFileName(this,
                         tr( "Choose a file name" ), ".",
                         tr( "XML based format (*.cz)" ) );

    if( file.isEmpty() )
        return;

    QFileInfo file_info( file );
    CzManip* cz_manipulator = new CzManip( &dispatcher );
    cz_manipulator->save( file_info, this->saved );
    delete cz_manipulator;
}

bool MainWindow::maybeSave()
{
     if( !saved )//Save last changes not implemented yet
     {
         QFileInfo file_info( file_path );
         QMessageBox::StandardButton ret;
         ret = QMessageBox::warning( this, tr("Cazabe warning"),
                      tr("Project has been modified.\n"
                         "Do you want to save your changes?"),
                      QMessageBox::Yes | QMessageBox::No
                      | QMessageBox::Cancel);
         if ( ret == QMessageBox::Yes )
             save();
         else if ( ret == QMessageBox::No )
             return true;
         else if ( ret == QMessageBox::Cancel )
             return false;
    }
    return true;
}

void MainWindow::closeEvent( QCloseEvent* event )
{
    if( maybeSave() )
    {
         event->accept();
    }
    else
    {
         event->ignore();
    }
}

void MainWindow::updateGui()
{
    this->setSceneFrame( 0, 0 );
    this->timelineDockWidget->repaintFrames();
    this->showSceneProperties();

    Scene* current = editionWindow->getScene();
    if( current )
    {
        int w = dispatcher.getMovieWidth();
        int h = dispatcher.getMovieHeight();

        editionWindow->getGraphicsView()->setFixedSize( w + 4, h + 4 );
        current->setSceneRect( QRectF( 0, 0, w, h )  );
    }
}



 void MainWindow::undo()
 {

 }

 void MainWindow::about()
 {
    //Show About Cazabe
    AboutDialog* about = new AboutDialog( this );
    about->exec();
 }

 void MainWindow::createActions()
 {
     newAct = new QAction( QIcon( ":/images/new.png" ), tr( "&New" ), this );
     newAct->setShortcut( tr( "Ctrl+N" ) );
     newAct->setStatusTip( tr("Create a new project") );
     connect( newAct, SIGNAL( triggered() ), this, SLOT( newModel() ) );

     openAct = new QAction( QIcon( ":/images/open.png" ), tr( "&Open" ), this );
     openAct->setShortcut( tr( "Ctrl+O" ) );
     openAct->setStatusTip( tr("Open project") );
     connect( openAct, SIGNAL( triggered() ), this, SLOT( open() ) );

     saveAct = new QAction( QIcon( ":/images/save.png" ), tr( "&Save..." ), this );
     saveAct->setShortcut( tr( "Ctrl+S" ) );
     saveAct->setStatusTip( tr( "Save current project" ) );
     connect( saveAct, SIGNAL( triggered() ), this, SLOT( save() ) );

     saveAsAct = new QAction( QIcon( ":/images/save.png" ), tr( "&Save as..." ), this );
     saveAsAct->setShortcut( tr( "Ctrl+A" ) );
     saveAsAct->setStatusTip( tr( "Save current project as...") );
     connect( saveAsAct, SIGNAL( triggered() ), this, SLOT( saveAs() ) );

     quitAct = new QAction( tr( "Quit" ), this );
     quitAct->setShortcut(tr("Ctrl+Q"));
     quitAct->setStatusTip(tr("Quit application"));
     connect( quitAct, SIGNAL( triggered() ), this, SLOT( close() ) );

     convertSymbolAct = new QAction( tr( "Set to symbol" ), this );
     convertSymbolAct->setShortcut( tr( "F8" ) );
     connect( convertSymbolAct, SIGNAL( triggered() ), this, SLOT( convertToSymbol() ) );

     enterToSymbolAct = new QAction( tr( "Enter to symbol" ), this );
     enterToSymbolAct->setShortcut( tr( "F2" ) );
     connect( enterToSymbolAct, SIGNAL( triggered() ), this, SLOT( enterToSymbol() ) );

     createEmptyFrameAct = new QAction( tr( "Insert empty frame" ), this );
     createEmptyFrameAct->setShortcut( tr( "F5" ) );
     connect( createEmptyFrameAct, SIGNAL( triggered() ), this, SLOT( createEmptyFrame() ) );

     createEmptyKeyFrameAct = new QAction( tr( "Insert empty key frame" ), this );
     createEmptyKeyFrameAct->setShortcut( tr( "F7" ) );
     connect( createEmptyKeyFrameAct, SIGNAL( triggered() ), this, SLOT( createEmptyKeyFrame() ) );

     createKeyFrameAct = new QAction( tr( "Insert key frame" ), this );
     createKeyFrameAct->setShortcut( tr( "F6" ) );
     connect( createKeyFrameAct, SIGNAL( triggered() ), this, SLOT( createKeyFrame() ) );

     mainTimelineAct = new QAction( tr( "Main timeline" ), this );
     mainTimelineAct->setShortcut( tr( "F3" ) );
     connect( mainTimelineAct, SIGNAL( triggered() ), this, SLOT( mainTimeline() ) );

     /*previousAct = new QAction(QIcon("images/previous.gif"), tr("&Anterior"), this);
     previousAct->setShortcut(tr("Ctrl+Z"));
     previousAct->setStatusTip(tr("Undo the last editing action"));
     connect( previousAct, SIGNAL(triggered()), this, SLOT( undo() ) );*/

     //pauseAct = new QAction( QIcon(":/images/pause.png"), tr("&Detener"), this);

     //goAct = new QAction( QIcon(":/images/go.png"), tr("Ejecutar..."), this);

     //nextAct = new QAction( QIcon(":/images/next.gif"), tr("&Siguiente..."), this);

     testMovieAct = new QAction( QIcon(":/images/testmovie.png"), tr( "Test movie" ), this );
     testMovieAct->setShortcut( tr( "Ctrl+R" ) );
     connect( testMovieAct, SIGNAL( triggered()), this, SLOT( testMovie() ) );

     importToSceneAct = new QAction( tr("to scene"), this );
     connect( importToSceneAct, SIGNAL( triggered() ), this, SLOT( addFromFileToScene() ) );

     importToLibraryAct = new QAction( tr("to library"), this );

     exportLibraryAct = new QAction( tr("Exportar biblioteca"), this );


     aboutAct = new QAction( tr( "About Cazabe" ), this );
     aboutAct->setStatusTip( tr( "Show the application's About box" ) );
     connect( aboutAct, SIGNAL( triggered() ), this, SLOT( about() ) );

     aboutQtAct = new QAction( tr( "About Qt" ), this );
     aboutQtAct->setStatusTip( tr( "Show the Qt library's About box" ) );
     connect( aboutQtAct, SIGNAL( triggered() ), qApp, SLOT( aboutQt() ) );
 }

 void MainWindow::createMenus()
 {
     importMenu = new QMenu( tr( "Import" ) );
     importMenu->addAction( importToSceneAct );
     importMenu->addAction( importToLibraryAct );

     fileMenu = menuBar()->addMenu( tr( "&File" ) );
     fileMenu->addAction( newAct );
     fileMenu->addAction( openAct );
     fileMenu->addAction( saveAct );
     fileMenu->addAction( saveAsAct );
     fileMenu->addMenu( importMenu );


     fileMenu->addSeparator();
     fileMenu->addAction( quitAct );


     editMenu = menuBar()->addMenu( tr("&Edit") );

     viewMenu = menuBar()->addMenu( tr("&View") );

     modifyMenu = menuBar()->addMenu( tr("&Modify") );
     modifyMenu->addAction( convertSymbolAct );
     modifyMenu->addAction( enterToSymbolAct );

     timelineMenu = new QMenu( tr("Timeline") );
     timelineMenu->addAction( createEmptyFrameAct );
     timelineMenu->addAction( createKeyFrameAct );
     timelineMenu->addAction( createEmptyKeyFrameAct );

     modifyMenu->addMenu( timelineMenu );
     modifyMenu->addAction( mainTimelineAct );

     controlMenu = menuBar()->addMenu( tr("&Control") );
     controlMenu->addAction( testMovieAct );

     menuBar()->addSeparator();

     helpMenu = menuBar()->addMenu(tr("Help"));
     helpMenu->addAction( aboutAct );
     helpMenu->addAction( aboutQtAct );
 }

 void MainWindow::createToolBars()
 {
     toolbox = new Toolbox();
     addToolBar( Qt::LeftToolBarArea, toolbox->toolBox() );
 }

 void MainWindow::createStatusBar()
 {
     statusBar()->showMessage( tr("Ready") );
 }

 void MainWindow::createDockWindows()
 {
    library_widget = new LibraryDockWidget();

     propertyDockWidget = new PropertyEditor();
     viewMenu->addAction( propertyDockWidget->toggleViewAction() );
     connect( propertyDockWidget, SIGNAL( widthChanged(int) ), this, SLOT( changeWidth(int) ) );
     connect( propertyDockWidget, SIGNAL( heightChanged(int) ), this, SLOT( changeHeight(int) ) );
     connect( propertyDockWidget, SIGNAL( framerateChanged(int) ), this, SLOT( changeFramerate(int) ) );
     connect( propertyDockWidget, SIGNAL( colorChanged(QColor) ), this, SLOT( changeColor(QColor) ) );

     addDockWidget( Qt::RightDockWidgetArea, library_widget );
     viewMenu->addAction( library_widget->toggleViewAction() );

     tabifyDockWidget( library_widget, propertyDockWidget );

     //timelineDockWidget = new GuiTimeline( dispatcher.getTimeline() );

     connect( timelineDockWidget, SIGNAL( changeScene( int, int ) ), this, SLOT( setSceneFrame( int, int ) ) );

     addDockWidget( Qt::TopDockWidgetArea, timelineDockWidget );

 }

//Slots
void MainWindow::addFromFileToScene()
{
    QStringList filenames;
    filenames = QFileDialog::getOpenFileNames( this, "Importar", QString(), tr("Images (*.png *.jpg)") );
    foreach( QString filename, filenames )
        {
            editionWindow->insertSceneItem( filename );
        }
}

void MainWindow::mainTimeline()
{
    disconnect( editionWindow->getScene(), SIGNAL( itemInserted(QGraphicsItem*) ), this, SLOT( insertItem(QGraphicsItem*) ) );
    disconnect( editionWindow->getScene(), SIGNAL( itemRemoved(QGraphicsItem*) ), this->current_timeline, SLOT( removeItemFromCurrentFrame(QGraphicsItem*) ) );
    this->current_timeline = dispatcher.getTimeline();
    connect( editionWindow->getScene(), SIGNAL( itemInserted(QGraphicsItem*) ), this, SLOT( insertItem(QGraphicsItem*) ) );
    connect( editionWindow->getScene(), SIGNAL( itemRemoved(QGraphicsItem*) ), this->current_timeline, SLOT( removeItemFromCurrentFrame(QGraphicsItem*) ) );
    timelineDockWidget->setTimeline( this->current_timeline );
    setSceneFrame( 0, columnOne );/////////////
    //timelineDockWidget->repaintFrames();
    this->updateGui();    
}

void MainWindow::testMovie()
{
    if( !saved )
        this->save();
    if( saved )
    {
        QProcess* process = new QProcess( this );

        QString cz2swf_process( "cz2swf " );
        QFileInfo file_info( file_path );
        QString file_name = file_info.baseName();
        QString cz_file = file_name;
        cz_file.append( ".cz" );
        cz2swf_process.append( cz_file );
        cz2swf_process.append( " " );
        cz2swf_process.append( file_name.append( ".swf" ) );

        QString w_dir = file_info.absolutePath();
        process->setWorkingDirectory( w_dir );

        process->start( cz2swf_process );
        process->waitForFinished();

        QString gnash_process( "gnash -v " );
        gnash_process.append( file_name );
        QStringList list;
        list.append( "-v" );
        list.append( file_name );
        process->startDetached( "gnash", list , w_dir );
        process->waitForStarted();

        delete process;
    }
}


void MainWindow::setSceneFrame( int layer, int framepos )
{
 if( layer >= 0 && framepos >= 0 )
   {
    this->current_timeline->setCurrentLayer( layer );
    this->current_timeline->getLayer( layer )->setCurrentFrame( framepos );

    if( framepos == 0 )
        columnOne = 0;

    Frame* frame = this->current_timeline->getLayer( layer )->getFrame( framepos, true );

    if( frame != 0 )
    {
        /*Scene* new_scene = dispatcher.getTimeline()->getScene( framepos );
        if( new_scene != 0 )
        {
            disconnect( new_scene, SIGNAL( sceneSelected() ), this, SLOT( showSceneProperties() ) );
            disconnect( new_scene, SIGNAL( itemSelected(QGraphicsItem*) ), this, SLOT( showItemProperties(QGraphicsItem*)) );

            new_scene->setSceneRect( QRectF( 0, 0, dispatcher.getMovieWidth(), dispatcher.getMovieHeight() ) );
            new_scene->setBackgroundBrush( dispatcher.getBackgroundColor() );

            connect( new_scene, SIGNAL( sceneSelected() ), this, SLOT( showSceneProperties()) );
            connect( new_scene, SIGNAL( itemSelected(QGraphicsItem*) ), this, SLOT( showItemProperties(QGraphicsItem*)) );

            editionWindow->setScene( new_scene );
            codeEditorWindow->setDocument( frame->getScript() );
        } */        
        codeEditorWindow->setDocument( frame->getScript() );
     }
    editionWindow->setItems( this->current_timeline->getItemsAt( framepos ) );
   }
}

void MainWindow::showSceneProperties()
{
    propertyDockWidget->showSceneProperties( dispatcher.getMovie() );
    convertSymbolAct->setEnabled( false );
    enterToSymbolAct->setEnabled( false );
}

void MainWindow::showItemProperties( QGraphicsItem* item )
{
    if( item != NULL )
    {
        propertyDockWidget->takeItem( item );
        convertSymbolAct->setEnabled( true );
        enterToSymbolAct->setEnabled( true );

        //When an item is clicked current layer and current frame are those of the item clicked
        GraphicItem* selected_item = dynamic_cast<GraphicItem*>( item );
        this->current_timeline->setCurrentLayer( selected_item->getLayerNumber() );
        this->current_timeline->getLayer( selected_item->getLayerNumber() )->setCurrentFrame( selected_item->getFrameNumber() );


        //Frame* f = dispatcher.getTimeline()->getFrame( selected_item->getLayerNumber(), selected_item->getFrameNumber() );
        /*cout<< endl;
        cout<< "Min:"<< f->getMinDepth() << endl;
        cout<< "Depth:"<< (int)item->zValue() << endl;
        cout<< "Max:"<<f->getMaxDepth() << endl;*/
    }
}

void MainWindow::changeWidth( int value )
{     
     Scene* current = editionWindow->getScene();
     if( current )
     {
         editionWindow->getGraphicsView()->setFixedWidth( value + 4 );
         current->setSceneRect( QRectF( 0, 0, value, current->height() )  );
         dispatcher.setMovieWidth( value );
     }
}

void MainWindow::changeHeight( int value )
{
     Scene* current = editionWindow->getScene();
     if( current )
     {
         editionWindow->getGraphicsView()->setFixedHeight( value + 4 );
         current->setSceneRect( QRectF( 0, 0, current->width(), value )  );
         dispatcher.setMovieHeight( value );
     }
}

void MainWindow::changeFramerate( int value )
{
    dispatcher.setMovieFramerate( value );
}

void MainWindow::changeColor(const QColor& color )
{
    Scene* current = editionWindow->getScene();
    if( current )
    {
        dispatcher.setBackgroundColor( color );
        current->setBackgroundBrush( color );
    }
}

void MainWindow::convertToSymbol()
{
    QDialog::DialogCode returnedCode = QDialog::Rejected;

    ConvertToSymbol dialog;
    returnedCode = ( QDialog::DialogCode ) dialog.exec();

    if( returnedCode == QDialog::Accepted )
    {
        SymbolType type = dialog.getSymbolType();
        string name = dialog.getSymbolName();
        Symbol* result = 0;
        editionWindow->convertItemToSymbol( type, name, result );
        //if( !result ) cout<< "shit" <<endl;
        dispatcher.addSymbolToLibrary( result );
        library_widget->updateSymbolsList( dispatcher.getAllSymbols() );
    }
}

void MainWindow::enterToSymbol()
{
    Symbol* symbol = editionWindow->selectedSymbol();

    if( symbol )
    {
        disconnect( editionWindow->getScene(), SIGNAL( itemInserted(QGraphicsItem*) ), this->current_timeline, SLOT( addItemToCurrentFrame(QGraphicsItem*) ) );
        disconnect( editionWindow->getScene(), SIGNAL( itemRemoved(QGraphicsItem*) ), this->current_timeline, SLOT( removeItemFromCurrentFrame(QGraphicsItem*) ) );
        this->current_timeline = symbol->timeline();        
        connect( editionWindow->getScene(), SIGNAL( itemInserted(QGraphicsItem*) ), this, SLOT( insertItem(QGraphicsItem*) ) );
        connect( editionWindow->getScene(), SIGNAL( itemRemoved(QGraphicsItem*) ), this->current_timeline, SLOT( removeItemFromCurrentFrame(QGraphicsItem*) ) );
        if( typeid( *symbol) == typeid( Button ) )
            timelineDockWidget->setTimeline( this->current_timeline, true );
        else
            timelineDockWidget->setTimeline( this->current_timeline );

        //timelineDockWidget->repaintFrames();
        this->updateGui();        
    }
}

void MainWindow::createEmptyFrame()
{
    timelineDockWidget->setFrameType( EmptyFrame );
}

void MainWindow::createEmptyKeyFrame()
{
    timelineDockWidget->setFrameType( EmptyKeyFrame );
}

void MainWindow::createKeyFrame()
{
    timelineDockWidget->setFrameType( KeyFrame );
}

void MainWindow::setActionEnabled()
{

}

void MainWindow::insertItem( QGraphicsItem* item )
{
    bool flag = false;

    if( current_timeline->createKeyFrameNeeded() )
    {
        timelineDockWidget->setFrameType( KeyFrame );
        flag = true;
    }
    if( current_timeline->getLayerCount() > 0 )
    {
        current_timeline->addItemToCurrentFrame( item );

        if( flag )
        {            
            setSceneFrame( current_timeline->currentLayer(), current_timeline->currentFrame() );
        }
    }
}



