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
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_graph01_clicked()
{
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
    customPlot->plotLayout()->addElement(0, 1, subLayout); // (Row, Column) = (0,1)にsubLayoutを追加
    subLayout->addElement(0, 0, new QCPLayoutElement); // subLayoutの(Row, Column) = (0,0)にPadding用QCPLayoutElementを
    subLayout->addElement(1, 0, customPlot->legend); // (Row, Column) = (1,0)に凡例（Legend）を追加
    subLayout->addElement(2, 0, new QCPLayoutElement); // 同Paddingを追加
    subLayout->setColumnStretchFactor(0, 0.01);        // subLayoutの横幅はなるべく小さくする
    subLayout->setRowStretchFactor(1, 0.01);           // subLayoutの凡例がはいるRow=1はなるべく小さくする
    customPlot->plotLayout()->setColumnStretchFactor(1, 0.01);

    customPlot->replot();

}

void MainWindow::on_pushButton_graph02_clicked()
{
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

    func_makeGraph01(x1 , y1);
}

void MainWindow::func_makeGraph01( QVector<double> input_x, QVector<double> input_y)
{
    //QCustomPlot *customPlot = ui->customPlot;
    QCPCurve *verticalLine;
    QCPItemTracer *tracer;

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
      x1 = input_x;
      y1 = input_y;
      //x1[0] = -45;
      //y1[0] = -43;
      //x1[1] = 46;
      //y1[1] = 42;
      //x1[2] = -25;
      //y1[2] = -24;
      //x1[3] = -12;
      //y1[3] = 10;
      //x1[4] = 25;
      //y1[4] = 26;

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
