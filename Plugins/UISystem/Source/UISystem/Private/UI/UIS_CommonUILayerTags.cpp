#include "UI/UIS_CommonUILayerTags.h"

namespace UI::Layer
{
	// HUD
	UE_DEFINE_GAMEPLAY_TAG(Game, TEXT("UI.Layer.Game"))

	// Menus related to gameplay eg. Inventory
	UE_DEFINE_GAMEPLAY_TAG(GameMenu, TEXT("UI.Layer.GameMenu"))

	// Screen like eg. settings 
	UE_DEFINE_GAMEPLAY_TAG(Menu, TEXT("UI.Layer.Menu"))

	// Confirmation dialogs, error dialogs
	UE_DEFINE_GAMEPLAY_TAG(Modal, TEXT("UI.Layer.Modal"))
}
