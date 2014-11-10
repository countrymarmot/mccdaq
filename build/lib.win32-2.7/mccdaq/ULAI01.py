from mccdaq import *
import WConio

def main():
    USB1208LS=MCCDAQ()
    
    WConio.clrscr() 
    print "Demonstration of AIn()\n"\
           "Press any key to quit.\n"

    # get the A/D channel to sample 
    Chan = int ( raw_input('Enter the channel to display: ') )

    print "\nThe raw data value on Channel %u is: " %Chan,
    (a,a,a,a,a,a,a,a,a,col,row)=WConio.gettextinfo() 
    print "\nThe voltage on Channel %u        is: " %Chan,
    
    # collect the sample from the channel until a key is pressed 
    while (WConio.kbhit()==False):
        DataValue=USB1208LS.AIn (0, Chan, BIP5VOLTS)
        EngUnits =USB1208LS.ToEngUnits (0, BIP5VOLTS, DataValue)

        WConio.gotoxy(col,row)  
        print "%5d" %DataValue,
        WConio.gotoxy(col,row+1)  
        print "%.2fV" %EngUnits,

if __name__ == '__main__':
    main()

