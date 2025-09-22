#pragma once
#include "DarkEdif.hpp"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <cstdlib>

class Extension
{
public:

	RunHeader* rhPtr;
	RunObjectMultiPlatPtr rdPtr; // you should not need to access this
#ifdef __ANDROID__
	global<jobject> javaExtPtr;
#elif defined(__APPLE__)
	void* const objCExtPtr;
#endif

	Edif::Runtime Runtime;

	static const int MinimumBuild = 254;
	static const int Version = 2;

	// If you change OEFLAGS, make sure you modify RUNDATA so the data is available, or you'll get crashes!
	// For example, OEFLAGS::VALUES makes use of the AltVals rv struct.
	static const OEFLAGS OEFLAGS = OEFLAGS::VALUES;
	static const OEPREFS OEPREFS = OEPREFS::NONE;

	static const int WindowProcPriority = 100;

#ifdef _WIN32
	Extension(RunObject* const rdPtr, const EDITDATA* const edPtr, const CreateObjectInfo* const cobPtr);
#elif defined(__ANDROID__)
	Extension(const EDITDATA* const edPtr, const jobject javaExtPtr);
#else
	Extension(const EDITDATA* const edPtr, void* const objCExtPtr);
#endif
	~Extension();

	/*  Add any data you want to store in your extension to this class
		(eg. what you'd normally store in rdPtr in old SDKs).

		Unlike rdPtr, you can store real C++ objects with constructors
		and destructors, without having to call them manually or store
		a pointer.
	*/





	SOCKET livesplitSocket = NULL;
	std::tstring errorIdentifier = _T("");
	std::string format_millis(int ms);
	std::tstring handleExpressionSocket(std::string command);




	/*  Add your actions, conditions and expressions as real class member
		functions here. The arguments (and return type for expressions) must
		match EXACTLY what you defined in the JSON.

		Remember to link the actions, conditions and expressions to their
		numeric IDs in the class constructor (Extension.cpp)
	*/

	/// Actions

#define Act_LivesplitConnect		0
#define Act_LivesplitDisconnect		1
#define Act_StartOrSplit			2
#define Act_Split					3
#define Act_Unsplit					4
#define Act_SkipSplit				5
#define Act_Pause					6
#define Act_Resume					7
#define Act_Reset					8
#define Act_StartTimer				9
#define Act_SetGameTime				10
#define Act_SetLoadingTimes			11
#define Act_AddLoadingTimes			12
#define Act_PauseGameTime			13
#define Act_UnpauseGameTime			14
#define Act_AlwaysPauseGameTime		15
#define Act_SetComparison			16
#define Act_SwitchToRealTime		17
#define Act_SwitchToGameTime		18
#define Act_SetSplitName			19
#define Act_SetCurrentSplitName		20
#define Act_SetCustomVariableOLD	21
#define Act_SetCustomVariable		22

		void LivesplitConnect(int port);
		void LivesplitDisconnect();
		void StartOrSplit();
		void Split();
		void Unsplit();
		void SkipSplit();
		void Pause();
		void Resume();
		void Reset();
		void StartTimer();
		void SetGameTime(int time);
		void SetLoadingTimes(int time);
		void AddLoadingTimes(int time);
		void PauseGameTime();
		void UnpauseGameTime();
		void AlwaysPauseGameTime();
		void SetComparison(const TCHAR* comparison);
		void SwitchToRealTime();
		void SwitchToGameTime();
		void SetSplitName(int index, const TCHAR* name);
		void SetCurrentSplitName(const TCHAR* name);
		void SetCustomVariableOLD(const TCHAR* json);
		void SetCustomVariable(const TCHAR* name, const TCHAR* value);

	/// Conditions

#define Cnd_OnError			0
#define Cnd_OnConnected		1
#define Cnd_OnDisconnect	2
#define Cnd_IsConnected		3

		bool ImmediateDefault();
		bool LivesplitConnected();

	/// Expressions

#define Exp_GetErrorID				0
#define Exp_GetDelta				1
#define Exp_GetDeltaC				2
#define Exp_GetLastSplitTime		3
#define Exp_GetComparisonSplitTime	4
#define Exp_GetCurrentRealTime		5
#define Exp_GetCurrentGameTime		6
#define Exp_GetCurrentTime			7
#define Exp_GetFinalTime			8
#define Exp_GetFinalTimeC			9
#define Exp_GetPredictedTime		10
#define Exp_GetBestPossibleTime		11
#define Exp_GetSplitIndex			12
#define Exp_GetAttemptCount			13
#define Exp_GetCompletedCount		14
#define Exp_GetCurrentSplitName		15
#define Exp_GetPreviousSplitName	16
#define Exp_GetCurrentTimerPhase	17
#define Exp_GetCustomVariableValue	18
#define Exp_Ping					19

		const TCHAR* GetErrorID();
		const TCHAR* GetDelta();
		const TCHAR* GetDeltaC(const TCHAR* comparison);
		const TCHAR* GetLastSplitTime();
		const TCHAR* GetComparisonSplitTime();
		const TCHAR* GetCurrentRealTime();
		const TCHAR* GetCurrentGameTime();
		const TCHAR* GetCurrentTime_();
		const TCHAR* GetFinalTime();
		const TCHAR* GetFinalTimeC(const TCHAR* comparison);
		const TCHAR* GetPredictedTime(const TCHAR* comparison);
		const TCHAR* GetBestPossibleTime();
		int			 GetSplitIndex();
		int			 GetAttemptCount();
		int			 GetCompletedCount();
		const TCHAR* GetCurrentSplitName();
		const TCHAR* GetPreviousSplitName();
		const TCHAR* GetCurrentTimerPhase();
		const TCHAR* GetCustomVariableValue(const TCHAR* varName);
		const TCHAR* Ping();



	/* These are called if there's no function linked to an ID */

	void UnlinkedAction(int ID);
	long UnlinkedCondition(int ID);
	long UnlinkedExpression(int ID);




	/*  These replace the functions like HandleRunObject that used to be
		implemented in Runtime.cpp. They work exactly the same, but they're
		inside the extension class.
	*/

	REFLAG Handle();
	REFLAG Display();

	short FusionRuntimePaused();
	short FusionRuntimeContinued();
};
