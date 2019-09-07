# UE Blender Importer

Unreal Engine Editor Plugin for processing meshes imported from Blender. Designed to work with the blender addon: https://github.com/DigiKrafting/blender_addon_ue.

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

# Installation

Download either the tar.gz or zip from [https://github.com/DigiKrafting/ue_blender_importer/releases/latest](https://github.com/DigiKrafting/ue_blender_importer/releases/latest)

Extract to your Plugins folder (if it doesn't exist you'll need to create it) or to C:\Program Files\Epic Games\UE_4.23\Engine\Plugins\Editor.

E.g. c:/projects/projects/plugins (Should be the same level as your Content folder c:/projects/projects/Content)

# Screenshots
## Blender
![alt](/screenshots/ue_blender.png)
## Unreal Editor
![alt](/screenshots/ue_material_setup.png)
