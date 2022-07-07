import Jetson.GPIO as GPIO

channel1 = 37
channel2 = 18

GPIO.setmode(GPIO.BOARD)
GPIO.setup(channel1, GPIO.IN)   # 18
GPIO.setup(channel2, GPIO.IN)   # 37

while True:
    if (GPIO.input(channel1)==GPIO.LOW)and(GPIO.input(channel2)==GPIO.HIGH):
        flag = GPIO.HIGH
    else:
        flag = GPIO.LOW
    if (GPIO.input(channel1)==GPIO.HIGH)and(GPIO.input(channel2)==GPIO.LOW):
        flag2 = GPIO.HIGH
    else:
        flag2 = GPIO.LOW
    if (GPIO.input(channel1)==GPIO.HIGH)and(GPIO.input(channel2)==GPIO.HIGH):
        flag3 = GPIO.HIGH
    else:
        flag3 = GPIO.LOW
    print(flag,flag2,flag3)
