// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillNode/PZ_SkillTreeSNode_Skill.h"


class UPZ_SkillTreeEdNode_PassiveSkill;
class UPZ_SkillTreeRPassiveSkillNode;


class SPZ_SkillTreeSNode_PassiveSkill: public SPZ_SkillTreeSNode_Skill
{

	typedef SPZ_SkillTreeSNode_PassiveSkill Super;
	typedef SPZ_SkillTreeSNode_PassiveSkill Self;


public:

	SLATE_BEGIN_ARGS(SPZ_SkillTreeSNode_PassiveSkill) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UPZ_SkillTreeEdNode_PassiveSkill* InNode);



	virtual FText GetNodeName() const override;
	virtual FLinearColor GetNodeTitleColor()  const override;
	virtual FLinearColor GetNodeBackgroundColor_Default() const override;
	virtual const FSlateBrush* GetNodeImage()  const override;



public:

	UPZ_SkillTreeEdNode_PassiveSkill* EdPassiveSkillNode = nullptr;
	UPZ_SkillTreeRPassiveSkillNode* RPassiveSkillNode = nullptr;

};
