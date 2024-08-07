#pragma once
#include "cIGZUnknown.h"
#include <string>

class cIGZString;

class cISC4LineItem : public cIGZUnknown
{
public:

	virtual uint32_t GetID() const = 0;

	virtual uint32_t GetType() const = 0;
	virtual bool SetType(uint32_t value) = 0;

	// The name parameter uses the game's internal RZString type.
	// It stores the name string using the CRT std::string type and
	// tries to assign it to the RZString object, which crashes due
	// to the different object layouts.
	virtual bool GetName(intptr_t& name) = 0;
	/**
	 * @brief Sets the name of the line item.
	 * @param groupID The group ID of the LTEXT entry, can be 0
	 * to get the name of the building represented by instanceID.
	 * @param instanceID The instance ID.
	 * @return True on success; otherwise, false.
	*/
	virtual bool SetName(uint32_t groupID, uint32_t instanceID) = 0;

	virtual int64_t GetSecondaryInfoField() const = 0;
	virtual bool SetSecondaryInfoField(int64_t value) = 0;

	virtual int64_t GetFullExpenses() const = 0;
	virtual int64_t GetCurrentExpenses() const = 0;

	virtual bool SetFullExpenses(int64_t value) = 0;
	virtual bool AddToFullExpenses(int64_t value) = 0;

	virtual int64_t GetIncome() const = 0;
	virtual bool SetIncome(int64_t value) = 0;
	virtual bool AddToIncome(int64_t value) = 0;

	virtual uint32_t GetDisplayFlags() = 0;
	virtual bool SetDisplayFlag(uint32_t mask, bool value) = 0;

	virtual bool IsLocalFundingItem() const = 0;
};