// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/SkillActionNode/PZ_SkillTreeRSkillActionNode.h"

#include "PZ_SkillTreeContext.h"



UPZ_SkillTreeRSkillActionNode::UPZ_SkillTreeRSkillActionNode()
{

}



bool UPZ_SkillTreeRSkillActionNode::OnExecute(UPZ_SkillTreeContext* SkillTreeContext)
{
	if (!SkillTreeContext) return false;

	SkillTreeContext->ExecuteEvents(SendEvents);

	return true;
}