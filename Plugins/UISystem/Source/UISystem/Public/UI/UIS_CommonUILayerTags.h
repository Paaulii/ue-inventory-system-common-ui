#pragma once

#include "NativeGameplayTags.h"

namespace UI::Layer
{
	// HUD
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UISYSTEM_API  Game)

	// Menus related to gameplay eg. Inventory
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UISYSTEM_API GameMenu)

	// Screen like eg. settings 
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UISYSTEM_API Menu)

	// Confirmation dialogs, error dialogs
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UISYSTEM_API Modal)
}
