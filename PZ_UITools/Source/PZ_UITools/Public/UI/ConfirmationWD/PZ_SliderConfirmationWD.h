// Copyright (c) 2020 - 2022 GameWheelStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PZ_ConfirmationWD.h"
#include "PZ_SliderConfirmationWD.generated.h"




class USlider;
class UButton;
class UTextBlock;



/*
	UI element that implements Yes/No question with interpolation value.
*/
UCLASS(Abstract)
class PZ_UITOOLS_API UPZ_SliderConfirmationWD : public UPZ_ConfirmationWD
{
	GENERATED_BODY()

//Constructor
public:

	UPZ_SliderConfirmationWD(const FObjectInitializer& ObjectInitializer);




//c++ protected methods
protected:

	virtual void NativeConstruct() override;


	UFUNCTION()
		void OnSliderValueChanged(float Value);


	/*
		@return current slider value in text format.
		@see DisplaySliderValueAsInt.
	*/
	FText GetSliderValueAsText(float Value) const;


//c++ protected values
protected:


//>>.........................................................................................................................<<//


//Blueprint protected methods
protected:

	virtual void OnYesButtonPressed_Implementation() override;
	virtual void OnNoButtonPressed_Implementation() override;

//Blueprint public methods
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SliderConfirmationWD")
		void InitializeSliderConfirmationWD(UObject* InOwner, const FString& InFunctionName_Yes, const FString& InFunctionName_No, float MaxValue);
		virtual void InitializeSliderConfirmationWD_Implementation(UObject* InOwner, const FString& InFunctionName_Yes, const FString& InFunctionName_No, float MaxValue);

	UFUNCTION(BlueprintCallable, Category = "SliderConfirmationWD")
		void SetSliderValue(float NewValue);
	UFUNCTION(BlueprintCallable, Category = "SliderConfirmationWD")
		float GetCurrentSliderValue() const;
	UFUNCTION(BlueprintCallable, Category = "SliderConfirmationWD")
		void SetSliderValueDisplayType(bool NewDisplaySliderValueAsInt);


//Blueprint values
public:

	/*
		Default slider value for creation.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SliderConfirmationWD")
		float DefaultSliderValue = 0.0f;
	/*
		How many digits will be shown for float after dot.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "!DisplaySliderValueAsInt"), Category = "SliderConfirmationWD")
		int DisplayDigitsCount = 2;
	/*
		If true then displaying value will be rounded to nearest int.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SliderConfirmationWD")
		bool DisplaySliderValueAsInt = true;

	/*
		Slider for value selecting.
	*/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "SliderConfirmationWD|Widgets")
		USlider* ConfirmSlider = nullptr;
	/*
		Text block for showing current value.
	*/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "SliderConfirmationWD|Widgets")
		UTextBlock* SliderCountText = nullptr;

};
