#pragma once
#include "TextureManager.h"
#include "Aircraft.h"
#include <map>

namespace GEX
{
	struct AircraftData
	{
		int			hitpoints;
		float		speed;
		TextureID	texture;
	};

	std::map<AircraftType, AircraftData> initalizeAircraftData(); 
}

