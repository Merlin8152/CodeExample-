// Copyright (c) 2020 - 2022 GameWheelStudio. All rights reserved.

#include "UI/ConfirmationWD/PZ_WithTimeConfirmationWD.h"

//...............Subwidgets/Elements................//

#include "Components/Button.h"
#include "Components/TextBlock.h"

//..................................................//

#include "Misc/OutputDeviceNull.h"
#include "TimerManager.h"





UPZ_WithTimeConfirmationWD::UPZ_WithTimeConfirmationWD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}



void UPZ_WithTimeConfirmationWD::NativeConstruct()
{
	Super::NativeConstruct();

}


void UPZ_WithTimeConfirmationWD::InitializeWithTimeConfirmationWD_Implementation(UObject* InOwner, const FText& InText, const FText& InTimeEndText, float InTimeToAnswer, const FString& InFunctionName_Yes, const FString& InFunctionName_No, const FString& InFunctionName_TimeEnd)
{
	InitializeConfirmationWD(InOwner, InText, InFunctionName_Yes, InFunctionName_No);
	FunctionName_TimeEnd = InFunctionName_TimeEnd;
	TimeToAnswer = InTimeToAnswer;
	if( TimeEndConfirmationText ) TimeEndConfirmationText->SetText(InTimeEndText);

	if( TimeToAnswer > 0 )
	{
		FTimerHandle LTimerHandle;
		FTimerDelegate TimerDel;
		TimerDel.BindUFunction(this, FName("OnTimeEnd"));
		GetWorld()->GetTimerManager().SetTimer(LTimerHandle, TimerDel, TimeToAnswer, false);
	}
}


void UPZ_WithTimeConfirmationWD::OnYesButtonPressed_Implementation()
{
	AnswerWasSelected = true;
	Super::OnYesButtonPressed_Implementation();
}

void UPZ_WithTimeConfirmationWD::OnNoButtonPressed_Implementation()
{
	AnswerWasSelected = true;
	Super::OnNoButtonPressed_Implementation();
}

void UPZ_WithTimeConfirmationWD::OnTimeEnd_Implementation()
{
	if( !AnswerWasSelected && IsValid(FunctionsOwner) )
	{
		FOutputDeviceNull Ar;
		FunctionsOwner->CallFunctionByNameWithArguments(*FunctionName_TimeEnd, Ar, FunctionsOwner, true);
	}
}
