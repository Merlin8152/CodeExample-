// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "PZ_SkillTreeNodesInfo.h"
#include "PZ_SkillTreeStructureEdGraphSchema.generated.h"



class UPZ_SkillTreeEdNode_Base;
class UPZ_SkillTreeEdNode_Edge;



USTRUCT()
struct FAssetSchemaAction_SkillTreeGraph_NewNode : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();


public:

	FAssetSchemaAction_SkillTreeGraph_NewNode()
		: NodeTemplate(nullptr)
	{
	}


	FAssetSchemaAction_SkillTreeGraph_NewNode(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping)
		: FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping), NodeTemplate(nullptr)
	{
	}


public:

	//~ Begin FEdGraphSchemaAction Interface
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2D Location, bool bSelectNewNode = true) override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	//~ End FEdGraphSchemaAction Interface

	UPZ_SkillTreeEdNode_Base* NodeTemplate = nullptr;
};


USTRUCT()
struct FAssetSchemaAction_SkillTreeGraph_NewSubNode : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();


public:

	FAssetSchemaAction_SkillTreeGraph_NewSubNode()
		: NodeTemplate(nullptr)
	{
	}

	FAssetSchemaAction_SkillTreeGraph_NewSubNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : 
		FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping),
		NodeTemplate(nullptr), ParentNode(nullptr)
	{
	}


public:

	//~ Begin FEdGraphSchemaAction Interface
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2D Location, bool bSelectNewNode = true) override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	//~ End FEdGraphSchemaAction Interface


	UPZ_SkillTreeEdNode_Base* NodeTemplate = nullptr;
	UPZ_SkillTreeEdNode_Base* ParentNode = nullptr;
};


USTRUCT()
struct FNewComment_SkillTreeGraphSchemaAction : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();

public:

	FNewComment_SkillTreeGraphSchemaAction() : FEdGraphSchemaAction() {}
	FNewComment_SkillTreeGraphSchemaAction(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, int32 InGrouping) :
		FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping)
	{
	}


public:

	//~ Begin FEdGraphSchemaAction Interface
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	//~ End FEdGraphSchemaAction Interface

};




USTRUCT()
struct FAssetSchemaAction_SkillTreeGraph_NewEdge : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();

public:

	FAssetSchemaAction_SkillTreeGraph_NewEdge() : NodeTemplate(nullptr) {}

	FAssetSchemaAction_SkillTreeGraph_NewEdge(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping)	: 
		FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping), NodeTemplate(nullptr)
	{
	}

public:

	//~ Begin FEdGraphSchemaAction Interface
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	//~ End FEdGraphSchemaAction Interface


	UPZ_SkillTreeEdNode_Edge* NodeTemplate = nullptr;
};







UCLASS()
class UPZ_SkillTreeEdGraphSchema : public UEdGraphSchema
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




	template<class T, class R>
	static void AddAction(const FText& Category, const FText& Title, const FText& Tooltip, TArray<TSharedPtr<FEdGraphSchemaAction> >& OutActions, UEdGraph* OwnerOfTemporaries);

	template<class T, class R>
	static void AddAction_SubNode(const FText& Category, const FText& Title, const FText& Tooltip, UPZ_SkillTreeEdNode_Base* InParentNode, TArray<TSharedPtr<FEdGraphSchemaAction> >& OutActions, UEdGraph* OwnerOfTemporaries);



private:

	static int32 CurrentCacheRefreshID;

};

int32 UPZ_SkillTreeEdGraphSchema::CurrentCacheRefreshID = 0;
