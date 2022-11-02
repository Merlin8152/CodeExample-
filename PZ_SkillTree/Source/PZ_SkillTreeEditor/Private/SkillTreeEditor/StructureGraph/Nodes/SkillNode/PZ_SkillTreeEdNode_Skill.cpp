// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeEditor/StructureGraph/Nodes/SkillNode/PZ_SkillTreeEdNode_Skill.h"
#include "SkillTreeEditor/StructureGraph/Nodes/SkillActionNode/PZ_SkillTreeEdNode_SkillAction.h"

#include "SkillTreeEditor/StructureGraph/Nodes/LayerNode/PZ_SkillTreeEdNode_Layer.h"

#include "SkillTreeEditor/StructureGraph/Nodes/BaseNode/PZ_SkillTreeSNode_Base.h"

#include "Nodes/SkillNode/PZ_SkillTreeRSkillNode.h"

#include "Nodes/LayerNode/PZ_SkillTreeRLayerNode.h"
#include "PZ_SkillTree_Editor.h"

#include "SkillTreeEditor/StructureGraph/Graph/PZ_SkillTreeStructureEdGraphSchema.h"
#include "ToolMenus.h"
#include "SkillTreeEditor/PZ_SkillTreeEditorConstant.h"
#include "SkillTreeEditor/StructureGraph/CustomWidgets/PZ_SkillTreeActionSubNodesMenu.h"

#define LOCTEXT_NAMESPACE "SkillTreeEditor"

UPZ_SkillTreeEdNode_Skill::UPZ_SkillTreeEdNode_Skill()
{
	bCanRenameNode = false;
}


void UPZ_SkillTreeEdNode_Skill::AllocateDefaultPins() 
{
	CreatePin(EGPD_Input, FPZ_SkillTreeEditorConstant::PinCategory_Main, FPZ_SkillTreeEditorConstant::PinSubCategory_TopBottom, TEXT("In"));
	CreatePin(EGPD_Output, FPZ_SkillTreeEditorConstant::PinCategory_Main, FPZ_SkillTreeEditorConstant::PinSubCategory_TopBottom, TEXT("Out"));

	CreatePin(EGPD_Input, FPZ_SkillTreeEditorConstant::PinCategory_Second, FPZ_SkillTreeEditorConstant::PinSubCategory_LeftRight, TEXT("In"));
}


bool UPZ_SkillTreeEdNode_Skill::CanDuplicateNode() const
{
	return true;
}

bool UPZ_SkillTreeEdNode_Skill::CanUserDeleteNode() const
{
	return true;
}





bool UPZ_SkillTreeEdNode_Skill::IsHaveUINode() const
{
	return true;
}

ESkillTreeNodeType UPZ_SkillTreeEdNode_Skill::GetNodeType() const
{
	return ESkillTreeNodeType::SkillNode;
}



void UPZ_SkillTreeEdNode_Skill::CompileThisNodeInfo(UPZ_SkillTree_Editor* SkillTree)
{
	Super::CompileThisNodeInfo(SkillTree);


	if (UPZ_SkillTreeRSkillNode* RSkillNode = Cast<UPZ_SkillTreeRSkillNode>(RNode))
	{
		RSkillNode->Layers.Empty();
		for (const auto& EdLayer: Layers)
		{
			if (UPZ_SkillTreeRLayerNode* RLayer = Cast<UPZ_SkillTreeRLayerNode>(EdLayer->RNode))
			{
				RSkillNode->Layers.Add(RLayer);
			}

			EdLayer->CompileThisNodeInfo(SkillTree);
				
		}
		
	}
}




void UPZ_SkillTreeEdNode_Skill::CompileError(UPZ_SkillTree_Editor* SkillTree)
{
	ErrorMsg = FString();


	if (auto RSkillNode = Cast<UPZ_SkillTreeRSkillNode>(RNode))
	{
		// TODO Place in layers
		//if (UnlockAction)
		//{

		//	if (auto ActionNode = Cast<UPZ_SkillTreeRSkillActionNode>(UnlockAction->RNode))
		//	{
		//		RSkillNode->SkillActionNode = ActionNode;

		//		if (ActionNode->SendEvents.Num() > 0)
		//		{
		//			if (!ActionNode->SendEvents[0])
		//			{
		//				ErrorMsg = FString("The Action must have valid value");

		//			}
		//		}
		//		else
		//		{
		//			ErrorMsg = FString("The Action must have  value");

		//		}
		//	}

		//}

		//if (Conditions)
		//{


		//	if (auto ConditionsNode = Cast<UPZ_SkillTreeRConditionNode>(Conditions->RNode))
		//	{

		//		RSkillNode->ConditionNode = ConditionsNode;

		//		if (ConditionsNode->SendConditionEvents.Num() > 0)
		//		{
		//			if (!ConditionsNode->SendConditionEvents[0])
		//			{
		//				ErrorMsg = FString("The Condition must have valid value");
		//			}

		//		}
		//		else
		//		{
		//			ErrorMsg = FString("The Condition must have value");
		//		}
		//	}

		//}

	}
}







void UPZ_SkillTreeEdNode_Skill::OnNodeDoubleClicked()
{
	// TODO....
}

void UPZ_SkillTreeEdNode_Skill::OnChangedProperties(const FName& PropertyName) const
{
	Super::OnChangedProperties(PropertyName);

	// TODO....
}



void UPZ_SkillTreeEdNode_Skill::OnSubNodeAdded(UPZ_SkillTreeEdNode_Base* NodeTemplate)
{
	if (UPZ_SkillTreeEdNode_Layer* STLayerNode = Cast<UPZ_SkillTreeEdNode_Layer>(NodeTemplate))
	{
		CurrentLayer = Layers.Add(STLayerNode);
	}

}


void UPZ_SkillTreeEdNode_Skill::OnSubNodeRemoved(UPZ_SkillTreeEdNode_Base* SubNode)
{

	if (Layers.Contains(SubNode))
	{
		Layers.Remove(SubNode);
		CurrentLayer--;

		if (CurrentLayer < 0) CurrentLayer = 0;
	}
}

void UPZ_SkillTreeEdNode_Skill::RemoveAllSubNodes()
{
	Super::RemoveAllSubNodes();
	Layers.Empty();
	CurrentLayer = 0;
}


void UPZ_SkillTreeEdNode_Skill::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{

	FToolMenuSection& Section = Menu->FindOrAddSection("SkillTreeSubNodes");


		Section.AddSubMenu(
			"AddLayer",
			LOCTEXT("AddLayer", "Add Layer..."), 
			LOCTEXT("AddLayerTooltip",
			"Adds new Layer as a subnode"),
			FNewToolMenuDelegate::CreateUObject(this, &UPZ_SkillTreeEdNode_Skill::CreateAddLayerSubMenu, (UEdGraph*)Context->Graph));
}

bool UPZ_SkillTreeEdNode_Skill::CanContainsSubNode(UClass* SubNodeClass)
{
	return (SubNodeClass->IsChildOf(UPZ_SkillTreeEdNode_Layer::StaticClass()));
}


void UPZ_SkillTreeEdNode_Skill::PostPlacedNewNode()
{
	if (UPZ_SkillTreeRSkillNode* SkillRNode = Cast<UPZ_SkillTreeRSkillNode>(RNode))
	{
		SkillRNode->TempUIPositionOnCompile = FVector2D(NodePosX, NodePosY);
	}
}

void UPZ_SkillTreeEdNode_Skill::SetLayer(int LayerIndex)
{
	CurrentLayer = LayerIndex;
	SEdNode->UpdateGraphNode();
}

void UPZ_SkillTreeEdNode_Skill::CreateAddUnlockEventsSubMenu(UToolMenu* Menu, UEdGraph* Graph) const
{
	TSharedRef<SPZ_SkillTreeActionSubNodesMenu> Widget =
		SNew(SPZ_SkillTreeActionSubNodesMenu)
		.GraphObj(Graph)
		.GraphNode((UPZ_SkillTreeEdNode_Base*)this)
		.NodeType(ESkillTreeNodeType::SkillActionNode)
		.AutoExpandActionMenu(true);

	FToolMenuSection& Section = Menu->FindOrAddSection("Section");
	Section.AddEntry(FToolMenuEntry::InitWidget("UnlockActionWidget", Widget, FText(), true));
}

void UPZ_SkillTreeEdNode_Skill::CreateAddConditionSubMenu(UToolMenu* Menu, UEdGraph* Graph) const
{
	TSharedRef<SPZ_SkillTreeActionSubNodesMenu> Widget =
		SNew(SPZ_SkillTreeActionSubNodesMenu)
		.GraphObj(Graph)
		.GraphNode((UPZ_SkillTreeEdNode_Base*)this)
		.NodeType(ESkillTreeNodeType::ConditionSkillNode)
		.AutoExpandActionMenu(true);

	FToolMenuSection& Section = Menu->FindOrAddSection("Section");
	Section.AddEntry(FToolMenuEntry::InitWidget("ConditionWidget", Widget, FText(), true));
}

void UPZ_SkillTreeEdNode_Skill::CreateAddLayerSubMenu(UToolMenu* Menu, UEdGraph* Graph) const
{
	TSharedRef<SPZ_SkillTreeActionSubNodesMenu> Widget =
		SNew(SPZ_SkillTreeActionSubNodesMenu).
		GraphObj(Graph).
		GraphNode((UPZ_SkillTreeEdNode_Base*)this).
		NodeType(ESkillTreeNodeType::LayerNode).
		AutoExpandActionMenu(true);

	FToolMenuSection& Section = Menu->FindOrAddSection("Section");
	Section.AddEntry(FToolMenuEntry::InitWidget("Layer", Widget, FText(), true));
}

