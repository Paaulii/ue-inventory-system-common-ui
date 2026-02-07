// 

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UIS_CommonUIExtensions.generated.h"

struct FGameplayTag;
/**
 * 
 */
UCLASS()
class UISYSTEM_API UUIS_CommonUIExtensions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Extensions")
	static UCommonActivatableWidget* PushContentToLayer(const ULocalPlayer* LocalPlayer, UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerName, UPARAM(meta = (AllowAbstract = false)) TSubclassOf<UCommonActivatableWidget> WidgetClass);
};
