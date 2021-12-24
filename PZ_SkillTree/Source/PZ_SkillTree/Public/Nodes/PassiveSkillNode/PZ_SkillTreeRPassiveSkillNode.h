// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillNode/PZ_SkillTreeRSkillNode.h"
#include "PZ_SkillTreeRPassiveSkillNode.generated.h"



class UCurveFloat;


UCLASS()
class PZ_SKILLTREE_API UPZ_SkillTreeRPassiveSkillNode : public UPZ_SkillTreeRSkillNode
{
	GENERATED_BODY()


//Constructor
public:

	UPZ_SkillTreeRPassiveSkillNode();


//c++ public methods
public:

	virtual bool OnExecute(UPZ_SkillTreeContext* SkillTreeContext) override;



	//......................................................................................................//

//Blueprint values
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill Settings")
		UCurveFloat* SkillCurve = nullptr;


//only for editor settings
#if WITH_EDITORONLY_DATA



#endif

};
