// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeEditor/StructureGraph/Nodes/ActiveSkillNode/PZ_SkillTreeEdNode_ActiveSkill.h"




UPZ_SkillTreeEdNode_ActiveSkill::UPZ_SkillTreeEdNode_ActiveSkill()
{
	bCanRenameNode = false;
}





bool UPZ_SkillTreeEdNode_ActiveSkill::CanDuplicateNode() const
{
	return true;
}

bool UPZ_SkillTreeEdNode_ActiveSkill::CanUserDeleteNode() const
{
	return Super::CanUserDeleteNode();
}





ESkillTreeNodeType UPZ_SkillTreeEdNode_ActiveSkill::GetNodeType() const
{
	return ESkillTreeNodeType::ActiveSkillNode;
}



void UPZ_SkillTreeEdNode_ActiveSkill::OnNodeDoubleClicked()
{
	// TODO....
}

void UPZ_SkillTreeEdNode_ActiveSkill::OnChangedProperties(const FName& PropertyName) const
{
	Super::OnChangedProperties(PropertyName);

	// TODO....
}
