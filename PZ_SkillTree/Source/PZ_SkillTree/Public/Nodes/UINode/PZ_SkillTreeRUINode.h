// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/BaseTreeElement/PZ_SkillTreeRBaseTreeElement.h"

#include "PZ_SkillTreeRUINode.generated.h"



class UPZ_SkillTreeRBaseNode;

class UPZ_SkillTreeObjectCreator;


UCLASS(Blueprintable)
class PZ_SKILLTREE_API UPZ_SkillTreeRUINode : public UPZ_SkillTreeRBaseTreeElement
{
	GENERATED_BODY()

//Constructor
public:

	UPZ_SkillTreeRUINode();


//c++ public methods
public:

	virtual bool OnExecute(UPZ_SkillTreeContext* SkillTreeContext) override;
	

	//......................................................................................................//



//Blueprint values
public:



	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category = "UI Settings")
		UPZ_SkillTreeObjectCreator* ObjectCreator = nullptr;



	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI Settings")
		FVector2D UIPosition;

	UPROPERTY(BlueprintReadOnly, Category = "UI Settings")
		bool IsPlacedInUI = false; // если true ноду трогали в UIPosition mode, и координаты из Struct графа больше не учитаваются

	UPROPERTY(BlueprintReadOnly, Category = "UI Settings")
		bool IsUIRootNode = false; // нода относительно которой строится граф в UIPosition mode

	UPROPERTY(BlueprintReadOnly)
		UPZ_SkillTreeRBaseNode* RNodeLink = nullptr;



//only for editor settings
#if WITH_EDITORONLY_DATA



#endif


};
