#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class STANDALONECURVEEDITOR_API SRichCurveValueContent final : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRichCurveValueContent) {}
	SLATE_END_ARGS()

	void Construct(FArguments const & InArgs, TSharedRef<IPropertyHandle> PropertyHandle);
	virtual ~SRichCurveValueContent() override;
private:
	static TSharedRef<SDockTab> CreateStandaloneCurveEditorTab(FSpawnTabArgs const & Args);
	/// Closes the edit tab, if only it exists
	void ClosePotentialEditTab();
	void EditTabClosedCallback();
private:
	TSharedPtr<SDockTab> EditTab;
	TSharedPtr<SButton> EditButton;
	TSharedPtr<SButton> ShowEditorButton;
	TSharedPtr<SButton> CloseEditorButton;
	struct FPassedCurveData
	{
		FRichCurve * Curve;
		UObject * OwnerObject;
		FString CurveName;
		FString OwnerName;
	};
	/// Used to pass the pointers to soon-to-be edited curves to the nomad tabs.
	static inline TArray<FPassedCurveData> PassedCurveDataChain;
};
