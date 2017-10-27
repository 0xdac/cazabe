
#include "czmanip.h"


CzManip::CzManip( EventDispatcher* dispatcher )
{
    //Reading
    this->project_settings = dispatcher;

    //Writing
    cz_writer = new QXmlStreamWriter();
    cz_writer->setAutoFormatting( true );
    QTextCodec* codec = QTextCodec::codecForName( "iso-8859-1" );
    cz_writer->setCodec( codec );

    current_layer = 0;
    current_frame = 0;
    current_item = 0;
}

QStringList CzManip::getXmlParseErrors()
{
    return xml_parse_errors;
}

void CzManip::removeTempFiles( QString path )
{
     //Remove the document.xml file and the library folder
     QDir cz_dir( path );
     if( cz_dir.exists( "document.xml" ) )
     {
         cz_dir.remove( "document.xml" );
         if( cz_dir.cd( "library" ) )
         {
             foreach( QString file, cz_dir.entryList() )
             {
                 cz_dir.remove( file );
             }
         }
         cz_dir.cdUp();
         cz_dir.rmdir( "library" );

         if( cz_dir.cd( "assets" ) )
         {
             foreach( QString file, cz_dir.entryList() )
             {
                 cz_dir.remove( file );
             }
         }
         cz_dir.cdUp();
         cz_dir.rmdir( "assets" );
     }
}

    //Start reading functions
bool CzManip::drawCircle( TiXmlElement* element, int layer_index, int frame_index )
{
    const char* pen_color = 0;      //pen style
    const char* fill_color = 0;     //fill style
    int p_width = 0;
    int depth = 0;
    double x, y = 0.0;              //the center of the circle
    double r = 0.0;                 //radius of circle

    TiXmlAttribute* attrib = 0;
    attrib = element->FirstAttribute();

    if( !attrib )
    {
        xml_parse_errors.append( "Cz warning: Circle without attributes, ignored." );
        return false;
    }

    while( attrib )
    {
        if( strcmp( attrib->Name(), "penColor" ) == 0 )
        {
            pen_color = attrib->Value();
        }
        if( strcmp( attrib->Name(), "penWidth" ) == 0 )
        {
            p_width = attrib->IntValue();
        }
        if( strcmp( attrib->Name(), "fillColor" ) == 0 )
        {
            fill_color = attrib->Value();
        }
        if( strcmp( attrib->Name(), "x" ) == 0 )
        {
            x = attrib->DoubleValue();
        }
        if( strcmp( attrib->Name(), "y" ) == 0 )
        {
            y = attrib->DoubleValue();
        }
        if( strcmp( attrib->Name(), "r" ) == 0 )
        {
            r = attrib->DoubleValue();
        }
        if( strcmp( attrib->Name(), "depth" ) == 0 )
        {
            depth = attrib->IntValue();
        }
        attrib = attrib->Next();
    }//End while

    /* Here we have only the center and the radius of the circle and we need
       the top left corner and the bottom right corner of the circle bounding rectangle.
     */
    //Calculate the top left corner
    double x_top_left = x - r;
    double y_top_left = y - r;
    QPointF top_left( x_top_left, y_top_left );

    //Calculate the bottom right corner
    double x_bottom_right = x + r;
    double y_bottom_right = y + r;
    QPointF bottom_right( x_bottom_right, y_bottom_right );
    QPen pen;
    pen.setColor( QColor( pen_color ) );
    pen.setWidth( p_width );
    QColor fc( fill_color );
    QBrush brush( fc );
    //Create circle shape
    CircleItem* c_item = new CircleItem( pen, brush );
    c_item->changeGeometry( top_left, bottom_right );
    c_item->setLayerNumber( layer_index );
    c_item->setFrameNumber( frame_index );
    c_item->setZValue( depth );

    Timeline* main_timeline = project_settings->getTimeline();
    Frame* container_of_items = main_timeline->getFrame( layer_index, frame_index );
    container_of_items->addItem( c_item );
    //Scene* equiv_scene = main_timeline->justGetScene( frame_index );
    //equiv_scene->addItem( c_item );

    return true;
}

bool CzManip::drawEllipse( TiXmlElement* element, int layer_index, int frame_index )
{
    const char* pen_color = 0;      //pen style
    const char* fill_color = 0;     //fill style
    int p_width = 0;
    int depth = 0;
    double x_center, y_center = 0.0;
    double bound_rect_width = 0.0;
    double bound_rect_height = 0.0;

    TiXmlAttribute* attrib = 0;
    attrib = element->FirstAttribute();

    if( !attrib )
    {
        xml_parse_errors.append( "Cz warning: Ellipse without attributes, ignored." );
        return false;
    }

    while( attrib )
    {
        if( strcmp( attrib->Name(), "penColor" ) == 0 )
        {
            pen_color = attrib->Value();
        }
        if( strcmp( attrib->Name(), "penWidth" ) == 0 )
        {
            p_width = attrib->IntValue();
        }
        if( strcmp( attrib->Name(), "fillColor" ) == 0 )
        {
            fill_color = attrib->Value();
        }
        if( strcmp( attrib->Name(), "x" ) == 0 )
        {
            x_center = attrib->DoubleValue();
        }
        if( strcmp( attrib->Name(), "y" ) == 0 )
        {
            y_center = attrib->DoubleValue();
        }
        if( strcmp( attrib->Name(), "width" ) == 0 )
        {
            bound_rect_width = attrib->DoubleValue();
        }
        if( strcmp( attrib->Name(), "height" ) == 0 )
        {
            bound_rect_height = attrib->DoubleValue();
        }
        if( strcmp( attrib->Name(), "depth" ) == 0 )
        {
            depth = attrib->IntValue();
        }
        attrib = attrib->Next();
    }

    /* Here we have only the center, the width and the height of the ellipse and we need
       the top left corner and the bottom right corner of the ellipse bounding rectangle.
     */
    //Calculate the top left corner
    double x_top_left = x_center - ( bound_rect_width / 2 );
    double y_top_left = y_center - ( bound_rect_height / 2 );
    QPointF top_left( x_top_left, y_top_left );

    //Calculate the bottom right corner
    double x_bottom_right = x_center + ( bound_rect_width / 2 );
    double y_bottom_right = y_center + ( bound_rect_height / 2 );
    QPointF bottom_right( x_bottom_right, y_bottom_right );
    QPen pen;
    pen.setColor( QColor( pen_color ) );
    pen.setWidth( p_width );
    QColor fc( fill_color );
    QBrush brush( fc );

    //Create ellipse shape
    EllipseItem* e_item = new EllipseItem( pen, brush );
    e_item->changeGeometry( top_left, bottom_right );
    e_item->setLayerNumber( layer_index );
    e_item->setFrameNumber( frame_index );
    e_item->setZValue( depth );

    Timeline* main_timeline = project_settings->getTimeline();
    Frame* container_of_items = main_timeline->getFrame( layer_index, frame_index );
    container_of_items->addItem( e_item );
    //Scene* equiv_scene = main_timeline->justGetScene( frame_index );
    //equiv_scene->addItem( e_item );

    return true;
}

bool CzManip::drawRect( TiXmlElement* element, int layer_index, int frame_index )
{
    const char* pen_color = 0;      //pen style
    const char* fill_color = 0;     //fill style
    int p_width = 0;
    int depth = 0;
    double x1, y1, x2, y2 = 0;
    TiXmlAttribute* attrib = 0;

    attrib = element->FirstAttribute();
    if( !attrib )
    {
        xml_parse_errors.append( "Cz warning: Rectangle without attributes, ignored." );
        return false;
    }

    while( attrib )
    {
        if( strcmp( attrib->Name(), "penColor" ) == 0 )
        {
            pen_color = attrib->Value();
        }
        else if( strcmp( attrib->Name(), "penWidth" ) == 0 )
        {
            p_width = attrib->IntValue();
        }
        else if( strcmp( attrib->Name(), "fillColor" ) == 0 )
        {
            fill_color = attrib->Value();
        }
        else if( strcmp( attrib->Name(), "x1" ) == 0 )
        {
            x1 = attrib->DoubleValue();
        }
        else if( strcmp( attrib->Name(), "y1" ) == 0 )
        {
            y1 = attrib->DoubleValue();
        }
        else if( strcmp( attrib->Name(), "x2" ) == 0 )
        {
            x2 = attrib->DoubleValue();
        }
        else if( strcmp( attrib->Name(), "y2" ) == 0 )
        {
            y2 = attrib->DoubleValue();
        }
        if( strcmp( attrib->Name(), "depth" ) == 0 )
        {
            depth = attrib->IntValue();
        }
        attrib = attrib->Next();
    }

    QPen pen;
    pen.setColor( QColor( pen_color ) );
    pen.setWidth( p_width );
    QColor fc( fill_color );
    QBrush brush( fc );

    QPointF top_left( x1, y1 );
    QPointF bottom_right( x2, y2 );

    //Create rect shape
    RectItem* r_item = new RectItem( pen, brush );
    r_item->changeGeometry( top_left, bottom_right );
    r_item->setLayerNumber( layer_index );
    r_item->setFrameNumber( frame_index );
    r_item->setZValue( depth );

    Timeline* main_timeline = project_settings->getTimeline();
    Frame* container_of_items = main_timeline->getFrame( layer_index, frame_index );
    container_of_items->addItem( r_item );
    //Scene* equiv_scene = main_timeline->justGetScene( frame_index );
    //equiv_scene->addItem( r_item );

    return true;
}

bool CzManip::drawPath( TiXmlElement* element, int layer_index, int frame_index )
{
    const char* pen_color = 0;      //pen style
    const char* fill_color = 0;     //fill style
    int p_width = 0;
    double x, y = 0.0;
    int depth = 0;
    TiXmlAttribute* attrib = 0;
    TiXmlElement* child_element = 0;
    QVector<QPointF> points;

    attrib = element->FirstAttribute();
    if( !attrib )
    {
        xml_parse_errors.append( "Cz warning: Path without attributes, ignored." );
        return false;
    }

    while( attrib )
    {
        if( strcmp( attrib->Name(), "penColor" ) == 0 )
        {
            pen_color = attrib->Value();
        }
        else if( strcmp( attrib->Name(), "penWidth" ) == 0 )
        {
            p_width = attrib->IntValue();
        }
        else if( strcmp( attrib->Name(), "fillColor" ) == 0 )
        {
            fill_color = attrib->Value();
        }
        if( strcmp( attrib->Name(), "depth" ) == 0 )
        {
            depth = attrib->IntValue();
        }
        attrib = attrib->Next();
    }

    child_element = element->FirstChildElement();
    if( !child_element )
    {
        xml_parse_errors.append( "Cz warning: Path without points, ignored." );
        return false;
    }

    while( child_element )
    {
        if( child_element->ValueStr() == "point" )
        {
            attrib = child_element->FirstAttribute();
            if( !attrib )
            {
                xml_parse_errors.append( "Cz warning: Point without attributes, ignored." );
                return false;
            }

            while( attrib )
            {
                if( strcmp( attrib->Name(), "x" ) == 0 )
                {
                    x = attrib->DoubleValue();
                }
                else if( strcmp( attrib->Name(), "y" ) == 0 )
                {
                    y = attrib->DoubleValue();
                }
                attrib = attrib->Next();
            }
            QPointF p( x, y );
            points.push_back( p );
        }
        else
        {
            xml_parse_errors.append( "Cz error: Bad document structure, no <point> tag." );
        }
        child_element = child_element->NextSiblingElement();
    }

    QPen pen;
    pen.setColor( QColor( pen_color ) );
    pen.setWidth( p_width );
    QColor fc( fill_color );
    QBrush brush( fc );    

    //Create path shape
    RectItem* p_item = new RectItem( pen, brush );
    p_item->setControlPoints( points );
    p_item->setLayerNumber( layer_index );
    p_item->setFrameNumber( frame_index );
    p_item->setZValue( depth );

    Timeline* main_timeline = project_settings->getTimeline();
    Frame* container_of_items = main_timeline->getFrame( layer_index, frame_index );
    container_of_items->addItem( p_item );
    //Scene* equiv_scene = main_timeline->justGetScene( frame_index );
    //equiv_scene->addItem( p_item );

    return true;
}

bool CzManip::drawLine( TiXmlElement* element, int layer_index, int frame_index )
{
    const char* pen_color = 0;      //pen style
    int p_width = 0;
    TiXmlAttribute* attrib = 0;
    int depth = 0;				//the elevation of the item
    double x1, y1, x2, y2 = 0.0;


    attrib = element->FirstAttribute();
    if( !attrib )
    {
        cout<< "cz2swf: Line without attributes, ignored." << endl;
        return false;
    }

    while( attrib )
    {
        if( strcmp( attrib->Name(), "penColor" ) == 0 )
        {
            pen_color = attrib->Value();
        }
        if( strcmp( attrib->Name(), "penWidth" ) == 0 )
        {
            p_width = attrib->IntValue();
        }
        if( strcmp( attrib->Name(), "x1" ) == 0 )
        {
            x1 = attrib->DoubleValue();
        }
        if( strcmp( attrib->Name(), "y1" ) == 0 )
        {
            y1 = attrib->DoubleValue();
        }
        if( strcmp( attrib->Name(), "x2" ) == 0 )
        {
            x2 = attrib->DoubleValue();
        }
        if( strcmp( attrib->Name(), "y2" ) == 0 )
        {
            y2 = attrib->DoubleValue();
        }
        if( strcmp( attrib->Name(), "depth" ) == 0 )
        {
            depth = attrib->IntValue();
        }

        attrib = attrib->Next();
    }//End while

    QPen pen;
    pen.setColor( QColor( pen_color ) );
    pen.setWidth( p_width );
    QPointF top_left( x1, y1 );
    QPointF bottom_right( x2, y2 );

    //Create line shape
    LineItem* l_item = new LineItem( pen );
    l_item->changeGeometry( top_left, bottom_right );
    l_item->setLayerNumber( layer_index );
    l_item->setFrameNumber( frame_index );
    l_item->setZValue( depth );

    Timeline* main_timeline = project_settings->getTimeline();
    Frame* container_of_items = main_timeline->getFrame( layer_index, frame_index );
    container_of_items->addItem( l_item );
    //Scene* equiv_scene = main_timeline->justGetScene( frame_index );
    //equiv_scene->addItem( p_item );

    return true;
}

bool CzManip::drawImage( TiXmlElement* element, int layer_index, int frame_index )
{
    const char* path = 0;
    double x, y = 0.0;
    int depth = 0;				//the elevation of the item
    TiXmlAttribute* attrib = 0;

    attrib = element->FirstAttribute();
    if( !attrib )
    {
        cout<< "cz2swf: Image without attributes, ignored." << endl;
        return false;
    }

    while( attrib )
    {
        if( strcmp( attrib->Name(), "x" ) == 0 )
        {
            x = attrib->DoubleValue();
        }
        if( strcmp( attrib->Name(), "y" ) == 0 )
        {
            y = attrib->DoubleValue();
        }
        if( strcmp( attrib->Name(), "path" ) == 0 )
        {
            path = attrib->Value();
        }
        if( strcmp( attrib->Name(), "depth" ) == 0 )
        {
            depth = attrib->IntValue();
        }

        attrib = attrib->Next();
    }//End while

    //Create image item
    QString p( path );
    QPointF pos( x, y );
    ImageItem* i_item = new ImageItem( QPixmap( p ) );
    i_item->setLayerNumber( layer_index );
    i_item->setFrameNumber( frame_index );
    i_item->setZValue( depth );
    i_item->setPath( p );
    i_item->setPos( pos );

    Timeline* main_timeline = project_settings->getTimeline();
    Frame* container_of_items = main_timeline->getFrame( layer_index, frame_index );
    container_of_items->addItem( i_item );

    return true;
}


bool CzManip::load( QFileInfo file_info )
{
     QString layer_name = "";

    TiXmlNode* pParent = 0;
    TiXmlElement* document = 0;
    TiXmlElement* first_child = 0;      //Can be <symbols> or <timeline>
    TiXmlElement* timeline_tag = 0;
    TiXmlElement* layers_tag = 0;
    TiXmlElement* one_layer_tag = 0;
    TiXmlElement* frames_tag = 0;
    TiXmlElement* one_frame_tag = 0;
    TiXmlElement* elements_tag = 0;
    TiXmlElement* one_element_tag = 0;
    TiXmlAttribute* pAttrib = 0;
    TiXmlAttribute* attrib = 0;
    int duration = 0;
    int layer_index = 0;
    int frame_index = 0;
    bool is_frame_empty = true;

     //A pointer to dumb the xml data to Cazabe main timeline
     Timeline* main_timeline = project_settings->getTimeline();
     main_timeline->clearLayersList();
     xml_parse_errors.clear();

     QString cz_path = file_info.absolutePath();
     QString file_name = file_info.fileName();

     //Remove the document.xml file and the library folder created on a previous call
     /*QDir c_dir( cz_path );
     if( c_dir.exists( "document.xml" ) )
     {
         c_dir.remove( "document.xml" );
         if( c_dir.cd( "library" ) )
         {
             foreach( QString file, c_dir.entryList() )
             {
                 c_dir.remove( file );
             }
         }
         c_dir.cdUp();
         c_dir.rmdir( "library" );
     }*/
     this->removeTempFiles( cz_path );

     QString decompress_string = "unzip ";
     decompress_string.append( file_name );

     QProcess* decompress_process = new QProcess();
     decompress_process->setWorkingDirectory( cz_path );
     decompress_process->start( decompress_string );
     decompress_process->waitForFinished();

     QString complete_file_name = cz_path;
     complete_file_name.append( "/document.xml" );

     TiXmlDocument doc( complete_file_name.toStdString().c_str() );
     bool load_ok = doc.LoadFile();

    if( !load_ok )
    {
        xml_parse_errors.append( "Cz error: Failed to load the xml file" );
        return false;
    }

    pParent = &doc;
    document = pParent->FirstChildElement();	//Go into document
    if( !document )
    {
        xml_parse_errors.append( "Cz error: Failed to load the 'document' tag" );
        return false;
    }

    if( document->ValueStr() == "document" )
    {
        pAttrib = document->FirstAttribute();
        while( pAttrib )
        {
         if( strcmp( pAttrib->Name(), "width" ) == 0  )
         {
            int width = pAttrib->IntValue();
            project_settings->setMovieWidth( width );
         }
         else if( strcmp( pAttrib->Name(), "height" ) == 0 )
         {
            int height = pAttrib->IntValue();
            project_settings->setMovieHeight( height );
         }
         else if( strcmp( pAttrib->Name(), "backgroundColor" ) == 0 )
         {
            const char* background_color = pAttrib->Value();
            project_settings->setBackgroundColor( background_color );
         }
         else if( strcmp( pAttrib->Name(), "framerate" ) == 0 )
         {
            int framerate = pAttrib->IntValue();
            project_settings->setMovieFramerate( framerate );
         }

         pAttrib = pAttrib->Next();
        }//End while

        first_child = document->FirstChildElement();
        if( !first_child )
        {
            xml_parse_errors.append( "Cz error: incomplete document" );
            return false;
        }

        //Check if "symbols" tag exists
        if( first_child->ValueStr() == "symbols" )
        {
            timeline_tag = first_child->NextSiblingElement();
            //Include symbols
        }
        else
        {
            timeline_tag = first_child;
            xml_parse_errors.append( "Cz warning: there is not <symbols> tag, any <symbolInstance> tag will be ignored" );
        }

        //Check if "timeline" tag exists
        if( timeline_tag->ValueStr() == "timeline" )
        {
            layers_tag = timeline_tag->FirstChildElement();
            if( !layers_tag )
                return false;

            if( layers_tag->ValueStr() == "layers" )
            {
                one_layer_tag = layers_tag->FirstChildElement();    //First layer
                if( !one_layer_tag )
                    return false;

                if( one_layer_tag->ValueStr() == "layer" )
                {
                  while( one_layer_tag )
                  {
                    attrib = one_layer_tag->FirstAttribute();
                    if( !attrib )
                        return false;
                    if( strcmp( attrib->Name(), "name" ) == 0 )
                    {
                        layer_name = QString ( attrib->Value() );
                    }
                    if( strcmp( attrib->Name(), "index" ) == 0 )
                    {
                        layer_index = attrib->IntValue();                        
                    }
                    //Create a new layer here
                    TimelineLayer* layer = new TimelineLayer();
                    layer->setName( layer_name );
                    main_timeline->addLayer( layer );

                    frames_tag = one_layer_tag->FirstChildElement();
                    if( !frames_tag )
                        return false;

                    if( frames_tag->ValueStr() == "frames" )
                    {
                        one_frame_tag = frames_tag->FirstChildElement();
                        if( !one_frame_tag )
                        {
                            this->removeTempFiles( cz_path );
                            return false;
                        }

                        if( one_frame_tag->ValueStr() == "frame" )
                        {
                            while( one_frame_tag )
                            {
                                attrib = one_frame_tag->FirstAttribute();
                                if( !attrib )
                                    return false;

                                while( attrib )
                                {
                                    if( strcmp( attrib->Name(), "index" ) == 0 )
                                    {
                                        frame_index = attrib->IntValue();                                        
                                    }
                                    else if( strcmp( attrib->Name(), "empty" ) == 0 )
                                    {
                                        if( attrib->IntValue() == 1 )
                                        {
                                            is_frame_empty = true;
                                        }
                                        else if( attrib->IntValue() == 0 )
                                        {
                                            is_frame_empty = false;
                                        }
                                    }
                                    else if( strcmp( attrib->Name(), "duration" ) == 0 )
                                    {
                                        duration = attrib->IntValue();
                                    }
                                    attrib = attrib->Next();
                                }

                                //Create a new frame here                                
                                //int layer_index = main_timeline->getLayerCount() - 1;
                                if( is_frame_empty )
                                {
                                    main_timeline->setFrameType( EmptyKeyFrame, layer_index, frame_index );
                                }
                                else
                                {
                                    main_timeline->setFrameType( KeyFrame, layer_index, frame_index );
                                    //Scene* s = main_timeline->getScene( frame_index );
                                    //s->clear();
                                }

                                TimelineLayer* layer = 0;
                                for( int i = frame_index + 1, j = 1; j <= duration; i ++, j ++ )
                                {
                                    layer = main_timeline->getLayer( layer_index );
                                    layer->setFrameType( EmptyFrame, i );
                                }

                            if( !is_frame_empty )
                            {
                                elements_tag = one_frame_tag->FirstChildElement();
                                if( !elements_tag )//Before return clean library y document.xml, in all return statements
                                    return false;

                                if( elements_tag->ValueStr() == "elements" )
                                {
                                    one_element_tag = elements_tag->FirstChildElement();
                                    if( !one_element_tag )
                                        return false;

                                    while( one_element_tag )
                                    {
                                        if( one_element_tag->ValueStr() == "script" )
                                        {

                                        }
                                        else if( one_element_tag->ValueStr() == "symbolInstance" )
                                        {

                                        }
                                        else if( one_element_tag->ValueStr() == "ellipse" )
                                        {
                                            if( !this->drawEllipse( one_element_tag, layer_index, frame_index ) )
                                            {
                                                xml_parse_errors.append( "Cz error: can not draw ellipse" );
                                            }
                                        }
                                        else if( one_element_tag->ValueStr() == "circle" )
                                        {
                                            if( !this->drawCircle( one_element_tag, layer_index, frame_index ) )
                                            {
                                                xml_parse_errors.append( "Cz error: can not draw circle" );
                                            }
                                        }
                                        else if( one_element_tag->ValueStr() == "rect" )
                                        {
                                            if( !this->drawRect( one_element_tag, layer_index, frame_index ) )
                                            {
                                                xml_parse_errors.append( "Cz error: can not draw rect" );
                                            }                                            
                                        }
                                        else if( one_element_tag->ValueStr() == "path" )
                                        {
                                            if( !this->drawPath( one_element_tag, layer_index, frame_index ) )
                                            {
                                                xml_parse_errors.append( "Cz error: can not draw path" );
                                            }
                                        }
                                        else if( one_element_tag->ValueStr() == "line" )
                                        {
                                            if( !this->drawLine( one_element_tag, layer_index, frame_index ) )
                                            {
                                                xml_parse_errors.append( "Cz error: can not draw path" );
                                            }
                                        }
                                        else if( one_element_tag->ValueStr() == "image" )
                                        {
                                            if( !this->drawImage( one_element_tag, layer_index, frame_index ) )
                                            {
                                                xml_parse_errors.append( "Cz error: can not draw path" );
                                            }
                                        }
                                        //Get the following element
                                        one_element_tag = one_element_tag->NextSiblingElement();
                                    }
                                }

                                else
                                {
                                    xml_parse_errors.append( "Cz error: Bad document structure, no <elements> tag." );
                                    return false;
                                }
                            }
                                one_frame_tag = one_frame_tag->NextSiblingElement();
                            }
                        }
                    }
                    else
                    {
                        xml_parse_errors.append( "Cz error: Bad document structure, no <frames> tag." );
                        return false;
                    }

                    one_layer_tag = one_layer_tag->NextSiblingElement();    //The others layers
                  }
                }
            }
            else
            {
                xml_parse_errors.append( "Cz error: Bad document structure, no <layers> tag." );
                return false;
            }
        }
        else
        {
            xml_parse_errors.append( "Cz error: Bad document structure, no <timeline> tag." );
            return false;
        }
    }
    else
    {
        xml_parse_errors.append( "Cz error: Bad document structure, no <document> tag." );
        return false;
    }

     //Remove the document.xml file and the library folder
     /*QDir cz_dir( cz_path );
     if( cz_dir.exists( "document.xml" ) )
     {
         cz_dir.remove( "document.xml" );
         if( cz_dir.cd( "library" ) )
         {
             foreach( QString file, cz_dir.entryList() )
             {
                 cz_dir.remove( file );
             }
         }
         cz_dir.cdUp();
         cz_dir.rmdir( "library" );

         if( cz_dir.cd( "assets" ) )
         {
             foreach( QString file, cz_dir.entryList() )
             {
                 cz_dir.remove( file );
             }
         }
         cz_dir.cdUp();
         cz_dir.rmdir( "assets" );
     }*/
    this->removeTempFiles( cz_path );

    return true;
}
    //End reading functions


    //Start writing functions
bool CzManip::save( QFileInfo file_info, bool saved )
{
    QList<Symbol*> symbols_list;
    QList<QString> symbols_name_list;
    QString symbol_name;
    QVariant layer_number;
    //Timeline* symbol_timeline;
    //TimelineLayer* current_layer;
    //Frame* current_frame;
    QDir dir;
    Symbol* one_symbol;

     dir.cd( file_info.absolutePath() );
     QString cz_file_name = file_info.baseName();
     cz_file_name.append( ".cz" );

     if( dir.exists( cz_file_name ) )
     {
         dir.remove( cz_file_name );
     }

     QString file_name = file_info.baseName();
     QString xml_path = file_info.absolutePath();
     QString m_path = file_info.absolutePath();
     //QString images_path = file_info.absolutePath();
     //images_path.append( "/assets/" );
     //QString temp_image_path = images_path;
     //QFile image_manip;
     //QFileInfo image_info;

     dir.mkdir( "library" );
     dir.mkdir( "assets" );

            /***    Library code from here   ***/

     if( dir.exists( "library" ) )
     {
         //Go into "library" dir
         //dir.cd( "library" );

         symbols_list = project_settings->getAllSymbols();
         //QXmlStreamWriter* library_writer = new QXmlStreamWriter();

         for( int i = 0; i < symbols_list.size(); i ++ )
         {
             one_symbol = symbols_list.at( i );
             symbol_name = QString( one_symbol->name().c_str() );
             symbol_name.append( ".xml" );
             symbols_name_list.append( symbol_name );

             QFile one_file( symbol_name );
             if( !one_file.open( QIODevice::WriteOnly | QIODevice::Text ) )
             {
                 qDebug()<< "Can not open "<< symbol_name;
                 return false;
             }

             cz_writer->setDevice( &one_file );

             cz_writer->writeStartElement( "symbol" );
             cz_writer->writeStartElement( "timeline" );
             cz_writer->writeStartElement( "layers" );

             timeline = one_symbol->timeline();
             for( int i = 0; i < timeline->getLayerCount(); i ++ )
             {
                layer_number = i;
                cz_writer->writeStartElement( "layer" );
                cz_writer->writeAttribute( "index", layer_number.toString()  );
                                                          //To be changed
                cz_writer->writeAttribute( "name", layer_number.toString()  );
                cz_writer->writeStartElement( "frames" );

                    //Write to .xml file all the frames elements of the layer at "i"
                    this->writeLayer( i, file_info );

                cz_writer->writeEndElement();     //End frames tag
                cz_writer->writeEndElement();     //End layer tag
             }

             cz_writer->writeEndElement();     //End layers tag
             cz_writer->writeEndElement();     //End timeline tag
             cz_writer->writeEndElement();     //End symbol tag

            //Copy all .xml files to library/ dir
            QString library_path = file_info.absolutePath();
            library_path.append( "/library/" );            
            one_file.copy( library_path.append( symbol_name ) );
            QDir temp_dir( QDir::currentPath() );
            temp_dir.remove( symbol_name );
         }
     }
     else qDebug()<< "Library directory does not exists.";

/***    End Library Code    ***/

     QFile dom_xml( "document.xml" );
     if( !dom_xml.open( QIODevice::WriteOnly | QIODevice::Text ) )
       return false;

     //cz xml based format code
     cz_writer->setDevice( &dom_xml );
     timeline = project_settings->getTimeline();
     //To convert the integer width to QString
     QVariant width_variant(  project_settings->getMovieWidth() );
     QString width = width_variant.toString();

     //To convert the integer height to QString
     QVariant height_variant( project_settings->getMovieHeight() );
     QString height = height_variant.toString();

     QString background_color = project_settings->getBackgroundColor().name();

     //To convert the integer framerate to QString
     QVariant framerate_variant( project_settings->getMovieFramerate() );
     QString framerate = framerate_variant.toString();

     cz_writer->writeStartElement( "document" );
     cz_writer->writeAttribute( "width", width  );
     cz_writer->writeAttribute( "height", height );
     cz_writer->writeAttribute( "backgroundColor", background_color.toUpper() );
     cz_writer->writeAttribute( "framerate", framerate );

     cz_writer->writeStartElement( "symbols" );
     QString lib_path = "library/";
     for( int k = 0; k < symbols_list.size(); k ++ )
     {
         lib_path.append( symbols_name_list.at( k ) );
         cz_writer->writeStartElement( "include" );
         cz_writer->writeAttribute( "href", lib_path );
         cz_writer->writeEndElement();  //End include tag
         lib_path = "library/";
     }
     cz_writer->writeEndElement();  //End symbols tag

     cz_writer->writeStartElement( "timeline" );
     cz_writer->writeStartElement( "layers" );

     for( int i = 0; i < timeline->getLayerCount(); i ++ )
     {
        cz_writer->writeStartElement( "layer" );

        layer_number = i;
        cz_writer->writeAttribute( "index", layer_number.toString()  );//Layer name
                                               //To be changed
        cz_writer->writeAttribute( "name", layer_number.toString()  );//Layer index
        cz_writer->writeStartElement( "frames" );

            //Write to .xml file all the frames elements of the layer at "i"
            this->writeLayer( i, file_info );

        cz_writer->writeEndElement();   //End "frames"
        cz_writer->writeEndElement();   //End "layer"
     }
     cz_writer->writeEndElement();//End "layers"
     cz_writer->writeEndElement();//End "timeline"
     cz_writer->writeEndElement();//End "document"

     dom_xml.copy( xml_path.append( "/document.xml" ) );
     dir.cd( QDir::current().path() );
     dir.remove( "document.xml" );
     //end of cz code

     QProcess* convert_process = new QProcess();
     convert_process->setWorkingDirectory( file_info.absolutePath() );

     QString pro_args1( "zip -r" );
     pro_args1.append( " " );

     QString zip_file( file_name );     //the file_name to add the .zip string at the end
     zip_file.append( ".zip" );

     pro_args1.append( zip_file );
     pro_args1.append( " " );
     pro_args1.append( "library/ assets/ document.xml" );

     convert_process->start( pro_args1 );
     convert_process->waitForFinished();

     dir.cd( file_info.absolutePath() );
     if( dir.exists( zip_file ) )
     {
         if( saved )
         {
             QString old_file = file_name;
             dir.remove( old_file.append( ".cz" ) );
         }
         dir.rename( zip_file, file_name.append( ".cz" ) );
     }

     convert_process->start( "rm -f -r library assets document.xml" );
     convert_process->waitForFinished();

     delete convert_process;
}

void CzManip::writeLayer( int layer_number, QFileInfo file_info )
{
    current_layer = timeline->getLayer( layer_number );

    for( int j = 0; j < current_layer->getFramesCount(); j ++ )
    {
        current_frame = current_layer->getFrame( j );

        switch( current_frame->type() )
        {
            case EmptyFrame:
                //Do nothing, just advance
            break;

            case EmptyKeyFrame:
                this->writeEmptyKeyFrame( j );
            break;

            case KeyFrame:
                this->writeKeyFrame( j, file_info );
            break;

            default:
                break;
        }
    }
}

void CzManip::writeEmptyKeyFrame( QVariant index )
{
    QVariant duration = 0;

    cz_writer->writeStartElement( "frame" );
    cz_writer->writeAttribute( "index", index.toString()  );
    cz_writer->writeAttribute( "empty", "1"  );
    duration = current_frame->getDuration();
    cz_writer->writeAttribute( "duration", duration.toString() );
    cz_writer->writeEndElement();   //End "frame"
}

void CzManip::writeKeyFrame( QVariant index, QFileInfo file_info )
{
    QVariant duration = 0;
    //GraphicItem* current_item = 0;

    cz_writer->writeStartElement( "frame" );
    cz_writer->writeAttribute( "index", index.toString()  );
    cz_writer->writeAttribute( "empty", "0"  );
    duration = current_frame->getDuration();
    cz_writer->writeAttribute( "duration", duration.toString()  );

        //Begins the elements of the frame
        cz_writer->writeStartElement( "elements" );
        if( !current_frame->getScript()->toPlainText().isEmpty() )
        {
            this->writeScript();
        }

        for( int k = 0; k < current_frame->getItemsCount(); k ++ )
        {
            current_item = current_frame->getItem( k );

            switch( current_item->getItemType() )
            {
                case SymbolInstanceType:
                    this->writeSymbol();
                break;

                case LineType:
                    this->writeLine();
                break;

                case ImageType:
                    this->writeImage( file_info );
                break;

                case EllipseType:
                    this->writeEllipse();
                break;

                case CircleType:
                    this->writeCircle();
                break;

                case RectType:
                    this->writeRect();
                break;

                case RoundRectType:

                break;

                case PathType:
                    this->writePath();
                break;

                default:
                    break;
            }
        }

        cz_writer->writeEndElement();   //End "elements"
    cz_writer->writeEndElement();       //End "frame"
}

void CzManip::writeScript()
{
    cz_writer->writeStartElement( "script" );
    cz_writer->writeCDATA( current_frame->getScript()->toPlainText() );
    cz_writer->writeEndElement();
}

void CzManip::writeLine()
{
    QVariant pen_width;
    QVariant x_to_draw;
    QVariant y_to_draw;
    QVariant depth;

    cz_writer->writeStartElement( "line" );
    cz_writer->writeAttribute( "penColor", current_item->getPenColor().name().toUpper() );
    pen_width = current_item->getPenWidth();
    cz_writer->writeAttribute( "penWidth", pen_width.toString() );
    x_to_draw = ((LineItem*)current_item)->getLine().x1();
    y_to_draw = ((LineItem*)current_item)->getLine().y1();
    cz_writer->writeAttribute( "x1", x_to_draw.toString() );
    cz_writer->writeAttribute( "y1", y_to_draw.toString() );
    x_to_draw = ((LineItem*)current_item)->getLine().x2();
    y_to_draw = ((LineItem*)current_item)->getLine().y2();
    cz_writer->writeAttribute( "x2", x_to_draw.toString() );
    cz_writer->writeAttribute( "y2", y_to_draw.toString() );
    depth = (int) current_item->zValue();
    cz_writer->writeAttribute( "depth", depth.toString() );
    cz_writer->writeEndElement();
}

void CzManip::writeImage( QFileInfo file_info )
{
    QVariant x_to_draw;
    QVariant y_to_draw;
    QVariant depth;
    QString images_path = file_info.absolutePath();
    images_path.append( "/assets/" );
    QString temp_image_path = images_path;
    QFile image_manip;
    QFileInfo image_info;

    cz_writer->writeStartElement( "image" );
    x_to_draw = ((ImageItem*)current_item)->pos().x();
    y_to_draw = ((ImageItem*)current_item)->pos().y();
    cz_writer->writeAttribute( "x", x_to_draw.toString() );
    cz_writer->writeAttribute( "y", y_to_draw.toString() );

    image_info.setFile( ((ImageItem*)current_item)->path() );
    temp_image_path.append( image_info.fileName() );
    image_manip.copy( ((ImageItem*)current_item)->path(), temp_image_path );
    temp_image_path = "assets/";
    temp_image_path.append( image_info.fileName() );
    cz_writer->writeAttribute( "path", temp_image_path );
    depth = (int) current_item->zValue();
    cz_writer->writeAttribute( "depth", depth.toString() );
    cz_writer->writeEndElement();
    //temp_image_path = images_path;
}

void CzManip::writePath()
{
    QVariant pen_width;
    QVariant x_to_draw;
    QVariant y_to_draw;
    QVariant depth;
    QPointF one_path_point;

    RectItem* path_item = ((RectItem*)current_item);
    cz_writer->writeStartElement( "path" );
    cz_writer->writeAttribute( "penColor", current_item->getPenColor().name().toUpper() );
    pen_width = current_item->getPenWidth();
    cz_writer->writeAttribute( "penWidth", pen_width.toString() );
    cz_writer->writeAttribute( "fillColor", current_item->getFillColor().name().toUpper() );
    depth = (int) current_item->zValue();
    cz_writer->writeAttribute( "depth", depth.toString() );
    for( int i = 0; i < path_item->getControlPoints().size(); i ++ )
    {
        one_path_point = path_item->getControlPoints().at( i );
        x_to_draw = one_path_point.x();
        y_to_draw = one_path_point.y();
        cz_writer->writeStartElement( "point" );
        cz_writer->writeAttribute( "x", x_to_draw.toString()  );
        cz_writer->writeAttribute( "y", y_to_draw.toString()  );
        cz_writer->writeEndElement();       //End point tag
    }
    cz_writer->writeEndElement();
}

void CzManip::writeRect()
{
    QVariant pen_width;
    QVariant x_to_draw;
    QVariant y_to_draw;
    QVariant width;
    QVariant height;
    QVariant depth;
    qreal x2;
    qreal y2;
    QVariant x2_real;
    QVariant y2_real;

    RectItem* path_item = ((RectItem*)current_item);//don't like this, just for the moment
    cz_writer->writeStartElement( "rect" );
    cz_writer->writeAttribute( "penColor", current_item->getPenColor().name().toUpper() );
    pen_width = current_item->getPenWidth();
    cz_writer->writeAttribute( "penWidth", pen_width.toString() );
    cz_writer->writeAttribute( "fillColor", current_item->getFillColor().name().toUpper() );
    x_to_draw = path_item->getControlPoints().at( 0 ).x();
    y_to_draw = path_item->getControlPoints().at( 0 ).y();
    cz_writer->writeAttribute( "x1", x_to_draw.toString() );
    cz_writer->writeAttribute( "y1", y_to_draw.toString()  );
    x2 = path_item->getControlPoints().at( 3 ).x();
    x2_real = x2;
    y2 = path_item->getControlPoints().at( 3 ).y();
    y2_real = y2;
    cz_writer->writeAttribute( "x2", x2_real.toString() );
    cz_writer->writeAttribute( "y2", y2_real.toString() );
    depth = (int) current_item->zValue();
    cz_writer->writeAttribute( "depth", depth.toString() );
    cz_writer->writeEndElement();
}

void CzManip::writeEllipse()
{
    QVariant pen_width;
    QVariant x_to_draw;
    QVariant y_to_draw;
    QVariant width;
    QVariant height;
    QVariant depth;

    cz_writer->writeStartElement( "ellipse" );
    cz_writer->writeAttribute( "penColor", current_item->getPenColor().name().toUpper()  );
    pen_width = current_item->getPenWidth();
    cz_writer->writeAttribute( "penWidth",  pen_width.toString() );
    cz_writer->writeAttribute( "fillColor", current_item->getFillColor().name().toUpper()  );
    //The center of the ellipse
    x_to_draw = current_item->xToDraw();
    y_to_draw = current_item->yToDraw();
    cz_writer->writeAttribute( "x", x_to_draw.toString() );
    cz_writer->writeAttribute( "y", y_to_draw.toString()  );
    width = current_item->boundingRect().width();
    height = current_item->boundingRect().height();
    cz_writer->writeAttribute( "width", width.toString() );
    cz_writer->writeAttribute( "height", height.toString() );
    depth = (int) current_item->zValue();
    cz_writer->writeAttribute( "depth", depth.toString() );
    cz_writer->writeEndElement();
}

void CzManip::writeCircle()
{
    QVariant pen_width;
    QVariant x_to_draw;
    QVariant y_to_draw;
    QVariant width;
    QVariant height;
    QVariant depth;
    QVariant radius;

    cz_writer->writeStartElement( "circle" );
    cz_writer->writeAttribute( "penColor", current_item->getPenColor().name().toUpper()  );
    pen_width = current_item->getPenWidth();
    cz_writer->writeAttribute( "penWidth",  pen_width.toString() );
    cz_writer->writeAttribute( "fillColor", current_item->getFillColor().name().toUpper()  );
    x_to_draw = current_item->xToDraw();
    y_to_draw = current_item->yToDraw();
    cz_writer->writeAttribute( "x", x_to_draw.toString()  );
    cz_writer->writeAttribute( "y", y_to_draw.toString()  );
    depth = (int) current_item->zValue();
    cz_writer->writeAttribute( "depth", depth.toString() );
    radius = abs( current_item->boundingRect().topRight().x() - current_item->boundingRect().topLeft().x() )/2;
    cz_writer->writeAttribute( "r", radius.toString()  );
    cz_writer->writeEndElement();
}

void CzManip::writeSymbol()
{
    Symbol* symbol_item = dynamic_cast<Symbol*>( current_item );
    QVariant depth = (int) symbol_item->zValue();
    QVariant x = symbol_item->pos().x();
    QVariant y = symbol_item->pos().y();

    cz_writer->writeStartElement( "symbolInstance" );
    cz_writer->writeAttribute( "libraryItemName", QString( symbol_item->name().c_str() ) );
    cz_writer->writeAttribute( "depth", depth.toString() );
    cz_writer->writeAttribute( "x", x.toString() );
    cz_writer->writeAttribute( "y", y.toString() );
    cz_writer->writeEndElement();
}
//End writing functions



