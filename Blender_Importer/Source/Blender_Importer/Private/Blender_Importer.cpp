// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Blender_Importer.h"

static const FName Blender_ImporterTabName("Blender_Importer");

#define LOCTEXT_NAMESPACE "FBlender_ImporterModule"

bool FBlender_ImporterModule::SupportsDynamicReloading()
{
	return true;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBlender_ImporterModule, Blender_Importer)