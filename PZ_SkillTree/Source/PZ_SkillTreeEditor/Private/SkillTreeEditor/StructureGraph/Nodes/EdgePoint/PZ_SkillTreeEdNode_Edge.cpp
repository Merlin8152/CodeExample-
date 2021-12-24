// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillTreeEditor/StructureGraph/Nodes/EdgePoint/PZ_SkillTreeEdNode_Edge.h"

#include "PZ_SkillTree_Editor.h"
#include "Nodes/EdgePoint/PZ_SkillTreeREdgeNode.h"




void UPZ_SkillTreeEdNode_Edge::AllocateDefaultPins()
{
	UEdGraphPin* Inputs = CreatePin(EGPD_Input, TEXT("Edge"), FName("In"), TEXT("In"));
	Inputs->bHidden = true;
	UEdGraphPin* Outputs = CreatePin(EGPD_Output, TEXT("Edge"), FName("Out"), TEXT("Out"));
	Outputs->bHidden = true;
}


void UPZ_SkillTreeEdNode_Edge::PinConnectionListChanged(UEdGraphPin* Pin)
{
	if (Pin->LinkedTo.Num() == 0)
	{
		// Commit suicide; transitions must always have an input and output connection
		Modify();

		// Our parent graph will have our graph in SubGraphs so needs to be modified to record that.
		if (UEdGraph* ParentGraph = GetGraph())
		{
			ParentGraph->Modify();
		}


		DestroyNode();
	}
}



void UPZ_SkillTreeEdNode_Edge::PrepareForCopying()
{
	Super::PrepareForCopying();

	REdgeNode->Rename(nullptr, this, REN_DontCreateRedirectors | REN_DoNotDirty);
}






ESkillTreeNodeType UPZ_SkillTreeEdNode_Edge::GetNodeType() const
{
	return ESkillTreeNodeType::None;
}


UEdGraphPin* UPZ_SkillTreeEdNode_Edge::GetInputPin(const FName& PinCategory) const
{
	for (UEdGraphPin* Pin : Pins)
	{
		if (Pin->Direction == EEdGraphPinDirection::EGPD_Input)
		{
			return Pin;
		}
	}

	return nullptr;
}

UEdGraphPin* UPZ_SkillTreeEdNode_Edge::GetOutputPin(const FName& PinCategory) const
{
	for (UEdGraphPin* Pin : Pins)
	{
		if (Pin->Direction == EEdGraphPinDirection::EGPD_Output)
		{
			return Pin;
		}
	}

	return nullptr;
}






void UPZ_SkillTreeEdNode_Edge::CompileThisNodeInfo(UPZ_SkillTree_Editor* SkillTree)
{
	if (SkillTree)
	{
		int32 NodeIndex = SkillTree->CompiledNodes.Add(REdgeNode);
		if (REdgeNode)
		{
			REdgeNode->ResetNavigationNode();
			REdgeNode->MyIndex = NodeIndex;
			REdgeNode->NodeType = GetNodeType();
			REdgeNode->Rename(nullptr, SkillTree, REN_DontCreateRedirectors | REN_DoNotDirty);
		}
	}


}

bool UPZ_SkillTreeEdNode_Edge::IsNeedCompile()
{



	if (!REdgeNode->IsNeedCompile)
	{
		return false;
	}
	else
	{
		UEdGraphPin* InEdgePin = GetInputPin("Edge");

		if (InEdgePin && InEdgePin->LinkedTo.Num() > 0)
		{
			bool IsHaveCompiledPrevNode = false;
			for (const auto& LinkedToPin : InEdgePin->LinkedTo)
			{
				if (IPZ_SkillTreeNodeInterface* LSkillTreeNode = Cast<IPZ_SkillTreeNodeInterface>(LinkedToPin->GetOwningNode()))
				{
					if (LSkillTreeNode->IsNeedCompile())
					{
						IsHaveCompiledPrevNode = true;
						break;
					}
				}
			}
			return IsHaveCompiledPrevNode;
		}
		else
		{
			return false;
		}
	}
}







UEdGraphNode* UPZ_SkillTreeEdNode_Edge::GetStartNode()
{
	if (GetInputPin()->LinkedTo.Num() > 0)
	{
		return GetInputPin()->LinkedTo[0]->GetOwningNode();
	}

	return nullptr;
}

UEdGraphNode* UPZ_SkillTreeEdNode_Edge::GetEndNode()
{
	if (GetOutputPin()->LinkedTo.Num() > 0)
	{
		return GetOutputPin()->LinkedTo[0]->GetOwningNode();
	}

	return nullptr;
}










void UPZ_SkillTreeEdNode_Edge::OnNodeDoubleClicked()
{
	// TODO ....
}

void UPZ_SkillTreeEdNode_Edge::OnChangedProperties(const FName& PropertyName) const
{
	// TODO ....
}





void UPZ_SkillTreeEdNode_Edge::CreateConnections(UEdGraphPin* Start, UEdGraphPin* End)
{
	if (!Start || !End) return;


	UEdGraphPin* ThisInputPin = GetInputPin();
	UEdGraphPin* ThisOutputPin = GetOutputPin();

	ThisInputPin->Modify();
	ThisInputPin->LinkedTo.Empty();
	ThisOutputPin->Modify();
	ThisOutputPin->LinkedTo.Empty();




	Start->Modify();
	ThisInputPin->MakeLinkTo(Start);
	Start->MakeLinkTo(ThisInputPin);


	End->Modify();
	ThisOutputPin->MakeLinkTo(End);
	End->MakeLinkTo(ThisOutputPin);
}




