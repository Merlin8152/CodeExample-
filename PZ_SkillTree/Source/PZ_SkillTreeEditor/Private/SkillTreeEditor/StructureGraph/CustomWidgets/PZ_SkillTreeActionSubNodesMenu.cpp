// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeEditor/StructureGraph/CustomWidgets/PZ_SkillTreeActionSubNodesMenu.h"

#include "EdGraph/EdGraph.h"
#include "Widgets/Layout/SBox.h"
#include "EditorStyleSet.h"
#include "Framework/Application/SlateApplication.h"
#include "SGraphActionMenu.h"

#include "SkillTreeEditor/StructureGraph/Nodes/BaseNode/PZ_SkillTreeEdNode_Base.h"
#include "SkillTreeEditor/StructureGraph/Graph/PZ_SkillTreeStructureEdGraphSchema.h"





SPZ_SkillTreeActionSubNodesMenu::~SPZ_SkillTreeActionSubNodesMenu()
{
	OnClosedCallback.ExecuteIfBound();
}

void SPZ_SkillTreeActionSubNodesMenu::Construct(const FArguments& InArgs)
{
	this->GraphObj = InArgs._GraphObj;
	this->GraphNode = InArgs._GraphNode;
	this->DraggedFromPins = InArgs._DraggedFromPins;
	this->NewNodePosition = InArgs._NewNodePosition;
	this->OnClosedCallback = InArgs._OnClosedCallback;
	this->AutoExpandActionMenu = InArgs._AutoExpandActionMenu;
	this->NodeType = InArgs._NodeType;

	// Build the widget layout
	SBorder::Construct(SBorder::FArguments()
		.BorderImage(FEditorStyle::GetBrush("Menu.Background"))
		.Padding(5)
		[
			// Achieving fixed width by nesting items within a fixed width box.
			SNew(SBox)
			//.WidthOverride(400)
			[
				SAssignNew(GraphActionMenu, SGraphActionMenu)
				.OnActionSelected(this, &SPZ_SkillTreeActionSubNodesMenu::OnActionSelected)
				.OnCollectAllActions(this, &SPZ_SkillTreeActionSubNodesMenu::CollectAllActions)
				.AutoExpandActionMenu(AutoExpandActionMenu)
			]
		]
	);
}



TSharedRef<SEditableTextBox> SPZ_SkillTreeActionSubNodesMenu::GetFilterTextBox()
{
	return GraphActionMenu->GetFilterTextBox();
}

void SPZ_SkillTreeActionSubNodesMenu::OnActionSelected(const TArray< TSharedPtr<FEdGraphSchemaAction> >& SelectedAction, ESelectInfo::Type InSelectionType)
{
	if (InSelectionType == ESelectInfo::OnMouseClick || InSelectionType == ESelectInfo::OnKeyPress || SelectedAction.Num() == 0)
	{
		bool bDoDismissMenus = false;

		if (GraphObj)
		{
			for (int32 ActionIndex = 0; ActionIndex < SelectedAction.Num(); ++ActionIndex)
			{
				TSharedPtr<FEdGraphSchemaAction> CurrentAction = SelectedAction[ActionIndex];

				if (CurrentAction.IsValid())
				{
					CurrentAction->PerformAction(GraphObj, DraggedFromPins, NewNodePosition);
					bDoDismissMenus = true;
				}
			}
		}

		if (bDoDismissMenus)
		{
			FSlateApplication::Get().DismissAllMenus();
		}
	}
}


void SPZ_SkillTreeActionSubNodesMenu::CollectAllActions(FGraphActionListBuilderBase& OutAllActions)
{
	// Build up the context object
	FGraphContextMenuBuilder ContextMenuBuilder(GraphObj);
	if (GraphNode != NULL)
	{
		ContextMenuBuilder.SelectedObjects.Add(GraphNode);
	}
	if (DraggedFromPins.Num() > 0)
	{
		ContextMenuBuilder.FromPin = DraggedFromPins[0];
	}

	// Determine all possible actions
	if (const UPZ_SkillTreeEdGraphSchema* MySchema = Cast<const UPZ_SkillTreeEdGraphSchema>(GraphObj->GetSchema()))
	{
		MySchema->GetGraphNodeContextActions(ContextMenuBuilder, NodeType);
	}

	// Copy the added options back to the main list
	OutAllActions.Append(ContextMenuBuilder);
}
