// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UnrealEd.h"
#include "Factories.h"
#include "Import_Factory.generated.h"

UCLASS(transient)
class UImport_Factory : public UFactory
{
	GENERATED_UCLASS_BODY()

public:

	// UFactory interface
	virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
	virtual bool FactoryCanImport(const FString& Filename) override;
	// End of UFactory interface

private:
	FString Processing_Filename;
};
