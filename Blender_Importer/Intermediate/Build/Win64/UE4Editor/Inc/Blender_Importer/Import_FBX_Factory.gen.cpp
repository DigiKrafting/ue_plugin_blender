// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Blender_Importer/Public/Import_FBX_Factory.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeImport_FBX_Factory() {}
// Cross Module References
	BLENDER_IMPORTER_API UClass* Z_Construct_UClass_UImport_FBX_Factory_NoRegister();
	BLENDER_IMPORTER_API UClass* Z_Construct_UClass_UImport_FBX_Factory();
	UNREALED_API UClass* Z_Construct_UClass_UFbxFactory();
	UPackage* Z_Construct_UPackage__Script_Blender_Importer();
// End Cross Module References
	void UImport_FBX_Factory::StaticRegisterNativesUImport_FBX_Factory()
	{
	}
	UClass* Z_Construct_UClass_UImport_FBX_Factory_NoRegister()
	{
		return UImport_FBX_Factory::StaticClass();
	}
	struct Z_Construct_UClass_UImport_FBX_Factory_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UImport_FBX_Factory_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UFbxFactory,
		(UObject* (*)())Z_Construct_UPackage__Script_Blender_Importer,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UImport_FBX_Factory_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Object Object" },
		{ "IncludePath", "Import_FBX_Factory.h" },
		{ "ModuleRelativePath", "Public/Import_FBX_Factory.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UImport_FBX_Factory_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UImport_FBX_Factory>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UImport_FBX_Factory_Statics::ClassParams = {
		&UImport_FBX_Factory::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UImport_FBX_Factory_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UImport_FBX_Factory_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UImport_FBX_Factory()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UImport_FBX_Factory_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UImport_FBX_Factory, 2610361341);
	template<> BLENDER_IMPORTER_API UClass* StaticClass<UImport_FBX_Factory>()
	{
		return UImport_FBX_Factory::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UImport_FBX_Factory(Z_Construct_UClass_UImport_FBX_Factory, &UImport_FBX_Factory::StaticClass, TEXT("/Script/Blender_Importer"), TEXT("UImport_FBX_Factory"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UImport_FBX_Factory);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
