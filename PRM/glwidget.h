#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtCore>
#include <QObject>
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLFormat>
#include <QResizeEvent>
#include <glthread.h>
#include <prm.h>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent,PRM *prm);
    ~GLWidget();
    QSize minimumSize() const;
    QSize sizeHint() const;
    QSize maximumSize() const;
    void resize(int w, int h);
    void startRendering();
    void stopRendering();
    bool isRendering();
    void resizeGL(int w, int h);
    void setPrm(PRM *prm);
    PRM* prm();

protected:
    void initializeGL();
    void paintGL();
    void resizeEvent(QResizeEvent *event);
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    int width, height;
    GLThread mGLThread;
    PRM *mPrm;

public slots:
    void updateScreen();

signals:

};

#endif // GLWIDGET_H
