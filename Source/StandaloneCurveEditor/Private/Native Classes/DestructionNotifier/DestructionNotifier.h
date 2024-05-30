#pragma once

class FDestructionNotifier
{
public:
	TMulticastDelegate<void()> OnDestroyed;
	inline ~FDestructionNotifier() { OnDestroyed.Broadcast(); }
};
