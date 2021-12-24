// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"

#include "Toolkits/AssetEditorToolkit.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"
#include "SGraphPanel.h"



class FPZ_SkillTreeGraph;



struct FPZ_SkillTreeGraphTabFactory : public FWorkflowTabFactory
{

	DECLARE_DELEGATE_RetVal(TSharedRef<SGraphEditor>, FOnCreateGraphEditorWidget);

public:

	FPZ_SkillTreeGraphTabFactory(TSharedPtr<FPZ_SkillTreeGraph> InSkillTreeGraphEditorPtr, FOnCreateGraphEditorWidget CreateGraphEditorWidgetCallback);


public:

	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;



protected:

	FOnCreateGraphEditorWidget OnCreateGraphEditorWidget;

};

