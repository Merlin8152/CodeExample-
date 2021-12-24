// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTreeSNode_Condition.h"
#include "PZ_SkillTreeEdNode_Condition.h"
#include "Nodes/ConditionNode/PZ_SkillTreeRConditionNode.h"
#include "SkillTreeEvent/PZ_SkillTreeCondition.h"

#include "EditorStyleSet.h"
#include "../../../PZ_SkillTreeEditorStyle.h"


#include "SGraphPanel.h"

void SPZ_SkillTreeSNode_Condition::Construct(const FArguments& InArgs, UPZ_SkillTreeEdNode_Condition* InNode)
{

	GraphNode = InNode;
	InNode->SEdNode = this;
	EdBaseNode = InNode;
	EdConditionNode = InNode;
	RConditionNode = Cast<UPZ_SkillTreeRConditionNode>(InNode->RNode);

	this->SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}



void SPZ_SkillTreeSNode_Condition::GetAdditionalNodeInfo(TArray<FString>& AdditionalInfoArray)
{
	for (int Index = 0; Index < RConditionNode->SendConditionEvents.Num(); Index++)
	{
		auto SendConditionEvent = RConditionNode->SendConditionEvents[Index];
		FString ClassName = SendConditionEvent ? SendConditionEvent->GetName() : "None";
		FString Line = FString::FromInt(Index) + ": " + ClassName;
		AdditionalInfoArray.Add(Line);
	}
}




FText SPZ_SkillTreeSNode_Condition::GetNodeName() const
{
	return FText::FromString("Condition");
}

FLinearColor SPZ_SkillTreeSNode_Condition::GetNodeTitleColor() const
{
	return FLinearColor(0.2f, 0.2f, 0.6f);
}



const FSlateBrush* SPZ_SkillTreeSNode_Condition::GetBackgroundImage() const
{
	return FEditorStyle::GetBrush("Graph.StateNode.Body");
}

const FSlateBrush* SPZ_SkillTreeSNode_Condition::GetNodeImage() const
{
	return FPZ_SkillTreeEditorStyle::Get()->GetBrush(FPZ_SkillTreeEditorStyle::NodeIcon_ConditionNodeIcon);
}



const float SPZ_SkillTreeSNode_Condition::GetNodeBodyPadding() const
{
	return 2.0f;
}
