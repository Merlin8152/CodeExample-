// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "PZ_SkillTreeEditorFactory.generated.h"


UCLASS()
class UPZ_SkillTreeEditorFactory : public UFactory
{
	GENERATED_BODY()

public:

	UPZ_SkillTreeEditorFactory();

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
