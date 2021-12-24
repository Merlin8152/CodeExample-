// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "PZ_SkillTreeEditor/Private/SkillTreeEditor/PZ_SkillTreeGraphEditor.h"



class FPZ_SkillTreeUIPositionEditorMode : public FApplicationMode
{

public:

	FPZ_SkillTreeUIPositionEditorMode(const TSharedPtr<FPZ_SkillTreeGraph>& InSkillTreeGraphEditor);


public:

	virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;

	virtual void AddTabFactory(FCreateWorkflowTabFactory FactoryCreator) override;
	virtual void RemoveTabFactory(FName TabFactoryID) override;

	virtual void PreDeactivateMode() override;
	virtual void PostActivateMode() override;


private:

	TWeakPtr<FPZ_SkillTreeGraph> SkillTreeGraphEditor;
	FWorkflowAllowedTabSet StandartTabFactories;

};
