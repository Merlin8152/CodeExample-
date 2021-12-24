// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/ConditionNode/PZ_SkillTreeRConditionNode.h"

#include "PZ_SkillTreeContext.h"



UPZ_SkillTreeRConditionNode::UPZ_SkillTreeRConditionNode()
{

}



bool UPZ_SkillTreeRConditionNode::OnExecute(UPZ_SkillTreeContext* SkillTreeContext)
{
	if (!SkillTreeContext) return false;


	return SkillTreeContext->ExecuteCondition(SendConditionEvents);
}
