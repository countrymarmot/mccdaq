from mccdaq import *
import WConio

def main():

    USB1208LS=MCCDAQ()
    USB1208LS.FlashLED(0)
    
    USB1208LS.GetBoardName(0)
    i=USB1208LS.getStatus()
    print USB1208LS.GetErrMsg(i)

    print USB1208LS.GetConfig(BOARDINFO,0,0,BISERIALNUM)
    
    WConio.clrscr() 

    print "Demonstration of cbAOut() - chan0 pin13 - D/A 10bits"

    ExitFlag = False
    while (ExitFlag==False):

        WConio.gotoxy (0, 3)
        EngUnits = float ( raw_input('Enter a voltage between -5.0 and +5.0:  ') )

        DataValue=USB1208LS.FromEngUnits(0, BIP5VOLTS, EngUnits)
        USB1208LS.AOut (0, 0 , BIP5VOLTS, DataValue)
        
        print "%.2f volts has been sent to D/A 0.\n"\
               "Press Q to quit , any other key to continue: "  %EngUnits
        (ch,)=WConio.getch()
        
        if (ch=='q' or ch=='Q'): ExitFlag=True


if __name__ == '__main__':
    main()
