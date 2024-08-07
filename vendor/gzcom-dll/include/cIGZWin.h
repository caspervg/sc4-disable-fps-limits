#pragma once
#include "cIGZUnknown.h"

class cGZMessage;
class cIGZCursor;
class cIGZKeyboard;
class cIGZString;
class cIGZWinKeyAccelerator;
class cIGZWinMgr;
class cRZRect;

static const uint32_t GZIID_cIGZWin = 0x22BA0121;

/**
 * @brief An interface for the game's UI windows
 */
class cIGZWin : public cIGZUnknown
{
	public:
		virtual bool DoMessage(cGZMessage& sMessage) = 0;

		virtual bool Init(void) = 0;
		virtual bool Shutdown(void) = 0;

		virtual cIGZWinMgr* GetWindowManager(void) = 0;
		virtual bool SetWindowManager(cIGZWinMgr* pWinMgr) = 0;

		virtual cIGZKeyboard* GetKeyboard(void) = 0;
		virtual bool SetKeyboard(cIGZKeyboard* pKeyboard) = 0;

		virtual cIGZWin* GetMainWindow(void) = 0;
		virtual cIGZWin* GetParentWin(void) = 0;
		virtual bool SetParentWin(cIGZWin* pWin) = 0;

		virtual int32_t GetChildCount(void) = 0;
		virtual bool ChildAdd(cIGZWin* pWin) = 0;
		virtual bool ChildRemove(cIGZWin* pWin) = 0;
		virtual bool ChildDelete(cIGZWin* pWin) = 0;
		virtual bool ChildDeleteAbsolute(cIGZWin* pWin) = 0;
		virtual bool ChildDeleteAll(void) = 0;
		virtual bool ChildExists(cIGZWin* pWin) = 0;
		virtual bool ChildExists(uint32_t dwWinID) = 0;
		virtual bool IsWinInParentChain(cIGZWin* pWin) = 0;
		virtual bool IsWinInChildChain(cIGZWin* pWin) = 0;

		virtual bool PullToFront(void) = 0;
		virtual bool SendToBack(void) = 0;
		virtual bool ChildToFront(cIGZWin* pWin) = 0;
		virtual bool ChildToFront(uint32_t dwWinID) = 0;
		virtual bool ChildToBack(cIGZWin* pWin) = 0;
		virtual bool ChildStepFront(cIGZWin* pWin) = 0;
		virtual bool ChildStepBack(cIGZWin* pWin) = 0;
		virtual bool MoveRelativeTo(cIGZWin* pWin, bool) = 0;
		virtual bool ChildMoveRelative(cIGZWin*, cIGZWin*, bool) = 0;

		virtual bool EnumChildren(uint32_t, bool(*)(cIGZWin*, uint32_t, void*, void*), void*) = 0;
		virtual bool SortChildren(bool(*)(cIGZWin*, cIGZWin*, void*), void*, bool) = 0;

		virtual cIGZWin* GetChildWindowFromID(uint32_t dwWinID) = 0;
		virtual cIGZWin* GetChildWindowFromIDRecursive(uint32_t dwWinID) = 0;

		virtual bool GetChildAs(uint32_t dwWinID, uint32_t riid, void** ppvObj) = 0;
		virtual bool GetChildAsRecursive(uint32_t dwWinID, uint32_t riid, void** ppvObj) = 0;

		virtual cIGZWin* GetWindowFromPoint(int32_t nX, int32_t nZ) = 0;
		virtual cIGZWin* GetChildWindowFromPoint(int32_t nX, int32_t nZ) = 0;
		virtual cIGZWin* GetChildWindowFromCursorPoint(int32_t nX, int32_t nZ) = 0;

		virtual int32_t GetW() const = 0;
		virtual int32_t GetH() const = 0;

		virtual int32_t GetL() const = 0;
		virtual int32_t GetT() const = 0;
		virtual int32_t GetR() const = 0;
		virtual int32_t GetB() const = 0;

		virtual int32_t* GetArea() const = 0;
		virtual bool GetArea(cRZRect& rect) const = 0;
		virtual int32_t* GetAreaAbsolute() const = 0;
		virtual bool GetAreaAbsolute(cRZRect& rect) const = 0;

		virtual bool SetW(int32_t value) = 0;
		virtual bool SetH(int32_t value) = 0;

		virtual bool SetSize(int32_t unknown1, int32_t unknown2) = 0;

		virtual bool SetArea(int32_t left, int32_t top, int32_t right, int32_t bottom) = 0;
		virtual bool SetArea(const cRZRect& rect) = 0;

		virtual bool GZWinMoveTo(int32_t x, int32_t y) = 0;
		virtual bool GZWinOffset(int32_t unknown1, int32_t unknown2) = 0;

		virtual bool FitRectToWindow(cRZRect& unknown1, int32_t unknown2) = 0;
		virtual bool ScreenToWindowCoordinates(int32_t& unknown1, int32_t& unknown2) const = 0;
		virtual bool WindowToScreenCoordinates(int32_t& unknown1, int32_t& unknown2) const = 0;
		virtual bool WindowToWindowCoordinates(cIGZWin* unknown1, int32_t& unknown2, int32_t& unknown3) const = 0;
		virtual bool IsPointInWindowScreenCoordinates(int32_t unknown1, int32_t unknown2) const = 0;

		virtual uint32_t GetID() const = 0;
		virtual bool SetID(uint32_t id) = 0;

		virtual uint32_t GetInstanceID() const = 0;
		virtual bool SetInstanceID(uint32_t id) = 0;

		virtual bool GetFlag(uint32_t flag) const = 0;
		virtual bool SetFlag(uint32_t flag, bool value) = 0;

		virtual bool ShowWindow() = 0;
		virtual bool HideWindow() = 0;

		virtual bool IsVisible() const = 0;
		virtual bool IsEnabled() const = 0;

		virtual cIGZString* GetCaption() const = 0;
		virtual bool SetCaption(cIGZString const& caption) = 0;

		virtual cIGZWinKeyAccelerator* GetKeyboardAccelerator() = 0;
		virtual bool SetKeyboardAccelerator(cIGZWinKeyAccelerator* pWinKeyAccelerator) = 0;

		virtual bool AccelerateKeyboardMsg() = 0;

		virtual uint32_t GetKeyEquivalent() = 0;
		virtual bool SetKeyEquivalent(uint32_t value) = 0;
		virtual bool CheckKeyEquivalent(uint32_t value) = 0;
		virtual uint32_t MakeKeyEquivalent(uint32_t unknown1, uint32_t unknown2) = 0;
		virtual bool IsChildKeyEquivalent(uint32_t unknown1, uint32_t unknown2) = 0;

		virtual bool ProcessCursorMessage(cGZMessage& msg) = 0;
		virtual bool UpdateCursor() = 0;
		virtual bool SetCursor(cIGZCursor* unknown1, bool unknown2) = 0;

		virtual bool SetNotificationTarget(cIGZWin* pTarget) = 0;
		virtual cIGZWin* GetNotificationTarget() = 0;

		// <TODO>
};