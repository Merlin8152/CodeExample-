// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Nodes/BaseTreeElement/PZ_SkillTreeRBaseTreeElement.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../PZ_SkillTreeNodesInfo.h"
#include "PZ_SkillTreeRBaseNode.generated.h"




class UPZ_SkillTreeContext;
class UPZ_SkillTreeRUINode;






UCLASS()
class PZ_SKILLTREE_API UPZ_SkillTreeRBaseNode : public UPZ_SkillTreeRBaseTreeElement
{
	GENERATED_BODY()
	
//Constructor
public:

	UPZ_SkillTreeRBaseNode();




//c++ public methods
public:


	UPROPERTY(BlueprintReadOnly)
		UPZ_SkillTreeRUINode* UINode = nullptr; // ссылка на настройки UI


	void FindNextNodesWithUI(TArray<UPZ_SkillTreeRBaseNode*>& InNextNodes);
	void FindPrevNodesWithUI(TArray<UPZ_SkillTreeRBaseNode*>& InPrevNodes);





	//......................................................................................................//

//Blueprint values
public:


	//only for editor settings
#if WITH_EDITORONLY_DATA


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool DoUseCustomColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor CustomColor = FLinearColor(1, 1, 1, 1);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName CustomName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Skill UI Settings")
		FVector2D TempUIPositionOnCompile; // временные коорданаты нод в Structure режиме

#endif
};
