// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/SwitcherNode/PZ_SkillTreeRSwitcherNode.h"

#include "Nodes/SkillNode/PZ_SkillTreeRSkillNode.h"
#include "Nodes/EdgePoint/PZ_SkillTreeREdgeNode.h"

#include "PZ_SkillTreeContext.h"



UPZ_SkillTreeRSwitcherNode::UPZ_SkillTreeRSwitcherNode()
{

}



bool UPZ_SkillTreeRSwitcherNode::OnExecute(UPZ_SkillTreeContext* SkillTreeContext)
{
	if (!SkillTreeContext) return false;

	return false;
}


