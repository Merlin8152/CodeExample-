// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PZ_SkillTreeManager.generated.h"



class UPZ_SkillTree_Editor;
class UPZ_SkillTreeContext;
class UPZ_SkillTreeComponent;

UCLASS()
class PZ_SKILLTREE_API UPZ_SkillTreeManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	


public:

	UFUNCTION(BlueprintCallable, Category = "SkillTree")
		static UPZ_SkillTreeContext* CreateSkillTreeContext(UPZ_SkillTree_Editor* SkillTree, AActor* Outer, UPZ_SkillTreeComponent* STComponent);



};
