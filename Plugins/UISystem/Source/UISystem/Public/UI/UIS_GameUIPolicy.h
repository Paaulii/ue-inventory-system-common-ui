#pragma once
#include "UIS_PrimaryGameLayout.h"
#include "UIS_GameUIPolicy.generated.h"

class UUIS_LocalPlayer;

UCLASS(Abstract, Blueprintable)
class UISYSTEM_API UUIS_GameUIPolicy : public UObject
{
	GENERATED_BODY()
	
public:
	UUIS_PrimaryGameLayout* GetRootLayout() const { return RootLayout; }
	
protected:
	virtual void OnRootLayoutAddedToViewport(UUIS_LocalPlayer* LocalPlayer, UUIS_PrimaryGameLayout* Layout);
	void CreateLayoutWidget(UUIS_LocalPlayer* LocalPlayer);
	void AddLayoutToViewport(UUIS_LocalPlayer* LocalPlayer, UUIS_PrimaryGameLayout* Layout);
	void RemoveLayoutFromViewport(UUIS_PrimaryGameLayout* Layout);
	
private:
	void NotifyPlayerAdded(UUIS_LocalPlayer* LocalPlayer);
	void NotifyPlayerDestroyed(UUIS_LocalPlayer* LocalPlayer);

	UPROPERTY(EditAnywhere, Category = "UI | Layout")
	TSubclassOf<UUIS_PrimaryGameLayout> LayoutClass = {};

	UPROPERTY()
	TObjectPtr<UUIS_PrimaryGameLayout> RootLayout = nullptr;
	
	friend class UUIS_UIManagerSubsystem;
};