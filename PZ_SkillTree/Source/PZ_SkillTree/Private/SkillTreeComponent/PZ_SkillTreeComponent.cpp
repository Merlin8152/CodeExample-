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
	Super::BeginPlay();

	SkillContexts.Empty();

	for (auto SkillTree : SkillGraphs) 
	{
		SkillContexts.Add(SkillTree.Key,UPZ_SkillTreeManager::CreateSkillTreeContext(SkillTree.Value, GetOwner(), this ));
	}

	// need refactoring, difficult to understand
	for (const auto& LContext : SkillContexts)
	{
		for (const auto& LInContextConnection : LContext.Value->ImplementSkillTree->InConnectionNodes)
		{
			for (const auto& RContext : SkillContexts)
			{
				if (LContext == RContext) continue;

				for (const auto& LOutContextConnection : RContext.Value->ImplementSkillTree->OutConnectionNodes)
				{
					if (LOutContextConnection.Key == LInContextConnection.Key)
					{
						TArray<UPZ_SkillTreeContextItem_Base*> InConnectionContextArray;
						TArray<UPZ_SkillTreeContextItem_Base*> OutConnectionContextArray;

						//InConnectionContextArray prepare
						if (LInContextConnection.Value->IsNeedCreateContext())
						{
							InConnectionContextArray.Add(LContext.Value->ContextNodeInfo2[LInContextConnection.Value->MyIndex]);
						}
						else
						{
							TArray<UPZ_SkillTreeRBaseTreeElement*> InNodesWithContext;
							LInContextConnection.Value->GetOutRNodesByClass_WithContext<UPZ_SkillTreeRBaseTreeElement>(InNodesWithContext);
							for (const auto& InNodeWithContext : InNodesWithContext)
							{
								InConnectionContextArray.Add(LContext.Value->ContextNodeInfo2[InNodeWithContext->MyIndex]);
							}
						}

						//OutConnectionContextArray prepare						
						if (LOutContextConnection.Value->IsNeedCreateContext())
						{
							OutConnectionContextArray.Add(LContext.Value->ContextNodeInfo2[LOutContextConnection.Value->MyIndex]);
						}
						else
						{
							TArray<UPZ_SkillTreeRBaseTreeElement*> OutNodesWithContext;
							LOutContextConnection.Value->GetInRNodesByClass_WithContext<UPZ_SkillTreeRBaseTreeElement>(OutNodesWithContext);
							for (const auto& OutNodeWithContext : OutNodesWithContext)
							{
								OutConnectionContextArray.Add(LContext.Value->ContextNodeInfo2[OutNodeWithContext->MyIndex]);
							}
						}

						//Add links
						for (const auto& InConnectionNode : InConnectionContextArray)
						{
							for (const auto& OutConnectionNode : OutConnectionContextArray)
							{
								InConnectionNode->ParentContextNodes.Add(OutConnectionNode);
								OutConnectionNode->NextContextNodes.Add(InConnectionNode);
							}
						}

					}
				}

			}

		}
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




