#pragma once

#include "CoreMinimal.h"
#include "CurveEditor.h"
#include "Native Classes/DestructionNotifier/DestructionNotifier.h"
#include "Widgets/SCompoundWidget.h"

class STANDALONECURVEEDITOR_API SStandaloneCurveEditor final : public SCompoundWidget, public FDestructionNotifier
{
public:
	SLATE_BEGIN_ARGS(SStandaloneCurveEditor)
		: _TreeItemText(FText::FromString("Curve"))
		, _EditorTopRightText(FText::FromString("Editor")) {}
		SLATE_ARGUMENT(FText, TreeItemText)
		SLATE_ARGUMENT(FText, EditorTopRightText)
	SLATE_END_ARGS()

	void Construct(FArguments const & InArgs, FRichCurve & InCurve);
private:
	FText TreeItemText;
	FText EditorTopRightText;
	FRichCurve * Curve = nullptr;
	TSharedPtr<FCurveEditor> CurveEditor;
	TSharedPtr<SCurveEditorPanel> CurveEditorPanel;
};
