# UE Blender Importer

Unreal Engine Editor Plugin for processing FBX's imported from Blender. Designed to work with the blender addon https://github.com/DigiKrafting/blender_addon_ue which creates a "{fbx_file_name}.bjd" needed for this plugin to activate.

This plugin utilises the standard built in FBX import by using "UFbxFactory" as a child class so essentially it's only passing options from the ".bjd" file and assigning textures to materials.

\* WIP - ALPHA (All the hard stuff is figured out now :) Just need to expose/make more options available)

# Features

- Automagically imports fbx's from settings set in Blender.
- Assigns textures to materials.

# Roadmap

- Implement more options for import.
- Submit to Marketplace once stable and well tested.

# Required Unreal Version

4.23

\* The source compiles in 4.22 (Tested) and maybe (?) earlier versions.

# NOTES 

\* There is no UI or editor toolbar buttons!!!

### {fbx_file_name}.bjd
~~~
{
   "Path":"Meshes/Test/",
   "Options":{
      "ImportMesh":true,
      "ImportMaterials":true,
      "ImportAnimations":true,
      "CreatePhysicsAsset":true,
      "AutoComputeLodDistances":true,
      "Static_Mesh":{
         "NormalImportMethod":"ImportNormalsAndTangents",
         "ImportMeshLODs":false,
         "CombineMeshes":false,
         "AutoGenerateCollision":true
      },
      "Skeletal_Mesh":{
         "NormalImportMethod":"ImportNormalsAndTangents",
         "ImportMeshLODs":false,
         "UseT0AsRefPose":true,
         "PreserveSmoothingGroups":true,
         "ImportMorphTargets":false
      },
      "Animation":{
         "AnimationLength":"ExportedTime",
         "FrameRangeMin":0,
         "FrameRangeMax":0,
         "ImportMeshesInBoneHierarchy":true,
         "UseDefaultSampleRate":false,
         "CustomSampleRate":0,
         "ConvertScene":true
      }
   },
   "Materials":[
      {
         "Name":"Material",
         "BaseColor":"Textures/Cube_Material_BaseColor",
         "Normal":"Textures/Cube_Material_Normal",
         "Orm":"Textures/Cube_Material_OcclusionRoughnessMetallic",
         "Opacity":"",
         "AmbientOcclusion":"",
         "Metallic":"",
         "Roughness":"",
         "Emissive":"Textures/Cube_Material_Emissive"
      }
   ]
}
~~~

# Installation

Download either the tar.gz or zip from [https://github.com/DigiKrafting/ue_plugin_blender/releases/latest](https://github.com/DigiKrafting/ue_plugin_blender/releases/latest)

Extract and copy "Blender_Importer" to your projects "Plugins" folder (if it doesn't exist you'll need to create it) or to "C:\Program Files\Epic Games\UE_4.23\Engine\Plugins\Editor".

E.g. "C:\Users\kye\Documents\Unreal Projects\DKS_Importer_Project\Plugins" (Should be the same level as your Content folder "C:\Users\kye\Documents\Unreal Projects\DKS_Importer_Project\Content")

You should end up with "Plugins/Blender_Importer".

# Screenshots
## Blender
![alt](/screenshots/ue_blender.png)
## Unreal Editor
![alt](/screenshots/ue_material_setup.png)
## Material Editor
![alt](/screenshots/ue_material_nodes.png)
