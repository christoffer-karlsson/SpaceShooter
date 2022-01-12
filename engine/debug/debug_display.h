#pragma once

#include "..\..\global_defines.h"
#include "..\renderer\render_base.h"
#include "..\game_base\game_timing.h"
#include "..\..\win32\win32_perf_query.h"//temp
#include "..\debug\debug_datacollector.h"
#include <string>
#include <vector>

struct debug_message
{
	std::string Message;
	real32 Time;
};

class debug_display
{
	private:
	debug_datacollector DataCollector;
	static std::vector<debug_message> DebugMessages;

	protected:
	void PushMessage(std::string Message, real64 TimeSeconds);

	public:	
	void ShowTempDebug(win32_perf_query *Performance);//temp
	void ShowTimedMessages();

	public:
	debug_display();
	debug_display(std::string Message);
	debug_display(std::string Message, real64 TimeSeconds);
	debug_display(std::string Text1, size_t Variable1, real64 TimeSeconds);
	debug_display(std::string Text1, size_t Variable1, std::string Text2, real64 TimeSeconds);
	debug_display(std::string Text1, size_t Variable1, std::string Text2, size_t Variable2, real64 TimeSeconds);
	debug_display(std::string Text1, size_t Variable1, std::string Text2, size_t Variable2, std::string Text3, size_t Variable3, real64 TimeSeconds);
};