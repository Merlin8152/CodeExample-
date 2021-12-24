// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode/PZ_SkillTreeSNode_Base.h"


class UPZ_SkillTreeEdNode_Condition;
class UPZ_SkillTreeRConditionNode;


class SPZ_SkillTreeSNode_Condition : public SPZ_SkillTreeSNode_Base
{

	typedef SPZ_SkillTreeSNode_Condition Super;
	typedef SPZ_SkillTreeSNode_Condition Self;


public:

	SLATE_BEGIN_ARGS(SPZ_SkillTreeSNode_Condition) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UPZ_SkillTreeEdNode_Condition* InNode);


	virtual void GetAdditionalNodeInfo(TArray<FString>& AdditionalInfoArray) override;


	virtual FText GetNodeName() const override;
	virtual FLinearColor GetNodeTitleColor()  const override;

	virtual const FSlateBrush* GetBackgroundImage()  const override;
	virtual const FSlateBrush* GetNodeImage()  const override;

	virtual const float GetNodeBodyPadding() const override;

public:

	UPZ_SkillTreeEdNode_Condition* EdConditionNode = nullptr;
	UPZ_SkillTreeRConditionNode* RConditionNode = nullptr;

};
