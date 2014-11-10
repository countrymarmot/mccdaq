from mccdaq import *
import WConio
import sys

def main():
    USB1208LS=MCCDAQ()
    
    WConio.clrscr() 
    print "Demonstration of voltage conversions.\n"\
           "Press any key to quit.\n"

    # get the A/D channel to sample 
    Chan = int ( raw_input('Enter the channel to display: ') ) 

    print "\n\nNote: Please make certain that the board you are using supports\n"\
           "      the gain you are choosing and if it is not a programmable\n"\
           "      gain that the switches on the board are set correctly.\n\n"
    
    BoardNum = 0
    Gain = BIPPT625VOLTS
    
    # collect the sample with cbAIn() */
    while (Gain > 0):
        # select gain */
        WConio.gotoxy(0,10)
        while 1:
            Gain = int ( raw_input ("Please select one of the following ranges(1 to 4):\n"\
                                    "                           10 VOLTS UNIPOLAR --> 1\n"\
                                    "                           10 VOLTS BIPOLAR ---> 2\n"\
                                    "                            5 VOLTS UNIPOLAR --> 3\n"\
                                    "                            5 VOLTS BIPOLAR ---> 4\n"\
                                    "                                       Quit ---> 0\n\n"\
                                    "                                Your Choice ---> "))
            if  ( (Gain >= 0) and (Gain <= 4) ): break
        
        # Set Gain, MaxVal, and MinVal */
        if   (Gain==0): sys.exit(1)
        elif (Gain==1): Gain = UNI10VOLTS
        elif (Gain==2): Gain = BIP10VOLTS
        elif (Gain==3): Gain = UNI5VOLTS
        elif (Gain==4): Gain = BIP5VOLTS

        if (Gain >= 0):
            DataValue=USB1208LS.AIn (BoardNum, Chan, Gain)
            EngUnits =USB1208LS.ToEngUnits(BoardNum, Gain, DataValue)
            print "\nThe voltage on channel %d is %.2f " %(Chan, EngUnits)
            
        Gain = BIPPT625VOLTS
    
if __name__ == '__main__':
    main()


