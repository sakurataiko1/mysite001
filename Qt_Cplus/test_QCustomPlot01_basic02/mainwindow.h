#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTimer>
#include "qcustomplot.h" // the header file of QCustomPlot. Don't forget to add it to your project, if you use an IDE, so it gets compiled.

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // MainWindow(QWidget *parent = nullptr);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QCustomPlot *wGraphic;
    QCPCurve *verticalLine;
    QCPItemTracer *tracer;

};
#endif // MAINWINDOW_H
