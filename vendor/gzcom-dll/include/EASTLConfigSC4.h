#pragma once

// This file configures EASTL to work with SC4
// It must be included before any EASTL headers

// The following define allows us to replace the default
// EASTL allocator with one that uses SC4's memory pool.
// See EASTLAllocatorSC4.cpp

#define EASTL_USER_DEFINED_ALLOCATOR

#include "EASTL/internal/config.h"