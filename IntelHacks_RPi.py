from firebase import firebase
import serial

arduinoSerialData = serial.Serial('/dev/ttyACM1',9600)
firebase = firebase.FirebaseApplication('https://intel-hacks.firebaseio.com/',None)

while(1):
    line = arduinoSerialData.readline()
    if int(line) == 1:
        print line
        new_user = 'Address'
        new_serial = 'Serial - 4a3re89'
        result = firebase.post('/Address',new_address)
    else:
        print line
        print 'no hit'
