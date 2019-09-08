// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Factories/FbxFactory.h"
#include "Import_FBX_Factory.generated.h"

UCLASS(hidecategories = Object)
class UImport_FBX_Factory : public UFbxFactory
{
	GENERATED_UCLASS_BODY()

public:

	// UFactory interface
	virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
	virtual bool FactoryCanImport(const FString& Filename) override;
	// End of UFactory interface	

};
