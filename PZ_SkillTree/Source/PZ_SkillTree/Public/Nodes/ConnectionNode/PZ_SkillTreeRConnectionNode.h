// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/BaseNode/PZ_SkillTreeRBaseNode.h"
#include "../../PZ_SkillTreeNodesInfo.h"
#include "PZ_SkillTreeRConnectionNode.generated.h"




UCLASS(Blueprintable)
class PZ_SKILLTREE_API UPZ_SkillTreeRConnectionNode : public UPZ_SkillTreeRBaseNode
{
	GENERATED_BODY()

//Constructor
public:

	UPZ_SkillTreeRConnectionNode();


//c++ public methods
public:

	virtual bool OnExecute(UPZ_SkillTreeContext* SkillTreeContext) override;
	

	//......................................................................................................//



//Blueprint values
public:




	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Connection Settings")
		FName ConnectionName;

	UPROPERTY(BlueprintReadOnly, Category = "Connection Settings")
		ESkillTreeConnectionType ConnectionType;



//only for editor settings
#if WITH_EDITORONLY_DATA


#endif


};
