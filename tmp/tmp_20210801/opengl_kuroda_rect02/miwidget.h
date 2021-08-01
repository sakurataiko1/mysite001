#ifndef MIWIDGET_H
#define MIWIDGET_H

#include <myfunction.h> //kuroda

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
#include <vertex.h>

#include <QTextCodec>
// For Japanese
# define TR(s) (QString::fromLocal8Bit(s))

#include <QFile> //kuroda
#include <QFileInfo> //kuroda
#include <tuple> //kuroda 2021.06.xx-01 //2つ以上の帰り値を返すため　std::tuple, std::forward_as_tuple, std::tie で使用する

//#include <QWidget>

//class miwidget : public QWidget
class miWidget : public QOpenGLWidget, public QOpenGLFunctions
{




public:
    //explicit miwidget(QWidget *parent = nullptr);
    explicit miWidget(QWidget *parent = 0);
    ~miWidget();

    //kuroda commentout// void grafficLines();
    void grafficSurface();

    double rotate_y=0;
    double rotate_x=0;
    double rotate_z=0;

    double y_scroll=1.0;

    QString voxfilePath;

    QStringList g_DrawMeshXYZList;


    //kuroda commentout//void initializeGL() Q_DECL_OVERRIDE;
    //kuroda commentout//void resizeGL(int w, int h)Q_DECL_OVERRIDE;
    //kuroda commentout//void paintGL()Q_DECL_OVERRIDE;

    //kuroda commentout//void dragEnterEvent(QDragEnterEvent *e) Q_DECL_OVERRIDE;
    //kuroda commentout//void dropEvent(QDropEvent *e) Q_DECL_OVERRIDE;

















private:






    //メッシュサイズ
    float meshsize;
    float meshsize_x;
    float meshsize_y;
    float meshsize_z;

    //総メッシュ数
    int nx,ny,nz;
    unsigned int meshAll;

    QColor faceColors[20];

    float normalize;

    QStringList dragFilePathList;
    int paintExeFlag;

    int WIDTH = 700;
    int HEIGHT = 700;

































   QVector<int> mateNoOfMesh;
   //メッシュごとのマテリアルNo
   unsigned int meshNo = 0;



   //voxに登録されている全マテリアルのNoと名前
   QList<int> mateNoList;
   QStringList mateNameList;




   //メッシュNo. および面情報
   QMultiMap<int,unsigned int> DrawMesh;
   QMultiHash<unsigned int, int> DrawSurface;


   //GLSL
   int verticies_cnt=0;



   QVector<GLfloat> vertexList;
   QVector<GLfloat> colorList;
   QVector<GLfloat> normalList;











   QVector3D* m_vertices = new QVector3D[verticies_cnt];
   QVector<QVector3D> g_verticesVector; //kuroda
   QVector<QVector3D> g_colorsVector; //kuroda

//-start- kuroda commentout
//   QOpenGLBuffer m_position_vbo;
//   QOpenGLBuffer m_color_vbo;
//   QOpenGLVertexArrayObject m_vao;

//   QScopedPointer<QOpenGLShaderProgram> m_program;
//-end- kuroda commentout

//   //attribute
   int m_vertexLocation;
   int m_colorLocation;
   int m_normalLocation;

   //uniform
   int m_mvpmatrixLocation;
   int m_invmatrixLocation;
   int m_lightDirectionLocation;

   QMatrix4x4 mMatrix;
   QMatrix4x4 vMatrix;
   QMatrix4x4 mvpMatrix;
   QMatrix4x4 invMatrix;
   QMatrix4x4 pMatrix;

   GLfloat aspectRatio;
   GLfloat widgetSizeX;
   GLfloat widgetSizeY;

















public slots:
    void fileWrteForWindows(QString WriteFilePath, QString WriteMode, QStringList msgList);
    QStringList readTextFileAll(QString fileName);
    void readTextFileLine(QString fileName);

    //kuroda commentout//void clearFrame();





//public slots:  //元はprivate slots:　だったが、 public slots とする。

    void drawSurfaceOfMesh(int mateNo);

    void getMateNumOfMesh();
    void getPointOfMesh(int i, int j, int k, int surfaceNo, int mateNo);
    QList<int> getXYZ(unsigned int meshNo);

    void checkMateNumOfAdjoinMesh();

    //QVector<GLfloat> func_get_voxGraffic(QString in_voxfilepath, QString mode); //[DEBU]kuroda　shaderで描くための座標・色設定情報を関数呼び出し先にリターンする
    QVector<QVector3D> func_get_voxGraffic(QString in_voxfilepath, QString mode); //[DEBU]kuroda　shaderで描くための座標・色設定情報を関数呼び出し先にリターンする
    void func_getPointOfMesh_new(int i, int j, int k, int surfaceNo, int input_MateNo); //kuroda　もとのgetPointOfMesh 関数から変更

//signals:

};

#endif // MIWIDGET_H
