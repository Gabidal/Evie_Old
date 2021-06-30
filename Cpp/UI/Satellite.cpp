#include "../../H/UI/Satellite.h"
#include "../../H/UI/Usr.h"
#include "../../H/UI/Safe.h"
#include "../../H/Docker/Docker.h"
#include <filesystem>

extern Usr* sys;

void Satellite::Init_Wanted_Dependencies()
{
	if (Installation_Type == INSTALL::DEFAULT) {
		Dependecies = {
			{OS::UNIX, INTRODUCE::CONSOLE, nullptr, "git"},
			{OS::UNIX, INTRODUCE::CONSOLE, nullptr, "libcurl4-openssl-dev"},
			{OS::UNIX, INTRODUCE::CONSOLE, &sys->Info.Assembler_Location, "as"},
			{OS::UNIX, INTRODUCE::CONSOLE, &sys->Info.Linker_Location, "ld"},

			{OS::WIN, INTRODUCE::CONSOLE, nullptr, "git"},
			{OS::WIN, INTRODUCE::LOCAL,   nullptr, "libcurl"},
			{OS::WIN, INTRODUCE::LOCAL, &sys->Info.Assembler_Location, "as"},
		};

		if (sys->Info.Architecture == ARCHITECTURE::X86)
			Dependecies.push_back({ OS::WIN, INTRODUCE::CONSOLE, &sys->Info.Linker_Location, "x86_ld" });
		
		if (sys->Info.Architecture == ARCHITECTURE::ARM)
			Dependecies.push_back({ OS::WIN, INTRODUCE::CONSOLE, &sys->Info.Linker_Location, "arm_ld" });
	}
}

void Satellite::Factory()
{
	for (auto Medium : Dependecies) {
		//HOST_OS because in host we need to compile the source
		if (Medium.Platform == sys->Info.HOST_OS) {
			Process_Local_Dependencies(Medium);
		}
	}
}

void Satellite::Process_Local_Dependencies(Medium Medium)
{
	if (Medium.Introducer != INTRODUCE::LOCAL)
		return;

	//start the search for the dependency from Evie eecutable and downwards.
	string Path_To_Medium = DOCKER::Find(Medium.Product_ID);
	if (Path_To_Medium != "") {
		if (Medium.Dependency_Location != nullptr) {
			*Medium.Dependency_Location = Path_To_Medium;
		}
		return;	//the dependecy is there
	}

	Report(Observation(ERROR, "Dependency '" + Medium.Product_ID + "' is missing or unreachable to Evie!"));
}

void Satellite::Process_Console_Dependencies(Medium m)
{
	
}
