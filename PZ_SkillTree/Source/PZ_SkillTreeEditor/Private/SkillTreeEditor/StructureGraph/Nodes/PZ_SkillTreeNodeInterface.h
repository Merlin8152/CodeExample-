// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PZ_SkillTreeNodesInfo.h"
#include "PZ_SkillTreeNodeInterface.generated.h"


class UPZ_SkillTree_Editor;
class UPZ_SkillTreeRBaseNode;



// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPZ_SkillTreeNodeInterface : public UInterface
{
	GENERATED_BODY()
};



class IPZ_SkillTreeNodeInterface
{
	GENERATED_BODY()


public:

	virtual ESkillTreeNodeType GetNodeType() const PURE_VIRTUAL(IPZ_SkillTreeNodeInterface::GetNodeType(), return ESkillTreeNodeType::None;);


	//добавил FName - категорию как параметр, т.к пины бывают разные
	virtual UEdGraphPin* GetInputPin(const FName& PinCategory) const PURE_VIRTUAL(IPZ_SkillTreeNodeInterface::GetInputPin(const FName& PinCategory), return nullptr;);
	virtual UEdGraphPin* GetOutputPin(const FName& PinCategory) const PURE_VIRTUAL(IPZ_SkillTreeNodeInterface::GetOutputPin(const FName& PinCategory), return nullptr;);


	virtual void CompileThisNodeInfo(UPZ_SkillTree_Editor* SkillTree) PURE_VIRTUAL(IPZ_SkillTreeNodeInterface::CompileThisNodeInfo(), return;);

	virtual bool IsNeedCompile() PURE_VIRTUAL(IPZ_SkillTreeNodeInterface::IsNeedCompile(), return true;);
	virtual void OnNodeDoubleClicked() PURE_VIRTUAL(IPZ_SkillTreeNodeInterface::OnNodeDoubleClicked(), return;);
	virtual void OnChangedProperties(const FName & PropertyName) const PURE_VIRTUAL(IPZ_SkillTreeNodeInterface::OnChangedProperties(), return;);
};
