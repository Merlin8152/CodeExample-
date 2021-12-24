// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeComponent/PZ_SkillTreeComponent.h"

#include "PZ_SkillTree_Editor.h"
#include "PZ_SkillTreeManager.h"
#include "PZ_SkillTreeContext.h"


#include "Nodes/ConnectionNode/PZ_SkillTreeRConnectionNode.h"



// Sets default values for this component's properties
UPZ_SkillTreeComponent::UPZ_SkillTreeComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
	
}

void UPZ_SkillTreeComponent::BeginPlay()
{
	SkillContexts.Empty();

	for (auto SkillTree : SkillGraphs) 
	{
		SkillContexts.Add(SkillTree.Key,UPZ_SkillTreeManager::CreateSkillTreeContext(SkillTree.Value, GetOwner(), this ));
	}

}

UPZ_SkillTreeContext* UPZ_SkillTreeComponent::GetSkillTreeByName(FString GraphName) const
{
	if ( SkillContexts.Contains(GraphName) && IsValid(SkillContexts[GraphName]) )
	{
		return SkillContexts[GraphName];
	}

	return nullptr;
}

UPZ_SkillTree_Editor* UPZ_SkillTreeComponent::GetSkillTreeEditorByName(FString GraphName) const
{
	if (SkillGraphs.Contains(GraphName)) return SkillGraphs[GraphName];

	return nullptr;
}

void UPZ_SkillTreeComponent::OnUpdateNextNode_Connection(UPZ_SkillTreeRConnectionNode* InConnectionNode)
{
	for (const auto& Context : SkillContexts)
	{
		if (Context.Value->ImplementSkillTree->InConnectionNodes.Contains(InConnectionNode->ConnectionName))
		{
			Context.Value->UpdateNextNodes(Context.Value->ImplementSkillTree->InConnectionNodes[InConnectionNode->ConnectionName]);
		}
	}
}

void UPZ_SkillTreeComponent::OnUpdatePrevNode_Connection(UPZ_SkillTreeRConnectionNode* InConnectionNode)
{
	for (const auto& Context : SkillContexts)
	{
		if (Context.Value->ImplementSkillTree->OutConnectionNodes.Contains(InConnectionNode->ConnectionName))
		{
			Context.Value->UpdatePreviousNodes(Context.Value->ImplementSkillTree->OutConnectionNodes[InConnectionNode->ConnectionName]);
		}
	}
}




