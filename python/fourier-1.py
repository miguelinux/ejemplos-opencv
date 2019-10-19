#!/usr/bin/env python

'''
Taken from : https://opencv-python-tutroals.readthedocs.io/en/latest/py_tutorials/py_imgproc/py_transforms/py_fourier_transform/py_fourier_transform.html
'''

import cv2 as cv
import numpy as np
from matplotlib import pyplot as plt

img = cv.imread('../resources/lena.jpg', cv.IMREAD_GRAYSCALE)

f = np.fft.fft2(img)
fshift = np.fft.fftshift(f)
magnitude_spectrum = 20*np.log(np.abs(fshift))

plt.subplot(121)
plt.imshow(img, cmap = 'gray')
plt.title('Lenna'), plt.xticks([]), plt.yticks([])
plt.subplot(122),plt.imshow(magnitude_spectrum, cmap = 'gray')
plt.title('Espectro de magnitud'), plt.xticks([]), plt.yticks([])
plt.show()
