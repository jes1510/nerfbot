#-------------------------------------------------------------------------------
# Name:        Wii Remote - connect to Bluetooth cwiid
# Purpose:
#
# Author:      Brian Hensley
#
# Created:     21/07/2012
# Copyright:   (c) Brian 2012
#-------------------------------------------------------------------------------
#!/usr/bin/env python

import cwiid
import time
import serial
import wii
import math
import qik

q = qik.Qik('/dev/ttyUSB0', 9600)
#ser.open()

sentFlag = 0

'''
Nunchuk
forward:  x,228
back:  x,35
left:  27, x
right:  222,x
middle:  124, 134
'''



def main():

    print 'Press button 1 + 2 on your Wii Remote...'
    time.sleep(.1)
    wm=cwiid.Wiimote()
    print 'Wii Remote connected...'
    print '\nPress the PLUS button to disconnect the Wii and end the application'
    time.sleep(1)

    Rumble = False
    wm.rpt_mode = cwiid.RPT_BTN | cwiid.RPT_NUNCHUK

    global sentFlag
    speed = '128'

    while True:
        button = wm.state['buttons']
        print wm.state['nunchuk']['stick']
        stick_y = wm.state['nunchuk']['stick'][1]
        stick_x = wm.state['nunchuk']['stick'][0]

        x = remap(stick_x, 27, 222, -127, 127)
        y = remap(stick_y, 35, 228, -127, 127)
        print "X, Y", x, y
        print "Steering ->", steer(x, y)
        l_pwm, r_pwm = steer(x, y)

        if l_pwm < 0 :
            l_dir = 1
        else :
            l_dir = 0

        if r_pwm < 0 :
            r_dir = 1
        else :
            r_dir = 0

        l_pwm = abs(l_pwm)
        r_pwm = abs(r_pwm)

        q.moveM1(l_dir, l_pwm)
        q.moveM0(r_dir, r_pwm)

        #send('motor1 ' + str(l_pwm) + ' ' + str(l_dir))
        #send('motor2 ' + str(r_pwm) + ' ' + str(r_dir))

        time.sleep(0.1)


        if button == (wii.BTN_PLUS | wii.BTN_MINUS):
            print 'closing Bluetooth connection. Good Bye!'
            time.sleep(1)
            ser.close()
            exit(wm)

        if (button == wii.BTN_LEFT) and not(sentFlag & wii.BTN_LEFT):
            print "Left"
        #    send ('motor1 128 1')
        #    send ('motor2 128 0')
            sentFlag = wii.BTN_LEFT
            time.sleep(.5)


        if (button == wii.BTN_UP) and not(sentFlag & wii.BTN_UP) :
            print "forward"
        #    send('motor1 ' + speed + ' 0')
        #    send('motor2 ' + speed + ' 0')
            sentFlag = wii.BTN_UP
            time.sleep(.5)

        if (button  == wii.BTN_RIGHT) and not (sentFlag & wii.BTN_RIGHT):
            print "Right"
        #    send ('motor1 128 0')
        #    send ('motor2 128 1')
            sentFlag = wii.BTN_RIGHT
            time.sleep(.5)

        if (button == wii.BTN_DOWN) and not(sentFlag & wii.BTN_DOWN):
            print "back"
        #    send('motor1 ' + speed + ' 1')
        #    send('motor2 ' + speed + ' 1')
            sentFlag = wii.BTN_DOWN
            time.sleep(.5)
'''
	if (button == wii.BTN_1) :
   	    speed = '255'

	if (button != wii.BTN_1) :
	    speed = '128'

        if (button == 0 ) and not (sentFlag & 8192):
            send('stop1')
            send('stop2')
            sentFlag = 8192
            print "Stop"
'''
def remap (x, in_min, in_max, out_min, out_max) :
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min



def steer (x, y) :
    left_motor = x + y
    right_motor = x - y

# Scale factor defaults to 1
    scale_factor = 1

# Calculate scale factor
    if abs(left_motor) > 100 or abs(right_motor) > 100:
    # Find highest of the 2 values, since both could be above 100
        x = max(abs(left_motor), abs(right_motor))

    # Calculate scale factor
        scale_factor = 100.0 / x


    left_motor = int(left_motor * scale_factor) * -1
    right_motor = int(right_motor * scale_factor)

    l = remap(left_motor, -100, 100, -127, 127)
    r = remap(right_motor, -100, 100, -127, 127)

    return l, r


def send(command) :
    #ser.flush()
    out = command + '\n'
    print "Sending: '" + command + "'"
    #ser.write(out)

    print "Controller returned: " + ser.readline()



if __name__ == '__main__':
    main()
