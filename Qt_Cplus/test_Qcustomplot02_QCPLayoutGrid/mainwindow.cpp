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

    QCustomPlot *customPlot = ui->customPlot;

    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
        x[i] = i/50.0 - 1; // x goes from -1 to 1
        y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);


    //凡例表示
    customPlot->setAutoAddPlottableToLegend(true);// plottable(=graph)を追加したら自動で凡例に追加
    customPlot->legend->setVisible(true); // 凡例を表示する

    //凡例をグラフの外に表示
    QCPLayoutGrid *subLayout = new QCPLayoutGrid;  // グラフの右に挿入されるQCPLayoutGrid(subLayout)
    //ui.histogram->plotLayout()->addElement(0, 1, subLayout); // (Row, Column) = (0,1)にsubLayoutを追加
    customPlot->plotLayout()->addElement(0, 1, subLayout); // (Row, Column) = (0,1)にsubLayoutを追加
      subLayout->addElement(0, 0, new QCPLayoutElement); // subLayoutの(Row, Column) = (0,0)にPadding用QCPLayoutElementを
    //subLayout->addElement(1, 0, ui.histogram->legend); // (Row, Column) = (1,0)に凡例（Legend）を追加
      subLayout->addElement(1, 0, customPlot->legend); // (Row, Column) = (1,0)に凡例（Legend）を追加
      subLayout->addElement(2, 0, new QCPLayoutElement); // 同Paddingを追加
      subLayout->setColumnStretchFactor(0, 0.01);        // subLayoutの横幅はなるべく小さくする
      subLayout->setRowStretchFactor(1, 0.01);           // subLayoutの凡例がはいるRow=1はなるべく小さくする
    //ui.histogram->plotLayout()->setColumnStretchFactor(1, 0.01);
    customPlot->plotLayout()->setColumnStretchFactor(1, 0.01);

    customPlot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

