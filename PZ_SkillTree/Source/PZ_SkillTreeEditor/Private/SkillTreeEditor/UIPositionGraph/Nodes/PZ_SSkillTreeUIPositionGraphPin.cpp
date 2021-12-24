// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SSkillTreeUIPositionGraphPin.h"

#include "../../PZ_SkillTreeEditorStyle.h"



void SPZ_SSkillTreeUIPositionGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InPin)
{
	check(InPin);
	SetCursor(EMouseCursor::Default);
	bShowLabel = true;
	IsEditable = true;
	GraphPinObj = InPin;

	const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
	check(Schema);

	SBorder::Construct(SBorder::FArguments()
		.BorderImage(this, &Self::GetPinBorder)
		.BorderBackgroundColor(this, &Self::GetPinColor)
		//.OnMouseButtonDown(this, &Self::OnPinMouseDown)
		.Cursor(this, &Self::GetPinCursor)
		.Padding(FMargin(10.f))
	);

}









TSharedRef<SWidget> SPZ_SSkillTreeUIPositionGraphPin::GetDefaultValueWidget()
{
	return SNew(STextBlock);
}

FSlateColor SPZ_SSkillTreeUIPositionGraphPin::GetPinColor() const
{

	const FLinearColor DarkColor(0.02f, 0.02f, 0.02f);
	const FLinearColor MarkerPinColor(0.3f, 0.3f, 0.3f);

	return IsHovered() ? DarkColor : MarkerPinColor;
}

const FSlateBrush* SPZ_SSkillTreeUIPositionGraphPin::GetPinBorder() const
{
	return  FEditorStyle::GetBrush(TEXT("Graph.StateNode.Body"));
}
