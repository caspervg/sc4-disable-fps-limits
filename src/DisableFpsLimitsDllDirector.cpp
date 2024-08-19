///////////////////////////////////////////////////////////////////////////////
//
// This file is part of sc4-disable-fps-limits, a DLL Plugin
// for SimCity 4 that disables the default FPS limitation while the simulation
// is running in Turtle (slow simulation, 30 FPS), Rhino (medium
// simulation, 20 FPS) and Cheetah (fast simulation , 15 FPS) speed.
// 
// Copyright (c) 2024 Casper Van Gheluwe
// Heavily inspired by sc4-disable-network-construction-sounds by Nicolas Hayes
//
// This file is licensed under terms of the MIT License.
// See LICENSE.txt for more information.
//
///////////////////////////////////////////////////////////////////////////////

#include "version.h"
#include "Logger.h"
#include "SC4VersionDetection.h"

#include "cIGZCOM.h"
#include "cIGZFrameWork.h"
#include "cRZCOMDllDirector.h"

#include <filesystem>

#include <Windows.h>
#include "wil/resource.h"
#include "wil/win32_helpers.h"

static constexpr uint32_t kDisableFpsLimitsDirectorID = 0xCA500002;

static constexpr std::string_view PluginLogFileName = "SC4DisableFpsLimit.log";

namespace
{
	std::filesystem::path GetDllFolderPath()
	{
		wil::unique_cotaskmem_string modulePath = wil::GetModuleFileNameW(wil::GetModuleInstanceHandle());

		std::filesystem::path temp(modulePath.get());

		return temp.parent_path();
	}

	void OverwriteMemory(uintptr_t address, uint8_t newValue)
	{
		DWORD oldProtect;
		// Allow the executable memory to be written to.
		THROW_IF_WIN32_BOOL_FALSE(VirtualProtect(
			reinterpret_cast<LPVOID>(address),
			sizeof(newValue),
			PAGE_EXECUTE_READWRITE,
			&oldProtect));

		// Patch the memory at the specified address.
		*((uint8_t*)address) = newValue;
	}

	void DisableFpsLimits()
	{
		Logger& logger = Logger::GetInstance();

		const uint16_t gameVersion = SC4VersionDetection::GetInstance().GetGameVersion();

		if (gameVersion == 641)
		{
			try
			{
				// Original instruction:	0xC786840000000f000 (MOV dword ptr [ESI  + 0x84], 0xf)
				// New instruction:			0xC78684000000ff000 (MOV dword ptr [ESI  + 0x84], 0xff)

				logger.WriteLine(LogLevel::Info, "Attempting to overwrite memory");

				OverwriteMemory(0x70244a, 0xFF);
				OverwriteMemory(0x702457, 0xFF);
				OverwriteMemory(0x702462, 0xFF);

				logger.WriteLine(LogLevel::Info, "Disabled the FPS limits during simulation.");
			}
			catch (const std::exception& e)
			{
				logger.WriteLineFormatted(
					LogLevel::Error,
					"Failed to disable the FPS limits: %s",
					e.what());
			}
		}
		else
		{
			logger.WriteLineFormatted(
				LogLevel::Error,
				"Unable to disable the FPS limits. Requires "
				"game version 641, found game version %d.",
				gameVersion);
		}
	}
}

class DisableFpsLimitsDllDirector final : public cRZCOMDllDirector
{
public:

	DisableFpsLimitsDllDirector()
	{
		std::filesystem::path dllFolderPath = GetDllFolderPath();

		std::filesystem::path logFilePath = dllFolderPath;
		logFilePath /= PluginLogFileName;

		Logger& logger = Logger::GetInstance();
		logger.Init(logFilePath, LogLevel::Error, false);
		logger.WriteLogFileHeader("SC4DisableFpsLimits v" PLUGIN_VERSION_STR);
	}

	uint32_t GetDirectorID() const
	{
		return kDisableFpsLimitsDirectorID;
	}

	bool OnStart(cIGZCOM* pCOM)
	{
		DisableFpsLimits();

		return true;
	}
};

cRZCOMDllDirector* RZGetCOMDllDirector() {
	static DisableFpsLimitsDllDirector sDirector;
	return &sDirector;
}