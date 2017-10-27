# -------------------------------------------------
# Project created by QtCreator 2009-06-30T10:09:04
# -------------------------------------------------
QT += gui
LIBS += -lming
TARGET = cazabe
TEMPLATE = app
SOURCES += main.cpp \
    Src/Gui/mainwindow.cpp \
    Src/Gui/GraphicsEditor/visualeditormdichild.cpp \
    Src/Gui/CodeEditor/codeeditormdichild.cpp \
    Src/Gui/newdialog.cpp \
    Src/Gui/CodeEditor/codeeditor.cpp \
    Src/Gui/CodeEditor/highlighter.cpp \
    Src/Gui/PropertyEditor/propertydelegate.cpp \
    Src/Core/frame.cpp \
    Src/Core/timeline.cpp \
    Src/Core/scene.cpp \
    Src/Core/Shapes/textitem.cpp \
    Src/Core/Shapes/imageitem.cpp \
    Src/Gui/Toolbox/toolbox.cpp \
    Src/Core/movie.cpp \
    Src/Gui/Dialogs/converttosymbol.cpp \
    Src/Gui/Dialogs/aboutdialog.cpp \
    Src/Gui/PropertyEditor/propertyeditor.cpp \
    Src/Core/Shapes/ellipseitem.cpp \
    Src/Core/symbol.cpp \
    Src/Core/graphic.cpp \
    Src/Core/button.cpp \
    Src/Core/movieclip.cpp \
    Src/Core/Shapes/graphicitem.cpp \
    Src/Core/Shapes/circleitem.cpp \
    Src/Core/Shapes/lineitem.cpp \
    Src/Core/Shapes/rectitem.cpp \
    Src/Gui/Timeline/guitimeline.cpp \
    Src/Gui/Timeline/timewidget.cpp \
    Src/Gui/Timeline/timevscroll.cpp \
    Src/Gui/Timeline/timetableitem.cpp \
    Src/Gui/Timeline/timetable.cpp \
    Src/Gui/Timeline/timelineruler.cpp \
    Src/Gui/Timeline/timelistitem.cpp \
    Src/Gui/Timeline/timelist.cpp \
    Src/Core/eventdispatcher.cpp \
    Src/Core/paintsettings.cpp \
    Src/Core/timelinelayer.cpp \
    Src/cz/czmanip.cpp \
    Src/TinyXml/tinyxmlparser.cpp \
    Src/TinyXml/tinyxmlerror.cpp \
    Src/TinyXml/tinyxml.cpp \
    Src/TinyXml/tinystr.cpp \
    Src/Gui/Library/librarydockwidget.cpp
HEADERS += Src/Gui/mainwindow.h \
    Src/Gui/GraphicsEditor/visualeditormdichild.h \
    Src/Gui/CodeEditor/codeeditormdichild.h \
    Src/Gui/newdialog.h \
    Src/Gui/CodeEditor/codeeditor.h \
    Src/Gui/CodeEditor/highlighter.h \
    Src/Gui/PropertyEditor/propertydelegate.h \
    Src/Core/enumMode.h \
    Src/Core/enumFrameType.h \
    Src/Core/frame.h \
    Src/Core/timeline.h \
    Src/Core/scene.h \
    Src/Core/Shapes/graphicitem.h \
    Src/Core/Shapes/textitem.h \
    Src/Core/Shapes/imageitem.h \
    Src/Gui/Toolbox/toolbox.h \
    Src/Core/movie.h \
    Src/Gui/Dialogs/converttosymbol.h \
    Src/Gui/Dialogs/aboutdialog.h \
    Src/Gui/PropertyEditor/propertyeditor.h \
    Src/Core/Shapes/ellipseitem.h \
    Src/Core/symbol.h \
    Src/Core/enumSymbolType.h \
    Src/Core/cloneable.h \
    Src/Core/graphic.h \
    Src/Core/button.h \
    Src/Core/movieclip.h \
    Src/Core/Shapes/circleitem.h \
    Src/Core/Shapes/lineitem.h \
    Src/Core/Shapes/rectitem.h \
    Src/Gui/Timeline/guitimeline.h \
    Src/Gui/Timeline/timewidget.h \
    Src/Gui/Timeline/timevscroll.h \
    Src/Gui/Timeline/timetableitem.h \
    Src/Gui/Timeline/timetable.h \
    Src/Gui/Timeline/timelineruler.h \
    Src/Gui/Timeline/timelistitem.h \
    Src/Gui/Timeline/timelist.h \
    Src/Core/eventdispatcher.h \
    Src/Core/paintsettings.h \
    Src/Core/timelinelayer.h \
    Src/Core/enumGraphicItemType.h \
    Src/cz/czmanip.h \
    Src/TinyXml/tinyxml.h \
    Src/TinyXml/tinystr.h \
    Src/Gui/Library/librarydockwidget.h
FORMS += 
RESOURCES += resources.qrc
