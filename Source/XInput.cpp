#include <windows.h>
#include "XInput.h"
#include "IniReader\IniReader.h"
#pragma comment(lib, "XInput.lib")

#define DLLEXPORT extern "C" __declspec(dllexport)

int TickCounter = 0;
bool QuickAccessLeft = false;
bool QuickAccessUp = false;
bool QuickAccessRight = false;
bool QuickAccessDown = false;
bool SniperRiffleMode = false;

int SkipPollCount = 0;
bool QuickAccess = true;
bool RightStickAIM = true;

DLLEXPORT BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CIniReader IniFile("xinput1_3.ini");
		QuickAccess = IniFile.ReadBoolean("Main", "QuickAccess", true);
		RightStickAIM = IniFile.ReadBoolean("Main", "RightStickAIM", true);
		break;
	}
	return TRUE;
}

DLLEXPORT DWORD WINAPI XInputGetState2(_In_ DWORD dwUserIndex, _Out_ XINPUT_STATE *pState)
{
	int Res = XInputGetState(dwUserIndex, pState);

	if (SkipPollCount == 0 && (GetAsyncKeyState(VK_LMENU) & 0x8000) != 0 && (GetAsyncKeyState('9') & 0x8000) != 0) {
		QuickAccess = !QuickAccess;
		SkipPollCount = 30;
	}

	if (SkipPollCount == 0 && (GetAsyncKeyState(VK_LMENU) & 0x8000) != 0 && (GetAsyncKeyState('0') & 0x8000) != 0) {
		RightStickAIM = !RightStickAIM;
		SkipPollCount = 30;
	}

	if (Res == ERROR_SUCCESS) {
		if (pState->Gamepad.wButtons & XINPUT_GAMEPAD_START) {
			pState->Gamepad.wButtons ^= XINPUT_GAMEPAD_START;
			pState->Gamepad.wButtons |= XINPUT_GAMEPAD_Y;
		}
		else if (pState->Gamepad.wButtons & XINPUT_GAMEPAD_Y) {
			pState->Gamepad.wButtons ^= XINPUT_GAMEPAD_Y;
			pState->Gamepad.wButtons |= XINPUT_GAMEPAD_START;
		}

		if (pState->Gamepad.bLeftTrigger > 0 && pState->Gamepad.wButtons & XINPUT_GAMEPAD_X)
			pState->Gamepad.wButtons |= XINPUT_GAMEPAD_A;

		if (RightStickAIM && pState->Gamepad.bLeftTrigger > 0) {
			if (SniperRiffleMode == false) {
				if (abs(pState->Gamepad.sThumbRX) > 0)
					pState->Gamepad.sThumbLX = pState->Gamepad.sThumbRX;
				if (abs(pState->Gamepad.sThumbRY) > 0)
					pState->Gamepad.sThumbLY = pState->Gamepad.sThumbRY;
			} else { 
				SHORT TempAxis = 0;
				TempAxis = pState->Gamepad.sThumbLX;
				pState->Gamepad.sThumbLX = pState->Gamepad.sThumbRX;
				pState->Gamepad.sThumbRX = TempAxis;
				TempAxis = pState->Gamepad.sThumbLY;
				pState->Gamepad.sThumbLY = pState->Gamepad.sThumbRY;
				pState->Gamepad.sThumbRY = TempAxis;
			}

		}

		if (pState->Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			pState->Gamepad.wButtons ^= XINPUT_GAMEPAD_RIGHT_SHOULDER;
			pState->Gamepad.wButtons |= XINPUT_GAMEPAD_A;
		}

		if (pState->Gamepad.wButtons & XINPUT_GAMEPAD_B)
			pState->Gamepad.wButtons |= XINPUT_GAMEPAD_RIGHT_SHOULDER;

		if (SkipPollCount == 0 && pState->Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) {
			SniperRiffleMode = !SniperRiffleMode;
			SkipPollCount = 30;
		}

		if (QuickAccess) {
			if (pState->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
				pState->Gamepad.wButtons ^= XINPUT_GAMEPAD_DPAD_LEFT;
				if (TickCounter == 0 && QuickAccessUp == false && QuickAccessLeft == false && QuickAccessRight == false && QuickAccessDown == false) {
					QuickAccessLeft = true;
					SniperRiffleMode = false;
					TickCounter = 230;
				}
			}
			else if (pState->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) {
				pState->Gamepad.wButtons ^= XINPUT_GAMEPAD_DPAD_UP;
				if (TickCounter == 0 && QuickAccessUp == false && QuickAccessLeft == false && QuickAccessRight == false && QuickAccessDown == false) {
					QuickAccessUp = true;
					SniperRiffleMode = false;
					TickCounter = 255;
				}
			}
			else if (pState->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
				pState->Gamepad.wButtons ^= XINPUT_GAMEPAD_DPAD_RIGHT;
				if (TickCounter == 0 && QuickAccessUp == false && QuickAccessLeft == false && QuickAccessRight == false && QuickAccessDown == false) {
					QuickAccessRight = true;
					SniperRiffleMode = false;
					TickCounter = 285;
				}
			}
			else if (pState->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
				pState->Gamepad.wButtons ^= XINPUT_GAMEPAD_DPAD_DOWN;
				if (TickCounter == 0 && QuickAccessUp == false && QuickAccessLeft == false && QuickAccessRight == false && QuickAccessDown == false) {
					QuickAccessDown = true;
					SniperRiffleMode = true;
					TickCounter = 315;
				}
			}
		}

		if (QuickAccessLeft) {
			if (TickCounter < 230 && TickCounter > 180)
				pState->Gamepad.wButtons |= pState->Gamepad.wButtons |= XINPUT_GAMEPAD_START;
		}

		if (QuickAccessUp) {
			if (TickCounter < 255 && TickCounter > 205)
				pState->Gamepad.wButtons |= pState->Gamepad.wButtons |= XINPUT_GAMEPAD_START;
			else if (TickCounter < 205 && TickCounter > 180)
				pState->Gamepad.wButtons |= pState->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
		}

		if (QuickAccessRight) {
			if (TickCounter < 285 && TickCounter > 235)
				pState->Gamepad.wButtons |= pState->Gamepad.wButtons |= XINPUT_GAMEPAD_START;
			else if (TickCounter < 235 && TickCounter > 180)
				pState->Gamepad.wButtons |= pState->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
		}

		if (QuickAccessDown) {
			if (TickCounter < 315 && TickCounter > 265)
				pState->Gamepad.wButtons |= pState->Gamepad.wButtons |= XINPUT_GAMEPAD_START;
			else if (TickCounter < 265 && TickCounter > 180)
				pState->Gamepad.wButtons |= pState->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
		}

		if (QuickAccessLeft || QuickAccessUp || QuickAccessRight || QuickAccessDown) {
			if (TickCounter < 180 && TickCounter > 130)
				pState->Gamepad.wButtons |= pState->Gamepad.wButtons |= XINPUT_GAMEPAD_A;
			else if (TickCounter < 100 && TickCounter > 50)
				pState->Gamepad.wButtons |= pState->Gamepad.wButtons |= XINPUT_GAMEPAD_A;
			else if (TickCounter < 50 && TickCounter > 1)
				pState->Gamepad.wButtons |= XINPUT_GAMEPAD_START;
		}

		if (TickCounter > 0) {
			if (TickCounter == 1) {
				QuickAccessLeft = false;
				QuickAccessUp = false;
				QuickAccessRight = false;
				QuickAccessDown = false;
			}
			TickCounter--;
		}
		if (SkipPollCount > 0)
			SkipPollCount--;
	}

	return Res;
}

DLLEXPORT DWORD WINAPI XInputSetState2(_In_ DWORD dwUserIndex, _In_ XINPUT_VIBRATION *pVibration)
{
	return XInputSetState(dwUserIndex, pVibration);
}


DLLEXPORT DWORD WINAPI XInputGetCapabilities2(_In_ DWORD dwUserIndex, _In_ DWORD dwFlags, _Out_ XINPUT_CAPABILITIES *pCapabilities)
{
	return ERROR_SUCCESS;
}

DLLEXPORT void WINAPI XInputEnable2(_In_ BOOL enable)
{

}

DLLEXPORT DWORD WINAPI XInputGetDSoundAudioDeviceGuids2(DWORD dwUserIndex, GUID* pDSoundRenderGuid, GUID* pDSoundCaptureGuid)
{
	return ERROR_SUCCESS;
}

DLLEXPORT DWORD WINAPI XInputGetBatteryInformation2(_In_ DWORD dwUserIndex, _In_ BYTE devType, _Out_ XINPUT_BATTERY_INFORMATION *pBatteryInformation)
{
	return ERROR_SUCCESS;
}

DLLEXPORT DWORD WINAPI XInputGetKeystroke2(DWORD dwUserIndex, DWORD dwReserved, PXINPUT_KEYSTROKE pKeystroke)
{
	return ERROR_SUCCESS;
}

DLLEXPORT DWORD WINAPI XInputGetStateEx2(_In_ DWORD dwUserIndex, _Out_ XINPUT_STATE *pState)
{
	return ERROR_SUCCESS;
}

DLLEXPORT DWORD WINAPI XInputWaitForGuideButton2(_In_ DWORD dwUserIndex, _In_ DWORD dwFlag, _In_ LPVOID pVoid)
{
	return ERROR_SUCCESS;
}

DLLEXPORT DWORD XInputCancelGuideButtonWait2(_In_ DWORD dwUserIndex)
{
	return ERROR_SUCCESS;
}

DLLEXPORT DWORD XInputPowerOffController2(_In_ DWORD dwUserIndex)
{
	return ERROR_SUCCESS;
}