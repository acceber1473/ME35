import hub, utime
import math 

# initialize motor sensors and wio 
rightMotor = hub.port.D.motor
leftMotor = hub.port.C.motor
utime.sleep(0.005)
wio = hub.port.F
wio.mode(hub.port.MODE_FULL_DUPLEX)
wio.baud(9600)

rightMotor.mode(2)
leftMotor.mode(2)

# get starting degree values for right and left motors 
rightStart = rightMotor.get()[0]
leftStart = leftMotor.get()[0]

# arrays containing relative position adjustment values for right and left motors
positionsRight = [-2, -1, 4, 5, 5, 8, 17, 26, 37, 52, 64, 74, 84, 86, 86, 81, 75, 71, 63, 55, 49, 41, 34, 30, 28]
positionsLeft = [-10, -17, -26, -34, -39, -44, -48, -50, -50, -44, -36, -24, -11, 1, 10, 18, 23, 27, 29, 30, 32, 36, 36, 36, 36]

# MATH PART #

# setting lengths of legos/spacing 
L1 = 325
L2 = 400
a = 212.5

# arrays containing resultant x,y coordinates from degrees
xvalues = []
yvalues = []

# MAIN LOOP# 

# nested for loop that draws 'c' backwards and forwards 4 times to make it look better lol

for y in range(4):  

    # makes sure motor is at starting positions 
    rightMotor.run_to_position(rightStart,10)
    leftMotor.run_to_position(leftStart,10)
    
    # draws 'c' forwards 
    for x in range(len(positionsRight)):
        rightMotor.run_to_position(rightStart+positionsRight[x],15)
        leftMotor.run_to_position(leftStart+positionsLeft[x],15)
        utime.sleep(0.5)
        
        beta1 = positionsRight[x]  # right motor angle
        beta2 = positionsLeft[x]-180   # left motor angle
        beta1 = beta1*((math.pi)/180) # converts to rad
        beta2 = beta2*((math.pi)/180) 
        # math from chris
        A = (L1/L2)*(math.sin(beta1)-math.sin(math.pi-beta2))
        B = (a/L2)*(L1/L2)*(math.cos(beta1)+math.cos(math.pi-beta2))
        L = math.sqrt(A**2+B**2)
        theta = math.atan(A/B)
        C = (2-L**2)/2
        sigma = math.acos((2-L**2)/2)
        gamma2 = 0.5*(math.pi-sigma+2*theta)
        gamma1 = gamma2-2*theta
        # x value 
        x = (a/2)+L1*math.cos(beta1)-L2*math.cos(gamma1)
        xvalues.append(x)
        # send over to wio
        #wio.write(str(x) + ' \n')
        #print("sent over x")
        #utime.sleep(0.5)
        # y value
        y = L1*math.sin(beta1)+L2*math.sin(gamma1)
        yvalues.append(y)
       # wio.write(str(y) + ' \n')
       # print("sent over y")
        wio.write(str(y) + ',' + str(x) + ' \n')
        x
        y
        utime.sleep(1)
        theta = theta*(180/math.pi)
        sigma = sigma*(180/math.pi)
        gamma1 = gamma1*(180/math.pi)
        gamma2 = gamma2*(180/math.pi)

    # draws 'c' backwards
    for i in range(len(positionsRight)-1, -1, -1):
        rightMotor.run_to_position(rightStart+positionsRight[i],15)
        leftMotor.run_to_position(leftStart+positionsLeft[i],15)
        utime.sleep(0.5)  
        
        beta1 = positionsRight[i]  # right motor angle
        beta2 = positionsLeft[i]-180   # left motor angle
        beta1 = beta1*((math.pi)/180) # converts to rad
        beta2 = beta2*((math.pi)/180) 
        # math from chris
        A = (L1/L2)*(math.sin(beta1)-math.sin(math.pi-beta2))
        B = (a/L2)*(L1/L2)*(math.cos(beta1)+math.cos(math.pi-beta2))
        L = math.sqrt(A**2+B**2)
        theta = math.atan(A/B)
        C = (2-L**2)/2
        sigma = math.acos((2-L**2)/2)
        gamma2 = 0.5*(math.pi-sigma+2*theta)
        gamma1 = gamma2-2*theta
        # x value 
        x = (a/2)+L1*math.cos(beta1)-L2*math.cos(gamma1)
        xvalues.append(x)
        # send over to wio
        #wio.write(str(x) + ' \n')
        #print("sent over x")
        #utime.sleep(0.5)
        # y value
        y = L1*math.sin(beta1)+L2*math.sin(gamma1)
        yvalues.append(y)
       # wio.write(str(y) + ' \n')
       # print("sent over y")
        wio.write(str(y) + ',' + str(x) + ' \n')
        x
        y
        utime.sleep(1)
        theta = theta*(180/math.pi)
        sigma = sigma*(180/math.pi)
        gamma1 = gamma1*(180/math.pi)
        gamma2 = gamma2*(180/math.pi)
        

#positionsLeft
#positionsRight
#xvalues
#yvalues



    
    
