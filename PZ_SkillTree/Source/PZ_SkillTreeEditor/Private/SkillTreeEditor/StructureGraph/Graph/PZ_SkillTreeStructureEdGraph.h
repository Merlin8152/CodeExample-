// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "PZ_SkillTreeStructureEdGraph.generated.h"



class UPZ_SkillTreeEdNode_Base;
class UPZ_SkillTreeEdNode_Skill;
class UPZ_SkillTreeRSkillNode;

class UPZ_SkillTree_Editor;
class FPZ_SkillTreeGraph;



UCLASS()
class UPZ_SkillTreeEdGraph : public UEdGraph
{
	GENERATED_BODY()


//c++ public methods
public:

	void RebuildGraph();


//c++ protected methods
protected:

	virtual void NotifyGraphChanged(const FEdGraphEditAction& Action) override;

//c++ private methods
private:

	void CompileNode(UEdGraphNode* Node);

	void CompileEventNodes();

	void LinkCompiledNodes();
	void LinkUINodes();



	TArray<UPZ_SkillTreeEdNode_Base*> FindRoot();

	void UniqueArrayNames(TArray<FName>& Names);





//c++ public values
public:

	UPZ_SkillTree_Editor* SkillTree = nullptr; // сам объект
	FPZ_SkillTreeGraph* SkillTreeGraph = nullptr; // визуальное представление



//c++ private values
private:

	TArray<UEdGraphNode*> CompilingVisitedNodes;
	
};
