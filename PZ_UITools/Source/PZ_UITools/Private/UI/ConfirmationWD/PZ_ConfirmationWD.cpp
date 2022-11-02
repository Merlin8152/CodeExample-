// Copyright (c) 2020 - 2022 GameWheelStudio. All rights reserved.

#include "UI/ConfirmationWD/PZ_ConfirmationWD.h"

//...............Subwidgets/Elements................//

#include "Components/Button.h"
#include "Components/TextBlock.h"

//..................................................//

#include "Misc/OutputDeviceNull.h"
#include "GameFramework/InputSettings.h"




UPZ_ConfirmationWD::UPZ_ConfirmationWD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsFocusable = true;
}



void UPZ_ConfirmationWD::NativeConstruct()
{
	Super::NativeConstruct();


	if( YesButton ) YesButton->OnClicked.AddDynamic(this, &UPZ_ConfirmationWD::OnYesButtonPressed);
	if( NoButton ) NoButton->OnClicked.AddDynamic(this, &UPZ_ConfirmationWD::OnNoButtonPressed);
}

FReply UPZ_ConfirmationWD::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if( WasKeyPressed ) return FReply::Unhandled();
	WasKeyPressed = true;

	TArray<FInputActionKeyMapping> LOutMappings;
	UInputSettings::GetInputSettings()->GetActionMappingByName(ConfirmationInputAction_Yes, LOutMappings);
	UInputSettings::GetInputSettings()->GetActionMappingByName(ConfirmationInputAction_No, LOutMappings);
	if( LOutMappings.Num() != 2 ) return FReply::Unhandled();
	if( InKeyEvent.GetKey() == LOutMappings[0].Key )
	{
		OnYesButtonPressed();
		return FReply::Handled();
	}
	if( InKeyEvent.GetKey() == LOutMappings[1].Key )
	{
		OnNoButtonPressed();
		return FReply::Handled();
	}

	return FReply::Unhandled();
}

FReply UPZ_ConfirmationWD::NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyUp(InGeometry, InKeyEvent);

	WasKeyPressed = false;

	return FReply::Unhandled();
}


void UPZ_ConfirmationWD::InitializeConfirmationWD_Implementation(UObject* InOwner, const FText& InText, const FString& InFunctionName_Yes, const FString& InFunctionName_No)
{
	FunctionsOwner = InOwner;
	FunctionName_Yes = InFunctionName_Yes;
	FunctionName_No = InFunctionName_No;

	if( ConfirmationText ) ConfirmationText->SetText(InText);
}



void UPZ_ConfirmationWD::OnYesButtonPressed_Implementation()
{
	if( IsValid(FunctionsOwner) )
	{
		FOutputDeviceNull Ar;
		FunctionsOwner->CallFunctionByNameWithArguments(*FunctionName_Yes, Ar, FunctionsOwner, true);
	}
}

void UPZ_ConfirmationWD::OnNoButtonPressed_Implementation()
{
	if( IsValid(FunctionsOwner) )
	{
		FOutputDeviceNull Ar;
		FunctionsOwner->CallFunctionByNameWithArguments(*FunctionName_No, Ar, FunctionsOwner, true);
	}
}