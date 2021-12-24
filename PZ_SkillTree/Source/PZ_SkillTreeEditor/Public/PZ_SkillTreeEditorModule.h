// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"



class FPZ_SkillTreeEditorModule : public IModuleInterface
{

public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;


private:

	TArray< TSharedPtr<class IAssetTypeActions> > CreatedAssetTypeActions;


	TSharedPtr<struct FPZ_SkillTreeGraphNodeFactory> SkillTreeStructureGraphNodeFactory;
	TSharedPtr<struct FPZ_SkillTreeGraphPinFactory> SkillTreeStructureGraphPinFactory;

	TSharedPtr<struct FPZ_SkillTreeUIPositionGraphNodeFactory> SkillTreeUIPositionGraphNodeFactory;
	TSharedPtr<struct FPZ_SkillTreeUIPositionGraphPinFactory> SkillTreeUIPositionGraphPinFactory;

};
