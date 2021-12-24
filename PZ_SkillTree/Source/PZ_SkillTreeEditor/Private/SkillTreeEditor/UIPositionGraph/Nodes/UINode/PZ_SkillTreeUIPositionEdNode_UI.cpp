// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeEditor/UIPositionGraph/Nodes/UINode/PZ_SkillTreeUIPositionEdNode_UI.h"

#include "Nodes/UINode/PZ_SkillTreeRUINode.h"
#include "Nodes/BaseNode/PZ_SkillTreeRBaseNode.h"
#include "SkillTreeEditor/UIPositionGraph/Graph/PZ_SkillTreeUIPositionEdGraphSchema.h"
#include "ToolMenus.h"
#include "SkillTreeEditor/PZ_SkillTreeEditorConstant.h"

#include "SkillTreeWidgetCreator/PZ_SkillTreeWidgetCreator.h"


#define LOCTEXT_NAMESPACE "SkillTreeEditor"

UPZ_SkillTreeUIPositionEdNode_UI::UPZ_SkillTreeUIPositionEdNode_UI()
{
	bCanRenameNode = false;
}


void UPZ_SkillTreeUIPositionEdNode_UI::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, FPZ_SkillTreeEditorConstant::PinCategory_Main, FPZ_SkillTreeEditorConstant::PinSubCategory_TopBottom, TEXT("In"));
	CreatePin(EGPD_Output, FPZ_SkillTreeEditorConstant::PinCategory_Main, FPZ_SkillTreeEditorConstant::PinSubCategory_TopBottom, TEXT("Out"));
}


bool UPZ_SkillTreeUIPositionEdNode_UI::CanDuplicateNode() const
{
	return true;
}

bool UPZ_SkillTreeUIPositionEdNode_UI::CanUserDeleteNode() const
{

	return true;
}

void UPZ_SkillTreeUIPositionEdNode_UI::CompileError()
{
	Super::CompileError();

	if (!RUINode->ObjectCreator)
	{
		ErrorMsg = FString("Add ObjectCreator");
	}
	else
	{
		ErrorMsg = RUINode->ObjectCreator->GetErrorMessage();
	}
}





ESkillTreeNodeType UPZ_SkillTreeUIPositionEdNode_UI::GetNodeType() const
{
	return ESkillTreeNodeType::UINode;
}

void UPZ_SkillTreeUIPositionEdNode_UI::AutowireNewNode(UEdGraphPin* FromPin)
{
	UPZ_SkillTreeUIPositionEdNode_Base::AutowireNewNode(FromPin);

	{
		TArray<UPZ_SkillTreeRBaseTreeElement*> ParentRNodes;
		RUINode->GetInRNodesByClass<UPZ_SkillTreeRBaseTreeElement>(ParentRNodes);

		TArray<UPZ_SkillTreeRBaseTreeElement*> ChildsRNodes;
		RUINode->GetOutRNodesByClass<UPZ_SkillTreeRBaseTreeElement>(ChildsRNodes);

		TArray<UPZ_SkillTreeUIPositionEdNode_UI*> EdSkillNodes;
		GetGraph()->GetNodesOfClass<UPZ_SkillTreeUIPositionEdNode_UI>(EdSkillNodes);

		for (const auto& EdSkillNode : EdSkillNodes)
		{
			if (EdSkillNode == this) continue;

			if (ParentRNodes.Contains(EdSkillNode->RUINode))
			{
				{
					auto Schema = GetSchema();
					auto pinA = EdSkillNode->GetOutputPin(FPZ_SkillTreeEditorConstant::PinCategory_Main);
					auto pinB = GetInputPin(FPZ_SkillTreeEditorConstant::PinCategory_Main);
					Schema->TryCreateConnection(pinA, pinB);
				}
			}

			if (ChildsRNodes.Contains(EdSkillNode->RUINode))
			{
				{
					auto Schema = GetSchema();
					auto pinA = EdSkillNode->GetInputPin(FPZ_SkillTreeEditorConstant::PinCategory_Main);
					auto pinB = GetOutputPin(FPZ_SkillTreeEditorConstant::PinCategory_Main);
					Schema->TryCreateConnection(pinA, pinB);
				}
			}
		}
	}

}







void UPZ_SkillTreeUIPositionEdNode_UI::OnNodeDoubleClicked()
{
	// TODO....
}

void UPZ_SkillTreeUIPositionEdNode_UI::OnChangedProperties(const FName& PropertyName) const
{
	Super::OnChangedProperties(PropertyName);

	// TODO....
}

void UPZ_SkillTreeUIPositionEdNode_UI::DestroyNode()
{
	Super::DestroyNode();
}



