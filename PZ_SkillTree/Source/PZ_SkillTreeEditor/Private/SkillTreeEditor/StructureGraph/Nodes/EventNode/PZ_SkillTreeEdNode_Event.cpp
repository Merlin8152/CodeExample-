// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeEditor/StructureGraph/Nodes/EventNode/PZ_SkillTreeEdNode_Event.h"

#include "SkillTreeEditor/StructureGraph/Nodes/SkillNode/PZ_SkillTreeEdNode_Skill.h"
#include "Nodes/SkillNode/PZ_SkillTreeRSkillNode.h"

#include "Nodes/EventNode/PZ_SkillTreeREventNode.h"
#include "PZ_SkillTree_Editor.h"

#include "SkillTreeEditor/PZ_SkillTreeEditorConstant.h"

UPZ_SkillTreeEdNode_Event::UPZ_SkillTreeEdNode_Event()
{
	bCanRenameNode = false;
}



void UPZ_SkillTreeEdNode_Event::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, FPZ_SkillTreeEditorConstant::PinCategory_Second, FPZ_SkillTreeEditorConstant::PinSubCategory_LeftRight, TEXT("Out"));
}




bool UPZ_SkillTreeEdNode_Event::CanDuplicateNode() const
{
	return true;
}

bool UPZ_SkillTreeEdNode_Event::CanUserDeleteNode() const
{
	return true;
}





ESkillTreeNodeType UPZ_SkillTreeEdNode_Event::GetNodeType() const
{
	return ESkillTreeNodeType::EventSkillNode;
}



void UPZ_SkillTreeEdNode_Event::CompileThisNodeInfo(UPZ_SkillTree_Editor* SkillTree)
{
	UPZ_SkillTreeEdNode_Base::CompileThisNodeInfo(SkillTree);

	CompileError(SkillTree);

	UPZ_SkillTreeREventNode* EventNode = Cast<UPZ_SkillTreeREventNode>(RNode);

	if (!EventNode->EventName.IsNone())
	{
		EventNode->NextNodes.Empty();

		if (GetOutputPin(FPZ_SkillTreeEditorConstant::PinCategory_Second) == nullptr) return;


		for (UEdGraphPin* LPin : GetOutputPin(FPZ_SkillTreeEditorConstant::PinCategory_Second)->LinkedTo)
		{
			auto Node = LPin->GetOwningNode();

			if (auto SkillNode = Cast<UPZ_SkillTreeEdNode_Skill>(Node))
			{

				if (auto RSkillNode = Cast<UPZ_SkillTreeRSkillNode>(SkillNode->RNode))
				{
					if (SkillTree->CompiledNodes.Contains(RSkillNode))
					{
						EventNode->NextNodes.Add(SkillNode->RNode);
					}
				}

			}

		}

		if (!SkillTree->CompiledEventNodes.Contains(EventNode->EventName) && EventNode->NextNodes.Num() > 0)
		{
			SkillTree->CompiledEventNodes.Add(EventNode->EventName, EventNode);
		}

	}

}


void UPZ_SkillTreeEdNode_Event::CompileError(UPZ_SkillTree_Editor* SkillTree)
{
	if (!SkillTree) return;

	ErrorMsg = FString();

	if (UPZ_SkillTreeREventNode* EventNode = Cast<UPZ_SkillTreeREventNode>(RNode)) 
	{

		if (!EventNode->EventName.IsNone())
		{
			if (SkillTree->CompiledEventNodes.Contains(EventNode->EventName))
			{
				ErrorMsg = FString("Events must not have the same name");
			}
		}
		else
		{
			ErrorMsg = FString("The event must have a name");
		}
	}

}






void UPZ_SkillTreeEdNode_Event::OnNodeDoubleClicked()
{
	// TODO....
}

void UPZ_SkillTreeEdNode_Event::OnChangedProperties(const FName& PropertyName) const
{
	Super::OnChangedProperties(PropertyName);

	// TODO....
}

