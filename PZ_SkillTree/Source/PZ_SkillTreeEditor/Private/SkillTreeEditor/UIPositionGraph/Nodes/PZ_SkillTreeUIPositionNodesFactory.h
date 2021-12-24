// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EdGraphUtilities.h"


struct FPZ_SkillTreeUIPositionGraphNodeFactory : public FGraphPanelNodeFactory
{
	TSharedPtr<class SGraphNode> CreateNode(class UEdGraphNode* InNode) const override;
};


struct FPZ_SkillTreeUIPositionGraphPinFactory : public FGraphPanelPinFactory
{
	TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* Pin) const override;
};