// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PZ_SkillTreeWidgetCreator.generated.h"




class UPZ_SkillTreeContext;

UCLASS(Blueprintable, BlueprintType, EditInlineNew, Abstract)
class PZ_SKILLTREE_API UPZ_SkillTreeObjectCreator : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SkillTree | ObjectCreator")
		UObject* CreateObject(UWorld* ObjectOwner);
	virtual UObject* CreateObject_Implementation(UWorld* ObjectOwner) { return nullptr; };

	virtual void GetAdditionalNodeInfo(TArray<FString>& AdditionalInfoArray) {};

	virtual FString GetErrorMessage() { return FString(""); };

};


