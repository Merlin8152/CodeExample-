// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/BaseNode/PZ_SkillTreeRBaseNode.h"

#include "PZ_SkillTreeRSkillNode.generated.h"


class UPZ_SkillTreeRConditionNode;
class UPZ_SkillTreeRSkillActionNode;



UCLASS(Blueprintable)
class PZ_SKILLTREE_API UPZ_SkillTreeRSkillNode : public UPZ_SkillTreeRBaseNode
{
	GENERATED_BODY()

//Constructor
public:

	UPZ_SkillTreeRSkillNode();


//c++ public methods
public:

	virtual bool OnExecute(UPZ_SkillTreeContext* SkillTreeContext) override;
	

	//......................................................................................................//



//Blueprint values
public:



	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill Settings")
		bool AlwaysCanBeOpen = false; /// ћожго прокачать если преведущ€€ нода ещЄ не прокачена 

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill Settings")
	//	bool IsRootNode = false;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill Settings")
	//	FName SkillName;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill UI Settings")
	//	UTexture2D* SkillIconTexture;

	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Skill UI Settings")
	//	FVector2D UIPosition;

	//UPROPERTY(BlueprintReadOnly, Category = "Skill UI Settings")
	//	bool IsPlacedInUI = false; // если true ноду трогали в UIPosition mode, и координаты из Struct графа больше не учитаваютс€

	UPROPERTY(BlueprintReadOnly, Category = "Skill UI Settings")
		bool IsUIRootNode = false; // нода относительно которой строитс€ граф в UIPosition mode


	UPROPERTY(BlueprintReadOnly)
		UPZ_SkillTreeRConditionNode* ConditionNode = nullptr;

	UPROPERTY(BlueprintReadOnly)
		UPZ_SkillTreeRSkillActionNode* SkillActionNode = nullptr;



//only for editor settings
#if WITH_EDITORONLY_DATA




#endif


};
