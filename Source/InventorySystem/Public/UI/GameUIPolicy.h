#pragma once
#include "GameUIPolicy.generated.h"

class UCommonLocalPlayer;
class UPrimaryGameLayout;

UCLASS(Abstract, Blueprintable)
class INVENTORYSYSTEM_API UGameUIPolicy : public UObject
{
	GENERATED_BODY()
public:
	UPrimaryGameLayout* GetRootLayout() const { return RootLayout; }
protected:
	void CreateLayoutWidget(UCommonLocalPlayer* LocalPlayer);
	void AddLayoutToViewport(UCommonLocalPlayer* LocalPlayer, UPrimaryGameLayout* Layout);
	virtual void OnRootLayoutAddedToViewport(UCommonLocalPlayer* LocalPlayer, UPrimaryGameLayout* Layout);
	void RemoveLayoutFromViewport(UPrimaryGameLayout* Layout);
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPrimaryGameLayout> LayoutClass;

	UPROPERTY()
	TObjectPtr<UPrimaryGameLayout> RootLayout = nullptr;

	void NotifyPlayerAdded(UCommonLocalPlayer* LocalPlayer);
	void NotifyPlayerDestroyed(UCommonLocalPlayer* LocalPlayer);

	friend class UGameUIManagerSubsystem;
};