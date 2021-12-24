// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode/PZ_SkillTreeSNode_Base.h"


class UPZ_SkillTreeEdNode_Connection;
class UPZ_SkillTreeRConnectionNode;


class SPZ_SkillTreeSNode_Connection : public SPZ_SkillTreeSNode_Base
{
	typedef SPZ_SkillTreeSNode_Base Super;
	typedef SPZ_SkillTreeSNode_Connection Self;
public:

	SLATE_BEGIN_ARGS(SPZ_SkillTreeSNode_Connection) {}
	SLATE_END_ARGS()

		void Construct(const FArguments& InArgs, UPZ_SkillTreeEdNode_Connection* InNode);


	virtual void GetAdditionalNodeInfo(TArray<FString>& AdditionalInfoArray) override;


	virtual FText GetNodeName() const override;
	virtual FLinearColor GetNodeTitleColor()  const override;
	virtual FLinearColor GetNodeBackgroundColor_Default() const override;

	virtual const FSlateBrush* GetNodeImage()  const override;
	virtual const EVisibility GetTopPinsBoxVisibility() const override;
	virtual const EVisibility GetBottomPinsBoxVisibility() const override;




	virtual void MoveTo(const FVector2D& NewPosition, FNodeSet& NodeFilter) override;
protected:


	TSharedPtr<SVerticalBox> ConditionsBox;
	TSharedPtr<SVerticalBox> UnlockActionBox;

public:

	UPZ_SkillTreeEdNode_Connection* EdConnectionNode = nullptr;
	UPZ_SkillTreeRConnectionNode* RConnectionNode = nullptr;

};
