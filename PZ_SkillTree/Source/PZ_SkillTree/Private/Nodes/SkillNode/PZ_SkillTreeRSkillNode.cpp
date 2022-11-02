// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/SkillNode/PZ_SkillTreeRSkillNode.h"

//#include "Nodes/ConditionNode/PZ_SkillTreeRConditionNode.h"
//#include "Nodes/SkillActionNode/PZ_SkillTreeRSkillActionNode.h"
#include "Nodes/LayerNode/PZ_SkillTreeRLayerNode.h"

#include "SkillTreeContextItems/PZ_SkillTreeContextItem_Skill.h"

#include "PZ_SkillTreeContext.h"



UPZ_SkillTreeRSkillNode::UPZ_SkillTreeRSkillNode()
{

}



bool UPZ_SkillTreeRSkillNode::OnExecute(UPZ_SkillTreeContext* SkillTreeContext)
{
	return false;
}

UPZ_SkillTreeContextItem_Base* UPZ_SkillTreeRSkillNode::CreateContext(UPZ_SkillTreeContext* SkillTreeContext)
{
	UPZ_SkillTreeContextItem_Skill* SkillContext = NewObject<UPZ_SkillTreeContextItem_Skill>(SkillTreeContext, UPZ_SkillTreeContextItem_Skill::StaticClass());
	SkillContext->IsOpen = AlwaysCanBeOpen;
	SkillContext->SkillTreeNode = this;

	return SkillContext;
}
