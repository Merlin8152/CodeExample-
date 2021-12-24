// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "../PZ_SkillTreeNodeInterface.h"
#include "PZ_SkillTreeNodesInfo.h"
#include "PZ_SkillTreeEdNode_Edge.generated.h"



class UPZ_SkillTree_Editor;

 
UCLASS()
class UPZ_SkillTreeEdNode_Edge : public UEdGraphNode,
								 public IPZ_SkillTreeNodeInterface
{
	GENERATED_BODY()



public:

	virtual void AllocateDefaultPins() override;


	virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;

	virtual void PrepareForCopying() override;




	////DialogueNodeInterface begin///////
	virtual ESkillTreeNodeType GetNodeType() const override;


	virtual UEdGraphPin* GetInputPin(const FName& PinCategory = "") const override;
	virtual UEdGraphPin* GetOutputPin(const FName& PinCategory = "") const override;




	virtual void CompileThisNodeInfo(UPZ_SkillTree_Editor* SkillTree) override;
	virtual bool IsNeedCompile() override;

	virtual void OnNodeDoubleClicked() override;
	virtual void OnChangedProperties(const FName& PropertyName) const override;
	////DialogueNodeInterface end/////////



	UEdGraphNode* GetStartNode();
	UEdGraphNode* GetEndNode();



	void CreateConnections(UEdGraphPin* Start, UEdGraphPin* End);



	//Blueprint values
public:

	UPROPERTY(VisibleAnywhere, Instanced)
		class UPZ_SkillTreeREdgeNode* REdgeNode = nullptr;
	
};
