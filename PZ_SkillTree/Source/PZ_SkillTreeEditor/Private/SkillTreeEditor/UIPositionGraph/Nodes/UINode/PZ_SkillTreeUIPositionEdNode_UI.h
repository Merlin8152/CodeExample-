// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode/PZ_SkillTreeUIPositionEdNode_Base.h"
#include "PZ_SkillTreeUIPositionEdNode_UI.generated.h"



UCLASS()
class UPZ_SkillTreeUIPositionEdNode_UI : public UPZ_SkillTreeUIPositionEdNode_Base
{
	GENERATED_BODY()

//Constructor
public:

	UPZ_SkillTreeUIPositionEdNode_UI();


//c++ public Methods
public:
	virtual void AllocateDefaultPins() override;

	virtual bool CanDuplicateNode() const override;
	virtual bool CanUserDeleteNode() const override;

	virtual void CompileError() override;

	virtual ESkillTreeNodeType GetNodeType() const override;

	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;

	virtual void OnNodeDoubleClicked() override;
	virtual void OnChangedProperties(const FName& PropertyName) const override;
	

	virtual void DestroyNode() override;

//Blueprint values
public:

	/*
	здесь хранятся компилируемые настройки ноды. Могут быть модифицированны во время CompileThisNodeInfo
	экземпляр класса создается в EdGraphSchema при создании ноды
	настройки чисто для редактора хранятся тоже в RNode, но вырезаются после компиляции
	*/
};
