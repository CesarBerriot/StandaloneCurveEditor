#include "RichCurveValueContent.h"
#include "SlateOptMacros.h"
#include "Slate Widgets/SStandaloneCurveEditor/StandaloneCurveEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SSpacer.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SRichCurveValueContent::Construct(FArguments const & InArgs, TSharedRef<IPropertyHandle> PropertyHandle)
{
	enum { InBetweenButtonsSpacerWidth = 7 };

	// @formatter:off
	ChildSlot
	[
		SNew(SBox)
		.VAlign(VAlign_Center)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				SAssignNew(EditButton, SButton)
				.Text(FText::FromString("Edit"))
				.OnClicked_Lambda(
					[PropertyHandle, this]
				    {
						// This button shouldn't be clickable until it has no assigned editor
						check(!EditTab)
	
						// Obtain curve owner
						check(PropertyHandle->GetNumOuterObjects())
					    TArray<UObject*> OuterObjects;
					    PropertyHandle->GetOuterObjects(OuterObjects);
					    UObject * OwnerObject = OuterObjects.Last();
	
						// Obtain curve
						FRichCurve * Curve = (FRichCurve*)PropertyHandle->GetValueBaseAddress((uint8*)OwnerObject);
						check(Curve)
	
						// Prepare passed data
					    FPassedCurveData PassedCurveData;
					    PassedCurveData.Curve = Curve;
					    PassedCurveData.OwnerObject = OwnerObject;
					    PassedCurveData.CurveName = PropertyHandle->GetPropertyDisplayName().ToString();
					    PassedCurveData.OwnerName = OwnerObject->GetName();
						
					    // Supply the passed data chain with the prepared data
					    PassedCurveDataChain.Add(PassedCurveData);
						
						// Create standalone curve editor tab
					    FName TabID = "StandaloneCurveEditorNomadTabSpawner";
					    TSharedRef<FGlobalTabmanager> GlobalTabManager = FGlobalTabmanager::Get();
					    GlobalTabManager->RegisterNomadTabSpawner(TabID, FOnSpawnTab::CreateStatic(&SRichCurveValueContent::CreateStandaloneCurveEditorTab));
					    EditTab = GlobalTabManager->TryInvokeTab(TabID);
						EditTab->SetOnTabClosed(SDockTab::FOnTabClosedCallback::CreateLambda(
							[this](TSharedRef<SDockTab>){ EditTabClosedCallback(); }
						));
					    GlobalTabManager->UnregisterNomadTabSpawner(TabID);

						// Update buttons
						EditButton->SetEnabled(false);
						ShowEditorButton->SetEnabled(true);
						CloseEditorButton->SetEnabled(true);
						
					    return FReply::Handled();
				    }
				)
			]
			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SSpacer)
				.Size(FVector2D(InBetweenButtonsSpacerWidth, 0))
			]
			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				SAssignNew(ShowEditorButton, SButton)
				.Text(FText::FromString("Show Editor"))
				.IsEnabled(false)
				.OnClicked_Lambda(
					[this]
					{
						check(EditTab)
						TSharedPtr<SWindow> Window = EditTab->GetParentWindow();
						Window->BringToFront(true);
						Window->FlashWindow();
						EditTab->FlashTab(); // Does nothing ??? Even without flashing the window.
						EditTab->ActivateInParent(ETabActivationCause::SetDirectly);
						return FReply::Handled();
					}
				)
			]
			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SSpacer)
				.Size(FVector2D(InBetweenButtonsSpacerWidth, 0))
			]
			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				SAssignNew(CloseEditorButton, SButton)
				.Text(FText::FromString("Close Editor"))
				.IsEnabled(false)
				.OnClicked_Lambda(
					[this]
					{
						check(EditTab)
						ClosePotentialEditTab();
						EditButton->SetEnabled(true);
						ShowEditorButton->SetEnabled(false);
						CloseEditorButton->SetEnabled(false);
						return FReply::Handled();
					}
				)
			]
		]
	];
	// @formatter:on
}

SRichCurveValueContent::~SRichCurveValueContent()
{
	SCompoundWidget::~SCompoundWidget();
	ClosePotentialEditTab();
}

TSharedRef<SDockTab> SRichCurveValueContent::CreateStandaloneCurveEditorTab(FSpawnTabArgs const & Args)
{
	check(PassedCurveDataChain.Num())
	FPassedCurveData CurveData = PassedCurveDataChain.Pop();

	FText CurveLabelText = FText::FromString(FString() + CurveData.CurveName + " (" + CurveData.OwnerName + ')');

	TSharedPtr<SStandaloneCurveEditor> StandaloneCurveEditor;

	TSharedRef<SDockTab> Result = SNew(SDockTab)
	                              .Label(CurveLabelText)
	                              [
		                              SAssignNew(StandaloneCurveEditor, SStandaloneCurveEditor, *CurveData.Curve)
		                              .TreeItemText(FText::FromString(CurveData.CurveName))
		                              .EditorTopRightText(CurveLabelText)
	                              ];

	StandaloneCurveEditor->OnDestroyed.AddLambda(
		[CurveData]
		{
			UObject * BlueprintClass = CurveData.OwnerObject->GetClass()->ClassGeneratedBy;
			if(BlueprintClass)
				verify(BlueprintClass->MarkPackageDirty())
			else
				verify(CurveData.OwnerObject->MarkPackageDirty());
		}
	);

	return Result;
}

void SRichCurveValueContent::ClosePotentialEditTab()
{
	if(EditTab)
	{
		verify(EditTab->RequestCloseTab());
		EditTab = nullptr;
	}
}

void SRichCurveValueContent::EditTabClosedCallback()
{
	EditTab = nullptr;
	EditButton->SetEnabled(true);
	ShowEditorButton->SetEnabled(false);
	CloseEditorButton->SetEnabled(false);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
