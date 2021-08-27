import hub,utime
import math

# Setup and initilize sensors 
drive = hub.port.A.motor.pair(hub.port.B.motor) # pairs motors
drive.pwm(0,0)              # start motors off at 0,0
sonar = hub.port.E.device   # ultrasonic sensor
color = hub.port.C.device   # color sensor

# Initializing constants 
target = 99    # target ambient light value for white tape
kp = 1.8       # gain factor  
scale = 0.7   # scaling factor for delta 
error = 0   # intializing error

# Main Loop with proportional controller for color sensor
while True:
    dist = sonar.get()[0]      # retrieve current distance value
    color_level=color.get()[0] # retrieve current light ambience level
    colorGreen=color.get()[2]  # retrieve current red color level 
    utime.sleep(0.005)            # comparing red levels, not green because 
                                    # the carpet has too much green
    if dist is not None and dist < 10:  # if object close, beeps and stops
        drive.pwm(0,0)                  # also filters out none type values 
        hub.sound.beep(350, 350, 3)
    else:
        if colorGreen <= 700 and colorGreen >= 600:  # prints green if detects green
            print("Green!!!!")
        error=target-color_level   # error between target and actual value
        delta=math.floor(kp*error*scale) # delta is how much needs to be adjusted 
        speed_A=35+delta  # new speed for one motor
        speed_B=35-delta  # new speed for other motor
        drive.pwm(speed_A, -speed_B)          
drive.pwm(0,0)
 
