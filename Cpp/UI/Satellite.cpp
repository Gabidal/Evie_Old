#include "../../H/UI/Satellite.h"
#include "../../H/UI/Usr.h"

extern Usr* sys;

void Satellite::Init_Wanted_Dependencies()
{
	if (Installation_Type == INSTALL::DEFAULT) {
		Dependecies = {
			{"git", OS::LINUX, INTRODUCE::CONSOLE},

		};
	}
}

void Satellite::Factory()
{
}
