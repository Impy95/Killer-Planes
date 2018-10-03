#include "DataTables.h"


namespace GEX
{
	std::map<AircraftType, AircraftData> initalizeAircraftData()
	{
		std::map<GEX::AircraftType, AircraftData> data;

		data[AircraftType::Eagle].hitpoints = 100;
		data[AircraftType::Eagle].speed = 200.f;
		data[AircraftType::Eagle].texture = TextureID::Eagle;

		data[AircraftType::Raptor].hitpoints = 20;
		data[AircraftType::Raptor].speed = 80.f;
		data[AircraftType::Raptor].texture = TextureID::Raptor;

		data[AircraftType::Avenger].hitpoints = 40;
		data[AircraftType::Avenger].speed = 50.f;
		data[AircraftType::Avenger].texture = TextureID::Avenger;

		return data;
	}
}