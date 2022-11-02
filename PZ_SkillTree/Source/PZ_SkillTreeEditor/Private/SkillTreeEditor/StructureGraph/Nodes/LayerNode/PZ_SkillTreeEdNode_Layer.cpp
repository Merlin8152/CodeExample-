// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeEditor/StructureGraph/Nodes/LayerNode/PZ_SkillTreeEdNode_Layer.h"

#include "SkillTreeEditor/StructureGraph/Nodes/SkillActionNode/PZ_SkillTreeEdNode_SkillAction.h"
#include "SkillTreeEditor/StructureGraph/Nodes/ConditionNode/PZ_SkillTreeEdNode_Condition.h"

#include "Nodes/LayerNode/PZ_SkillTreeRLayerNode.h"
#include "Nodes/SkillActionNode/PZ_SkillTreeRSkillActionNode.h"
#include "Nodes/ConditionNode/PZ_SkillTreeRConditionNode.h"

#include "SkillTreeEditor/StructureGraph/Graph/PZ_SkillTreeStructureEdGraphSchema.h"
#include "ToolMenus.h"

#include "SkillTreeEditor/StructureGraph/CustomWidgets/PZ_SkillTreeActionSubNodesMenu.h"

#include "SkillTreeEditor/PZ_SkillTreeEditorConstant.h"


#define LOCTEXT_NAMESPACE "SkillTreeEditor"

UPZ_SkillTreeEdNode_Layer::UPZ_SkillTreeEdNode_Layer()
{
	bCanRenameNode = false;
}



void UPZ_SkillTreeEdNode_Layer::AllocateDefaultPins()
{
	// NO PINS
}




bool UPZ_SkillTreeEdNode_Layer::CanDuplicateNode() const
{
	return true;
}

bool UPZ_SkillTreeEdNode_Layer::CanUserDeleteNode() const
{
	return true;
}





ESkillTreeNodeType UPZ_SkillTreeEdNode_Layer::GetNodeType() const
{
	return ESkillTreeNodeType::LayerNode;
}

void UPZ_SkillTreeEdNode_Layer::CompileThisNodeInfo(UPZ_SkillTree_Editor* SkillTree)
{
	if (UPZ_SkillTreeRLayerNode* RLayer = Cast<UPZ_SkillTreeRLayerNode>(RNode))
	{
		RNode->ResetNavigationNode();
		RNode->NodeType = GetNodeType();
		RNode->Rename(nullptr, SkillTree, REN_DontCreateRedirectors | REN_DoNotDirty);

		RLayer->ConditionNode = nullptr;
		RLayer->SkillActionNode = nullptr;
		if (Conditions)	RLayer->ConditionNode = Cast<UPZ_SkillTreeRConditionNode>(Conditions->RNode);
		if( UnlockAction )
		{
			RLayer->SkillActionNode = Cast<UPZ_SkillTreeRSkillActionNode>(UnlockAction->RNode);
			UnlockAction->CompileThisNodeInfo(SkillTree);
		}
	}
}





void UPZ_SkillTreeEdNode_Layer::OnNodeDoubleClicked()
{
	// TODO....
}

void UPZ_SkillTreeEdNode_Layer::OnChangedProperties(const FName& PropertyName) const
{
	Super::OnChangedProperties(PropertyName);

	// TODO....
}





void UPZ_SkillTreeEdNode_Layer::OnSubNodeAdded(UPZ_SkillTreeEdNode_Base* NodeTemplate)
{
	if (UPZ_SkillTreeEdNode_SkillAction* STSkillActionNode = Cast<UPZ_SkillTreeEdNode_SkillAction>(NodeTemplate))
	{
		UnlockAction = STSkillActionNode;
	}
	else if (UPZ_SkillTreeEdNode_Condition* STConditionNode = Cast<UPZ_SkillTreeEdNode_Condition>(NodeTemplate))
	{
		Conditions = STConditionNode;
	}
}


void UPZ_SkillTreeEdNode_Layer::OnSubNodeRemoved(UPZ_SkillTreeEdNode_Base* SubNode)
{

	if (UnlockAction == SubNode)
	{
		UnlockAction = nullptr;
	}
	else if (Conditions == SubNode)
	{
		Conditions = nullptr;
	}
}

void UPZ_SkillTreeEdNode_Layer::RemoveAllSubNodes()
{
	Super::RemoveAllSubNodes();
	UnlockAction = nullptr;
	Conditions = nullptr;
}


void UPZ_SkillTreeEdNode_Layer::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{

	FToolMenuSection& Section = Menu->FindOrAddSection("SkillTreeSubNodes");

	if (!Conditions)
	{
		Section.AddSubMenu("AddCondition", LOCTEXT("AddCondition", "Add Condition..."), LOCTEXT("AddConditionTooltip", "Adds new condition as a subnode"),
			FNewToolMenuDelegate::CreateUObject(this, &UPZ_SkillTreeEdNode_Layer::CreateAddConditionSubMenu, (UEdGraph*)Context->Graph));
	}

	if (!UnlockAction)
	{
		Section.AddSubMenu("AddUnlockEvent", LOCTEXT("AddUnlockAction", "Add UnlockAction..."), LOCTEXT("AddUnlockActionTooltip", "Adds new UnlockAction as a subnode"),
			FNewToolMenuDelegate::CreateUObject(this, &UPZ_SkillTreeEdNode_Layer::CreateAddUnlockEventsSubMenu, (UEdGraph*)Context->Graph));
	}

}

bool UPZ_SkillTreeEdNode_Layer::CanContainsSubNode(UClass* SubNodeClass)
{
	return (SubNodeClass->IsChildOf(UPZ_SkillTreeEdNode_Condition::StaticClass()) && !Conditions) || (SubNodeClass->IsChildOf(UPZ_SkillTreeEdNode_SkillAction::StaticClass()) && !UnlockAction) ||
		   (SubNodeClass->IsChildOf(UPZ_SkillTreeEdNode_Layer::StaticClass()) && !UnlockAction);
}


void UPZ_SkillTreeEdNode_Layer::CreateAddUnlockEventsSubMenu(UToolMenu* Menu, UEdGraph* Graph) const
{
	TSharedRef<SPZ_SkillTreeActionSubNodesMenu> Widget =
		SNew(SPZ_SkillTreeActionSubNodesMenu).GraphObj(Graph).GraphNode((UPZ_SkillTreeEdNode_Base*)this).NodeType(ESkillTreeNodeType::SkillActionNode).AutoExpandActionMenu(true);

	FToolMenuSection& Section = Menu->FindOrAddSection("Section");
	Section.AddEntry(FToolMenuEntry::InitWidget("UnlockActionWidget", Widget, FText(), true));
}

void UPZ_SkillTreeEdNode_Layer::CreateAddConditionSubMenu(UToolMenu* Menu, UEdGraph* Graph) const
{
	TSharedRef<SPZ_SkillTreeActionSubNodesMenu> Widget =
		SNew(SPZ_SkillTreeActionSubNodesMenu).GraphObj(Graph).GraphNode((UPZ_SkillTreeEdNode_Base*)this).NodeType(ESkillTreeNodeType::ConditionSkillNode).AutoExpandActionMenu(true);

	FToolMenuSection& Section = Menu->FindOrAddSection("Section");
	Section.AddEntry(FToolMenuEntry::InitWidget("ConditionWidget", Widget, FText(), true));
}