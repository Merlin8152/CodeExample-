// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillTreeEditor/StructureGraph/Nodes/SkillNode/PZ_SkillTreeEdNode_Skill.h"

#include "PZ_SkillTreeEdNode_PassiveSkill.generated.h"

/**
 * 
 */
UCLASS()
class UPZ_SkillTreeEdNode_PassiveSkill : public UPZ_SkillTreeEdNode_Skill
{
	GENERATED_BODY()

//Constructor
public:

	UPZ_SkillTreeEdNode_PassiveSkill();



//c++ public Methods
public:

	virtual bool CanDuplicateNode() const override;
	virtual bool CanUserDeleteNode() const override;


	virtual ESkillTreeNodeType GetNodeType() const override;


	virtual void OnNodeDoubleClicked() override;
	virtual void OnChangedProperties(const FName& PropertyName) const override;

};
