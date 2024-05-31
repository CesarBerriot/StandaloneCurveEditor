# StandaloneCurveEditor
An Unreal Engine plugin that provides a custom FRichCurve editor to enable the usage of Unreal Engine's curves without curve assets.

## Known Issues
### UE5.2 And Preceding Versions
Curve editors assigned to FRichCurves that are not direct members of their UObject owner may not get automatically closed once their owner's editor tab gets closed.
This is due to the assigned FRichCurve's custom editor widget not being destroyed by the engine once its tab gets destroyed, as its destructor is used to detect the destruction of the owning tab.
This is most definitely an engine bug, as the custom editor of some non-direct FRicheCurve members (seemingly somewhat randomly) do get destroyed.
My assumption is the engine wrongfully keeps a shared pointer to some of the custom editor widgets somewhere, causing them to not end up being destroyed, thus creating this bug.
A workaround would be to rely on the owning tab's OnClosed event instead of the custom editor destructors, but sadly I couldn't find a way to consistently access said owning tab from the custom editors.
