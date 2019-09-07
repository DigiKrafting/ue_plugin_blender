// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FBlender_ImporterModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */

	virtual bool SupportsDynamicReloading() override;

};
