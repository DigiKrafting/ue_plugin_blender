// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Import_FBX_Factory.h"
#include "Import_Processer.h"
#include "Misc/Paths.h"
#include "AssetImportTask.h"
#include "Factories/FbxImportUI.h"
#include "HAL/FileManager.h"

#define LOCTEXT_NAMESPACE "FBlender_ImporterModule"

UImport_FBX_Factory::UImport_FBX_Factory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	SupportedClass = NULL;

	Formats.Add(TEXT("fbx;FBX meshes and animations"));

	bCreateNew = false;
	bText = false;
	bEditorImport = true;
	bOperationCanceled = false;
	bDetectImportTypeOnImport = true;
	ImportPriority = 200;

}

bool UImport_FBX_Factory::FactoryCanImport(const FString& Filename)
{

	const FString Extension = FPaths::GetExtension(Filename);
	const FString JSON_Filename = Filename.Replace(TEXT(".fbx"), TEXT(".bjd"));

	if (Extension == TEXT("fbx") && IFileManager::Get().FileExists(*JSON_Filename)){
		return true;
	}

	return false;

}

UObject* UImport_FBX_Factory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{

	UObject* CreatedObject = NULL;
	
	FImport_Processer Import_Processer;
	
	const FString JSON_Filename = Filename.Replace(TEXT(".fbx"), TEXT(".bjd"));
	
	if (Import_Processer.Process_JSON_Open(JSON_Filename)) {

		UAssetImportTask* Task = NewObject<UAssetImportTask>();
		Task->bAutomated = true;
		Task->Options = Import_Processer.Process_Options();;
		SetAssetImportTask(Task);

		CreatedObject = Super::FactoryCreateFile(InClass, InParent, InName, Flags, Filename, Parms, Warn, bOutOperationCanceled);

		const bool _processed_materials = Import_Processer.Process_Materials();

		remove(TCHAR_TO_ANSI(*JSON_Filename));

	}

	return CreatedObject;

}

#undef LOCTEXT_NAMESPACE
