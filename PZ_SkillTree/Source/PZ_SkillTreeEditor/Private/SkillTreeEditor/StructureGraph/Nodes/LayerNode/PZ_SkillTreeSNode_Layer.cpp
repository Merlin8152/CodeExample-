// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTreeSNode_Layer.h"
#include "PZ_SkillTreeEdNode_Layer.h"
#include "Nodes/LayerNode/PZ_SkillTreeRLayerNode.h"
#include "SkillTreeEvent/PZ_SkillTreeCondition.h"

#include "NodeFactory.h"

#include "EditorStyleSet.h"
#include "../../../PZ_SkillTreeEditorStyle.h"


#include "SGraphPanel.h"

void SPZ_SkillTreeSNode_Layer::Construct(const FArguments& InArgs, UPZ_SkillTreeEdNode_Layer* InNode)
{

	GraphNode = InNode;
	InNode->SEdNode = this;
	EdBaseNode = InNode;
	EdLayerNode = InNode;
	RLayerNode = Cast<UPZ_SkillTreeRLayerNode>(InNode->RNode);

	this->SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}




void SPZ_SkillTreeSNode_Layer::UpdateGraphNode_ResetStage()
{
	if (ConditionsBox.IsValid())
	{
		ConditionsBox->ClearChildren();
	}
	else
	{
		SAssignNew(ConditionsBox, SVerticalBox);
	}

	if (UnlockActionBox.IsValid())
	{
		UnlockActionBox->ClearChildren();
	}
	else
	{
		SAssignNew(UnlockActionBox, SVerticalBox);
	}


	if (EdLayerNode)
	{

		if (EdLayerNode->UnlockAction)
		{
			TSharedPtr<SGraphNode> NewNode = FNodeFactory::CreateNodeWidget(EdLayerNode->UnlockAction);
			if (OwnerGraphPanelPtr.IsValid())
			{
				NewNode->SetOwner(OwnerGraphPanelPtr.Pin().ToSharedRef());
				OwnerGraphPanelPtr.Pin()->AttachGraphEvents(NewNode);
			}
			AddUnlockAction(NewNode);
			NewNode->UpdateGraphNode();
		}



		if (EdLayerNode->Conditions)
		{
			TSharedPtr<SGraphNode> NewNode = FNodeFactory::CreateNodeWidget(EdLayerNode->Conditions);
			if (OwnerGraphPanelPtr.IsValid())
			{
				NewNode->SetOwner(OwnerGraphPanelPtr.Pin().ToSharedRef());
				OwnerGraphPanelPtr.Pin()->AttachGraphEvents(NewNode);
			}
			AddCondition(NewNode);
			NewNode->UpdateGraphNode();
		}

	}
}

void SPZ_SkillTreeSNode_Layer::CreateNodeWidget_TopPart()
{
	NodeWidget_TopPart->AddSlot()[ConditionsBox.ToSharedRef()];
}

void SPZ_SkillTreeSNode_Layer::CreateNodeWidget_BottomPart()
{
	NodeWidget_BottomPart->AddSlot()[
		UnlockActionBox.ToSharedRef()
		];
}





void SPZ_SkillTreeSNode_Layer::GetAdditionalNodeInfo(TArray<FString>& AdditionalInfoArray)
{

}




FText SPZ_SkillTreeSNode_Layer::GetNodeName() const
{
	return FText::FromString("Layer");
}

FLinearColor SPZ_SkillTreeSNode_Layer::GetNodeTitleColor() const
{
	return FLinearColor(0.2f, 0.2f, 0.6f);
}



const FSlateBrush* SPZ_SkillTreeSNode_Layer::GetBackgroundImage() const
{
	return FEditorStyle::GetBrush("Graph.StateNode.Body");
}

const FSlateBrush* SPZ_SkillTreeSNode_Layer::GetNodeImage() const
{
	return FPZ_SkillTreeEditorStyle::Get()->GetBrush(FPZ_SkillTreeEditorStyle::NodeIcon_ConditionNodeIcon);
}



const float SPZ_SkillTreeSNode_Layer::GetNodeBodyPadding() const
{
	return 2.0f;
}






void SPZ_SkillTreeSNode_Layer::AddCondition(TSharedPtr<SGraphNode> ConditionWidget)
{
	ConditionsBox->AddSlot().AutoHeight()[ConditionWidget.ToSharedRef()];

	AddSubNode(ConditionWidget);
}

void SPZ_SkillTreeSNode_Layer::AddUnlockAction(TSharedPtr<SGraphNode> UnlockActionWidget)
{
	UnlockActionBox->AddSlot().AutoHeight()[UnlockActionWidget.ToSharedRef()];

	AddSubNode(UnlockActionWidget);
}