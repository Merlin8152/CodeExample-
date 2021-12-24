// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode/PZ_SkillTreeSNode_Base.h"


class UPZ_SkillTreeEdNode_Switcher;
class UPZ_SkillTreeRSwitcherNode;


class SPZ_SkillTreeSNode_Switcher: public SPZ_SkillTreeSNode_Base
{

	typedef SPZ_SkillTreeSNode_Switcher Super;
	typedef SPZ_SkillTreeSNode_Switcher Self;


public:

	SLATE_BEGIN_ARGS(SPZ_SkillTreeSNode_Switcher) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UPZ_SkillTreeEdNode_Switcher* InNode);



	virtual FText GetNodeName() const override;
	virtual FLinearColor GetNodeTitleColor()  const override;

	virtual FLinearColor GetNodeBackgroundColor_Default() const override;
	virtual const FSlateBrush* GetBackgroundImage()  const override;
	virtual const FSlateBrush* GetNodeImage()  const override;



public:

	UPZ_SkillTreeEdNode_Switcher* EdSwitcherNode = nullptr;
	UPZ_SkillTreeRSwitcherNode* RSwitcherNode = nullptr;

};
