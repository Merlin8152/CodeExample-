// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTreeNodesFactory.h"

#include "../Graph/PZ_SkillTreeStructureEdGraphSchema.h"


#include "PZ_SSkillTreeGraphPin.h"

#include"../PZ_EdNodesInclude.h"
#include "../PZ_SNodesInclude.h"



TSharedPtr<class SGraphNode> FPZ_SkillTreeGraphNodeFactory::CreateNode(UEdGraphNode* InNode) const
{
	if (UPZ_SkillTreeEdNode_Base* LNodeBase = Cast<UPZ_SkillTreeEdNode_Base>(InNode))
	{

		if (UPZ_SkillTreeEdNode_ActiveSkill* LNodeActiveSkill = Cast<UPZ_SkillTreeEdNode_ActiveSkill>(LNodeBase))
		{
			return SNew(SPZ_SkillTreeSNode_ActiveSkill, LNodeActiveSkill);
		}

		if (UPZ_SkillTreeEdNode_PassiveSkill* LNodePassiveSkill = Cast<UPZ_SkillTreeEdNode_PassiveSkill>(LNodeBase))
		{
			return SNew(SPZ_SkillTreeSNode_PassiveSkill, LNodePassiveSkill);
		}


		if (UPZ_SkillTreeEdNode_Event* LNodeEvent = Cast<UPZ_SkillTreeEdNode_Event>(LNodeBase))
		{
			return SNew(SPZ_SkillTreeSNode_Event, LNodeEvent);
		}

		if (UPZ_SkillTreeEdNode_SkillAction* LNodeSkillAction = Cast<UPZ_SkillTreeEdNode_SkillAction>(LNodeBase))
		{
			return SNew(SPZ_SkillTreeSNode_SkillAction, LNodeSkillAction);
		}

		if (UPZ_SkillTreeEdNode_Condition* LNodeCondition = Cast<UPZ_SkillTreeEdNode_Condition>(LNodeBase))
		{
			return SNew(SPZ_SkillTreeSNode_Condition, LNodeCondition);
		}

		if (UPZ_SkillTreeEdNode_Switcher* LNodeSwitcher = Cast<UPZ_SkillTreeEdNode_Switcher>(LNodeBase))
		{
			return SNew(SPZ_SkillTreeSNode_Switcher, LNodeSwitcher);
		}

		if (UPZ_SkillTreeEdNode_Custom* LNodeCustom = Cast<UPZ_SkillTreeEdNode_Custom>(LNodeBase))
		{
			return SNew(SPZ_SkillTreeSNode_Custom, LNodeCustom);
		}

		if (UPZ_SkillTreeEdNode_Connection* LNodeConnection = Cast<UPZ_SkillTreeEdNode_Connection>(LNodeBase))
		{
			return SNew(SPZ_SkillTreeSNode_Connection, LNodeConnection);
		}

		return SNew(SPZ_SkillTreeSNode_Base, LNodeBase);

	}
	else
	if (UPZ_SkillTreeEdNode_Edge* LNodeEdge = Cast<UPZ_SkillTreeEdNode_Edge>(InNode))
	{
		return SNew(SPZ_SkillTreeSNode_Edge, LNodeEdge);
	}

	return nullptr;
}






TSharedPtr<class SGraphPin> FPZ_SkillTreeGraphPinFactory::CreatePin(UEdGraphPin* Pin) const
{
	if (Pin->GetSchema()->IsA<UPZ_SkillTreeEdGraphSchema>())
	{
		return SNew(SPZ_SSkillTreeGraphPin, Pin);
	}

	return nullptr;
}
