#include "cRZBaseWinProc.h"

cRZBaseWinProc::cRZBaseWinProc() : refCount(0)
{
}

bool cRZBaseWinProc::QueryInterface(uint32_t riid, void** ppvObj)
{
    if (riid == GZIID_cIGZWinProc)
    {
        *ppvObj = static_cast<cIGZWinProc*>(this);
        AddRef();

        return true;
    }
    else if (riid == GZIID_cIGZUnknown)
    {
        *ppvObj = static_cast<cIGZUnknown*>(this);
        AddRef();

        return true;
    }

    return false;
}

uint32_t cRZBaseWinProc::AddRef()
{
    return ++refCount;
}

uint32_t cRZBaseWinProc::Release()
{
    if (refCount > 0)
    {
        --refCount;
    }

    return refCount;
}

bool cRZBaseWinProc::DoWinProcMessage(cIGZWin* pWin, cGZMessage& pMsg)
{
    return false;
}

bool cRZBaseWinProc::DoWinMsg(cIGZWin* pWin, uint32_t dwMessageID, uint32_t data1, uint32_t data2, uint32_t data3)
{
    return false;
}
