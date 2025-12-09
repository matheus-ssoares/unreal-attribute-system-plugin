#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AttributeComponent.h"
#include "AttributeData.h"
#include "AttributeWidget.generated.h"

UCLASS()
class ATTRIBUTESYSTEM_API UAttributeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Call this to link this bar to a specific stat (e.g., Health)
	UFUNCTION(BlueprintCallable, Category = "Attribute UI")
	void BindToAttribute(UAttributeComponent* TargetComp, UAttributeData* TargetAttribute);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Attribute UI")
	UAttributeData* WatchedAttribute;

	// Designers implement this in BP to update the Progress Bar
	UFUNCTION(BlueprintImplementableEvent, Category = "Attribute UI")
	void UpdatePercent(float NewPercent);

private:
	UFUNCTION()
	void OnAttributeChanged(UAttributeData* Attribute, float NewValue, float MaxValue);
};