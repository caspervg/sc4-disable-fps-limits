///////////////////////////////////////////////////////////////////////////////
//
// This file is part of sc4-disable-network-construction-sounds, a DLL Plugin
// for SimCity 4 that disables the sounds that are played during the network
// construction animation.
//
// Copyright (c) 2024 Nicholas Hayes
//
// This file is licensed under terms of the MIT License.
// See LICENSE.txt for more information.
//
///////////////////////////////////////////////////////////////////////////////

// Portions of this file have been adapted from:
/*
   Project: SC4Fix Patches for SimCity 4
   File: version.cpp

   Copyright (c) 2015 Nelson Gomez (simmaster07)

   Licensed under the MIT License. A copy of the License is available in
   LICENSE or at:

	   http://opensource.org/licenses/MIT

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#include "SC4VersionDetection.h"
#include <Windows.h>
#include "wil/resource.h"
#include "wil/win32_helpers.h"

namespace
{
	uint64_t GetAssemblyVersion(HMODULE hModule)
	{
		wil::unique_cotaskmem_string szVersionFile = wil::GetModuleFileNameW(hModule);

		// http://stackoverflow.com/a/940743
		DWORD verHandle = 0;
		UINT  size = 0;
		DWORD verSize = GetFileVersionInfoSizeW(szVersionFile.get(), &verHandle);

		if (verSize > 0)
		{
			auto verData = wil::make_unique_cotaskmem<BYTE[]>(verSize);
			LPBYTE lpBuffer = nullptr;

			if (GetFileVersionInfoW(szVersionFile.get(), 0, verSize, verData.get())
				&& VerQueryValueW(verData.get(), L"\\", reinterpret_cast<LPVOID*>(&lpBuffer), &size)
				&& size > 0)
			{
				VS_FIXEDFILEINFO* verInfo = (VS_FIXEDFILEINFO*)lpBuffer;
				if (verInfo->dwSignature == 0xfeef04bd)
				{
					uint64_t qwValue = (uint64_t)verInfo->dwFileVersionMS << 32;
					qwValue |= verInfo->dwFileVersionLS;

					return qwValue;
				}
			}
		}

		return 0;
	}

	uint16_t DetermineGameVersion()
	{
		uint64_t qwFileVersion = GetAssemblyVersion(nullptr);
		uint16_t wMajorVer = (qwFileVersion >> 48) & 0xFFFF;
		uint16_t wMinorVer = (qwFileVersion >> 32) & 0xFFFF;
		uint16_t wRevision = (qwFileVersion >> 16) & 0xFFFF;
		uint16_t wBuildNum = qwFileVersion & 0xFFFF;

		uint16_t nGameVersion = 0;

		// 1.1.x.x
		if (qwFileVersion > 0 && wMajorVer == 1 && wMinorVer == 1)
		{
			nGameVersion = wRevision;
		}
		else
		{
			nGameVersion = 0;
		}

		// Fall back to a less accurate detection mechanism
		if (nGameVersion == 0)
		{
			uint8_t uSentinel = *(uint8_t*)0x6E5000;

			switch (uSentinel)
			{
			case 0x8B:
				nGameVersion = 610; // Can't distinguish from 613
				break;
			case 0xFF:
				nGameVersion = 638;
				break;
			case 0x24:
				nGameVersion = 640;
				break;
			case 0x0F:
				nGameVersion = 641;
				break;
			default:
				nGameVersion = 0;
				break;
			}
		}

		return nGameVersion;
	}
}

SC4VersionDetection& SC4VersionDetection::GetInstance()
{
	static SC4VersionDetection instance;

	return instance;
}

uint16_t SC4VersionDetection::GetGameVersion() const noexcept
{
	return gameVersion;
}

SC4VersionDetection::SC4VersionDetection() : gameVersion(DetermineGameVersion())
{
}
