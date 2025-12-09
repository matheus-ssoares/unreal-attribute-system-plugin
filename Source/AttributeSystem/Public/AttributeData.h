#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h" 
#include "AttributeData.generated.h"

UCLASS(BlueprintType)
class ATTRIBUTESYSTEM_API UAttributeData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float DefaultMaxValue = 100.0f;

	// The Custom Parameter: If the attribute hits 0, this tag is broadcasted.
	// Example: "Event.Death" or "State.Exhausted"
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Logic")
	FGameplayTag ZeroTriggerTag;
};