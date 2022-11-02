// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeContextItems/PZ_SkillTreeContextItem_Base.h"


#include "Nodes/BaseTreeElement/PZ_SkillTreeRBaseTreeElement.h"
#include "PZ_SkillTreeContext.h"




void UPZ_SkillTreeContextItem_Base::UpdateNext(TArray<UPZ_SkillTreeContextItem_Base*>& UpdatedNodes)
{
	TArray<UPZ_SkillTreeContextItem_Base*> NextNodes;
	FindNextNodesToUpdate(NextNodes);

	for (const auto& NextNode : NextNodes)
	{
		if (UpdatedNodes.Contains(NextNode)) continue;
		UpdatedNodes.Add(NextNode);
		NextNode->OnUpdate();
		if (NextNode->IsNeedContinueUpdateNext(UpdatedNodes)) NextNode->UpdateNext(UpdatedNodes);
	}
}

void UPZ_SkillTreeContextItem_Base::UpdatePrevious(TArray<UPZ_SkillTreeContextItem_Base*>& UpdatedNodes)
{
	TArray<UPZ_SkillTreeContextItem_Base*> PreviousNodes;
	FindPreviousNodesToUpdate(PreviousNodes);


	for (const auto& PreviousNode : PreviousNodes)
	{
		if (UpdatedNodes.Contains(PreviousNode)) continue;
		UpdatedNodes.Add(PreviousNode);
		OnUpdate();
		if (PreviousNode->IsNeedContinueUpdatePrevious(UpdatedNodes)) PreviousNode->UpdatePrevious(UpdatedNodes);
	}
}

void UPZ_SkillTreeContextItem_Base::UpdateNode(TArray<UPZ_SkillTreeContextItem_Base*>& UpdatedNodes)
{
	if (UpdatedNodes.Contains(this)) return;

	UpdatedNodes.Add(this);
	//OnUpdate();

	if (IsNeedContinueUpdateNext(UpdatedNodes)) UpdateNext(UpdatedNodes);
	if (IsNeedContinueUpdatePrevious(UpdatedNodes)) UpdatePrevious(UpdatedNodes);
}

void UPZ_SkillTreeContextItem_Base::OnUpdate()
{
	SkillTreeContext->OnContextUpdateProcedure(this);

}

void UPZ_SkillTreeContextItem_Base::OnExecute()
{
	SkillTreeNode->OnExecute(SkillTreeContext);

	OnExecute_Impl();

	TArray<UPZ_SkillTreeContextItem_Base*> UpdatedNodes;

	SkillTreeContext->OnContextExecuteProcedure(this);

	UpdateNode(UpdatedNodes);
}

void UPZ_SkillTreeContextItem_Base::OnExecute_Impl()
{
}

bool UPZ_SkillTreeContextItem_Base::IsNeedContinueUpdateNext(TArray<UPZ_SkillTreeContextItem_Base*>& UpdatedNodes)
{
	return false;
}

bool UPZ_SkillTreeContextItem_Base::IsNeedContinueUpdatePrevious(TArray<UPZ_SkillTreeContextItem_Base*>& UpdatedNodes)
{
	return false;
}

void UPZ_SkillTreeContextItem_Base::FindNextNodesToUpdate(TArray<UPZ_SkillTreeContextItem_Base*>& NodesToUpdate)
{
}

void UPZ_SkillTreeContextItem_Base::FindPreviousNodesToUpdate(TArray<UPZ_SkillTreeContextItem_Base*>& NodesToUpdate)
{
}
