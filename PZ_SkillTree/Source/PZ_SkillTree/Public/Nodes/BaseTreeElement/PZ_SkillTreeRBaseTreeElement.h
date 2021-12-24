// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../PZ_SkillTreeNodesInfo.h"
#include "PZ_SkillTreeRBaseTreeElement.generated.h"




class UPZ_SkillTreeContext;
class UPZ_SkillTreeRUINode;






UCLASS(Abstract)
class PZ_SKILLTREE_API UPZ_SkillTreeRBaseTreeElement : public UObject
{
	GENERATED_BODY()
	
//Constructor
public:

	UPZ_SkillTreeRBaseTreeElement();




//c++ public methods
public:
	//return need to break iterating
	virtual bool OnExecute(UPZ_SkillTreeContext* SkillTreeContext) { return true; };

	//ищет соседние ноды заданного класса (первые ноды нужного класса подключенные к In(ParentNodes) пинам в дереве)
	// т.к при передаче класса отличного от UPZ_SkillTreeRBaseTreeElement или его потомков, результата не будет, оставлен static_assert
	template <class T>
	void GetInRNodesByClass(TArray<T*>& InArray);

	//ищет соседние ноды заданного класса (первые ноды нужного класса подключенные к Out(NextNodes) пинам в дереве)
	// т.к при передаче класса отличного от UPZ_SkillTreeRBaseTreeElement или его потомков, результата не будет, оставлен static_assert
	template <class T>
	void GetOutRNodesByClass(TArray<T*>& InArray);

	virtual UPZ_SkillTreeRBaseTreeElement* ChoseNextNode(UPZ_SkillTreeContext* SkillTreeContext) const;//-1 means no next nodes


#if WITH_EDITORONLY_DATA

	virtual void ResetNavigationNode();

#endif



	//......................................................................................................//

//Blueprint values
public:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Settings")
		bool IsRootNode = false;


	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category = "Settings")
	//	UWidget IsNeedCompile = false;

	UPROPERTY(BlueprintReadOnly)
		int32 MyIndex = 0;
	UPROPERTY(BlueprintReadOnly)
		ESkillTreeNodeType NodeType;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<UPZ_SkillTreeRBaseTreeElement*> NextNodes;//устанавливаются на этапе линковки во время компиляции
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<UPZ_SkillTreeRBaseTreeElement*> ParentNodes;


	//only for editor settings
#if WITH_EDITORONLY_DATA

#endif
};




template<class T>
inline void UPZ_SkillTreeRBaseTreeElement::GetInRNodesByClass(TArray<T*>& InArray)
{
	static_assert(std::is_base_of<UPZ_SkillTreeRBaseTreeElement, T>(),
		"UPZ_SkillTreeRBaseNode or childs class only allowed");

	for (const auto ParentNode : ParentNodes)
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
inline void UPZ_SkillTreeRBaseTreeElement::GetOutRNodesByClass(TArray<T*>& InArray)
{
	static_assert(std::is_base_of<UPZ_SkillTreeRBaseTreeElement, T>(),
		"UPZ_SkillTreeRBaseNode or childs class only allowed");

	for (const auto NextNode : NextNodes)
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
