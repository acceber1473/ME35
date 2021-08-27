
from flask import Flask, Response, render_template, request
import cv2
import serial
import time

ser = serial.Serial(

    port='/dev/ttyACM0',
    baudrate = 115200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1

)

cam = cv2.VideoCapture(0)

def gen_frames():

    while True:
        success, frame = cam.read()
        if not success:
            break
        else:
            ret, buffer = cv2.imencode(".jpg", frame)
            frame = buffer.tobytes()
            yield (
                b"--frame\r\n" b"Content-Type: image/jpeg\r\n\r\n" + frame + b"\r\n"
            )

app = Flask(__name__)
@app.route("/")

def index():
    return render_template("index.html")

@app.route("/<deviceName>/<action>")

def action(deviceName,action):
    if deviceName == 'motor':
        if action == 'left':
            print('LEFT')
            ser.write('drive.pwm(50,-30)\r\n'.encode(),)
            #send message to veer left

        if action == 'right':
            print('RIGHT')
            ser.write('drive.pwm(30,-50)\r\n'.encode(),)
            #send message to veer right

        if action == 'straight':
            print('STRAIGHT')
            ser.write('drive.pwm(50,-50)\r\n'.encode(),)
            #send message to go straight

        if action == 'stop':
            print('STOP')
            ser.write('drive.pwm(0,0)\r\n'.encode(),)
            #send message to stop motors

    return render_template("index.html")

@app.route("/video_feed")

def video_feed():
    return Response(gen_frames(), mimetype="multipart/x-mixed-replace; boundary=frame")

if __name__ == "__main__":
    app.run(debug=True)
