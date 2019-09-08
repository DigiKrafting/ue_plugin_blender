// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

class FImport_Processer
{

public:

	bool Process_JSON_Open(const FString& Filename);
	UFbxImportUI* Process_Options();
	bool Process_Materials();
	
private:

	TSharedPtr<FJsonObject> JsonObject;

};
