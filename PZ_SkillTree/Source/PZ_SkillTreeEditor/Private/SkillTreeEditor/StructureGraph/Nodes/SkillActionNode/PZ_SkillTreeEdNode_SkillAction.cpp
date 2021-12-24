// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeEditor/StructureGraph/Nodes/SkillActionNode/PZ_SkillTreeEdNode_SkillAction.h"

#include "SkillTreeEditor/PZ_SkillTreeEditorConstant.h"

UPZ_SkillTreeEdNode_SkillAction::UPZ_SkillTreeEdNode_SkillAction()
{
	bCanRenameNode = false;
}



void UPZ_SkillTreeEdNode_SkillAction::AllocateDefaultPins()
{
	// NO PINS
}




bool UPZ_SkillTreeEdNode_SkillAction::CanDuplicateNode() const
{
	return true;
}

bool UPZ_SkillTreeEdNode_SkillAction::CanUserDeleteNode() const
{
	return true;
}





ESkillTreeNodeType UPZ_SkillTreeEdNode_SkillAction::GetNodeType() const
{
	return ESkillTreeNodeType::SkillActionNode;
}







void UPZ_SkillTreeEdNode_SkillAction::OnNodeDoubleClicked()
{
	// TODO....
}

void UPZ_SkillTreeEdNode_SkillAction::OnChangedProperties(const FName& PropertyName) const
{
	Super::OnChangedProperties(PropertyName);

	// TODO....
}