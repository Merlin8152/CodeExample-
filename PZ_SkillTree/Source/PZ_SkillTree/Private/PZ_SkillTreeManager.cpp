// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTreeManager.h"

#include "PZ_SkillTreeContext.h"
#include "PZ_SkillTree_Editor.h"
#include "SkillTreeComponent/PZ_SkillTreeComponent.h"


UPZ_SkillTreeContext* UPZ_SkillTreeManager::CreateSkillTreeContext(UPZ_SkillTree_Editor* Dialog, AActor* Outer, UPZ_SkillTreeComponent* STComponent)
{
	if (Outer && Dialog)
	{
		UPZ_SkillTreeContext* LSkillTreeContext = NewObject<UPZ_SkillTreeContext>(Outer, UPZ_SkillTreeContext::StaticClass());

		LSkillTreeContext->InitContext(Dialog,Outer, STComponent);

		return LSkillTreeContext;
	}

	return nullptr;
}