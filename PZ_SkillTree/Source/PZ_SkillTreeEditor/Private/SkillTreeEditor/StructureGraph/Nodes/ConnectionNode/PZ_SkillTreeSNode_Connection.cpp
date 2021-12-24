// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTreeSNode_Connection.h"
#include "PZ_SkillTreeEdNode_Connection.h"

#include "Nodes/ConnectionNode/PZ_SkillTreeRConnectionNode.h"
#include "NodeFactory.h"
#include "EditorStyleSet.h"
#include "../../../PZ_SkillTreeEditorStyle.h"
#include "SGraphPanel.h"

#include "SkillTreeEditor/PZ_SkillTreeEditorConstant.h"



void SPZ_SkillTreeSNode_Connection::Construct(const FArguments& InArgs, UPZ_SkillTreeEdNode_Connection* InNode)
{
	GraphNode = InNode;
	InNode->SEdNode = this;
	EdBaseNode = InNode;
	EdConnectionNode = InNode;
	RConnectionNode = Cast<UPZ_SkillTreeRConnectionNode>(InNode->RNode);

	this->SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}









void SPZ_SkillTreeSNode_Connection::GetAdditionalNodeInfo(TArray<FString>& AdditionalInfoArray)
{
	Super::GetAdditionalNodeInfo(AdditionalInfoArray);
	AdditionalInfoArray.Add("Name: " + RConnectionNode->ConnectionName.ToString());
}



FText SPZ_SkillTreeSNode_Connection::GetNodeName() const
{
	return FText::FromString("Connection");
}

FLinearColor SPZ_SkillTreeSNode_Connection::GetNodeTitleColor() const
{
	return FLinearColor(0.6f, 0.6f, 0.6f);
}

FLinearColor SPZ_SkillTreeSNode_Connection::GetNodeBackgroundColor_Default() const
{
	return FLinearColor(0.9f, 0.15f, 0.7f);
}



const FSlateBrush* SPZ_SkillTreeSNode_Connection::GetNodeImage() const
{
	return FPZ_SkillTreeEditorStyle::Get()->GetBrush(FPZ_SkillTreeEditorStyle::NodeIcon_ConnectionNodeIcon);
}




const EVisibility SPZ_SkillTreeSNode_Connection::GetTopPinsBoxVisibility() const
{
	return EdConnectionNode->IsHaveOutConnection(FPZ_SkillTreeEditorConstant::PinCategory_Main) ? EVisibility::Hidden : EVisibility::Visible;
}

const EVisibility SPZ_SkillTreeSNode_Connection::GetBottomPinsBoxVisibility() const
{
	return EdConnectionNode->IsHaveInConnection(FPZ_SkillTreeEditorConstant::PinCategory_Main) ? EVisibility::Hidden : EVisibility::Visible;
}

void SPZ_SkillTreeSNode_Connection::MoveTo(const FVector2D& NewPosition, FNodeSet& NodeFilter)
{
	Super::MoveTo(NewPosition, NodeFilter);

}