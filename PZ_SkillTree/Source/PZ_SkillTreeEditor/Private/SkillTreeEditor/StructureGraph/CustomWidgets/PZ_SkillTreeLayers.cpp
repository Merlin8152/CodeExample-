// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTreeLayers.h"

#include "../Nodes/SkillNode/PZ_SkillTreeEdNode_Skill.h"
#include "../Nodes/LayerNode/PZ_SkillTreeEdNode_Layer.h"

void SPZ_Layers::Construct(const FArguments& InArgs)
{
	SkillNode = InArgs._SkillNode;


	SBorder::Construct(SBorder::FArguments()
		.BorderImage(FEditorStyle::GetBrush("Menu.Background"))
						   
		.Padding(5)
		[
			SAssignNew(LayersBox, SVerticalBox)

		]

	);
	UpdateLayers();
}

void SPZ_Layers::UpdateLayers()
{
	LayersBox.Get()->ClearChildren();
	int i = 0;
	for (const auto& Layer : SkillNode->Layers)
	{
		LayersBox.Get()->AddSlot()[SNew(SPZ_Layer)
			.LayerIndex(i).OnLayerClick(SPZ_Layer::FOnLayerClick::CreateSP(this, &SPZ_Layers::OnLayerClick)).IsSelect(SkillNode->CurrentLayer == i)
			];

		i++;
	}
	//TODO
}

FReply SPZ_Layers::OnLayerClick(int LayerIndex, const FPointerEvent&)
{
	SkillNode->SetLayer(LayerIndex);
	return FReply::Handled();
}

void SPZ_Layer::Construct(const FArguments& InArgs)
{
	LayerIndex = InArgs._LayerIndex;
	OnLayerClick = InArgs._OnLayerClick;
	IsSelect = InArgs._IsSelect;
	FLinearColor BorderColor = IsSelect ? FLinearColor(255, 0, 0) : FLinearColor(0, 0, 0);
	SBorder::Construct(SBorder::FArguments()
						   .BorderBackgroundColor(FSlateColor(BorderColor))
		.Padding(5)
		.OnMouseButtonDown(this, &SPZ_Layer::OnMouseDown)
		[
			SNew(STextBlock)
			.Text(FText::FromString(FString::FromInt(LayerIndex)))

		]

	);

}

FReply SPZ_Layer::OnMouseDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		if (OnLayerClick.IsBound())
		{
			return OnLayerClick.Execute(LayerIndex, MouseEvent);
		}
		
	}
	return FReply::Unhandled();
}




