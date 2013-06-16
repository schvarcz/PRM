#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <prm.h>
#include <glwidget.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);
    
private:
    Ui::MainWindow *ui;
    PRM *mPrm;
    GLWidget *mGlWidget;
};

#endif // MAINWINDOW_H
