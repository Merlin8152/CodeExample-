// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Widgets/Layout/SBorder.h"

class UPZ_SkillTreeEdNode_Skill;

class SPZ_Layer : public SBorder
{
public:
	DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnLayerClick, int LayerIndex, const FPointerEvent&);

public:


	SLATE_BEGIN_ARGS(SPZ_Layer) : 
		_LayerIndex(-1), _OnLayerClick(NULL), _IsSelect(false)
	{}

	SLATE_ARGUMENT(int, LayerIndex)
	SLATE_ARGUMENT(FOnLayerClick, OnLayerClick)
	SLATE_ARGUMENT(bool, IsSelect)	
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

protected:
	int LayerIndex = -1;
	bool IsSelect = false;
	FOnLayerClick OnLayerClick;
	FReply OnMouseDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);
};


class SPZ_Layers : public SBorder
{



	SLATE_BEGIN_ARGS(SPZ_Layers) : 
		_SkillNode(NULL)

	{
	}

	SLATE_ARGUMENT(UPZ_SkillTreeEdNode_Skill*, SkillNode)


	SLATE_END_ARGS()



	void Construct(const FArguments& InArgs);

	public:

		void UpdateLayers();
		FReply OnLayerClick(int LayerIndex, const FPointerEvent&);

	protected:
		TSharedPtr<SVerticalBox> LayersBox;
		UPZ_SkillTreeEdNode_Skill* SkillNode = nullptr;
};
