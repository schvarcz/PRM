#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int size = 300;
    double **array = new double*[size];
    for(int i=0;i<size;i++)
        array[i] = new double[size];


    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            array[i][j] = 1.0;
        }
    }

    //Paredes
    for(int i=0;i<size;i++)
    {

        for(int j=0;j<5;j++)
        {
            array[i][j] = 0.0;
        }
    }
    for(int i=0;i<5;i++)
    {

        for(int j=0;j<size;j++)
        {
            array[i][j] = 0.0;
        }
    }
    for(int i=size-5;i<size;i++)
    {

        for(int j=0;j<size;j++)
        {
            array[i][j] = 0.0;
        }
    }

    //Obstaculos no caminho
    for(int i=0;i<size;i++)
    {

        for(int j=size-5;j<size;j++)
        {
            array[i][j] = 0.0;
        }
    }
    for(int i=50;i<100;i++)
    {

        for(int j=50;j<100;j++)
        {
            if(i-50<100-j)
                array[i][j] = 0.0;
        }
    }
    for(int i=200;i<250;i++)
    {

        for(int j=200;j<250;j++)
        {
            if(i-200>250-j)
                array[i][j] = 0.0;
        }
    }
    for(int i=50;i<100;i++)
    {

        for(int j=200;j<250;j++)
        {
            if(j-200>i-50)
                array[i][j] = 0.0;
        }
    }
    for(int i=200;i<250;i++)
    {

        for(int j=50;j<100;j++)
        {
            if(j-50<i-200)
                array[i][j] = 0.0;
        }
    }
    for(int i=200;i<250;i++)
    {

        for(int j=50;j<100;j++)
        {
            if(j-50<i-200)
                array[i][j] = 0.0;
        }
    }
    for(int i=125;i<175;i++)
    {

        for(int j=125;j<175;j++)
        {
            if(
                    i>j-25
                    &&
                    j>i-25
                    &&
                    (i+j-250>25)
                    &&
                    (i+j-250<75)
                )
                array[i][j] = 0.0;
        }
    }

    mPrm = new PRM(array,size);

    mGlWidget = new GLWidget(ui->centralWidget,mPrm);


}

void MainWindow::closeEvent(QCloseEvent *event)
{
    mGlWidget->stopRendering();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    mGlWidget->resize(ui->centralWidget->width(),ui->centralWidget->height());
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    mGlWidget->resize(ui->centralWidget->width(),ui->centralWidget->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}
