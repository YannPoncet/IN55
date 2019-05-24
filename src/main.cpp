#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>

#include <QDebug>
#include <QDesktopWidget>

#ifndef QT_NO_OPENGL
#include "mainwidget.h"
#endif

const int WINDOW_HEIGHT = 1280;
const int WINDOW_WIDTH = 720;

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
    int height = rec.height();
    int width = rec.width();

    widget.resize(WINDOW_HEIGHT,WINDOW_WIDTH);
    widget.move((width-WINDOW_HEIGHT)/2,(height-WINDOW_WIDTH)/2);
    widget.show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif

    return app.exec();
}
