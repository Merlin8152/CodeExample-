// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"


class UPZ_SkillTreeUIPositionEdNode_Base;


class SPZ_SkillTreeUIPositionSNode_Base : public SGraphNode
{

	typedef SGraphNode Super;
	typedef SPZ_SkillTreeUIPositionSNode_Base Self;


public:

	SLATE_BEGIN_ARGS(SPZ_SkillTreeUIPositionSNode_Base) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UPZ_SkillTreeUIPositionEdNode_Base* InNode);



	virtual void UpdateGraphNode() override;
	virtual void CreateNodeWidget();

	void CreateCommentBubble();

	virtual void CreatePinWidgets() override;
	virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;
	virtual void CreateStandardPinWidget(UEdGraphPin* Pin) override;
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;

	virtual bool IsNameReadOnly() const override;




	virtual FText GetNodeName() const;
	
	virtual FLinearColor GetNodeTitleColor() const;
	virtual FLinearColor GetNodeBackgroundColor_Default() const;
	FSlateColor GetNodeBackgroundColor() const;
	virtual const FSlateBrush* GetBackgroundImage() const;
	virtual const FSlateBrush* GetNodeImage() const;
	virtual const float GetNodeBodyPadding() const;
	virtual const FSlateBrush* GetErrorImage() const;

	virtual const EVisibility GetTopPinsBoxVisibility() const;

	void FillAdditionalNodeInfo();
	virtual void GetAdditionalNodeInfo(TArray<FString>& AdditionalInfoArray) {};



protected:

	TSharedPtr<SHorizontalBox> BottomPinBox;
	TSharedPtr<SHorizontalBox> TopPinBox;
	TSharedPtr<SOverlay> NodeWidget;
	TSharedPtr<SVerticalBox> AdditionalNodeInfo;
	TSharedPtr<SErrorText> ErrorText;
	TArray<FString> AdditionalNodeInfo_LinesArray;

	FSlateBrush IconBrush;
};
