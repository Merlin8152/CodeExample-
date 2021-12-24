// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillNode/PZ_SkillTreeRSkillNode.h"
#include "PZ_SkillTreeRActiveSkillNode.generated.h"

/**
 * 
 */
UCLASS()
class PZ_SKILLTREE_API UPZ_SkillTreeRActiveSkillNode : public UPZ_SkillTreeRSkillNode
{
	GENERATED_BODY()

//Constructor
public:

	UPZ_SkillTreeRActiveSkillNode();


//c++ public methods
public:

	virtual bool OnExecute(UPZ_SkillTreeContext* SkillTreeContext) override;

	



	//......................................................................................................//

//Blueprint values
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (UIMin = "1", ClampMin = "1"), Category = "Skill Settings")
		int MaxSkillLevel = 1;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill Settings")
		bool CanAlwaysUpdate = false; /// Позволяет улучшать скилл бесконечное количество раз 

//only for editor settings


#if WITH_EDITORONLY_DATA



#endif

};
