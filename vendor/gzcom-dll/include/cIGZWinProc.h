#pragma once
#include "cIGZUnknown.h"

class cGZMessage;
class cIGZWin;

static const uint32_t GZIID_cIGZWinProc = 0x22E85D8E;

class cIGZWinProc : public cIGZUnknown
{
public:

	// Returns true if a message was handled; otherwise, false.
	virtual bool DoWinProcMessage(cIGZWin* pWin, cGZMessage& pMsg) = 0;

	// Returns true if a message was handled; otherwise, false.
	virtual bool DoWinMsg(cIGZWin* pWin, uint32_t dwMessageID, uint32_t data1, uint32_t data2, uint32_t data3) = 0;
};