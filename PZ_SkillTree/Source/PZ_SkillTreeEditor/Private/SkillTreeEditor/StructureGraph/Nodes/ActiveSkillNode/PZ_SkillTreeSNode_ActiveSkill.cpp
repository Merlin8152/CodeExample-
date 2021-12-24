// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTreeSNode_ActiveSkill.h"
#include "PZ_SkillTreeEdNode_ActiveSkill.h"

#include "Nodes/ActiveSkillNode/PZ_SkillTreeRActiveSkillNode.h"

#include "EditorStyleSet.h"
#include "../../../PZ_SkillTreeEditorStyle.h"



void SPZ_SkillTreeSNode_ActiveSkill::Construct(const FArguments& InArgs, UPZ_SkillTreeEdNode_ActiveSkill* InNode)
{
	GraphNode = InNode;
	InNode->SEdNode = this;
	EdBaseNode = InNode;
	EdActiveSkillNode = InNode;
	RActiveSkillNode = Cast<UPZ_SkillTreeRActiveSkillNode>(InNode->RNode);
	EdSkillNode = InNode;
	RSkillNode = Cast<UPZ_SkillTreeRSkillNode>(InNode->RNode);

	this->SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}



void SPZ_SkillTreeSNode_ActiveSkill::GetAdditionalNodeInfo(TArray<FString>& AdditionalInfoArray)
{
	SPZ_SkillTreeSNode_Skill::GetAdditionalNodeInfo(AdditionalInfoArray);
	AdditionalInfoArray.Add("Max LVL: " + FString::FromInt(RActiveSkillNode->MaxSkillLevel));
}





FText SPZ_SkillTreeSNode_ActiveSkill::GetNodeName() const
{
	return FText::FromString("ActiveSkill");
}

FLinearColor SPZ_SkillTreeSNode_ActiveSkill::GetNodeTitleColor() const
{
	return FLinearColor(0.6f, 0.6f, 0.6f);
}

FLinearColor SPZ_SkillTreeSNode_ActiveSkill::GetNodeBackgroundColor_Default() const
{
	return FLinearColor(0.0f, 0.1f, 0.5f);
}


const FSlateBrush* SPZ_SkillTreeSNode_ActiveSkill::GetBackgroundImage() const
{
	return FEditorStyle::GetBrush("Graph.StateNode.Body");
}

const FSlateBrush* SPZ_SkillTreeSNode_ActiveSkill::GetNodeImage() const
{
	return RActiveSkillNode->IsRootNode
		? FPZ_SkillTreeEditorStyle::Get()->GetBrush(FPZ_SkillTreeEditorStyle::NodeIcon_RootNodeIcon)
		: FPZ_SkillTreeEditorStyle::Get()->GetBrush(FPZ_SkillTreeEditorStyle::NodeIcon_SkillNodeIcon);
}

