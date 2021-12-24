// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/BaseNode/PZ_SkillTreeRBaseNode.h"
#include "PZ_SkillTreeRSwitcherNode.generated.h"

class UPZ_SkillTreeRSkillNode;

UCLASS()
class PZ_SKILLTREE_API UPZ_SkillTreeRSwitcherNode : public UPZ_SkillTreeRBaseNode
{
	GENERATED_BODY()

//Constructor
public:

	UPZ_SkillTreeRSwitcherNode();



//c++ public methods
public:

	virtual bool OnExecute(UPZ_SkillTreeContext* SkillTreeContext) override;



	//......................................................................................................//

//Blueprint values
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (UIMin = "1", ClampMin = "1"), Category = "Skill Settings")
		int MaxIncludeNodeCount = 1;



//only for editor settings
#if WITH_EDITORONLY_DATA



#endif

};
