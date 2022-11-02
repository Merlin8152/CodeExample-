// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/LayerNode/PZ_SkillTreeRLayerNode.h"

#include "PZ_SkillTreeContext.h"



UPZ_SkillTreeRLayerNode::UPZ_SkillTreeRLayerNode()
{

}



bool UPZ_SkillTreeRLayerNode::OnExecute(UPZ_SkillTreeContext* SkillTreeContext)
{
	if (!SkillTreeContext) return false;


	return nullptr; /*SkillTreeContext->ExecuteCondition(SendConditionEvents);*/
}
