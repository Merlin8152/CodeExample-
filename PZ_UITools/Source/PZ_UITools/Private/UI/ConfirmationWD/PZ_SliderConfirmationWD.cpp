// Copyright (c) 2020 - 2022 GameWheelStudio. All rights reserved.

#include "UI/ConfirmationWD/PZ_SliderConfirmationWD.h"

//...............Subwidgets/Elements................//

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"

//..................................................//

#include "Misc/OutputDeviceNull.h"





UPZ_SliderConfirmationWD::UPZ_SliderConfirmationWD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	if( ConfirmationText ) ConfirmationText->SetVisibility(ESlateVisibility::Collapsed);
}


void UPZ_SliderConfirmationWD::NativeConstruct()
{
	Super::NativeConstruct();

	if( ConfirmSlider ) ConfirmSlider->OnValueChanged.AddDynamic(this, &UPZ_SliderConfirmationWD::OnSliderValueChanged);

	if( SliderCountText ) SliderCountText->SetText(GetSliderValueAsText(DefaultSliderValue));
}

void UPZ_SliderConfirmationWD::InitializeSliderConfirmationWD_Implementation(UObject* InOwner, const FString& InFunctionName_Yes, const FString& InFunctionName_No, float MaxValue)
{
	InitializeConfirmationWD(InOwner, {}, InFunctionName_Yes, InFunctionName_No);

	if( ConfirmSlider )
	{
		ConfirmSlider->SetMaxValue(MaxValue);
		ConfirmSlider->SetValue(DefaultSliderValue);
	}
}


void UPZ_SliderConfirmationWD::SetSliderValue(float NewValue)
{
	if( !IsValid(ConfirmSlider) ) return;

	ConfirmSlider->SetValue(NewValue);
}

float UPZ_SliderConfirmationWD::GetCurrentSliderValue() const
{
	if( !IsValid(ConfirmSlider) ) return 0.0f;

	return ConfirmSlider->GetValue();
}

void UPZ_SliderConfirmationWD::SetSliderValueDisplayType(bool NewDisplaySliderValueAsInt)
{
	DisplaySliderValueAsInt = NewDisplaySliderValueAsInt;

	if( IsValid(SliderCountText) )
	{
		SliderCountText->SetText(GetSliderValueAsText(GetCurrentSliderValue()));
	}
}

void UPZ_SliderConfirmationWD::OnSliderValueChanged(float Value)
{
	if( !IsValid(SliderCountText) ) return;

	SliderCountText->SetText(GetSliderValueAsText(Value));
}


void UPZ_SliderConfirmationWD::OnYesButtonPressed_Implementation()
{
	FunctionName_Yes.Append(FString(" "));

	FunctionName_Yes.AppendInt(GetCurrentSliderValue());

	Super::OnYesButtonPressed_Implementation();
}

void UPZ_SliderConfirmationWD::OnNoButtonPressed_Implementation()
{
	Super::OnNoButtonPressed_Implementation();
}


FText UPZ_SliderConfirmationWD::GetSliderValueAsText(float Value) const
{
	if( DisplaySliderValueAsInt )
	{
		return FText::AsNumber(FMath::RoundToInt(Value));
	}
	FNumberFormattingOptions NumberFormattingOptions;
	NumberFormattingOptions.MaximumFractionalDigits = DisplayDigitsCount;
	return FText::AsNumber(Value, &NumberFormattingOptions);
}
