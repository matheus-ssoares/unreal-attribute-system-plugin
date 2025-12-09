#include "AttributeComponent.h"

UAttributeComponent::UAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// Initialize attributes from the list
	for (UAttributeData* Attr : DefaultAttributes)
	{
		if (Attr)
		{
			FAttributeValue NewVal;
			NewVal.MaxValue = Attr->DefaultMaxValue;
			NewVal.CurrentValue = Attr->DefaultMaxValue;

			AttributeContainer.Add(Attr, NewVal);
		}
	}
}

bool UAttributeComponent::ApplyAttributeChange(UAttributeData* Attribute, float Delta)
{
	if (!Attribute || !AttributeContainer.Contains(Attribute)) return false;

	FAttributeValue& Val = AttributeContainer[Attribute];

	// Apply math and clamp between 0 and Max
	Val.CurrentValue = FMath::Clamp(Val.CurrentValue + Delta, 0.0f, Val.MaxValue);

	// Notify UI (Health Bars, etc.)
	OnAttributeChanged.Broadcast(Attribute, Val.CurrentValue, Val.MaxValue);

	// Check if we hit the limit (Zero) AND if this attribute has a Trigger Tag
	if (Val.CurrentValue <= 0.0f && Attribute->ZeroTriggerTag.IsValid())
	{
		// Broadcast the custom tag (e.g., Event.Death)
		OnAttributeThresholdReached.Broadcast(Attribute->ZeroTriggerTag);
	}

	return true;
}

float UAttributeComponent::GetCurrentValue(UAttributeData* Attribute)
{
	if (Attribute && AttributeContainer.Contains(Attribute))
	{
		return AttributeContainer[Attribute].CurrentValue;
	}
	return 0.0f;
}