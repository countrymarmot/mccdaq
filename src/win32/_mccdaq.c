#include "cbw.h"
#include <Python.h>
#include <windows.h>

PyObject *_mccdaqError;
int status;
char Msg[BOARDNAMELEN];
/* ----------------------------------------------------- */

static char _mccdaq_cbErrHandling__doc__[] = "Initiates error handling";
static PyObject * _mccdaq_cbErrHandling(PyObject *self, PyObject *args)
{   int ErrReporting, ErrHandling;

    if (!PyArg_ParseTuple(args, "ii", &ErrReporting, &ErrHandling)) return NULL;
    status = cbErrHandling (ErrReporting, ErrHandling);
    return Py_BuildValue("i",status);
}


static char _mccdaq_cbAIn__doc__[] = "Reads an A/D Input Channel.";
static PyObject * _mccdaq_cbAIn(PyObject *self, PyObject *args)
{   int BoardNum, Chan, Gain;
    USHORT DataValue;
    
    if (!PyArg_ParseTuple(args, "iii", &BoardNum, &Chan, &Gain)) return NULL;
    status = cbAIn (BoardNum,  Chan,  Gain, &DataValue);
    return Py_BuildValue("(i,h)",status,DataValue);
    
}

static char _mccdaq_cbAInScan__doc__[] = "Scans a range of A/D Input Channels and stores the sample data in a list.";
static PyObject * _mccdaq_cbAInScan(PyObject *self, PyObject *args)
{   int BoardNum, LowChan, HighChan, Gain, Option;
    long Rate,Count;
    WORD ADData[20];
    
    if (!PyArg_ParseTuple(args, "iiiilli", &BoardNum, &LowChan, &HighChan, &Count, &Rate, &Gain, &Option)) return NULL;
    status = cbAInScan (BoardNum,  LowChan, HighChan, Count, &Rate, Gain, ADData, Option);
    return Py_BuildValue("i",status);
    
}

static char _mccdaq_cbAOut__doc__[] = "Writes to a D/A Output Channel";
static PyObject * _mccdaq_cbAOut(PyObject *self, PyObject *args)
{   int BoardNum, Chan, Gain;
    USHORT DataValue;
    
    if (!PyArg_ParseTuple(args, "iiih", &BoardNum, &Chan, &Gain, &DataValue)) return NULL;
    status = cbAOut (BoardNum,  Chan,  Gain, DataValue);
    return Py_BuildValue("i",status);
}

static char _mccdaq_cbToEngUnits__doc__[] = "Converts data in a voltage number";
static PyObject * _mccdaq_cbToEngUnits(PyObject *self, PyObject *args)
{   int BoardNum, Range;
    USHORT DataValue;
    float EngUnits;
    
    if (!PyArg_ParseTuple(args, "iih", &BoardNum, &Range, &DataValue)) return NULL;
    status = cbToEngUnits ( BoardNum, Range, DataValue, &EngUnits);
    return Py_BuildValue("i,f",status,EngUnits);
}

static char _mccdaq_cbFromEngUnits__doc__[] = "Converts a voltage number in a data";
static PyObject * _mccdaq_cbFromEngUnits(PyObject *self, PyObject *args)
{   int BoardNum, Range;
    USHORT DataValue;
    float EngUnits;
    
    if (!PyArg_ParseTuple(args, "iif", &BoardNum, &Range, &EngUnits)) return NULL;
    status = cbFromEngUnits ( BoardNum, Range, EngUnits, &DataValue);
    return Py_BuildValue("i,h",status,DataValue);
}

static char _mccdaq_cbDConfigPort__doc__[] = "Configures a Digital Port.";
static PyObject * _mccdaq_cbDConfigPort(PyObject *self, PyObject *args)
{   int BoardNum, PortNum, Direction;
    
    if (!PyArg_ParseTuple(args, "iii", &BoardNum, &PortNum, &Direction)) return NULL;
    status = cbDConfigPort (BoardNum, PortNum, Direction);
    return Py_BuildValue("i,",status);
    
}

static char _mccdaq_cbDIn__doc__[] = "Reads a Digital Input Port.";
static PyObject * _mccdaq_cbDIn(PyObject *self, PyObject *args)
{   int BoardNum, PortNum;
    USHORT DataValue;
    
    if (!PyArg_ParseTuple(args, "ii", &BoardNum, &PortNum )) return NULL;
    status = cbDIn (BoardNum, PortNum, &DataValue);
    return Py_BuildValue("(i,h)",status,DataValue);
}

static char _mccdaq_cbDBitIn__doc__[] = "Reads a single bit of a Digital Input Port.";
static PyObject * _mccdaq_cbDBitIn(PyObject *self, PyObject *args)
{   int BoardNum, PortType, BitNum;
    USHORT BitValue;
    
    if (!PyArg_ParseTuple(args, "iii", &BoardNum, &PortType, &BitNum)) return NULL;
    status = cbDBitIn (BoardNum, PortType, BitNum, &BitValue);
    return Py_BuildValue("(i,h)",status,BitValue);
}

static char _mccdaq_cbDOut__doc__[] = "Writes to a Digital Output Port.";
static PyObject * _mccdaq_cbDOut(PyObject *self, PyObject *args)
{   int BoardNum, PortNum;
    USHORT DataValue;
    
    if (!PyArg_ParseTuple(args, "iih", &BoardNum, &PortNum ,&DataValue)) return NULL;
    status = cbDOut (BoardNum, PortNum, DataValue);
    return Py_BuildValue("i",status);
}

static char _mccdaq_cbDBitOut__doc__[] = "Writes to a Digital Output Port.";
static PyObject * _mccdaq_cbDBitOut(PyObject *self, PyObject *args)
{   int BoardNum, PortType, BitNum;
    USHORT BitValue;
    
    if (!PyArg_ParseTuple(args, "iiih", &BoardNum, &PortType, &BitNum, &BitValue)) return NULL;
    status = cbDBitOut (BoardNum, PortType, BitNum, BitValue);
    return Py_BuildValue("i",status);
}

static char _mccdaq_cbC8254Config__doc__[] = "Configures the 8254 Counter .";
static PyObject * _mccdaq_cbC8254Config(PyObject *self, PyObject *args)
{   int BoardNum, CounterNum, Config;
    
    if (!PyArg_ParseTuple(args, "iii", &BoardNum, &CounterNum, &Config)) return NULL;
    status = cbC8254Config (BoardNum, CounterNum, Config);
    return Py_BuildValue("i,",status);
}

static char _mccdaq_cbCLoad__doc__[] = "Sends a starting value to the counter.";
static PyObject * _mccdaq_cbCLoad(PyObject *self, PyObject *args)
{   int BoardNum, RegName;
    unsigned int LoadValue;
    
    if (!PyArg_ParseTuple(args, "iih", &BoardNum, &RegName ,&LoadValue)) return NULL;
    status = cbCLoad (BoardNum, RegName, LoadValue);
    return Py_BuildValue("i",status);
}

static char _mccdaq_cbCLoad32__doc__[] = "Sends a starting value of 32 bits to the counter.";
static PyObject * _mccdaq_cbCLoad32(PyObject *self, PyObject *args)
{   int BoardNum, RegName;
    ULONG LoadValue;
    
    if (!PyArg_ParseTuple(args, "iih", &BoardNum, &RegName ,&LoadValue)) return NULL;
    status = cbCLoad (BoardNum, RegName, LoadValue);
    return Py_BuildValue("i",status);
}

static char _mccdaq_cbCIn__doc__[] = "Reads the counter.";
static PyObject * _mccdaq_cbCIn(PyObject *self, PyObject *args)
{   int BoardNum, CounterNum;
    USHORT Count;
    
    if (!PyArg_ParseTuple(args, "ii", &BoardNum, &CounterNum )) return NULL;
        
    status = cbCIn (BoardNum, CounterNum, &Count);
    return Py_BuildValue("(i,h)",status, Count);
}

static char _mccdaq_cbCIn32__doc__[] = "Reads a 32 bits counter.";
static PyObject * _mccdaq_cbCIn32(PyObject *self, PyObject *args)
{   int BoardNum, CounterNum;
    ULONG Count;
    
    if (!PyArg_ParseTuple(args, "ii", &BoardNum, &CounterNum )) return NULL;
        
    status = cbCIn32 (BoardNum, CounterNum, &Count);
    return Py_BuildValue("(i,l)",status, Count);
}

static char _mccdaq_cbCFreqIn__doc__[] = "Measures the frequency of a signal.";
static PyObject * _mccdaq_cbCFreqIn(PyObject *self, PyObject *args)
{   int BoardNum, SigSource, GateInterval;
    USHORT Count;
    long Freq;
    
    if (!PyArg_ParseTuple(args, "ii", &BoardNum, &SigSource, &GateInterval )) return NULL;
    status = cbCFreqIn (BoardNum,  SigSource, GateInterval, &Count, &Freq);
    return Py_BuildValue("(i,h,l)",status,Count,Freq);
}

static char _mccdaq_cbC9513Init__doc__[] = "Initialize the 9513 Counter .";
static PyObject * _mccdaq_cbC9513Init(PyObject *self, PyObject *args)
{   int BoardNum, ChipNum, FOutDivider,FOutSource, Compare1, Compare2, TimeOfDay;
    
    if (!PyArg_ParseTuple(args, "iiiiiii", &BoardNum, &ChipNum, &FOutDivider,&FOutSource, &Compare1, &Compare2, &TimeOfDay)) return NULL;
    status = cbC9513Init (BoardNum, ChipNum, FOutDivider, FOutSource, Compare1, Compare2, TimeOfDay);
    return Py_BuildValue("i",status);
}

static char _mccdaq_cbGetBoardName__doc__[] = "gets the board name.";
static PyObject * _mccdaq_cbGetBoardName(PyObject *self, PyObject *args)
{   int BoardNum;
    static char Msg[BOARDNAMELEN];
    
    if (!PyArg_ParseTuple(args, "i", &BoardNum)) return NULL;
    status = cbGetBoardName (BoardNum, Msg);
    //printf("%u\n",status);
    //printf("%s\n",Msg);
    return Py_BuildValue("s", &Msg[0]);
}

static char _mccdaq_cbGetErrMsg__doc__[] = "gets error message.";
static PyObject * _mccdaq_cbGetErrMsg(PyObject *self, PyObject *args)
{   int ErrCode;
    
    if (!PyArg_ParseTuple(args, "i", &ErrCode)) return NULL;
    status = cbGetErrMsg (ErrCode, &Msg[0]);
    return Py_BuildValue("s",&Msg[0]);
}

static char _mccdaq_cbFlashLED__doc__[] = "flashs led.";
static PyObject * _mccdaq_cbFlashLED(PyObject *self, PyObject *args)
{   int BoardNum;
    
    if (!PyArg_ParseTuple(args, "i", &BoardNum)) return NULL;
    status = cbFlashLED (BoardNum);
    return Py_BuildValue("i",status);
}

static char _mccdaq_cbGetConfig__doc__[] = "Gets Configuration.";
static PyObject * _mccdaq_cbGetConfig(PyObject *self, PyObject *args)
{   int InfoType, BoardNum, DevNum, ConfigItem, ConfigVal;
    
    if (!PyArg_ParseTuple(args, "iiii", &InfoType, &BoardNum, &DevNum, &ConfigItem)) return NULL;
    status = cbGetConfig (InfoType, BoardNum, DevNum, ConfigItem, &ConfigVal);
    return Py_BuildValue("(i,i)",status,ConfigVal);
}

static char _mccdaq_cbSetConfig__doc__[] = "Sets Configuration.";
static PyObject * _mccdaq_cbSetConfig(PyObject *self, PyObject *args)
{   int InfoType, BoardNum, DevNum, ConfigItem, ConfigVal;
    
    if (!PyArg_ParseTuple(args, "iiiii", &InfoType, &BoardNum, &DevNum, &ConfigItem,&ConfigVal)) return NULL;
    status = cbSetConfig (InfoType, BoardNum, DevNum, ConfigItem, ConfigVal);
    return Py_BuildValue("i",status);
}


/* List of methods defined in the module */
static struct PyMethodDef _mccdaq_methods[] = {
 {"ErrHandling",	_mccdaq_cbErrHandling,	1,	_mccdaq_cbErrHandling__doc__},
 {"AIn",    _mccdaq_cbAIn,   1,	_mccdaq_cbAIn__doc__},
 {"AInScan", _mccdaq_cbAInScan,   1, _mccdaq_cbAInScan__doc__},
 {"AOut",   _mccdaq_cbAOut,   1, _mccdaq_cbAOut__doc__},
 {"ToEngUnits",    _mccdaq_cbToEngUnits,   1, _mccdaq_cbToEngUnits__doc__},
 {"FromEngUnits",    _mccdaq_cbFromEngUnits,   1, _mccdaq_cbFromEngUnits__doc__},
 {"DConfigPort",   _mccdaq_cbDConfigPort,   1, _mccdaq_cbDConfigPort__doc__},
 {"DIn",    _mccdaq_cbDIn,   1,	_mccdaq_cbDIn__doc__},
 {"DBitIn",    _mccdaq_cbDBitIn,   1, _mccdaq_cbDBitIn__doc__},
 {"DOut",    _mccdaq_cbDOut,   1,	_mccdaq_cbDOut__doc__},
 {"DBitOut",    _mccdaq_cbDBitOut,   1, _mccdaq_cbDBitOut__doc__},
 {"C8254Config",   _mccdaq_cbC8254Config,   1, _mccdaq_cbC8254Config__doc__},
 {"CLoad",    _mccdaq_cbCLoad,   1, _mccdaq_cbCLoad__doc__},
 {"CLoad32",    _mccdaq_cbCLoad32,   1, _mccdaq_cbCLoad32__doc__}, 
 {"CIn",    _mccdaq_cbCIn,   1, _mccdaq_cbCIn__doc__}, 
 {"CIn32",    _mccdaq_cbCIn32,   1, _mccdaq_cbCIn32__doc__}, 
 {"CFreqIn",    _mccdaq_cbCFreqIn,   1,	_mccdaq_cbCFreqIn__doc__},
 {"C9513Init",    _mccdaq_cbC9513Init,   1,	_mccdaq_cbC9513Init__doc__},
 {"GetErrMsg",    _mccdaq_cbGetErrMsg,   1,	_mccdaq_cbGetErrMsg__doc__},
 {"GetBoardName",    _mccdaq_cbGetBoardName,   1,	_mccdaq_cbGetBoardName__doc__},
 {"FlashLED",    _mccdaq_cbFlashLED,   1,	_mccdaq_cbFlashLED__doc__},
 {"GetConfig",    _mccdaq_cbGetConfig,   1,	_mccdaq_cbGetConfig__doc__},
 {"SetConfig",    _mccdaq_cbSetConfig,   1,	_mccdaq_cbSetConfig__doc__},
 {NULL,	NULL}  /* sentinel */
};

/* Initialization function for the module (*must* be called init_mccdaq) */
static char _mccdaq_module_documentation[] = "_mccdaq object class: USB-DAQ interface";
void init_mccdaq(void)
{
	PyObject *m, *d;

	/* Create the module and add the functions */
	m = Py_InitModule4("_mccdaq", _mccdaq_methods, _mccdaq_module_documentation,
		(PyObject*)NULL, PYTHON_API_VERSION);

	/*m = Py_InitModule("_mccdaq", mccdaq_methods);*/
	
	/* Add some symbolic constants to the module */
	d = PyModule_GetDict(m);


	/* XXXX Add constants here */
	
	/* Check for errors */
	if (PyErr_Occurred())
        {
            Py_FatalError("module _mccdaq not initialized");
            _mccdaqError = PyString_FromString("module _mccdaq not initialized");
        }
        else _mccdaqError = PyString_FromString("");
        PyDict_SetItemString(d, "error", _mccdaqError);
}

