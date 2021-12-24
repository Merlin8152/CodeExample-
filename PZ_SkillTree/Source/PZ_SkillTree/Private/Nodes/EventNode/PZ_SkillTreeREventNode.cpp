// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/EventNode/PZ_SkillTreeREventNode.h"

#include "PZ_SkillTreeContext.h"



UPZ_SkillTreeREventNode::UPZ_SkillTreeREventNode()
{

}



bool UPZ_SkillTreeREventNode::OnExecute(UPZ_SkillTreeContext* SkillTreeContext)
{
	if (!SkillTreeContext) return false;


	return true;
}
