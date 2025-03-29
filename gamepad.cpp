/*


  File Name:		GamePad.Cpp

  Author:			David B. Harding
					2410 Rollingwood Drive
					San Bruno CA, 94066
					david@baycitygame.com

					Copyright (c) 2021 - 2025 Bay City Game

  Description:		Compilation Unit for GamePad Abstract Data Type
					Support for XBox Game Pad Controller type
  
  
  Classification:	C++ Compilation Unit

  History / Status:	Work in progress.

  Known Bugs:		None


*/

#include "gamepad.h"


PXINPUT_CAPABILITIES GamePad::pCapabilities;
PXINPUT_KEYSTROKE GamePad::pKeystroke;
GamePad::PCONTROLLER_STATE GamePad::pControllerState;
GamePad::PLAST_VK GamePad::pLast_VK;
BOOL GamePad::is_vibrating;



//#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  7849
//#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689
//#define XINPUT_GAMEPAD_TRIGGER_THRESHOLD    30

GamePad::GamePad()
{


	TRACE("GamePad::GamePad invoked\n");

	// allocate memory for the data structure
	pCapabilities = new XINPUT_CAPABILITIES;
	pKeystroke = new XINPUT_KEYSTROKE;
	pControllerState = new CONTROLLER_STATE;
	pLast_VK = new LAST_VK;

	pKeystroke->Unicode = 0;
	pKeystroke->Flags = XINPUT_KEYSTROKE_KEYUP;
	pKeystroke->UserIndex = XUSER_INDEX_ANY;
	pKeystroke->HidCode = 0;
	pKeystroke->VirtualKey = VK_PAD_START;
	
	GamePad::is_vibrating = FALSE;

	XIGetState();


	if (GamePad::pCapabilities != NULL)
	{
		for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
		{
			DWORD dwResult = XInputGetCapabilities(i, XINPUT_FLAG_GAMEPAD, GamePad::pCapabilities);
			if (dwResult == ERROR_SUCCESS)
			{
				TRACE("XInputGetCapabilities returned Controller IS connected, on %ld\n", i);
				switch (i)
				{
				case 0:
					pControllerState->id0_connected = TRUE; // id0 was initialized with FALSE, here we see that there is a controller present on id0
					break;
				case 1:
					pControllerState->id1_connected = TRUE; // id1 was initialized with FALSE, here we see that there is a controller present on id1
					break;
				case 2:
					pControllerState->id2_connected = TRUE; // id2 was initialized with FALSE, here we see that there is a controller present on id2
					break;
				case 3:
					pControllerState->id3_connected = TRUE; // id3 was initialized with FALSE, here we see that there is a controller present on id3
					break;
				}

				// Controller is connected
			}
			else
			{
				TRACE("XInputGetCapabilities returned Controller is NOT connected on %ld\n", i);

				switch (i)
				{
				case 0:
					pControllerState->id0_connected = FALSE; // id0 was initialized with FALSE, here we see that there is no controller present on id0
					break;
				case 1:
					pControllerState->id1_connected = FALSE; // id1 was initialized with FALSE, here we see that there is no controller present on id1
					break;
				case 2:
					pControllerState->id2_connected = FALSE; // id2 was initialized with FALSE, here we see that there is no controller present on id2
					break;
				case 3:
					pControllerState->id3_connected = FALSE; // id3 was initialized with FALSE, here we see that there is no controller present on id3
					break;
				}
				// Controller is not connected
			}

		}
	}

}


GamePad::~GamePad()
{
	TRACE("GamePad::~GamePad invoked\n");

	delete(pCapabilities);
	delete(pKeystroke);
	delete(pControllerState);
	delete(pLast_VK);

}



void GamePad::XIGetState(void)
{

	TRACE("GamePad::XIGetState invoked\n");

	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(i, &state);
		if (dwResult == ERROR_SUCCESS)
		{
			TRACE("XInputGetState returned Controller IS connected, on %ld\n", i);
			switch (i)
			{
			case 0:
				pControllerState->id0_connected = TRUE; // id0 was initialized with FALSE, here we see that there is a controller present on id0
				break;
			case 1:
				pControllerState->id1_connected = TRUE; // id1 was initialized with FALSE, here we see that there is a controller present on id1
				break;
			case 2:
				pControllerState->id2_connected = TRUE; // id2 was initialized with FALSE, here we see that there is a controller present on id2
				break;
			case 3:
				pControllerState->id3_connected = TRUE; // id3 was initialized with FALSE, here we see that there is a controller present on id3
				break;
			}

			// Controller is connected
		}
		else
		{
			TRACE("XInputGetState returned Controller is NOT connected on %ld\n", i);

			switch (i)
			{
			case 0:
				pControllerState->id0_connected = FALSE; // id0 was initialized with FALSE, here we see that there is no controller present on id0
				break;
			case 1:
				pControllerState->id1_connected = FALSE; // id1 was initialized with FALSE, here we see that there is no controller present on id1
				break;
			case 2:
				pControllerState->id2_connected = FALSE; // id2 was initialized with FALSE, here we see that there is no controller present on id2
				break;
			case 3:
				pControllerState->id3_connected = FALSE; // id3 was initialized with FALSE, here we see that there is no controller present on id3
				break;
			}
			// Controller is not connected
		}
			
	}

}

void GamePad::XIGetAudioIDs(void)
{
	TRACE("GamePad::XIGetAudioIDs invoked\n");
	//HRESULT hr;

	//XInputGetDSoundAudioDeviceGuids(i, &dsRenderGuid, &dsCaptureGuid);

	//// Create IDirectSound8 using the controller's render device
	//if (FAILED(hr = DirectSoundCreate8(&dsRenderGuid, &pDS, NULL)))
	//	return hr;

	//// Set coop level to DSSCL_PRIORITY
	//if (FAILED(hr = pDS->SetCooperativeLevel(hWnd, DSSCL_NORMAL)))
	//	return hr;

	//// Create IDirectSoundCapture using the controller's capture device
	//if (FAILED(hr = DirectSoundCaptureCreate8(&dsCaptureGuid, &pDSCapture, NULL)))
	//	return hr;
	;

}

//
// currently only support for controller 0 or Index == id0
// Vibration starts easily but does not shut down so easily
void GamePad::XISetVibration(enum XIUSER Index)
{
	TRACE("GamePad::XISetVibration invoked\n");
	

	if (pControllerState->id0_connected == TRUE)
	{
		DWORD dwResult;

		XINPUT_VIBRATION vibration;
		vibration.wLeftMotorSpeed = 0; // use any value between 0-65535 here
		vibration.wRightMotorSpeed = 0; // use any value between 0-65535 here

		if (!GamePad::is_vibrating)					// turn off the vibration
		{
			ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
			vibration.wLeftMotorSpeed = 32000; // use any value between 0-65535 here
			vibration.wRightMotorSpeed = 16000; // use any value between 0-65535 here
			dwResult = XInputSetState(Index, &vibration);
			if (dwResult == ERROR_SUCCESS)
			{
				GamePad::is_vibrating = TRUE;
				// Controller is connected
			}
			else
			{
				// Controller is not connected
			}

		}
		else {																		// turn on the vibration

			ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));					
			vibration.wLeftMotorSpeed = 0; // use any value between 0-65535 here
			vibration.wRightMotorSpeed = 0; // use any value between 0-65535 here
			dwResult = XInputSetState(Index, &vibration);
			if (dwResult == ERROR_SUCCESS)
			{
				GamePad::is_vibrating = FALSE;
				// Controller is connected
			}
			else
			{
				// Controller is not connected
			}
		}

	}
}


void GamePad::XISetState(enum XIUSER Index)
{
	TRACE("GamePad::XISetState invoked\n");
	
	PXINPUT_VIBRATION pVibration;
	DWORD dwResult;

	pVibration = new XINPUT_VIBRATION;
	pVibration->wRightMotorSpeed = 32000;
	pVibration->wLeftMotorSpeed = 16000;
	
	dwResult = XInputSetState(Index, pVibration);
	if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected
	}
	else
	{
		// Controller is not connected
	}

	
}


void GamePad::XIGetCaps(void)
{
	TRACE("GamePad::XIGetCaps invoked\n");

	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{

		if (GamePad::pCapabilities != NULL)
		{
			dwResult = XInputGetCapabilities(i, XINPUT_FLAG_GAMEPAD, GamePad::pCapabilities);
			if (dwResult == ERROR_SUCCESS)
			{
				TRACE("XInputGetCapabilities returned Controller IS connected, on %ld\n", i);
				switch (i)
				{
				case 0:
					pControllerState->id0_connected = TRUE; // id0 was initialized with FALSE, here we see that there is a controller present on id0
					break;
				case 1:
					pControllerState->id1_connected = TRUE; // id1 was initialized with FALSE, here we see that there is a controller present on id1
					break;
				case 2:
					pControllerState->id2_connected = TRUE; // id2 was initialized with FALSE, here we see that there is a controller present on id2
					break;
				case 3:
					pControllerState->id3_connected = TRUE; // id3 was initialized with FALSE, here we see that there is a controller present on id3
					break;
				}

				// Controller is connected
			}
			else
			{
				TRACE("XInputGetCapabilities returned Controller is NOT connected on %ld\n", i);

				switch (i)
				{
				case 0:
					pControllerState->id0_connected = FALSE; // id0 was initialized with FALSE, here we see that there is no controller present on id0
					break;
				case 1:
					pControllerState->id1_connected = FALSE; // id1 was initialized with FALSE, here we see that there is no controller present on id1
					break;
				case 2:
					pControllerState->id2_connected = FALSE; // id2 was initialized with FALSE, here we see that there is no controller present on id2
					break;
				case 3:
					pControllerState->id3_connected = FALSE; // id3 was initialized with FALSE, here we see that there is no controller present on id3
					break;
				}
				// Controller is not connected
			}

		}
	}
}

DWORD GamePad::XIGetVKey(void)
{

		
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{

		dwResult = XInputGetKeystroke(i, 0, GamePad::pKeystroke);
		if (dwResult == ERROR_SUCCESS)
		{
			TRACE("XInputGetKeyStroke returned Controller IS connected, on %ld\n", i);
			switch (i)
			{
			case 0:
				pControllerState->id0_connected = TRUE; // id0 was initialized with FALSE, here we see that there is a controller present on id0
				pLast_VK->id0_vk = GamePad::pKeystroke->VirtualKey;
				return pLast_VK->id0_vk;
				break;
			case 1:
				pControllerState->id1_connected = TRUE; // id1 was initialized with FALSE, here we see that there is a controller present on id1
				pLast_VK->id1_vk = GamePad::pKeystroke->VirtualKey;
				return pLast_VK->id1_vk;
				break;
			case 2:
				pControllerState->id2_connected = TRUE; // id2 was initialized with FALSE, here we see that there is a controller present on id2
				pLast_VK->id2_vk = GamePad::pKeystroke->VirtualKey;
				return pLast_VK->id2_vk;
				break;
			case 3:
				pControllerState->id3_connected = TRUE; // id3 was initialized with FALSE, here we see that there is a controller present on id3
				pLast_VK->id3_vk = GamePad::pKeystroke->VirtualKey;
				return pLast_VK->id3_vk;
				break;
			}

			// Controller is connected
		}
		else
		{
			TRACE("XInputGetKeyStroke returned Controller is NOT connected on %ld\n", i);

			switch (i)
			{
			case 0:
				pControllerState->id0_connected = FALSE; // id0 was initialized with FALSE, here we see that there is no controller present on id0
				return pLast_VK->id0_vk;
				break;
			case 1:
				pControllerState->id1_connected = FALSE; // id1 was initialized with FALSE, here we see that there is no controller present on id1
				return pLast_VK->id1_vk;
				break;
			case 2:
				pControllerState->id2_connected = FALSE; // id2 was initialized with FALSE, here we see that there is no controller present on id2
				return pLast_VK->id2_vk;
				break;
			case 3:
				pControllerState->id3_connected = FALSE; // id3 was initialized with FALSE, here we see that there is no controller present on id3
				return pLast_VK->id3_vk;
				break;
			}
			// Controller is not connected

		}

	}

	return 1; // no other control path was satisfied. Could be here if all controllers were unplugged
}

void GamePad::XIDeadZoneFilter(void)
{
	TRACE("GamePad::XIDeadZoneFilter invoked\n");

	class Controllers
	{
	public:
		XINPUT_STATE state;

	};

	float INPUT_DEADZONE = 32767;	// this is an arbitrary number and must be adjusted based on game play in the range of 0..65534
	short int i = 0;
	Controllers g_Controllers[XUSER_MAX_COUNT];


	for (i = 0; i < XUSER_MAX_COUNT; i++)
	{

		XINPUT_STATE state = g_Controllers[i].state;

		float LX = state.Gamepad.sThumbLX;
		float LY = state.Gamepad.sThumbLY;

		//determine how far the controller is pushed
		double magnitude = sqrt(LX * LX + LY * LY);

		//determine the direction the controller is pushed
		float normalizedLX = LX / magnitude;
		float normalizedLY = LY / magnitude;

		float normalizedMagnitude = 0;

		//check if the controller is outside a circular dead zone
		if (magnitude > INPUT_DEADZONE)
		{
			//clip the magnitude at its expected maximum value
			if (magnitude > 32767) magnitude = 32767;

			//adjust magnitude relative to the end of the dead zone
			magnitude -= INPUT_DEADZONE;

			//optionally normalize the magnitude with respect to its expected range
			//giving a magnitude value of 0.0 to 1.0
			normalizedMagnitude = magnitude / (32767 - INPUT_DEADZONE);
		}
		else //if the controller is in the deadzone zero out the magnitude
		{
			magnitude = 0.0;
			normalizedMagnitude = 0.0;
		}

		//repeat for right thumb stick
	}
}

