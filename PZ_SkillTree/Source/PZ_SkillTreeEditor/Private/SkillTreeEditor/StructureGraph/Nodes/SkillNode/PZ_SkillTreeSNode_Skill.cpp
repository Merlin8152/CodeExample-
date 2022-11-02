// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTreeSNode_Skill.h"
#include "PZ_SkillTreeEdNode_Skill.h"

#include "Nodes/SkillNode/PZ_SkillTreeRSkillNode.h"
#include "NodeFactory.h"
#include "EditorStyleSet.h"
#include "../../../PZ_SkillTreeEditorStyle.h"
#include "../../CustomWidgets/PZ_SkillTreeLayers.h"
#include "SGraphPanel.h"



void SPZ_SkillTreeSNode_Skill::Construct(const FArguments& InArgs, UPZ_SkillTreeEdNode_Skill* InNode)
{
	GraphNode = InNode;
	InNode->SEdNode = this;
	EdBaseNode = InNode;
	EdSkillNode = InNode;
	RSkillNode = Cast<UPZ_SkillTreeRSkillNode>(InNode->RNode);

	this->SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}



void SPZ_SkillTreeSNode_Skill::UpdateGraphNode_ResetStage()
{
	//if (ConditionsBox.IsValid())
	//{
	//	ConditionsBox->ClearChildren();
	//}
	//else
	//{
	//	SAssignNew(ConditionsBox, SVerticalBox);
	//}

	//if (UnlockActionBox.IsValid())
	//{
	//	UnlockActionBox->ClearChildren();
	//}
	//else
	//{
	//	SAssignNew(UnlockActionBox, SVerticalBox);
	//}

	if (LayerBox.IsValid())
	{
		LayerBox->ClearChildren();
	}
	else
	{
		SAssignNew(LayerBox, SVerticalBox);
	}

	if (LayersWidget.IsValid())
	{
		LayersWidget->UpdateLayers();
	}
	else
	{
		SAssignNew(LayersWidget, SPZ_Layers).SkillNode(EdSkillNode);
	}


	if (EdSkillNode)
	{
		
		//if (EdSkillNode->UnlockAction)
		//{
		//	TSharedPtr<SGraphNode> NewNode = FNodeFactory::CreateNodeWidget(EdSkillNode->UnlockAction);
		//	if (OwnerGraphPanelPtr.IsValid())
		//	{
		//		NewNode->SetOwner(OwnerGraphPanelPtr.Pin().ToSharedRef());
		//		OwnerGraphPanelPtr.Pin()->AttachGraphEvents(NewNode);
		//	}
		//	AddUnlockAction(NewNode);
		//	NewNode->UpdateGraphNode();
		//}
		//

		//
		//if (EdSkillNode->Conditions)
		//{
		//	TSharedPtr<SGraphNode> NewNode = FNodeFactory::CreateNodeWidget(EdSkillNode->Conditions);
		//	if (OwnerGraphPanelPtr.IsValid())
		//	{
		//		NewNode->SetOwner(OwnerGraphPanelPtr.Pin().ToSharedRef());
		//		OwnerGraphPanelPtr.Pin()->AttachGraphEvents(NewNode);
		//	}
		//	AddCondition(NewNode);
		//	NewNode->UpdateGraphNode();
		//}


		if ((EdSkillNode->Layers.Num() > 0) && (EdSkillNode->CurrentLayer >= 0))
		{
			TSharedPtr<SGraphNode> NewNode = FNodeFactory::CreateNodeWidget(EdSkillNode->Layers[EdSkillNode->CurrentLayer]);
			if (OwnerGraphPanelPtr.IsValid())
			{
				NewNode->SetOwner(OwnerGraphPanelPtr.Pin().ToSharedRef());
				OwnerGraphPanelPtr.Pin()->AttachGraphEvents(NewNode);
			}
			AddLayer(NewNode);
			NewNode->UpdateGraphNode();
		}
		
	}
}

void SPZ_SkillTreeSNode_Skill::CreateNodeWidget_TopPart()
{
	//NodeWidget_TopPart->AddSlot()
	//	[
	//		ConditionsBox.ToSharedRef()
	//	];
}

void SPZ_SkillTreeSNode_Skill::CreateNodeWidget_BottomPart()
{
	NodeWidget_BottomPart->AddSlot()
		[
			//UnlockActionBox.ToSharedRef()
			LayerBox.ToSharedRef()
		];
}

void SPZ_SkillTreeSNode_Skill::CreateNodeWidget_RightPart()
{
	if (EdSkillNode->Layers.Num() <= 1) return;
	NodeWidget_RightPart->AddSlot()
		[
			LayersWidget.ToSharedRef()
			//SAssignNew(LayersWidget, SPZ_Layers)
			//.SkillNode(EdSkillNode)
		];
}




void SPZ_SkillTreeSNode_Skill::GetAdditionalNodeInfo(TArray<FString>& AdditionalInfoArray)
{
	SPZ_SkillTreeSNode_Base::GetAdditionalNodeInfo(AdditionalInfoArray);

	//AdditionalInfoArray.Add("SkillName: " + RSkillNode->SkillName.ToString());
}



FText SPZ_SkillTreeSNode_Skill::GetNodeName() const
{
	return FText::FromString("Skill");
}

FLinearColor SPZ_SkillTreeSNode_Skill::GetNodeTitleColor() const
{
	return FLinearColor(0.6f, 0.6f, 0.6f);
}



const FSlateBrush* SPZ_SkillTreeSNode_Skill::GetNodeImage() const
{
	return FPZ_SkillTreeEditorStyle::Get()->GetBrush(FPZ_SkillTreeEditorStyle::NodeIcon_SkillNodeIcon);
}




const EVisibility SPZ_SkillTreeSNode_Skill::GetTopPinsBoxVisibility() const
{
	return EVisibility::Visible;
}



void SPZ_SkillTreeSNode_Skill::AddLayer(TSharedPtr<SGraphNode> LayerWidget)
{
	LayerBox->AddSlot().AutoHeight()
		[
			LayerWidget.ToSharedRef()
		];

	AddSubNode(LayerWidget);
}


void SPZ_SkillTreeSNode_Skill::MoveTo(const FVector2D& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty)
{
	RSkillNode->TempUIPositionOnCompile = NewPosition;

	SPZ_SkillTreeSNode_Base::MoveTo(NewPosition, NodeFilter, bMarkDirty);
}