#pragma once
#include <Windows.h>
#include "GfxSystem.h"

class System
{
public:
	bool init();
	void run();
	void deInit();

	static System* Instance();
	bool isInitialized() { return _isInitialized; }

private:
	// singleton
	System() {}
	static System*	_pInstance;
	bool			_isInitialized = false;

	bool createWindow();
	bool runWindow();
	void shutdownWindow();

	// High Frequency Timer
	bool initHighFrequencyTimer();
	void updateHighFrequencyTimer();
	float _secondsPerTick = 0.0f;
	LARGE_INTEGER _lastTickCount = {}; // tick count for last frame
	float _deltaTime = 0.0f; // time between two frames
	int _frames = 0; // frame count for one second
	float _timeSinceLastFrameUpdate = 0.0f;

	// window variables
	HWND	m_hWnd = nullptr;
	UINT	_screenWidth = 640;
	UINT	_screenHeight = 480;

	// gfx variables
	GfxSystem*	m_pGfx = nullptr;
};

