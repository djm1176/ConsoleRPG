#pragma once
#pragma comment(lib, "winmm.lib")

#ifndef UNICODE
#error Please enable UNICODE for your compiler! VS: Project Properties -> General -> \
Character Set -> Use Unicode. Thanks! - Javidx9
#endif

#include <windows.h>
#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <thread>
#include <atomic>
#include <condition_variable>

enum COLOUR {
	FG_BLACK = 0x0000,
	FG_DARK_BLUE = 0x0001,
	FG_DARK_GREEN = 0x0002,
	FG_DARK_CYAN = 0x0003,
	FG_DARK_RED = 0x0004,
	FG_DARK_MAGENTA = 0x0005,
	FG_DARK_YELLOW = 0x0006,
	FG_GREY = 0x0007, // Thanks MS :-/
	FG_DARK_GREY = 0x0008,
	FG_BLUE = 0x0009,
	FG_GREEN = 0x000A,
	FG_CYAN = 0x000B,
	FG_RED = 0x000C,
	FG_MAGENTA = 0x000D,
	FG_YELLOW = 0x000E,
	FG_WHITE = 0x000F,
	BG_BLACK = 0x0000,
	BG_DARK_BLUE = 0x0010,
	BG_DARK_GREEN = 0x0020,
	BG_DARK_CYAN = 0x0030,
	BG_DARK_RED = 0x0040,
	BG_DARK_MAGENTA = 0x0050,
	BG_DARK_YELLOW = 0x0060,
	BG_GREY = 0x0070,
	BG_DARK_GREY = 0x0080,
	BG_BLUE = 0x0090,
	BG_GREEN = 0x00A0,
	BG_CYAN = 0x00B0,
	BG_RED = 0x00C0,
	BG_MAGENTA = 0x00D0,
	BG_YELLOW = 0x00E0,
	BG_WHITE = 0x00F0,
};

enum PIXEL_TYPE {
	PIXEL_SOLID = 0x2588,
	PIXEL_THREEQUARTERS = 0x2593,
	PIXEL_HALF = 0x2592,
	PIXEL_QUARTER = 0x2591,
};


class olcSprite {
public:
	olcSprite();

	olcSprite(int w, int h);

	olcSprite(std::wstring sFile);

	int nWidth = 0;
	int nHeight = 0;

private:
	short* m_Glyphs = nullptr;
	short* m_Colours = nullptr;

	void Create(int w, int h);

public:
	void SetGlyph(int x, int y, short c);

	void SetColour(int x, int y, short c);

	short GetGlyph(int x, int y);

	short GetColour(int x, int y);

	short SampleGlyph(float x, float y);

	short SampleColour(float x, float y);

	bool Save(std::wstring sFile);

	bool Load(std::wstring sFile);
};

class olcConsoleGameEngine {
public:
	olcConsoleGameEngine();

	void EnableSound();

	int ConstructConsole(int width, int height, int fontw, int fonth);

	virtual void Draw(int x, int y, short c = 0x2588, short col = 0x000F);

	void Fill(int x1, int y1, int x2, int y2, short c = 0x2588, short col = 0x000F);

	void DrawString(int x, int y, std::wstring c, short col = 0x000F);

	void DrawStringAlpha(int x, int y, std::wstring c, short col = 0x000F);

	void Clip(int& x, int& y);

	void DrawLine(int x1, int y1, int x2, int y2, short c = 0x2588, short col = 0x000F);

	void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, short c = 0x2588, short col = 0x000F);

	// https://www.avrfreaks.net/sites/default/files/triangles.c
	void FillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, short c = 0x2588, short col = 0x000F);

	void DrawCircle(int xc, int yc, int r, short c = 0x2588, short col = 0x000F);

	void FillCircle(int xc, int yc, int r, short c = 0x2588, short col = 0x000F);

	void DrawSprite(int x, int y, olcSprite* sprite);

	void DrawPartialSprite(int x, int y, olcSprite* sprite, int ox, int oy, int w, int h);

	void DrawWireFrameModel(const std::vector<std::pair<float, float>>& vecModelCoordinates, float x, float y, float r = 0.0f, float s = 1.0f, short col = FG_WHITE, short c = PIXEL_SOLID);

	~olcConsoleGameEngine();

public:
	void Start();

	int ScreenWidth();

	int ScreenHeight();

private:
	void GameThread();

public:
	// User MUST OVERRIDE THESE!!
	virtual bool OnUserCreate() = 0;
	virtual bool OnUserUpdate(float fElapsedTime) = 0;

	// Optional for clean up 
	virtual bool OnUserDestroy();



protected: // Audio Engine =====================================================================

	class olcAudioSample {
	public:
		olcAudioSample();

		olcAudioSample(std::wstring sWavFile);

		WAVEFORMATEX wavHeader;
		float* fSample = nullptr;
		long nSamples = 0;
		int nChannels = 0;
		bool bSampleValid = false;
	};

	// This vector holds all loaded sound samples in memory
	std::vector<olcAudioSample> vecAudioSamples;

	// This structure represents a sound that is currently playing. It only
	// holds the sound ID and where this instance of it is up to for its
	// current playback
	struct sCurrentlyPlayingSample {
		int nAudioSampleID = 0;
		long nSamplePosition = 0;
		bool bFinished = false;
		bool bLoop = false;
	};
	std::list<sCurrentlyPlayingSample> listActiveSamples;

	// Load a 16-bit WAVE file @ 44100Hz ONLY into memory. A sample ID
	// number is returned if successful, otherwise -1
	unsigned int LoadAudioSample(std::wstring sWavFile);

	// Add sample 'id' to the mixers sounds to play list
	void PlaySample(int id, bool bLoop = false);

	void StopSample(int id);

	// The audio system uses by default a specific wave format
	bool CreateAudio(unsigned int nSampleRate = 44100, unsigned int nChannels = 1,
		unsigned int nBlocks = 8, unsigned int nBlockSamples = 512);

	// Stop and clean up audio system
	bool DestroyAudio();

	// Handler for soundcard request for more data
	void waveOutProc(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwParam1, DWORD dwParam2);

	// Static wrapper for sound card handler
	static void CALLBACK waveOutProcWrap(HWAVEOUT hWaveOut, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);

	// Audio thread. This loop responds to requests from the soundcard to fill 'blocks'
	// with audio data. If no requests are available it goes dormant until the sound
	// card is ready for more data. The block is fille by the "user" in some manner
	// and then issued to the soundcard.
	void AudioThread();

	// Overridden by user if they want to generate sound in real-time
	virtual float onUserSoundSample(int nChannel, float fGlobalTime, float fTimeStep);

	// Overriden by user if they want to manipulate the sound before it is played
	virtual float onUserSoundFilter(int nChannel, float fGlobalTime, float fSample);

	// The Sound Mixer - If the user wants to play many sounds simultaneously, and
	// perhaps the same sound overlapping itself, then you need a mixer, which
	// takes input from all sound sources for that audio frame. This mixer maintains
	// a list of sound locations for all concurrently playing audio samples. Instead
	// of duplicating audio data, we simply store the fact that a sound sample is in
	// use and an offset into its sample data. As time progresses we update this offset
	// until it is beyound the length of the sound sample it is attached to. At this
	// point we remove the playing souind from the list.
	//
	// Additionally, the users application may want to generate sound instead of just
	// playing audio clips (think a synthesizer for example) in whcih case we also
	// provide an "onUser..." event to allow the user to return a sound for that point
	// in time.
	//
	// Finally, before the sound is issued to the operating system for performing, the
	// user gets one final chance to "filter" the sound, perhaps changing the volume
	// or adding funky effects
	float GetMixerOutput(int nChannel, float fGlobalTime, float fTimeStep);

	unsigned int m_nSampleRate;
	unsigned int m_nChannels;
	unsigned int m_nBlockCount;
	unsigned int m_nBlockSamples;
	unsigned int m_nBlockCurrent;

	short* m_pBlockMemory = nullptr;
	WAVEHDR* m_pWaveHeaders = nullptr;
	HWAVEOUT m_hwDevice = nullptr;

	std::thread m_AudioThread;
	std::atomic<bool> m_bAudioThreadActive = false;
	std::atomic<unsigned int> m_nBlockFree = 0;
	std::condition_variable m_cvBlockNotZero;
	std::mutex m_muxBlockNotZero;
	std::atomic<float> m_fGlobalTime = 0.0f;



public:

	struct sKeyState {
		bool bPressed;
		bool bReleased;
		bool bHeld;
	} m_keys[256], m_mouse[5];

	int m_mousePosX;
	int m_mousePosY;



	sKeyState GetKey(int nKeyID);
	int GetMouseX();
	int GetMouseY();
	sKeyState GetMouse(int nMouseButtonID);
	bool IsFocused();


protected:
	int Error(const wchar_t* msg);

	static BOOL CloseHandler(DWORD evt);

protected:
	int m_nScreenWidth;
	int m_nScreenHeight;
	CHAR_INFO* m_bufScreen;
	std::wstring m_sAppName;
	HANDLE m_hOriginalConsole;
	CONSOLE_SCREEN_BUFFER_INFO m_OriginalConsoleInfo;
	HANDLE m_hConsole;
	HANDLE m_hConsoleIn;
	SMALL_RECT m_rectWindow;
	short m_keyOldState[256] = { 0 };
	short m_keyNewState[256] = { 0 };
	bool m_mouseOldState[5] = { 0 };
	bool m_mouseNewState[5] = { 0 };
	bool m_bConsoleInFocus = true;
	bool m_bEnableSound = false;

	// These need to be static because of the OnDestroy call the OS may make. The OS
	// spawns a special thread just for that
	static std::atomic<bool> m_bAtomActive;
	static std::condition_variable m_cvGameFinished;
	static std::mutex m_muxGame;
};