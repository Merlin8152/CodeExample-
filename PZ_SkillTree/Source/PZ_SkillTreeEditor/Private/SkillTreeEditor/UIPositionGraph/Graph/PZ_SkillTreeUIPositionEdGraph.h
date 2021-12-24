// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "PZ_SkillTreeUIPositionEdGraph.generated.h"


class UPZ_SkillTree_Editor;
class FPZ_SkillTreeGraph;
class UPZ_SkillTreeRSkillNode;
class UPZ_SkillTreeRBaseNode;
class UPZ_SkillTreeRBaseTreeElement;

UCLASS()
class UPZ_SkillTreeUIPositionEdGraph : public UEdGraph
{
	GENERATED_BODY()

//c++ public methods
public:

	void RebuildGraph(); // пересоздание всех нод
	void BuildUINodes(UPZ_SkillTreeRBaseTreeElement* RNode, TArray<UPZ_SkillTreeRBaseTreeElement*>& VisitedNodes);

	void CompileGraph();

//c++ private methods
private:

	void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);

//c++ protected methods
protected:


	virtual void NotifyGraphChanged(const FEdGraphEditAction& Action) override;


//c++ public values
public:

	UPZ_SkillTree_Editor* SkillTree; // сам объект (Asset)
	FPZ_SkillTreeGraph* SkillTreeGraph; // визуальное представление




//c++ private values
private:

};
