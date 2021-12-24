// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeEditor/StructureGraph/Nodes/CustomNode/PZ_SkillTreeEdNode_Custom.h"

#include "Nodes/CustomNode/PZ_SkillTreeRCustomNode.h"


#include "SkillTreeEditor/StructureGraph/Graph/PZ_SkillTreeStructureEdGraphSchema.h"

#include "SkillTreeEditor/PZ_SkillTreeEditorConstant.h"


#define LOCTEXT_NAMESPACE "SkillTreeEditor"

UPZ_SkillTreeEdNode_Custom::UPZ_SkillTreeEdNode_Custom()
{
	bCanRenameNode = false;
}


void UPZ_SkillTreeEdNode_Custom::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, FPZ_SkillTreeEditorConstant::PinCategory_Main, FPZ_SkillTreeEditorConstant::PinSubCategory_TopBottom, TEXT("In"));
	CreatePin(EGPD_Output, FPZ_SkillTreeEditorConstant::PinCategory_Main, FPZ_SkillTreeEditorConstant::PinSubCategory_TopBottom, TEXT("Out"));
}

bool UPZ_SkillTreeEdNode_Custom::IsHaveUINode() const
{
	UPZ_SkillTreeRCustomNode* CustomNode = Cast<UPZ_SkillTreeRCustomNode>(RNode);
	return CustomNode->IsHaveUI;
}


bool UPZ_SkillTreeEdNode_Custom::CanDuplicateNode() const
{
	return true;
}

bool UPZ_SkillTreeEdNode_Custom::CanUserDeleteNode() const
{
	return true;
}





ESkillTreeNodeType UPZ_SkillTreeEdNode_Custom::GetNodeType() const
{
	return ESkillTreeNodeType::CustomNode;
}



void UPZ_SkillTreeEdNode_Custom::CompileThisNodeInfo(UPZ_SkillTree_Editor* SkillTree)
{
	UPZ_SkillTreeEdNode_Base::CompileThisNodeInfo(SkillTree);


	CompileError(SkillTree);

}




void UPZ_SkillTreeEdNode_Custom::CompileError(UPZ_SkillTree_Editor* SkillTree)
{
	ErrorMsg = FString();

}







void UPZ_SkillTreeEdNode_Custom::OnNodeDoubleClicked()
{
	// TODO....
}

void UPZ_SkillTreeEdNode_Custom::OnChangedProperties(const FName& PropertyName) const
{
	Super::OnChangedProperties(PropertyName);

	// TODO....
}





bool UPZ_SkillTreeEdNode_Custom::CanContainsSubNode(UClass* SubNodeClass)
{
	return false;
}

void UPZ_SkillTreeEdNode_Custom::PostPlacedNewNode()
{

}

