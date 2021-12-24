// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTreeSNode_SkillAction.h"
#include "PZ_SkillTreeEdNode_SkillAction.h"
#include "Nodes/SkillActionNode/PZ_SkillTreeRSkillActionNode.h"

#include "EditorStyleSet.h"
#include "../../../PZ_SkillTreeEditorStyle.h"

#include "SkillTreeEvent/PZ_SkillTreeEvent.h"
#include "SGraphPanel.h"

void SPZ_SkillTreeSNode_SkillAction::Construct(const FArguments& InArgs, UPZ_SkillTreeEdNode_SkillAction* InNode)
{
	GraphNode = InNode;
	InNode->SEdNode = this;
	EdBaseNode = InNode;
	EdSkillActionNode = InNode;
	RSkillActionNode = Cast<UPZ_SkillTreeRSkillActionNode>(InNode->RNode);

	this->SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}

void SPZ_SkillTreeSNode_SkillAction::GetAdditionalNodeInfo(TArray<FString>& AdditionalInfoArray)
{
	for (int Index = 0; Index < RSkillActionNode->SendEvents.Num(); Index++)
	{
		auto SendEvent = RSkillActionNode->SendEvents[Index];
		FString ClassName = SendEvent ? SendEvent->GetName() : "None";
		FString Line = FString::FromInt(Index) + ": " + ClassName;
		AdditionalInfoArray.Add(Line);
	}
}





FText SPZ_SkillTreeSNode_SkillAction::GetNodeName() const
{
	return FText::FromString("Skill Action");
}

FLinearColor SPZ_SkillTreeSNode_SkillAction::GetNodeTitleColor() const
{
	return FLinearColor(0.2f, 0.2f, 0.6f);
}


const FSlateBrush* SPZ_SkillTreeSNode_SkillAction::GetBackgroundImage() const
{
	return FEditorStyle::GetBrush("Graph.StateNode.Body");
}

const FSlateBrush* SPZ_SkillTreeSNode_SkillAction::GetNodeImage() const
{
	return FPZ_SkillTreeEditorStyle::Get()->GetBrush(FPZ_SkillTreeEditorStyle::NodeIcon_SkillActionNodeIcon);
}




const float SPZ_SkillTreeSNode_SkillAction::GetNodeBodyPadding() const
{
	return 2.0f;
}


