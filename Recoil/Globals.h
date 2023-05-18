#pragma once
#include <Windows.h>
#include "C:\Users\famou\OneDrive\Desktop\distortion\Recoil\Imgui\imgui.h"
#include "C:\Users\famou\OneDrive\Desktop\distortion\Recoil\Imgui\imgui_impl_dx9.h"
#include "C:\Users\famou\OneDrive\Desktop\distortion\Recoil\Imgui\imgui_impl_win32.h"
#include "lazy_importer.hpp"
#include "xorstr.hpp"


struct screen_size {
	int w;
	int h;
};

namespace globals {
	extern HWND overlay;
	extern HWND rust;
	extern bool menu_active;
	extern screen_size small_screen;
	extern screen_size full_screen;
	ImFont* font2;
}