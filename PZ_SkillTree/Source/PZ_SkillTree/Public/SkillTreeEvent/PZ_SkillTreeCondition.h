// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PZ_SkillTreeCondition.generated.h"

class UPZ_SkillTreeContext;


UCLASS(Blueprintable, BlueprintType, EditInlineNew, Abstract)
class PZ_SKILLTREE_API UPZ_SkillTreeCondition : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SkillTree | SkillTreeEvent")
		bool Execute(UPZ_SkillTreeContext* SkillTreeContext, AActor* SkillTreePlayer);
		virtual bool Execute_Implementation(UPZ_SkillTreeContext* SkillTreeContext, AActor* SkillTreePlayer) { return true; }

};