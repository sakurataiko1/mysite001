# https://www.pythonpool.com/matplotlib-draw-rectangle/
import numpy as np
from mpl_toolkits.mplot3d.art3d import Poly3DCollection, Line3DCollection
import matplotlib.pyplot as plt
import datetime

def func_makeGraph(input_num):
    points = np.array([[-1, -1, -1],
                      [1, -1, -1 ],
                      [1, 1, -1],
                      [-1, 1, -1],
                      [-1, -1, 1],
                      [1, -1, 1 ],
                      [1, 1, 1],
                      [-1, 1, 1]])
    Z = points
    #Z = 10.0*Z
    Z = 5.0 * Z + ((input_num % 10) * 10) #[DEBUG]変更
    #fig = plt.figure()
    #ax = fig.add_subplot(111, projection='3d')
    r = [-1,1]
    X, Y = np.meshgrid(r, r)

    ax.scatter3D(Z[:, 0], Z[:, 1], Z[:, 2])

    verts = [[Z[0],Z[1],Z[2],Z[3]],
     [Z[4],Z[5],Z[6],Z[7]],
     [Z[0],Z[1],Z[5],Z[4]],
     [Z[2],Z[3],Z[7],Z[6]],
     [Z[1],Z[2],Z[6],Z[5]],
     [Z[4],Z[7],Z[3],Z[0]]]
    
    ax.add_collection3d(Poly3DCollection(verts, facecolors='cyan', linewidths=1, edgecolors='r', alpha=.20)) #枠線あり 
    #fcolor = "cyan"
    #if(input_num == 1 ):
    #    fcolor="red" 
    #ax.add_collection3d(Poly3DCollection(verts, facecolors=fcolor, linewidths=1, edgecolors='r', alpha=.20)) #枠線あり    
    #ax.add_collection3d(Poly3DCollection(verts, facecolors=fcolor, linewidths=1, alpha=.20)) #枠線なし



#--------------
# main
#--------------
print("start" ,datetime.datetime.now(), "\n")

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

for i in range (7000):
    #if(input_num == 0 or input_num % 100 ):
    print(i, ":", datetime.datetime.now(), "\n")
    
    func_makeGraph(i)

plt.show()


