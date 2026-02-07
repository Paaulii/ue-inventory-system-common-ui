#pragma once
#include "UIS_GameUIPolicy.generated.h"

class UUIS_LocalPlayer;
class UUIS_PrimaryGameLayout;

UCLASS(Abstract, Blueprintable)
class UISYSTEM_API UUIS_GameUIPolicy : public UObject
{
	GENERATED_BODY()
public:
	UUIS_PrimaryGameLayout* GetRootLayout() const { return RootLayout; }
protected:
	void CreateLayoutWidget(UUIS_LocalPlayer* LocalPlayer);
	void AddLayoutToViewport(UUIS_LocalPlayer* LocalPlayer, UUIS_PrimaryGameLayout* Layout);
	virtual void OnRootLayoutAddedToViewport(UUIS_LocalPlayer* LocalPlayer, UUIS_PrimaryGameLayout* Layout);
	void RemoveLayoutFromViewport(UUIS_PrimaryGameLayout* Layout);
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUIS_PrimaryGameLayout> LayoutClass;

	UPROPERTY()
	TObjectPtr<UUIS_PrimaryGameLayout> RootLayout = nullptr;

	void NotifyPlayerAdded(UUIS_LocalPlayer* LocalPlayer);
	void NotifyPlayerDestroyed(UUIS_LocalPlayer* LocalPlayer);

	friend class UUIS_UIManagerSubsystem;
};