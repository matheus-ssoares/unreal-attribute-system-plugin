#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeData.h"
#include "GameplayTagContainer.h"
#include "AttributeComponent.generated.h"

USTRUCT(BlueprintType)
struct FAttributeValue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	float CurrentValue = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	float MaxValue = 0.0f;
};

// Event when values change (for UI bars)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, UAttributeData*, Attribute, float, NewValue, float, MaxValue);

// Event when a specific threshold (Zero) is reached, passing the custom tag
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeThresholdReached, FGameplayTag, TriggerTag);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ATTRIBUTESYSTEM_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAttributeComponent();

	// Attributes to initialize on BeginPlay
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	TArray<UAttributeData*> DefaultAttributes;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAttributeChanged OnAttributeChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAttributeThresholdReached OnAttributeThresholdReached;

	virtual void BeginPlay() override;

	// Main function to modify stats
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyAttributeChange(UAttributeData* Attribute, float Delta);

	// Helper to get current value
	UFUNCTION(BlueprintPure, Category = "Attributes")
	float GetCurrentValue(UAttributeData* Attribute);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Attributes")
	TMap<UAttributeData*, FAttributeValue> AttributeContainer;
};