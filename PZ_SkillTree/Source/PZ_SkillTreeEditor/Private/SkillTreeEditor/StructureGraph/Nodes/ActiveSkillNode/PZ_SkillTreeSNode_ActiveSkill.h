// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillNode/PZ_SkillTreeSNode_Skill.h"


class UPZ_SkillTreeEdNode_ActiveSkill;
class UPZ_SkillTreeRActiveSkillNode;


class SPZ_SkillTreeSNode_ActiveSkill: public SPZ_SkillTreeSNode_Skill
{

	typedef SPZ_SkillTreeSNode_ActiveSkill Super;
	typedef SPZ_SkillTreeSNode_ActiveSkill Self;


public:

	SLATE_BEGIN_ARGS(SPZ_SkillTreeSNode_ActiveSkill) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UPZ_SkillTreeEdNode_ActiveSkill* InNode);


	virtual void GetAdditionalNodeInfo(TArray<FString>& AdditionalInfoArray) override;


	virtual FText GetNodeName() const override;
	virtual FLinearColor GetNodeTitleColor()  const override;
	virtual FLinearColor GetNodeBackgroundColor_Default() const override;
	virtual const FSlateBrush* GetBackgroundImage()  const override;
	virtual const FSlateBrush* GetNodeImage()  const override;


public:

	UPZ_SkillTreeEdNode_ActiveSkill* EdActiveSkillNode = nullptr;
	UPZ_SkillTreeRActiveSkillNode* RActiveSkillNode = nullptr;

};
