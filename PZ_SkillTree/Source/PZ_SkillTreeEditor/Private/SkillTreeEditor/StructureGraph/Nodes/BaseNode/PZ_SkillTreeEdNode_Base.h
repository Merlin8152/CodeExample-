// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "SkillTreeEditor/StructureGraph/Nodes/PZ_SkillTreeNodeInterface.h"
#include "PZ_SkillTreeNodesInfo.h"

#include "PZ_SkillTreeEdNode_Base.generated.h"



class UPZ_SkillTree_Editor;


UCLASS()
class UPZ_SkillTreeEdNode_Base : public UEdGraphNode,
								 public IPZ_SkillTreeNodeInterface
{
	GENERATED_BODY()


//constructor
public:

	UPZ_SkillTreeEdNode_Base();

	UPROPERTY()
		UPZ_SkillTreeEdNode_Base* ParentNode;
	UPROPERTY()
		TArray<UPZ_SkillTreeEdNode_Base*> SubNodes;
	UPROPERTY()
		int32 CopySubNodeIndex;

//c++ public methods
public:

	virtual void AllocateDefaultPins() override;
	virtual void PrepareForCopying() override;
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;



	////SkillTreeNodeInterface begin///////
	virtual ESkillTreeNodeType GetNodeType() const override;


	virtual UEdGraphPin* GetInputPin(const FName& PinCategory) const override;
	virtual UEdGraphPin* GetOutputPin(const FName& PinCategory) const override;



	virtual void CompileThisNodeInfo(UPZ_SkillTree_Editor* SkillTree) override;
	virtual void CompileError(UPZ_SkillTree_Editor* SkillTree) {};

	virtual bool IsNeedCompile() override;

	virtual void OnNodeDoubleClicked() override;
	virtual void OnChangedProperties(const FName& PropertyName) const override;
	////SkillTreeNodeInterface end/////////





	/////////////////overridable for other nodes///////////////////////////

	//properties/visual
	virtual bool IsHaveUINode() const;

	virtual bool CanDuplicateNode() const override;
	virtual bool CanUserDeleteNode() const override;
	virtual bool CanSplitPin(const UEdGraphPin* Pin) const override;
	virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* Schema) const override;


	virtual bool CanCreateConnectionTo(const UPZ_SkillTreeEdNode_Base* ToNode, FText& ErrorMessage, bool& CreateEdge) const;


	/////////////////////////////////////////////////////////

	virtual bool CanContainsSubNode(UClass* SubNodeClass);

	void SetPosition(int32 X, int32 Y);
	bool HasOutputConnectionToNode(const UEdGraphNode* TargetNode) const;



	bool AddSubNode(UPZ_SkillTreeEdNode_Base* SubNode, class UEdGraph* ParentGraph);
	void RemoveSubNode(UPZ_SkillTreeEdNode_Base* SubNode);
	virtual void RemoveAllSubNodes();
	virtual void OnSubNodeRemoved(UPZ_SkillTreeEdNode_Base* SubNode);
	virtual void OnSubNodeAdded(UPZ_SkillTreeEdNode_Base* SubNode);
	virtual void DestroyNode() override;


	bool IsHaveInConnection(const FName& PinCategory);
	bool IsHaveOutConnection(const FName& PinCategory);

	bool IsSubNode() const;


//c++ public values
public:

	class SPZ_SkillTreeSNode_Base* SEdNode;



//Blueprint values
public:

	/*
	здесь хранятся компилируемые настройки ноды. Могут быть модифицированны во время CompileThisNodeInfo
	экземпляр класса создается в EdGraphSchema при создании ноды
	настройки чисто для редактора хранятся тоже в RNode, но вырезаются после компиляции
	*/
	UPROPERTY(VisibleAnywhere, Instanced)
		class UPZ_SkillTreeRBaseNode* RNode = nullptr;

};
