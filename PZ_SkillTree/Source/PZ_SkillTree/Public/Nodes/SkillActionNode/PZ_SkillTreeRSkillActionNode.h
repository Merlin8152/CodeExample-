// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/BaseNode/PZ_SkillTreeRBaseNode.h"
#include "PZ_SkillTreeRSkillActionNode.generated.h"

/**
 * 
 */
UCLASS()
class PZ_SKILLTREE_API UPZ_SkillTreeRSkillActionNode : public UPZ_SkillTreeRBaseNode
{
	GENERATED_BODY()

//Constructor
public:

	UPZ_SkillTreeRSkillActionNode();


//c++ public methods
public:

	virtual bool OnExecute(UPZ_SkillTreeContext* SkillTreeContext) override;



	//......................................................................................................//

//Blueprint values
public:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced)
		TArray<class UPZ_SkillTreeEvent*> SendEvents;


//only for editor settings
#if WITH_EDITORONLY_DATA



#endif
};





