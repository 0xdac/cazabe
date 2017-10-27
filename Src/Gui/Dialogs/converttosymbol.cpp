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

#include "converttosymbol.h"
#include <QMessageBox>

ConvertToSymbol::ConvertToSymbol( QWidget *parent )
    : QDialog( parent )
{    
    label = new QLabel( tr( "Name:" ) );
    lineEdit = new QLineEdit;

    clipRadiobutton = new QRadioButton( tr( "Movie clip" ) );
    clipRadiobutton->setChecked( true );
    buttonRadiobutton = new QRadioButton( tr( "Button" ) );
    graphicsRadiobutton = new QRadioButton( tr( "Graphic" ) );

    acceptButton = new QPushButton( tr( "Accept" ) );
    acceptButton->setDefault( true );

    cancelButton = new QPushButton( tr( "Cancel" ) );

    moreButton = new QPushButton( tr( "More..." ) );
    moreButton->setCheckable( true );
    moreButton->setAutoDefault( false );

    buttonBox = new QDialogButtonBox( Qt::Vertical );
    buttonBox->addButton( acceptButton, QDialogButtonBox::ActionRole );
    buttonBox->addButton( cancelButton, QDialogButtonBox::ActionRole );
    buttonBox->addButton( moreButton, QDialogButtonBox::ActionRole );

    extension = new QWidget;

    wholeWordsCheckBox = new QCheckBox(tr("&Other options"));
    backwardCheckBox = new QCheckBox(tr("Other options"));
    searchSelectionCheckBox = new QCheckBox(tr("Other options"));

    connect( moreButton, SIGNAL( toggled( bool ) ), extension, SLOT( setVisible( bool ) ) );
    connect( cancelButton, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( acceptButton, SIGNAL( clicked() ), this, SLOT( accept() ) );

    QVBoxLayout *extensionLayout = new QVBoxLayout;
    extensionLayout->setMargin( 0 );
    extensionLayout->addWidget( wholeWordsCheckBox );
    extensionLayout->addWidget( backwardCheckBox );
    extensionLayout->addWidget( searchSelectionCheckBox );
    extension->setLayout( extensionLayout );

    QHBoxLayout* topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget( label );
    topLeftLayout->addWidget( lineEdit);

    QVBoxLayout* leftLayout = new QVBoxLayout;
    leftLayout->addLayout( topLeftLayout );
    leftLayout->addWidget( clipRadiobutton );
    leftLayout->addWidget( buttonRadiobutton );
    leftLayout->addWidget( graphicsRadiobutton );
    leftLayout->addStretch( 1 );

    QGridLayout* mainLayout = new QGridLayout;    
    mainLayout->setSizeConstraint( QLayout::SetFixedSize );
    mainLayout->addLayout( leftLayout, 0, 0 );
    mainLayout->addWidget( buttonBox, 0, 1 );
    mainLayout->addWidget( extension, 1, 0, 1, 2 );
    setLayout( mainLayout );

    setWindowTitle( tr( "Symbol" ) );
    extension->hide();
 }

string ConvertToSymbol::getSymbolName()
{
    return lineEdit->text().toStdString();
}

SymbolType ConvertToSymbol::getSymbolType()
{
    if( clipRadiobutton->isChecked() )
        return MovieClipSymbol;

    else if( buttonRadiobutton->isChecked() )
        return ButtonSymbol;

    else
        return GraphicSymbol;
}
