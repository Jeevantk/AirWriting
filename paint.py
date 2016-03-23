import cv2
import numpy as np
drawing=False
ix,iy=-1,-1
e=0

def nothing(x):
	pass
img = np.zeros((500,500,3), np.uint8)
cv2.namedWindow('image')



cv2.createTrackbar('Erase','image',0,1,nothing)

def draw_circle(event,x,y,flags,param):
	global ix,iy,drawing,e
	if event == cv2.EVENT_LBUTTONDOWN:
		drawing=True
		ix,iy=x,y
	elif event ==cv2.EVENT_MOUSEMOVE:
		if drawing==True:
			if e==1:
				cv2.rectangle(img,(ix,iy),(x,y),(0,0,0),-1)
			else:
				cv2.circle(img,(x,y),10,(255,255,255),-1)
	elif event ==cv2.EVENT_LBUTTONUP:
		drawing=False
		if e==1:
			cv2.rectangle(img,(ix,iy),(x,y),(0,0,0),-1)
		else:
			cv2.circle(img,(x,y),10,(255,255,255),-1)
cv2.setMouseCallback('image',draw_circle)

while(1):
	cv2.imshow('image',img)
	k=cv2.waitKey(1) & 0xFF
	if k==27:
		cv2.imwrite("digit.jpg",img)
		break
	
	e=cv2.getTrackbarPos('Erase','image')
cv2.destroyAllWindows()
	
