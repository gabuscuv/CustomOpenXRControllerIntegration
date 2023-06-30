# CustomOpenXRControllerIntegration

## Notice

This Library doesn't use have any assets from Intelectual Properties.  
This only reference Assets from Official OpenXR Plugin from Unreal Engine.

## Description

This project allows you, in a less painful way, to display highlighted buttons on OpenXR controllers in-game, ideal for tutorials, user reminders, and other tasks.

## Installation

- Clone OpenXRExpansion:
  - If you are using an already git repo, Run `git submodule add https://github.com/mordentral/VRExpansionPlugin.git Plugins/` in your project folder.
- Clone this repo:
  - If you are using an already git repo, Run `git submodule add git@github.com:gabuscuv/CustomOpenXRControllerIntegration.git Plugins/` in your project folder.

## How To Use

Just add/attach OpenXRController Actor where do you want,
It will autodetect your Controller in runtime (set the "leftcontroller" checkbox if you want Left Controller Models)

For use the highlight function, I recommend you, add the "OpenXRControllerCoordinatorComponent" to your Player Pawn Actor and add two childactorsComponents with OpenXRController and set their names in the OpenXRControllerCoordinatorComponent.

You can use the Plugin's Map and Tools for a DEMO of the controller highlighting system.

For using the Highlight System, Just call functions in the OpenXRCoordinator.
like:

- `void ShowControllerAndHighlightButtons(EActionButtons button, bool lefthanded);`
- `void ShouldShowController(bool left, UObject *object);`
- `void HideControllerVisibility();`

All of them accesible via Blueprints or C++ code.
