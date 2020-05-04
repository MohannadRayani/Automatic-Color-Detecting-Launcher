import RPi.GPIO as GPIO #import GPIO from RPI Library
import time #Import Time in case we need delay

def turn(): #Define Method (Begin Method Turn())
    GPIO.setmode(GPIO.BOARD) #Set the Input and output board

    ControlPin = [11,16,15, 13] #Declare one dimensional array of pins to be used
    #(counter-Clockwise)

    for pin in ControlPin: #Enhanced for loop through the controlpins
        GPIO.setup(pin, GPIO.OUT) #Make every controlpin set for output
        GPIO.output(pin, 0) #output nothing for now (initialize)
        
    seq = [ [1,0,0,0], #Stepper motor sequence for full steps
            #[1,1,0,0],
            [0,1,0,0],
            #[0,1,1,0],
            [0,0,1,0],
            #[0,0,1,1],
            [0,0,0,1],
            #[1,0,0,1]
            ]
    for i in range(200): #Run for loop 200 times
        for halfstep in range(4): #run for loops 4 times
            for pin in range(4): #run for loop 4 times
                GPIO.output(ControlPin[pin], seq[halfstep][pin])
                #for each run, output to the pin needed and use sequence
                #for half-step or full step
                time.sleep(0.001) #delay a little
    GPIO.cleanup() #clean up all pins and reset them
#end Method Turn()
turn();#call defined method so we can call from outside compiler

#REFERENCES: GAVIN MACDONALD (youtube.com/watch?v=Dc16mKFA7Fo)