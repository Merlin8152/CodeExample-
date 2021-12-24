// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode/PZ_SkillTreeEdNode_Base.h"
#include "PZ_SkillTreeEdNode_Custom.generated.h"



UCLASS()
class UPZ_SkillTreeEdNode_Custom : public UPZ_SkillTreeEdNode_Base
{
	GENERATED_BODY()

//Constructor
public:

	UPZ_SkillTreeEdNode_Custom();


//c++ public Methods
public:
	virtual void AllocateDefaultPins() override;

	virtual bool IsHaveUINode() const override;

	virtual bool CanDuplicateNode() const override;
	virtual bool CanUserDeleteNode() const override;


	virtual ESkillTreeNodeType GetNodeType() const override;

	virtual void CompileThisNodeInfo(UPZ_SkillTree_Editor* SkillTree) override;
	virtual void CompileError(UPZ_SkillTree_Editor* SkillTree) override;

	virtual void OnNodeDoubleClicked() override;
	virtual void OnChangedProperties(const FName& PropertyName) const override;



	virtual bool CanContainsSubNode(UClass* SubNodeClass) override;

	virtual void PostPlacedNewNode() override;

protected:




};
