
#include "PZ_PropertyDetailsTabFactory.h"

#include "PZ_SkillTreeEditorTabs.h"
#include "../SkillTreeEditor/PZ_SkillTreeGraphEditor.h"



FPZ_PropertyDetailsTabFactory::FPZ_PropertyDetailsTabFactory(TSharedPtr<FPZ_SkillTreeGraph> InSkillTreeGraphEditorPtr) :
	FWorkflowTabFactory(FPZ_SkillTreeEditor_Tabs::GraphPropertyID, InSkillTreeGraphEditorPtr),
	SkillTreeGraphEditorPtr(InSkillTreeGraphEditorPtr)
{
	TabLabel = FText::FromString("Details");
	TabIcon = FSlateIcon(FEditorStyle::GetStyleSetName(), "Kismet.Tabs.Components");

	bIsSingleton = true;

	ViewMenuDescription = FText::FromString("DetailsView");
	ViewMenuTooltip = FText::FromString("Show the details view");
}



TSharedRef<SWidget> FPZ_PropertyDetailsTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	return SkillTreeGraphEditorPtr.Pin()->GetPropertyWidget();
}

FText FPZ_PropertyDetailsTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString("Details");
}