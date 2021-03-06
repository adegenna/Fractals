# -*- noplot -*-
from __future__ import print_function

from mpl_toolkits.mplot3d import Axes3D
import pylab
import sys,os
import numpy
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter, ScalarFormatter, MaxNLocator
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.pyplot import figure, axes, plot, xlabel, ylabel, title, grid, savefig, show

import matplotlib
matplotlib.use('TkAgg')

inches_per_pt = 1.0/72.27
width = 1000
height = 1000
fig_size = [width*inches_per_pt,height*inches_per_pt]

params = {   #'axes.labelsize': 30,
             #'text.fontsize': 40,
             #'legend.fontsize': 20,
             'xtick.labelsize': 18,
             'ytick.labelsize': 18,             
             'figure.figsize':fig_size,
             #'figure.markersize': 50}
}
#pylab.rcParams.update(params)

fig = plt.figure();

# Initial plot of Mandelbrot set
command = './julia -3.0 4.0 -5.0 5.0 500 500';
os.system(command);
figure(1);
K = pylab.genfromtxt("JULIA", delimiter = ",");
colorperiod = 15;
mandel = pylab.imshow(K%colorperiod, extent=[-5.0,5.0,-3.5,4.0]);
#mandel = pylab.imshow(np.flipud(K.transpose())%colorperiod, extent=[-3.5,4.0,-5.0,5.0]);
mandel.set_cmap('inferno');
plt.axis('off');
plt.tight_layout();
plt.savefig('fractalJulia.png', dpi = 300)

while True:
    # Get new points from user
    print("SELECT POINTS BOUNDING ZOOM REGION");
    x = plt.ginput(2);
    for i in range(0,2):
        print(x[i]);

    # Refine plot using new points
    X = [x[0][0], x[1][0]];
    Y = [x[0][1], x[1][1]];
    command = './julia ' + str(X[0]) + ' ' + str(X[1]) + ' ' + str(Y[0]) + ' ' + str(Y[1]) + ' 500 500';
    print(command);
    os.system(command);
    
    # Update and redraw plot
    plt.gca().clear();
    K = pylab.genfromtxt("JULIA", delimiter = ",");
    mandel = pylab.imshow(np.flipud(K.transpose())%colorperiod, extent=[X[0],X[1],Y[0],Y[1]]);
    #mandel.set_cmap('nipy_spectral');
    mandel.set_cmap('inferno');

