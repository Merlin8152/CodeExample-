// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTreeUIPositionSNode_UI.h"
#include "PZ_SkillTreeUIPositionEdNode_UI.h"

#include "Nodes/UINode/PZ_SkillTreeRUINode.h"
#include "Nodes/BaseNode/PZ_SkillTreeRBaseNode.h"

#include "NodeFactory.h"
#include "EditorStyleSet.h"
#include "../../../PZ_SkillTreeEditorStyle.h"

#include "SkillTreeWidgetCreator/PZ_SkillTreeWidgetCreator.h"


void SPZ_SkillTreeUIPositionSNode_UI::Construct(const FArguments& InArgs, UPZ_SkillTreeUIPositionEdNode_UI* InNode)
{
	GraphNode = InNode;
	InNode->SEdNode = this;
	EdUINode = InNode;
	RUINode = Cast<UPZ_SkillTreeRUINode>(InNode->RUINode);

	this->SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}






void SPZ_SkillTreeUIPositionSNode_UI::GetAdditionalNodeInfo(TArray<FString>& AdditionalInfoArray)
{
	SPZ_SkillTreeUIPositionSNode_Base::GetAdditionalNodeInfo(AdditionalInfoArray);
	if (RUINode->IsUIRootNode) AdditionalInfoArray.Add("UI Root Node");
	if (RUINode->RNodeLink->IsRootNode) AdditionalInfoArray.Add("Root Node");
	AdditionalInfoArray.Add(*UEnum::GetDisplayValueAsText(RUINode->RNodeLink->NodeType).ToString());

	if (RUINode->ObjectCreator)	RUINode->ObjectCreator->GetAdditionalNodeInfo(AdditionalInfoArray);
}



FText SPZ_SkillTreeUIPositionSNode_UI::GetNodeName() const
{
	return RUINode->RNodeLink->CustomName != "" ? FText::FromName(RUINode->RNodeLink->CustomName) : FText::FromName("UI");
}

FLinearColor SPZ_SkillTreeUIPositionSNode_UI::GetNodeTitleColor() const
{
	return FLinearColor(0.6f, 0.6f, 0.6f);
}



const FSlateBrush* SPZ_SkillTreeUIPositionSNode_UI::GetNodeImage() const
{
	return FPZ_SkillTreeEditorStyle::Get()->GetBrush(FPZ_SkillTreeEditorStyle::NodeIcon_UINodeIcon);
}



const EVisibility SPZ_SkillTreeUIPositionSNode_UI::GetTopPinsBoxVisibility() const
{
	return EVisibility::Visible;
}


void SPZ_SkillTreeUIPositionSNode_UI::MoveTo(const FVector2D& NewPosition, FNodeSet& NodeFilter)
{
	SPZ_SkillTreeUIPositionSNode_Base::MoveTo(NewPosition, NodeFilter);
	/*if (!RUINode->IsUIRootNode)
	{
		SPZ_SkillTreeUIPositionSNode_Base::MoveTo(NewPosition, NodeFilter);
		RUINode->UIPosition = FVector2D(NewPosition);
	}*/

}

FLinearColor SPZ_SkillTreeUIPositionSNode_UI::GetNodeBackgroundColor_Default() const
{
	return 	FLinearColor(0.0f, 0.5f, 0.15f);
}

