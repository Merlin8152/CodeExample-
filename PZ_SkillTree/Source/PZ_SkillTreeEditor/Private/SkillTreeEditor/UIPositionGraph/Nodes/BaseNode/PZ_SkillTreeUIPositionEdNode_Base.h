// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "SkillTreeEditor/UIPositionGraph/Nodes/PZ_SkillTreeUIPositionNodeInterface.h"
#include "PZ_SkillTreeNodesInfo.h"

#include "PZ_SkillTreeUIPositionEdNode_Base.generated.h"



class UPZ_SkillTree_Editor;


UCLASS()
class UPZ_SkillTreeUIPositionEdNode_Base : public UEdGraphNode,
								 public IPZ_SkillTreeUIPositionNodeInterface
{
	GENERATED_BODY()


//constructor
public:

	UPZ_SkillTreeUIPositionEdNode_Base();


//c++ public methods
public:

	virtual void AllocateDefaultPins() override;
	virtual void PrepareForCopying() override;
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;

	virtual void CompileError() {};

	////SkillTreeNodeInterface begin///////
	virtual ESkillTreeNodeType GetNodeType() const override;


	virtual UEdGraphPin* GetInputPin(const FName& PinCategory) const override;
	virtual UEdGraphPin* GetOutputPin(const FName& PinCategory) const override;



	//virtual void CompileThisNodeInfo(UPZ_SkillTree_Editor* SkillTree) override;


	virtual void OnNodeDoubleClicked() override;
	virtual void OnChangedProperties(const FName& PropertyName) const override;
	////SkillTreeNodeInterface end/////////





	/////////////////overridable for other nodes///////////////////////////

	//properties/visual
	virtual bool CanDuplicateNode() const override;
	virtual bool CanUserDeleteNode() const override;
	virtual bool CanSplitPin(const UEdGraphPin* Pin) const override;
	virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* Schema) const override;


	virtual bool CanCreateConnectionTo(const UPZ_SkillTreeUIPositionEdNode_Base* ToNode, FText& ErrorMessage, bool& CreateEdge) const;


	/////////////////////////////////////////////////////////

	virtual bool CanContainsSubNode(UClass* SubNodeClass);

	void SetPosition(int32 X, int32 Y);
	bool HasOutputConnectionToNode(const UEdGraphNode* TargetNode) const;




	virtual void DestroyNode() override;


//c++ public values
public:

	class SPZ_SkillTreeUIPositionSNode_Base* SEdNode;



//Blueprint values
public:

	/*
	здесь хранятся ссылка на  компилируемые настройки ноды
	*/
	UPROPERTY(VisibleAnywhere)
		class UPZ_SkillTreeRUINode* RUINode = nullptr;

};
