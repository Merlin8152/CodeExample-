// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../BaseNode/PZ_SkillTreeEdNode_Base.h"

#include "PZ_SkillTreeEdNode_SkillAction.generated.h"

/**
 * 
 */
UCLASS()
class UPZ_SkillTreeEdNode_SkillAction : public UPZ_SkillTreeEdNode_Base
{
	GENERATED_BODY()

//Constructor
public:

	UPZ_SkillTreeEdNode_SkillAction();



//c++ public Methods
public:
	virtual void AllocateDefaultPins() override;

	virtual bool CanDuplicateNode() const override;
	virtual bool CanUserDeleteNode() const override;


	virtual ESkillTreeNodeType GetNodeType() const override;



	virtual void OnNodeDoubleClicked() override;
	virtual void OnChangedProperties(const FName& PropertyName) const override;
	
};





