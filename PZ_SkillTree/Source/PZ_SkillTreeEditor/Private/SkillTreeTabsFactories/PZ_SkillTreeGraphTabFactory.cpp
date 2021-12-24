
#include "PZ_SkillTreeGraphTabFactory.h"

#include "PZ_SkillTreeEditorTabs.h"
#include "../SkillTreeEditor/PZ_SkillTreeGraphEditor.h"




FPZ_SkillTreeGraphTabFactory::FPZ_SkillTreeGraphTabFactory(TSharedPtr<class FPZ_SkillTreeGraph> InSkillTreeGraphEditorPtr, FOnCreateGraphEditorWidget CreateGraphEditorWidgetCallback) :
	FWorkflowTabFactory(FPZ_SkillTreeEditor_Tabs::SkillTreeStructureGraph, InSkillTreeGraphEditorPtr),
	OnCreateGraphEditorWidget(CreateGraphEditorWidgetCallback)
{
	TabLabel = FText::FromString("Graph");
	TabIcon = FSlateIcon(FEditorStyle::GetStyleSetName(), "Kismet.Tabs.BlueprintDefaults");

	bIsSingleton = true;

	ViewMenuDescription = FText::FromString("GraphView");
	ViewMenuTooltip = FText::FromString("Shows the graph editor view");
}



TSharedRef<SWidget> FPZ_SkillTreeGraphTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	return OnCreateGraphEditorWidget.Execute();
}

FText FPZ_SkillTreeGraphTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString("Graph");
}
