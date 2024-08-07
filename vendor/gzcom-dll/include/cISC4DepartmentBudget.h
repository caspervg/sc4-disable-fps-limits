#pragma once
#include "cIGZUnknown.h"
#include "EASTLConfigSC4.h"
#include "EASTL/list.h"
#include "EASTL/vector.h"

class cIGZString;
class cISC4LineItem;
class cISCPropertyHolder;
class SC4Percentage;

template <typename T> class cRZAutoRefCount;

class cISC4DepartmentBudget : public cIGZUnknown
{
public:

	virtual uint32_t GetDepartmentID() const = 0;
	virtual bool GetDepartmentName(cIGZString& name) = 0;
	virtual bool SetDepartmentName(uint32_t ltextGroupID, uint32_t ltextInstanceID) = 0;

	virtual uint32_t GetBudgetGroup() const = 0;
	virtual bool SetBudgetGroup(uint32_t budgetGroup) = 0;

	virtual bool GetIsFixedFunding() const = 0;
	virtual bool SetFixedFunding(bool value) = 0;

	virtual float* GetFundingPercentage() const = 0;
	virtual bool SetFundingPercentage(SC4Percentage const& percentange, uint32_t lineItem) = 0;
	virtual float* GetMaxAllowedFundingPercentage() const = 0;
	virtual bool SetMaxAllowedFundingPercentage(SC4Percentage const& percentange) = 0;
	virtual int64_t GetIdealMonthlyFunding() const = 0;

	virtual int64_t GetTotalExpenses() const = 0;
	virtual int64_t GetTotalIncome() const = 0;

	virtual cISC4LineItem* CreateLineItem(uint32_t lineNumber, bool isLocallyFunded) = 0;
	virtual cISC4LineItem* CreateLineItemForBuildingType(uint32_t lineNumber, bool isLocallyFunded) = 0;
	virtual bool RemoveLineItem(uint32_t lineNumber) = 0;
	virtual cISC4LineItem* GetLineItem(uint32_t lineNumber) = 0;
	virtual bool GetAllLineItems(eastl::vector<cISC4LineItem*>& destination) = 0;

	virtual bool AddLocallyFundedObject(cISCPropertyHolder* unknown1, uint32_t unknown2) = 0;
	virtual bool RemoveLocallyFundedObject(cISCPropertyHolder* unknown1, uint32_t unknown2) = 0;
	virtual bool SetLocalFundingPercent(cISCPropertyHolder* unknown1, SC4Percentage* unknown2, uint32_t unknown3) = 0;
	virtual bool SetLocalFullFunding(cISCPropertyHolder* unknown1, int64_t unknown2, uint32_t unknown3) = 0;
	virtual float GetLocalFundingPercent(cISCPropertyHolder* unknown1, uint32_t unknown2) = 0;
	virtual int64_t GetLocalFullFunding(cISCPropertyHolder * unknown1, uint32_t unknown2) = 0;
	virtual bool IsLocallyFundedObjectInDepartment(cISCPropertyHolder* unknown1, uint32_t unknown2) = 0;

	virtual bool RecalculateAllLineItemCurrentExpenses() = 0;

	virtual int64_t GetTotalSpending() const = 0;
	virtual bool SetTotalSpending(int64_t value) = 0;

	virtual bool GetLocallyFundedItemsByPurpose(uint32_t unknown1, eastl::list<cRZAutoRefCount<cISCPropertyHolder>>& unknown2) = 0;
	virtual bool HasLocallyFundedItemsByPurpose(uint32_t unknown1) = 0;
};
