// Copyright Epic Games, Inc. All Rights Reserved.

#include "PZ_SkillTreeEditorModule.h"


#include "SkillTreeAssetTypes/PZ_SkillTreeEditorAssetType.h"
#include "SkillTreeEditor/StructureGraph/Nodes/PZ_SkillTreeNodesFactory.h"
#include "SkillTreeEditor/UIPositionGraph/Nodes/PZ_SkillTreeUIPositionNodesFactory.h"

#include "SkillTreeEditor/PZ_SkillTreeEditorStyle.h"

#include "SkillTreeEditor/PZ_SkillTreeGraphEditorCommands.h"



void FPZ_SkillTreeEditorModule::StartupModule()
{	
	
	////////////////////CreatingAssets/////////////////////////////////

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();


	
	auto GenericGraphAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName("PZ_SkillTree"), FText::FromString("PZ_SkillTree"));
	TSharedRef<IAssetTypeActions> Action = MakeShareable(new FPZ_SkillTreeEditorAssetType(GenericGraphAssetCategoryBit));
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);

	//.......................................................................................................//


	{
		SkillTreeStructureGraphNodeFactory = MakeShared<FPZ_SkillTreeGraphNodeFactory>();
		FEdGraphUtilities::RegisterVisualNodeFactory(SkillTreeStructureGraphNodeFactory);

		SkillTreeStructureGraphPinFactory = MakeShared<FPZ_SkillTreeGraphPinFactory>();
		FEdGraphUtilities::RegisterVisualPinFactory(SkillTreeStructureGraphPinFactory);
	}

	{
		SkillTreeUIPositionGraphNodeFactory = MakeShared<FPZ_SkillTreeUIPositionGraphNodeFactory>();
		FEdGraphUtilities::RegisterVisualNodeFactory(SkillTreeUIPositionGraphNodeFactory);

		SkillTreeUIPositionGraphPinFactory = MakeShared<FPZ_SkillTreeUIPositionGraphPinFactory>();
		FEdGraphUtilities::RegisterVisualPinFactory(SkillTreeUIPositionGraphPinFactory);
	}


	FPZ_SkillTreeEditorStyle::Initialize();
}



void FPZ_SkillTreeEditorModule::ShutdownModule()
{
	
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (int32 Index = 0; Index < CreatedAssetTypeActions.Num(); ++Index)
		{
			AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[Index].ToSharedRef());
		}
	}




	if (SkillTreeStructureGraphPinFactory.IsValid())
	{
		FEdGraphUtilities::UnregisterVisualPinFactory(SkillTreeStructureGraphPinFactory);
	}
	if (SkillTreeStructureGraphNodeFactory.IsValid())
	{
		FEdGraphUtilities::UnregisterVisualNodeFactory(SkillTreeStructureGraphNodeFactory);
	}
	

	if (SkillTreeUIPositionGraphPinFactory.IsValid())
	{
		FEdGraphUtilities::UnregisterVisualPinFactory(SkillTreeUIPositionGraphPinFactory);
	}
	if (SkillTreeUIPositionGraphNodeFactory.IsValid())
	{
		FEdGraphUtilities::UnregisterVisualNodeFactory(SkillTreeUIPositionGraphNodeFactory);
	}



	FPZ_SkillTreeEditorStyle::Shutdown();
	FPZ_SkillTreeGraphCommands::Unregister();

}




	
IMPLEMENT_MODULE(FPZ_SkillTreeEditorModule, PZ_SkillTreeEditor)