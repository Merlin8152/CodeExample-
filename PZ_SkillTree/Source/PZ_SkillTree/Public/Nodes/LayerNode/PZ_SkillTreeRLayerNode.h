// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Nodes/BaseNode/PZ_SkillTreeRBaseNode.h"
#include "Nodes/SkillActionNode/PZ_SkillTreeRSkillActionNode.h"
#include "Nodes/ConditionNode/PZ_SkillTreeRConditionNode.h"
#include "PZ_SkillTreeRLayerNode.generated.h"

/**
 * 
 */
UCLASS()
class PZ_SKILLTREE_API UPZ_SkillTreeRLayerNode : public UPZ_SkillTreeRBaseNode
{
	GENERATED_BODY()

	
//Constructor
public:

	UPZ_SkillTreeRLayerNode();


//c++ public methods
public:

	virtual bool OnExecute(UPZ_SkillTreeContext* SkillTreeContext) override;



	//......................................................................................................//



//Blueprint values
public:

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced)
	//	TArray<class UPZ_SkillTreeCondition*> SendConditionEvents;

	UPROPERTY (BlueprintReadOnly)
		UPZ_SkillTreeRConditionNode* ConditionNode = nullptr;

	UPROPERTY (BlueprintReadOnly)
		UPZ_SkillTreeRSkillActionNode* SkillActionNode = nullptr;

//only for editor settings
#if WITH_EDITORONLY_DATA



#endif


};
