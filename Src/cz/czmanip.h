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
    Date: February 22 2011
    Description: A class to manipulate the Cazabe project format .cz
                 Cz is an xml based format
*/

#ifndef CZMANIP_H
#define CZMANIP_H

#include <QFileInfo>
#include <QProcess>
#include <QStack>
#include <QDir>
#include <QXmlStreamWriter>
#include <QTextCodec>
#include <QtDebug>
#include "../Core/eventdispatcher.h"
#include "../Core/enumFrameType.h"
#include "../TinyXml/tinyxml.h"
#include "../Core/Shapes/ellipseitem.h"
#include "../Core/Shapes/circleitem.h"
#include "../Core/Shapes/rectitem.h"
#include "../Core/symbol.h"

class CzManip
{
public:
    CzManip( EventDispatcher* dispatcher );
    //Load an existent project file in .cz format, dump the content to Cazabe main timeline
    bool load( QFileInfo file_info );
    //Save current project to .cz file, dump the content of the Cazabe main timeline to a .cz file
    bool save( QFileInfo file_info, bool saved );
    QStringList getXmlParseErrors();

private:
    //Reading
    bool drawCircle( TiXmlElement* element, int layer_index, int frame_index );
    bool drawEllipse( TiXmlElement* element, int layer_index, int frame_index );
    bool drawRect( TiXmlElement* element, int layer_index, int frame_index );
    bool drawPath( TiXmlElement* element, int layer_index, int frame_index );
    bool drawLine( TiXmlElement* element, int layer_index, int frame_index );
    bool drawImage( TiXmlElement* element, int layer_index, int frame_index );

    EventDispatcher* project_settings;
    QStringList xml_parse_errors;

    //Writing
    void writeLayer( int layer_number, QFileInfo file_info );
    void writeKeyFrame( QVariant index, QFileInfo file_info );
    void writeEmptyKeyFrame( QVariant index );
    void writeScript();
    void writeLine();
    void writeImage( QFileInfo file_info );
    void writePath();
    void writeRect();
    void writeEllipse();
    void writeCircle();
    void writeSymbol();

    QXmlStreamWriter* cz_writer;
    Timeline* timeline;
    TimelineLayer* current_layer;
    Frame* current_frame;
    GraphicItem* current_item;


    void removeTempFiles( QString path );
};

#endif // CZMANIP_H
