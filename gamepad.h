#ifndef GamePad_H
#define GamePad_H
/*


  File Name:		GamePad.h

  Author:			David B. Harding
					2410 Rollingwood Drive
					San Bruno CA, 94066
					david@baycitygame.com

					Copyright (c) 2021 Bay City Game

  Description:		Compilation Unit for GamePad Abstract Data Type
					Support for XBox Game Pad Controller type


  Classification:	C++ Header File

  History / Status:	Work in progress. Have not fully tested the GamePad code, I have primarily tested only "DWORD XIGetVKey(void);" I want to work on another topic
					So I will be moving on temporarily to an issue involving transparency colors.

  Known Bugs:		None


*/

#include "precompile.h"

class GamePad : public BaseAppObject
{
public:
	GamePad();
	virtual ~GamePad();

	static BOOL is_vibrating;
	
	enum XIUSER { id0 = 0, id1 = 1, id2 = 2, id3 = 3 };

	typedef struct CONNECTED_CONTROLLERS {
		BOOL id0_connected = FALSE;
		BOOL id1_connected = FALSE;
		BOOL id2_connected = FALSE;
		BOOL id3_connected = FALSE;
	} CONTROLLER_STATE, *PCONTROLLER_STATE;

	typedef struct LAST_VK {
		DWORD id0_vk = VK_PAD_START;
		DWORD id1_vk = VK_PAD_START;
		DWORD id2_vk = VK_PAD_START;
		DWORD id3_vk = VK_PAD_START;
	} LAST_VK, *PLAST_VK;

	static PXINPUT_CAPABILITIES pCapabilities;
	static PXINPUT_KEYSTROKE pKeystroke;
	static PCONTROLLER_STATE pControllerState;
	static PLAST_VK pLast_VK;

	

	void XIGetState(void);
	void XISetState(enum XIUSER Index);
	void XIGetCaps(void);				// get the gamepad capabilities
	DWORD XIGetVKey(void);				// get the gamepad virtualkey needed by Scene

	void XIDeadZoneFilter(void);
	
	static void XISetVibration(enum XIUSER Index);
	

	void XIGetAudioIDs(void);




};

#endif