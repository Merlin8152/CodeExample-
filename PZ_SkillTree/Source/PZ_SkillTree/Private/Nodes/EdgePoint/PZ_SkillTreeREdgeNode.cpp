// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/EdgePoint/PZ_SkillTreeREdgeNode.h"




bool UPZ_SkillTreeREdgeNode::OnExecute(UPZ_SkillTreeContext* SkillTreeContext)
{
	if (!SkillTreeContext) return false;

	return AlwaysTrue;
}