# UE Blender Importer

Unreal Engine Editor Plugin for processing meshes imported from Blender. Designed to work with the blender addon https://github.com/DigiKrafting/blender_addon_ue which creates the "blender_addon_ue_data.json" needed for this plugin to activate.

\* WIP - ALPHA

# Features

- Assigns textures to materials for mesh exported from Blender

# Roadmap

- Automatically process imported fbx's with options set from Blender.

# Required Unreal Version

4.23

# NOTES 

\* There is no UI or editor toolbar buttons. The plugin activates on detection of a new "blender_addon_ue_data.json" file.

### blender_addon_ue_data.json
~~~
{
    "path": "Meshes/Test/",
    "materials": [
        {
            "name": "Material",
            "base_color": "Textures/Cube_Material_BaseColor",
            "normal": "Textures/Cube_Material_Normal",
            "orm": "Textures/Cube_Material_OcclusionRoughnessMetallic",
            "opacity": "",
            "ambient_occlusion": "",
            "metallic": "",
            "roughness": ""
        }
    ]
}
~~~

### Log Error Message
~~~
AssetReimport: Failed to import file C:/Users/kye/Documents/Unreal Projects/DKS_Importer_Project/Content/Meshes/Test/blender_addon_ue_data.json.
~~~

This can be ignored as nothing is actually imported, blender_addon_ue_data.json is deleted once processed.

\* If a UObject is returned from UImport_Factory::FactoryCreateFile, "blender_addon_ue_data.uasset" gets created. I tried returning the material from FImport_Processer::Process_JSON_Data, the error goes aways with a valid imported message, but the unneeded uasset file is created.

# Installation

Download either the tar.gz or zip from [https://github.com/DigiKrafting/ue_blender_importer/releases/latest](https://github.com/DigiKrafting/ue_blender_importer/releases/latest)

Extract and copy "Blender_Importer" to your projects "Plugins" folder (if it doesn't exist you'll need to create it) or to "C:\Program Files\Epic Games\UE_4.23\Engine\Plugins\Editor".

E.g. "C:\Users\kye\Documents\Unreal Projects\DKS_Importer_Project\Plugins" (Should be the same level as your Content folder "C:\Users\kye\Documents\Unreal Projects\DKS_Importer_Project\Content")

You should end up with Plugins/Blender_Importer.

# Screenshots
## Blender
![alt](/screenshots/ue_blender.png)
## Unreal Editor
![alt](/screenshots/ue_material_setup.png)
