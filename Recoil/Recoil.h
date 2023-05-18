#include <array>
#include <vector>
#include <string>

namespace r012401
{
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
		SCOPE_NONE,
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

	struct weapon_info
	{
		float delay;
		float crouch_delay;
		std::string name;
		std::vector<std::array<double, 2>> rta;
		std::vector<double> control_time;
	};

	extern std::array<weapon_info, WEAPON_MAX> weapons;
	extern void doo2135();
}