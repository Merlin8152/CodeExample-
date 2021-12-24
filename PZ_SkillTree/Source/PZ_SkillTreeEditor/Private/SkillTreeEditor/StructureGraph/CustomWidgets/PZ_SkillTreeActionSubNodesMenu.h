// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Layout/SBorder.h"
#include "EdGraph/EdGraphSchema.h"
#include "PZ_SkillTreeNodesInfo.h"
#include "GraphEditor.h"


class SEditableTextBox;
class SGraphActionMenu;
class UPZ_SkillTreeEdNode_Base;
class UEdGraph;


class SPZ_SkillTreeActionSubNodesMenu : public SBorder
{

public:

	SLATE_BEGIN_ARGS(SPZ_SkillTreeActionSubNodesMenu) :
		_GraphObj(static_cast<UEdGraph*>(NULL)),
		_GraphNode(NULL),
		_NewNodePosition(FVector2D::ZeroVector), 
		_AutoExpandActionMenu(false), 
		_NodeType(ESkillTreeNodeType::None)
	{}

	SLATE_ARGUMENT(UEdGraph*, GraphObj)
	SLATE_ARGUMENT(UPZ_SkillTreeEdNode_Base*, GraphNode)
	SLATE_ARGUMENT(FVector2D, NewNodePosition)
	SLATE_ARGUMENT(TArray<UEdGraphPin*>, DraggedFromPins)
	SLATE_ARGUMENT(SGraphEditor::FActionMenuClosed, OnClosedCallback)
	SLATE_ARGUMENT(bool, AutoExpandActionMenu)
	SLATE_ARGUMENT(ESkillTreeNodeType, NodeType)

	SLATE_END_ARGS()



	void Construct(const FArguments& InArgs);

	~SPZ_SkillTreeActionSubNodesMenu();


public:

	TSharedRef<SEditableTextBox> GetFilterTextBox();

protected:

	void OnActionSelected(const TArray< TSharedPtr<FEdGraphSchemaAction> >& SelectedAction, ESelectInfo::Type InSelectionType);

	/** Callback used to populate all actions list in SGraphActionMenu */
	void CollectAllActions(FGraphActionListBuilderBase& OutAllActions);



protected:

	UEdGraph* GraphObj = nullptr;
	UPZ_SkillTreeEdNode_Base* GraphNode = nullptr;

	TArray<UEdGraphPin*> DraggedFromPins;
	FVector2D NewNodePosition;
	bool AutoExpandActionMenu;
	ESkillTreeNodeType NodeType;

	SGraphEditor::FActionMenuClosed OnClosedCallback;
	TSharedPtr<SGraphActionMenu> GraphActionMenu;

};
