#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include <QVector3D>
#include <QArrayData>
#include <QMultiMap>
#include <QMultiHash>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //-start- miwidget.cppより
//    QString voxfilePath;
//    //メッシュサイズ
//    float meshsize;
//    float meshsize_x;
//    float meshsize_y;
//    float meshsize_z;
//    //総メッシュ数
//    int nx,ny,nz;
//    int meshAll; //unsigned int meshAll;
//    //メッシュNo. および面情報
//    //QMultiMap<int,unsigned int> DrawMesh;
//    //QMultiHash<unsigned int, int> DrawSurface;
//    QMultiMap<int,int> DrawMesh;
//    QMultiHash<int, int> DrawSurface;
//    //voxに登録されている全マテリアルのNoと名前
//    QList<int> mateNoList;
//    QStringList mateNameList;
//    QVector<int> mateNoOfMesh; //voxの全データ部分
//    //メッシュごとのマテリアルNo
//    int  meshNo = 0; //unsigned int meshNo = 0;
//    QStringList g_DrawMeshXYZList;
    //
    void fileWrteForWindows(QString WriteFilePath, QString WriteMode, QStringList msgList);
    QStringList readTextFileAll(QString fileName); //ファイル読み込みして、1行ごとにリストに格納する
    //-end- miwidget.cppより

    int nx, ny, nz, g_nx, g_ny, g_nz;
    int g_meshsize, g_meshsize_x, g_meshsize_y, g_meshsize_z;
    QList<int> g_matNoList;
    QStringList g_matNameList;

     QList<int> mateNoList;

    int ***g_voxDomain;
    //int g_drawMesh3Ary();
    QMultiHash<int, QString> g_drawMeshHash; //例： key=材質ID value=文字列カンマ区切り。メッシュ一列分の直方体：左下始点x1, y1, z1,z1終点x1, y2, z2, 描く面全てFRONTなどの面情報 0-1-2-3-4-5-6 (surfaceNo)

    void func_vox_readHeader();  //データ　3次元配列に格納
    void func_vox_read3Darray(); //voxデータ　3次元配列に格納

    void func_checkMateNumOfAdjoinMesh(); //描画するメッシュの面情報を取得

private slots:
    void on_pushButton_load_clicked();
    void on_pushButton_select_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
