// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Factories/FbxStaticMeshImportData.h"
#include "Factories/FbxSkeletalMeshImportData.h"
#include "Factories/FbxAnimSequenceImportData.h"
#include "Factories/FbxImportUI.h"

class FImport_BJD_Processer
{

public:

	bool Process_JSON_Open(const FString& Filename);
	UFbxImportUI* Process_Options();
	bool Process_Materials();
	bool Process_Auto();

private:

	TSharedPtr<FJsonObject> JsonObject;

};
