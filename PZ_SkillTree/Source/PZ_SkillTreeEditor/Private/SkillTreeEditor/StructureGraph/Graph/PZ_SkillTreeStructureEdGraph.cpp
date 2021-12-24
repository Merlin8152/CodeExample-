// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeEditor/StructureGraph/Graph/PZ_SkillTreeStructureEdGraph.h"
#include "PZ_SkillTree_Editor.h"
#include "../../PZ_SkillTreeGraphEditor.h"

#include "../../PZ_SkillTreeEditorConstant.h"

#include "../PZ_EdNodesInclude.h"
#include "PZ_SkillTreeRNodesInclude.h"
#include "../Nodes/PZ_SkillTreeNodeInterface.h"




void UPZ_SkillTreeEdGraph::RebuildGraph()
{

	SkillTree->CleanSkillTree();
	CompilingVisitedNodes.Empty();

	TArray<UPZ_SkillTreeEdNode_Base*> RootNodes;
	RootNodes = FindRoot();

	if (RootNodes.Num() > 0) 
	{

		for (auto RootNode : RootNodes)
		{
			CompileNode(RootNode);//рекурсивно компилируем ноду и ее дочерние(просто формируем набор нод только дерева с базовой информацией)
		}

		LinkCompiledNodes();
		LinkUINodes();
		CompileEventNodes();


		SkillTree->StructureEdGraph->NotifyGraphChanged();


		SkillTree->NeedToRebuild = false;

	}
	else 
	{
		SkillTree->NeedToRebuild = true;
	}

}



void UPZ_SkillTreeEdGraph::CompileNode(UEdGraphNode* Node)
{
	if (!IsValid(Node) || CompilingVisitedNodes.Contains(Node)) return;




	if (IPZ_SkillTreeNodeInterface* LSkillTreeeNode = Cast<IPZ_SkillTreeNodeInterface>(Node))
	{
		if (!LSkillTreeeNode->IsNeedCompile()) return;

		CompilingVisitedNodes.Add(Node);
		LSkillTreeeNode->CompileThisNodeInfo(SkillTree);

		if (LSkillTreeeNode->GetOutputPin(FPZ_SkillTreeEditorConstant::PinCategory_Main) == nullptr) return;
		for (UEdGraphPin* LPin : LSkillTreeeNode->GetOutputPin(FPZ_SkillTreeEditorConstant::PinCategory_Main)->LinkedTo)
		{
			CompileNode(LPin->GetOwningNode());
		}

	}

}



void UPZ_SkillTreeEdGraph::CompileEventNodes()
{
	TArray<UPZ_SkillTreeEdNode_Event*> EventNodeList;
	GetNodesOfClass<UPZ_SkillTreeEdNode_Event>(EventNodeList);



	SkillTree->CompiledEventNodes.Empty();


	for (const auto Event : EventNodeList)
	{
		Event->CompileThisNodeInfo(SkillTree);
	}
}




void UPZ_SkillTreeEdGraph::LinkCompiledNodes()
{
	for (int i = 0; i < CompilingVisitedNodes.Num(); ++i)
	{
		if (IPZ_SkillTreeNodeInterface* LSkillTreeNode = Cast<IPZ_SkillTreeNodeInterface>(CompilingVisitedNodes[i]))
		{
			if (LSkillTreeNode->GetOutputPin(FPZ_SkillTreeEditorConstant::PinCategory_Main) == nullptr) continue;
			for (UEdGraphPin* LPin : LSkillTreeNode->GetOutputPin(FPZ_SkillTreeEditorConstant::PinCategory_Main)->LinkedTo)
			{
				int32 LinkIndex = -1;
				CompilingVisitedNodes.Find(LPin->GetOwningNode(), LinkIndex);

				if (LinkIndex != -1)
				{
					SkillTree->CompiledNodes[i]->NextNodes.Add(SkillTree->CompiledNodes[LinkIndex]);
					SkillTree->CompiledNodes[LinkIndex]->ParentNodes.Add(SkillTree->CompiledNodes[i]);
				}

			}

		}

	}

}

void UPZ_SkillTreeEdGraph::LinkUINodes()
{
	for (const auto& RNode : SkillTree->CompiledNodes)
	{
		//свяжем UINodes чтобы потом не искать в рантайме
		if (UPZ_SkillTreeRBaseNode* BaseRNode = Cast<UPZ_SkillTreeRBaseNode>(RNode))
		{
			if (BaseRNode->UINode)
			{
				BaseRNode->UINode->NextNodes.Empty();
				BaseRNode->UINode->ParentNodes.Empty();

				TArray<UPZ_SkillTreeRBaseNode*> NextNodes;
				TArray<UPZ_SkillTreeRBaseNode*> PrevNodes;

				BaseRNode->FindNextNodesWithUI(NextNodes);
				BaseRNode->FindPrevNodesWithUI(PrevNodes);

				for (const auto& NextNode : NextNodes)
				{
					BaseRNode->UINode->NextNodes.AddUnique(NextNode->UINode);
				}

				for (const auto& PrevNode : PrevNodes)
				{
					BaseRNode->UINode->ParentNodes.AddUnique(PrevNode->UINode);
				}

			}
		}
	}
}






TArray<class UPZ_SkillTreeEdNode_Base*> UPZ_SkillTreeEdGraph::FindRoot()
{
	SkillTree->UIRoot = nullptr;
	TArray<UPZ_SkillTreeEdNode_Base*> AllNodeList;
	TArray<UPZ_SkillTreeEdNode_Base*> RootNodes;

	GetNodesOfClass<UPZ_SkillTreeEdNode_Base>(AllNodeList);


	for (const auto& Node : AllNodeList)
	{
		UEdGraphPin* InPin = Node->GetInputPin(FPZ_SkillTreeEditorConstant::PinCategory_Main);
		if (InPin)
		{
			bool IsHaveCompiledPrevNode = false;
			for (const auto& LinkedPin : InPin->LinkedTo)
			{
				if (IPZ_SkillTreeNodeInterface* LinkedPrevNode = Cast<IPZ_SkillTreeNodeInterface>(LinkedPin->GetOwningNode()))
				{
					if (LinkedPrevNode->IsNeedCompile())
					{
						IsHaveCompiledPrevNode = true;
					}
				}
			}

			Node->RNode->IsRootNode = !IsHaveCompiledPrevNode && Node->IsNeedCompile();
		}
		else
		{
			Node->RNode->IsRootNode = false;
		}
		if (Node->RNode->IsRootNode)
			RootNodes.Add(Node);

		if (!SkillTree->UIRoot && Node->IsHaveUINode())
		{
			SkillTree->UIRoot = Node->RNode;
		}

	}

	return RootNodes;

}


void UPZ_SkillTreeEdGraph::UniqueArrayNames(TArray<FName>& Names)
{
	TArray<FName> LUniqueNames;

	for (const FName LName : Names)
	{
		LUniqueNames.AddUnique(LName);
	}

	Names = LUniqueNames;
}





void UPZ_SkillTreeEdGraph::NotifyGraphChanged(const FEdGraphEditAction& Action)
{
	Super::NotifyGraphChanged(Action);

	if (!IsValid(SkillTree) || SkillTreeGraph == nullptr) return;


	SkillTree->NeedToRebuild = true;
	SkillTreeGraph->RegenerateMenusAndToolbars();
}