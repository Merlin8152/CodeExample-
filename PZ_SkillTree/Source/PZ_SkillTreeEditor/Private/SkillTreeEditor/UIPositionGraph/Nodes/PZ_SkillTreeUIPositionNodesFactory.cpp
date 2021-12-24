// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTreeUIPositionNodesFactory.h"

#include "../Graph/PZ_SkillTreeUIPositionEdGraphSchema.h"


#include "PZ_SSkillTreeUIPositionGraphPin.h"

#include"../Nodes/PZ_UIPositionEdNodesInclude.h"
#include "../Nodes/PZ_UIPositionSNodesInclude.h"



TSharedPtr<class SGraphNode> FPZ_SkillTreeUIPositionGraphNodeFactory::CreateNode(UEdGraphNode* InNode) const
{
	if (UPZ_SkillTreeUIPositionEdNode_Base* LNodeBase = Cast<UPZ_SkillTreeUIPositionEdNode_Base>(InNode))
	{

		if (UPZ_SkillTreeUIPositionEdNode_UI* LNodeUI = Cast<UPZ_SkillTreeUIPositionEdNode_UI>(LNodeBase))
		{
			return SNew(SPZ_SkillTreeUIPositionSNode_UI, LNodeUI);
		}


		return SNew(SPZ_SkillTreeUIPositionSNode_Base, LNodeBase);

	}

	return nullptr;
}






TSharedPtr<class SGraphPin> FPZ_SkillTreeUIPositionGraphPinFactory::CreatePin(UEdGraphPin* Pin) const
{
	if (Pin->GetSchema()->IsA<UPZ_SkillTreeUIPositionEdGraphSchema>())
	{
		return SNew(SPZ_SSkillTreeUIPositionGraphPin, Pin);
	}

	return nullptr;
}
