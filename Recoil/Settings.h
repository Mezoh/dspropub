#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include <Windows.h>
#include <thread>
typedef int virtual_key;

enum Weapons
{
	WEAPON_NONE = 0,
	WEAPON_AK,
	WEAPON_LR,
	WEAPON_M249,
	WEAPON_HMLMG,
	WEAPON_MP5A4,
	WEAPON_THOMPSON,
	WEAPON_CUSTOM,
	WEAPON_PYTHON,
	WEAPON_SEMI,
	WEAPON_M92,
	WEAPON_MAX
};

enum Scopes
{
	SCOPE_NONE = 0,
	SCOPE_HANDMADE,
	SCOPE_HOLOSIGHT,
	SCOPE_8X,
	SCOPE_16X,
	SCOPE_MAX
};

enum Barrel
{
	BARREL_NONE = 0,
	BARREL_MUZZLE_BOOST,
	BARREL_MUZZLE_BRAKE,
	BARREL_MAX
};

struct settings {
	//Menu
	bool enabled = false;
	bool disabled = false;
	bool autofire = false;
	bool crosshair = false;
	bool afk = false;
	bool hipfire = false;
	bool weapon_detect = false;
	bool furnace = false;
	bool smoothing = false;
	bool humanization = false;
	bool beep = false;
	bool sync = true;
	bool autodetect = false;
	

	//Recoil settings
	int weapon = WEAPON_NONE;
	int scope  = SCOPE_NONE;
	int barrel = BARREL_NONE;

	float sensitivity = 0.0f;
	float ads_sens = 0.0f;
	float fov = 0.0f;
	float x = 0;
	float y = 0;
	float humanize = 0;
	float stand = 0;
	float smoothness = 100;
	float holo = 0;
	float pitch = 0;
	float movementmultiplier = 1.0;
	float max = 2.0;
	float min = 0.0;

	virtual_key attack_key = 0x1;
	virtual_key scope_key = 0x2;
	virtual_key crouch_key = 0x11;

	//Keybind settings
	virtual_key enable_hotkey = 0x00; //None
	virtual_key reset = 0x00; //None
	virtual_key unload = 0x00; //None
	virtual_key menukey = 0x00; //None
	virtual_key hipfire_bind = 0x00; //None
	virtual_key weapon_cycler = 0x00; //None
	virtual_key scope_cycler  = 0x00; //None
	virtual_key barrel_cycler = 0x00; //None
	virtual_key ak_holo = 0x00; //None
	virtual_key mp5_holo = 0x00; //None
	virtual_key m2_sil = 0x00; //None
};
extern settings g_settings;