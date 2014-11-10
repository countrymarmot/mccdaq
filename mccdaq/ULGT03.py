from mccdaq import *
import WConio


def PrintADInfo (BoardNum):
	NumDevs=USB1208LS.GetConfig (BOARDINFO, BoardNum, 0, BINUMADCHANS)
	print"    Number of A/D channels: %d " %NumDevs

def PrintDAInfo (BoardNum):
	NumDevs=USB1208LS.GetConfig (BOARDINFO, BoardNum, 0, BINUMDACHANS)
	print "    Number of D/A channels: %d " %NumDevs

def PrintDigInfo (BoardNum):
    # get the number of digital devices for this board 
    NumDevs=USB1208LS.GetConfig (BOARDINFO, BoardNum, 0, BIDINUMDEVS)
    for i in range (NumDevs) :
        # For each digital device, get the number of bits 
        NumBits=USB1208LS.GetConfig (DIGITALINFO, BoardNum, i, DINUMBITS)
        print "    Digital Device #%d : %d bits" %(i, NumBits)
        
def PrintCtrInfo (BoardNum):
    # Get the number of counter devices for this board 
    NumDevs=USB1208LS.GetConfig (BOARDINFO, BoardNum, 0, BICINUMDEVS)
    print "    Counter Devices : %d" %NumDevs
    
def PrintExpInfo (BoardNum):
    NumDevs=USB1208LS.GetConfig (BOARDINFO, BoardNum, 0, BINUMEXPS)
    for DevNum in range(NumDevs):
        BoardType=SB1208LS.GetConfig (EXPANSIONINFO, BoardNum, DevNum, XIBOARDTYPE)
        ADChan1=SB1208LS.GetConfig (EXPANSIONINFO, BoardNum, DevNum, XIMUX_AD_CHAN1)
        if (BoardType==770):
            # it's a CIO-EXP32 occupying 2 A/D channels
            ADChan2=SB1208LS.GetConfig (EXPANSIONINFO, BoardNum, DevNum, XIMUX_AD_CHAN2)
            print "        A/D channels #%d and #%d connected to EXP(devID=%d)" %(ADChan1, ADChan2, BoardType)
        else: print "        A/D chan #%d connected to EXP(devID=%d)\n" %(ADChan1, BoardType)
      
      
def main():
   
    WConio.clrscr() 
    print "Demonstration of GetConfig().\n"\
          "List of Installed Boards:\n"
           
    # Get the number of boards installed in system 
    NumBoards=USB1208LS.GetConfig (GLOBALINFO, 0, 0, GINUMBOARDS)
    USB1208LS.SetConfig (BOARDINFO, 0, 0, BINUMADCHANS,8)  # single ended
    #USB1208LS.SetConfig (BOARDINFO, 0, 0, BINUMADCHANS,4)  # diff ended
    
    for i in range(NumBoards):
        # Get board type of each board 
        BoardType=USB1208LS.GetConfig (BOARDINFO, i, 0, BIBOARDTYPE)

        # If a board is installed 
        if (BoardType > 0):
             # Get the board's name 
            BoardNameStr=USB1208LS.GetBoardName (i)
            print "    Board #%d = %s" %(i,BoardNameStr)

            # Get the board's base address 
            BaseAdr=USB1208LS.GetConfig (BOARDINFO, i, 0, BIBASEADR)
            print "    Base Address = 0x%x" %BaseAdr

            PrintADInfo (i)
            PrintDAInfo (i)
            PrintDigInfo (i)
            PrintCtrInfo (i)
            PrintExpInfo (i)
   
    raw_input("\npause")
    
if __name__ == '__main__':
    USB1208LS=MCCDAQ()
    main()









