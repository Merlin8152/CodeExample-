// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeEditor/StructureGraph/Nodes/ConnectionNode/PZ_SkillTreeEdNode_Connection.h"

#include "Nodes/ConnectionNode/PZ_SkillTreeRConnectionNode.h"


#include "SkillTreeEditor/StructureGraph/Graph/PZ_SkillTreeStructureEdGraphSchema.h"
#include "PZ_SkillTree_Editor.h"
#include "SkillTreeEditor/PZ_SkillTreeEditorConstant.h"


#define LOCTEXT_NAMESPACE "SkillTreeEditor"

UPZ_SkillTreeEdNode_Connection::UPZ_SkillTreeEdNode_Connection()
{
	bCanRenameNode = false;
}


void UPZ_SkillTreeEdNode_Connection::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, FPZ_SkillTreeEditorConstant::PinCategory_Main, FPZ_SkillTreeEditorConstant::PinSubCategory_TopBottom, TEXT("In"));
	CreatePin(EGPD_Output, FPZ_SkillTreeEditorConstant::PinCategory_Main, FPZ_SkillTreeEditorConstant::PinSubCategory_TopBottom, TEXT("Out"));
}


bool UPZ_SkillTreeEdNode_Connection::CanDuplicateNode() const
{
	return true;
}

bool UPZ_SkillTreeEdNode_Connection::CanUserDeleteNode() const
{
	return true;
}





ESkillTreeNodeType UPZ_SkillTreeEdNode_Connection::GetNodeType() const
{
	return ESkillTreeNodeType::ConnectionNode;
}



void UPZ_SkillTreeEdNode_Connection::CompileThisNodeInfo(UPZ_SkillTree_Editor* SkillTree)
{
	Super::CompileThisNodeInfo(SkillTree);

	if (UPZ_SkillTreeRConnectionNode* RCNode = Cast<UPZ_SkillTreeRConnectionNode>(RNode))
	{
		if (IsHaveOutConnection(FPZ_SkillTreeEditorConstant::PinCategory_Main))
		{
			RCNode->ConnectionType = ESkillTreeConnectionType::InConnection;
			SkillTree->InConnectionNodes.Add(RCNode->ConnectionName, RCNode);
		}
		else
		{
			RCNode->ConnectionType = ESkillTreeConnectionType::OutConnection;
			SkillTree->OutConnectionNodes.Add(RCNode->ConnectionName, RCNode);
		}
		
	}
}




void UPZ_SkillTreeEdNode_Connection::CompileError(UPZ_SkillTree_Editor* SkillTree)
{
	ErrorMsg = FString();

	if (UPZ_SkillTreeRConnectionNode* RCNode = Cast<UPZ_SkillTreeRConnectionNode>(RNode))
	{
		if (IsHaveOutConnection(FPZ_SkillTreeEditorConstant::PinCategory_Main) && SkillTree->InConnectionNodes.Contains(RCNode->ConnectionName)
			||
			IsHaveInConnection(FPZ_SkillTreeEditorConstant::PinCategory_Main) && SkillTree->OutConnectionNodes.Contains(RCNode->ConnectionName))
		{
			ErrorMsg = "Node name already exist";
		}

	}
}







void UPZ_SkillTreeEdNode_Connection::OnNodeDoubleClicked()
{
	// TODO....
}

void UPZ_SkillTreeEdNode_Connection::OnChangedProperties(const FName& PropertyName) const
{
	Super::OnChangedProperties(PropertyName);

	// TODO....
}





bool UPZ_SkillTreeEdNode_Connection::CanContainsSubNode(UClass* SubNodeClass)
{
	return false;
}

void UPZ_SkillTreeEdNode_Connection::PostPlacedNewNode()
{

}

