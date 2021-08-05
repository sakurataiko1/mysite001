def func_define_color(input_num):
    colorNum = input_num % 10
    #if(colorNum==0) : colorStr = "#000000" #black
    #if(colorNum==0) : colorStr = "#808080" #gray
    #if(colorNum==0) : colorStr = "#C0C0C0" #silver
    #if(colorNum==0) : colorStr = "#FFFFFF" #white
    if(colorNum==0) :  colorStr = "#0000FF" #blue
    if(colorNum==1) : colorStr = "#000080" #navy
    if(colorNum==2) : colorStr = "#008080" #teal
    if(colorNum==3) : colorStr = "#008000" #green
    if(colorNum==4) : colorStr = "#00FF00" #lime
    if(colorNum==5) : colorStr = "#00FFFF" #aqua
    if(colorNum==6) : colorStr = "#FFFF00" #yellow
    if(colorNum==7) : colorStr = "#FF0000" #red
    if(colorNum==8) : colorStr = "#FF00FF" #fuchsia
    if(colorNum==9) : colorStr = "#808000" #olive
    #if(colorNum==10) : colorStr = "#800080" #purple
    #if(colorNum==11) : colorStr = "#800000" #maroon

    return(colorStr)


#参考URL：matplotlib公式サイト　pathpatch_2d_to_3dの使い方
#https://matplotlib.org/stable/gallery/mplot3d/pathpatch3d.html#sphx-glr-gallery-mplot3d-pathpatch3d-py
#
#参考URL：3D空間に直方体作成 pathpatch_2d_to_3dのRectangleの使い方
#https://sabopy.com/py/matplotlib-3d-43/
#
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import Circle, PathPatch
from matplotlib.text import TextPath
from matplotlib.transforms import Affine2D
import mpl_toolkits.mplot3d.art3d as art3d
from matplotlib.patches import Rectangle


fig = plt.figure()
ax = fig.add_subplot(projection='3d')

# Draw a circle on the x=0 'wall'
#p = Circle((5, 5), 3)

#-----------------
# 原点配置
#pLeftRight = Rectangle(xy=(0, 0), width=1, height=3 ,facecolor='magenta',edgecolor='magenta',alpha=0.5)
#ax.add_patch(pLeftRight)
#art3d.pathpatch_2d_to_3d(pLeftRight, z=0, zdir="x")
#
#pFrontBack = Rectangle(xy=(0, 0), width=5, height=2 ,facecolor='yellow', edgecolor='yellow',alpha=0.5)
#ax.add_patch(pFrontBack)
#art3d.pathpatch_2d_to_3d(pFrontBack, z=0, zdir="y")
#
#pTopBottom = Rectangle(xy=(0, 0), width=8.5, height=3.5 ,facecolor='cyan',edgecolor='cyan',alpha=0.5)
#ax.add_patch(pTopBottom)
#art3d.pathpatch_2d_to_3d(pTopBottom, z=0, zdir="z")


#----------------
# オフセット配置
# zdir="x" の場合, オフセット座標→Rectangle(xy=(Y軸, Z軸) pathpatch_2d_to_3d(z=X軸)
#pLeftRight = Rectangle(xy=(9, 1), width=1, height=3 ,facecolor='red',edgecolor='red',alpha=0.5)
#ax.add_patch(pLeftRight)
#art3d.pathpatch_2d_to_3d(pLeftRight, z=3, zdir="x")

# zdir="y" の場合, オフセット座標→Rectangle(xy=(X軸, Z軸) pathpatch_2d_to_3d(z=Y軸)
#pFrontBack = Rectangle(xy=(1, 5), width=5, height=2 ,facecolor='green',edgecolor='green',alpha=0.5)
#ax.add_patch(pFrontBack)
#art3d.pathpatch_2d_to_3d(pFrontBack, z=3, zdir="y")

# zdir="y" の場合, オフセット座標→Rectangle(xy=(X軸, Y軸) pathpatch_2d_to_3d(z=Z軸)
#pTopBottom = Rectangle(xy=(3.1 , 6.1), width=7.5, height=3.5 ,facecolor='blue',edgecolor='blue',alpha=0.5)
#ax.add_patch(pTopBottom)
#art3d.pathpatch_2d_to_3d(pTopBottom, z=9, zdir="z")

#-------------------
in_filepath = "C:/kuroda/work/00_Data_vox/DEBUG_3Dviewer/z_surfaceXY_mini7x6x5vox.txt"

with open(in_filepath) as f:
    linelist = [s.strip() for s in f.readlines()] #改行削除して1行ずつ読み込み
    print(linelist)
f.close();


for line in linelist:
    print(line)
    wordlist = line.split(",")
    matnum  = int(wordlist[0])
    surface = wordlist[1]
    xStart  = int(wordlist[2])
    yStart  = int(wordlist[3])
    zStart  = int(wordlist[4])
    xEnd    = int(wordlist[5])
    yEnd    = int(wordlist[6])
    zEnd    = int(wordlist[7])
    
    tmp_width = xEnd - xStart
    if(tmp_width == 0) : tmp_width = 1
    tmp_height = yEnd - yStart
    if(tmp_height == 0) : tmp_height = 1
    
    print("line=", line, " xStart=", xStart, " xEnd=", xEnd)
    
    #color = "#008000" #green 
    colorStr = func_define_color(matnum)
    pTopBottom = Rectangle(xy=(xStart , yStart), width=tmp_width, height=tmp_height,facecolor=colorStr ,edgecolor='blue',alpha=0.5)
    ax.add_patch(pTopBottom)
    art3d.pathpatch_2d_to_3d(pTopBottom, z=zStart, zdir="z")

#--------------------
ax.set_xlim(0, 10)
ax.set_ylim(0, 10)
ax.set_zlim(0, 10)

ax.set_xlabel("X-axis")
ax.set_ylabel("Y-axis")
ax.set_zlabel("Z-axis")

plt.show()





