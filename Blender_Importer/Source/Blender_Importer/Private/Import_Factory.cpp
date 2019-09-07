// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Import_Factory.h"
#include "Import_Processer.h"

#define LOCTEXT_NAMESPACE "FBlender_ImporterModule"

UImport_Factory::UImport_Factory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	bCreateNew = false;
	bEditorImport = true;
	bEditAfterNew = false;
	bText = true;

	SupportedClass = UObject::StaticClass();

	Formats.Add(TEXT("json;Blender Data"));

}

bool UImport_Factory::FactoryCanImport(const FString& Filename)
{

	const FString JSON_Filename = FPaths::GetCleanFilename(Filename);

	if (JSON_Filename == TEXT("blender_addon_ue_data.json"))
	{
		
		return true;

	}

	return false;

}

UObject* UImport_Factory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{

	UObject* ImportedObject = nullptr;

	bool processed = FImport_Processer::Process_JSON_Data(Filename);

	remove(TCHAR_TO_ANSI(*Filename));

	return nullptr;

}

#undef LOCTEXT_NAMESPACE
