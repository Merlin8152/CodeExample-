// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeAssetTypes/PZ_SkillTreeEditorFactory.h"

#include "PZ_SkillTree_Editor.h"



UPZ_SkillTreeEditorFactory::UPZ_SkillTreeEditorFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UPZ_SkillTree_Editor::StaticClass();
}

UObject* UPZ_SkillTreeEditorFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UPZ_SkillTree_Editor>(InParent, Class, Name, Flags | RF_Transactional);
}
