// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PZ_SkillTreeNodesInfo.h"
#include "PZ_SkillTreeUIPositionNodeInterface.generated.h"


class UPZ_SkillTree_Editor;
//class UPZ_DialogueSavedBaseNode;
class UPZ_SkillTreeRBaseNode;


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPZ_SkillTreeUIPositionNodeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IPZ_SkillTreeUIPositionNodeInterface
{
	GENERATED_BODY()


public:

	virtual ESkillTreeNodeType GetNodeType() const PURE_VIRTUAL(IPZ_SkillTreeUIPositionNodeInterface::GetNodeType(), return ESkillTreeNodeType::None;);


	//добавил FName - категорию как параметр, т.к пины бывают разные
	virtual UEdGraphPin* GetInputPin(const FName& PinCategory) const PURE_VIRTUAL(IPZ_SkillTreeUIPositionNodeInterface::GetInputPin(const FName& PinCategory), return nullptr;);
	virtual UEdGraphPin* GetOutputPin(const FName& PinCategory) const PURE_VIRTUAL(IPZ_SkillTreeUIPositionNodeInterface::GetOutputPin(const FName& PinCategory), return nullptr;);


	virtual void OnNodeDoubleClicked() PURE_VIRTUAL(IPZ_SkillTreeUIPositionNodeInterface::OnNodeDoubleClicked(), return;);
	virtual void OnChangedProperties(const FName & PropertyName) const PURE_VIRTUAL(IPZ_SkillTreeUIPositionNodeInterface::OnChangedProperties(), return;);
};
