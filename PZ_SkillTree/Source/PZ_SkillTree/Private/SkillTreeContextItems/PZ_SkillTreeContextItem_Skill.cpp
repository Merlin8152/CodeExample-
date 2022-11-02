// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeContextItems/PZ_SkillTreeContextItem_Skill.h"

#include "Nodes/BaseNode/PZ_SkillTreeRBaseNode.h"
#include "Nodes/ActiveSkillNode/PZ_SkillTreeRActiveSkillNode.h"
#include "Nodes/PassiveSkillNode/PZ_SkillTreeRPassiveSkillNode.h"
#include "Nodes/LayerNode/PZ_SkillTreeRLayerNode.h"
#include "PZ_SkillTreeContext.h"

void UPZ_SkillTreeContextItem_Skill::OnExecute_Impl()
{
	if (auto SkillNode = Cast<UPZ_SkillTreeRSkillNode>(SkillTreeNode))
	{
		if (auto ActiveNode = Cast<UPZ_SkillTreeRActiveSkillNode>(SkillTreeNode))
		{
			CurrentSkillLvl++;

			if (CurrentSkillLvl >= ActiveNode->MaxSkillLevel && !ActiveNode->CanAlwaysUpdate)
			{
				IsOpen = true;
			}
		}
		else if (auto PassiveNode = Cast<UPZ_SkillTreeRPassiveSkillNode>(SkillTreeNode))
		{
			CurrentSkillLvl++;
			IsOpen = true;
		}

		if( SkillNode->Layers.Num() <= 0 || !IsValid(SkillNode->Layers[CurrentSkillLayer]) ) return;
		if (auto SkillActionNode = Cast<UPZ_SkillTreeRSkillActionNode>(SkillNode->Layers[CurrentSkillLayer]->SkillActionNode))
		{
			SkillActionNode->OnExecute(SkillTreeContext);
		}
	}
}


bool UPZ_SkillTreeContextItem_Skill::IsNeedContinueUpdateNext(TArray<UPZ_SkillTreeContextItem_Base*>& UpdatedNodes)
{
	bool IsNeedContinue = true;
	for (const auto& ParentNode : ParentContextNodes)
	{
		if (UpdatedNodes.Contains(ParentNode))
		{
			IsNeedContinue = false;
			break;
		}
	}
	return IsNeedContinue;
}

bool UPZ_SkillTreeContextItem_Skill::IsNeedContinueUpdatePrevious(TArray<UPZ_SkillTreeContextItem_Base*>& UpdatedNodes)
{
	return false;
}

void UPZ_SkillTreeContextItem_Skill::OnUpdate()
{
	CanBeOpen = true;

	Super::OnUpdate();
}

void UPZ_SkillTreeContextItem_Skill::FindNextNodesToUpdate(TArray<UPZ_SkillTreeContextItem_Base*>& NodesToUpdate)
{
	TArray<UPZ_SkillTreeContextItem_Skill*> NextContextSkillNodes;
	GetOutRNodesByClass<UPZ_SkillTreeContextItem_Skill>(NextContextSkillNodes);

	for (const auto& NextContextSkillNode : NextContextSkillNodes)
	{
		NodesToUpdate.Add(NextContextSkillNode);
	}
}

void UPZ_SkillTreeContextItem_Skill::FindPreviousNodesToUpdate(TArray<UPZ_SkillTreeContextItem_Base*>& NodesToUpdate)
{

}
