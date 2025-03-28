# XBOX Controller Code
C++ Source code, which the public can download
You will need to include:
XINPUT.LIB
in your library path


//This is what I have in my code. You can use this also. It needs to be instantiated early in program execution.
// Mine is loading when I instantiate a video class library. It seems to do the trick so far.


HRESULT rtn = CoInitializeEx(NULL, COINIT_MULTITHREADED);

switch (rtn)
{

	case S_OK:
 
		TRACE("CoInitializeEx(NULL, COINIT_MULTITHREADED) returned S_OK\n");
  
		break;
  
	case S_FALSE:
 
		TRACE("CoInitializeEx(NULL, COINIT_MULTITHREADED) returned S_FALSE\n");
  
		break;
  
	case RPC_E_CHANGED_MODE:
 
		TRACE("CoInitializeEx(NULL, COINIT_MULTITHREADED) returned RPC_E_CHANGED_MODE\n");
  
		break;
  
	default:
 
		break;
  
};

