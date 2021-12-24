// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Views/STableRow.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Layout/SScrollBorder.h"
#include "SlateBasics.h"
#include "Nodes/SkillNode/PZ_SkillTreeRSkillNode.h"



// Виджет- контент для ITableRow(С информацией о R ноде)
class SPZ_SkillTreeNodesList_RowContent : public SCompoundWidget
{
public:

public:
	SLATE_BEGIN_ARGS(SPZ_SkillTreeNodesList_RowContent)
		:
		_ImageTexture2D(),
		_Text(),
		_NodeTextStyle()
		

	{}
	SLATE_ARGUMENT(UTexture2D*, ImageTexture2D)
		SLATE_ARGUMENT(FName, Text)
		SLATE_STYLE_ARGUMENT(FTextBlockStyle, NodeTextStyle)
		SLATE_END_ARGS()

		void Construct(const FArguments& Args);

protected:
	FSlateBrush ImageBrush;
	FName Text;
	FTextBlockStyle NodeTextStyle;
};

//Виджет - список нод, работает по переданному списку TArray<UPZ_SkillTreeRSkillNode*>
class SPZ_SkillTreeNodesList : public SCompoundWidget
{
public:
	DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnNodeDragged, UPZ_SkillTreeRSkillNode*, const FPointerEvent&);
	DECLARE_DELEGATE_RetVal_OneParam(const FTextBlockStyle*, FOnGetNodeTextStyle, UPZ_SkillTreeRSkillNode*);
	DECLARE_DELEGATE_RetVal_OneParam(const FTableRowStyle*, FOnGetRowStyle, UPZ_SkillTreeRSkillNode*);
public:
	SLATE_BEGIN_ARGS(SPZ_SkillTreeNodesList)
		:
		_NodesArray(),
		_OnNodeDragged(),
		_OnGetNodeTextStyle(),
		_OnGetRowStyle()
	{}
	SLATE_ARGUMENT(const TArray<UPZ_SkillTreeRSkillNode*>*, NodesArray)
	SLATE_EVENT(FOnNodeDragged, OnNodeDragged)
	SLATE_EVENT(FOnGetNodeTextStyle, OnGetNodeTextStyle)
	SLATE_EVENT(FOnGetRowStyle, OnGetRowStyle)
	SLATE_END_ARGS()

		void Construct(const FArguments& Args);
	TSharedRef <ITableRow> OnGenerateRowForList(UPZ_SkillTreeRSkillNode* InItem, const TSharedRef <STableViewBase>& OwnerTable);
	FReply OnItemDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);
	void Refresh_NodesArray();
protected:
	
	TSharedPtr< SListView<UPZ_SkillTreeRSkillNode*> > ListView;
	const TArray<UPZ_SkillTreeRSkillNode*>* NodesArray;
	FOnNodeDragged OnNodeDragged;
	FOnGetNodeTextStyle OnGetNodeTextStyle;
	FOnGetRowStyle OnGetRowStyle;
};
