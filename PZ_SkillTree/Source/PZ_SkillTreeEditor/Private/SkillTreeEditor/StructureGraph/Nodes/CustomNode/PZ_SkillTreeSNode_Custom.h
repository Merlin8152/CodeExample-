// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode/PZ_SkillTreeSNode_Base.h"


class UPZ_SkillTreeEdNode_Custom;
class UPZ_SkillTreeRCustomNode;


class SPZ_SkillTreeSNode_Custom : public SPZ_SkillTreeSNode_Base
{
	typedef SPZ_SkillTreeSNode_Base Super;
	typedef SPZ_SkillTreeSNode_Custom Self;
public:

	SLATE_BEGIN_ARGS(SPZ_SkillTreeSNode_Custom) {}
	SLATE_END_ARGS()

		void Construct(const FArguments& InArgs, UPZ_SkillTreeEdNode_Custom* InNode);


	virtual void GetAdditionalNodeInfo(TArray<FString>& AdditionalInfoArray) override;


	virtual FText GetNodeName() const override;
	virtual FLinearColor GetNodeTitleColor()  const override;
	virtual FLinearColor GetNodeBackgroundColor_Default() const override;

	virtual const FSlateBrush* GetNodeImage()  const override;
	virtual const EVisibility GetTopPinsBoxVisibility() const override;





	virtual void MoveTo(const FVector2D& NewPosition, FNodeSet& NodeFilter) override;
protected:


public:

	UPZ_SkillTreeEdNode_Custom* EdCustomNode = nullptr;
	UPZ_SkillTreeRCustomNode* RCustomNode = nullptr;

};
