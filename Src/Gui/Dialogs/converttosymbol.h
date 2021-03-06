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

#ifndef CONVERTTOSYMBOL_H
#define CONVERTTOSYMBOL_H

#include <QDialog>
#include <QRadioButton>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../../Core/enumSymbolType.h"
#include <string>
using namespace std;

class ConvertToSymbol : public QDialog
{
    Q_OBJECT

public:
    ConvertToSymbol( QWidget* parent = 0 );
    string getSymbolName();
    SymbolType getSymbolType();

private:
    QLabel *label;

    QRadioButton* clipRadiobutton;
    QRadioButton* buttonRadiobutton;
    QRadioButton* graphicsRadiobutton;

    QLineEdit *lineEdit;
    QCheckBox *caseCheckBox;
    QCheckBox *fromStartCheckBox;
    QCheckBox *wholeWordsCheckBox;
    QCheckBox *searchSelectionCheckBox;
    QCheckBox *backwardCheckBox;
    QDialogButtonBox *buttonBox;
    QPushButton* acceptButton;
    QPushButton* cancelButton;
    QPushButton *moreButton;
    QWidget *extension;
};

#endif // CONVERTTOSYMBOL_H
