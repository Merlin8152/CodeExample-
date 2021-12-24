// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTreeGraphEditorCommands.h"



#define LOCTEXT_NAMESPACE "EditorCommands_SkillTreeGraph"


void FPZ_SkillTreeGraphCommands::RegisterCommands()
{

	UI_COMMAND(RebuildSkillTree, "Rebuild SkillTree", "Rebuild SkillTree", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(CompileUI, "Compile UI Graph", "Compile SkillTree", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(SetTreeStructureMode, "StructureMode", "StructureMode", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(SetUIPositionMode, "UIPositionMode", "UIPositionMode", EUserInterfaceActionType::Button, FInputChord());

}


#undef LOCTEXT_NAMESPACE