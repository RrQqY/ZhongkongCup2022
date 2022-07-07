import Jetson.GPIO as GPIO

def servoAction(POS):
    if POS[2] == 1:
        GPIO.output(40, GPIO.LOW)
    else:
        GPIO.output(40, GPIO.HIGH)

    if POS[1] == 1:
        GPIO.output(38, GPIO.LOW)
    else:
        GPIO.output(38, GPIO.HIGH)

    if POS[0] == 1:
        GPIO.output(33, GPIO.LOW)
    else:
        GPIO.output(33, GPIO.HIGH)

    if POS[5] == 1:
        GPIO.output(29, GPIO.LOW)
    else:
        GPIO.output(29, GPIO.HIGH)

    if POS[4] == 1:
        GPIO.output(21, GPIO.LOW)
    else:
        GPIO.output(21, GPIO.HIGH)

    if POS[3] == 1:
        GPIO.output(19, GPIO.LOW)
    else:
        GPIO.output(19, GPIO.HIGH)

GPIO.setmode(GPIO.BOARD)
GPIO.setup(40, GPIO.OUT)   # 8
GPIO.setup(38, GPIO.OUT)   # 9
GPIO.setup(33, GPIO.OUT)   # 10
GPIO.setup(29, GPIO.OUT)   # 11
GPIO.setup(21, GPIO.OUT)   # 12
GPIO.setup(19, GPIO.OUT)   # 13
while True:
    servoAction([1,1,1,0,0,0])
