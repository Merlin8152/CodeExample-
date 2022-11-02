// Copyright (c) 2020 - 2022 GameWheelStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PZ_ConfirmationWD.h"
#include "PZ_WithTimeConfirmationWD.generated.h"




class UButton;
class UTextBlock;


/*
	Standard confirmation with time to answer.
*/
UCLASS()
class PZ_UITOOLS_API UPZ_WithTimeConfirmationWD : public UPZ_ConfirmationWD
{
	GENERATED_BODY()


//Constructor
public:

	UPZ_WithTimeConfirmationWD(const FObjectInitializer& ObjectInitializer);


//c++ protected methods
protected:

	virtual void NativeConstruct() override;


//c++ protected values
protected:


	FString FunctionName_TimeEnd;

	float TimeToAnswer = 0.0f;
	bool AnswerWasSelected = false;



//>>...........................................................................................................................................<<//


//Blueprint protected methods
protected:
	
	virtual void OnYesButtonPressed_Implementation() override;

	virtual void OnNoButtonPressed_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "WithTimeConfirmationWD")
		void OnTimeEnd();
		virtual void OnTimeEnd_Implementation();

//Blueprint public methods
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "WithTimeConfirmationWD")
		void InitializeWithTimeConfirmationWD
		(
			UObject* InOwner, const FText& InText, const FText& InTimeEndText, float InTimeToAnswer,
			const FString& InFunctionName_Yes, const FString& InFunctionName_No, const FString& InFunctionName_TimeEnd
		);
		virtual void InitializeWithTimeConfirmationWD_Implementation
		(
			UObject* InOwner, const FText& InText, const FText& InTimeEndText, float InTimeToAnswer,
			const FString& InFunctionName_Yes, const FString& InFunctionName_No, const FString& InFunctionName_TimeEnd
		);


//Blueprint values
public:

	/*
		Text block for showing confirmation time end text.
	*/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "WithTimeConfirmationWD|Widgets")
		UTextBlock* TimeEndConfirmationText = nullptr;
};
