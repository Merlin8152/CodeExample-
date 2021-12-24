// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/BaseNode/PZ_SkillTreeRBaseNode.h"

// Fill out your copyright notice in the Description page of Project Settings.

#include "Nodes/UINode/PZ_SkillTreeRUINode.h"
#include "Nodes/EdgePoint/PZ_SkillTreeREdgeNode.h"
#include "PZ_SkillTreeContext.h"


UPZ_SkillTreeRBaseNode::UPZ_SkillTreeRBaseNode()
{

}









#if WITH_EDITORONLY_DATA


#endif

void UPZ_SkillTreeRBaseNode::FindNextNodesWithUI(TArray<UPZ_SkillTreeRBaseNode*>& InNextNodes)
{
	TArray<UPZ_SkillTreeRBaseNode*> NextNodes_Temp;

	GetOutRNodesByClass<UPZ_SkillTreeRBaseNode>(NextNodes_Temp);

	for (const auto& NextNode : NextNodes_Temp)
	{
		if (IsValid(NextNode->UINode))
		{
			InNextNodes.AddUnique(NextNode);
		}
		else
		{
			NextNode->FindNextNodesWithUI(InNextNodes);
		}
	}
}

void UPZ_SkillTreeRBaseNode::FindPrevNodesWithUI(TArray<UPZ_SkillTreeRBaseNode*>& InPrevNodes)
{
	TArray<UPZ_SkillTreeRBaseNode*> PrevNodes_Temp;

	GetInRNodesByClass<UPZ_SkillTreeRBaseNode>(PrevNodes_Temp);

	for (const auto& PrevNode : PrevNodes_Temp)
	{
		if (IsValid(PrevNode->UINode))
		{
			InPrevNodes.AddUnique(PrevNode);
		}
		else
		{
			PrevNode->FindPrevNodesWithUI(InPrevNodes);
		}
	}
}
