// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode/PZ_SkillTreeSNode_Base.h"


class UPZ_SkillTreeEdNode_Layer;
class UPZ_SkillTreeRLayerNode;


class SPZ_SkillTreeSNode_Layer : public SPZ_SkillTreeSNode_Base
{

	typedef SPZ_SkillTreeSNode_Base Super;
	typedef SPZ_SkillTreeSNode_Layer Self;


public:

	SLATE_BEGIN_ARGS(SPZ_SkillTreeSNode_Layer) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UPZ_SkillTreeEdNode_Layer* InNode);


	virtual void UpdateGraphNode_ResetStage() override;
	virtual void CreateNodeWidget_TopPart() override;
	virtual void CreateNodeWidget_BottomPart() override;


	virtual void GetAdditionalNodeInfo(TArray<FString>& AdditionalInfoArray) override;


	virtual FText GetNodeName() const override;
	virtual FLinearColor GetNodeTitleColor()  const override;

	virtual const FSlateBrush* GetBackgroundImage()  const override;
	virtual const FSlateBrush* GetNodeImage()  const override;

	virtual const float GetNodeBodyPadding() const override;


	virtual void AddCondition(TSharedPtr<SGraphNode> ConditionWidget);
	virtual void AddUnlockAction(TSharedPtr<SGraphNode> UnlockActionWidget);

public:

	UPZ_SkillTreeEdNode_Layer* EdLayerNode = nullptr;
	UPZ_SkillTreeRLayerNode* RLayerNode = nullptr;


protected:
	TSharedPtr<SVerticalBox> ConditionsBox;
	TSharedPtr<SVerticalBox> UnlockActionBox;
};
