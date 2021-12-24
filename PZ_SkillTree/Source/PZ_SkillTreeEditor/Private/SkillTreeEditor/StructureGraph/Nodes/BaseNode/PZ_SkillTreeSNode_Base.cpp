// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeEditor/StructureGraph/Nodes/BaseNode/PZ_SkillTreeSNode_Base.h"

#include "PZ_SkillTreeEdNode_Base.h"


#include "SCommentBubble.h"
#include "../PZ_SSkillTreeGraphPin.h"

#include "EditorStyleSet.h"
#include "../../../PZ_SkillTreeEditorStyle.h"

#include "SkillTreeEditor/PZ_SkillTreeEditorConstant.h"
#include "Nodes/BaseNode/PZ_SkillTreeRBaseNode.h"
#include "SGraphPanel.h"




void SPZ_SkillTreeSNode_Base::Construct(const FArguments& InArgs, UPZ_SkillTreeEdNode_Base* InNode)
{
	GraphNode = InNode;
	InNode->SEdNode = this;
	EdBaseNode = InNode;
	this->SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}




void SPZ_SkillTreeSNode_Base::UpdateGraphNode()
{
	ErrorMsg = GraphNode->ErrorMsg;
	ErrorColor = FSlateColor(FLinearColor::Red);
	InputPins.Empty();
	OutputPins.Empty();

	RightNodeBox.Reset();
	LeftNodeBox.Reset();
	TopPinBox.Reset();
	BottomPinBox.Reset();

	SubNodes.Reset();

	UpdateGraphNode_ResetStage();

	const float IconSize = 24.0f;
	const int32 IconOffsetCoef = 3;

	const float NodeBodyPadding = GetNodeBodyPadding();

	const FSlateBrush* ErrorImage = GetErrorImage();
	FVector2D ErrorImageSize = FVector2D(0, 0);
	if (ErrorImage)
	{
		ErrorImageSize = ErrorImage->GetImageSize();
	}

	//Create Border
	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);
	this->GetOrAddSlot(ENodeZone::Center)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SBorder)
			.BorderImage(GetBackgroundImage())
			.Padding(0)
			.BorderBackgroundColor(this, &SPZ_SkillTreeSNode_Base::GetNodeBackgroundColor)
			.OnMouseButtonDown(this, &SPZ_SkillTreeSNode_Base::OnMouseDown)

			[
				SNew(SHorizontalBox)
				//LeftPins AREA
				+ SHorizontalBox::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Fill)
					.AutoWidth()
					[
						SAssignNew(LeftNodeBox, SVerticalBox)

					]
				+ SHorizontalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					[
						SNew(SOverlay)
						// INPUT PIN AREA
						+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Top)
							[
								SAssignNew(TopPinBox, SHorizontalBox)
							]
						// OUTPUT PIN AREA
						+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Bottom)
							[
								SAssignNew(BottomPinBox, SHorizontalBox)
							]
						//NodeWidget
						+ SOverlay::Slot()
							.HAlign(HAlign_Center)
							.VAlign(VAlign_Center)
							.Padding(0.0f, NodeBodyPadding)
							[
								SAssignNew(NodeWidget, SOverlay)
							]
						//ERROR
						+ SOverlay::Slot()
							.HAlign(HAlign_Right)
							.VAlign(VAlign_Top)
							.Padding(0.0f, -NodeBodyPadding - 10.0f)
							[
								SNew(SOverlay)
								+ SOverlay::Slot()
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Center)
									[
										SNew(SImage)
										.Image(ErrorImage)
										.ColorAndOpacity(ErrorColor)

									]
								+ SOverlay::Slot()
									.HAlign(HAlign_Right)
									.VAlign(VAlign_Center)
									.Padding(ErrorImageSize.X, 0, 0, 0)
									[
										SAssignNew(ErrorText, SErrorText)
										.BackgroundColor(this, &SPZ_SkillTreeSNode_Base::GetErrorColor)
										.ToolTipText(this, &SPZ_SkillTreeSNode_Base::GetErrorMsgToolTip)
									]
							]

					]
				//RightPins AREA
				+ SHorizontalBox::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Fill)
					.AutoWidth()
					[
						SAssignNew(RightNodeBox, SVerticalBox)
					]

			]
		];

	TopPinBox->SetVisibility(GetTopPinsBoxVisibility());
	BottomPinBox->SetVisibility(GetBottomPinsBoxVisibility());

	CreateNodeWidget();
	CreateCommentBubble();
	CreatePinWidgets();

	ErrorReporting = ErrorText;
	ErrorReporting->SetError(ErrorMsg);
}

void SPZ_SkillTreeSNode_Base::CreateNodeWidget()
{

	const float IconSize = 24.0f;
	const FSlateBrush* NodeImage = GetNodeImage();
	FVector2D ImageSize = FVector2D(0, 0);
	if (NodeImage)
	{
		ImageSize = NodeImage->GetImageSize();
	}

	NodeWidget->AddSlot()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SAssignNew(NodeWidget_TopPart, SOverlay)
				]
			+ SVerticalBox::Slot()
				.AutoHeight()
				[

					SNew(SBorder)
						.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.ColorSpill"))
						.BorderBackgroundColor(GetNodeTitleColor())
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.Visibility(EVisibility::SelfHitTestInvisible)
						[
							SNew(SHorizontalBox)


							+ SHorizontalBox::Slot()
								.Padding(4.0f, 4.0f)
								[
									SNew(SVerticalBox)
									+ SVerticalBox::Slot()
										.AutoHeight()
										[
											SNew(SOverlay)

											+SOverlay::Slot()
												.HAlign(HAlign_Left)
												.VAlign(VAlign_Center)
												[
													SNew(SImage)
													.Image(NodeImage)
												]
											+ SOverlay::Slot()
												.HAlign(HAlign_Right)
												.VAlign(VAlign_Center)
												.Padding(ImageSize.X, 0, 0, 0)
												[
													SNew(STextBlock)
													.Text(GetNodeName())
													.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 16))
												]

										]
									+ SVerticalBox::Slot()
										.AutoHeight()
										[
											SAssignNew(AdditionalNodeInfo, SVerticalBox)
										]

								]

						]
				]

			+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SAssignNew(NodeWidget_BottomPart, SOverlay)
				]
		];

	CreateNodeWidget_TopPart();
	CreateNodeWidget_BottomPart();
	FillAdditionalNodeInfo();
}

void SPZ_SkillTreeSNode_Base::CreateCommentBubble()
{
	TSharedPtr<SCommentBubble> CommentBubble;
	const FSlateColor CommentColor = FLinearColor::White;

	SAssignNew(CommentBubble, SCommentBubble)
		.GraphNode(GraphNode)
		.Text(this, &SGraphNode::GetNodeComment)
		.OnTextCommitted(this, &SGraphNode::OnCommentTextCommitted)
		.ColorAndOpacity(CommentColor)
		.AllowPinning(true)
		.EnableTitleBarBubble(true)
		.EnableBubbleCtrls(true)
		.GraphLOD(this, &SGraphNode::GetCurrentLOD)
		.IsGraphNodeHovered(this, &SGraphNode::IsHovered);

	GetOrAddSlot(ENodeZone::TopCenter)
		.SlotOffset(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetOffset))
		.SlotSize(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetSize))
		.AllowScaling(TAttribute<bool>(CommentBubble.Get(), &SCommentBubble::IsScalingAllowed))
		.VAlign(VAlign_Top)
		[
			CommentBubble.ToSharedRef()
		];
}






void SPZ_SkillTreeSNode_Base::CreatePinWidgets()
{
	UPZ_SkillTreeEdNode_Base* StateNode = CastChecked<UPZ_SkillTreeEdNode_Base>(GraphNode);

	for (const auto& LPin : StateNode->Pins)
	{
		if (!LPin->bHidden)
		{
			TSharedPtr<SGraphPin> NewPin = CreatePinWidget(LPin);
			AddPin(NewPin.ToSharedRef());
		}
	}
}

void SPZ_SkillTreeSNode_Base::CreateStandardPinWidget(UEdGraphPin* Pin)
{
	Super::CreateStandardPinWidget(Pin);
}

TSharedPtr<SGraphPin> SPZ_SkillTreeSNode_Base::CreatePinWidget(UEdGraphPin* Pin) const
{
	return SNew(SPZ_SSkillTreeGraphPin, Pin);
}


void SPZ_SkillTreeSNode_Base::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
	PinToAdd->SetOwner(SharedThis(this));


	const UEdGraphPin* PinObj = PinToAdd->GetPinObj();
	const bool bAdvancedParameter = PinObj && PinObj->bAdvancedView;
	if (bAdvancedParameter)
	{
		PinToAdd->SetVisibility(TAttribute<EVisibility>(PinToAdd, &SGraphPin::IsPinVisibleAsAdvanced));
	}


	if (UPZ_SkillTreeEdNode_Base* LEdNode = Cast<UPZ_SkillTreeEdNode_Base>(GraphNode))
	{
		if (PinToAdd->GetDirection() == EEdGraphPinDirection::EGPD_Input)
		{
			if (PinObj->PinType.PinSubCategory == FPZ_SkillTreeEditorConstant::PinSubCategory_TopBottom)
			{
				TopPinBox->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.FillWidth(1.0f)
					.Padding(20.0f, 0.0f)
					[
						PinToAdd
					];

			}
			else
			{
				LeftNodeBox->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.FillHeight(1.0f)
					.Padding(0.0f, 20.0f)
					[
						PinToAdd
					];
			}

			InputPins.Add(PinToAdd);

		}
		else 
		{
			if (PinObj->PinType.PinSubCategory == FPZ_SkillTreeEditorConstant::PinSubCategory_TopBottom)
			{
				BottomPinBox->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.FillWidth(1.0f)
					.Padding(20.0f, 0.0f)
					[
						PinToAdd
					];

			}
			else
			{
				RightNodeBox->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.FillHeight(1.0f)
					.Padding(0.0f, 20.0f)
					[
						PinToAdd
					];
			}
			OutputPins.Add(PinToAdd);
		}


	}
}



void SPZ_SkillTreeSNode_Base::SetOwner(const TSharedRef<SGraphPanel>& OwnerPanel)
{
	SGraphNode::SetOwner(OwnerPanel);

	for (auto& ChildWidget : SubNodes)
	{
		if (ChildWidget.IsValid())
		{
			ChildWidget->SetOwner(OwnerPanel);
			OwnerPanel->AttachGraphEvents(ChildWidget);
		}
	}
}




bool SPZ_SkillTreeSNode_Base::IsNameReadOnly() const
{
	return false;
}









FText SPZ_SkillTreeSNode_Base::GetNodeName() const
{
	return FText::FromString("BaseNode");
}




FLinearColor SPZ_SkillTreeSNode_Base::GetNodeTitleColor() const
{
	return FLinearColor(0.6f, 0.6f, 0.6f);
}

FLinearColor SPZ_SkillTreeSNode_Base::GetNodeBackgroundColor_Default() const
{
	return FLinearColor(0.15f, 0.15f, 0.15f);
}

FSlateColor SPZ_SkillTreeSNode_Base::GetNodeBackgroundColor() const
{
	UPZ_SkillTreeEdNode_Base* STGraphNode = Cast<UPZ_SkillTreeEdNode_Base>(GraphNode);
	UPZ_SkillTreeEdNode_Base* STParentNode = STGraphNode ? Cast<UPZ_SkillTreeEdNode_Base>(STGraphNode->ParentNode) : nullptr;
	const bool bSelectedSubNode = STParentNode && GetOwnerPanel().IsValid() && GetOwnerPanel()->SelectionManager.SelectedNodes.Contains(GraphNode);
	UPZ_SkillTreeRBaseNode* STRNode = Cast<UPZ_SkillTreeRBaseNode>(STGraphNode->RNode);
	const bool bUseCustomColor = STRNode && STRNode->DoUseCustomColor;
	return bSelectedSubNode ? FSlateColor(FLinearColor::Red) : bUseCustomColor ? STRNode->CustomColor : FSlateColor(GetNodeBackgroundColor_Default());
}

const FSlateBrush* SPZ_SkillTreeSNode_Base::GetBackgroundImage() const
{
	return FEditorStyle::GetBrush("Graph.StateNode.Body");
}

const FSlateBrush* SPZ_SkillTreeSNode_Base::GetNodeImage() const
{
	return FPZ_SkillTreeEditorStyle::Get()->GetBrush(FPZ_SkillTreeEditorStyle::NodeIcon_DefaultIcon);
}


const float SPZ_SkillTreeSNode_Base::GetNodeBodyPadding() const
{
	return 20.0f;
}

const FSlateBrush* SPZ_SkillTreeSNode_Base::GetErrorImage() const
{
	return ErrorMsg.IsEmpty() ? nullptr : FPZ_SkillTreeEditorStyle::Get()->GetBrush("SkillTreeEditor.NodeError");
}

const EVisibility SPZ_SkillTreeSNode_Base::GetTopPinsBoxVisibility() const
{
	return EVisibility::Visible;
}

const EVisibility SPZ_SkillTreeSNode_Base::GetBottomPinsBoxVisibility() const
{
	return EVisibility::Visible;
}





void SPZ_SkillTreeSNode_Base::AddSubNode(TSharedPtr<SGraphNode> SubNodeWidget)
{
	SubNodes.Add(SubNodeWidget);
}

void SPZ_SkillTreeSNode_Base::FillAdditionalNodeInfo()
{
	AdditionalNodeInfo_LinesArray.Empty();
	//
	GetAdditionalNodeInfo(AdditionalNodeInfo_LinesArray);

	for (int32 Index = 0; Index < AdditionalNodeInfo_LinesArray.Num(); Index++)
	{
		AdditionalNodeInfo->AddSlot()
			.AutoHeight()
			[
				SNew(STextBlock)
					.Text(FText::FromString(AdditionalNodeInfo_LinesArray[Index]))
					.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 8))
			];		
	}
}

void SPZ_SkillTreeSNode_Base::GetAdditionalNodeInfo(TArray<FString>& AdditionalInfoArray)
{
	if (EdBaseNode->RNode->IsRootNode) AdditionalInfoArray.Add("Root Node");
	if (EdBaseNode->RNode->CustomName != "") AdditionalInfoArray.Add(EdBaseNode->RNode->CustomName.ToString());
}



TSharedRef<SGraphNode> SPZ_SkillTreeSNode_Base::GetNodeUnderMouse(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	TSharedPtr<SGraphNode> SubNode = GetSubNodeUnderCursor(MyGeometry, MouseEvent);
	return SubNode.IsValid() ? SubNode.ToSharedRef() : StaticCastSharedRef<SGraphNode>(AsShared());
}

TSharedPtr<SGraphNode> SPZ_SkillTreeSNode_Base::GetSubNodeUnderCursor(const FGeometry& WidgetGeometry, const FPointerEvent& MouseEvent)
{
	TSharedPtr<SGraphNode> ResultNode;

	// We just need to find the one WidgetToFind among our descendants.
	TSet< TSharedRef<SWidget> > SubWidgetsSet;
	for (int32 i = 0; i < SubNodes.Num(); i++)
	{
		SubWidgetsSet.Add(SubNodes[i].ToSharedRef());
	}

	TMap<TSharedRef<SWidget>, FArrangedWidget> Result;
	FindChildGeometries(WidgetGeometry, SubWidgetsSet, Result);

	if (Result.Num() > 0)
	{
		FArrangedChildren ArrangedChildren(EVisibility::Visible);
		Result.GenerateValueArray(ArrangedChildren.GetInternalArray());

		const int32 HoveredIndex = SWidget::FindChildUnderMouse(ArrangedChildren, MouseEvent);
		if (HoveredIndex != INDEX_NONE)
		{
			ResultNode = StaticCastSharedRef<SGraphNode>(ArrangedChildren[HoveredIndex].Widget);
		}
	}

	return ResultNode;
}

FReply SPZ_SkillTreeSNode_Base::OnMouseDown(const FGeometry& SenderGeometry, const FPointerEvent& MouseEvent)
{

	UPZ_SkillTreeEdNode_Base* STEdNode = Cast<UPZ_SkillTreeEdNode_Base>(GraphNode);
	if (STEdNode && STEdNode->IsSubNode())
	{
		auto OwnerPanel = GetOwnerPanel();
		if (OwnerPanel.IsValid())
		{

			OwnerPanel->SelectionManager.ClickedOnNode(GraphNode, MouseEvent);
			return FReply::Handled();
		}
		else
			return FReply::Unhandled();

	}

	return FReply::Unhandled();
}

void SPZ_SkillTreeSNode_Base::MoveTo(const FVector2D& NewPosition, FNodeSet& NodeFilter)
{
	Super::MoveTo(NewPosition, NodeFilter);

	EdBaseNode->RNode->TempUIPositionOnCompile = NewPosition;


}
