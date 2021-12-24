// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTreeEditorStyle.h"
#include "Styling/SlateTypes.h"
#include "Styling/SlateStyleRegistry.h"
#include "Misc/Paths.h"



// Const icon sizes
static const FVector2D Icon16x16(16.0f, 16.0f);
static const FVector2D Icon20x20(20.0f, 20.0f);
static const FVector2D Icon24x24(24.0f, 24.0f);
static const FVector2D Icon40x40(40.0f, 40.0f);
static const FVector2D Icon32x32(32.0f, 32.0f);
static const FVector2D Icon64x64(64.0f, 64.0f);
static const FVector2D Icon96x96(96.0f, 96.0f);



const FName FPZ_SkillTreeEditorStyle::NodeIcon_DefaultIcon("NodeIcon.DefaultIcon");
const FName FPZ_SkillTreeEditorStyle::NodeIcon_RootNodeIcon("NodeIcon.RootIcon");
const FName FPZ_SkillTreeEditorStyle::NodeIcon_SkillNodeIcon("NodeIcon.SkillIcon");
const FName FPZ_SkillTreeEditorStyle::NodeIcon_ConditionNodeIcon("NodeIcon.ConditionIcon");
const FName FPZ_SkillTreeEditorStyle::NodeIcon_SkillActionNodeIcon("NodeIcon.SkillActionIcon");
const FName FPZ_SkillTreeEditorStyle::NodeIcon_EventNodeIcon("NodeIcon.EventIcon");
const FName FPZ_SkillTreeEditorStyle::NodeIcon_SwitchNodeIcon("NodeIcon.SwitchIcon");
const FName FPZ_SkillTreeEditorStyle::NodeIcon_ConnectionNodeIcon("NodeIcon.ConnectionIcon");
const FName FPZ_SkillTreeEditorStyle::NodeIcon_CustomNodeIcon("NodeIcon.CustomIcon");

const FName FPZ_SkillTreeEditorStyle::NodeIcon_UINodeIcon("NodeIcon.UIIcon");

TSharedPtr<FSlateStyleSet> FPZ_SkillTreeEditorStyle::StyleSet = nullptr;




void FPZ_SkillTreeEditorStyle::Initialize()
{
	if (StyleSet.IsValid()) { return; }


	StyleSet = MakeShareable(new FSlateStyleSet("SkillTreeEditorStyle"));
	StyleSet->SetContentRoot(FPaths::ProjectPluginsDir() / TEXT("PZ_SkillTree/Resources"));



	
	StyleSet->Set(
		"ClassThumbnail.PZ_SkillTree_Editor",
		new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("SkillTreeEditorIcon_64x"), TEXT(".png")), Icon64x64, FLinearColor(1.f, 1.f, 1.f, 1.f))
	);



	///////////ToolbarIcons/////////////////////////////////////

	StyleSet->Set(
		"SkillTreeEditor.RebuildSkillTree",
		new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("RebuildDialogueIcon_32x"), TEXT(".png")), Icon32x32, FLinearColor::Gray)
	);

	StyleSet->Set(
		"SkillTreeEditor.NeedRebuildSkillTree",
		new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("RebuildDialogueIcon_32x"), TEXT(".png")), Icon32x32, FLinearColor::Yellow)
	);

	
	//...............................................




	/////////////NodeSettingsIcon///////////////////

	StyleSet->Set(
		"SkillTreeEditor.NodeError",
		new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("ErrorNode_24x"), TEXT(".png")), Icon24x24, FLinearColor::White)
	);

	//.................................................





	//////////////////////////NodesIcon///////////////////

	StyleSet->Set(
		NodeIcon_DefaultIcon,
		new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("BaseNode_24x"), TEXT(".png")), Icon24x24, FLinearColor::Gray)
	);


	StyleSet->Set(
		NodeIcon_SkillNodeIcon,
		new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("SkillNodeIcon_24x"), TEXT(".png")), Icon24x24, FLinearColor::Gray)
	);


	StyleSet->Set(
		NodeIcon_ConditionNodeIcon,
		new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("Condition_24x"), TEXT(".png")), Icon24x24, FLinearColor::Gray)
	);

	StyleSet->Set(
		NodeIcon_EventNodeIcon,
		new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("EventNode_24x"), TEXT(".png")), Icon24x24, FLinearColor::Gray)
	);

	StyleSet->Set(
		NodeIcon_SkillActionNodeIcon,
		new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("SkillActionNode_24x"), TEXT(".png")), Icon24x24, FLinearColor::Gray)
	);

	StyleSet->Set(
		NodeIcon_RootNodeIcon,
		new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("RootNode_24x"), TEXT(".png")), Icon24x24, FLinearColor::Gray)
	);

	StyleSet->Set(
		NodeIcon_SwitchNodeIcon,
		new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("SwitchNodeIcon_24x"), TEXT(".png")), Icon24x24, FLinearColor::Gray)
	);

	StyleSet->Set(
		NodeIcon_ConnectionNodeIcon,
		new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("ConnectionNodeIcon_24x"), TEXT(".png")), Icon24x24, FLinearColor::Gray)
	);

	StyleSet->Set(
		NodeIcon_CustomNodeIcon,
		new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("CustomNodeIcon_24x"), TEXT(".png")), Icon24x24, FLinearColor::Gray)
	);
	//........................................................................

	StyleSet->Set(
		NodeIcon_UINodeIcon,
		new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("UINodeIcon_24x"), TEXT(".png")), Icon24x24, FLinearColor::Gray)
	);

	//........................................................................
	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}





void FPZ_SkillTreeEditorStyle::Shutdown()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
		ensure(StyleSet.IsUnique());
		StyleSet.Reset();
	}
}


const FName& FPZ_SkillTreeEditorStyle::GetStyleSetName()
{
	return StyleSet->GetStyleSetName();
}
