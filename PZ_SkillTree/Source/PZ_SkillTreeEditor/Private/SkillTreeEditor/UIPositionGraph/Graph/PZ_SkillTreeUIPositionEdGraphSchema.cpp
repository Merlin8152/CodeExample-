// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeEditor/UIPositionGraph/Graph/PZ_SkillTreeUIPositionEdGraphSchema.h"

#include "PZ_UIPositionGraphDrawingConnectionPolicy.h"
#include "PZ_SkillTreeUIPositionEdGraph.h"
#include "../../PZ_SkillTreeGraphEditor.h"
#include "PZ_SkillTree_Editor.h"


#include "../Nodes/PZ_UIPositionEdNodesInclude.h"
#include "PZ_SkillTreeRNodesInclude.h"


#include "EdGraph/EdGraphPin.h"
#include "Framework/Commands/GenericCommands.h"
#include "GraphEditorActions.h"
#include "ScopedTransaction.h"


#include "ToolMenu.h"
#include "EdGraphNode_Comment.h"


#include "SkillTreeEditor/PZ_SkillTreeEditorConstant.h"


UEdGraphNode* FAssetSchemaAction_SkillTreeUIPositionGraph_NewSkillNode_FromRNode::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
	UEdGraphNode* ResultNode = NULL;
	UPZ_SkillTreeUIPositionEdNode_UI* NodeTemplate = NewObject<UPZ_SkillTreeUIPositionEdNode_UI>(ParentGraph);
	if (NodeTemplate != NULL)
	{
		NodeTemplate->Rename(NULL, (UObject*)ParentGraph, REN_NonTransactional);
		NodeTemplate->SetFlags(RF_Transactional);
		NodeTemplate->RUINode = RNode;
		NodeTemplate->RUINode->SetFlags(RF_Transactional);
		ParentGraph->AddNode(NodeTemplate, true, bSelectNewNode);

		NodeTemplate->CreateNewGuid();
		NodeTemplate->PostPlacedNewNode();
		NodeTemplate->AllocateDefaultPins();

		if (!RNode->IsUIRootNode)
		{
			NodeTemplate->SetPosition(Location.X, Location.Y);
		}
		else
		{
			NodeTemplate->SetPosition(0.0f, 0.0f);
		}

		NodeTemplate->AutowireNewNode(FromPin);
		ResultNode = NodeTemplate;

	}

	return ResultNode;
}

UEdGraphNode* FAssetSchemaAction_SkillTreeUIPositionGraph_NewSkillNode_FromRNode::PerformAction(UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2D Location, bool bSelectNewNode)
{
	UEdGraphNode* ResultNode = NULL;


	if (FromPins.Num() > 0)
	{
		ResultNode = PerformAction(ParentGraph, FromPins[0], Location, bSelectNewNode);
	}
	else
	{
		ResultNode = PerformAction(ParentGraph, NULL, Location, bSelectNewNode);
	}

	return ResultNode;
}

void FAssetSchemaAction_SkillTreeUIPositionGraph_NewSkillNode_FromRNode::AddReferencedObjects(FReferenceCollector& Collector)
{
}








//.............................................................................................................//







///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//.......................................................................................................................//

void UPZ_SkillTreeUIPositionEdGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{

}

void UPZ_SkillTreeUIPositionEdGraphSchema::GetGraphNodeContextActions(FGraphContextMenuBuilder& ContextMenuBuilder, ESkillTreeNodeType NodeType) const
{


}



void UPZ_SkillTreeUIPositionEdGraphSchema::GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{


}






void UPZ_SkillTreeUIPositionEdGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{

	Super::CreateDefaultNodesForGraph(Graph);

	// This should only be called on empty graphs
	if (Graph.Nodes.Num() > 0) return;




}







const FPinConnectionResponse UPZ_SkillTreeUIPositionEdGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{

	if (A == nullptr || B == nullptr)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, FText::FromString("Invalid pins"));
	}

	// Make sure the pins are not on the same node
	if (A->GetOwningNode() == B->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, FText::FromString("Both are on the same node"));
	}

	// Compare the directions
	if ((A->Direction == EGPD_Input) && (B->Direction == EGPD_Input))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, FText::FromString("Can't connect input node to input node"));
	}
	else if ((A->Direction == EGPD_Output) && (B->Direction == EGPD_Output))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, FText::FromString("Can't connect output node to output node"));
	}

	// Compare category
	if (A->PinType.PinCategory != B->PinType.PinCategory)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, FText::FromString("Can't connect nodes with different pin category"));
	}

	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, FText::FromString("Connect nodes"));
}

bool UPZ_SkillTreeUIPositionEdGraphSchema::TryCreateConnection(UEdGraphPin* PinA, UEdGraphPin* PinB) const
{
	return Super::TryCreateConnection(PinA, PinB);

}


bool UPZ_SkillTreeUIPositionEdGraphSchema::CreateAutomaticConversionNodeAndConnections(UEdGraphPin* PinA, UEdGraphPin* PinB) const
{
	return true;
}



FConnectionDrawingPolicy* UPZ_SkillTreeUIPositionEdGraphSchema::CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj) const
{
	return new FPZ_UIPositionGraphDrawingConnectionPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements, InGraphObj);
}






FLinearColor UPZ_SkillTreeUIPositionEdGraphSchema::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
	return FLinearColor::White;
}

FPinConnectionResponse UPZ_SkillTreeUIPositionEdGraphSchema::MovePinLinks(UEdGraphPin& MoveFromPin, UEdGraphPin& MoveToPin, bool bIsIntermediateMove, bool bNotifyLinkedNodes) const
{
	//TODO...
	return FPinConnectionResponse();
}


FPinConnectionResponse UPZ_SkillTreeUIPositionEdGraphSchema::CopyPinLinks(UEdGraphPin& CopyFromPin, UEdGraphPin& CopyToPin, bool bIsIntermediateCopy) const
{
	//TODO...
	return FPinConnectionResponse();
}

void UPZ_SkillTreeUIPositionEdGraphSchema::BreakNodeLinks(UEdGraphNode& TargetNode) const
{
	const FScopedTransaction Transaction(FText::FromString("BreakNodeLinks"));

	Super::BreakNodeLinks(TargetNode);
}

void UPZ_SkillTreeUIPositionEdGraphSchema::BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const
{
	const FScopedTransaction Transaction(FText::FromString("BreakPinLinks"));

	Super::BreakPinLinks(TargetPin, bSendsNodeNotifcation);
}

void UPZ_SkillTreeUIPositionEdGraphSchema::BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const
{
	const FScopedTransaction Transaction(FText::FromString("BreakPinLinks"));

	Super::BreakSinglePinLink(SourcePin, TargetPin);
}

UEdGraphPin* UPZ_SkillTreeUIPositionEdGraphSchema::DropPinOnNode(UEdGraphNode* InTargetNode, const FName& InSourcePinName, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection) const
{

	return nullptr;
}

bool UPZ_SkillTreeUIPositionEdGraphSchema::SupportsDropPinOnNode(UEdGraphNode* InTargetNode, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection, FText& OutErrorMessage) const
{
	return false;
}






TSharedPtr<FEdGraphSchemaAction> UPZ_SkillTreeUIPositionEdGraphSchema::GetCreateCommentAction() const
{
	return nullptr;
}





void UPZ_SkillTreeUIPositionEdGraphSchema::DroppedAssetsOnGraph(const TArray<FAssetData>& Assets, const FVector2D& GraphPosition, UEdGraph* Graph) const
{
	//TODO...
}

void UPZ_SkillTreeUIPositionEdGraphSchema::DroppedAssetsOnNode(const TArray<FAssetData>& Assets, const FVector2D& GraphPosition, UEdGraphNode* Node) const
{
	//TODO...
}






bool UPZ_SkillTreeUIPositionEdGraphSchema::IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const
{
	return CurrentCacheRefreshID != InVisualizationCacheID;
}

int32 UPZ_SkillTreeUIPositionEdGraphSchema::GetCurrentVisualizationCacheID() const
{
	return CurrentCacheRefreshID;
}

void UPZ_SkillTreeUIPositionEdGraphSchema::ForceVisualizationCacheClear() const
{
	++CurrentCacheRefreshID;
}

