// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

//#include "PZ_SkillTreeNodesInfo.h"
//
//#include "SkillTreeBlackBoard/SkillTreeBlackboardData.h"
//
#include "PZ_SkillTreeContextItem_Base.generated.h"




//class UPZ_SkillTree_Editor;
//class UPZ_SkillTreeRBaseTreeElement;
class UPZ_SkillTreeRBaseTreeElement;
class UPZ_SkillTreeContext;
//class UPZ_SkillTreeREventNode;
//class UPZ_SkillTreeRUINode;
//class UPZ_SkillTreeBlackboardKeyType;
//class UPZ_SkillTreeComponent;









UCLASS(BlueprintType)
class PZ_SKILLTREE_API UPZ_SkillTreeContextItem_Base : public UObject
{
	GENERATED_BODY()


//constructor
public:

	UPZ_SkillTreeContextItem_Base() {};
	UPZ_SkillTreeContextItem_Base(UPZ_SkillTreeRBaseTreeElement* InSkillTreeNode, UPZ_SkillTreeContext* InSkillTreeContext) 
		: SkillTreeNode(InSkillTreeNode), SkillTreeContext(InSkillTreeContext)
	{};

	void UpdateNext(TArray<UPZ_SkillTreeContextItem_Base*>& UpdatedNodes);
	void UpdatePrevious(TArray<UPZ_SkillTreeContextItem_Base*>& UpdatedNodes);
	void UpdateNode(TArray<UPZ_SkillTreeContextItem_Base*>& UpdatedNodes);
	void OnExecute();

	//--------virtual--------//
	virtual void OnExecute_Impl();
	virtual bool IsNeedContinueUpdateNext(TArray<UPZ_SkillTreeContextItem_Base*>& UpdatedNodes);
	virtual bool IsNeedContinueUpdatePrevious(TArray<UPZ_SkillTreeContextItem_Base*>& UpdatedNodes);
	virtual void OnUpdate();
	virtual void FindNextNodesToUpdate(TArray<UPZ_SkillTreeContextItem_Base*>& NodesToUpdate);
	virtual void FindPreviousNodesToUpdate(TArray<UPZ_SkillTreeContextItem_Base*>& NodesToUpdate);
	//--------virtual--------//

	bool IsOpen = false;

	TArray<UPZ_SkillTreeContextItem_Base*> NextContextNodes; //устанавливаются на этапе линковки во время компиляции
	TArray<UPZ_SkillTreeContextItem_Base*> ParentContextNodes;

	UPZ_SkillTreeRBaseTreeElement* SkillTreeNode;
	UPZ_SkillTreeContext* SkillTreeContext;


	//ищет соседние ноды заданного класса (первые ноды нужного класса подключенные к In(ParentNodes) пинам в дереве)
	// т.к при передаче класса отличного от UPZ_SkillTreeContextItem_Base или его потомков, результата не будет, оставлен static_assert
	template<class T>
	void GetInRNodesByClass(TArray<T*>& InArray);

	//ищет соседние ноды заданного класса (первые ноды нужного класса подключенные к Out(NextNodes) пинам в дереве)
	// т.к при передаче класса отличного от UPZ_SkillTreeContextItem_Base или его потомков, результата не будет, оставлен static_assert
	template<class T>
	void GetOutRNodesByClass(TArray<T*>& InArray);


//c++ public methods:
public:


//c++ private methods:
private:




	
//Blueprint public methods:
public:


//c++ public Values
public:



//c++ private Values
private:




};





template<class T>
inline void UPZ_SkillTreeContextItem_Base::GetInRNodesByClass(TArray<T*>& InArray)
{
	static_assert(std::is_base_of<UPZ_SkillTreeContextItem_Base, T>(), "UPZ_SkillTreeContextItem_Base or childs class only allowed");

	for (const auto& ParentNode : ParentContextNodes)
	{
		if (T* CastedNode = Cast<T>(ParentNode))
		{
			InArray.AddUnique(CastedNode);
		}
		else
		{
			ParentNode->GetInRNodesByClass<T>(InArray);
		}
	}
}

template<class T>
inline void UPZ_SkillTreeContextItem_Base::GetOutRNodesByClass(TArray<T*>& InArray)
{
	static_assert(std::is_base_of<UPZ_SkillTreeContextItem_Base, T>(), "UPZ_SkillTreeContextItem_Base or childs class only allowed");

	for (const auto& NextNode : NextContextNodes)
	{
		if (T* CastedNode = Cast<T>(NextNode))
		{
			InArray.AddUnique(CastedNode);
		}
		else
		{
			NextNode->GetOutRNodesByClass<T>(InArray);
		}
	}
}
