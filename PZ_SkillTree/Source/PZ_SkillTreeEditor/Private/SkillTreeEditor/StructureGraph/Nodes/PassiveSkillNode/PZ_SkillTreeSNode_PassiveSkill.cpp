// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTreeSNode_PassiveSkill.h"
#include "PZ_SkillTreeEdNode_PassiveSkill.h"
#include "Nodes/PassiveSkillNode/PZ_SkillTreeRPassiveSkillNode.h"

#include "EditorStyleSet.h"
#include "../../../PZ_SkillTreeEditorStyle.h"



void SPZ_SkillTreeSNode_PassiveSkill::Construct(const FArguments& InArgs, UPZ_SkillTreeEdNode_PassiveSkill* InNode)
{
	GraphNode = InNode;
	InNode->SEdNode = this;
	EdBaseNode = InNode;
	EdPassiveSkillNode = InNode;
	RPassiveSkillNode = Cast<UPZ_SkillTreeRPassiveSkillNode>(InNode->RNode);
	EdSkillNode = InNode;
	RSkillNode = Cast<UPZ_SkillTreeRSkillNode>(InNode->RNode);

	this->SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}




FText SPZ_SkillTreeSNode_PassiveSkill::GetNodeName() const
{
	return FText::FromString("Passive Skill");
}

FLinearColor SPZ_SkillTreeSNode_PassiveSkill::GetNodeTitleColor() const
{
	return FLinearColor(0.6f, 0.6f, 0.6f);
}

FLinearColor SPZ_SkillTreeSNode_PassiveSkill::GetNodeBackgroundColor_Default() const
{
	return FLinearColor(0.0f, 0.5f, 0.15f);
}


const FSlateBrush* SPZ_SkillTreeSNode_PassiveSkill::GetNodeImage() const
{
	return RPassiveSkillNode->IsRootNode
		? FPZ_SkillTreeEditorStyle::Get()->GetBrush(FPZ_SkillTreeEditorStyle::NodeIcon_RootNodeIcon) 
		: FPZ_SkillTreeEditorStyle::Get()->GetBrush(FPZ_SkillTreeEditorStyle::NodeIcon_SkillNodeIcon);
}



