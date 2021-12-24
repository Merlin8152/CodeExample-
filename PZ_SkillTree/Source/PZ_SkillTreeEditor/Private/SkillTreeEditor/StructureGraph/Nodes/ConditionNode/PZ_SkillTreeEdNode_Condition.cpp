// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeEditor/StructureGraph/Nodes/ConditionNode/PZ_SkillTreeEdNode_Condition.h"

#include "SkillTreeEditor/PZ_SkillTreeEditorConstant.h"




UPZ_SkillTreeEdNode_Condition::UPZ_SkillTreeEdNode_Condition()
{
	bCanRenameNode = false;
}



void UPZ_SkillTreeEdNode_Condition::AllocateDefaultPins()
{
	// NO PINS
}




bool UPZ_SkillTreeEdNode_Condition::CanDuplicateNode() const
{
	return true;
}

bool UPZ_SkillTreeEdNode_Condition::CanUserDeleteNode() const
{
	return true;
}





ESkillTreeNodeType UPZ_SkillTreeEdNode_Condition::GetNodeType() const
{
	return ESkillTreeNodeType::ConditionSkillNode;
}





void UPZ_SkillTreeEdNode_Condition::OnNodeDoubleClicked()
{
	// TODO....
}

void UPZ_SkillTreeEdNode_Condition::OnChangedProperties(const FName& PropertyName) const
{
	Super::OnChangedProperties(PropertyName);

	// TODO....
}