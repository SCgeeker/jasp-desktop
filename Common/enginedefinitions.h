#ifndef ENGINEDEFINITIONS_H
#define ENGINEDEFINITIONS_H

#include "enumutilities.h"

///
/// This file defines the necessary types for communication between Desktop and Engine
/// Using enumutilities templates to make sure we can easily and quickly go from enum -> string -> enum for json communication
///

DECLARE_ENUM(engineState,			initializing, idle, analysis, filter, rCode, computeColumn, moduleInstallRequest, moduleLoadRequest, pauseRequested, paused, resuming, stopRequested, stopped, logCfg, settings, killed);
DECLARE_ENUM(performType,			run, abort, saveImg, editImg, rewriteImgs);
DECLARE_ENUM(analysisResultStatus,	validationError, fatalError, imageSaved, imageEdited, imagesRewritten, complete, running, changed, waiting);
DECLARE_ENUM(moduleStatus,			initializing, installNeeded, installModPkgNeeded, loadingNeeded, unloadingNeeded, readyForUse, error);
DECLARE_ENUM(engineAnalysisStatus,	empty, toRun, running, changed, complete, error, exception, aborted, stopped, saveImg, editImg, rewriteImgs, synchingData);

struct unexpectedEngineReply  : public std::runtime_error
{
	unexpectedEngineReply(std::string msg)															: std::runtime_error(msg) {}
	unexpectedEngineReply(engineState unexpectedState, std::string msg = "Engine got unexpected")	: std::runtime_error(msg + ": " + engineStateToString(unexpectedState)) {}
	unexpectedEngineReply(engineState unexpectedState, int engineNo, std::string extra = "")		: std::runtime_error("Engine " + std::to_string(engineNo) + " got unexpected reply: " + engineStateToString(unexpectedState) + extra) {}
	const char* what() const noexcept override; //Put that

	static void checkIfExpected(engineState expectedReplyState, engineState currentState, int channelNo);
};

///How many seconds do we wait for an engine to be killed if it gets stuck in some analysis?
#define ENGINE_KILLTIME 2

///How many seconds should there be at minimum between two attempts to start an extra idle engine?
#define ENGINE_EXTRA_INTERVAL 10

///After how many seconds is an engine allowed to shutdown due to boredom?
/// SHOULD TOTALLY BE BIGGER THAN 6 in actual development! more like 600
#define ENGINE_BORED_SHUTDOWN 600


#endif // ENGINEDEFINITIONS_H
