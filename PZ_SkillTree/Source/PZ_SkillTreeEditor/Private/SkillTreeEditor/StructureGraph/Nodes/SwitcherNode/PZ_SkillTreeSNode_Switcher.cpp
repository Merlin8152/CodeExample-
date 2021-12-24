// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTreeSNode_Switcher.h"
#include "PZ_SkillTreeEdNode_Switcher.h"
#include "Nodes/SwitcherNode/PZ_SkillTreeRSwitcherNode.h"

#include "EditorStyleSet.h"
#include "../../../PZ_SkillTreeEditorStyle.h"



void SPZ_SkillTreeSNode_Switcher::Construct(const FArguments& InArgs, UPZ_SkillTreeEdNode_Switcher* InNode)
{
	GraphNode = InNode;
	InNode->SEdNode = this;
	EdBaseNode = InNode;
	EdSwitcherNode = InNode;
	RSwitcherNode = Cast<UPZ_SkillTreeRSwitcherNode>(InNode->RNode);

	this->SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}




FText SPZ_SkillTreeSNode_Switcher::GetNodeName() const
{
	return FText::FromString("Switcher");
}

FLinearColor SPZ_SkillTreeSNode_Switcher::GetNodeTitleColor() const
{
	return FLinearColor(0.6f, 0.6f, 0.6f);
}

FLinearColor SPZ_SkillTreeSNode_Switcher::GetNodeBackgroundColor_Default() const
{
	return FLinearColor(0.15f, 0.15f, 0.25f);
}



const FSlateBrush* SPZ_SkillTreeSNode_Switcher::GetBackgroundImage() const
{
	return FEditorStyle::GetBrush("Graph.StateNode.Body");
}

const FSlateBrush* SPZ_SkillTreeSNode_Switcher::GetNodeImage() const
{
	return FPZ_SkillTreeEditorStyle::Get()->GetBrush(FPZ_SkillTreeEditorStyle::NodeIcon_SwitchNodeIcon);
}

