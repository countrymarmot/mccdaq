from mccdaq import *
import WConio

def main():

    USB1208LS=MCCDAQ()

    WConio.clrscr() 
    print "Demonstration of cbDIn()\n"\
           "Press any key to quit.\n\n"\
           "You may change a bit by applying a TTL high or\n"\
           "a TTL low to the corresponding pin# on port A.\n"

    print "The first 7 bits are: pin32 to pin 39\n"\
           "0  1  2  3  4  5  6  7\n "
    (a,a,a,a,a,a,a,a,a,a,row)=WConio.gettextinfo() 
    
    USB1208LS.DConfigPort (0, FIRSTPORTB, DIGITALIN)

    while (WConio.kbhit()==False):
        DataValue=USB1208LS.DIn(0, FIRSTPORTB)
        WConio.gotoxy(0,row)  
        print "Port Value: %d         " %DataValue

        # parse DataValue into bit values to indicate on/off status */
        for I in range (8):
            if (DataValue & 2**I):  BitValue = 1
            else:  BitValue = 0
            print "%d " %BitValue,


if __name__ == '__main__':
    main()
