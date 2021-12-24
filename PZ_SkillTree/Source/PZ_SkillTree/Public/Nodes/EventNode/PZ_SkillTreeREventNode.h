// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/BaseNode/PZ_SkillTreeRBaseNode.h"
#include "PZ_SkillTreeREventNode.generated.h"

/**
 * 
 */
UCLASS()
class PZ_SKILLTREE_API UPZ_SkillTreeREventNode : public UPZ_SkillTreeRBaseNode
{
	GENERATED_BODY()


//Constructor
public:

	UPZ_SkillTreeREventNode();


//c++ public methods
public:

	virtual bool OnExecute(UPZ_SkillTreeContext* SkillTreeContext) override;



	//......................................................................................................//

//Blueprint values
public:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName EventName;





//only for editor settings
#if WITH_EDITORONLY_DATA

//TODO

#endif


};
