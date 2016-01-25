import RPi.GPIO as GPIO
import os
import time

def alert(channel):
    global start1
    if time.time()-start1 > 30:
        start1 = time.time()
        print('Motor Failure Detected: Imminent Threat to: Laundry')
        os.system("curl -X POST http://textbelt.com/text -d number=5558675309 -d message=\"SOS SMS: Zombie Apocalypse\nYour laundry is soggy!\"")
        os.system("curl -X POST http://textbelt.com/text -d number=5558675309 -d message=\"SOS SMS: Zombie Apocalypse\nYour laundry is soggy!\"")
        os.system("curl -X POST http://textbelt.com/text -d number=5558675309 -d message=\"SOS SMS: Zombie Apocalypse\nYour laundry is soggy!\"")

GPIO.setmode(GPIO.BCM)

GPIO.setup(23,GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(24,GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

start1 = 0.0
start2 = 0.0

print"system armed\n"

GPIO.add_event_detect(23,GPIO.RISING,callback = alert)
GPIO.add_event_detect(24,GPIO.RISING,callback = alert)

while True:
    #raw_input("press enter to exit")
    time.sleep(1)
    
