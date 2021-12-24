// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeEditor/UIPositionGraph/Graph/PZ_SkillTreeUIPositionEdGraph.h"
#include "PZ_SkillTree_Editor.h"
#include "../../PZ_SkillTreeGraphEditor.h"

#include "../../PZ_SkillTreeEditorConstant.h"

#include "Nodes/SkillNode/PZ_SkillTreeRSkillNode.h"
#include "Nodes/BaseTreeElement/PZ_SkillTreeRBaseTreeElement.h"
#include "Nodes/UINode/PZ_SkillTreeRUINode.h"

#include "../Nodes/PZ_UIPositionEdNodesInclude.h"

#include "../Nodes/PZ_SkillTreeUIPositionNodeInterface.h"

#include "SkillTreeEditor/UIPositionGraph/Graph/PZ_SkillTreeUIPositionEdGraphSchema.h"




void UPZ_SkillTreeUIPositionEdGraph::RebuildGraph()
{

	for (int i = Nodes.Num() - 1; i >= 0; i--)
	{
		const auto& EdNode = Nodes[i];
		RemoveNode(EdNode);
	}

	TArray<UPZ_SkillTreeRBaseTreeElement*> Roots;
	TArray<UPZ_SkillTreeRBaseTreeElement*> VisitedNodes;
	SkillTree->GetRootNodes(Roots);

	for (const auto& Node : Roots)
	{
		BuildUINodes(Node, VisitedNodes);
	}

	CompileGraph();
}

void UPZ_SkillTreeUIPositionEdGraph::BuildUINodes(UPZ_SkillTreeRBaseTreeElement* RNode, TArray<UPZ_SkillTreeRBaseTreeElement*>& VisitedNodes)
{
	if (VisitedNodes.Contains(RNode)) return;

	VisitedNodes.Add(RNode);

	if (UPZ_SkillTreeRBaseNode* RBaseNode = Cast<UPZ_SkillTreeRBaseNode>(RNode))
		if (RBaseNode->UINode)
		{
			FAssetSchemaAction_SkillTreeUIPositionGraph_NewSkillNode_FromRNode* NewNodeAction = new FAssetSchemaAction_SkillTreeUIPositionGraph_NewSkillNode_FromRNode(RBaseNode->UINode);
			NewNodeAction->PerformAction(this, NULL, RBaseNode->UINode->UIPosition, false);
		}

	TArray<UPZ_SkillTreeRBaseNode*> NextNodes;
	RNode->GetOutRNodesByClass<UPZ_SkillTreeRBaseNode>(NextNodes);

	for (const auto& NextNode : NextNodes)
	{
		BuildUINodes(NextNode, VisitedNodes);
	}

}


void UPZ_SkillTreeUIPositionEdGraph::CompileGraph()
{
	//find root
	UEdGraphNode* RootNode = nullptr;
	for (const auto& EdNode : Nodes)
	{
		if (UPZ_SkillTreeUIPositionEdNode_UI* UIEdNode = Cast<UPZ_SkillTreeUIPositionEdNode_UI>(EdNode))
		{
			if (UIEdNode->RUINode->IsUIRootNode)
			{
				RootNode = UIEdNode;
				break;
			}
		}
	}

	if (RootNode)
	{
		for (const auto& EdNode : Nodes)
		{
			if (UPZ_SkillTreeUIPositionEdNode_UI* UIEdNode = Cast<UPZ_SkillTreeUIPositionEdNode_UI>(EdNode))
			{
				UIEdNode->CompileError();

				if (!UIEdNode->RUINode->IsUIRootNode)
				{
					UIEdNode->RUINode->UIPosition = FVector2D(UIEdNode->NodePosX - RootNode->NodePosX, UIEdNode->NodePosY - RootNode->NodePosY);
				}
				else
				{
					UIEdNode->RUINode->UIPosition = FVector2D(0.0f, 0.0f);
				}
			}
		}
	}

	SkillTree->UIPositionEdGraph->NotifyGraphChanged();
	SkillTree->NeedCompileUI = false;
}

void UPZ_SkillTreeUIPositionEdGraph::OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent)
{
}













void UPZ_SkillTreeUIPositionEdGraph::NotifyGraphChanged(const FEdGraphEditAction& Action)
{
	Super::NotifyGraphChanged(Action);

	if (!IsValid(SkillTree) || SkillTreeGraph == nullptr) return;


	SkillTree->NeedCompileUI = true;
	SkillTreeGraph->RegenerateMenusAndToolbars();
}












