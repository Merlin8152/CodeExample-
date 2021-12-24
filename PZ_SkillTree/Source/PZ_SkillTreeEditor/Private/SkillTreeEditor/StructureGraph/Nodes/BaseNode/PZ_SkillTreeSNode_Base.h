// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"


class UPZ_SkillTreeEdNode_Base;


class SPZ_SkillTreeSNode_Base : public SGraphNode
{
	typedef SGraphNode Super;
	typedef SPZ_SkillTreeSNode_Base Self;


public:

	SLATE_BEGIN_ARGS(SPZ_SkillTreeSNode_Base) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UPZ_SkillTreeEdNode_Base* InNode);



	virtual void UpdateGraphNode() override;
	virtual void UpdateGraphNode_ResetStage() {};
	virtual void CreateNodeWidget();
	virtual void CreateNodeWidget_TopPart() {};
	virtual void CreateNodeWidget_BottomPart() {};

	void CreateCommentBubble();

	virtual void CreatePinWidgets() override;
	virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;
	virtual void CreateStandardPinWidget(UEdGraphPin* Pin) override;
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;
	virtual void SetOwner(const TSharedRef<SGraphPanel>& OwnerPanel) override;

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
	virtual const EVisibility GetBottomPinsBoxVisibility() const;

	virtual void AddSubNode(TSharedPtr<SGraphNode> SubNodeWidget);

	void FillAdditionalNodeInfo();
	virtual void GetAdditionalNodeInfo(TArray<FString>& AdditionalInfoArray);
	virtual TSharedRef<SGraphNode> GetNodeUnderMouse(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	TSharedPtr<SGraphNode> GetSubNodeUnderCursor(const FGeometry& WidgetGeometry, const FPointerEvent& MouseEvent);

	FReply OnMouseDown(const FGeometry& SenderGeometry, const FPointerEvent& MouseEvent);

	virtual void MoveTo(const FVector2D& NewPosition, FNodeSet& NodeFilter) override;

protected:
	TArray< TSharedPtr<SGraphNode> > SubNodes;

	TSharedPtr<SHorizontalBox> BottomPinBox;
	TSharedPtr<SHorizontalBox> TopPinBox;
	TSharedPtr<SOverlay> NodeWidget;
	TSharedPtr<SOverlay> NodeWidget_TopPart;
	TSharedPtr<SOverlay> NodeWidget_BottomPart;
	TSharedPtr<SVerticalBox> AdditionalNodeInfo;
	TSharedPtr<SErrorText> ErrorText;
	TArray<FString> AdditionalNodeInfo_LinesArray;

public:

	UPZ_SkillTreeEdNode_Base* EdBaseNode = nullptr;

};
