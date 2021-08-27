from flask import Flask, Response, render_template
import serial
import time
import sys
import os

os.chdir("/")
ser = serial.Serial(
    port='/dev/serial0',
    baudrate = 115200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)

while True:
    hour = int(time.strftime("%I"))
    hour_conv = round((hour/12),5)
    hour_degrees = round(hour_conv*360)

    time.sleep(1)

    minute = int(time.strftime("%M"))
    minute_conv = round((minute/60),5)
    minute_degrees = round(minute_conv*360)

    ser.write(('%d,%d\r\n'%(hour_degrees, minute_degrees)).encode())
