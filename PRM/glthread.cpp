#include "glthread.h"

GLThread::GLThread(GLWidget *glWidget) :
    QThread(),
    mGLWidget(glWidget)
{
    doRendering = true;
    doResize = false;
}

void GLThread::resizeViewport(QSize size)
{
    //qDebug() << "Resizing Viewport";
    mSize = size;
    doResize = true;
}

void GLThread::stop()
{
    doRendering = false;
}

void GLThread::run()
{

    msleep(500);
    while(doRendering)
    {
        //qDebug() << "Rendering" << endl;
        mGLWidget->makeCurrent();
        if(doResize)
        {
            doResize = false;
            mGLWidget->resizeGL(mSize.width(),mSize.height());
        }
        mGLWidget->updateGL();
        mGLWidget->doneCurrent();
        msleep(33);
    }
}
