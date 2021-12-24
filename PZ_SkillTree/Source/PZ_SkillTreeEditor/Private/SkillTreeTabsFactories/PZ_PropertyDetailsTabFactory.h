// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"

#include "Toolkits/AssetEditorToolkit.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"
#include "SGraphPanel.h"



class FPZ_SkillTreeGraph;



struct FPZ_PropertyDetailsTabFactory : public FWorkflowTabFactory
{

public:

	FPZ_PropertyDetailsTabFactory(TSharedPtr<FPZ_SkillTreeGraph> InSkillTreeGraphEditorPtr);

public:

	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;


protected:

	TWeakPtr<FPZ_SkillTreeGraph> SkillTreeGraphEditorPtr;
};
