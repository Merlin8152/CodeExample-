// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PZ_SkillTreeEvent.generated.h"




class UPZ_SkillTreeContext;

UCLASS(Blueprintable, BlueprintType, EditInlineNew, Abstract)
class PZ_SKILLTREE_API UPZ_SkillTreeEvent : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SkillTree | SkillTreeEvent")
		void Execute(UPZ_SkillTreeContext* SkillTreeContext, AActor* SkillTreePlayer);
		virtual void Execute_Implementation(UPZ_SkillTreeContext* SkillTreeContext, AActor* SkillTreePlayer) {}

};


