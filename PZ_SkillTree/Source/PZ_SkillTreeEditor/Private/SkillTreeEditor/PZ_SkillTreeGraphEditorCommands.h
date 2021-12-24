// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PZ_SkillTreeEditorStyle.h"



class FPZ_SkillTreeGraphCommands : public TCommands<FPZ_SkillTreeGraphCommands>
{

public:

	FPZ_SkillTreeGraphCommands()
		: TCommands<FPZ_SkillTreeGraphCommands>("GenericGraphEditor", NSLOCTEXT("Contexts", "GenericGraphEditor", "Generic Graph Editor"), NAME_None, FEditorStyle::GetStyleSetName())
	{
	};


	TSharedPtr<FUICommandInfo> RebuildSkillTree;
	TSharedPtr<FUICommandInfo> CompileUI;
	TSharedPtr<FUICommandInfo> SetTreeStructureMode;
	TSharedPtr<FUICommandInfo> SetUIPositionMode;


	virtual void RegisterCommands() override;
};
