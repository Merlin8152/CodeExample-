// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeEditor/StructureGraph/Nodes/SwitcherNode/PZ_SkillTreeEdNode_Switcher.h"



UPZ_SkillTreeEdNode_Switcher::UPZ_SkillTreeEdNode_Switcher()
{
	bCanRenameNode = false;
}





bool UPZ_SkillTreeEdNode_Switcher::CanDuplicateNode() const
{
	return true;
}

bool UPZ_SkillTreeEdNode_Switcher::CanUserDeleteNode() const
{
	return true;
}





ESkillTreeNodeType UPZ_SkillTreeEdNode_Switcher::GetNodeType() const
{
	return ESkillTreeNodeType::SwitcherNode;
}






void UPZ_SkillTreeEdNode_Switcher::OnNodeDoubleClicked()
{
	// TODO....
}

void UPZ_SkillTreeEdNode_Switcher::OnChangedProperties(const FName& PropertyName) const
{
	Super::OnChangedProperties(PropertyName);

	// TODO....
}
