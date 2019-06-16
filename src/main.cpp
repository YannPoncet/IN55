#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>

#include <QDebug>
#include <QDesktopWidget>

#include "globals.h"

#ifndef QT_NO_OPENGL
#include "mainwidget.h"
#endif


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_UseDesktopOpenGL);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("IN55 - Project");
    app.setApplicationVersion("1.0");

#ifndef QT_NO_OPENGL
    MainWidget widget;

    QRect rec = QApplication::desktop()->screenGeometry();

    widget.resize(WINDOW_HEIGHT,WINDOW_WIDTH);
    widget.showMaximized();

    // If not maximized, the code below can be used to put the window at the center of the screen
    /*int height = rec.height();
    int width = rec.width();
    widget.move((width-WINDOW_HEIGHT)/2,(height-WINDOW_WIDTH)/2);*/

    widget.show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif

    return app.exec();
}
