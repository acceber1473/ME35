from flask import Flask, Response, render_template
import serial
import sys
import os 
import numpy as np
import cv2
import time
import math

### Set up serial ###
os.chdir("/")
ser = serial.Serial(
    port = '/dev/ttyACM0',
    baudrate = 115200,
    parity = serial.PARITY_NONE,
    stopbits = serial.STOPBITS_ONE,
    bytesize = serial.EIGHTBITS,
    timeout = 1
)
### Set up Camera ###

# Call Haar Cascade classifier 
faceCascade = cv2.CascadeClassifier('/home/pi/Desktop/Midterm/haarcascade_frontalface_default.xml')
# Camera display settings 
cap = cv2.VideoCapture(0)    
cap.set(cv2.CAP_PROP_FPS, 2);   # Change fps to 2 to combat lag 
cap.set(3,640) # set Width
cap.set(4,480) # set Height

### Initialize Variables ###
prev_x = 1      # stores 1 x value in order to compare to current x 
center_x = 320  # center of the screen, aka the target value
kp = 0.1        # kp value of 0.1- low so that the motor corrects in small increments
error = 0       # initialize error as 0

### Main While Loop ###

while True:
    ret, img = cap.read()
    img = cv2.flip(img, 1,-1)    # flip the image about the y-axis 
    img = cv2.rotate(img, cv2.ROTATE_180)  # rotate image 180 bc camera mounted upside down
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.2,
        minNeighbors=5,
        minSize=(20,20)
    )  
    
    ## Retrieve parameters from Haar Cascade 
    for (x,y,w,h) in faces:
        cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
        roi_gray = gray[y:y+h, x:x+w]
        roi_color = img[y:y+h, x:x+w]
        
        # Calculate area of face rectangle in order to determine distance 
        area = int(w*h)
        # If area is large- person is close to camera and send that over to Wio via REPL
        if area >= 30000 and area%5 == 0:
            ser.write(('wio.write(str(%d)+" \n")\r\n'%(2)).encode())
        # If area is small- person is far from camera and sent that over to Wio via REPL
        if area <= 30000 and area%5 == 0:
            ser.write(('wio.write(str(%d)+" \n")\r\n'%(1)).encode())
            
        # Calculate x-value of person's face- center of face box 
        x_val = int(x + (w/2))
        # Calculate difference between current and previous x values
        diff = abs(x_val - prev_x)
        # Only send over the x_val if it differs by the previous value by 8 to reduce lag
        if diff > 8:
            error = center_x - x_val        # calculate error based on target value
            delta = (math.floor(kp*error))  # degrees motor needs to correct
            # Send over commands to SPIKE via REPl
            # Add delta onto the motor's current degree position
            # Use function run_to_position at a speed of 10 degrees 
            ser.write('current_pos = swivel.get()[0]\r\n'.encode())
            ser.write(('pos = current_pos+%d\r\n'%(delta)).encode())
            ser.write('swivel.run_to_position(pos,10)\r\n'.encode())
        
            prev_x = x_val # Set current value as new previous value 
        
    cv2.imshow('video',img)
    k = cv2.waitKey(30) & 0xff
    if k == 27: 
        break
cap.release()
cv2.destroyAllWindows()
