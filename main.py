from pyfirmata2 import Arduino
from time import sleep
import pyfirmata2


board = Arduino('/dev/ttyUSB0')
led = board.get_pin('d:2:o')

while True:
    led.write(1)
    sleep(1)
    led.write(0)
    sleep(1)