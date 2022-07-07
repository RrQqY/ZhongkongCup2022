import Jetson.GPIO as GPIO
import time as time

stmpin = 18
GPIO.setmode(GPIO.BOARD)
GPIO.setup(stmpin, GPIO.IN)
try:
    while True:
        flag = GPIO.input(stmpin)
        if flag == GPIO.HIGH:
            print("find")
finally:
    GPIO.cleanup()

