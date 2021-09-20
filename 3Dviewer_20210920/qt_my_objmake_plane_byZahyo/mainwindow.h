#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QVector3D>
#include <QArrayData>
#include <QMultiMap>
#include <QMultiHash>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void fileWriteForWindows(QString WriteFilePath, QString WriteMode, QStringList msgList);
    QStringList readTextFileAll(QString fileName); //ファイル読み込みして、1行ごとにリストに格納する

    void func_objfile_write_plane(QVector3D in_vertex1, QVector3D in_vertex2, QVector3D in_vertex3, QVector3D in_vertex4, int input_matNum, int in_surfaceCnt, QString in_msg1, QString in_surfaceStr); //objファイル書き込み

    QStringList resObjLineList;
    QStringList g_out_obj1; //結果書き出しするファイル内容 (以前のプログラムではファイル書き込みポインタだったが、変更）

private slots:
    void on_pushButton_Run_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
