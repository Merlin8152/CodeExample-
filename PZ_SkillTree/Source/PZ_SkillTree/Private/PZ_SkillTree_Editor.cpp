// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTree_Editor.h"
#include "Nodes/BaseNode/PZ_SkillTreeRBaseNode.h"
#include "Nodes/EventNode/PZ_SkillTreeREventNode.h"
#include "Nodes/SkillNode/PZ_SkillTreeRSkillNode.h"
#include "Nodes/UINode/PZ_SkillTreeRUINode.h"

UPZ_SkillTree_Editor::UPZ_SkillTree_Editor()
{

}

UPZ_SkillTreeRBaseNode* UPZ_SkillTree_Editor::GetUIRootNode()
{
	for (const auto& Node : CompiledNodes)
	{
		if (UPZ_SkillTreeRBaseNode* BaseNode = Cast<UPZ_SkillTreeRBaseNode>(Node))
		{
			if (IsValid(BaseNode->UINode) && BaseNode->UINode->IsUIRootNode) return BaseNode;
		}

	}

	return nullptr;
}

void UPZ_SkillTree_Editor::GetRootNodes(TArray<UPZ_SkillTreeRBaseTreeElement*>& RootNodes)
{
	for (const auto& Node : CompiledNodes)
	{
		if (Node->IsRootNode) RootNodes.Add(Node);
	}

}


#if WITH_EDITOR

void UPZ_SkillTree_Editor::CleanSkillTree()
{

	CompiledNodes.Empty();
	InConnectionNodes.Empty();
	OutConnectionNodes.Empty();
}




#endif
