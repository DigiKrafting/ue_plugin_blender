// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Import_Processer.h"
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
#include "Factories/FbxImportUI.h"
#include "Factories/FbxStaticMeshImportData.h"
#include "Factories/FbxSkeletalMeshImportData.h"
#include "Factories/FbxAnimSequenceImportData.h"

#define LOCTEXT_NAMESPACE "FBlender_ImporterModule"

bool FImport_Processer::Process_JSON_Open(const FString& Filename)
{

	FString JsonString;
	FFileHelper::LoadFileToString(JsonString, *Filename);
	JsonObject = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid()){
		
		return true;

	} else {

		FText DialogText = FText::Format(
			LOCTEXT("Error deserializing/processing ", "[{0}]"),
			FText::FromString(Filename)
		);
		FMessageDialog::Open(EAppMsgType::Ok, DialogText);

		return false;

	}

}

UFbxImportUI* FImport_Processer::Process_Options() {

	UFbxImportUI* FBX_Options = NewObject<UFbxImportUI>();

	TSharedPtr<FJsonObject> json = JsonObject->GetObjectField(TEXT("options"));

	FBX_Options->bImportTextures = false; 

	FBX_Options->bImportMesh = json->GetBoolField(TEXT("ImportMesh"));
	FBX_Options->bImportMaterials = json->GetBoolField(TEXT("ImportMaterials"));
	FBX_Options->bImportAnimations = json->GetBoolField(TEXT("ImportAnimations"));
	FBX_Options->bCreatePhysicsAsset = json->GetBoolField(TEXT("CreatePhysicsAsset"));
	FBX_Options->bAutoComputeLodDistances = json->GetBoolField(TEXT("AutoComputeLodDistances"));

	// Static Mesh

	TSharedPtr<FJsonObject> json_static_mesh = json->GetObjectField(TEXT("static_mesh"));

	FBX_Options->StaticMeshImportData->bImportMeshLODs = json_static_mesh->GetBoolField(TEXT("ImportMeshLODs"));
	FBX_Options->StaticMeshImportData->bCombineMeshes = json_static_mesh->GetBoolField(TEXT("CombineMeshes"));
	FBX_Options->StaticMeshImportData->bAutoGenerateCollision = json_static_mesh->GetBoolField(TEXT("AutoGenerateCollision"));

	const FString options_static_mesh_normal_import_method = json_static_mesh->GetStringField(TEXT("NormalImportMethod"));
	if (options_static_mesh_normal_import_method == "ImportNormalsAndTangents") {
		FBX_Options->StaticMeshImportData->NormalImportMethod = EFBXNormalImportMethod::FBXNIM_ImportNormalsAndTangents;
	} else if (options_static_mesh_normal_import_method == "ComputeNormals") {
		FBX_Options->StaticMeshImportData->NormalImportMethod = EFBXNormalImportMethod::FBXNIM_ComputeNormals;
	} else if (options_static_mesh_normal_import_method == "ImportNormals") {
		FBX_Options->StaticMeshImportData->NormalImportMethod = EFBXNormalImportMethod::FBXNIM_ImportNormals;
	}
	
	// Skeletal Mesh

	TSharedPtr<FJsonObject> json_skeletal_mesh = json->GetObjectField(TEXT("skeletal_mesh"));

	FBX_Options->SkeletalMeshImportData->bImportMeshLODs = json_skeletal_mesh->GetBoolField(TEXT("ImportMeshLODs"));
	FBX_Options->SkeletalMeshImportData->bUseT0AsRefPose = json_skeletal_mesh->GetBoolField(TEXT("UseT0AsRefPose"));
	FBX_Options->SkeletalMeshImportData->bPreserveSmoothingGroups = json_skeletal_mesh->GetBoolField(TEXT("PreserveSmoothingGroups"));
	FBX_Options->SkeletalMeshImportData->bImportMorphTargets = json_skeletal_mesh->GetBoolField(TEXT("ImportMorphTargets"));

	const FString options_skeletal_mesh_normal_import_method = json_skeletal_mesh->GetStringField(TEXT("NormalImportMethod"));
	if (options_skeletal_mesh_normal_import_method == "ImportNormalsAndTangents") {
		FBX_Options->SkeletalMeshImportData->NormalImportMethod = EFBXNormalImportMethod::FBXNIM_ImportNormalsAndTangents;
	} else if (options_skeletal_mesh_normal_import_method == "ComputeNormals") {
		FBX_Options->SkeletalMeshImportData->NormalImportMethod = EFBXNormalImportMethod::FBXNIM_ComputeNormals;
	} else if (options_skeletal_mesh_normal_import_method == "ImportNormals") {
		FBX_Options->SkeletalMeshImportData->NormalImportMethod = EFBXNormalImportMethod::FBXNIM_ImportNormals;
	}

	// Animation
	
	TSharedPtr<FJsonObject> json_animation = json->GetObjectField(TEXT("animation"));
	
	FBX_Options->AnimSequenceImportData->bImportMeshesInBoneHierarchy = json_animation->GetBoolField(TEXT("ImportMeshesInBoneHierarchy"));
	FBX_Options->AnimSequenceImportData->bUseDefaultSampleRate = json_animation->GetBoolField(TEXT("UseDefaultSampleRate"));
	FBX_Options->AnimSequenceImportData->CustomSampleRate = json_animation->GetNumberField(TEXT("CustomSampleRate"));
	FBX_Options->AnimSequenceImportData->bConvertScene = json_animation->GetBoolField(TEXT("ConvertScene"));

	const FString options_animation_time = json_animation->GetStringField(TEXT("animation_time"));
	if (options_animation_time == "AnimatedKey") {
		FBX_Options->AnimSequenceImportData->AnimationLength = EFBXAnimationLengthImportType::FBXALIT_AnimatedKey;
	} else if (options_animation_time == "ExportedTime") {
		FBX_Options->AnimSequenceImportData->AnimationLength = EFBXAnimationLengthImportType::FBXALIT_ExportedTime;
	} else if (options_animation_time == "SetRange") {
		FBX_Options->AnimSequenceImportData->AnimationLength = EFBXAnimationLengthImportType::FBXALIT_SetRange;
		FBX_Options->AnimSequenceImportData->FrameImportRange = FInt32Interval(json_animation->GetNumberField(TEXT("frame_range_min")), json_animation->GetNumberField(TEXT("frame_range_max")));
	}

	return FBX_Options;

}
bool FImport_Processer::Process_Materials()
{

		const FString data_path = JsonObject->GetStringField(TEXT("path"));
		
		// Process Materials

		TArray<TSharedPtr<FJsonValue>> objArray = JsonObject->GetArrayField(TEXT("materials"));

		for (int32 i = 0; i < objArray.Num(); i++)
		{
			TSharedPtr<FJsonValue> value = objArray[i];
			TSharedPtr<FJsonObject> json = value->AsObject();
			
			const FString data_name = json->GetStringField(TEXT("name"));
			const FString data_base_color = json->GetStringField(TEXT("base_color"));
			const FString data_orm = json->GetStringField(TEXT("orm"));
			const FString data_normal = json->GetStringField(TEXT("normal"));
			const FString data_ambient_occlusion = json->GetStringField(TEXT("ambient_occlusion"));
			const FString data_metallic = json->GetStringField(TEXT("metallic"));
			const FString data_roughness = json->GetStringField(TEXT("roughness"));
			const FString data_emissive = json->GetStringField(TEXT("emissive"));

			FString PackageName = TEXT("/Game/") + data_path + data_name;

			UPackage* Package = CreatePackage(NULL, *PackageName);

			auto MaterialFactory = NewObject<UMaterialFactoryNew>();
			UMaterial* UnrealMaterial = (UMaterial*)MaterialFactory->FactoryCreateNew(UMaterial::StaticClass(), Package, *data_name, RF_Standalone | RF_Public, NULL, GWarn);
			FAssetRegistryModule::AssetCreated(UnrealMaterial);
			Package->FullyLoad();
			Package->SetDirtyFlag(true);
			
			int32 position_x = -400;
			int32 position_y = -300;

			// Base Color

			if (data_base_color != "") {
			
				FStringAssetReference AssetPath_Base_Color(TEXT("/Game/") + data_path + data_base_color);
				UTexture* Texture_Base_Color = Cast<UTexture>(AssetPath_Base_Color.TryLoad());
				if (Texture_Base_Color)
				{
					UMaterialExpressionTextureSample* TextureExpression = NewObject<UMaterialExpressionTextureSample>(UnrealMaterial);
					TextureExpression->Texture = Texture_Base_Color;
					TextureExpression->SamplerType = SAMPLERTYPE_Color;
					TextureExpression->MaterialExpressionEditorX = position_x;
					TextureExpression->MaterialExpressionEditorY = position_y;
					UnrealMaterial->Expressions.Add(TextureExpression);
					UnrealMaterial->BaseColor.Expression = TextureExpression;
					
				}
				
				position_y += 300;

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
					TextureExpression->MaterialExpressionEditorX = position_x;
					TextureExpression->MaterialExpressionEditorY = position_y;
					UnrealMaterial->Expressions.Add(TextureExpression);
					UnrealMaterial->AmbientOcclusion.Connect(1, TextureExpression); // R
					UnrealMaterial->Roughness.Connect(2, TextureExpression); // G
					UnrealMaterial->Metallic.Connect(3, TextureExpression); // B
					
				}

				position_y += 300;

			} else {

				// Ambient Occlusion

				if (data_ambient_occlusion != "") {

					FStringAssetReference AssetPath_Ambient_Occlusion(TEXT("/Game/") + data_path + data_ambient_occlusion);
					UTexture* Texture_Ambient_Occlusion = Cast<UTexture>(AssetPath_Ambient_Occlusion.TryLoad());
					if (Texture_Ambient_Occlusion)
					{
						UMaterialExpressionTextureSample* TextureExpression = NewObject<UMaterialExpressionTextureSample>(UnrealMaterial);
						TextureExpression->Texture = Texture_Ambient_Occlusion;
						TextureExpression->SamplerType = SAMPLERTYPE_Color;
						TextureExpression->MaterialExpressionEditorX = position_x;
						TextureExpression->MaterialExpressionEditorY = position_y;
						UnrealMaterial->Expressions.Add(TextureExpression);
						UnrealMaterial->AmbientOcclusion.Expression = TextureExpression;
					}
					
					position_y += 300;

				}
				
				// Metallic

				if (data_metallic != "") {

					FStringAssetReference AssetPath_Metallic(TEXT("/Game/") + data_path + data_metallic);
					UTexture* Texture_Metallic = Cast<UTexture>(AssetPath_Metallic.TryLoad());
					if (Texture_Metallic)
					{
						UMaterialExpressionTextureSample* TextureExpression = NewObject<UMaterialExpressionTextureSample>(UnrealMaterial);
						TextureExpression->Texture = Texture_Metallic;
						TextureExpression->SamplerType = SAMPLERTYPE_Color;
						TextureExpression->MaterialExpressionEditorX = position_x;
						TextureExpression->MaterialExpressionEditorY = position_y;
						UnrealMaterial->Expressions.Add(TextureExpression);
						UnrealMaterial->Metallic.Expression = TextureExpression;
					}
					
					position_y += 300;

				}
				
				// Roughness

				if (data_roughness != "") {

					FStringAssetReference AssetPath_Roughness(TEXT("/Game/") + data_path + data_roughness);
					UTexture* Texture_Roughness = Cast<UTexture>(AssetPath_Roughness.TryLoad());
					if (Texture_Roughness)
					{
						UMaterialExpressionTextureSample* TextureExpression = NewObject<UMaterialExpressionTextureSample>(UnrealMaterial);
						TextureExpression->Texture = Texture_Roughness;
						TextureExpression->SamplerType = SAMPLERTYPE_Color;
						TextureExpression->MaterialExpressionEditorX = position_x;
						TextureExpression->MaterialExpressionEditorY = position_y;
						UnrealMaterial->Expressions.Add(TextureExpression);
						UnrealMaterial->Roughness.Expression = TextureExpression;
					}
					
					position_y += 300;

				}

			}
			
			// Emissive

			if (data_emissive != "") {

				FStringAssetReference AssetPath_Emissive(TEXT("/Game/") + data_path + data_emissive);
				UTexture* Texture_Emissive = Cast<UTexture>(AssetPath_Emissive.TryLoad());
				if (Texture_Emissive)
				{
					UMaterialExpressionTextureSample* TextureExpression = NewObject<UMaterialExpressionTextureSample>(UnrealMaterial);
					TextureExpression->Texture = Texture_Emissive;
					TextureExpression->SamplerType = SAMPLERTYPE_Color;
					TextureExpression->MaterialExpressionEditorX = position_x;
					TextureExpression->MaterialExpressionEditorY = position_y;
					UnrealMaterial->Expressions.Add(TextureExpression);
					UnrealMaterial->EmissiveColor.Expression = TextureExpression;

				}

				position_y += 300;

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
					TextureExpression->MaterialExpressionEditorX = position_x;
					TextureExpression->MaterialExpressionEditorY = position_y;
					UnrealMaterial->Expressions.Add(TextureExpression);
					UnrealMaterial->Normal.Expression = TextureExpression;
				}
				
				position_y += 300;

			}
			
			UnrealMaterial->PreEditChange(NULL);
			UnrealMaterial->PostEditChange();

		}
		

	return true;

}

#undef LOCTEXT_NAMESPACE
