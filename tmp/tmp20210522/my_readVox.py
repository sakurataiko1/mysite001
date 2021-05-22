#-*- coding-utf8 -*-
#
# voxファイルを読み込む
#

import numpy as np
import pandas as pd
import re #正規表現
import math

class myglobal :
    #グローバル変数一覧
    g_infilepath = "C:/kuroda/work/00_Data_vox/test_mini0-3_5x3x4-2_vox.txt"
    g_meshsize :float = 0.02
    g_nx :int = 1
    g_ny :int = 1
    g_nz :int = 1
    g_list_material = []
    g_row_datastart :int = -1  # 0行目始まり
    g_arydraw = np.zeros((1,1,1))

def func_main():
    # マテリアル名、メッシュサイズ、CellData数などの取得
    myglobal.g_meshsize = 0.02
    myglobal.g_nx=1
    myglobal.g_ny=1
    myglobal.g_nz=1
    myglobal.g_list_material = []
    myglobal.g_row_datastart = -1 # 0行目始まり
    lines_header = func_readfile_voxHeader(myglobal.g_infilepath) # マテリアル名、メッシュサイズ、CellData数などの取得
    print("[DEBUG]func_main() g_meshsize=%s g_nx=%s g_ny=%s g_nz=%s g_row_datastart=%d\n" % (myglobal.g_meshsize, myglobal.g_nx, myglobal.g_ny, myglobal.g_nz, myglobal.g_row_datastart) )
    #for i in range(len(myglobal.g_list_material) - 1 ) :
    #    print("[DEBUG]func_main myglobal.g_list_material=" ,myglobal.g_list_material[i])

    #　描画データ部分を読み込んで、 myglobal.g_arydrawに入れる。文字列として保存されるので使う時はintとして扱う。
    func_readfile_voxData(myglobal.g_infilepath, myglobal.g_row_datastart+1) #描画データ部分をいったんpandasに読み込む (numpyだと列数違いのデータ読み込みでエラーになるので)
    print("[DEBUG]main() myglobal.g_arydraw=\n", myglobal.g_arydraw, "\n");

def func_readfile_voxHeader(in_filepath) :
    #global g_infilepath, g_meshsize, g_nx, g_ny, g_nz, g_list_material, g_row_datastart
    with open(in_filepath, mode='r') as f:
        flag_material = 0
        row_line = -1
        for line in f:
            row_line = row_line + 1
            strlist1 = line.splitlines() #改行削除
            strlist2 = strlist1[0].split("\t")
            tmpID =""
            if (len(strlist2)-1 >= 1) : tmpID = strlist2[1]
            tmpvalue = strlist2[0]

            tmp_match = re.match(r'[0-9]+ x [0-9]+ x [0-9+]' , strlist1[0])
            if(tmp_match) :
                tmplist = strlist1[0].split(' x ')
                myglobal.g_nx = int(tmplist[0])
                myglobal.g_ny = int(tmplist[1])
                myglobal.g_nz = int(tmplist[2])
                break

            if(tmpID == "unitlength"):
                myglobal.g_meshsize = tmpvalue
                flag_material = 1
                continue

            if(strlist1[0] == 'CellData') :
                print("Celldata rowline=%d" % row_line)
                flag_material = 0
                myglobal.g_row_datastart = row_line + 1
                continue
            elif(flag_material == 1) :
                myglobal.g_list_material.append(tmpID)
                continue


def func_readfile_voxData(in_filepath, in_skiprow) :
    # 改行削除して1行ずつ読み込み
    with open(in_filepath) as f:
        linelist = [str.strip() for str in f.readlines()]
    f.close();

    # ヘッダー部削除
    del linelist[0:in_skiprow]
    #print("[DEBUG]func_readfile_voxData() linelist=", linelist);

    # データ展開　1行あたり 　['マテリアル番号A 連続数3 マテリアル番号B 連続数2'] =　x=5の場合 ['99 3 11 2', '88 1 20 4' , ... ]　→　[99,99,99,11,11,88,20,20,20,20]
    #for i in len(linelist):
    #    #x :int = i
    #    z :int = i / int(myglobal.g_ny)
    #   y :int = i - z * int(myglobal.g_ny) ;
    linelist2 = []
    for termstr in linelist :
        termlist= termstr.split(' ');
        for i in range(int(len(termlist)/2)) :
            for j in range(int(termlist[2*i+1])) :
                linelist2.append(termlist[2*i])
    print("[DEBUG]func_readfile_voxData() linelist2 len=", len(linelist2) ," ", linelist2, "\n");
    #　numpy_arraysy初期化
    myglobal.g_arydraw = np.zeros((myglobal.g_nz , myglobal.g_ny, myglobal.g_nx))
    #　numpy_array 展開したvoxファイルデータを入れる

    myglobal.g_arydraw = np.array(linelist2)
    myglobal.g_arydraw = myglobal.g_arydraw.reshape(myglobal.g_nz, myglobal.g_ny, myglobal.g_nx)
    #print("[DEBUG]func_readfile_voxData() myglobal.g_arydraw=\n", myglobal.g_arydraw, "\n");

def func_readfile_voxData_pandas(in_filepath, in_skiprow) : #描画データ部分をいったんpandasに読み込む (numpyだと列数違いのデータ読み込みでエラーになるので)
    #DEBUG# infilepath  = "C:/kuroda/work/00_Data_vox/test_mini_vox.txt"
    #outfilepath = "c:/tmp/result_XY-String.txt"

    #列数が不揃いのファイルをpandasに読み込む
    max_row = 10 #仮の最大列数
    col_names = [ 'c{0:03d}'.format(i) for i in range(10) ] #最大列数でカラム名を作る
    #
    # 例 最大列数でカラム名を作る
    #col_names = [ 'c{0:02d}'.format(i) for i in range(10) ]
    #  #=> ['c00', 'c01', 'c02', 'c03', 'c04', 'c05', 'c06', 'c07', 'c08', 'c09']

    df = pd.read_csv( in_filepath , sep=' ', names=col_names , skiprows=in_skiprow)
    #print("[DEBUG]df=" , df)

    return(df)

##################################
# Main部　実行
##################################
if __name__ == '__main__':
    func_main()







 