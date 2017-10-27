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
#ifndef __CABOUTDIALOG_H__
#define __CABOUTDIALOG_H__


#include <QDialog>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QTabWidget>

class AboutDialog : public QDialog
{
    Q_OBJECT

    public :
	AboutDialog(QWidget * iParent = NULL);
	~AboutDialog();

    protected :

	void SetupUi(QDialog *PreferencesDialog);

        QPushButton * OkButton;			//!< "Ok" button at the bottom of the dialog.

	QTabWidget* m_TabWidget;	//!< This widget has three tabs with info about the project.
	QWidget * m_Tab;			//!< First tab ("Info" widget).
	QWidget * m_Tab1;			//!< Second tab ("Authors" widget).
	QWidget * m_Tab2;			//!< Third tab ("License" widget).
	
	QTextEdit *m_InfoTextEdit;		//!< Info text, with webpage and irc channel.
	QTextEdit *m_AuthorsTextEdit;	//!< Authors text, with the people who has helped develop Uira.
	QTextEdit * m_LicenseTextEdit;	//!< License text, with info about LGPL.

    public slots :

    private:

}; // class AboutDialog

#endif // __ABOUTDIALOG_H__
