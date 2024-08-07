#pragma once
#include "cIGZWinProc.h"

class cRZBaseWinProc : public cIGZWinProc
{
protected:

	cRZBaseWinProc();

public:

	bool QueryInterface(uint32_t riid, void** ppvObj);

	uint32_t AddRef();

	uint32_t Release();

	bool DoWinProcMessage(cIGZWin* pWin, cGZMessage& pMsg);

	bool DoWinMsg(cIGZWin* pWin, uint32_t dwMessageID, uint32_t data1, uint32_t data2, uint32_t data3) override;

private:

	uint32_t refCount;
};