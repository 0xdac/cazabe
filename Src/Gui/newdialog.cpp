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

#include "newdialog.h"
#include <QMessageBox>

NewDialog::NewDialog()
{
    setFixedSize( 510, 260 );
    dim = new QListWidget;
    dim->addItem( "" );
    dim->addItem( "" );
    dim->addItem( "" );
    n = new QSpinBox;
    t = new QSpinBox;
    p = new QSpinBox;
    iter = new QSpinBox;
    n->setFixedWidth( 100 );
    t->setFixedWidth( 100 );
    p->setFixedWidth( 100 );
    iter->setFixedWidth( 120 );
    QHBoxLayout* mainHorizontal = new QHBoxLayout;
    QHBoxLayout* hbox1 = new QHBoxLayout;
    hbox1->addWidget( new QLabel("N") );
    hbox1->addWidget( n );
    QHBoxLayout* hbox2 = new QHBoxLayout;
    hbox2->addWidget( new QLabel("T") );
    hbox2->addWidget( t );
    QHBoxLayout* hbox3 = new QHBoxLayout;
    hbox3->addWidget( new QLabel("P") );
    hbox3->addWidget( p );
    QVBoxLayout* vertical = new QVBoxLayout;
    vertical->addWidget( new QLabel("Iteraciones") );
    vertical->addWidget( iter );
    QGroupBox *groupBox = new QGroupBox( tr("") );
    groupBox->setFixedWidth( 365 );
    QHBoxLayout* boundary = new QHBoxLayout;
    periodicBoundary = new QRadioButton( tr("") );
    periodicBoundary->setChecked( true );
    reflectBoundary = new QRadioButton( tr("") );
    withOutBoundary = new QRadioButton( tr(" ") );
    openBoundary = new QRadioButton( tr("") );
    boundary->addWidget( periodicBoundary );
    boundary->addWidget( reflectBoundary );
    boundary->addWidget( withOutBoundary );
    boundary->addWidget( openBoundary );
    groupBox->setLayout( boundary );
    QGroupBox* init = new QGroupBox( tr(" ") );
    init->setFixedWidth( 365 );
    QHBoxLayout* cond = new QHBoxLayout;
    random =  new QRadioButton( tr("") );
    random->setChecked( true );
    cond->addWidget( random );
    cond->addWidget( new QRadioButton( tr("") ) );
    init->setLayout( cond );

    QVBoxLayout* vbox = new QVBoxLayout;    
    vbox->addWidget( dim );
    vbox->addLayout( hbox1 );
    vbox->addLayout( hbox2 );
    vbox->addLayout( hbox3 );
    vbox->addLayout( vertical );
    QVBoxLayout* vbox2 = new QVBoxLayout;
    acceptButton = new QPushButton( "Aceptar" );
    cancelButton = new QPushButton( "Cancelar" );
    help = new QPushButton( "Ayuda" );
    QHBoxLayout* buttons = new QHBoxLayout;
    buttons->addWidget( help );
    buttons->addWidget( cancelButton );
    buttons->addWidget( acceptButton );

    vbox2->addWidget( groupBox );
    vbox2->addWidget( init );
    checkNeighborhood = new QCheckBox( tr("") );
    checkNeighborhood->setChecked( true );
    vbox2->addWidget( checkNeighborhood );
    checkStates = new QCheckBox( tr(" ") );
    vbox2->addWidget( checkStates );
    vbox2->addLayout( buttons );
    mainHorizontal->addLayout( vbox );
    mainHorizontal->addLayout( vbox2 );
    setWindowTitle( tr( " " ) );
    setLayout( mainHorizontal );

    connect( cancelButton, SIGNAL( clicked() ), this, SLOT( close() ) );    
    connect( acceptButton, SIGNAL( clicked() ), this, SLOT( slotAccept() ) );
    connect( dim, SIGNAL( clicked( const QModelIndex&) ), this, SLOT( pressDim( const QModelIndex&) ) );

}

NewDialog::~NewDialog()
{

}
//Slots
void NewDialog::pressDim( const QModelIndex& index )
{ 
    switch( index.row() )
    {
        case 0:
            p->setEnabled( false );
        break;

        case 1:
            p->setEnabled( false );
        break;

        case 2:
            p->setEnabled( true );
        break;
    }
}

void NewDialog::slotAccept()
{
                QMessageBox mb;
            mb.setText( "asdad");
            mb.exec();
}

