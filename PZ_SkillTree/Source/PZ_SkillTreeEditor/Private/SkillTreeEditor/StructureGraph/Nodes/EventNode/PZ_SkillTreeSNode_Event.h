// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode/PZ_SkillTreeSNode_Base.h"


class UPZ_SkillTreeEdNode_Event;
class UPZ_SkillTreeREventNode;


class SPZ_SkillTreeSNode_Event: public SPZ_SkillTreeSNode_Base
{

	typedef SPZ_SkillTreeSNode_Event Super;
	typedef SPZ_SkillTreeSNode_Event Self;


public:

	SLATE_BEGIN_ARGS(SPZ_SkillTreeSNode_Event) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UPZ_SkillTreeEdNode_Event* InNode);


	virtual void GetAdditionalNodeInfo(TArray<FString>& AdditionalInfoArray) override;

	virtual FText GetNodeName() const override;
	virtual FLinearColor GetNodeTitleColor()  const override;
	virtual FLinearColor GetNodeBackgroundColor_Default() const override;

	virtual const FSlateBrush* GetBackgroundImage()  const override;

	virtual const float GetNodeBodyPadding() const override;
	virtual const FSlateBrush* GetNodeImage() const override;
public:

	UPZ_SkillTreeEdNode_Event* EdEventNode = nullptr;
	UPZ_SkillTreeREventNode* REventNode = nullptr;

};
