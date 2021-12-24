// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGraphPin.h"


class SPZ_SSkillTreeGraphPin : public SGraphPin
{

	typedef SGraphPin Super;
	typedef SPZ_SSkillTreeGraphPin Self;


public:

	SLATE_BEGIN_ARGS(Self) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InPin);



protected:
	
	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override;
	virtual FSlateColor GetPinColor() const override;
	const FSlateBrush* GetPinBorder() const;
	
};
