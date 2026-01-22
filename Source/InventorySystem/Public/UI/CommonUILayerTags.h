#pragma once

#include "NativeGameplayTags.h"

namespace UI
{
	namespace Layer
	{
		// HUD
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Game)

		// Menus related to gameplay eg. Inventory
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameMenu)
		
		// Screen like eg. settings 
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Menu)

		// Confirmation dialogs, error dialogs
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Modal)
	}
}
