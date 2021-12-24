// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EdGraphUtilities.h"


struct FPZ_SkillTreeGraphNodeFactory : public FGraphPanelNodeFactory
{
	TSharedPtr<class SGraphNode> CreateNode(class UEdGraphNode* InNode) const override;
};


struct FPZ_SkillTreeGraphPinFactory : public FGraphPanelPinFactory
{
	TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* Pin) const override;
};