from mccdaq import *
import WConio

def main():

    USB1208LS=MCCDAQ()

    WConio.clrscr() 
    print "Demonstration of DOut()\n"\
           "Press any key to quit."

    USB1208LS.DConfigPort (0, FIRSTPORTA, DIGITALOUT)
    
    # get a user value to write to the port 
    DataValue=256
    while ((DataValue < 0) or (DataValue > 255)):
        DataValue = int ( raw_input('Enter a value to send to FIRSTPORTA (0-255):     ') )

    USB1208LS.DOut(0, FIRSTPORTA, DataValue)
    print "\nThe value %u was written to FIRSTPORTA. \n" \
           "see pin21-PA0    pin28-PA7"    %DataValue
    raw_input('\nPause')

if __name__ == '__main__':
    main()





