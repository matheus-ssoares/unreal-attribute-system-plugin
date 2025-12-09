#include "AttributeWidget.h"

void UAttributeWidget::BindToAttribute(UAttributeComponent* TargetComp, UAttributeData* TargetAttribute)
{
	if (!TargetComp || !TargetAttribute) return;

	WatchedAttribute = TargetAttribute;

	TargetComp->OnAttributeChanged.AddDynamic(this, &UAttributeWidget::OnAttributeChanged);

	// Initial Update
	float Current = TargetComp->GetCurrentValue(WatchedAttribute);
	float Max = TargetAttribute->DefaultMaxValue;

	if (Max > 0)
	{
		UpdatePercent(Current / Max);
	}
}

void UAttributeWidget::OnAttributeChanged(UAttributeData* Attribute, float NewValue, float MaxValue)
{
	if (Attribute == WatchedAttribute && MaxValue > 0)
	{
		UpdatePercent(NewValue / MaxValue);
	}
}