// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillTreeContextItems/PZ_SkillTreeContextItem_Base.h"

#include "PZ_SkillTreeContextItem_Skill.generated.h"




class UPZ_SkillTreeRBaseNode;
class UPZ_SkillTreeRActiveSkillNode;
class UPZ_SkillTreeRPassiveSkillNode;
class UPZ_SkillTreeContext;



UCLASS(BlueprintType)
class PZ_SKILLTREE_API UPZ_SkillTreeContextItem_Skill : public UPZ_SkillTreeContextItem_Base
{
	GENERATED_BODY()


//constructor
public:

	UPZ_SkillTreeContextItem_Skill() {}


	virtual void OnExecute_Impl() override;
	virtual bool IsNeedContinueUpdateNext(TArray<UPZ_SkillTreeContextItem_Base*>& UpdatedNodes) override;
	virtual bool IsNeedContinueUpdatePrevious(TArray<UPZ_SkillTreeContextItem_Base*>& UpdatedNodes) override;
	virtual void OnUpdate() override;
	virtual void FindNextNodesToUpdate(TArray<UPZ_SkillTreeContextItem_Base*>& NodesToUpdate) override;
	virtual void FindPreviousNodesToUpdate(TArray<UPZ_SkillTreeContextItem_Base*>& NodesToUpdate) override;



	int CurrentSkillLvl = 0;
	int CurrentSkillLayer = 0;
	bool IsOpen = false;

	bool CanBeOpen = false;

};
