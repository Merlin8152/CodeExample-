// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PZ_SkillTreeNodesInfo.generated.h"




UENUM(BlueprintType)
enum class ESkillTreeNodeType : uint8
{
	None				UMETA(DisplayName = "None"),
	SkillNode			UMETA(DisplayName = "Skill Node"),
	RootSkillNode		UMETA(DisplayName = "Root Skill Node"),
	ActiveSkillNode		UMETA(DisplayName = "Active Skill Node"),
	PassiveSkillNode	UMETA(DisplayName = "Passive Skill Node"),
	EventSkillNode		UMETA(DisplayName = "Event Skill Node"),
	ConditionSkillNode	UMETA(DisplayName = "Condition Skill Node"),
	SkillActionNode		UMETA(DisplayName = "Action Skill Node"),
	SwitcherNode		UMETA(DisplayName = "Switcher Node"),
	ConnectionNode		UMETA(DisplayName = "Connection Node"),
	CustomNode		    UMETA(DisplayName = "Custom Node"),
	UINode	        	UMETA(DisplayName = "UI Node")
};


UENUM(BlueprintType)
enum class ESkillTreeConnectionType : uint8
{
	None				UMETA(DisplayName = "None"),
	InConnection		UMETA(DisplayName = "In Connection Node"),
	OutConnection		UMETA(DisplayName = "Out Connection Node"),
};

