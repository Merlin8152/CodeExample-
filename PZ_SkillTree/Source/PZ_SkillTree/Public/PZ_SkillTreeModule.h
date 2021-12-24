// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FPZ_SkillTreeModule : public IModuleInterface
{


public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

};
