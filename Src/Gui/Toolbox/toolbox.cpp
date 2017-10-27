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

#include "toolbox.h"

Toolbox::Toolbox()
{
     short size = 23;
     QToolButton* pointerToolButton = new QToolButton;
     pointerToolButton->setIcon( QIcon( ":/images/pointer.png" ) );
     pointerToolButton->setCheckable( true );
     pointerToolButton->setChecked( true );
     pointerToolButton->setFixedSize( size, size );
     pointerToolButton->setToolTip( tr("Select and move") );

     QToolButton* penToolButton = new QToolButton;
     penToolButton->setIcon( QIcon( ":/images/linecursor.png" ) );
     penToolButton->setCheckable( true );
     penToolButton->setFixedSize( size, size );
     penToolButton->setToolTip( tr("Free drawing tool") );

     QToolButton* labelToolButton = new QToolButton;
     labelToolButton->setIcon( QIcon( ":/images/label.png" ) );
     labelToolButton->setCheckable( true );
     labelToolButton->setFixedSize( size, size );
     labelToolButton->setToolTip( tr("Insert text") );

     QToolButton* rectToolButton = new QToolButton;
     rectToolButton->setIcon( QIcon( ":/images/rect.png" ) );
     rectToolButton->setCheckable( true );
     rectToolButton->setFixedSize( size, size );
     rectToolButton->setToolTip( tr("Draw rectangle") );

     lineColorToolButton = new QToolButton;     
     QPixmap pixLine( size, size );
     pixLine.fill( PaintSettings::getPenColor() );
     lineColorToolButton->setIcon( QIcon( pixLine ) );
     lineColorToolButton->setFixedSize( size, size );
     lineColorToolButton->setToolTip( tr("Pen color") );
     //connect( lineColorToolButton, SIGNAL( pressed() ), this, SLOT( setLineColor() ) );

     fillColorToolButton = new QToolButton;     
     //fillColor = QColor( "white" );
     QPixmap pixFill( size, size );
     pixFill.fill( PaintSettings::getFillColor() );
     fillColorToolButton->setIcon( QIcon( pixFill ) );
     fillColorToolButton->setFixedSize( size, size );
     fillColorToolButton->setToolTip( tr("Fill color") );
     //connect( fillColorToolButton, SIGNAL( pressed() ), this, SLOT( setFillColor() ) );

     QToolButton* lineToolButton = new QToolButton;
     lineToolButton->setIcon( QIcon( ":/images/line.png" ) );
     lineToolButton->setCheckable( true );
     lineToolButton->setFixedSize( size, size );
     lineToolButton->setToolTip( tr("Draw line") );

     QToolButton* circleToolButton = new QToolButton;
     circleToolButton->setIcon( QIcon( ":/images/circle.png" ) );
     circleToolButton->setCheckable( true );
     circleToolButton->setFixedSize( size, size );
     circleToolButton->setToolTip( tr("Draw circle") );

     QToolButton* ellipseToolButton = new QToolButton;
     ellipseToolButton->setIcon( QIcon( ":/images/ellipse.png" ) );
     ellipseToolButton->setCheckable( true );
     ellipseToolButton->setFixedSize( size, size );
     ellipseToolButton->setToolTip( tr("Draw ellipse") );

     QToolButton* roundrectToolButton = new QToolButton;
     roundrectToolButton->setIcon( QIcon( ":/images/roundrect.png" ) );
     roundrectToolButton->setCheckable( true );
     roundrectToolButton->setFixedSize( size, size );
     roundrectToolButton->setToolTip( tr("Draw rounded rectangle") );

     QToolButton* freeTransformToolButton = new QToolButton;
     freeTransformToolButton->setIcon( QIcon( ":/images/subselection_tool.png" ) );
     freeTransformToolButton->setCheckable( true );
     freeTransformToolButton->setFixedSize( size, size );
     freeTransformToolButton->setToolTip( tr("Subselection tool") );

     QToolButton* transformToolButton = new QToolButton;
     transformToolButton->setIcon( QIcon( ":/images/ftransform.png" ) );
     transformToolButton->setCheckable( true );
     transformToolButton->setFixedSize( size, size );
     transformToolButton->setToolTip( tr("Scale tool") );

     toolsToolBar = new QToolBar( tr( "Tools" ) );
     toolsToolBar->setOrientation( Qt::Vertical );
     toolsToolBar->setAllowedAreas( Qt::LeftToolBarArea );

     QWidget* toolsWidget = new QWidget;

     QToolBar* toolbar1 = new QToolBar;
     toolbar1->setOrientation( Qt::Vertical );
     toolbar1->addWidget( pointerToolButton );

     QToolBar* penToolBar = new QToolBar;
     penToolBar->setOrientation( Qt::Vertical );
     penToolBar->addWidget( penToolButton );

     QToolBar* labelToolBar = new QToolBar;
     labelToolBar->setOrientation( Qt::Vertical );
     labelToolBar->addWidget( labelToolButton );

     QToolBar* rectToolBar = new QToolBar;
     rectToolBar->setOrientation( Qt::Vertical );
     rectToolBar->addWidget( rectToolButton );

     QToolBar* roundRectToolBar = new QToolBar;
     roundRectToolBar->setOrientation( Qt::Vertical );
     roundRectToolBar->addWidget( roundrectToolButton );

     QToolBar* lineToolBar = new QToolBar;
     lineToolBar->setOrientation( Qt::Vertical );
     lineToolBar->addWidget( lineToolButton );

     QToolBar* circleToolBar = new QToolBar;
     circleToolBar->setOrientation( Qt::Vertical );
     circleToolBar->addWidget( circleToolButton );

     QToolBar* ellipseToolBar = new QToolBar;
     ellipseToolBar->setOrientation( Qt::Vertical );
     ellipseToolBar->addWidget( ellipseToolButton );

     QToolBar* ftToolBar = new QToolBar;
     ftToolBar->setOrientation( Qt::Vertical );
     ftToolBar->addWidget( freeTransformToolButton );

     QToolBar* transfToolBar = new QToolBar;
     transfToolBar->setOrientation( Qt::Vertical );
     transfToolBar->addWidget(transformToolButton  );

     QToolBar* toolbar5 = new QToolBar;
     toolbar5->setOrientation( Qt::Vertical );
     toolbar5->addWidget( lineColorToolButton );

     QToolBar* toolbar6 = new QToolBar;
     toolbar6->setOrientation( Qt::Vertical );
     toolbar6->addWidget( fillColorToolButton );

     QHBoxLayout* hl1 = new QHBoxLayout;
     hl1->setSpacing(0);
     hl1->addWidget( toolbar1 );
     hl1->addWidget( ftToolBar );

     QHBoxLayout* labelAndLine = new QHBoxLayout;
     labelAndLine->addWidget( labelToolBar );
     labelAndLine->addWidget( lineToolBar );

     QHBoxLayout* ellipseAndCircle = new QHBoxLayout;
     ellipseAndCircle->setSpacing(0);
     ellipseAndCircle->addWidget( circleToolBar );
     ellipseAndCircle->addWidget( ellipseToolBar );     

     QHBoxLayout* rectAndRRect = new QHBoxLayout;
     rectAndRRect->setSpacing(0);
     rectAndRRect->addWidget( rectToolBar );
     rectAndRRect->addWidget( roundRectToolBar );

     QHBoxLayout* hl3 = new QHBoxLayout;
     hl3->setSpacing(0);
     hl3->addWidget( toolbar5 );
     hl3->addWidget( toolbar6 );

     QHBoxLayout* transfLayout = new QHBoxLayout;
     transfLayout->setSpacing(0);
     transfLayout->addWidget( transfToolBar );
     transfLayout->addWidget( ftToolBar );

     QVBoxLayout* vlayout = new QVBoxLayout;
     vlayout->setSpacing(0);
     vlayout->addLayout( hl1 );
     vlayout->addLayout( labelAndLine );
     vlayout->addLayout( rectAndRRect );
     vlayout->addLayout( ellipseAndCircle );
     //vlayout->addLayout( transfLayout );
     vlayout->addSpacing( 10 );
     vlayout->addLayout( hl3 );
     penw_spinbox = new QSpinBox;
     penw_spinbox->setToolTip( tr( "Pen width" ) );
     vlayout->addSpacing( 3 );
     vlayout->addWidget( penw_spinbox );

     toolsWidget->setLayout( vlayout );

     toolsToolBar->addWidget( toolsWidget );

     buttongroup = new QButtonGroup();
     buttongroup->addButton( pointerToolButton, MoveItem );
     buttongroup->addButton( penToolButton, FreeDrawing );
     buttongroup->addButton( freeTransformToolButton, FreeTransformItem );
     buttongroup->addButton( transformToolButton, TransformItem );
     buttongroup->addButton( labelToolButton, InsertText );
     buttongroup->addButton( rectToolButton, InsertRect );
     buttongroup->addButton( lineToolButton, InsertLine );
     buttongroup->addButton( circleToolButton, InsertCircle );
     buttongroup->addButton( ellipseToolButton, InsertEllipse );
     buttongroup->addButton( lineColorToolButton, PenColorId );
     buttongroup->addButton( fillColorToolButton, FillColorId );

     connect( buttongroup, SIGNAL( buttonPressed( int ) ), this, SLOT( setMode( int ) ) );
     connect( penw_spinbox, SIGNAL( valueChanged( int ) ), this, SLOT( setPenWidth( int ) ) );
     penw_spinbox->setValue( 1 );
}
Toolbox::~Toolbox()
{

}

void Toolbox::setMode( int mode )
{
    if( mode == PenColorId )
    {
        QColor pen_color = QColorDialog::getColor( PaintSettings::getPenColor() );
        QPixmap p( 23, 23 );
        p.fill( pen_color );
        lineColorToolButton->setIcon( QIcon( p ) );
        PaintSettings::setPenColor( pen_color );
    }
    else if( mode == FillColorId )
    {
        QColor fill_color = QColorDialog::getColor( PaintSettings::getFillColor() );
        QPixmap p( 23, 23 );
        p.fill( fill_color );
        fillColorToolButton->setIcon( QIcon( p ) );
        PaintSettings::setFillColor( fill_color );
    }
    else
    {
        PaintSettings::setMode( (Mode) mode );
    }
}

void Toolbox::setPenWidth( int value )
{
    penw_spinbox->setValue( value );
    PaintSettings::setPenWidth( value );
}

QToolBar* Toolbox::toolBox()
{
    return toolsToolBar;
}


