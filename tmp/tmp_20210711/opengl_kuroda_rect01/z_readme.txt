参考：

■　OpenGLコードの参考　Qt公式プログラム
http://ftp.jaist.ac.jp/pub/qtproject/learning/developerguides/qtopengltutorial/
ソースコード：　opengl_src.zip
解説：　OpenGLTutorial.pdf

■　GUI参考
https://www.bogotobogo.com/Qt/Qt5_OpenGL_QGLWidget.php

widget の格上げもここを参考にした。

■ Qtの設定参考。（シェーダプログラムの追加とリソースファイルへの登録.vsh, fsh)
https://armadillo.atmark-techno.com/blog/1562/1988


-----
現在の処理の流れ：

Window::on_pushButton_voxpathLoad_clicked()
↓
myGLWidget.cpp-func_load_voxfile()
↓
myGLWidget.cpp-paintGL()
  vox読み出し～ openGLで描くための座標  vertices, colors の取得
 
  vertices, colors さえ入れてあげればよい。
   →  func_getPointOfMesh_new(i, j, k, drawSurfaceList.at(n), mateNo);
  　　　を i , j , k, drawSurfaceList.at(n)を変えて 回すだけ