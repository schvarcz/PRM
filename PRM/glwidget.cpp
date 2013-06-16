#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent, PRM *prm) :
    QGLWidget(QGLFormat(QGL::SampleBuffers),parent),
    mGLThread(this)
{
    mPrm = prm;
    startRendering();
}

GLWidget::~GLWidget()
{
}

void GLWidget::startRendering()
{
    mGLThread.start();
}

void GLWidget::stopRendering()
{
    mGLThread.stop();
    mGLThread.wait();
}

bool GLWidget::isRendering()
{
    return mGLThread.isRunning();
}

QSize GLWidget::minimumSize() const
{
    return QSize(400,400);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400,400);
}

QSize GLWidget::maximumSize() const
{
    return QSize(400,400);
}

void GLWidget::initializeGL()
{
    //qDebug() << "initialize GL" << endl;

    qglClearColor(QColor(200,200,200));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWidget::paintGL()
{
    //qDebug() << "Paint GL" << endl;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    if(mPrm)
    {
        mPrm->render();
    }

    glFlush();
}

void GLWidget::resizeGL(int w, int h)
{
    //qDebug() << "Resize GL" << endl;
    width = w;
    height = h;

    int side = qMin(w, h);
    glViewport((w - side) / 2, (h - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int size = 15000;
    glOrtho(-size, size, -size, size,-1,1);
    if(!mGLThread.isRunning())
        updateGL();
}

void GLWidget::resizeEvent(QResizeEvent *event)
{
    //qDebug() << "Resizing Event";
    QGLWidget::resizeEvent(event);
    //mGLThread.resizeViewport(event->size());
    //this->resizeGL(event->size().width(),event->size().height());
}

void GLWidget::paintEvent(QPaintEvent *event)
{
    //Done by GLThread
    if(!this->isRendering())
    {
        startRendering();
    }
}

void GLWidget::closeEvent(QCloseEvent *event)
{
    stopRendering();
    QGLWidget::closeEvent(event);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    double side = (double)min(width,height);

    double size = 15000.0;
    double x = event->x() - (double)width/2, y =(double)height/2 - event->y();
    x *= (2*size)/side;
    y *= (2*size)/side;

    if( mPrm->mInitNode && !mPrm->mGoalNode)
    {
        mPrm->setGoalNode(x,y);
        if(mPrm->mInitNode && mPrm->mGoalNode)
            vector<Edge*> edges = mPrm->query(4);
        /*
        for(int i=0;i<edges.size();i++)
        {
            qDebug() << edges.at(i)->mNodeR->mId;
        }*/

    }
    else
    {
        delete mPrm->mGoalNode;
        mPrm->mGoalNode = NULL;
        mPrm->setInitNode(x,y);
    }

}

void GLWidget::resize(int w, int h)
{
    //qDebug() << "Resizing";
    mGLThread.resizeViewport(QSize(w,h));
    QGLWidget::resize(w,h);
    //this->resizeGL(w,h);
}

void GLWidget::setPrm(PRM *prm)
{
    mPrm = prm;
}

PRM* GLWidget::prm()
{
    return mPrm;
}

void GLWidget::updateScreen()
{
    //startRendering();

    if(!mGLThread.isRunning())
        this->updateGL();

}
