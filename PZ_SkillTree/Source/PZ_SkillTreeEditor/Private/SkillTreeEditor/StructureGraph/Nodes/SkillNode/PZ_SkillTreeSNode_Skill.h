// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode/PZ_SkillTreeSNode_Base.h"


class UPZ_SkillTreeEdNode_Skill;
class UPZ_SkillTreeRSkillNode;


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



	virtual void GetAdditionalNodeInfo(TArray<FString>& AdditionalInfoArray) override;


	virtual FText GetNodeName() const override;
	virtual FLinearColor GetNodeTitleColor()  const override;

	virtual const FSlateBrush* GetNodeImage()  const override;
	virtual const EVisibility GetTopPinsBoxVisibility() const override;



	virtual void AddCondition(TSharedPtr<SGraphNode> ConditionWidget);
	virtual void AddUnlockAction(TSharedPtr<SGraphNode> UnlockActionWidget);


	virtual void MoveTo(const FVector2D& NewPosition, FNodeSet& NodeFilter) override;
protected:


	TSharedPtr<SVerticalBox> ConditionsBox;
	TSharedPtr<SVerticalBox> UnlockActionBox;

public:

	UPZ_SkillTreeEdNode_Skill* EdSkillNode = nullptr;
	UPZ_SkillTreeRSkillNode* RSkillNode = nullptr;

};
