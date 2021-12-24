// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeEditor/StructureGraph/Graph/PZ_SkillTreeStructureEdGraphSchema.h"

#include "PZ_StructureGraphDrawingConnectionPolicy.h"
#include "PZ_SkillTreeStructureEdGraph.h"
#include "../../PZ_SkillTreeGraphEditor.h"
#include "PZ_SkillTree_Editor.h"


#include "../PZ_EdNodesInclude.h"
#include "PZ_SkillTreeRNodesInclude.h"


#include "EdGraph/EdGraphPin.h"
#include "Framework/Commands/GenericCommands.h"
#include "GraphEditorActions.h"
#include "ScopedTransaction.h"


#include "ToolMenu.h"
#include "EdGraphNode_Comment.h"


#include "SkillTreeEditor/PZ_SkillTreeEditorConstant.h"




UEdGraphNode* FAssetSchemaAction_SkillTreeGraph_NewNode::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
	UEdGraphNode* ResultNode = NULL;

	if (NodeTemplate != NULL)
	{
		// set outer to be the graph so it doesn't go away
		NodeTemplate->Rename(NULL, (UObject*)ParentGraph, REN_NonTransactional);
		ParentGraph->AddNode(NodeTemplate, true, bSelectNewNode);

		if (UPZ_SkillTreeEdGraph* LPZ_EdGraph = Cast<UPZ_SkillTreeEdGraph>(ParentGraph))
		{
			LPZ_EdGraph->SkillTree->NeedToRebuild = true;
			LPZ_EdGraph->SkillTreeGraph->RegenerateMenusAndToolbars();
		}

		

		NodeTemplate->NodePosX = Location.X;
		NodeTemplate->NodePosY = Location.Y;

		NodeTemplate->CreateNewGuid();
		NodeTemplate->PostPlacedNewNode();
		NodeTemplate->AllocateDefaultPins();
		NodeTemplate->AutowireNewNode(FromPin);

		NodeTemplate->SetFlags(RF_Transactional);
		NodeTemplate->RNode->SetFlags(RF_Transactional);

		ResultNode = NodeTemplate;
	}

	return ResultNode;
}

UEdGraphNode* FAssetSchemaAction_SkillTreeGraph_NewNode::PerformAction(UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2D Location, bool bSelectNewNode)
{
	UEdGraphNode* ResultNode = NULL;

	if (FromPins.Num() > 0)
	{
		ResultNode = PerformAction(ParentGraph, FromPins[0], Location, bSelectNewNode);

		// Try autowiring the rest of the pins
		for (int32 Index = 1; Index < FromPins.Num(); ++Index)
		{
			ResultNode->AutowireNewNode(FromPins[Index]);
		}
	}
	else
	{
		ResultNode = PerformAction(ParentGraph, NULL, Location, bSelectNewNode);
	}

	return ResultNode;
}

void FAssetSchemaAction_SkillTreeGraph_NewNode::AddReferencedObjects(FReferenceCollector& Collector)
{
	FEdGraphSchemaAction::AddReferencedObjects(Collector);
	Collector.AddReferencedObject(NodeTemplate);
}






UEdGraphNode* FAssetSchemaAction_SkillTreeGraph_NewSubNode::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
	if (ParentNode->AddSubNode(NodeTemplate, ParentGraph))
		if (UPZ_SkillTreeEdGraph* LPZ_EdGraph = Cast<UPZ_SkillTreeEdGraph>(ParentGraph))
		{
			LPZ_EdGraph->SkillTree->NeedToRebuild = true;
			LPZ_EdGraph->SkillTreeGraph->RegenerateMenusAndToolbars();
		}

	return NULL;
}

UEdGraphNode* FAssetSchemaAction_SkillTreeGraph_NewSubNode::PerformAction(class UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2D Location, bool bSelectNewNode)
{
	return PerformAction(ParentGraph, NULL, Location, bSelectNewNode);
}

void FAssetSchemaAction_SkillTreeGraph_NewSubNode::AddReferencedObjects(FReferenceCollector& Collector)
{
	FEdGraphSchemaAction::AddReferencedObjects(Collector);

	// These don't get saved to disk, but we want to make sure the objects don't get GC'd while the action array is around
	Collector.AddReferencedObject(NodeTemplate);
	Collector.AddReferencedObject(ParentNode);
}




//...........................FNewComment_SkillTreeGraphSchemaAction.........................................................//

UEdGraphNode* FNewComment_SkillTreeGraphSchemaAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
	UEdGraphNode_Comment* CommentTemplate = NewObject<UEdGraphNode_Comment>();

	FVector2D SpawnLocation = Location;
	FSlateRect Bounds;
	if (UPZ_SkillTreeEdGraph* LEdGraph = Cast<UPZ_SkillTreeEdGraph>(ParentGraph))
	{
		if (LEdGraph->SkillTreeGraph->GetSelectedNodesBounds(Bounds, 50.0f))
		{
			CommentTemplate->SetBounds(Bounds);
			SpawnLocation.X = CommentTemplate->NodePosX;
			SpawnLocation.Y = CommentTemplate->NodePosY;
		}
	}


	return FEdGraphSchemaAction_NewNode::SpawnNodeFromTemplate<UEdGraphNode_Comment>(ParentGraph, CommentTemplate, SpawnLocation, bSelectNewNode);
}

//.............................................................................................................//






//.......................................FAssetSchemaAction_SkillTreeGraph_NewEdge.........................................................//

UEdGraphNode* FAssetSchemaAction_SkillTreeGraph_NewEdge::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
	UEdGraphNode* ResultNode = NULL;

	if (NodeTemplate != NULL)
	{


		// set outer to be the graph so it doesn't go away
		NodeTemplate->Rename(NULL, (UObject*)ParentGraph, REN_NonTransactional);
		ParentGraph->AddNode(NodeTemplate, true, bSelectNewNode);

		NodeTemplate->CreateNewGuid();
		NodeTemplate->PostPlacedNewNode();
		NodeTemplate->AllocateDefaultPins();
		NodeTemplate->AutowireNewNode(FromPin);

		NodeTemplate->NodePosX = Location.X;
		NodeTemplate->NodePosY = Location.Y;

		NodeTemplate->SetFlags(RF_Transactional);
		NodeTemplate->REdgeNode->SetFlags(RF_Transactional);

		ResultNode = NodeTemplate;
	}

	return ResultNode;
}

void FAssetSchemaAction_SkillTreeGraph_NewEdge::AddReferencedObjects(FReferenceCollector& Collector)
{
	FEdGraphSchemaAction::AddReferencedObjects(Collector);
	Collector.AddReferencedObject(NodeTemplate);
}

//.............................................................................................................//




template<class T, class R>
inline void UPZ_SkillTreeEdGraphSchema::AddAction(const FText& Category, const FText& Title, const FText& Tooltip, TArray<TSharedPtr<FEdGraphSchemaAction>>& OutActions, UEdGraph* OwnerOfTemporaries)
{
	TSharedPtr<FAssetSchemaAction_SkillTreeGraph_NewNode> NewAction = TSharedPtr<FAssetSchemaAction_SkillTreeGraph_NewNode>(new FAssetSchemaAction_SkillTreeGraph_NewNode(Category, Title, Tooltip, 0));
	NewAction->NodeTemplate = NewObject<T>((UObject*)OwnerOfTemporaries);
	NewAction->NodeTemplate->RNode = NewObject<R>(NewAction->NodeTemplate);

	OutActions.Add(NewAction);
}

template<class T, class R>
void UPZ_SkillTreeEdGraphSchema::AddAction_SubNode(const FText& Category, const FText& Title, const FText& Tooltip, UPZ_SkillTreeEdNode_Base* InParentNode, TArray<TSharedPtr<FEdGraphSchemaAction>>& OutActions, UEdGraph* OwnerOfTemporaries)
{
	TSharedPtr<FAssetSchemaAction_SkillTreeGraph_NewSubNode> NewAction = TSharedPtr<FAssetSchemaAction_SkillTreeGraph_NewSubNode>(new FAssetSchemaAction_SkillTreeGraph_NewSubNode(Category, Title, Tooltip, 0));
	NewAction->NodeTemplate = NewObject<T>((UObject*)OwnerOfTemporaries);
	NewAction->NodeTemplate->RNode = NewObject<R>(NewAction->NodeTemplate);

	NewAction->ParentNode = InParentNode;
	OutActions.Add(NewAction);
}






///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//.......................................................................................................................//

void UPZ_SkillTreeEdGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{

	TArray<TSharedPtr<FEdGraphSchemaAction> > Actions;

	AddAction<UPZ_SkillTreeEdNode_ActiveSkill, UPZ_SkillTreeRActiveSkillNode>(FText::FromString("Nodes"), FText::FromString("Add Active Skill Node"), FText::FromString("Add Active Skill Node"), Actions, ContextMenuBuilder.OwnerOfTemporaries);
	AddAction<UPZ_SkillTreeEdNode_PassiveSkill, UPZ_SkillTreeRPassiveSkillNode>(FText::FromString("Nodes"), FText::FromString("Add Passive Skill Node"), FText::FromString("Add Passive Skill Node"), Actions, ContextMenuBuilder.OwnerOfTemporaries);
	AddAction<UPZ_SkillTreeEdNode_Event, UPZ_SkillTreeREventNode>(FText::FromString("Nodes"), FText::FromString("Add Event Node"), FText::FromString("Add Event Node"), Actions, ContextMenuBuilder.OwnerOfTemporaries);
	AddAction<UPZ_SkillTreeEdNode_Switcher, UPZ_SkillTreeRSwitcherNode>(FText::FromString("Nodes"), FText::FromString("Add Switcher Node"), FText::FromString("Add Switcher Node"), Actions, ContextMenuBuilder.OwnerOfTemporaries);
	AddAction<UPZ_SkillTreeEdNode_Custom, UPZ_SkillTreeRCustomNode>(FText::FromString("Nodes"), FText::FromString("Add Custom Node"), FText::FromString("Add Custom Node"), Actions, ContextMenuBuilder.OwnerOfTemporaries);
	AddAction<UPZ_SkillTreeEdNode_Connection, UPZ_SkillTreeRConnectionNode>(FText::FromString("Nodes"), FText::FromString("Add Connection Node"), FText::FromString("Add Connection Node"), Actions, ContextMenuBuilder.OwnerOfTemporaries);


	for (TSharedPtr<FEdGraphSchemaAction> Action : Actions)
	{
		ContextMenuBuilder.AddAction(Action);
	}
}

void UPZ_SkillTreeEdGraphSchema::GetGraphNodeContextActions(FGraphContextMenuBuilder& ContextMenuBuilder, ESkillTreeNodeType NodeType) const
{
	TArray<TSharedPtr<FEdGraphSchemaAction> > Actions;

	UPZ_SkillTreeEdNode_Base* ParentNode = Cast<UPZ_SkillTreeEdNode_Base>(ContextMenuBuilder.SelectedObjects[0]);

	if (ParentNode)
	{

		switch (NodeType)
		{

		case ESkillTreeNodeType::ConditionSkillNode:
			AddAction_SubNode<UPZ_SkillTreeEdNode_Condition, UPZ_SkillTreeRConditionNode>
				(FText::FromString("Unlock Condition"),
					FText::FromString("Add unlock Condition to Node"),
					FText::FromString("Condition to unlock skill"),
					ParentNode,
					Actions, ContextMenuBuilder.OwnerOfTemporaries);
			break;

		case ESkillTreeNodeType::SkillActionNode:
			AddAction_SubNode<UPZ_SkillTreeEdNode_SkillAction, UPZ_SkillTreeRSkillActionNode>
				(FText::FromString("Unlock Skill Action"),
					FText::FromString("Add unlock Skill Action to Node"),
					FText::FromString("Execute Skill Action on unlock skill"),
					ParentNode,
					Actions, ContextMenuBuilder.OwnerOfTemporaries);
			break;

		default:
			break;
		} 


	}



	for (TSharedPtr<FEdGraphSchemaAction> Action : Actions)
	{
		ContextMenuBuilder.AddAction(Action);
	}

}



void UPZ_SkillTreeEdGraphSchema::GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{

	FToolMenuSection& Section = Menu->AddSection("GenericGraphAssetGraphSchemaNodeActions", FText::FromString("Node Actions"));


	Section.AddMenuEntry(FGenericCommands::Get().Delete);
	Section.AddMenuEntry(FGenericCommands::Get().Cut);
	Section.AddMenuEntry(FGenericCommands::Get().Copy);
	Section.AddMenuEntry(FGenericCommands::Get().Paste);
	Section.AddMenuEntry(FGenericCommands::Get().Duplicate);
	Section.AddMenuEntry(FGenericCommands::Get().Rename);
	Section.AddMenuEntry(FGenericCommands::Get().SelectAll);

	if (Context->Pin)
	{
		Section.AddMenuEntry(FGraphEditorCommands::Get().BreakPinLinks);
	}
	else
	{
		Section.AddMenuEntry(FGraphEditorCommands::Get().BreakNodeLinks);
	}


	Super::GetContextMenuActions(Menu, Context);

}






void UPZ_SkillTreeEdGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{

	Super::CreateDefaultNodesForGraph(Graph);

	// This should only be called on empty graphs
	if (Graph.Nodes.Num() > 0) return;

}







const FPinConnectionResponse UPZ_SkillTreeEdGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
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

	const UPZ_SkillTreeEdNode_Base* SourceNode = CastChecked<UPZ_SkillTreeEdNode_Base>(A->GetOwningNode());
	const UPZ_SkillTreeEdNode_Base* TargetNode = CastChecked<UPZ_SkillTreeEdNode_Base>(B->GetOwningNode());
	if (!IsValid(SourceNode) || !IsValid(TargetNode))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, FText::FromString("Invalid pins"));
	}


	if (SourceNode->HasOutputConnectionToNode(TargetNode) || TargetNode->HasOutputConnectionToNode(SourceNode))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, FText::FromString("Connection between nodes already made"));
	}



	if (A->PinType.PinCategory == FPZ_SkillTreeEditorConstant::PinCategory_Second)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, FText::FromString("Connect nodes"));
	}
	else
	{
		FText ErrorMessage;
		bool CreateEdge = false;
		if (SourceNode->CanCreateConnectionTo(TargetNode, ErrorMessage, CreateEdge))
		{
			if (CreateEdge)
			{
				return FPinConnectionResponse(CONNECT_RESPONSE_MAKE_WITH_CONVERSION_NODE, FText::FromString("Connect nodes with edge"));
			}
			else
			{

				return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, FText::FromString("Connect nodes"));
			}
		}
		else
		{
			return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, ErrorMessage);
		}
	}

}

bool UPZ_SkillTreeEdGraphSchema::TryCreateConnection(UEdGraphPin* PinA, UEdGraphPin* PinB) const
{
	if (PinA && PinB)
	{
		return Super::TryCreateConnection(PinA, PinB);
	}

	return false;
}


bool UPZ_SkillTreeEdGraphSchema::CreateAutomaticConversionNodeAndConnections(UEdGraphPin* PinA, UEdGraphPin* PinB) const
{
	UPZ_SkillTreeEdNode_Base* NodeA = Cast<UPZ_SkillTreeEdNode_Base>(PinA->GetOwningNode());
	UPZ_SkillTreeEdNode_Base* NodeB = Cast<UPZ_SkillTreeEdNode_Base>(PinB->GetOwningNode());

	if (NodeA == nullptr || NodeB == nullptr) return false;


	FVector2D InitPos((NodeA->NodePosX + NodeB->NodePosX) / 2, (NodeA->NodePosY + NodeB->NodePosY) / 2);

	// TODO разные варианты Edge
	FAssetSchemaAction_SkillTreeGraph_NewEdge Action;
	Action.NodeTemplate = NewObject<UPZ_SkillTreeEdNode_Edge>(NodeA->GetGraph());
	Action.NodeTemplate->REdgeNode = NewObject<UPZ_SkillTreeREdgeNode>(Action.NodeTemplate);
	UPZ_SkillTreeEdNode_Edge* EdgeNode = Cast<UPZ_SkillTreeEdNode_Edge>(Action.PerformAction(NodeA->GetGraph(), nullptr, InitPos, false));



	if (PinA->Direction == EGPD_Output)
	{
		EdgeNode->CreateConnections(PinA, PinB);
	}
	else
	{
		EdgeNode->CreateConnections(PinB, PinA);
	}


	return true;

}



FConnectionDrawingPolicy* UPZ_SkillTreeEdGraphSchema::CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj) const
{
	return new FPZ_GraphDrawingConnectionPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements, InGraphObj);
}






FLinearColor UPZ_SkillTreeEdGraphSchema::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
	return FLinearColor::White;
}

FPinConnectionResponse UPZ_SkillTreeEdGraphSchema::MovePinLinks(UEdGraphPin& MoveFromPin, UEdGraphPin& MoveToPin, bool bIsIntermediateMove, bool bNotifyLinkedNodes) const
{
	//TODO...
	return FPinConnectionResponse();
}


FPinConnectionResponse UPZ_SkillTreeEdGraphSchema::CopyPinLinks(UEdGraphPin& CopyFromPin, UEdGraphPin& CopyToPin, bool bIsIntermediateCopy) const
{
	//TODO...
	return FPinConnectionResponse();
}

void UPZ_SkillTreeEdGraphSchema::BreakNodeLinks(UEdGraphNode& TargetNode) const
{
	const FScopedTransaction Transaction(FText::FromString("BreakNodeLinks"));

	Super::BreakNodeLinks(TargetNode);
}

void UPZ_SkillTreeEdGraphSchema::BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const
{
	const FScopedTransaction Transaction(FText::FromString("BreakPinLinks"));

	Super::BreakPinLinks(TargetPin, bSendsNodeNotifcation);
}

void UPZ_SkillTreeEdGraphSchema::BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const
{
	const FScopedTransaction Transaction(FText::FromString("BreakPinLinks"));

	Super::BreakSinglePinLink(SourcePin, TargetPin);
}

UEdGraphPin* UPZ_SkillTreeEdGraphSchema::DropPinOnNode(UEdGraphNode* InTargetNode, const FName& InSourcePinName, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection) const
{
	UPZ_SkillTreeEdNode_Base* EdNode = Cast<UPZ_SkillTreeEdNode_Base>(InTargetNode);
	switch (InSourcePinDirection)
	{
	case EGPD_Input:
		return EdNode->GetOutputPin(InSourcePinType.PinCategory);
	case EGPD_Output:
		return EdNode->GetInputPin(InSourcePinType.PinCategory);
	default:
		return nullptr;
	}
}

bool UPZ_SkillTreeEdGraphSchema::SupportsDropPinOnNode(UEdGraphNode* InTargetNode, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection, FText& OutErrorMessage) const
{
	return Cast<UPZ_SkillTreeEdNode_Base>(InTargetNode) != nullptr;
}






TSharedPtr<FEdGraphSchemaAction> UPZ_SkillTreeEdGraphSchema::GetCreateCommentAction() const
{

	return TSharedPtr<FEdGraphSchemaAction>(static_cast<FEdGraphSchemaAction*>(new FNewComment_SkillTreeGraphSchemaAction));
}





void UPZ_SkillTreeEdGraphSchema::DroppedAssetsOnGraph(const TArray<FAssetData>& Assets, const FVector2D& GraphPosition, UEdGraph* Graph) const
{
	//TODO...
}

void UPZ_SkillTreeEdGraphSchema::DroppedAssetsOnNode(const TArray<FAssetData>& Assets, const FVector2D& GraphPosition, UEdGraphNode* Node) const
{
	//TODO...
}






bool UPZ_SkillTreeEdGraphSchema::IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const
{
	return CurrentCacheRefreshID != InVisualizationCacheID;
}

int32 UPZ_SkillTreeEdGraphSchema::GetCurrentVisualizationCacheID() const
{
	return CurrentCacheRefreshID;
}

void UPZ_SkillTreeEdGraphSchema::ForceVisualizationCacheClear() const
{
	++CurrentCacheRefreshID;
}

