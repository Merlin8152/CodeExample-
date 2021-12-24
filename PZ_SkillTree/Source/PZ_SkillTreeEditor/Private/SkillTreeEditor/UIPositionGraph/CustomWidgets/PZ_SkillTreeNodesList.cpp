// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTreeNodesList.h"


void SPZ_SkillTreeNodesList_RowContent::Construct(const FArguments& Args)
{
	Text = Args._Text;
	if (Args._ImageTexture2D)
	{
		ImageBrush.SetResourceObject(Args._ImageTexture2D);
	}
	ImageBrush.ImageSize = FVector2D(32, 32);

	ChildSlot
		.Padding(0.0f, 2.0f, 0.0f, 0.0f)
		[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(EVerticalAlignment::VAlign_Center)
					[
						SNew(SImage)
						.Image(&ImageBrush)
		
					]
				+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(EVerticalAlignment::VAlign_Center)
					[
						SNew(STextBlock)
						.Text(FText::FromName(Text))
						.TextStyle(Args._NodeTextStyle)
					]
		];
}










void SPZ_SkillTreeNodesList::Construct(const FArguments& Args)
{
	NodesArray = Args._NodesArray;
	OnNodeDragged = Args._OnNodeDragged;
	OnGetNodeTextStyle = Args._OnGetNodeTextStyle;
	ChildSlot
		[
		SNew(SScrollBox)

				+ SScrollBox::Slot()
					[
					SAssignNew(ListView, SListView <UPZ_SkillTreeRSkillNode*>)
					.ItemHeight(24)
					.ListItemsSource(NodesArray)
					.OnGenerateRow(this, &SPZ_SkillTreeNodesList::OnGenerateRowForList)
					
					]
		];
}

TSharedRef <ITableRow> SPZ_SkillTreeNodesList::OnGenerateRowForList(UPZ_SkillTreeRSkillNode* InItem, const TSharedRef <STableViewBase>& OwnerTable)
{ 
	
	const FTableRowStyle* RowStyle;
	if (OnGetRowStyle.IsBound())
	{
		RowStyle = OnGetRowStyle.Execute(InItem);
	}
	else
	{
		RowStyle = &FCoreStyle::Get().GetWidgetStyle<FTableRowStyle>("TableView.DarkRow");
	}

	const FTextBlockStyle* NodeTextStyle;
	if (OnGetNodeTextStyle.IsBound())
	{
		NodeTextStyle = OnGetNodeTextStyle.Execute(InItem);
	}
	else
	{
		NodeTextStyle = &FCoreStyle::Get().GetWidgetStyle< FTextBlockStyle >("NormalText");
	}

	TSharedRef<SWidget> RowContent = SNew(SPZ_SkillTreeNodesList_RowContent)
		//.ImageTexture2D(InItem->SkillIconTexture)
		//.Text(InItem->SkillName)
		.NodeTextStyle(NodeTextStyle);

	auto Row = SNew(STableRow<UPZ_SkillTreeRSkillNode*>, OwnerTable)
					.Style(RowStyle)
					.OnDragDetected(this, &SPZ_SkillTreeNodesList::OnItemDragDetected)
					;
	Row->SetContent(RowContent);

	return Row;
}

FReply SPZ_SkillTreeNodesList::OnItemDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		TArray<UPZ_SkillTreeRSkillNode*> SelectedNodes = ListView->GetSelectedItems();
		if (SelectedNodes.Num() > 0 && OnNodeDragged.IsBound())
		{
			UPZ_SkillTreeRSkillNode* Node = SelectedNodes[0];
			return OnNodeDragged.Execute(Node, MouseEvent);

		}
	}

	return FReply::Unhandled();
}

void SPZ_SkillTreeNodesList::Refresh_NodesArray()
{
	ListView->RebuildList();
}

