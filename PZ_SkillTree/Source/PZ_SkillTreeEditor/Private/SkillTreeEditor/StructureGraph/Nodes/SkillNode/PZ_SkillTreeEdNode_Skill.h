// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode/PZ_SkillTreeEdNode_Base.h"
#include "PZ_SkillTreeEdNode_Skill.generated.h"



UCLASS()
class UPZ_SkillTreeEdNode_Skill : public UPZ_SkillTreeEdNode_Base
{
	GENERATED_BODY()

//Constructor
public:

	UPZ_SkillTreeEdNode_Skill();


	UPROPERTY()
		UPZ_SkillTreeEdNode_Base* Conditions;

	UPROPERTY()
		UPZ_SkillTreeEdNode_Base* UnlockAction;

//c++ public Methods
public:
	virtual void AllocateDefaultPins() override;

	virtual bool CanDuplicateNode() const override;
	virtual bool CanUserDeleteNode() const override;


	virtual bool IsHaveUINode() const override;

	virtual ESkillTreeNodeType GetNodeType() const override;

	virtual void CompileThisNodeInfo(UPZ_SkillTree_Editor* SkillTree) override;
	virtual void CompileError(UPZ_SkillTree_Editor* SkillTree) override;

	virtual void OnNodeDoubleClicked() override;
	virtual void OnChangedProperties(const FName& PropertyName) const override;
	

	virtual void OnSubNodeAdded(UPZ_SkillTreeEdNode_Base* SubNode) override;
	virtual void OnSubNodeRemoved(UPZ_SkillTreeEdNode_Base* SubNode) override;
	virtual void RemoveAllSubNodes() override;
	/** Gets a list of actions that can be done to this particular node */
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;


	virtual bool CanContainsSubNode(UClass* SubNodeClass) override;

	virtual void PostPlacedNewNode() override;

protected:

	void CreateAddUnlockEventsSubMenu(class UToolMenu* Menu, UEdGraph* Graph) const;
	void CreateAddConditionSubMenu(class UToolMenu* Menu, UEdGraph* Graph) const;


};
