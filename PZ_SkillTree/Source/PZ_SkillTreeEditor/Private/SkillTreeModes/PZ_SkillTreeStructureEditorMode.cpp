// Fill out your copyright notice in the Description page of Project Settings.

#include "PZ_SkillTreeEditor/Private/SkillTreeModes/PZ_SkillTreeStructureEditorMode.h"
#include "PZ_SkillTreeEditorModes.h"

#include "SkillTreeTabsFactories/PZ_SkillTreeEditorTabs.h"
#include "SkillTreeTabsFactories/PZ_SkillTreeGraphTabFactory.h"
#include "SkillTreeTabsFactories/PZ_PropertyDetailsTabFactory.h"




FPZ_SkillTreeStructureEditorMode::FPZ_SkillTreeStructureEditorMode(const TSharedPtr<FPZ_SkillTreeGraph>& InSkillTreeGraphEditor) :
	FApplicationMode(FPZ_SkillTreeGraphEditor_Modes::StructureEditMode),
	SkillTreeGraphEditor(InSkillTreeGraphEditor)
{

	StandartTabFactories.RegisterFactory( MakeShareable(new FPZ_PropertyDetailsTabFactory(InSkillTreeGraphEditor)) );
	StandartTabFactories.RegisterFactory
	(
		MakeShareable(new FPZ_SkillTreeGraphTabFactory
		(
			InSkillTreeGraphEditor,
			FPZ_SkillTreeGraphTabFactory::FOnCreateGraphEditorWidget::CreateSP(InSkillTreeGraphEditor.Get(), &FPZ_SkillTreeGraph::CreateStructureGraphEditorWidget)
		))
	);



	TabLayout = FTabManager::NewLayout("SkillTree_StructureEditorLayout_v1.22")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->AddTab(InSkillTreeGraphEditor->GetToolbarTabId(), ETabState::OpenedTab)->SetHideTabWell(true)
			)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)->SetSizeCoefficient(0.9f)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.7f)
					->AddTab(FPZ_SkillTreeEditor_Tabs::SkillTreeStructureGraph, ETabState::OpenedTab)->SetHideTabWell(true)
				)
				->Split
				(
					FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
					->Split
					(
						FTabManager::NewStack()
						->AddTab(FPZ_SkillTreeEditor_Tabs::GraphPropertyID, ETabState::OpenedTab)->SetHideTabWell(true)
					)

				)
			)
		);




	ToolbarExtender->AddToolBarExtension
	(
		"Asset",
		EExtensionHook::After, InSkillTreeGraphEditor.Get()->GetToolkitCommands(),
		FToolBarExtensionDelegate::CreateSP(InSkillTreeGraphEditor.Get(), &FPZ_SkillTreeGraph::FillStructureGraphToolbar)
	);

}





void FPZ_SkillTreeStructureEditorMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{

	TSharedPtr<FPZ_SkillTreeGraph> Editor = SkillTreeGraphEditor.Pin();

	// Tool bar tab (Default)
	Editor->RegisterTabSpawners(InTabManager.ToSharedRef());

	// Other tabs
	Editor->PushTabFactories(StandartTabFactories);


	FApplicationMode::RegisterTabFactories(InTabManager);
}






void FPZ_SkillTreeStructureEditorMode::AddTabFactory(FCreateWorkflowTabFactory FactoryCreator)
{
	if (FactoryCreator.IsBound())
	{
		StandartTabFactories.RegisterFactory(FactoryCreator.Execute(SkillTreeGraphEditor.Pin()));
	}
}

void FPZ_SkillTreeStructureEditorMode::RemoveTabFactory(FName TabFactoryID)
{
	StandartTabFactories.UnregisterFactory(TabFactoryID);
}






void FPZ_SkillTreeStructureEditorMode::PreDeactivateMode()
{
	//TODO
}

void FPZ_SkillTreeStructureEditorMode::PostActivateMode()
{
	//TODO
}
