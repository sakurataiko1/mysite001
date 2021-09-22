#include "miwidget.h"
#include <QMouseEvent>
#include <QMouseEventTransition>
#include <qmouseeventtransition.h>
#include <QSurfaceFormat>
//kuroda commentout//#include <mainwindow.h>
//kuroda commentout//#include <ui_mainwindow.h>
#include <GL/GLU.h>
#include <gl/GL.h>

#include <QScopedPointer>

//for Drag&Drop
#include <QMimeData>

//ProgressBar
#include <QProgressBar>
#include <QProgressDialog>

//for Japanese
#include <QTextCodec>


#include <QString> //2021.06.xx-01
#include <tuple>

#define NA(i,j,k) (i)*ny*nz+(j)*nz+(k)


miWidget::miWidget(QWidget *parent)
    :QOpenGLWidget(parent)
{
     paintExeFlag = 0;
}

miWidget::~miWidget(){

    //-start- kuroda commentout
//     m_program->disableAttributeArray(m_vertexLocation);
//     m_program->disableAttributeArray(m_colorLocation);
//     m_program->disableAttributeArray(m_normalLocation);
//     m_program->release();
    //-end- kuroda commentout

}

//void miWidget::clearFrame()
//{
//     initializeGL();
//}

//void miWidget::initializeGL()
//{
//     //初期化(OpenGL APIコール前に必要)
//     initializeOpenGLFunctions();

//     //shader------------------------------
//     m_program.reset(new QOpenGLShaderProgram(this));
//     m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
//              "attribute vec3 position;\n"
//              "attribute vec3 sourceColor;\n"
//              "attribute vec3 normal;\n"
//              "uniform mat4 mvpMatrix;\n"
//              "uniform mat4 invMatrix;\n"
//              "uniform vec3 lightDirection;\n"

//              "uniform mat4 modelViewerpMatrix;\n"
//              "uniform mat4 projectionMatrix;\n"
//              "varying vec4 color;\n"
//              "varying vec4 vColor;\n"

//              "void main()\n"
//              "{\n"
//              "  color = vec4(sourceColor, 1.0);\n"
//              "  vec3 invLight = normalize(invmatrix *vec4(lightDirection, 0.0)).xyz;\n"
//              "  float diffuse = clamp(dot(normal, invLight), 0.1, 1.0);\n"
//              "}");


//      m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,
//               "varying vec4 vColor;\n"
//               "void main()\n"
//               "{\n"
//               "gl_FragColor = vColor;\n"
//               "}");

//      m_program->link();
//      m_program->bind();

//      //attribute
//      m_vertexLocation = m_program->attributeLocation("position");
//      m_colorLocation = m_program->attributeLocation("sourceColor");
//      m_normalLocation = m_program->attributeLocation("normal");

//      //uniform
//      m_mvpmatrixLocation = m_program->uniformLocation("mvpMatrix");
//      m_mvpmatrixLocation = m_program->uniformLocation("invMatrix");
//      m_mvpmatrixLocation = m_program->uniformLocation("lightDirection");

//}


//void miWidget::resizeGL(int w, int h)
//{
//     //ビューポート変換　左下隅の座標(x), (y), ウィンドウ幅(W), 高さ(H)
//    glViewport(0, 0, w, h);
//    widgetSizeX = GLfloat(w);
//    widgetSizeX = GLfloat(h);

//    aspectRatio = qreal(w)/qreal(h ? h : 1);

//}


//void miWidget::paintGL()
//{
//    QVector<GLfloat> lightDirection = {-0.5f, 0.5f, 0.5f};

//    if(paintExeFlag == 1){
//        //座標読み込み
//        grafficSurface();

//        rotate_x = 0.0f;
//        rotate_y = 0.0f;

//        mMatrix = QMatrix4x4(); //必ずリセット
//        mMatrix.translate(QVector3D(0.0, 0.0, -0.5));
//        mMatrix.rotate(rotate_x,rotate_y,rotate_z,0.0f);

//        vMatrix = QMatrix4x4();
//        vMatrix.lookAt(QVector3D(0.0, 0.0, 2.0), QVector3D(0, 0, 0), QVector3D(0, 1, 0));

//        pMatrix = QMatrix4x4();
//        pMatrix.setToIdentity();
//        pMatrix.perspective(45, aspectRatio, 0.1f, 100.0f);

//        mvpMatrix = pMatrix * vMatrix * mMatrix;

//        invMatrix = mvpMatrix.inverted();

//        //読み込んだ座標からシェーダー、バッファオブジェクトを生成(exeFlat = 1 で実行し、処理終了後 exeFlag = 2 で返す)

//        //Shader Programに渡す値を渡す領域の定義
//        m_program->enableAttributeArray(m_vertexLocation);
//        m_program->enableAttributeArray(m_colorLocation);
//        m_program->enableAttributeArray(m_normalLocation);


//        //Shader Programに頂点配列をセットする
//        m_program->setAttributeArray(m_vertexLocation, vertexList.constData(), 3, 0);
//        m_program->setAttributeArray(m_colorLocation, vertexList.constData(), 3, 0);
//        m_program->setAttributeArray(m_normalLocation, vertexList.constData(), 3, 0);

//        m_program->setUniformValue(m_mvpmatrixLocation, mvpMatrix);
//        m_program->setUniformValue(m_invmatrixLocation, invMatrix);
//        m_program->setUniformValue(m_lightDirectionLocation, lightDirection.at(0), lightDirection.at(1), lightDirection.at(2));

//        m_program->bind();
//        m_program->release();

//        paintExeFlag=2;
//    }
//    //-end- if(paintExeFlag == 1)

//    if(paintExeFlag == 2){
//        paintExeFlag = 3;
//    }

//    if(paintExeFlag == 3){
//        mMatrix = QMatrix4x4();
//        mMatrix.rotate(-rotate_x, -rotate_x, -rotate_z, 0.0f);

//        mvpMatrix = QMatrix4x4();
//        mvpMatrix = pMatrix * vMatrix * mMatrix;


//        //Shader Programに渡す値を渡す領域の定義
//        m_program->setUniformValue(m_mvpmatrixLocation, mvpMatrix);
//        m_program->bind();

//        glDrawArrays(GL_QUADS,0, vertexList.size()/4);
//        glFlush();
//    }
//    //-end- if(paintExeFlag == 3)
//}

//void miWidget::dragEnterEvent(QDragEnterEvent *e)
//{
//    if(e->mimeData()->hasUrls()){
//        e->acceptProposedAction();
//    }
//}

//void miWidget::dropEvent(QDropEvent *e)
//{
//     dragFilePathList.clear();
//     if(e->mimeData()->hasUrls()){
//         foreach (QUrl url, e->mimeData()->urls()){
//             dragFilePathList << url.toLocalFile();
//             qDebug() << url.toLocalFile();
//         }
//     }

//     glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//     mMatrix = QMatrix4x4();
//     mMatrix.setToIdentity();

//     DrawMesh.clear();
//     DrawSurface.clear();
//     mateNoList.clear();
//     mateNoOfMesh.clear();

//     vertexList.clear();
//     colorList.clear();
//     normalList.clear();

//     m_program->disableAttributeArray(m_vertexLocation);
//     m_program->disableAttributeArray(m_colorLocation);
//     m_program->disableAttributeArray(m_normalLocation);

//     m_program->release();

//     //各メッシュの材質No. を取得
//     getMateNumOfMesh();

//     //描画するメッシュの面情報を取得
//     checkMateNumOfAdjoinMesh();

//     //paintGL実行フラグ有効
//     paintExeFlag = 1;

//}

//-start- kuroda commentout for change
//void miWidget::grafficSurface()
//{
//    //多分　参考にしている？ http://www.natural-science.or.jp/article/20091110211125.php
//    //----------------------------------------------------
//    // 物質質感の定義
//    //----------------------------------------------------
//    struct MaterialStruct {
//      GLfloat ambient[4];
//      GLfloat diffuse[4];
//      GLfloat specular[4];
//      GLfloat shininess;
//    };
//    //jade(翡翠)
//    MaterialStruct ms_jade = {
//      {0.135,     0.2225,   0.1575,   1.0},
//      {0.54,      0.89,     0.63,     1.0},
//      {0.316228,  0.316228, 0.316228, 1.0},
//      12.8};
//    //ruby(ルビー)
//    MaterialStruct ms_ruby  = {
//      {0.1745,   0.01175,  0.01175,   1.0},
//      {0.61424,  0.04136,  0.04136,   1.0},
//      {0.727811, 0.626959, 0.626959,  1.0},
//      76.8};

//    //陰影ON-----------------------------
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);//光源0を利用
//    glEnable(GL_CULL_FACE);
//    glDepthFunc(GL_LEQUAL);
//    //-----------------------------------

//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ms_jade.ambient);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ms_jade.diffuse);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ms_jade.specular);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &ms_jade.shininess);

//    drawSurfaceOfMesh(0);

//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ms_ruby.ambient);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ms_ruby.diffuse);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ms_ruby.specular);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &ms_ruby.shininess);

//    drawSurfaceOfMesh(37);

//    for(int i=0; i<mateNoList.size(); i++){
//        drawSurfaceOfMesh(mateNoList.at(i));
//    }
//}
//-end- kuroda commentout for change

void miWidget::grafficSurface(){  //kuroda change-new
    QString outfileDir =  QFileInfo(QFile(voxfilePath)).absolutePath() + "/objfile_" + QFileInfo(QFile(voxfilePath)).fileName();//2021.06.xx-01 for-obj
    QDir dir(outfileDir);
    if(!dir.exists()){ dir.mkpath(outfileDir); } //フォルダがなければ作る

    for(int i=0; i<mateNoList.size(); i++){
        QString outfilePath = outfileDir + "/" + QFileInfo(QFile(voxfilePath)).fileName() + "_" + QString::number(mateNoList.at(i)) + ".obj";
        if(QFile(outfilePath).exists()) { QFile(outfilePath).remove(); }

        drawSurfaceOfMesh(mateNoList.at(i));
    }
}

//-start- kuroda commentout
//void miWidget::grafficLines()
//{
//    glBegin(GL_LINES); // glEnd() と対になる

//    glColor3f(1, 0, 0);
//    glVertex3f(0, 0, 0);
//    glVertex3f(20, 0, 0);

//    glColor3f(1, 1, 0);
//    glVertex3f(0, 0, 0);
//    glVertex3f(0, 20, 0);

//    glColor3f(0, 1, 1);
//    glVertex3f(0, 0, 0);
//    glVertex3f(0, 0, 20);

//    glEnd(); //glBegin() と対になる
//}
//-end- kuroda commentout


void miWidget::drawSurfaceOfMesh(int mateNo) {
    //-start- objファイル作成前準備
    QString outfileDir =  QFileInfo(QFile(voxfilePath)).absolutePath() + "/objfile_" + QFileInfo(QFile(voxfilePath)).fileName();//2021.06.xx-01 for-obj
    QString outfilePath = outfileDir + "/" + QFileInfo(QFile(voxfilePath)).fileName() + "_" + QString::number(mateNo) + ".obj"; //
    if(QFile(outfilePath).exists()) { QFile(outfilePath).remove(); }
//    QFile outfile(outfilePath);
//    if(!outfile.open(QIODevice::WriteOnly| QIODevice::Text)){
//        QMessageBox::information(this, tr("Unable to openfile"), outfile.errorString());
//        return;
//    }
//    QTextStream g_out_obj(&outfile);
    //-end- objファイル作成

    QList<unsigned int> drawMeshList = DrawMesh.values(mateNo);
    int i,j,k;
    i=0;
    j=0;
    k=0;

    int surfaceCnt = 0;
    for(int m=0; m < drawMeshList.size(); m++){
        QList<int> drawSurfaceList = DrawSurface.values(drawMeshList.at(m));
        //qDebug() << "[DEBUG]miWidget.cpp - drawSurfaceOfMesh() m=" << QString::number(m) << "drawMeshList.at(m)= " << drawMeshList.at(m);
        QList<int> meshXYZ = getXYZ(drawMeshList.at(m));
        i = meshXYZ.at(0);
        j = meshXYZ.at(1);
        k = meshXYZ.at(2);

        //座標定義        
        for(int n=0; n< drawSurfaceList.size(); n++){
            //もと//getPointOfMesh(i, j, k, drawSurfaceList.at(n), mateNo);
            func_getPointOfMesh_new(i, j, k, drawSurfaceList.at(n), mateNo, surfaceCnt);
            surfaceCnt = surfaceCnt + 1;
        }
    }
    //outfile.close(); //objファイル書き込み

}

//voxファイルを読み込んで、メッシュごとにマテリアルNo.を割り当てる
void miWidget::getMateNumOfMesh()
{
     //voxfilePath = dragFilePathList.at(0);
     QStringList read_vox = readTextFileAll(voxfilePath);
     qDebug() << "read_vox.size" << read_vox.size();

     int voxflag = 0;

     //初期値
     meshsize = 1.0;

     //進捗表示のバー
//     QProgressDialog pd(this);
//     pd.setRange(0, read_vox.size());
//     pd.setWindowModality(Qt::WindowModal);
//     pd.setLabelText(TR("Getting Material No. of Mesh"));
//     qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
//     if(pd.wasCanceled()){
//         exit(false);
//     }

     for(int line_n=0; line_n < read_vox.size(); line_n++){ //-2; CellData(nx * ny * nz)の次行から読み始めた分の相殺
//       pd.setValue(line_n);
         //if(read_vox.at(line_n).trimmed() == "CellData" ){ continue; }; //kuroda

         //qDebug() << "miWidget::getMateNumOfMesh() read_vox.at(line_n).trimmed()=" << read_vox.at(line_n).trimmed();

         if(read_vox.at(line_n).trimmed()=="CellData"){
             voxflag = 2;
             line_n = line_n + 1;
             //qDebug() << "miWidget::getMateNumOfMesh() CellData voxflag=" << QString::number(voxflag);
         }

         QStringList temp01 = read_vox.at(line_n).split("\t");

         if(voxflag != 2 && temp01.size()>1){ //これがないとプログラムがクラッシュして、立体画面が起動しない
             //メッシュサイズ
             if(temp01.at(1) == "unitlength"){
                 meshsize = temp01.at(0).toFloat();
                 voxflag = 1;
                 line_n = line_n+1;
             }
             //マテリアルNo & 名前
             if(voxflag == 1){
                 QStringList temp02 = read_vox.at(line_n).split("\t");
                 mateNoList << temp02.at(0).toInt();
                 mateNameList << temp02.at(1);
             }
         }

         if(voxflag == 2){
             nx = (int)read_vox.at(line_n).split(" ").at(0).toInt();
             ny = (int)read_vox.at(line_n).split(" ").at(2).toInt();
             nz = (int)read_vox.at(line_n).split(" ").at(4).toInt();
             voxflag = 3;
             line_n = line_n+1;
         }

         if(voxflag == 3 ){
             QStringList temp03 = read_vox.at(line_n).split(" ");
             //qDebug() << "miWidget::getMateNumOfMesh() temp03=" << temp03;
             //materialNoの個数を抽出->cnt
             for(int i=0; i<temp03.size()/2; i++){
                 int cnt = temp03.at(2*i+1).toInt();

                 for(int j=0; j<cnt; j++){
                     mateNoOfMesh << temp03.at(2*i).toInt();
                 }
             }
         }
     }
     //-end- for(int line_n=0; line_n < read_vox.size(); line_n++)

     //プログレスバーのMAXを100にするため
//     pd.setValue(read_vox.size());

     //正規化
     int maxn;

     //xyzメッシュ数最大値取得
     maxn = nx;
     if(ny > maxn){maxn = ny;}
     if(nz > maxn){maxn = nz;}

     //正規化の掛け数抽出
     meshsize = 1.0 / maxn;

     meshsize_x = meshsize;
     meshsize_y = meshsize;
     meshsize_z = meshsize;

}

void miWidget::checkMateNumOfAdjoinMesh()
{
    int i,j,k;
    meshAll = nx*ny*nz;
    unsigned int nowMeshNo = 0;
    unsigned int chkMeshNo = 0;
    int drawMeshFlag;

    //-start- kuroda commentout
    //QProgressDialog pd(this);
    //pd.setRange(0, meshAll/1000);
    //pd.setWindowModality(Qt::WindowModal);
    //pd.setLabelText(TR("Selecting Drawing Mesh"));
    //qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    //if(pd.wasCanceled()){
    //    exit(false);
    //}
    //-end- kuroda commentout

    for(k=0; k<nz; k++){
        for(j=0; j<ny; j++){
            for(i=0; i<nx; i++){
                drawMeshFlag = 0;

                 QString strXYZ = QString::number(i) + "," + QString::number(j) + "," + QString::number(k) ;

                //front
                chkMeshNo = nowMeshNo - nx * ny;
                if(k ==0 || (k !=0) && (mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo])){
                    if(drawMeshFlag == 0){
                        DrawMesh.insert(mateNoOfMesh[nowMeshNo], nowMeshNo);
                        drawMeshFlag = 1;
                        g_DrawMeshXYZList << strXYZ ;
                    }
                    DrawSurface.insert(nowMeshNo, 1);
                }

                //back
                chkMeshNo = nowMeshNo + nx * ny;
                if(k ==nz-1 || (k != nz-1) && (mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo])){
                    if(drawMeshFlag == 0){
                        DrawMesh.insert(mateNoOfMesh[nowMeshNo], nowMeshNo);
                        drawMeshFlag = 1;
                        g_DrawMeshXYZList << strXYZ;
                    }
                    DrawSurface.insert(nowMeshNo, 2);
                }

                //right
                chkMeshNo = nowMeshNo + 1;
                if(i ==nx-1 || (i != nx-1) && (mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo])){
                    if(drawMeshFlag == 0){
                        DrawMesh.insert(mateNoOfMesh[nowMeshNo], nowMeshNo);
                        drawMeshFlag = 1;
                        g_DrawMeshXYZList << strXYZ;
                    }
                    DrawSurface.insert(nowMeshNo, 3);
                }

                //left
                chkMeshNo = nowMeshNo - 1;
                if(i ==0 || (i != 0) && (mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo])){
                    if(drawMeshFlag == 0){
                        DrawMesh.insert(mateNoOfMesh[nowMeshNo], nowMeshNo);
                        drawMeshFlag = 1;
                        g_DrawMeshXYZList << strXYZ;
                    }
                    DrawSurface.insert(nowMeshNo, 4);
                }

                //top
                chkMeshNo = nowMeshNo + nx;
                if(j == ny-1 || (j != ny-1) && (mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo])){
                    if(drawMeshFlag == 0){
                        DrawMesh.insert(mateNoOfMesh[nowMeshNo], nowMeshNo);
                        drawMeshFlag = 1;
                        g_DrawMeshXYZList << strXYZ;
                    }
                    DrawSurface.insert(nowMeshNo, 5);
                }

                //bottom
                chkMeshNo = nowMeshNo - nx;
                if(j == 0 || (j != 0) && (mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo])){
                    if(drawMeshFlag == 0){
                        DrawMesh.insert(mateNoOfMesh[nowMeshNo], nowMeshNo);
                        drawMeshFlag = 1;
                        g_DrawMeshXYZList << strXYZ;
                    }
                    DrawSurface.insert(nowMeshNo, 6);
                }

                nowMeshNo++;

            }//-end- for i
        }//-end- for j
    }//-end- for k

}

QList<int> miWidget::getXYZ(unsigned int meshNo) //1次元リストとしてのインデックス番号の取得？
{
     int i,j,k;
     QList<int> XYZ;

     int nxny = nx * ny;

     int tempxy;
     k = meshNo / nxny;

     tempxy = meshNo % nxny;

     j=tempxy / nx;
     i=tempxy % nx;

     XYZ << i;
     XYZ << j;
     XYZ << k;

     return XYZ;
}


void miWidget::getPointOfMesh(int i, int j, int k, int surfaceNo, int input_MateNo)
{
     QString vertexP;
     QStringList vertexName ;

     myfunction *m_myfunction = new myfunction;
     QVector3D tmpColorVector = m_myfunction->func_defineColor(input_MateNo);

     //1:front 2:back 3:right 4:left 5:top 6:bottom

     //front
     if(surfaceNo == 1){
         vertexName << "A" << "B" << "C" << "D" ;
         //glNormal3f(0.0, 0.0, -1.0)
         for(int n=0; n<4; n++){
             normalList << 0.0;
             normalList << 0.0;
             normalList << 1.0;
         }
     }

     //back
     if(surfaceNo == 2){
         vertexName << "E" << "F" << "G" << "H" ;

         for(int n=0; n<4; n++){
             normalList << 0.0;
             normalList << 0.0;
             normalList << -1.0;
         }
     }

     //right
     if(surfaceNo == 3){
         vertexName << "B" << "F" << "G" << "C" ;

         for(int n=0; n<4; n++){
             normalList << 1.0;
             normalList << 0.0;
             normalList << 0.0;
         }
     }

     //left
     if(surfaceNo == 4){
         vertexName << "E" << "A" << "D" << "H" ;

         for(int n=0; n<4; n++){
             normalList << -1.0;
             normalList << 0.0;
             normalList << 0.0;
         }
     }

     //top
     if(surfaceNo == 5){
         vertexName << "D" << "C" << "G" << "H" ;

         for(int n=0; n<4; n++){
             normalList << 0.0;
             normalList << 1.0;
             normalList << 0.0;
         }
     }

     //bottom
     if(surfaceNo == 6){
         vertexName << "E" << "F" << "B" << "A" ;

         for(int n=0; n<4; n++){
             normalList << 0.0;
             normalList << -1.0;
             normalList << 0.0;
         }
     }

     //指定された面を描画
     GLfloat nowOP_x, nowOP_y, nowOP_z;
     GLfloat x,y,z;
     for(int n=0; n<vertexName.size(); n++){
         //もと:松岡さんより流用//nowOP_x = i*meshsize_x -0.5;
         //もと:松岡さんより流用//nowOP_y = i*meshsize_y -0.5;
         //もと:松岡さんより流用//nowOP_z = i*meshsize_z -0.5;

         //nowOP_x = i*meshsize_x; //kuroda変更　-0.5 では表示が小さすぎになってしまうための対処
         //nowOP_y = j*meshsize_y; //kuroda変更　-0.5 では表示が小さすぎになってしまうための対処
         //nowOP_z = k*meshsize_z; //kuroda変更　-0.5 では表示が小さすぎになってしまうための対処

         vertexP = vertexName.at(n);

         //Aを(0, 0, 0) に設定した場合
         if(vertexP == "A"){ //頂点A(0,0,0)
             x = nowOP_x;
             y = nowOP_y;
             z = nowOP_z;

             m_vertices->operator*=(QVector3D(x,y,z));

             vertexList << x;
             vertexList << y;
             vertexList << z;

             colorList << 1.0f;
             colorList << 0.0f;
             colorList << 0.0f;

             g_verticesVector << QVector3D(x,y,z); //kuroda
             //g_colorsVector << QVector3D(1.0f, 0.0f, 0.0f); //kuroda
             g_colorsVector << tmpColorVector; //kuroda
         }

         if(vertexP == "B"){ //頂点B(1,0,0)
             x = nowOP_x + meshsize_x;
             y = nowOP_y;
             z = nowOP_z;

             m_vertices->operator*=(QVector3D(x,y,z));

             vertexList << x;
             vertexList << y;
             vertexList << z;

             colorList << 1.0f;
             colorList << 0.0f;
             colorList << 0.0f;

             g_verticesVector << QVector3D(x,y,z); //kuroda
             //g_colorsVector << QVector3D(1.0f, 0.0f, 0.0f); //kuroda
             g_colorsVector << tmpColorVector; //kuroda
         }

         if(vertexP == "C"){ //頂点B(1,1,0)
             x = nowOP_x + meshsize_x;
             y = nowOP_y + meshsize_y;
             z = nowOP_z;

             m_vertices->operator*=(QVector3D(x,y,z));

             vertexList << x;
             vertexList << y;
             vertexList << z;

             colorList << 1.0f;
             colorList << 0.0f;
             colorList << 0.0f;

             g_verticesVector << QVector3D(x,y,z); //kuroda
             //g_colorsVector << QVector3D(1.0f, 0.0f, 0.0f); //kuroda
             g_colorsVector << tmpColorVector; //kuroda
         }

         if(vertexP == "D"){ //頂点D(0,1,0)
             x = nowOP_x;
             y = nowOP_y + meshsize_y;
             z = nowOP_z;

             m_vertices->operator*=(QVector3D(x,y,z));

             vertexList << x;
             vertexList << y;
             vertexList << z;

             colorList << 1.0f;
             colorList << 0.0f;
             colorList << 0.0f;

             g_verticesVector << QVector3D(x,y,z); //kuroda
             //g_colorsVector << QVector3D(1.0f, 0.0f, 0.0f); //kuroda
             g_colorsVector << tmpColorVector; //kuroda
         }

         if(vertexP == "E"){ //頂点E(0,0,1)
             x = nowOP_x;
             y = nowOP_y;
             z = nowOP_z - meshsize_z;

             m_vertices->operator*=(QVector3D(x,y,z));

             vertexList << x;
             vertexList << y;
             vertexList << z;

             colorList << 1.0f;
             colorList << 0.0f;
             colorList << 0.0f;

             g_verticesVector << QVector3D(x,y,z); //kuroda
             //g_colorsVector << QVector3D(1.0f, 0.0f, 0.0f); //kuroda
             g_colorsVector << tmpColorVector; //kuroda
         }

         if(vertexP == "F"){ //頂点F(1,0,1)
             x = nowOP_x + meshsize_x;
             y = nowOP_y;
             z = nowOP_z - meshsize_z;

             m_vertices->operator*=(QVector3D(x,y,z));

             vertexList << x;
             vertexList << y;
             vertexList << z;

             colorList << 1.0f;
             colorList << 0.0f;
             colorList << 0.0f;

             g_verticesVector << QVector3D(x,y,z); //kuroda
             //g_colorsVector << QVector3D(1.0f, 0.0f, 0.0f); //kuroda
             g_colorsVector << tmpColorVector; //kuroda
         }

         if(vertexP == "G"){ //頂点G(1,1,1)
             x = nowOP_x + meshsize_x;
             y = nowOP_y + meshsize_y;
             z = nowOP_z - meshsize_z;

             m_vertices->operator*=(QVector3D(x,y,z));

             vertexList << x;
             vertexList << y;
             vertexList << z;

             colorList << 1.0f;
             colorList << 0.0f;
             colorList << 0.0f;

             g_verticesVector << QVector3D(x,y,z); //kuroda
             //g_colorsVector << QVector3D(1.0f, 0.0f, 0.0f); //kuroda
             g_colorsVector << tmpColorVector; //kuroda
         }

         if(vertexP == "H"){ //頂点H(0,1,1)
             x = nowOP_x;
             y = nowOP_y + meshsize_y;
             z = nowOP_z - meshsize_z;

             m_vertices->operator*=(QVector3D(x,y,z));

             vertexList << x;
             vertexList << y;
             vertexList << z;

             colorList << 1.0f;
             colorList << 0.0f;
             colorList << 0.0f;

             g_verticesVector << QVector3D(x,y,z); //kuroda
             //g_colorsVector << QVector3D(1.0f, 0.0f, 0.0f); //kuroda
             g_colorsVector << tmpColorVector; //kuroda
         }
     }//-end- for(int n=0; n<vertexName.size(); n++)
}

//ファイル書き込み(windowsで使うファイル用)
void miWidget::fileWrteForWindows(QString WriteFilePath, QString WriteMode, QStringList msgList)
{
     QFile file(WriteFilePath);
     if(WriteMode == "Append"){
         if(!file.open(QIODevice::Append| QIODevice::Text)){
             QMessageBox::information(this, tr("Unable to openfile"), file.errorString());
             return;
         }
     } else {
         if(!file.open(QIODevice::WriteOnly| QIODevice::Text)){
             QMessageBox::information(this, tr("Unable to openfile"), file.errorString());
             return;
         }
     }

     QTextStream out(&file);
     for (int n=0; n<msgList.size(); n++){
         out << msgList.at(n) << endl;
     }
     file.close();
}

QStringList miWidget::readTextFileAll(QString fileName)
{
    QStringList lines;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)){
        QString errStr =  "file open error:" + file.errorString();
        qDebug() << errStr;
        //return(lines);
    }
    QTextStream in(&file);
    QString inStr = in.readAll();
    file.close();

    //voxファイルのLF改行に対応
    //QStringList lines = inStr.split("\r\n");
    lines = inStr.split("\r\n"); //kuroda add
    lines = inStr.split("\n");
    return lines;

}

void miWidget::readTextFileLine(QString fileName)
{
     QFile file(fileName);
     if(!file.open(QIODevice::ReadOnly)){
         QString errStr =  "file open error:" + file.errorString();
         qDebug() << errStr;
         return;
     }
     QTextStream in(&file);
     while(! in.atEnd()){
         qDebug() << in.readLine();
     }
     file.close();
}

//QVector<GLfloat> miWidget::func_get_voxGraffic(QString in_voxfilepath, QString mode) //[DEBU]kuroda　shaderで描くための座標・色設定情報を関数呼び出し先にリターンする
//QVector<QVector3D>  miWidget::func_get_voxGraffic(QString in_voxfilepath, QString mode)  //[DEBU]kuroda　shaderで描くための座標・色設定情報を関数呼び出し先にリターンする
//{
//    g_DrawMeshXYZList.clear(); //[DEBUG]用途
//    dragFilePathList.clear();
//    dragFilePathList << in_voxfilepath;
//    voxfilePath = in_voxfilepath;

//    //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//    mMatrix = QMatrix4x4();
//    mMatrix.setToIdentity();

//    DrawMesh.clear();
//    DrawSurface.clear();
//    mateNoList.clear();
//    mateNoOfMesh.clear();

//    vertexList.clear();
//    colorList.clear();
//    normalList.clear();

//    g_verticesVector.clear();
//    g_colorsVector.clear();

//    //m_program->disableAttributeArray(m_vertexLocation);
//    //m_program->disableAttributeArray(m_colorLocation);
//    //m_program->disableAttributeArray(m_normalLocation);
//    //
//    //m_program->release();

//    //各メッシュの材質No. を取得
//    getMateNumOfMesh();
//    QList<int> tmpQList;
//    for(int i=0; i<mateNoOfMesh.size(); i++ ){ tmpQList << mateNoOfMesh[i]; } //[DEBUG]kuroda qDebug表示のため、QListに代入する。
//    //qDebug() << "[DEBUG]01 miwidget.cpp-func_get_voxGraffic  mateNoOfMesh size=" << QString::number(mateNoOfMesh.size()) << ""  << tmpQList;

//    //描画するメッシュの面情報を取得
//    checkMateNumOfAdjoinMesh();
//    qDebug() << "[DEBUG]01 miwidget.cpp-func_get_voxGraffic DrawMesh=" << DrawMesh;
//    qDebug() << "[DEBUG]01 miwidget.cpp-func_get_voxGraffic DrawSurface=" << DrawSurface;

//    //paintGL実行フラグ有効
//    paintExeFlag = 1;

//    grafficSurface(); //voxから shaderで描くための図形取得　vertexList, colorList (normalListも？？）

//    //qDebug() << "[DEBUG]02 miwidget.cpp-func_get_voxGraffic  g_verticesVector=" << g_verticesVector;
//    //qDebug() << "[DEBUG]02func_get_voxGraffic.cpp g_colorsVector=" << cg_colorsVector;

//    QString WriteFilePath =  QFileInfo(voxfilePath).absolutePath() + "/log_DrawMeshXYZList.txt";
//    QString WriteFileMode = "WriteOnly";
//    //qDebug() << "[DEBUG] miWidget.cpp-func_get_voxGraffic write-log-DrawMeshXYZList path=" << WriteFilePath;
//    fileWrteForWindows(WriteFilePath, WriteFileMode, g_DrawMeshXYZList);

//    if(mode == "color"){
//        return g_colorsVector; //QVector<GLfloat> colorList;
//    } else {
//        return g_verticesVector;   //QVector<GLfloat> vertexList;
//    }

//}

//vertices と colors をまとめて返値する　→ tuple を使う　2021.06.xx-01
std::tuple<QVector<QVector3D>, QVector<QVector3D>> miWidget::func_get_voxGraffic(QString in_voxfilepath, QString mode)  //kuroda　shaderで描くための座標・色設定情報を関数呼び出し先にリターンする
{
    g_DrawMeshXYZList.clear(); //[DEBUG]用途
    dragFilePathList.clear();
    dragFilePathList << in_voxfilepath;
    voxfilePath = in_voxfilepath;

    //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    mMatrix = QMatrix4x4();
    mMatrix.setToIdentity();

    DrawMesh.clear();
    DrawSurface.clear();
    mateNoList.clear();
    mateNoOfMesh.clear();

    vertexList.clear();
    colorList.clear();
    normalList.clear();

    g_verticesVector.clear();
    g_colorsVector.clear();

    //m_program->disableAttributeArray(m_vertexLocation);
    //m_program->disableAttributeArray(m_colorLocation);
    //m_program->disableAttributeArray(m_normalLocation);
    //
    //m_program->release();

    //各メッシュの材質No. を取得
    qDebug() << "[DEBUG]-start- getMateNumOfMesh() " + QDateTime::currentDateTime().toString("hh:mm:ss");
    getMateNumOfMesh();
    qDebug() << "[DEBUG]-end- getMateNumOfMesh() " + QDateTime::currentDateTime().toString("hh:mm:ss");
    //QList<int> tmpQList;
    //for(int i=0; i<mateNoOfMesh.size(); i++ ){ tmpQList << mateNoOfMesh[i]; } //[DEBUG]kuroda qDebug表示のため、QListに代入する。
    //qDebug() << "[DEBUG]01 miwidget.cpp-func_get_voxGraffic  mateNoOfMesh size=" << QString::number(mateNoOfMesh.size()) << ""  << tmpQList;

    //描画するメッシュの面情報を取得
    qDebug() << "[DEBUG]-start- checkMateNumOfAdjoinMesh() " + QDateTime::currentDateTime().toString("hh:mm:ss");
    checkMateNumOfAdjoinMesh();
    qDebug() << "[DEBUG]-end- checkMateNumOfAdjoinMesh() " + QDateTime::currentDateTime().toString("hh:mm:ss");
    //qDebug() << "[DEBUG]01 miwidget.cpp-func_get_voxGraffic DrawMesh=" << DrawMesh;
    //qDebug() << "[DEBUG]01 miwidget.cpp-func_get_voxGraffic DrawSurface=" << DrawSurface;

    //paintGL実行フラグ有効
    paintExeFlag = 1;

    //voxから shaderで描くための図形取得
    qDebug() << "[DEBUG]-start- grafficSurface() " + QDateTime::currentDateTime().toString("hh:mm:ss");
    grafficSurface(); //voxから shaderで描くための図形取得　vertexList, colorList (normalListも？？）
    qDebug() << "[DEBUG]-end- grafficSurface() " + QDateTime::currentDateTime().toString("hh:mm:ss");

    //qDebug() << "[DEBUG]02 miwidget.cpp-func_get_voxGraffic  g_verticesVector=" << g_verticesVector;
    //qDebug() << "[DEBUG]02func_get_voxGraffic.cpp g_colorsVector=" << cg_colorsVector;

//    QString WriteFilePath =  QFileInfo(voxfilePath).absolutePath() + "/log_DrawMeshXYZList.txt";
//    QString WriteFileMode = "WriteOnly";
//    qDebug() << "[DEBUG] miWidget.cpp-func_get_voxGraffic write-log-DrawMeshXYZList path=" << WriteFilePath;
//    fileWrteForWindows(WriteFilePath, WriteFileMode, g_DrawMeshXYZList);

//    if(mode == "color"){
//        return g_colorsVector; //QVector<GLfloat> colorList;
//    } else {
//        return g_verticesVector;   //QVector<GLfloat> vertexList;
//    }

      //2021.06.xx-01
      return std::forward_as_tuple(g_verticesVector, g_colorsVector);

}



void miWidget::func_getPointOfMesh_new(int in_i, int in_j, int in_k, int surfaceNo, int input_MateNo, int in_surfaceCnt) //kuroda　もとのgetPointOfMesh 関数から変更
{
    //qDebug() << "[DEBUG]miWidget.cpp-func_getPointOfMesh_new MateNo=" << input_MateNo << " surfaceNo " << surfaceNo  << " in_i=" << in_i << " in_j=" << in_j << " in_k=" << in_k ;

//    //-start- objファイル作成前準備
//    QString outfileDir =  QFileInfo(QFile(voxfilePath)).absolutePath() + "/objfile_" + QFileInfo(QFile(voxfilePath)).fileName() ;//2021.06.xx-01 for-obj
//    QString outfilePath = outfileDir + "/" + QFileInfo(QFile(voxfilePath)).fileName() + "_" + QString::number(input_MateNo) + ".obj"; //
//    QFile outfile(outfilePath);
//    if(!outfile.open(QIODevice::Append | QIODevice::Text)){
//        QMessageBox::information(this, tr("Unable to openfile"), outfile.errorString());
//        return;
//    }
//    QTextStream g_out_obj(&outfile);

//    //-end- objファイル作成

    QString vertexP;
    QStringList vertexName ;

    myfunction *m_myfunction = new myfunction;
    QVector3D tmpColorVector = m_myfunction->func_defineColor(input_MateNo);

    //1:front 2:back 3:right 4:left 5:top 6:bottom

    //頂点の定義
    //   通常座標　と openGLでは違う。　openGLの座標で定義する
    //   通常座標　　　　　FRONT-XY軸:　A=左下　B：右下 C:右上　D:左上　　　　　　　　　　　　　　　　 / BACK-XY軸:　A=左下　B：右下 C:右上　D:左上
    //   通常座標　　　　　FRONT-XY軸: A(0, 0, 0) B(0, 1, 0) C(0, 1, 1) D(0, 0, 1) / BACK-XY軸: A(0, 0, 1) B(0, 1, 1) C(0, 1, 1) D(0, 1, 0)
    //   openGL座標標　FRONT-XY軸: A(0, 0, 0) B(0, 1, 0) C(0, 1, 1) D(0, 0, 1) / BACK-XY軸: A(0, 0, 1) B(0, 1, 1) C(0, 1, 1) D(0, 1, 0)
    //      ※ ①openGL座標では (通常X, 通常-Z, 通常Y) 2番目は上下方向。　3番目は奥行きで。順番が通常と逆。
    //      ※　②openGL座標では　3番目の通常Yは奥行きで手前が＋で後ろがーなので通常座標と+-が逆

    GLfloat nowOP_x, nowOP_y , nowOP_z;
    //GLfloat x,y,z;
    //nowOP_x = in_i * meshsize_x -0.5;
    //nowOP_y = in_j * meshsize_y -0.5;
    //nowOP_z = in_k * meshsize_z -0.5;

    nowOP_x = in_i * meshsize_x; //kuroda変更　-0.5 では表示が小さすぎになってしまうための対処
    nowOP_y = in_j * meshsize_y; //kuroda変更　-0.5 では表示が小さすぎになってしまうための対処
    nowOP_z = in_k * meshsize_z; //kuroda変更　-0.5 では表示が小さすぎになってしまうための対処

    // 1メッシュ立方体の頂点座標を定義する。
    QVector3D vertexA = QVector3D(nowOP_x, nowOP_y, nowOP_z);
    QVector3D vertexB = QVector3D(nowOP_x + meshsize_x, nowOP_y, nowOP_z);
    QVector3D vertexC = QVector3D(nowOP_x + meshsize_x, nowOP_y + meshsize_y, nowOP_z);
    QVector3D vertexD = QVector3D(nowOP_x , nowOP_y + meshsize_y, nowOP_z);
    QVector3D vertexE = QVector3D(nowOP_x, nowOP_y, nowOP_z - meshsize_z);
    QVector3D vertexF = QVector3D(nowOP_x + meshsize_x, nowOP_y, nowOP_z - meshsize_z);
    QVector3D vertexG = QVector3D(nowOP_x + meshsize_x, nowOP_y + meshsize_y, nowOP_z - meshsize_z);
    QVector3D vertexH = QVector3D(nowOP_x , nowOP_y + meshsize_y, nowOP_z - meshsize_z);

    //1つの正方形平面を作る。　(openGLはすべての図形を 三角形で描くため、２つの三角形で1つの正方形平面を作る。)
    //if(surfaceNo == 1){ //Front
    if(surfaceNo == 2){ //glFront 2021.06.xx-01変更  checkMate関数では通常座標（Y:奥行　手前が-,奥が+)としているが、ここではopenGL用（glZ前が-, 奥が+で描画するための変更）
        g_verticesVector << vertexA; //１つ目の三角形
        g_verticesVector << vertexB;
        g_verticesVector << vertexC;
        g_verticesVector << vertexC; //2つ目の三角形
        g_verticesVector << vertexD;
        g_verticesVector << vertexA;

        for(int n=1; n<=6; n++){
            g_colorsVector << tmpColorVector; // 各頂点6つ分の色定義
        }


        //objファイル書き込み
        QString tmpmsg = "# MateNo=" + QString::number(input_MateNo) + " surfaceNo " + QString::number(surfaceNo)  + " in_i=" + QString::number(in_i) + " in_j=" + QString::number(in_j) + " in_k=" + QString::number(in_k) + " in_surfacecnt=" + QString::number(in_surfaceCnt);
        func_objfile_write(input_MateNo, in_surfaceCnt, tmpmsg ,vertexD, vertexA, vertexC, vertexB);

//        //例 FRONT
//        //mtllib sample_plane_front_blender.mtl
//        //o Plane
//        //v -1.000000 1.000000 1.000000
//        //v -1.000000 -1.000000 1.000000
//        //v 1.000000 1.000000 1.000000
//        //v 1.000000 -1.000000 1.000000
//        g_out_obj << "#" << endl;
//        g_out_obj << "o Plane." + QString::number(in_surfaceCnt) +  "\n";
//        //objでは、(x,y,z) 水平：Xは小さいほうから、奥行Zは大きい方から。高さYはx,z に合わせて。
//        g_out_obj << "v " << vertexD.x() << " " << vertexD.y() << " " << vertexD.z() <<endl; //objの場合↑とは描き方が違うので注意すること　objテキストファイルに書き出すは4頂点だけ
//        g_out_obj << "v " << vertexA.x() << " " << vertexA.y() << " " << vertexA.z() <<endl; //頂点順番はこれから修正する
//        g_out_obj << "v " << vertexC.x() << " " << vertexC.y() << " " << vertexC.z() <<endl;
//        g_out_obj << "v " << vertexB.x() << " " << vertexB.y() << " " << vertexB.z() <<endl;
//        //vt,vn,s行：固定
//        g_out_obj << "vt 0.000000 0.000000" << endl;
//        g_out_obj << "vt 1.000000 0.000000" << endl;
//        g_out_obj << "vt 1.000000 1.000000" << endl;
//        g_out_obj << "vt 0.000000 1.000000" << endl;
//        g_out_obj << "vn 0.0000 1.0000 0.0000" << endl;
//        g_out_obj << "s off"<< endl;
//        //f行：可変。Planeごとにカウントアップ必要。
//        //g_out_obj << "f 1/1/1 2/2/1 4/3/1"<< endl; //D A B
//        //g_out_obj << "f 4/3/1 3/4/1 1/1/1"<< endl; //B C D
//        QList<int> vList,vtList;
//        vList << 1 << 2 << 4 << 4 << 3 << 1;
//        vtList << 1 << 2 << 3 << 3 << 4 << 1;
//        for(int i=0; i < vList.count(); i++ ){
//            vList[i] = vList.at(i) + 4 * in_surfaceCnt;
//            vtList[i] = vtList.at(i) + 4 * in_surfaceCnt;
//        }
//        QString tmpstr;
//        g_out_obj << tmpstr.asprintf("f %d/%d/%d %d/%d/%d %d/%d/%d\n",
//                                     vList.at(0), vtList.at(0),in_surfaceCnt,
//                                     vList.at(1), vtList.at(1),in_surfaceCnt,
//                                     vList.at(2), vtList.at(2),in_surfaceCnt);
//        g_out_obj << tmpstr.asprintf("f %d/%d/%d %d/%d/%d %d/%d/%d\n",
//                                     vList.at(3), vtList.at(3),in_surfaceCnt,
//                                     vList.at(4), vtList.at(4),in_surfaceCnt,
//                                     vList.at(5), vtList.at(5),in_surfaceCnt);

       //例 objファイル書式　v：可変　vt,vn,s行：固定 f行：可変。Planeごとにカウントアップ必要。
//1面目 bottom
//                o Plane
//                v -1.000000 0.000000 1.000000
//                v 1.000000 0.000000 1.000000
//                v -1.000000 0.000000 -1.000000
//                v 1.000000 0.000000 -1.000000
//                vt 0.000000 0.000000
//                vt 1.000000 0.000000
//                vt 1.000000 1.000000
//                vt 0.000000 1.000000
//                vn 0.0000 1.0000 0.0000
//                s off
//                f 1/1/1 2/2/1 4/3/1
//                f 4/3/1 3/4/1 1/1/1
//2面目 Right
//                o Plane.001
//                v 2.000000 1.000000 1.000000
//                v 2.000000 -1.000000 1.000000
//                v 2.000000 1.000000 -1.000000
//                v 2.000000 -1.000000 -1.000000
//                vt 0.000000 0.000000
//                vt 1.000000 0.000000
//                vt 1.000000 1.000000
//                vt 0.000000 1.000000
//                vn 1.0000 0.0000 0.0000
//                s off
//                #f 5/5/2 6/6/2 8/7/2 7/8/2
//                f 5/5/2 6/6/2 8/7/2
//                f 8/7/2 7/8/2 5/5/2
    }

    //if(surfaceNo == 2){ //Back
    if(surfaceNo == 1){ //glBack 2021.06.xx-01変更  checkMate関数では通常座標（Y:奥行　手前が-,奥が+)としているが、ここではopenGL用（glZ前が-, 奥が+で描画するための変更）

        g_verticesVector << vertexF; //１つ目の三角形
        g_verticesVector << vertexE;
        g_verticesVector << vertexH;
        g_verticesVector << vertexH; //2つ目の三角形
        g_verticesVector << vertexG;
        g_verticesVector << vertexF;

        for(int n=1; n<=6; n++){
            g_colorsVector << tmpColorVector; // 各頂点6つ分の色定義
        }

        //objファイル書き込み
        QString tmpmsg = "# MateNo=" + QString::number(input_MateNo) + " surfaceNo " + QString::number(surfaceNo)  + " in_i=" + QString::number(in_i) + " in_j=" + QString::number(in_j) + " in_k=" + QString::number(in_k) + " in_surfacecnt=" + QString::number(in_surfaceCnt);
        func_objfile_write(input_MateNo, in_surfaceCnt, tmpmsg ,vertexH, vertexE, vertexG, vertexF);

//        //objファイル書き込み
//        //例 BACK
//        //mtllib sample_plane_back_blender.mtl
//        //o Plane
//        //v -1.000000 1.000000 -0.000000
//        //v -1.000000 -1.000000 -0.000000
//        //v 1.000000 1.000000 0.000000
//        //v 1.000000 -1.000000 0.000000
//        g_out_obj << "#" << endl;
//        g_out_obj << "o Plane." + QString::number(in_surfaceCnt) +  "\n";
//        //objでは、(x,y,z) 水平：Xは小さいほうから、奥行Zは大きい方から。高さYはx,z に合わせて。
//        g_out_obj << "v " << vertexH.x() << " " << vertexH.y() << " " << vertexH.z() <<endl; //objの場合↑とは描き方が違うので注意すること　objテキストファイルに書き出すは4頂点だけ
//        g_out_obj << "v " << vertexE.x() << " " << vertexE.y() << " " << vertexE.z() <<endl; //頂点順番はこれから修正する
//        g_out_obj << "v " << vertexG.x() << " " << vertexG.y() << " " << vertexG.z() <<endl;
//        g_out_obj << "v " << vertexF.x() << " " << vertexF.y() << " " << vertexF.z() <<endl;
//        //vt,vn,s行：固定
//        g_out_obj << "vt 0.000000 0.000000" << endl;
//        g_out_obj << "vt 1.000000 0.000000" << endl;
//        g_out_obj << "vt 1.000000 1.000000" << endl;
//        g_out_obj << "vt 0.000000 1.000000" << endl;
//        g_out_obj << "vn 0.0000 1.0000 0.0000" << endl;
//        g_out_obj << "s off"<< endl;
//        //f行：可変。Planeごとにカウントアップ必要。
//        //g_out_obj << "f 1/1/1 2/2/1 4/3/1"<< endl; //H E F
//        //g_out_obj << "f 4/3/1 3/4/1 1/1/1"<< endl; //F G H
//        QList<int> vList,vtList;
//        vList << 1 << 2 << 4 << 4 << 3 << 1;
//        vtList << 1 << 2 << 3 << 3 << 4 << 1;
//        for(int i=0; i < vList.count(); i++ ){
//            vList[i] = vList.at(i) + 4 * in_surfaceCnt;
//            vtList[i] = vtList.at(i) + 4 * in_surfaceCnt;
//        }
//        QString tmpstr;
//        g_out_obj << tmpstr.asprintf("f %d/%d/%d %d/%d/%d %d/%d/%d\n",
//                                     vList.at(0), vtList.at(0),in_surfaceCnt,
//                                     vList.at(1), vtList.at(1),in_surfaceCnt,
//                                     vList.at(2), vtList.at(2),in_surfaceCnt);
//        g_out_obj << tmpstr.asprintf("f %d/%d/%d %d/%d/%d %d/%d/%d\n",
//                                     vList.at(3), vtList.at(3),in_surfaceCnt,
//                                     vList.at(4), vtList.at(4),in_surfaceCnt,
//                                     vList.at(5), vtList.at(5),in_surfaceCnt);


    }

    if(surfaceNo == 3){ //Right
        g_verticesVector << vertexB; //１つ目の三角形
        g_verticesVector << vertexF;
        g_verticesVector << vertexG;
        g_verticesVector << vertexG; //2つ目の三角形
        g_verticesVector << vertexC;
        g_verticesVector << vertexB;

        for(int n=1; n<=6; n++){
            g_colorsVector << tmpColorVector; // 各頂点6つ分の色定義
        }

        //objファイル書き込み
        QString tmpmsg = "# MateNo=" + QString::number(input_MateNo) + " surfaceNo " + QString::number(surfaceNo)  + " in_i=" + QString::number(in_i) + " in_j=" + QString::number(in_j) + " in_k=" + QString::number(in_k) + " in_surfacecnt=" + QString::number(in_surfaceCnt);
        func_objfile_write(input_MateNo, in_surfaceCnt, tmpmsg ,vertexC, vertexB, vertexG, vertexF);

//        //objファイル書き込み
//        //例 Right
////        #mtllib sample_plane_right_blender.mtl
////        o Plane
////        v 1.000000 1.000000 1.000000
////        v 1.000000 -1.000000 1.000000
////        v 1.000000 1.000000 -1.000000
////        v 1.000000 -1.000000 -1.000000
//        //
//        g_out_obj << "#" << endl;
//        g_out_obj << "o Plane." + QString::number(in_surfaceCnt) +  "\n";
//        //objでは、(x,y,z) 水平：Xは小さいほうから、奥行Zは大きい方から。高さYはx,z に合わせて。
//        g_out_obj << "v " << vertexC.x() << " " << vertexC.y() << " " << vertexC.z() <<endl; //objの場合↑とは描き方が違うので注意すること　objテキストファイルに書き出すは4頂点だけ
//        g_out_obj << "v " << vertexB.x() << " " << vertexB.y() << " " << vertexB.z() <<endl; //頂点順番はこれから修正する
//        g_out_obj << "v " << vertexG.x() << " " << vertexG.y() << " " << vertexG.z() <<endl;
//        g_out_obj << "v " << vertexF.x() << " " << vertexF.y() << " " << vertexF.z() <<endl;
//        //vt,vn,s行：固定
//        g_out_obj << "vt 0.000000 0.000000" << endl;
//        g_out_obj << "vt 1.000000 0.000000" << endl;
//        g_out_obj << "vt 1.000000 1.000000" << endl;
//        g_out_obj << "vt 0.000000 1.000000" << endl;
//        g_out_obj << "vn 0.0000 1.0000 0.0000" << endl;
//        g_out_obj << "s off"<< endl;
//        //f行：可変。Planeごとにカウントアップ必要。
//        //g_out_obj << "f 1/1/1 2/2/1 4/3/1"<< endl; //C B F
//        //g_out_obj << "f 4/3/1 3/4/1 1/1/1"<< endl; //F G C
//        QList<int> vList,vtList;
//        vList << 1 << 2 << 4 << 4 << 3 << 1;
//        vtList << 1 << 2 << 3 << 3 << 4 << 1;
//        for(int i=0; i < vList.count(); i++ ){
//            vList[i] = vList.at(i) + 4 * in_surfaceCnt;
//            vtList[i] = vtList.at(i) + 4 * in_surfaceCnt;
//        }
//        QString tmpstr;
//        g_out_obj << tmpstr.asprintf("f %d/%d/%d %d/%d/%d %d/%d/%d\n",
//                                     vList.at(0), vtList.at(0),in_surfaceCnt,
//                                     vList.at(1), vtList.at(1),in_surfaceCnt,
//                                     vList.at(2), vtList.at(2),in_surfaceCnt);
//        g_out_obj << tmpstr.asprintf("f %d/%d/%d %d/%d/%d %d/%d/%d\n",
//                                     vList.at(3), vtList.at(3),in_surfaceCnt,
//                                     vList.at(4), vtList.at(4),in_surfaceCnt,
//                                     vList.at(5), vtList.at(5),in_surfaceCnt);
    }

    if(surfaceNo == 4){ //Left
        g_verticesVector << vertexE; //１つ目の三角形
        g_verticesVector << vertexA;
        g_verticesVector << vertexD;
        g_verticesVector << vertexD; //2つ目の三角形
        g_verticesVector << vertexH;
        g_verticesVector << vertexE;

        for(int n=1; n<=6; n++){
            g_colorsVector << tmpColorVector; // 各頂点6つ分の色定義
         }

        //objファイル書き込み
        QString tmpmsg = "# MateNo=" + QString::number(input_MateNo) + " surfaceNo " + QString::number(surfaceNo)  + " in_i=" + QString::number(in_i) + " in_j=" + QString::number(in_j) + " in_k=" + QString::number(in_k) + " in_surfacecnt=" + QString::number(in_surfaceCnt);
        func_objfile_write(input_MateNo, in_surfaceCnt, tmpmsg ,vertexD, vertexA, vertexH, vertexE);

//        //objファイル書き込み
//        //例 Left
//        //mtllib sample_plane_left_blender.mtl
//        //o Plane
//        //v 0.000000 1.000000 1.000000
//        //v -0.000000 -1.000000 1.000000
//        //v 0.000000 1.000000 -1.000000
//        //v -0.000000 -1.000000 -1.000000
//        //
//        g_out_obj << "#" << endl;
//        g_out_obj << "o Plane." + QString::number(in_surfaceCnt) +  "\n";
//        //objでは、(x,y,z) 水平：Xは小さいほうから、奥行Zは大きい方から。高さYはx,z に合わせて。
//        g_out_obj << "v " << vertexD.x() << " " << vertexD.y() << " " << vertexD.z() <<endl; //objの場合↑とは描き方が違うので注意すること　objテキストファイルに書き出すは4頂点だけ
//        g_out_obj << "v " << vertexA.x() << " " << vertexA.y() << " " << vertexA.z() <<endl; //頂点順番はこれから修正する
//        g_out_obj << "v " << vertexH.x() << " " << vertexH.y() << " " << vertexH.z() <<endl;
//        g_out_obj << "v " << vertexE.x() << " " << vertexE.y() << " " << vertexE.z() <<endl;
//        //vt,vn,s行：固定
//        g_out_obj << "vt 0.000000 0.000000" << endl;
//        g_out_obj << "vt 1.000000 0.000000" << endl;
//        g_out_obj << "vt 1.000000 1.000000" << endl;
//        g_out_obj << "vt 0.000000 1.000000" << endl;
//        g_out_obj << "vn 0.0000 1.0000 0.0000" << endl;
//        g_out_obj << "s off"<< endl;
//        //f行：可変。Planeごとにカウントアップ必要。
//        //g_out_obj << "f 1/1/1 2/2/1 4/3/1"<< endl; //D A E
//        //g_out_obj << "f 4/3/1 3/4/1 1/1/1"<< endl; //E H D
//        QList<int> vList,vtList;
//        vList << 1 << 2 << 4 << 4 << 3 << 1;
//        vtList << 1 << 2 << 3 << 3 << 4 << 1;
//        for(int i=0; i < vList.count(); i++ ){
//            vList[i] = vList.at(i) + 4 * in_surfaceCnt;
//            vtList[i] = vtList.at(i) + 4 * in_surfaceCnt;
//        }
//        QString tmpstr;
//        g_out_obj << tmpstr.asprintf("f %d/%d/%d %d/%d/%d %d/%d/%d\n",
//                                     vList.at(0), vtList.at(0),in_surfaceCnt,
//                                     vList.at(1), vtList.at(1),in_surfaceCnt,
//                                     vList.at(2), vtList.at(2),in_surfaceCnt);
//        g_out_obj << tmpstr.asprintf("f %d/%d/%d %d/%d/%d %d/%d/%d\n",
//                                     vList.at(3), vtList.at(3),in_surfaceCnt,
//                                     vList.at(4), vtList.at(4),in_surfaceCnt,
//                                     vList.at(5), vtList.at(5),in_surfaceCnt);
    }

    if(surfaceNo == 5){ //Top
        g_verticesVector << vertexD; //１つ目の三角形
        g_verticesVector << vertexC;
        g_verticesVector << vertexG;
        g_verticesVector << vertexG; //2つ目の三角形
        g_verticesVector << vertexH;
        g_verticesVector << vertexD;

        for(int n=1; n<=6; n++){
            g_colorsVector << tmpColorVector; // 各頂点6つ分の色定義
        }

        //objファイル書き込み
        QString tmpmsg = "# MateNo=" + QString::number(input_MateNo) + " surfaceNo " + QString::number(surfaceNo)  + " in_i=" + QString::number(in_i) + " in_j=" + QString::number(in_j) + " in_k=" + QString::number(in_k) + " in_surfacecnt=" + QString::number(in_surfaceCnt);
        func_objfile_write(input_MateNo, in_surfaceCnt, tmpmsg ,vertexD, vertexC, vertexH, vertexG);

//        //objファイル書き込み
//        //例 Top
//        //mtllib sample_plane_top_blender.mtl
//        //o Plane
//        //v -1.000000 1.000000 1.000000
//        //v 1.000000 1.000000 1.000000
//        //v -1.000000 1.000000 -1.000000
//        //v 1.000000 1.000000 -1.000000
//        g_out_obj << "#" << endl;
//        g_out_obj << "o Plane." + QString::number(in_surfaceCnt) +  "\n";
//        //objでは、(x,y,z) 水平：Xは小さいほうから、奥行Zは大きい方から。高さYはx,z に合わせて。
//        g_out_obj << "v " << vertexD.x() << " " << vertexD.y() << " " << vertexD.z() <<endl; //objの場合↑とは描き方が違うので注意すること　objテキストファイルに書き出すは4頂点だけ
//        g_out_obj << "v " << vertexC.x() << " " << vertexC.y() << " " << vertexC.z() <<endl; //頂点順番はこれから修正する
//        g_out_obj << "v " << vertexH.x() << " " << vertexH.y() << " " << vertexH.z() <<endl;
//        g_out_obj << "v " << vertexG.x() << " " << vertexG.y() << " " << vertexG.z() <<endl;
//        //vt,vn,s行：固定
//        g_out_obj << "vt 0.000000 0.000000" << endl;
//        g_out_obj << "vt 1.000000 0.000000" << endl;
//        g_out_obj << "vt 1.000000 1.000000" << endl;
//        g_out_obj << "vt 0.000000 1.000000" << endl;
//        g_out_obj << "vn 0.0000 1.0000 0.0000" << endl;
//        g_out_obj << "s off"<< endl;
//        //f行：可変。Planeごとにカウントアップ必要。
//        //g_out_obj << "f 1/1/1 2/2/1 4/3/1"<< endl; //D C G
//        //g_out_obj << "f 4/3/1 3/4/1 1/1/1"<< endl; //G H D
//        QList<int> vList,vtList;
//        vList << 1 << 2 << 4 << 4 << 3 << 1;
//        vtList << 1 << 2 << 3 << 3 << 4 << 1;
//        for(int i=0; i < vList.count(); i++ ){
//            vList[i] = vList.at(i) + 4 * in_surfaceCnt;
//            vtList[i] = vtList.at(i) + 4 * in_surfaceCnt;
//        }
//        QString tmpstr;
//        g_out_obj << tmpstr.asprintf("f %d/%d/%d %d/%d/%d %d/%d/%d\n",
//                                     vList.at(0), vtList.at(0),in_surfaceCnt,
//                                     vList.at(1), vtList.at(1),in_surfaceCnt,
//                                     vList.at(2), vtList.at(2),in_surfaceCnt);
//        g_out_obj << tmpstr.asprintf("f %d/%d/%d %d/%d/%d %d/%d/%d\n",
//                                     vList.at(3), vtList.at(3),in_surfaceCnt,
//                                     vList.at(4), vtList.at(4),in_surfaceCnt,
//                                     vList.at(5), vtList.at(5),in_surfaceCnt);


    }

    if(surfaceNo == 6){ //Bottom
        g_verticesVector << vertexE; //１つ目の三角形
        g_verticesVector << vertexF;
        g_verticesVector << vertexB;
        g_verticesVector << vertexB; //2つ目の三角形
        g_verticesVector << vertexA;
        g_verticesVector << vertexE;

        for(int n=1; n<=6; n++){
            g_colorsVector << tmpColorVector; // 各頂点6つ分の色定義
        }

        for(int n=1; n<=6; n++){
            g_colorsVector << tmpColorVector; // 各頂点6つ分の色定義
        }

        //objファイル書き込み
        QString tmpmsg = "# MateNo=" + QString::number(input_MateNo) + " surfaceNo " + QString::number(surfaceNo)  + " in_i=" + QString::number(in_i) + " in_j=" + QString::number(in_j) + " in_k=" + QString::number(in_k) + " in_surfacecnt=" + QString::number(in_surfaceCnt);
        func_objfile_write(input_MateNo, in_surfaceCnt, tmpmsg ,vertexA, vertexB, vertexE, vertexF);

//        //objファイル書き込み
//        //例 Bottom
//        //mtllib sample_plane_bottom_blender.mtl
//        //o Plane
//        //v -1.000000 0.000000 1.000000
//        //v 1.000000 0.000000 1.000000
//        //v -1.000000 0.000000 -1.000000
//        //v 1.000000 0.000000 -1.000000
//        g_out_obj << "#" << endl;
//        g_out_obj << "o Plane." + QString::number(in_surfaceCnt) +  "\n";
//        //objでは、(x,y,z) 水平：Xは小さいほうから、奥行Zは大きい方から。高さYはx,z に合わせて。
//        g_out_obj << "v " << vertexA.x() << " " << vertexA.y() << " " << vertexA.z() << endl; //objの場合↑とは描き方が違うので注意すること　objテキストファイルに書き出すは4頂点だけ
//        g_out_obj << "v " << vertexB.x() << " " << vertexB.y() << " " << vertexB.z() << endl; //頂点順番はこれから修正する
//        g_out_obj << "v " << vertexE.x() << " " << vertexE.y() << " " << vertexE.z() << endl;
//        g_out_obj << "v " << vertexF.x() << " " << vertexF.y() << " " << vertexF.z() << endl;
//        //vt,vn,s行：固定
//        g_out_obj << "vt 0.000000 0.000000" << endl;
//        g_out_obj << "vt 1.000000 0.000000" << endl;
//        g_out_obj << "vt 1.000000 1.000000" << endl;
//        g_out_obj << "vt 0.000000 1.000000" << endl;
//        g_out_obj << "vn 0.0000 1.0000 0.0000" << endl;
//        g_out_obj << "s off"<< endl;
//        //f行：可変。Planeごとにカウントアップ必要。
//        //g_out_obj << "f 1/1/1 2/2/1 4/3/1"<< endl; //A B F
//        //g_out_obj << "f 4/3/1 3/4/1 1/1/1"<< endl; //F E A
//        QList<int> vList,vtList;
//        vList << 1 << 2 << 4 << 4 << 3 << 1;
//        vtList << 1 << 2 << 3 << 3 << 4 << 1;
//        for(int i=0; i < vList.count(); i++ ){
//            vList[i] = vList.at(i) + 4 * in_surfaceCnt;
//            vtList[i] = vtList.at(i) + 4 * in_surfaceCnt;
//        }
//        QString tmpstr;
//        g_out_obj << tmpstr.asprintf("f %d/%d/%d %d/%d/%d %d/%d/%d\n",
//                                     vList.at(0), vtList.at(0),in_surfaceCnt+1,
//                                     vList.at(1), vtList.at(1),in_surfaceCnt+1,
//                                     vList.at(2), vtList.at(2),in_surfaceCnt+1);
//        g_out_obj << tmpstr.asprintf("f %d/%d/%d %d/%d/%d %d/%d/%d\n",
//                                     vList.at(3), vtList.at(3),in_surfaceCnt+1,
//                                     vList.at(4), vtList.at(4),in_surfaceCnt+1,
//                                     vList.at(5), vtList.at(5),in_surfaceCnt+1);

        //1面目 bottom
        //                o Plane
        //                v -1.000000 0.000000 1.000000
        //                v 1.000000 0.000000 1.000000
        //                v -1.000000 0.000000 -1.000000
        //                v 1.000000 0.000000 -1.000000
        //                vt 0.000000 0.000000
        //                vt 1.000000 0.000000
        //                vt 1.000000 1.000000
        //                vt 0.000000 1.000000
        //                vn 0.0000 1.0000 0.0000
        //                s off
        //                f 1/1/1 2/2/1 4/3/1
        //                f 4/3/1 3/4/1 1/1/1
    }

    //outfile.close(); //objファイル書き込み。

}

void miWidget::func_objfile_write(int input_MateNo, int in_surfaceCnt, QString in_msg1,  QVector3D in_vertex1, QVector3D in_vertex2, QVector3D in_vertex3, QVector3D in_vertex4) //objファイル書き込み
{
    //-start- objファイル作成前準備
    QString outfileDir =  QFileInfo(QFile(voxfilePath)).absolutePath() + "/objfile_" + QFileInfo(QFile(voxfilePath)).fileName() ;//2021.06.xx-01 for-obj
    QString outfilePath = outfileDir + "/" + QFileInfo(QFile(voxfilePath)).fileName() + "_" + QString::number(input_MateNo) + ".obj"; //
    QFile outfile1(outfilePath);
    if(!outfile1.open(QIODevice::Append | QIODevice::Text)){
        QMessageBox::information(this, tr("Unable to openfile"), outfile1.errorString());
        return;
    }
    QTextStream g_out_obj1(&outfile1);
    //-end- objファイル作成

    //qDebug() << "[DEBUG]01miWidget.cpp-func_objfile_write()";

    //objファイル書き込み
    //例 FRONT
    //mtllib sample_plane_front_blender.mtl
    //o Plane
    //v -1.000000 1.000000 1.000000
    //v -1.000000 -1.000000 1.000000
    //v 1.000000 1.000000 1.000000
    //v 1.000000 -1.000000 1.000000
    g_out_obj1 << "# " + in_msg1 << endl;
    g_out_obj1 << "o Plane." + QString::number(in_surfaceCnt) +  "\n";
    //objでは、(x,y,z) 水平：Xは小さいほうから、奥行Zは大きい方から。高さYはx,z に合わせて。
    g_out_obj1 << "v " << in_vertex1.x() << " " << in_vertex1.y() << " " << in_vertex1.z() <<endl; //objの場合↑とは描き方が違うので注意すること　objテキストファイルに書き出すは4頂点だけ
    g_out_obj1 << "v " << in_vertex2.x() << " " << in_vertex2.y() << " " << in_vertex2.z() <<endl; //頂点順番はこれから修正する
    g_out_obj1 << "v " << in_vertex3.x() << " " << in_vertex3.y() << " " << in_vertex3.z() <<endl;
    g_out_obj1 << "v " << in_vertex4.x() << " " << in_vertex4.y() << " " << in_vertex4.z() <<endl;
    //vt,vn,s行：固定
    g_out_obj1 << "vt 0.000000 0.000000" << endl;
    g_out_obj1 << "vt 1.000000 0.000000" << endl;
    g_out_obj1 << "vt 1.000000 1.000000" << endl;
    g_out_obj1 << "vt 0.000000 1.000000" << endl;
    g_out_obj1 << "vn 0.0000 1.0000 0.0000" << endl;
    g_out_obj1 << "s off"<< endl;
    //f行：可変。Planeごとにカウントアップ必要。
    //g_out_obj1 << "f 1/1/1 2/2/1 4/3/1"<< endl; //D A B
    //g_out_obj1 << "f 4/3/1 3/4/1 1/1/1"<< endl; //B C D
    QList<int> vList,vtList;
    vList << 1 << 2 << 4 << 4 << 3 << 1;
    vtList << 1 << 2 << 3 << 3 << 4 << 1;
    for(int i=0; i < vList.count(); i++ ){
        vList[i] = vList.at(i) + 4 * in_surfaceCnt;
        vtList[i] = vtList.at(i) + 4 * in_surfaceCnt;
    }
    QString tmpstr;
    g_out_obj1 << tmpstr.asprintf("f %d/%d/%d %d/%d/%d %d/%d/%d\n",
                                 vList.at(0), vtList.at(0), in_surfaceCnt + 1,
                                 vList.at(1), vtList.at(1), in_surfaceCnt + 1,
                                 vList.at(2), vtList.at(2), in_surfaceCnt + 1);
    g_out_obj1 << tmpstr.asprintf("f %d/%d/%d %d/%d/%d %d/%d/%d\n",
                                 vList.at(3), vtList.at(3), in_surfaceCnt + 1,
                                 vList.at(4), vtList.at(4), in_surfaceCnt + 1,
                                 vList.at(5), vtList.at(5), in_surfaceCnt + 1);

    outfile1.close(); //objファイル書き込み。
}
