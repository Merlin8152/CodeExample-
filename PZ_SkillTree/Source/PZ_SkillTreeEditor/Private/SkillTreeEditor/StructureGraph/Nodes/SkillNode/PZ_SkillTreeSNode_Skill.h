// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode/PZ_SkillTreeSNode_Base.h"


class UPZ_SkillTreeEdNode_Skill;
class UPZ_SkillTreeRSkillNode;
class SPZ_Layers;
	//class UPZ_SkillTreeRLayerNode;

class SPZ_SkillTreeSNode_Skill: public SPZ_SkillTreeSNode_Base
{

	typedef SPZ_SkillTreeSNode_Skill Super;
	typedef SPZ_SkillTreeSNode_Skill Self;


public:

	SLATE_BEGIN_ARGS(SPZ_SkillTreeSNode_Skill) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UPZ_SkillTreeEdNode_Skill* InNode);


	virtual void UpdateGraphNode_ResetStage() override;
	virtual void CreateNodeWidget_TopPart() override;
	virtual void CreateNodeWidget_BottomPart() override;
	virtual void CreateNodeWidget_RightPart() override;


	virtual void GetAdditionalNodeInfo(TArray<FString>& AdditionalInfoArray) override;


	virtual FText GetNodeName() const override;
	virtual FLinearColor GetNodeTitleColor()  const override;

	virtual const FSlateBrush* GetNodeImage()  const override;
	virtual const EVisibility GetTopPinsBoxVisibility() const override;



	virtual void AddLayer(TSharedPtr<SGraphNode> LayerWidget);

	virtual void MoveTo(const FVector2D& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty) override;
protected:



	TSharedPtr<SVerticalBox> LayerBox;
	TSharedPtr<SPZ_Layers> LayersWidget;

public:

	UPZ_SkillTreeEdNode_Skill* EdSkillNode = nullptr;
	UPZ_SkillTreeRSkillNode* RSkillNode = nullptr;

};
