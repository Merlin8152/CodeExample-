// Copyright (c) 2020 - 2022 GameWheelStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PZ_ConfirmationWD.generated.h"




class UButton;
class UTextBlock;



/*
	UI element that implements Yes/No question.
*/
UCLASS(Abstract)
class PZ_UITOOLS_API UPZ_ConfirmationWD : public UUserWidget
{
	GENERATED_BODY()
	

//Constructor
public:

	UPZ_ConfirmationWD(const FObjectInitializer& ObjectInitializer);



//c++ protected methods
protected:

	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

//c++ private values
private:

	bool WasKeyPressed = false;

//c++ protected values
protected:

	FString FunctionName_Yes;
	FString FunctionName_No;

	UPROPERTY()
		UObject* FunctionsOwner = nullptr;



//>>...........................................................................................................................................<<//


//Blueprint protected methods
protected:

	UFUNCTION(BlueprintNativeEvent, Category = "ConfirmationWD")
		void OnYesButtonPressed();
		virtual void OnYesButtonPressed_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "ConfirmationWD")
		void OnNoButtonPressed();
		virtual void OnNoButtonPressed_Implementation();

//Blueprint public methods
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ConfirmationWD")
		void InitializeConfirmationWD(UObject* InOwner, const FText& InText, const FString& InFunctionName_Yes, const FString& InFunctionName_No);
		virtual void InitializeConfirmationWD_Implementation(UObject* InOwner, const FText& InText, const FString& InFunctionName_Yes, const FString& InFunctionName_No);



//Blueprint values
public:

	/*
		Button for call YES action.
	*/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "ConfirmationWD|Widgets")
		UButton* YesButton = nullptr;
	/*
		Button for call NO action
	*/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "ConfirmationWD|Widgets")
		UButton* NoButton = nullptr;
	/*
		Text block for showing confirmation text.
	*/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "ConfirmationWD|Widgets")
		UTextBlock* ConfirmationText = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ConfirmationWD")
		FName ConfirmationInputAction_Yes = "ConfirmationYes";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ConfirmationWD")
		FName ConfirmationInputAction_No = "ConfirmationNo";

};
