// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "PZ_SkillTreeNodesInfo.h"
#include "PZ_SkillTreeUIPositionEdGraphSchema.generated.h"



class UPZ_SkillTreeUIPositionEdNode_Base;
class UPZ_SkillTreeRSkillNode;
class UPZ_SkillTreeRUINode;

USTRUCT()
struct FAssetSchemaAction_SkillTreeUIPositionGraph_NewSkillNode_FromRNode : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();

public:


	FAssetSchemaAction_SkillTreeUIPositionGraph_NewSkillNode_FromRNode()
		: RNode(nullptr)
	{
	}


	FAssetSchemaAction_SkillTreeUIPositionGraph_NewSkillNode_FromRNode(UPZ_SkillTreeRUINode* InRNode)
		: FEdGraphSchemaAction(), RNode(InRNode)
	{
	}

	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2D Location, bool bSelectNewNode = true) override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;


	UPZ_SkillTreeRUINode* RNode;
};












UCLASS()
class UPZ_SkillTreeUIPositionEdGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()

public:

	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	virtual void GetGraphNodeContextActions(FGraphContextMenuBuilder& ContextMenuBuilder, ESkillTreeNodeType NodeType) const;

	virtual void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;


	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;





	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
	virtual bool TryCreateConnection(UEdGraphPin* PinA, UEdGraphPin* PinB) const override;
	virtual bool CreateAutomaticConversionNodeAndConnections(UEdGraphPin* PinA, UEdGraphPin* PinB) const override;
	virtual class FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;





	virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;

	FPinConnectionResponse MovePinLinks(
		UEdGraphPin& MoveFromPin,
		UEdGraphPin& MoveToPin,
		bool bIsIntermediateMove = false,
		bool bNotifyLinkedNodes = false
	) const override;


	FPinConnectionResponse CopyPinLinks(UEdGraphPin& CopyFromPin, UEdGraphPin& CopyToPin, bool bIsIntermediateCopy = false) const override;

	virtual void BreakNodeLinks(UEdGraphNode& TargetNode) const override;

	virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const override;

	virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;


	virtual UEdGraphPin* DropPinOnNode(UEdGraphNode* InTargetNode, const FName& InSourcePinName, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection) const override;
	virtual bool SupportsDropPinOnNode(UEdGraphNode* InTargetNode, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection, FText& OutErrorMessage) const override;





	virtual TSharedPtr<FEdGraphSchemaAction> GetCreateCommentAction() const override;



	virtual void DroppedAssetsOnGraph(const TArray<FAssetData>& Assets, const FVector2D& GraphPosition, UEdGraph* Graph) const override;
	virtual void DroppedAssetsOnNode(const TArray<FAssetData>& Assets, const FVector2D& GraphPosition, UEdGraphNode* Node) const override;




	virtual bool IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const override;
	virtual int32 GetCurrentVisualizationCacheID() const override;
	virtual void ForceVisualizationCacheClear() const override;







private:

	static int32 CurrentCacheRefreshID;

};

int32 UPZ_SkillTreeUIPositionEdGraphSchema::CurrentCacheRefreshID = 0;
