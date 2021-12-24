// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/PassiveSkillNode/PZ_SkillTreeRPassiveSkillNode.h"

#include "Curves/CurveFloat.h"

#include "PZ_SkillTreeContext.h"



UPZ_SkillTreeRPassiveSkillNode::UPZ_SkillTreeRPassiveSkillNode()
{

}



bool UPZ_SkillTreeRPassiveSkillNode::OnExecute(UPZ_SkillTreeContext* SkillTreeContext)
{
	if (!SkillTreeContext) return false;

	return false;
}