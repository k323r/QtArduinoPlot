#!/usr/bin/python

import serial, time, struct, os

dev = "/dev/ttyACM0"

# create a serial object and connect it to /dev/ttyUSB0

arduino_serial = serial.Serial();
# arduino_serial.port = "/dev/ttyUSB0"
arduino_serial.port = dev
arduino_serial.baudrate = 115200
arduino_serial.bytesize = serial.EIGHTBITS
arduino_serial.parity = serial.PARITY_NONE
arduino_serial.stopbits = serial.STOPBITS_ONE
arduino_serial.timeout = None

try:
    arduino_serial.open()
except Exception, e:
    print "error opening serial port: ", dev," : ", str(e)
    exit()

if not os.path.isdir("./logs"):
	try:
		os.mkdir("./logs")
	except:
		print "could not create directory 'logs'"
		exit()

## create timestamp
timestring = time.strftime("%Y%m%d-%H%M%S")

log_name = './logs/' + timestring + '.log'
# log_name = './logs/telemetry.log'

log = open(log_name, 'w+')

log.writelines("# a b c d e f \n")

if arduino_serial.isOpen():
    arduino_serial.flushInput()
    arduino_serial.flushOutput()

'''

struct Data {

    float a;
    float b;
    float c;

    float d;
    float e;
    float f;
    
} data;

'''

FORMAT_STR = "ffffff"

size_struct = struct.calcsize(FORMAT_STR)
print size_struct

counter = 0

    # for binary data (later use)
while True:
    Byte = arduino_serial.read(1)
    if Byte == 'S':
        data = arduino_serial.read(size_struct)
        Byte = arduino_serial.read(1)
        if Byte == 'E':
			msg = str(struct.unpack(FORMAT_STR, data)).replace("(", "").replace(")", "")
			counter += 1
			if counter > 50:
				print (msg)
				counter = 0
			log.writelines(msg + "\n")
#    while True:
#        msg = arduino_serial.readline()
#        print "arduino_serial: " + msg
#        log.writelines(msg)


 
