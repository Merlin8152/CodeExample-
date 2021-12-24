// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeEditor/UIPositionGraph/Nodes/BaseNode/PZ_SkillTreeUIPositionEdNode_Base.h"

#include "PZ_SkillTreeUIPositionSNode_Base.h"

#include "../../Graph/PZ_SkillTreeUIPositionEdGraph.h"
#include "PZ_SkillTree_Editor.h"

#include "../../../PZ_SkillTreeEditorStyle.h"

#include "SkillTreeEditor/PZ_SkillTreeEditorConstant.h"
#include "Nodes/BaseNode/PZ_SkillTreeRBaseNode.h"
#include "Nodes/UINode/PZ_SkillTreeRUINode.h"

#include "SkillTreeEditor/StructureGraph/Nodes/EdgePoint/PZ_SkillTreeEdNode_Edge.h"

#define LOCTEXT_NAMESPACE "SkillTreeEditor"

UPZ_SkillTreeUIPositionEdNode_Base::UPZ_SkillTreeUIPositionEdNode_Base()
{
	bCanRenameNode = false;

}




void UPZ_SkillTreeUIPositionEdNode_Base::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, FPZ_SkillTreeEditorConstant::PinCategory_Main, FPZ_SkillTreeEditorConstant::PinSubCategory_TopBottom, TEXT("In"));
	CreatePin(EGPD_Output, FPZ_SkillTreeEditorConstant::PinCategory_Main, FPZ_SkillTreeEditorConstant::PinSubCategory_TopBottom, TEXT("Out"));

}


void UPZ_SkillTreeUIPositionEdNode_Base::PrepareForCopying()
{
	Super::PrepareForCopying();

	RUINode->Rename(nullptr, this, REN_DontCreateRedirectors | REN_DoNotDirty);

}


void UPZ_SkillTreeUIPositionEdNode_Base::AutowireNewNode(UEdGraphPin* FromPin)
{
	Super::AutowireNewNode(FromPin);
}







bool UPZ_SkillTreeUIPositionEdNode_Base::CanDuplicateNode() const
{
	return true;
}

bool UPZ_SkillTreeUIPositionEdNode_Base::CanUserDeleteNode() const
{
	return true;
}

bool UPZ_SkillTreeUIPositionEdNode_Base::CanSplitPin(const UEdGraphPin* Pin) const
{
	return false;
}

bool UPZ_SkillTreeUIPositionEdNode_Base::CanCreateUnderSpecifiedSchema(const UEdGraphSchema* Schema) const
{
	return true;
}








ESkillTreeNodeType UPZ_SkillTreeUIPositionEdNode_Base::GetNodeType() const
{
	return ESkillTreeNodeType::None;
}



UEdGraphPin* UPZ_SkillTreeUIPositionEdNode_Base::GetInputPin(const FName& PinCategory) const
{
	for (UEdGraphPin* Pin : Pins)
	{
		if (Pin->Direction == EEdGraphPinDirection::EGPD_Input && Pin->PinType.PinCategory == PinCategory)
		{
			return Pin;
		}
	}
	
	return nullptr;
}


UEdGraphPin* UPZ_SkillTreeUIPositionEdNode_Base::GetOutputPin(const FName& PinCategory) const
{
	for (UEdGraphPin* Pin : Pins)
	{
		if (Pin->Direction == EEdGraphPinDirection::EGPD_Output && Pin->PinType.PinCategory == PinCategory)
		{
			return Pin;
		}
	}

	return nullptr;
}




















bool UPZ_SkillTreeUIPositionEdNode_Base::CanCreateConnectionTo(const UPZ_SkillTreeUIPositionEdNode_Base* ToNode, FText& ErrorMessage, bool& CreateEdge) const
{
	CreateEdge = true;
	return true;
}


void UPZ_SkillTreeUIPositionEdNode_Base::OnNodeDoubleClicked()
{
	// TODO on childs
}


void UPZ_SkillTreeUIPositionEdNode_Base::OnChangedProperties(const FName& PropertyName) const
{
	SEdNode->UpdateGraphNode();
	this->StaticClass();
}












bool UPZ_SkillTreeUIPositionEdNode_Base::HasOutputConnectionToNode(const UEdGraphNode* TargetNode) const
{
	// проверяем все пины ищем Out
	for (UEdGraphPin* Pin : Pins)
	{
		if (Pin->Direction == EEdGraphPinDirection::EGPD_Output)
		{
			for (UEdGraphPin* ChildInputPin : Pin->LinkedTo)
			{
				UPZ_SkillTreeEdNode_Edge* EdgeNode = Cast<UPZ_SkillTreeEdNode_Edge>(ChildInputPin->GetOwningNode());

				//если соединение через Edge, его не учитываем
				if (EdgeNode)
				{
					if (EdgeNode->GetEndNode() == TargetNode)
					{
						return true;
					}
				}//эсли соединение без посредников - проверяем напрямую
				else if (ChildInputPin->GetOwningNode() == TargetNode)
				{
					return true;
				}
			}
		}
	}

	return false;
}



bool UPZ_SkillTreeUIPositionEdNode_Base::CanContainsSubNode(UClass* SubNodeClass)
{
	return false;
}

void UPZ_SkillTreeUIPositionEdNode_Base::SetPosition(int32 X, int32 Y)
{
	NodePosX = X;
	NodePosY = Y;
}



void UPZ_SkillTreeUIPositionEdNode_Base::DestroyNode()
{
	Super::DestroyNode();
}

