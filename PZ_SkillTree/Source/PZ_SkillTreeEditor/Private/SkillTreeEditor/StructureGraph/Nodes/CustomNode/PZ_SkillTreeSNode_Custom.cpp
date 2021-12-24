// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTreeSNode_Custom.h"
#include "PZ_SkillTreeEdNode_Custom.h"

#include "Nodes/CustomNode/PZ_SkillTreeRCustomNode.h"
#include "NodeFactory.h"
#include "EditorStyleSet.h"
#include "../../../PZ_SkillTreeEditorStyle.h"
#include "SGraphPanel.h"



void SPZ_SkillTreeSNode_Custom::Construct(const FArguments& InArgs, UPZ_SkillTreeEdNode_Custom* InNode)
{
	GraphNode = InNode;
	InNode->SEdNode = this;
	EdBaseNode = InNode;
	EdCustomNode = InNode;
	RCustomNode = Cast<UPZ_SkillTreeRCustomNode>(InNode->RNode);

	this->SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}









void SPZ_SkillTreeSNode_Custom::GetAdditionalNodeInfo(TArray<FString>& AdditionalInfoArray)
{
	Super::GetAdditionalNodeInfo(AdditionalInfoArray);
	if (RCustomNode->IsHaveUI) AdditionalInfoArray.Add("Node with UI");
}



FText SPZ_SkillTreeSNode_Custom::GetNodeName() const
{
	return FText::FromString("Custom");
}

FLinearColor SPZ_SkillTreeSNode_Custom::GetNodeTitleColor() const
{
	return FLinearColor(0.6f, 0.6f, 0.6f);
}

FLinearColor SPZ_SkillTreeSNode_Custom::GetNodeBackgroundColor_Default() const
{
	return FLinearColor(0.2f, 0.02f, 0.02f);
}



const FSlateBrush* SPZ_SkillTreeSNode_Custom::GetNodeImage() const
{
	return FPZ_SkillTreeEditorStyle::Get()->GetBrush(FPZ_SkillTreeEditorStyle::NodeIcon_CustomNodeIcon);
}




const EVisibility SPZ_SkillTreeSNode_Custom::GetTopPinsBoxVisibility() const
{
	return EVisibility::Visible;
}



void SPZ_SkillTreeSNode_Custom::MoveTo(const FVector2D& NewPosition, FNodeSet& NodeFilter)
{
	Super::MoveTo(NewPosition, NodeFilter);

}