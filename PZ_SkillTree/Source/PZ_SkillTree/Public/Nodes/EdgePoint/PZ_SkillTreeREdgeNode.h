// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Nodes/BaseTreeElement/PZ_SkillTreeRBaseTreeElement.h"

#include "PZ_SkillTreeREdgeNode.generated.h"


class UPZ_SkillTreeRConditionNode;

UCLASS()
class PZ_SKILLTREE_API UPZ_SkillTreeREdgeNode : public UPZ_SkillTreeRBaseTreeElement
{
	GENERATED_BODY()


// Constructor
public:


//c++ public methods
public:

	virtual bool OnExecute(UPZ_SkillTreeContext* SkillTreeContext) override;

//Blueprint values
public:

	UPROPERTY(EditDefaultsOnly)
		bool AlwaysTrue = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		bool IsNeedCompile = true;



//only for editor settings
#if WITH_EDITORONLY_DATA



#endif

};
