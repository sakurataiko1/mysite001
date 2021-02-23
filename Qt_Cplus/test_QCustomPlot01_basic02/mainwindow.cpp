// 参考:https://evileg.com/en/post/94/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QCustomPlot *wGraphic = ui->customPlot;

      // Init vertical Line
      verticalLine = new QCPCurve(wGraphic->xAxis, wGraphic->yAxis);

      // creating a vector for the vertical line
      QVector<double> x(2) , y(2);
          x[0] = 0;
          y[0] = -50;
          x[1] = 0;
          y[1] = 50;

      // creating of the graphics vector
      QVector<double> x1(5) , y1(5);
          x1[0] = -45;
          y1[0] = -43;
          x1[1] = 46;
          y1[1] = 42;
          x1[2] = -25;
          y1[2] = -24;
          x1[3] = -12;
          y1[3] = 10;
          x1[4] = 25;
          y1[4] = 26;

      wGraphic->addGraph(wGraphic->xAxis, wGraphic->yAxis);
      wGraphic->graph(0)->setData(x1,y1);     // Set the coordinates of the points chart

      // Initialize the router
      tracer = new QCPItemTracer(wGraphic);
      tracer->setGraph(wGraphic->graph(0));

      wGraphic->xAxis->setLabel("x");
      wGraphic->yAxis->setLabel("y");

      wGraphic->xAxis->setRange(-50,50);
      wGraphic->yAxis->setRange(-50,50);

      wGraphic->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

