#include "input/InputManager.h"

#include <iostream>

namespace CS418
{
	InputManager::~InputManager()
	{

	}

	void InputManager::Initialize()
	{
		for (U32 i = 0; i < 256; i++)
			m_keys[i] = false;
	}

	void InputManager::Update(WPARAM wParam, bool isDown)
	{
		m_keys[wParam] = isDown;
	}

	bool InputManager::IsPressed(U32 key)
	{
		return m_keys[key];
	}

	U32 CS418_KEY_CANCEL = VK_CANCEL;
	U32 CS418_KEY_BACK = VK_BACK;
	U32 CS418_KEY_TAB = VK_TAB;
	U32 CS418_KEY_CLEAR = VK_CLEAR;
	U32 CS418_KEY_ENTER = VK_RETURN;
	U32 CS418_KEY_SHIFT = VK_SHIFT;
	U32 CS418_KEY_CONTROL = VK_CONTROL;
	U32 CS418_KEY_ALT = VK_MENU;
	U32 CS418_KEY_PAUSE = VK_PAUSE;
	U32 CS418_KEY_CAPS = VK_CAPITAL;
	U32 CS418_KEY_ESCAPE = VK_ESCAPE;
	U32 CS418_KEY_SPACE = VK_SPACE;
	U32 CS418_KEY_PAGEUP = VK_PRIOR;
	U32 CS418_KEY_PAGEDOWN = VK_NEXT;
	U32 CS418_KEY_END = VK_END;
	U32 CS418_KEY_HOME = VK_HOME;
	U32 CS418_KEY_LEFT = VK_LEFT;
	U32 CS418_KEY_UP = VK_UP;
	U32 CS418_KEY_RIGHT = VK_RIGHT;
	U32 CS418_KEY_DOWN = VK_DOWN;
	U32 CS418_KEY_SELECT = VK_SELECT;
	U32 CS418_KEY_PRINT = VK_PRINT;
	U32 CS418_KEY_EXECUTE = VK_EXECUTE;
	U32 CS418_KEY_PRTSCN = VK_SNAPSHOT;
	U32 CS418_KEY_INSERT = VK_INSERT;
	U32 CS418_KEY_DELETE = VK_DELETE;
	U32 CS418_KEY_HELP = VK_HELP;

	U32 CS418_KEY_0 = 0x30;
	U32 CS418_KEY_1 = 0x31;
	U32 CS418_KEY_2 = 0x32;
	U32 CS418_KEY_3 = 0x33;
	U32 CS418_KEY_4 = 0x34;
	U32 CS418_KEY_5 = 0x35;
	U32 CS418_KEY_6 = 0x36;
	U32 CS418_KEY_7 = 0x37;
	U32 CS418_KEY_8 = 0x38;
	U32 CS418_KEY_9 = 0x39;

	U32 CS418_KEY_A = 0x41;
	U32 CS418_KEY_B = 0x42;
	U32 CS418_KEY_C = 0x43;
	U32 CS418_KEY_D = 0x44;
	U32 CS418_KEY_E = 0x45;
	U32 CS418_KEY_F = 0x46;
	U32 CS418_KEY_G = 0x47;
	U32 CS418_KEY_H = 0x48;
	U32 CS418_KEY_I = 0x49;
	U32 CS418_KEY_J = 0x4A;
	U32 CS418_KEY_K = 0x4B;
	U32 CS418_KEY_L = 0x4C;
	U32 CS418_KEY_M = 0x4D;
	U32 CS418_KEY_N = 0x4E;
	U32 CS418_KEY_O = 0x4F;
	U32 CS418_KEY_P = 0x50;
	U32 CS418_KEY_Q = 0x51;
	U32 CS418_KEY_R = 0x52;
	U32 CS418_KEY_S = 0x53;
	U32 CS418_KEY_T = 0x54;
	U32 CS418_KEY_U = 0x55;
	U32 CS418_KEY_V = 0x56;
	U32 CS418_KEY_W = 0x57;
	U32 CS418_KEY_X = 0x58;
	U32 CS418_KEY_Y = 0x59;
	U32 CS418_KEY_Z = 0x5A;

	U32 CS418_KEY_LWIN = VK_LWIN;
	U32 CS418_KEY_RWIN = VK_RWIN;
	U32 CS418_KEY_APPS = VK_APPS;
	U32 CS418_KEY_SLEEP = VK_SLEEP;

	U32 CS418_KEY_NUMPAD0 = VK_NUMPAD0;
	U32 CS418_KEY_NUMPAD1 = VK_NUMPAD1;
	U32 CS418_KEY_NUMPAD2 = VK_NUMPAD2;
	U32 CS418_KEY_NUMPAD3 = VK_NUMPAD3;
	U32 CS418_KEY_NUMPAD4 = VK_NUMPAD4;
	U32 CS418_KEY_NUMPAD5 = VK_NUMPAD5;
	U32 CS418_KEY_NUMPAD6 = VK_NUMPAD6;
	U32 CS418_KEY_NUMPAD7 = VK_NUMPAD7;
	U32 CS418_KEY_NUMPAD8 = VK_NUMPAD8;
	U32 CS418_KEY_NUMPAD9 = VK_NUMPAD9;

	U32 CS418_KEY_MULTIPLY = VK_MULTIPLY;
	U32 CS418_KEY_ADD = VK_ADD;
	U32 CS418_KEY_SEPARATOR = VK_SEPARATOR;
	U32 CS418_KEY_SUBTRACT = VK_SUBTRACT;
	U32 CS418_KEY_DECIMAL = VK_DECIMAL;
	U32 CS418_KEY_DIVIDE = VK_DIVIDE;

	U32 CS418_KEY_F1 = VK_F1;
	U32 CS418_KEY_F2 = VK_F2;
	U32 CS418_KEY_F3 = VK_F3;
	U32 CS418_KEY_F4 = VK_F4;
	U32 CS418_KEY_F5 = VK_F5;
	U32 CS418_KEY_F6 = VK_F6;
	U32 CS418_KEY_F7 = VK_F7;
	U32 CS418_KEY_F8 = VK_F8;
	U32 CS418_KEY_F9 = VK_F9;
	U32 CS418_KEY_F10 = VK_F10;
	U32 CS418_KEY_F11 = VK_F11;
	U32 CS418_KEY_F12 = VK_F12;
	U32 CS418_KEY_F13 = VK_F13;
	U32 CS418_KEY_F14 = VK_F14;
	U32 CS418_KEY_F15 = VK_F15;
	U32 CS418_KEY_F16 = VK_F16;
	U32 CS418_KEY_F17 = VK_F17;
	U32 CS418_KEY_F18 = VK_F18;
	U32 CS418_KEY_F19 = VK_F19;
	U32 CS418_KEY_F20 = VK_F20;
	U32 CS418_KEY_F21 = VK_F21;
	U32 CS418_KEY_F22 = VK_F22;
	U32 CS418_KEY_F23 = VK_F23;
	U32 CS418_KEY_F24 = VK_F24;

	U32 CS418_KEY_NUMLOCK = VK_NUMLOCK;
	U32 CS418_KEY_SCROLLLOCK = VK_SCROLL;

	U32 CS418_KEY_LSHIFT = VK_LSHIFT;
	U32 CS418_KEY_RSHIFT = VK_RSHIFT;
	U32 CS418_KEY_LCONTROL = VK_LCONTROL;
	U32 CS418_KEY_RCONTROL = VK_RCONTROL;
	U32 CS418_KEY_LALT = VK_LMENU;
	U32 CS418_KEY_RALT = VK_RMENU;

	U32 CS418_KEY_PLUS = VK_OEM_PLUS;
	U32 CS418_KEY_COMMA = VK_OEM_COMMA;
	U32 CS418_KEY_MINUS = VK_OEM_MINUS;
	U32 CS418_KEY_PERIOD = VK_OEM_PERIOD;
}