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

#ifndef PROPERTYDELEGATE_H
#define PROPERTYDELEGATE_H

#include <QItemDelegate>
#include <QSpinBox>
#include <QColorDialog>
#include <QLineEdit>

class ScenePropertyDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ScenePropertyDelegate();
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const;
     void setEditorData(QWidget *editor, const QModelIndex &index) const;
     void setModelData(QWidget *editor, QAbstractItemModel *model,
                       const QModelIndex &index) const;

public slots:
     void showColorDialog();

 signals:
    void widthChanged( int );
    void heightChanged( int );
    void framerateChanged( int );
    void colorChanged( const QColor& color );

};

//class ItemPropertyDelegate
class ItemPropertyDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ItemPropertyDelegate();
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const;
     void setEditorData(QWidget *editor, const QModelIndex &index) const;
     void setModelData(QWidget *editor, QAbstractItemModel *model,
                       const QModelIndex &index) const;

public slots:
     void showColorDialog();

 signals:
    void widthChanged( int );
    void heightChanged( int );
    void framerateChanged( int );
    void colorChanged( const QColor& color );

};

#endif // PROPERTYDELEGATE_H
