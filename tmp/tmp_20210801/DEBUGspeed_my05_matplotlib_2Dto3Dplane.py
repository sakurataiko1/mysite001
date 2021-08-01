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

import datetime


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
#pLeftRight = Rectangle(xy=(9, 1), width=1, height=3, facecolor='red', edgecolor='red', alpha=0.5)
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

#--------
#速度計測
for i in range(240000):
    print("[DEBUG]i=", i, " time=", datetime.datetime.now())
    pFrontBack = Rectangle(xy=(1, i), width=5, height=2 ,facecolor='green',edgecolor='green',alpha=0.5)
    ax.add_patch(pFrontBack)
    art3d.pathpatch_2d_to_3d(pFrontBack, z=3, zdir="y")

ax.set_xlim(0, 10)
ax.set_ylim(0, 10)
ax.set_zlim(0, 10)

ax.set_xlabel("X-axis")
ax.set_ylabel("Y-axis")
ax.set_zlabel("Z-axis")

plt.show()
