// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BehaviorTree/BlackboardData.h"
#include "SkillTreeBlackBoard/SkillTreeBlackboardData.h"

#include "PZ_SkillTree_Editor.generated.h"

class UPZ_SkillTreeRBaseTreeElement;
class UPZ_SkillTreeRBaseNode;
class UPZ_SkillTreeREventNode;
class UPZ_SkillTreeRSkillNode;
class UPZ_SkillTreeRUINode;
class UPZ_SkillTreeRConnectionNode;

UCLASS()
class PZ_SKILLTREE_API UPZ_SkillTree_Editor : public UObject
{
	GENERATED_BODY()

//constructor
public:

	UPZ_SkillTree_Editor();


//c++ private values
private:





//c++ public values
public:

//EditorSave
#if WITH_EDITORONLY_DATA


	UPROPERTY()
		bool NeedToRebuild = true;
	    bool NeedCompileUI = true;

	UPROPERTY()
		class UEdGraph* StructureEdGraph = nullptr;//чтобы не удалялся. Он же является сохранением редактора
	UPROPERTY()
		class UEdGraph* UIPositionEdGraph = nullptr;


#endif



//c++ public methods
public:

#if WITH_EDITOR

	void CleanSkillTree();

#endif


//c++ protected methods
protected:



//..........................................




//Blueprint methods
public:

	UPZ_SkillTreeRBaseNode* GetUIRootNode(); //TODO MB DEL 

	void GetRootNodes(TArray<UPZ_SkillTreeRBaseTreeElement*>& RootNodes);

//Blueprint values
public:

	UPZ_SkillTreeRBaseNode* UIRoot = nullptr;// Root нода UI. Нужна для компиляции скилл нод


	///////compiled/////////////////////

	UPROPERTY(BlueprintReadOnly)
		TArray<UPZ_SkillTreeRBaseTreeElement*> CompiledNodes;

	UPROPERTY(BlueprintReadOnly)
		TMap<FName,UPZ_SkillTreeREventNode*> CompiledEventNodes; 

	UPROPERTY(BlueprintReadOnly)
		TMap<FName, UPZ_SkillTreeRConnectionNode*> InConnectionNodes;
	UPROPERTY(BlueprintReadOnly)
		TMap<FName, UPZ_SkillTreeRConnectionNode*> OutConnectionNodes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FSkillTreeBlackboardEntry> SkillTreeBlackBoard;
	

/////////////////////////////////////////////////////





/////////Игровые параметры/////////////





///////////////////////////////////





////////настройки редактора и компиляции/////
#if WITH_EDITORONLY_DATA



#endif
///////////////////////////////////////////////

};
