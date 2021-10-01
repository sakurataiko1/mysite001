#ifndef VOXREAD_MAKEGLDATA_H
#define VOXREAD_MAKEGLDATA_H

//#include "qobj3dreader.h" //使わない。　struct QOpenGLTriangle3D使用のためだったが、今はQOpenGLTriangle3D_voxを代わりに使うので不要。

#include <QObject>
#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <QFile>
#include <QRegularExpression>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QDateTime>

//-start- add for vox
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLWindow>
#include <QOpenGLVertexArrayObject>

#include <QOpenGLVertexArrayObject>
#include <QOpenGLVertexArrayObject>
#include <QMouseEvent>
#include <QMouseEventTransition>
#include <QOpenGLShader>
#include <QtOpenGL/QtOpenGL>
#include <QVector3D>
#include <QArrayData>
#include <gl/GL.h>
#include <gl/GL.h>
#include <math.h>
#include <QMatrix4x4>
#include <QScopedPointer>
#include <QElapsedTimer>
//#include <mainwindow.h>
//#inlude  <ui_mainwindow.h>
//#include <vertex.h>
#include <QTextCodec>
// For Japanese
# define TR(s) (QString::fromLocal8Bit(s))
#include <QFile> //kuroda
#include <QFileInfo> //kuroda
#include <tuple> //kuroda 2021.06.xx-01 //2つ以上の帰り値を返すため　std::tuple, std::forward_as_tuple, std::tie で使用する
//-end- add for vox



//-start-　本番時はコメントアウト解除する予定。 qobj3dreader.h と重複しないように一旦コメントアウト。 今後、qobj3dreader.hを分離・使用不要になった時点デコメントアウト解除する。
struct QOpenGLTriangle3D_vox
{
    QVector3D p1;
    QVector3D p2;
    QVector3D p3;
    QVector3D p1Normal;
    QVector3D p2Normal;
    QVector3D p3Normal;
    QVector2D p1UV;
    QVector2D p2UV;
    QVector2D p3UV;

    //-start- add by myk
    QVector3D color;
    //-end-
};
//-end-　本番時はコメントアウト解除する予定。

//class voxRead_makeGLdata
//{
//public:
//    voxRead_makeGLdata();
//};

class voxRead_makeGLdata : public QObject
{
    Q_OBJECT
public:
    explicit voxRead_makeGLdata(QObject *parent = 0);

    //void func_getPointOfMesh_makeGLdata(QVector<QOpenGLTriangle3D> &triangles);
    void func_01main_GL_make_getPointOfMesh(QVector<QOpenGLTriangle3D_vox> &triangles, QString in_voxfilepath);
    void func_vox_get_voxGraffic(QString in_voxfilepath); //voxファイルから、座標とマテリアル情報を取得する　1点ごと
    void zDEBUG_vox_get_voxGraffic_DEBUG01(QString in_voxfilepath); //[DEBUG] 例：　正方形1つ表示 正常表示される.
    void zDEBUG_vox_get_voxGraffic_DEBUG02(QString in_voxfilepath); //[DEBUG] 例：　閉じてない面だけの3D形状　→　裏に色が付かない.　これから対処する　or voxは全て閉じているはずなので問題にならないかもしれない。

    QVector<QVector3D> g_voxXYZVec;
    QVector<QVector3D> g_voxColors;
    QStringList g_voxSurfaceStrList;
    QVector<QVector3D> g_GLColors;

    QVector3D func_GL_defineColor(int input_num); //

    //-start- opengl_myk miwidget.cppから流用
    //voxファイル読み込み用途
    //QStringList g_DrawMeshXYZList; //[DEBUG]用途　使わない。
    //dragFilePathList.clear();　//　使わない。
    QString g_voxfilePath;

    //メッシュサイズ
    float meshsize;
    float meshsize_x;
    float meshsize_y;
    float meshsize_z;

    //総メッシュ数
    int nx,ny,nz;
    unsigned int meshAll;
    void func_vox_getMateNumOfMesh(QString in_voxfilepath); //voxファイルのヘッダー情報読み込み + voxファイルを読み込んで、メッシュごとにマテリアルNo.を割り当てる
    void func_vox_GLadd_checkMateNumOfAdjoinMesh(); //openGL描画用の情報を入れる。　(流用元checkMateNumOfAdjoinMeshでは、通常座標としての記録のみだったが、処理内容変更。）

    QVector<int> mateNoOfMesh;
    //メッシュごとのマテリアルNo
    unsigned int meshNo = 0;

    //メッシュNo. および面情報
    QMultiMap<int,unsigned int> DrawMesh;
    QMultiHash<unsigned int, int> DrawSurface;

    //voxに登録されている全マテリアルのNoと名前
    QList<int> mateNoList;
    QStringList mateNameList;

    //
    //QVector<GLfloat> vertexList;
    //QVector<GLfloat> colorList;
    //QVector<GLfloat> normalList;

    //g_verticesVector.clear();
    //g_colorsVector.clear();
    //QVector<QVector3D> g_verticesVector;
    //QVector<QVector3D> g_colorsVector;
    //-end- 流用元:　opengl_myk miwidget.cpp


signals:

public slots:
    int fileWrteForWindows(QString WriteFilePath, QString WriteMode, QStringList msgList);
    QStringList readTextFileAll(QString fileName);

};

#endif // VOXREAD_MAKEGLDATA_H
