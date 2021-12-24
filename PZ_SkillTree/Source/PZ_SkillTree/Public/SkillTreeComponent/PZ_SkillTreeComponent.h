// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"


#include "PZ_SkillTreeComponent.generated.h"

class UPZ_SkillTree_Editor;
class UPZ_SkillTreeContext;
class UPZ_SkillTreeRConnectionNode;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PZ_SKILLTREE_API UPZ_SkillTreeComponent : public UActorComponent
{
	GENERATED_BODY()

	friend UPZ_SkillTreeContext;

//constructor
public:

	UPZ_SkillTreeComponent();





//c++ public methods
public:


//c++ protected methods
protected:

	virtual void BeginPlay() override;



//c++ private methods
private:




//c++ public values
public:




//c++ protected values
protected:




//c++ private values
private:





//Blueprint Protected Methods
protected:






//Blueprint Public Methods
public:

	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SkillTree | SkillTreeComponent")
		UPZ_SkillTreeContext* GetSkillTreeByName(FString GraphName) const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SkillTree | SkillTreeComponent")
		UPZ_SkillTree_Editor* GetSkillTreeEditorByName(FString GraphName) const;


	void OnUpdateNextNode_Connection(UPZ_SkillTreeRConnectionNode* InConnectionNode);
	void OnUpdatePrevNode_Connection(UPZ_SkillTreeRConnectionNode* InConnectionNode);
//Blueprint Values
public:



	UPROPERTY(BlueprintReadOnly)
		 TMap<FString, class UPZ_SkillTreeContext*> SkillContexts;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TMap<FString , class UPZ_SkillTree_Editor*> SkillGraphs;
		
};
