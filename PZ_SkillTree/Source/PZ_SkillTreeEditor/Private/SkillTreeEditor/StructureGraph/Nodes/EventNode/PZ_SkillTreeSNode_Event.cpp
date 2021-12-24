// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTreeSNode_Event.h"
#include "PZ_SkillTreeEdNode_Event.h"
#include "Nodes/EventNode/PZ_SkillTreeREventNode.h"

#include "EditorStyleSet.h"
#include "../../../PZ_SkillTreeEditorStyle.h"


#include "SGraphPanel.h"

void SPZ_SkillTreeSNode_Event::Construct(const FArguments& InArgs, UPZ_SkillTreeEdNode_Event* InNode)
{
	GraphNode = InNode;
	InNode->SEdNode = this;
	EdBaseNode = InNode;
	EdEventNode = InNode;
	REventNode = Cast<UPZ_SkillTreeREventNode>(InNode->RNode);

	this->SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}


void SPZ_SkillTreeSNode_Event::GetAdditionalNodeInfo(TArray<FString>& AdditionalInfoArray)
{
	SPZ_SkillTreeSNode_Base::GetAdditionalNodeInfo(AdditionalInfoArray);
	AdditionalInfoArray.Add(REventNode->EventName.ToString());
}




FText SPZ_SkillTreeSNode_Event::GetNodeName() const
{
	return FText::FromString("Event");
}

FLinearColor SPZ_SkillTreeSNode_Event::GetNodeTitleColor() const
{
	return FLinearColor(0.2f, 0.2f, 0.6f);
}

FLinearColor SPZ_SkillTreeSNode_Event::GetNodeBackgroundColor_Default() const
{
	return FLinearColor(0.15f, 0.05f, 0.5f);
}



const FSlateBrush* SPZ_SkillTreeSNode_Event::GetBackgroundImage() const
{
	return FEditorStyle::GetBrush("Graph.StateNode.Body");
}





const float SPZ_SkillTreeSNode_Event::GetNodeBodyPadding() const
{
	return 2.0f;
}

const FSlateBrush* SPZ_SkillTreeSNode_Event::GetNodeImage() const
{
	return FPZ_SkillTreeEditorStyle::Get()->GetBrush(FPZ_SkillTreeEditorStyle::NodeIcon_EventNodeIcon);
}
