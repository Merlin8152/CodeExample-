// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode/PZ_SkillTreeUIPositionSNode_Base.h"


class UPZ_SkillTreeUIPositionEdNode_UI;
class UPZ_SkillTreeRUINode;


class SPZ_SkillTreeUIPositionSNode_UI: public SPZ_SkillTreeUIPositionSNode_Base
{

	typedef SPZ_SkillTreeUIPositionSNode_Base Super;
	typedef SPZ_SkillTreeUIPositionSNode_UI Self;


public:

	SLATE_BEGIN_ARGS(SPZ_SkillTreeUIPositionSNode_UI) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UPZ_SkillTreeUIPositionEdNode_UI* InNode);



	virtual void GetAdditionalNodeInfo(TArray<FString>& AdditionalInfoArray) override;


	virtual FText GetNodeName() const override;
	virtual FLinearColor GetNodeTitleColor()  const override;

	virtual const FSlateBrush* GetNodeImage()  const override;
	virtual const EVisibility GetTopPinsBoxVisibility() const override;



	virtual void MoveTo(const FVector2D& NewPosition, FNodeSet& NodeFilter) override;

	virtual FLinearColor GetNodeBackgroundColor_Default() const override;

protected:


public:

	UPZ_SkillTreeUIPositionEdNode_UI* EdUINode = nullptr;
	UPZ_SkillTreeRUINode* RUINode = nullptr;



};
