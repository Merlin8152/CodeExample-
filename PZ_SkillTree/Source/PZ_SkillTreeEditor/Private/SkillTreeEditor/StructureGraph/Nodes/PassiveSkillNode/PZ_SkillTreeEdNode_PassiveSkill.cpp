// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeEditor/StructureGraph/Nodes/PassiveSkillNode/PZ_SkillTreeEdNode_PassiveSkill.h"


UPZ_SkillTreeEdNode_PassiveSkill::UPZ_SkillTreeEdNode_PassiveSkill()
{
	bCanRenameNode = false;
}





bool UPZ_SkillTreeEdNode_PassiveSkill::CanDuplicateNode() const
{
	return Super::CanDuplicateNode();
}

bool UPZ_SkillTreeEdNode_PassiveSkill::CanUserDeleteNode() const
{
	return true;
}





ESkillTreeNodeType UPZ_SkillTreeEdNode_PassiveSkill::GetNodeType() const
{
	return ESkillTreeNodeType::PassiveSkillNode;
}





void UPZ_SkillTreeEdNode_PassiveSkill::OnNodeDoubleClicked()
{
	// TODO....
}

void UPZ_SkillTreeEdNode_PassiveSkill::OnChangedProperties(const FName& PropertyName) const
{
	Super::OnChangedProperties(PropertyName);

	// TODO....
}
