#include "voxRead_makeGLdata.h"

//org//voxRead_makeGLdata::voxRead_makeGLdata()
voxRead_makeGLdata::voxRead_makeGLdata(QObject *parent) : QObject(parent)
{

}

void voxRead_makeGLdata::func_01main_GL_make_getPointOfMesh(QVector<QOpenGLTriangle3D_vox> &triangles, QString in_voxfilepath)
{
    //■ GL描画用形式への置き換え　通常図形=正方形平面(座標4点）→ GL描画用形式 = 3角形2個(座標6点)　反時計回り座標
    //
    //■ 通常座標 (x, y, z) のまま、設定すると　openGLでは、Y軸と、Z軸が反対に表示されてしまうため
    //  GL座標 (x, -y, -z) として入れなおして計算する
    //

    //openGLでの描画単位=1つの三角形ごとの情報作成する。
    //メモリ使用量削減するなら、この処理介さず、 qobj3dviewer.h　setTriangleで使う形式にしてしまった方がいいかもしれない。
    //1三角形ごと個別→頂点情報(v.p1～p3)色情報　は。 2つの三角形で共通→色(colors)、vn(法線=面の向き surfaceStr)。 全三角形で共通→vt(テクスチャ情報)
    triangles.clear();
    QVector<QVector3D> v, vn;
    QVector<QVector2D> vt;

    //voxファイルから座標・面方向・マテリアル情報取得する
    qDebug() << "[DEBUG]voxRead_makeGLdata.cpp-func_01main_GL_make: start func_vox_get_voxGraffic " +  QDateTime::currentDateTime().toString("hh:mm:ss");
    func_vox_get_voxGraffic(in_voxfilepath);
    //zDEBUG_vox_get_voxGraffic_DEBUG01(in_voxfilepath); 元座標が　正方形=閉じた面　で表示OK 全部 (1,1,1) (2,2,2) (10,10,10)などの場合。
    //zDEBUG_vox_get_voxGraffic_DEBUG02(in_voxfilepath);
    qDebug() << "[DEBUG]voxRead_makeGLdata.cpp-func_01main_GL_make: end func_vox_get_voxGraffic " +  QDateTime::currentDateTime().toString("hh:mm:ss");


    //voxファイルからの取得情報を、openGL描画形式のデータに置き換える
    qDebug() << "[DEBUG]voxRead_makeGLdata.cpp-func_01main_GL_make: start makeGLinfo " +  QDateTime::currentDateTime().toString("hh:mm:ss");
    for(int pnum=0; pnum < g_voxXYZVec.count(); pnum++){
        //qDebug() << "[DEBUG]voxRead_makeGLdata.cpp-func_01main_GL_make_getPointOfMesh voxXYZvec=" << QString::number( g_voxXYZVec.at(pnum).x())<< "," <<   QString::number( g_voxXYZVec.at(pnum).y()) << "," <<  QString::number( g_voxXYZVec.at(pnum).z());

        int in_i, in_j, in_k;
        //in_i = 1;
        //in_j = 1;
        //in_k = 1;
        in_i = g_voxXYZVec.at(pnum).x();
        in_j = g_voxXYZVec.at(pnum).z(); //GL:Z軸　j=通常:Z軸
        in_k = g_voxXYZVec.at(pnum).y() * (-1);  //GL:Y軸　k=通常:Y軸 * -1(反転 前がプラス, 後ろがマイナス）
        //GLfloat nowOP_x, nowOP_y , nowOP_z;
        float nowOP_x, nowOP_y , nowOP_z;
        float meshsize_x, meshsize_y, meshsize_z;
        meshsize_x = 1; //[DEBUG]決め打ち GL座標として
        meshsize_y = 1;
        meshsize_z = 1;
        nowOP_x = in_i * meshsize_x; //kuroda変更　-0.5 では表示が小さすぎになってしまうための対処
        nowOP_y = in_j * meshsize_y; //kuroda変更　-0.5 では表示が小さすぎになってしまうための対処
        nowOP_z = in_k * meshsize_z; //kuroda変更　-0.5 では表示が小さすぎになってしまうための対処

        //前準備 openGL座標作成 1メッシュ立方体の頂点座標を定義する
        QVector3D vertexA = QVector3D(nowOP_x, nowOP_y, nowOP_z);
        QVector3D vertexB = QVector3D(nowOP_x + meshsize_x, nowOP_y, nowOP_z);
        QVector3D vertexC = QVector3D(nowOP_x + meshsize_x, nowOP_y + meshsize_y, nowOP_z);
        QVector3D vertexD = QVector3D(nowOP_x , nowOP_y + meshsize_y, nowOP_z);
        QVector3D vertexE = QVector3D(nowOP_x, nowOP_y, nowOP_z - meshsize_z);
        QVector3D vertexF = QVector3D(nowOP_x + meshsize_x, nowOP_y, nowOP_z - meshsize_z);
        QVector3D vertexG = QVector3D(nowOP_x + meshsize_x, nowOP_y + meshsize_y, nowOP_z - meshsize_z);
        QVector3D vertexH = QVector3D(nowOP_x , nowOP_y + meshsize_y, nowOP_z - meshsize_z);

        //[DEBUG]
        //    vertexA = QVector3D(0.0, 0.0, 0.0); //Front, Bottom, Left
        //    vertexB = QVector3D(1, 0, 0);
        //    vertexC = QVector3D(1, 1, 0);
        //    vertexD = QVector3D(0, 1, 0);
        //    vertexE = QVector3D(0, 0, -1); //Back,  Bottom, Left
        //    vertexF = QVector3D(1, 0, -1);
        //    vertexG = QVector3D(1, 1, -1);
        //    vertexH = QVector3D(0, 1, -1);

        //前準備(openGL座標作成)  使う対象全部 前後・左右・上下で共通　　後処理trianglesアレイに入れる順番だけ違う。
        vt.append(QVector2D(0.0, 0.0));
        vt.append(QVector2D(1, 0));
        vt.append(QVector2D(1, 1));
        vt.append(QVector2D(0, 1));

        //前準備(openGL座標作成) objファイルのf情報(v, vn, vt の描画上での並び） 使う対象全部 面：前後・左右・上下で共通
        //f 1/1/1 2/2/1 4/3/1
        //f 4/3/1 3/4/1 1/1/1
        //QVector<int> vList;
        //QVector<int> vtList;
        //vList << 1 << 2 << 4 << 4 << 3 << 1;
        //vtList << 1 << 2 << 3 << 3 << 4 << 1;

        //-start- openGL描画用情報作成
        QString in_surfaceStr = "Front";

        //前準備(openGL座標作成)
        QVector<QVector3D> rectVec; //Front など 1平面（四角形の4頂点をopenGL描画用の並びにした座標リスト
        rectVec.clear();
        if(g_voxSurfaceStrList.at(pnum) == "Bottom"){ //通常座標=Bottom → GL座標=前
            //GL図形 前
            rectVec.append(vertexA); //1つ目の三角形
            rectVec.append(vertexB);
            rectVec.append(vertexC);
            rectVec.append(vertexC); //2つ目の三角形
            rectVec.append(vertexD);
            rectVec.append(vertexA);
        }
        if(g_voxSurfaceStrList.at(pnum) == "Top"){ //通常座標=Top → GL座標=後
            //GL図形 後
            rectVec.append(vertexF); //１つ目の三角形
            rectVec.append(vertexE);
            rectVec.append(vertexH);
            rectVec.append(vertexH); //2つ目の三角形
            rectVec.append(vertexG);
            rectVec.append(vertexF);
        }
        if(g_voxSurfaceStrList.at(pnum) == "Right"){
            //GL平面図形 右
            rectVec.append(vertexB); //１つ目の三角形
            rectVec.append(vertexF);
            rectVec.append(vertexG);
            rectVec.append(vertexG); //2つ目の三角形
            rectVec.append(vertexC);
            rectVec.append(vertexB);
        }
        if(g_voxSurfaceStrList.at(pnum) == "Left"){
            //GL平面図形 左
            rectVec.append(vertexE); //１つ目の三角形
            rectVec.append(vertexA);
            rectVec.append(vertexD);
            rectVec.append(vertexD); //2つ目の三角形
            rectVec.append(vertexH);
            rectVec.append(vertexE);
        }
        if(g_voxSurfaceStrList.at(pnum) == "Front"){ //通常座標=Front → GL座標=上
            //GL平面図形 上
            rectVec.append(vertexD); //１つ目の三角形
            rectVec.append(vertexC);
            rectVec.append(vertexG);
            rectVec.append(vertexG); //2つ目の三角形
            rectVec.append(vertexH);
            rectVec.append(vertexD);
        }
        if(g_voxSurfaceStrList.at(pnum) == "Back"){ //通常座標=Back → GL座標=下
            //GL平面図形 下
            rectVec.append(vertexE); //１つ目の三角形
            rectVec.append(vertexF);
            rectVec.append(vertexB);
            rectVec.append(vertexB); //2つ目の三角形
            rectVec.append(vertexA);
            rectVec.append(vertexE);
        }

        //前準備(openGL座標作成) objファイルのvn情報　(法線=面の方向)
        //    if(in_surfaceStr == "Front"){  vnStr = "vn 0.0000 0.0000 1.0000" ; }
        //    if(in_surfaceStr == "Back"){   vnStr = "vn 0.0000 0.0000 -1.0000" ; }
        //    if(in_surfaceStr == "Right"){  vnStr = "vn 1.0000 0.0000 0.0000" ; }
        //    if(in_surfaceStr == "Left"){   vnStr = "vn -1.0000 0.0000 0.0000" ; }
        //    if(in_surfaceStr == "Top"){    vnStr = "vn 0.0000 1.0000 0.0000" ; }
        //    if(in_surfaceStr == "Bottom"){ vnStr = "vn 0.0000 -1.0000 0.0000" ; }
        QVector3D vn_now;
        vn_now = QVector3D(0, 0, 1);
        if(g_voxSurfaceStrList.at(pnum) == "Bottom"){ vn_now = QVector3D(0, 0, 1);  }
        if(g_voxSurfaceStrList.at(pnum) == "Top"){    vn_now = QVector3D(0, 0, -1); }
        if(g_voxSurfaceStrList.at(pnum) == "Right"){  vn_now = QVector3D(1, 0, 0);  }
        if(g_voxSurfaceStrList.at(pnum) == "Left"){   vn_now = QVector3D(-1, 0, 0); }
        if(g_voxSurfaceStrList.at(pnum) == "Front"){  vn_now = QVector3D(0, 1, 0);  }
        if(g_voxSurfaceStrList.at(pnum) == "Back"){   vn_now = QVector3D(0, -1, 0); }

        for(int shapeCnt=1; shapeCnt<=2; shapeCnt++ ){ //1平面 = 2つの三角形
            //if(shapeCnt == 1){

            QOpenGLTriangle3D_vox triangle;

            //色設定
            //g_GLColors.append(g_voxColors.at(pnum));
            triangle.color = g_voxColors.at(pnum);

            // 1平面(四角形)-1つ目の三角形 頂点情報 (objファイルのvt)
            QVector3D p1, p2, p3;
            if(shapeCnt == 1){
                p1 = rectVec.at(0);
                p2 = rectVec.at(1);
                p3 = rectVec.at(2);
            } else if(shapeCnt == 2){
                p1 = rectVec.at(3);
                p2 = rectVec.at(4);
                p3 = rectVec.at(5);
            }
            triangle.p1 = p1;
            triangle.p2 = p2;
            triangle.p3 = p3;

            QVector2D p1UV, p2UV, p3UV;
            //-start- NG QVector2D(0,0) がなぜか抜けてしまうため、vt.at(3)で落ちてしまう。。
            //if(shapeCnt == 1){
            //    p1UV = vt.at(0);
            //    p2UV = vt.at(1);
            //    p3UV = vt.at(2);
            //} else if (shapeCnt == 2){
            //    p1UV = vt.at(2);
            //    p2UV = vt.at(3);
            //    p3UV = vt.at(0);
            //}
            //-end- NG
            if(shapeCnt == 1){
                p1UV = QVector2D(0.0, 0.0);
                p2UV = QVector2D(1, 0);
                p3UV = QVector2D(1, 1);
            } else if (shapeCnt == 2){
                p1UV = QVector2D(1, 1);
                p2UV = QVector2D(0, 1);
                p3UV = QVector2D(0.0, 0.0);
            }
            triangle.p1UV = p1UV;
            triangle.p2UV = p2UV;
            triangle.p3UV = p3UV;

            triangle.p1Normal = vn_now;
            triangle.p2Normal = vn_now;
            triangle.p3Normal = vn_now;

            triangles.append(triangle);

        }
        //-end- for(int shapeCnt=1; shapeCnt<=2; shapeCnt++ )
    }
    //-end- for(int pnum=0; pnum < g_voxXYZVec.count(); pnum++)
    qDebug() << "[DEBUG]voxRead_makeGLdata.cpp-func_01main_GL_make: end makeGLinfo " +  QDateTime::currentDateTime().toString("hh:mm:ss");

}



void voxRead_makeGLdata::zDEBUG_vox_get_voxGraffic_DEBUG01(QString in_voxfilepath) //voxファイルから、座標とマテリアル情報を取得する　1点ごと
{
    //取得する情報　Meshの位置(始点・終点）　面の方向(vn)　マテリアル番号からの色　 　将来的には半透明かどうか(acolorも）

    //[DEBUG]-start-
    g_voxXYZVec.clear();
    g_voxColors.clear();
    g_voxSurfaceStrList.clear();

    g_voxXYZVec.append(QVector3D(1 ,1, 1));
    g_voxColors.append(QVector3D(1, 0, 0)); //赤
    g_voxSurfaceStrList.append("Front");

    //g_voxXYZVec.append(QVector3D(1, 1, 2)); //XYZ=1,1,2 向き=Backだと表示がされない。。
    g_voxXYZVec.append(QVector3D(1, 1, 1));
    g_voxColors.append(QVector3D(0, 1, 0)); //緑
    g_voxSurfaceStrList.append("Back");

    g_voxXYZVec.append(QVector3D(1 ,1, 1));
    g_voxColors.append(QVector3D(1, 0, 1)); //マゼンタ
    g_voxSurfaceStrList.append("Right");

    g_voxXYZVec.append(QVector3D(1 ,1, 1));
    g_voxColors.append(QVector3D(0, 0, 1)); //青
    g_voxSurfaceStrList.append("Left");

    g_voxXYZVec.append(QVector3D(1 ,1, 1));
    g_voxColors.append(QVector3D(1, 1, 0)); //黄色
    g_voxSurfaceStrList.append("Top");

    g_voxXYZVec.append(QVector3D(1 ,1, 1));
    g_voxColors.append(QVector3D(0, 1, 1)); //水色
    g_voxSurfaceStrList.append("Bottom");

    return;
    //[DEBUG]-end-

}


void voxRead_makeGLdata::zDEBUG_vox_get_voxGraffic_DEBUG02(QString in_voxfilepath) //voxファイルから、座標とマテリアル情報を取得する　1点ごと
{
    //取得する情報　Meshの位置(始点・終点）　面の方向(vn)　マテリアル番号からの色　 　将来的には半透明かどうか(acolorも）
    //裏側に色が付かない件、どうするかはこれから考える。。

    //[DEBUG]-start-
    g_voxXYZVec.clear();
    g_voxColors.clear();
    g_voxSurfaceStrList.clear();

    g_voxXYZVec.append(QVector3D(1, 1, 1));
    g_voxColors.append(QVector3D(1, 0, 0)); //赤
    g_voxSurfaceStrList.append("Front");


    g_voxXYZVec.append(QVector3D(1, 1, 2));
    g_voxColors.append(QVector3D(0, 1, 0)); //緑
    g_voxSurfaceStrList.append("Back");

    g_voxXYZVec.append(QVector3D(1, 1, 1));
    g_voxColors.append(QVector3D(1, 0, 1)); //マゼンタ
    g_voxSurfaceStrList.append("Right");

    g_voxXYZVec.append(QVector3D(1, 1, 2));
    g_voxColors.append(QVector3D(0, 0, 1)); //青
    g_voxSurfaceStrList.append("Left");

    g_voxXYZVec.append(QVector3D(1, 1, 1));
    g_voxColors.append(QVector3D(1, 1, 0)); //黄色
    g_voxSurfaceStrList.append("Top");

    g_voxXYZVec.append(QVector3D(1, 1, 2));
    g_voxColors.append(QVector3D(0, 1, 1)); //水色
    g_voxSurfaceStrList.append("Bottom");

    return;
    //[DEBUG]-end-

}


//流用元: QVector<QVector3D>  miWidget::func_get_voxGraffic(QString in_voxfilepath, QString mode)  //[DEBU]kuroda　shaderで描くための座標・色設定情報を関数呼び出し先にリターンする
void voxRead_makeGLdata::func_vox_get_voxGraffic(QString in_voxfilepath) //voxファイル読み込みして、座標とマテリアル情報を取得する　1Meshごと
{
//  g_DrawMeshXYZList.clear(); //[DEBUG]用途
//  dragFilePathList.clear();
//  dragFilePathList << in_voxfilepath;
    QString voxfilePath = in_voxfilepath;

//    //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//    mMatrix = QMatrix4x4();
//    mMatrix.setToIdentity();

    DrawMesh.clear();
    DrawSurface.clear();
    mateNoList.clear();
    mateNoOfMesh.clear();

//    vertexList.clear();
//    colorList.clear();
//    normalList.clear();

//    g_verticesVector.clear();
//    g_colorsVector.clear();

    //m_program->disableAttributeArray(m_vertexLocation);
    //m_program->disableAttributeArray(m_colorLocation);
    //m_program->disableAttributeArray(m_normalLocation);
    //
    //m_program->release();

    //各メッシュの材質No. を取得
    func_vox_getMateNumOfMesh(in_voxfilepath);
    QList<int> tmpQList;
    //for(int i=0; i<mateNoOfMesh.size(); i++ ){ tmpQList << mateNoOfMesh[i]; } //[DEBUG]kuroda qDebug表示のため、QListに代入する。
    //qDebug() << "[DEBUG]01 miwidget.cpp-func_get_voxGraffic  mateNoOfMesh size=" << QString::number(mateNoOfMesh.size()) << ""  << tmpQList;

    //描画するメッシュの面情報を取得
    func_vox_GLadd_checkMateNumOfAdjoinMesh();
    //qDebug() << "[DEBUG]01 miwidget.cpp-func_get_voxGraffic DrawMesh=" << DrawMesh;
    //qDebug() << "[DEBUG]01 miwidget.cpp-func_get_voxGraffic DrawSurface=" << DrawSurface;

//    //paintGL実行フラグ有効
//    paintExeFlag = 1;

//    grafficSurface(); //voxから shaderで描くための図形取得　vertexList, colorList (normalListも？？）

//    //qDebug() << "[DEBUG]02 miwidget.cpp-func_get_voxGraffic  g_verticesVector=" << g_verticesVector;
//    //qDebug() << "[DEBUG]02func_get_voxGraffic.cpp g_colorsVector=" << cg_colorsVector;

//    QString WriteFilePath =  QFileInfo(voxfilePath).absolutePath() + "/log_DrawMeshXYZList.txt";
//    QString WriteFileMode = "WriteOnly";
//    qDebug() << "[DEBUG] miWidget.cpp-func_get_voxGraffic write-log-DrawMeshXYZList path=" << WriteFilePath;
//    fileWrteForWindows(WriteFilePath, WriteFileMode, g_DrawMeshXYZList);

//    if(mode == "color"){
//        return g_colorsVector; //QVector<GLfloat> colorList;
//    } else {
//        return g_verticesVector;   //QVector<GLfloat> vertexList;
//    }

}

//voxファイルのヘッダー情報読み込み + voxファイルを読み込んで、メッシュごとにマテリアルNo.を割り当てる
void voxRead_makeGLdata::func_vox_getMateNumOfMesh(QString in_voxfilepath)
{
     //voxfilePath = dragFilePathList.at(0);
     QString voxfilePath = in_voxfilepath;
     QStringList read_vox = readTextFileAll(voxfilePath);
     //qDebug() << "read_vox.size" << read_vox.size();

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

         //qDebug() << "miWidget::func_vox_getMateNumOfMesh() read_vox.at(line_n).trimmed()=" << read_vox.at(line_n).trimmed();

         if(read_vox.at(line_n).trimmed()=="CellData"){
             voxflag = 2;
             line_n = line_n + 1;
             //qDebug() << "miWidget::func_vox_getMateNumOfMesh() CellData voxflag=" << QString::number(voxflag);
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
             //qDebug() << "miWidget::func_vox_getMateNumOfMesh() temp03=" << temp03;
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


void voxRead_makeGLdata::func_vox_GLadd_checkMateNumOfAdjoinMesh()
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

                if(mateNoOfMesh[nowMeshNo] == 0 ){
                    nowMeshNo++;
                    continue; //マテリアル番号=0 の場合はAir とみなして表示しない。以下の処理をスキップする
                }

                 QString strXYZ = QString::number(i) + "," + QString::number(j) + "," + QString::number(k) ;

                //front → glBack (引き継ぎ時点で、間違っていた。。　正しくはglBack）
                chkMeshNo = nowMeshNo - nx * ny;
                if(k ==0 || (k !=0) && (mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo])){
                    //if(drawMeshFlag == 0){
                    //    DrawMesh.insert(mateNoOfMesh[nowMeshNo], nowMeshNo);
                    //    drawMeshFlag = 1;
                    //    //g_DrawMeshXYZList << strXYZ ;
                    //}
                    //DrawSurface.insert(nowMeshNo, 1);

                    g_voxXYZVec.append(QVector3D(i, j, k)); //openGL座標なので (glX, glY, glZ) = 通常座標(x, z, -y)
                    g_voxColors.append(func_GL_defineColor(mateNoOfMesh[nowMeshNo])); //例　QVector3D(0, 1, 0) 緑など設定
                    g_voxSurfaceStrList.append("Back");
                }

                //back (引き継ぎ時点で、間違っていた。。　正しくはglFront）
                chkMeshNo = nowMeshNo + nx * ny;
                if(k ==nz-1 || (k != nz-1) && (mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo])){
//                    if(drawMeshFlag == 0){
//                        DrawMesh.insert(mateNoOfMesh[nowMeshNo], nowMeshNo);
//                        drawMeshFlag = 1;
//                        //g_DrawMeshXYZList << strXYZ;
//                    }
//                    DrawSurface.insert(nowMeshNo, 2);

                    g_voxXYZVec.append(QVector3D(i, j, k));
                    g_voxColors.append(func_GL_defineColor(mateNoOfMesh[nowMeshNo]));
                    g_voxSurfaceStrList.append("Front");
                }

                //right
                chkMeshNo = nowMeshNo + 1;
                if(i ==nx-1 || (i != nx-1) && (mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo])){
//                    if(drawMeshFlag == 0){
//                        DrawMesh.insert(mateNoOfMesh[nowMeshNo], nowMeshNo);
//                        drawMeshFlag = 1;
//                        //g_DrawMeshXYZList << strXYZ;
//                    }
//                    DrawSurface.insert(nowMeshNo, 3);

                    g_voxXYZVec.append(QVector3D(i, j, k));
                    g_voxColors.append(func_GL_defineColor(mateNoOfMesh[nowMeshNo]));
                    g_voxSurfaceStrList.append("Right");
                }

                //left
                chkMeshNo = nowMeshNo - 1;
                if(i ==0 || (i != 0) && (mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo])){
//                    if(drawMeshFlag == 0){
//                        DrawMesh.insert(mateNoOfMesh[nowMeshNo], nowMeshNo);
//                        drawMeshFlag = 1;
//                        //g_DrawMeshXYZList << strXYZ;
//                    }
//                    DrawSurface.insert(nowMeshNo, 4);

                    g_voxXYZVec.append(QVector3D(i, j, k));
                    g_voxColors.append(func_GL_defineColor(mateNoOfMesh[nowMeshNo]));
                    g_voxSurfaceStrList.append("Left");
                }

                //top
                chkMeshNo = nowMeshNo + nx;
                if(j == ny-1 || (j != ny-1) && (mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo])){
//                    if(drawMeshFlag == 0){
//                        DrawMesh.insert(mateNoOfMesh[nowMeshNo], nowMeshNo);
//                        drawMeshFlag = 1;
//                        //g_DrawMeshXYZList << strXYZ;
//                    }
//                    DrawSurface.insert(nowMeshNo, 5);

                    g_voxXYZVec.append(QVector3D(i, j, k));
                    g_voxColors.append(func_GL_defineColor(mateNoOfMesh[nowMeshNo]));
                    g_voxSurfaceStrList.append("Top");

                }

                //bottom
                chkMeshNo = nowMeshNo - nx;
                if(j == 0 || (j != 0) && (mateNoOfMesh[nowMeshNo] != mateNoOfMesh[chkMeshNo])){
//                    if(drawMeshFlag == 0){
//                        DrawMesh.insert(mateNoOfMesh[nowMeshNo], nowMeshNo);
//                        drawMeshFlag = 1;
//                        //g_DrawMeshXYZList << strXYZ;
//                    }
//                    DrawSurface.insert(nowMeshNo, 6);

                    g_voxXYZVec.append(QVector3D(i, j, k));
                    g_voxColors.append(func_GL_defineColor(mateNoOfMesh[nowMeshNo]));
                    g_voxSurfaceStrList.append("Bottom");
                }

                nowMeshNo++;

            }//-end- for i
        }//-end- for j
    }//-end- for k

}



QStringList voxRead_makeGLdata::readTextFileAll(QString fileName)
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

//ファイル書き込み(windowsで使うファイル用)
int voxRead_makeGLdata::fileWrteForWindows(QString WriteFilePath, QString WriteMode, QStringList msgList)
{
     QFile file(WriteFilePath);
     if(WriteMode == "Append"){
         if(!file.open(QIODevice::Append| QIODevice::Text)){
             //QMessageBox::information(this, tr("Unable to openfile"), file.errorString()); //Qtフォームクラスでないため、QMessageBoxが使えない。。代わりにエラーの場合は -1 を返り値に渡す
             return(-1);
         }
     } else {
         if(!file.open(QIODevice::WriteOnly| QIODevice::Text)){
             //QMessageBox::information(this, tr("Unable to openfile"), file.errorString());　 //Qtフォームクラスでないため、QMessageBoxが使えない。。代わりにエラーの場合は -1 を返り値に渡す
             return(-1);
         }
     }

     QTextStream out(&file);
     for (int n=0; n<msgList.size(); n++){
         out << msgList.at(n) << endl;
     }
     file.close();
}

QVector3D voxRead_makeGLdata::func_GL_defineColor(int input_colornum){

     QVector3D resultColor = QVector3D(1, 0, 0);
     int tmpint_color = input_colornum % 10;

     if(tmpint_color == 0){ resultColor = QVector3D(1, 0, 0); } //赤
     if(tmpint_color == 1){ resultColor = QVector3D(0, 1, 0); } //緑
     if(tmpint_color == 2){ resultColor = QVector3D(0, 0, 1); } //青

     if(tmpint_color == 3){ resultColor = QVector3D(1, 1, 0); } //黄色
     if(tmpint_color == 4){ resultColor = QVector3D(1, 0, 1); } //マゼンタ
     if(tmpint_color == 5){ resultColor = QVector3D(0, 1, 1); } //シアン(水色)

     if(tmpint_color == 6){ resultColor = QVector3D(0.75, 0.8, 0); } //オレンジ
     if(tmpint_color == 7){ resultColor = QVector3D(0.67, 1, 0.18); } //黄緑
     if(tmpint_color == 8){ resultColor = QVector3D(0.5, 0, 0.5); } //紫

     if(tmpint_color == 8){ resultColor = QVector3D(1, 0.75, 0.8); } //ピンク

     if(tmpint_color == 6){ resultColor = QVector3D(0.5, 0, 0); } //濃い赤
     if(tmpint_color == 7){ resultColor = QVector3D(0, 0.5, 0); } //濃い緑
     if(tmpint_color == 8){ resultColor = QVector3D(0, 0, 0.5); } //濃い青

     //-------------------------
     //参考
     //if(tmpint_color == 0){ resultColor = QVector3D(0, 0, 0); } //Black QColor(0, 0, 0, 255)
     //if(tmpint_color == 1){ resultColor = QVector3D(0.5, 0.5, 0.5); } //Glay QColor(128, 128, 128, 255)
     //if(tmpint_color == 2){ resultColor = QVector3D(0.82, 0.82, 0.82); } //LightGlay QColor(211, 211, 211, 255)
     //if(tmpint_color == 3){ resultColor = QVector3D(1, 1, 1); } //White QColor(255, 255, 255, 255)

     //if(tmpint_color == 4){ resultColor = QVector3D(0.64, 0.16, 0.16); } //Brown QColor(165, 42, 42, 255)
     //if(tmpint_color == 5){ resultColor = QVector3D(0.5, 0, 0.5); } //Purple QColor(128, 0, 128, 255)
     //if(tmpint_color == 6){ resultColor = QVector3D(0.57, 0.43, 0.85); } //Medium Purple QColor(147, 112, 219, 255)
     //if(tmpint_color == 7){ resultColor = QVector3D(1, 0, 0); } //Red QColor(255, 0, 0, 255)
     //if(tmpint_color == 8){ resultColor = QVector3D(1, 0, 1); } //Magenta QColor(255, 0, 255, 255)
     //if(tmpint_color == 9){ resultColor = QVector3D(1, 0.75, 0.8); } //pink QColor(255, 192, 203, 255)
     //if(tmpint_color == 10){ resultColor = QVector3D(0.75, 0.8, 0); } //Orange QColor(225, 165, 0, 255)
     //if(tmpint_color == 11){ resultColor = QVector3D(1, 0.84, 0); } //Gold QColor(255, 215, 0, 255)
     //if(tmpint_color == 12){ resultColor = QVector3D(1, 1, 0); } //Yellow QColor(255, 255, 0, 255)

     //if(tmpint_color == 13){ resultColor = QVector3D(0, 0.5, 0); } //Green QColor(0, 128, 0, 255)
     //if(tmpint_color == 14){ resultColor = QVector3D(0.67, 1, 0.18); } //GreenYellow QColor(173, 255, 47, 255)
     //if(tmpint_color == 15){ resultColor = QVector3D(0.5, 0.5, 0); } //0live QColor(128, 128, 0, 255)
     //if(tmpint_color == 16){ resultColor = QVector3D(0, 0, 0.5); } //Navy QColor(0, 0, 128, 255)
     //if(tmpint_color == 17){ resultColor = QVector3D(0, 0, 1); } //Blue QColorr(0, 0, 255, 255)
     //if(tmpint_color == 18){ resultColor = QVector3D(0, 1, 1); } //cyan QColor(0, 255, 255, 255)
     //if(tmpint_color == 19){ resultColor = QVector3D(0.87, 1, 1); } //LightCyan QColor(224, 255, 255, 255)
     //-------------------------

     return resultColor;
}
