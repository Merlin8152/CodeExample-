// Fill out your copyright notice in the Description page of Project Settings.

#include "PZ_SkillTreeEditor/Private/SkillTreeModes/PZ_SkillTreeUIPositionMode.h"
#include "PZ_SkillTreeEditorModes.h"

#include "SkillTreeTabsFactories/PZ_SkillTreeEditorTabs.h"
#include "SkillTreeTabsFactories/PZ_SkillTreeGraphTabFactory.h"
#include "SkillTreeTabsFactories/PZ_PropertyDetailsTabFactory.h"


FPZ_SkillTreeUIPositionEditorMode::FPZ_SkillTreeUIPositionEditorMode(const TSharedPtr<FPZ_SkillTreeGraph>& InSkillTreeGraphEditor) :
	FApplicationMode(FPZ_SkillTreeGraphEditor_Modes::UIPositionMode),
	SkillTreeGraphEditor(InSkillTreeGraphEditor)
{
	StandartTabFactories.RegisterFactory(MakeShareable(new FPZ_PropertyDetailsTabFactory(InSkillTreeGraphEditor)));
	StandartTabFactories.RegisterFactory
	( 
		MakeShareable(new FPZ_SkillTreeGraphTabFactory
		(
			InSkillTreeGraphEditor,
			FPZ_SkillTreeGraphTabFactory::FOnCreateGraphEditorWidget::CreateSP(InSkillTreeGraphEditor.Get(), &FPZ_SkillTreeGraph::CreateUIPositionGraphEditorWidget)
		))
	);



	TabLayout = FTabManager::NewLayout("SkillTree_UIPositionEditorLayout_v1.3")
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
			//FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			//->Split
			//(
			//	FTabManager::NewStack()
			//	->SetSizeCoefficient(0.1f)
			//	->AddTab(InSkillTreeGraphEditor->GetToolbarTabId(), ETabState::OpenedTab)->SetHideTabWell(true)
			//)
			//->Split
			//(
			//	FTabManager::NewStack()
			//	->SetSizeCoefficient(0.5f)
			//	->AddTab(FPZ_SkillTreeEditor_Tabs::SkillTreeStructureGraph, ETabState::OpenedTab)->SetHideTabWell(true)
			//)

		);




	ToolbarExtender->AddToolBarExtension
	(
		"Asset",
		EExtensionHook::After, InSkillTreeGraphEditor.Get()->GetToolkitCommands(),
		FToolBarExtensionDelegate::CreateSP(InSkillTreeGraphEditor.Get(), &FPZ_SkillTreeGraph::FillUIPositionGraphToolbar)
	);
}



void FPZ_SkillTreeUIPositionEditorMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	TSharedPtr<FPZ_SkillTreeGraph> Editor = SkillTreeGraphEditor.Pin();

	// Tool bar tab
	Editor->RegisterTabSpawners(InTabManager.ToSharedRef());

	// Other tabs
	Editor->PushTabFactories(StandartTabFactories);


	FApplicationMode::RegisterTabFactories(InTabManager);
}




void FPZ_SkillTreeUIPositionEditorMode::AddTabFactory(FCreateWorkflowTabFactory FactoryCreator)
{
	if (FactoryCreator.IsBound())
	{
		StandartTabFactories.RegisterFactory(FactoryCreator.Execute(SkillTreeGraphEditor.Pin()));
	}
}

void FPZ_SkillTreeUIPositionEditorMode::RemoveTabFactory(FName TabFactoryID)
{
	StandartTabFactories.UnregisterFactory(TabFactoryID);
}




void FPZ_SkillTreeUIPositionEditorMode::PreDeactivateMode()
{
	//TODO
}

void FPZ_SkillTreeUIPositionEditorMode::PostActivateMode()
{
	//TODO
}

