// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Import_Factory.h"
#include "AssetRegistryModule.h"
#include "Editor/UnrealEd/Public/Editor.h"
#include "Misc/FeedbackContext.h"
#include "Logging/LogMacros.h"
#include "Logging/TokenizedMessage.h"
#include "MessageLogModule.h"
#include "Serialization/JsonTypes.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "ContentBrowserModule.h"
#include "Factories/MaterialFactoryNew.h"
#include "Materials/MaterialExpressionTextureSample.h"
#include "Materials/Material.h"
#include "Materials/MaterialExpressionConstant.h"

#define LOCTEXT_NAMESPACE "FBlender_ImporterModule"

UImport_Factory::UImport_Factory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	bCreateNew = true;
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
	
		FString JsonString; 
		FFileHelper::LoadFileToString(JsonString, *Filename);
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

		if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
		{
			const FString data_path = JsonObject->GetStringField(TEXT("path"));

			TArray<TSharedPtr<FJsonValue>> objArray = JsonObject->GetArrayField(TEXT("materials"));
			for (int32 i = 0; i < objArray.Num(); i++)
			{
				TSharedPtr<FJsonValue> value = objArray[i];
				TSharedPtr<FJsonObject> json = value->AsObject();
			
				const FString data_name = json->GetStringField(TEXT("name"));
				const FString data_base_color = json->GetStringField(TEXT("base_color"));
				const FString data_orm = json->GetStringField(TEXT("orm"));
				const FString data_normal = json->GetStringField(TEXT("normal"));

				FString PackageName = TEXT("/Game/") + data_path + data_name;

				UPackage* Package = CreatePackage(NULL, *PackageName);

				auto MaterialFactory = NewObject<UMaterialFactoryNew>();
				UMaterial* UnrealMaterial = (UMaterial*)MaterialFactory->FactoryCreateNew(UMaterial::StaticClass(), Package, *data_name, RF_Standalone | RF_Public, NULL, GWarn);
				FAssetRegistryModule::AssetCreated(UnrealMaterial);
				Package->FullyLoad();
				Package->SetDirtyFlag(true);
			
				// Base Color

				if (data_base_color != "") {
			
					FStringAssetReference AssetPath_Basecolor(TEXT("/Game/") + data_path + data_base_color);
					UTexture* Texture_Basecolor = Cast<UTexture>(AssetPath_Basecolor.TryLoad());
					if (Texture_Basecolor)
					{
						UMaterialExpressionTextureSample* TextureExpression = NewObject<UMaterialExpressionTextureSample>(UnrealMaterial);
						TextureExpression->Texture = Texture_Basecolor;
						TextureExpression->SamplerType = SAMPLERTYPE_Color;
						UnrealMaterial->Expressions.Add(TextureExpression);
						UnrealMaterial->BaseColor.Expression = TextureExpression;
					}
			
				}
			
				// ORM

				if (data_orm != "") {
			
					FStringAssetReference AssetPath_ORM(TEXT("/Game/") + data_path + data_orm);
					UTexture* Texture_ORM = Cast<UTexture>(AssetPath_ORM.TryLoad());
					if (Texture_ORM)
					{
						UMaterialExpressionTextureSample* TextureExpression = NewObject<UMaterialExpressionTextureSample>(UnrealMaterial);
						TextureExpression->Texture = Texture_ORM;
						TextureExpression->SamplerType = SAMPLERTYPE_Color;
						UnrealMaterial->Expressions.Add(TextureExpression);

						UnrealMaterial->AmbientOcclusion.Connect(1, TextureExpression);
						UnrealMaterial->Roughness.Connect(2, TextureExpression);
						UnrealMaterial->Metallic.Connect(3, TextureExpression);

					}
			
				}

				// Normal

				if (data_normal != "") {
				
					FStringAssetReference AssetPath_Normal(TEXT("/Game/") + data_path + data_normal);
					UTexture* Texture_Normal = Cast<UTexture>(AssetPath_Normal.TryLoad());
					if (Texture_Normal)
					{
						UMaterialExpressionTextureSample* TextureExpression = NewObject<UMaterialExpressionTextureSample>(UnrealMaterial);
						TextureExpression->Texture = Texture_Normal;
						TextureExpression->SamplerType = SAMPLERTYPE_Normal;
						UnrealMaterial->Expressions.Add(TextureExpression);
						UnrealMaterial->Normal.Expression = TextureExpression;
					}

				}

			}

		} else {

			FText DialogText = FText::Format(
				LOCTEXT("Error deserializing/processing ", "[{0}]"),
				FText::FromString(Filename)
			);
			FMessageDialog::Open(EAppMsgType::Ok, DialogText);

		}
		
		return true;

	} else {

		return false;

	}

}

UObject* UImport_Factory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	return nullptr;
}

#undef LOCTEXT_NAMESPACE
