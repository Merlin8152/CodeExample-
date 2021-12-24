// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/BaseTreeElement/PZ_SkillTreeRBaseTreeElement.h"


#include "PZ_SkillTreeContext.h"


UPZ_SkillTreeRBaseTreeElement::UPZ_SkillTreeRBaseTreeElement()
{

}






UPZ_SkillTreeRBaseTreeElement* UPZ_SkillTreeRBaseTreeElement::ChoseNextNode(UPZ_SkillTreeContext* SkillTreeContext) const
{
	if (!SkillTreeContext || NextNodes.Num() == 0) return nullptr;


	UPZ_SkillTreeRBaseTreeElement* NextNode = NextNodes[0];

	return NextNode;
}





#if WITH_EDITORONLY_DATA

void UPZ_SkillTreeRBaseTreeElement::ResetNavigationNode()
{
	NextNodes.Empty();
	ParentNodes.Empty();
}

#endif


