// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTreeEditorAssetType.h"

#include "PZ_SkillTree_Editor.h"
#include "SkillTreeEditor/PZ_SkillTreeGraphEditor.h"


FPZ_SkillTreeEditorAssetType::FPZ_SkillTreeEditorAssetType(EAssetTypeCategories::Type InAssetCategory)
	: MyAssetCategory(InAssetCategory)
{
}



FText FPZ_SkillTreeEditorAssetType::GetName() const
{
	return FText::FromString("SkillTree Graph");
}

FColor FPZ_SkillTreeEditorAssetType::GetTypeColor() const
{
	return FColor(220, 20, 60);
}

UClass* FPZ_SkillTreeEditorAssetType::GetSupportedClass() const
{
	return UPZ_SkillTree_Editor::StaticClass();
}

void FPZ_SkillTreeEditorAssetType::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (UPZ_SkillTree_Editor* Editor = Cast<UPZ_SkillTree_Editor>(*ObjIt))
		{
			TSharedRef<FPZ_SkillTreeGraph> NewGraphEditor(new FPZ_SkillTreeGraph());
			NewGraphEditor->InitSkillTreeGraph(Mode, EditWithinLevelEditor, Editor);
		}
	}
}

uint32 FPZ_SkillTreeEditorAssetType::GetCategories()
{
	return MyAssetCategory;
}


