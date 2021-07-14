//#include "window.h"
//#include "ui_window.h"

//Window::Window(QWidget *parent)
//    : QWidget(parent)
//    , ui(new Ui::Window)
//{
//    ui->setupUi(this);
//}

//Window::~Window()
//{
//    delete ui;
//}

// window.cpp

#include <QtWidgets>
#include "window.h"
#include "ui_window.h"

#include "myglwidget.h"

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    connect(ui->myGLWidget, SIGNAL(xRotationChanged(int)), ui->rotXSlider, SLOT(setValue(int)));
    connect(ui->myGLWidget, SIGNAL(yRotationChanged(int)), ui->rotYSlider, SLOT(setValue(int)));
    connect(ui->myGLWidget, SIGNAL(zRotationChanged(int)), ui->rotZSlider, SLOT(setValue(int)));

}

Window::~Window()
{
    delete ui;
}

void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}



void Window::on_pushButton_DEBUG_clicked()
{
    ui->myGLWidget->func_DEBUG_kuroda();
}

void Window::on_pushButton_voxpathSelect_clicked()
{
    QString loadfileName = "";
    QStringList tmpStringList;
    QString loadfileNameBefore;
    QString beforefilename , beforefilepath;
    QString tmpDirPath;

    //tmpDirPath = "Desktop";
    //loadfileName = QFileDialog::getOpenFileName(this, tr("Select file"), tmpDirPath, tr("text file (*.txt)"));
    //if(loadfileName.isEmpty() == 1 ){return;} // ファイル選択でキャンセルボタンが押されたら, そのまま終了。

    //既にloadされているファイルがある場合はそのファイルがあるフォルダをファイル選択ダイアログの起点フォルダとする
    tmpDirPath =  "Desktop";
    if(ui->lineEdit_voxpath->text() != ""){
        tmpDirPath = QFileInfo(ui->lineEdit_voxpath->text()).absolutePath();
    }
    loadfileName = QFileDialog::getOpenFileName(this, tr("Select file"), tmpDirPath, tr("text file (*.txt)"));
    if(loadfileName.isEmpty() == 1 ){return;} // ファイル選択でキャンセルボタンが押されたら, そのまま終了。
    ui->lineEdit_voxpath->setText(loadfileName);

}

void Window::on_pushButton_voxpathLoad_clicked()
{
    //マテリアルテーブルへのセット
    //QStringList lineList = func_getMaterialfromVoxPath(filepath); //ファイルを開いて material名、番号を取得する
    //func_set_tableMaterial(lineList); //materialテーブルに反映
    //openGL widget画面に表示する
    ui->myGLWidget->func_load_voxfile(ui->lineEdit_voxpath->text());
}

