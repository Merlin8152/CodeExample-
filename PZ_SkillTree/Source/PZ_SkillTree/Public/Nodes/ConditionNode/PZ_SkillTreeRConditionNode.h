// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Nodes/BaseNode/PZ_SkillTreeRBaseNode.h"

#include "PZ_SkillTreeRConditionNode.generated.h"

/**
 * 
 */
UCLASS()
class PZ_SKILLTREE_API UPZ_SkillTreeRConditionNode : public UPZ_SkillTreeRBaseNode
{
	GENERATED_BODY()

	
//Constructor
public:

	UPZ_SkillTreeRConditionNode();


//c++ public methods
public:

	virtual bool OnExecute(UPZ_SkillTreeContext* SkillTreeContext) override;



	//......................................................................................................//



//Blueprint values
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced)
		TArray<class UPZ_SkillTreeCondition*> SendConditionEvents;



//only for editor settings
#if WITH_EDITORONLY_DATA



#endif


};
