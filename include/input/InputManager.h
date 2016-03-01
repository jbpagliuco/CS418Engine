#pragma once

#include <Windows.h>

#include "util/Util.h"

namespace CS418
{
	class InputManager
	{
	public:
		virtual ~InputManager();

		void Initialize();

		void Update(WPARAM wParam, bool isDown);

		bool IsPressed(U32 key);

	private:
		bool m_keys[256];
	};


	extern U32 CS418_KEY_CANCEL;
	extern U32 CS418_KEY_BACK;
	extern U32 CS418_KEY_TAB;
	extern U32 CS418_KEY_CLEAR;
	extern U32 CS418_KEY_ENTER;
	extern U32 CS418_KEY_SHIFT;
	extern U32 CS418_KEY_CONTROL;
	extern U32 CS418_KEY_ALT;
	extern U32 CS418_KEY_PAUSE;
	extern U32 CS418_KEY_CAPS;
	extern U32 CS418_KEY_ESCAPE;
	extern U32 CS418_KEY_SPACE;
	extern U32 CS418_KEY_PAGEUP;
	extern U32 CS418_KEY_PAGEDOWN;
	extern U32 CS418_KEY_END;
	extern U32 CS418_KEY_HOME;
	extern U32 CS418_KEY_LEFT;
	extern U32 CS418_KEY_UP;
	extern U32 CS418_KEY_RIGHT;
	extern U32 CS418_KEY_DOWN;
	extern U32 CS418_KEY_SELECT;
	extern U32 CS418_KEY_PRINT;
	extern U32 CS418_KEY_EXECUTE;
	extern U32 CS418_KEY_PRTSCN;
	extern U32 CS418_KEY_INSERT;
	extern U32 CS418_KEY_DELETE;
	extern U32 CS418_KEY_HELP;

	extern U32 CS418_KEY_0;
	extern U32 CS418_KEY_1;
	extern U32 CS418_KEY_2;
	extern U32 CS418_KEY_3;
	extern U32 CS418_KEY_4;
	extern U32 CS418_KEY_5;
	extern U32 CS418_KEY_6;
	extern U32 CS418_KEY_7;
	extern U32 CS418_KEY_8;
	extern U32 CS418_KEY_9;

	extern U32 CS418_KEY_A;
	extern U32 CS418_KEY_B;
	extern U32 CS418_KEY_C;
	extern U32 CS418_KEY_D;
	extern U32 CS418_KEY_E;
	extern U32 CS418_KEY_F;
	extern U32 CS418_KEY_G;
	extern U32 CS418_KEY_H;
	extern U32 CS418_KEY_I;
	extern U32 CS418_KEY_J;
	extern U32 CS418_KEY_K;
	extern U32 CS418_KEY_L;
	extern U32 CS418_KEY_M;
	extern U32 CS418_KEY_N;
	extern U32 CS418_KEY_O;
	extern U32 CS418_KEY_P;
	extern U32 CS418_KEY_Q;
	extern U32 CS418_KEY_R;
	extern U32 CS418_KEY_S;
	extern U32 CS418_KEY_T;
	extern U32 CS418_KEY_U;
	extern U32 CS418_KEY_V;
	extern U32 CS418_KEY_W;
	extern U32 CS418_KEY_X;
	extern U32 CS418_KEY_Y;
	extern U32 CS418_KEY_Z;

	extern U32 CS418_KEY_LWIN;
	extern U32 CS418_KEY_RWIN;
	extern U32 CS418_KEY_APPS;
	extern U32 CS418_KEY_SLEEP;

	extern U32 CS418_KEY_NUMPAD0;
	extern U32 CS418_KEY_NUMPAD1;
	extern U32 CS418_KEY_NUMPAD2;
	extern U32 CS418_KEY_NUMPAD3;
	extern U32 CS418_KEY_NUMPAD4;
	extern U32 CS418_KEY_NUMPAD5;
	extern U32 CS418_KEY_NUMPAD6;
	extern U32 CS418_KEY_NUMPAD7;
	extern U32 CS418_KEY_NUMPAD8;
	extern U32 CS418_KEY_NUMPAD9;

	extern U32 CS418_KEY_MULTIPLY;
	extern U32 CS418_KEY_ADD;
	extern U32 CS418_KEY_SEPARATOR;
	extern U32 CS418_KEY_SUBTRACT;
	extern U32 CS418_KEY_DECIMAL;
	extern U32 CS418_KEY_DIVIDE;

	extern U32 CS418_KEY_F1;
	extern U32 CS418_KEY_F2;
	extern U32 CS418_KEY_F3;
	extern U32 CS418_KEY_F4;
	extern U32 CS418_KEY_F5;
	extern U32 CS418_KEY_F6;
	extern U32 CS418_KEY_F7;
	extern U32 CS418_KEY_F8;
	extern U32 CS418_KEY_F9;
	extern U32 CS418_KEY_F10;
	extern U32 CS418_KEY_F11;
	extern U32 CS418_KEY_F12;
	extern U32 CS418_KEY_F13;
	extern U32 CS418_KEY_F14;
	extern U32 CS418_KEY_F15;
	extern U32 CS418_KEY_F16;
	extern U32 CS418_KEY_F17;
	extern U32 CS418_KEY_F18;
	extern U32 CS418_KEY_F19;
	extern U32 CS418_KEY_F20;
	extern U32 CS418_KEY_F21;
	extern U32 CS418_KEY_F22;
	extern U32 CS418_KEY_F23;
	extern U32 CS418_KEY_F24;

	extern U32 CS418_KEY_NUMLOCK;
	extern U32 CS418_KEY_SCROLLLOCK;

	extern U32 CS418_KEY_LSHIFT;
	extern U32 CS418_KEY_RSHIFT;
	extern U32 CS418_KEY_LCONTROL;
	extern U32 CS418_KEY_RCONTROL;
	extern U32 CS418_KEY_LALT;
	extern U32 CS418_KEY_RALT;

	extern U32 CS418_KEY_PLUS;
	extern U32 CS418_KEY_COMMA;
	extern U32 CS418_KEY_MINUS;
	extern U32 CS418_KEY_PERIOD;
}