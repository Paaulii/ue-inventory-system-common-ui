#include "UI/UIS_CommonUILayerTags.h"

namespace UI::Layer
{
	// HUD
	UE_DEFINE_GAMEPLAY_TAG(Game, "UI.Layer.Game")

	// Menus related to gameplay eg. Inventory
	UE_DEFINE_GAMEPLAY_TAG(GameMenu, "UI.Layer.GameMenu")

	// Screen like eg. settings 
	UE_DEFINE_GAMEPLAY_TAG(Menu, "UI.Layer.Menu")

	// Confirmation dialogs, error dialogs
	UE_DEFINE_GAMEPLAY_TAG(Modal, "UI.Layer.Modal")
}
