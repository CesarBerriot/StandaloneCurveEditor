#include "SStandaloneCurveEditor.h"
#include "RichCurveEditorModel.h"
#include "SCurveEditorPanel.h"
#include "SlateOptMacros.h"
#include "Curve Asset Editor Tree Item/CurveAssetEditorTreeItem.h"
#include "Tree/SCurveEditorTree.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SStandaloneCurveEditor::Construct(FArguments const & InArgs, FRichCurve & InCurve)
{
	Curve = &InCurve;
	TreeItemText = InArgs._TreeItemText;
	EditorTopRightText = InArgs._EditorTopRightText;

	// Create the curve editor
	CurveEditor = MakeShared<FCurveEditor>();
	FCurveEditorInitParams InitParams;
	CurveEditor->InitCurveEditor(InitParams);

	// Create the curve edition widget
	CurveEditorPanel = SNew(SCurveEditorPanel, CurveEditor.ToSharedRef())
	                   .TreeContent()
	                   [
		                   SNew(SCurveEditorTree, CurveEditor)
	                   ];

	// Create and pin the curve asset editor tree item
	TSharedPtr<FCurveAssetEditorTreeItem> TreeItem = MakeShared<FCurveAssetEditorTreeItem>(Curve, TreeItemText, EditorTopRightText);
	FCurveEditorTreeItem * NewItem = CurveEditor->AddTreeItem(FCurveEditorTreeItemID::Invalid());
	NewItem->SetStrongItem(TreeItem);
	CurveEditor->PinCurve(NewItem->GetOrCreateCurves(CurveEditor.Get())[0]);

	// Display the curve edition widget
	ChildSlot
	[
		CurveEditorPanel.ToSharedRef()
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
