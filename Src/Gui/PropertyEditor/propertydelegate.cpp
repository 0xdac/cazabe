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

#include "propertydelegate.h"
#include <QPushButton>
#include <QMessageBox>

ScenePropertyDelegate::ScenePropertyDelegate()
{
}

QWidget* ScenePropertyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem&,
                           const QModelIndex &index)const
{
    if( index.column() == 1 && index.row() == 0 )
    {
        QSpinBox *editor = new QSpinBox( parent );
        editor->setMinimum(0);
        editor->setMaximum(1000);
        QObject::connect( editor, SIGNAL( valueChanged(int) ), this, SIGNAL( widthChanged(int) ) );

        return editor;
    }
    else if( index.column() == 1 && index.row() == 1 )
    {
        QSpinBox *editor = new QSpinBox( parent );
        editor->setMinimum(0);
        editor->setMaximum(1000);
        QObject::connect( editor, SIGNAL( valueChanged(int) ), this, SIGNAL( heightChanged(int) ) );

        return editor;
    }
    else if( index.column() == 1 && index.row() == 2 )
    {
        QSpinBox *editor = new QSpinBox( parent );
        editor->setMinimum( 0 );
        editor->setMaximum( 1000 );
        QObject::connect( editor, SIGNAL( valueChanged(int) ), this, SIGNAL( framerateChanged(int) ) );

        return editor;
    }
    else if( index.column() == 1 && index.row() == 3 )
    {
        QPushButton* b = new QPushButton( tr( "Choose" ), parent );
        connect( b, SIGNAL( clicked() ), this, SLOT( showColorDialog() ) );
        return b;

    }
    return 0;
}

 void ScenePropertyDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
 {
     if( index.column() == 1 && (index.row() == 0 || index.row() == 1 || index.row() == 2 ) )
     {
        int value = index.model()->data(index, Qt::EditRole).toInt();

        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        spinBox->setValue(value);
    }
 }

 void ScenePropertyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
 {
     if( index.column() == 1 && (index.row() == 0 || index.row() == 1 || index.row() == 2 ) )
     {
        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        spinBox->interpretText();
        int value = spinBox->value();

        model->setData(index, value, Qt::EditRole);
     }
 }

void ScenePropertyDelegate::showColorDialog()
{
    QColor color = QColorDialog::getRgba();
    emit colorChanged( color );
}

//class ItemPropertyDelegate
ItemPropertyDelegate::ItemPropertyDelegate()
{
}

QWidget* ItemPropertyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem&,
                           const QModelIndex &index)const
{
    if( index.column() == 1 && index.row() == 0 )
    {
        QSpinBox *editor = new QSpinBox( parent );
        editor->setMinimum(0);
        editor->setMaximum(1000);
        QObject::connect( editor, SIGNAL( valueChanged(int) ), this, SIGNAL( widthChanged(int) ) );

        return editor;
    }
    else if( index.column() == 1 && index.row() == 1 )
    {
        QSpinBox *editor = new QSpinBox( parent );
        editor->setMinimum(0);
        editor->setMaximum(1000);
        QObject::connect( editor, SIGNAL( valueChanged(int) ), this, SIGNAL( heightChanged(int) ) );

        return editor;
    }
    else if( index.column() == 1 && index.row() == 2 )
    {
        QSpinBox *editor = new QSpinBox( parent );
        editor->setMinimum(0);
        editor->setMaximum(1000);
        //QObject::connect( editor, SIGNAL( valueChanged(int) ), this, SIGNAL( heightChanged(int) ) );

        return editor;
    }
    else if( index.column() == 1 && index.row() == 3 )
    {
        QSpinBox *editor = new QSpinBox( parent );
        editor->setMinimum(0);
        editor->setMaximum(1000);
        //QObject::connect( editor, SIGNAL( valueChanged(int) ), this, SIGNAL( heightChanged(int) ) );

        return editor;
    }
    else if( index.column() == 1 && index.row() == 6 )
    {
       QLineEdit* editor = new QLineEdit( parent );

       return editor;
    }
    else if( index.column() == 1 && index.row() == 5 )
    {
        QSpinBox* editor = new QSpinBox( parent );
        editor->setMinimum(0);
        editor->setMaximum(1000);
        //QObject::connect( editor, SIGNAL( valueChanged(int) ), this, SIGNAL( heightChanged(int) ) );

        return editor;
    }
    else if( index.column() == 1 && index.row() == 4 )
    {
        QPushButton* b = new QPushButton( tr( "Choose" ), parent );
        connect( b, SIGNAL( clicked() ), this, SLOT( showColorDialog() ) );
        return b;

    }
    return 0;
}

 void ItemPropertyDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
 {
     if( index.column() == 1 && (index.row() == 0 || index.row() == 1 || index.row() == 2 || index.row() == 3 ) )
     {
        int value = index.model()->data(index, Qt::EditRole).toInt();

        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        spinBox->setValue(value);
     }
     else if( index.column() == 1 && index.row() == 6 )
     {
        QString text = index.model()->data( index, Qt::EditRole).toString();

        QLineEdit* lineEdit = static_cast<QLineEdit*>( editor );
        lineEdit->setText( text );
     }
 }

 void ItemPropertyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
 {
     if( index.column() == 1 && (index.row() == 0 || index.row() == 1 || index.row() == 2 || index.row() == 3 ) )
     {
        QSpinBox* spinBox = static_cast<QSpinBox*>( editor );
        spinBox->interpretText();
        int value = spinBox->value();

        model->setData( index, value, Qt::EditRole );
     }
     else if( index.column() == 1 && index.row() == 6 )
     {
        QLineEdit* lineEdit = static_cast<QLineEdit*>( editor );

        model->setData( index, lineEdit->text(), Qt::EditRole );
     }
 }

void ItemPropertyDelegate::showColorDialog()
{
    QColor color = QColorDialog::getRgba();
    emit colorChanged( color );
}







