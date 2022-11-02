// Copyright (c) 2020 - 2022 GameWheelStudio. All rights reserved.

#include "PZ_UITools.h"



#define LOCTEXT_NAMESPACE "FPZ_UIToolsModule"



void FPZ_UIToolsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FPZ_UIToolsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}



#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPZ_UIToolsModule, PZ_UITools)