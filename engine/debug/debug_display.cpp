#include "debug_display.h"

std::vector<debug_message> debug_display::DebugMessages;

debug_display::debug_display()
{
}

debug_display::debug_display(std::string Message)
{
	PushMessage(Message, 10.0);
}

debug_display::debug_display(std::string Message, real64 TimeSeconds)
{
	PushMessage(Message, TimeSeconds);
}

debug_display::debug_display(std::string Text1, size_t Variable1, real64 TimeSeconds)
{
	std::string Message = Text1 + std::to_string(Variable1);
	PushMessage(Message, TimeSeconds);
}

debug_display::debug_display(std::string Text1, size_t Variable1, std::string Text2, real64 TimeSeconds)
{
	std::string Message = Text1 + std::to_string(Variable1) + Text2;
	PushMessage(Message, TimeSeconds);
}

debug_display::debug_display(std::string Text1, size_t Variable1, std::string Text2, size_t Variable2, real64 TimeSeconds)
{
	std::string Message = Text1 + std::to_string(Variable1) + Text2 + std::to_string(Variable2);
	PushMessage(Message, TimeSeconds);
}

debug_display::debug_display(std::string Text1, size_t Variable1, std::string Text2, size_t Variable2, std::string Text3, size_t Variable3, real64 TimeSeconds)
{
	std::string Message = Text1 + std::to_string(Variable1) + Text2 + std::to_string(Variable2) + Text3 + std::to_string(Variable3);
	PushMessage(Message, TimeSeconds);
}

void debug_display::ShowTempDebug(win32_perf_query *PerformanceQuery)
{
	//NOTE(temp): Do some text printing in window. This should be implemented properly.
	render_base Render;
	std::string StrA, StrB, StrC, StrComb;

	StrA = "Frame Time: ";
	StrB = std::to_string((real16)PerformanceQuery->GetElapsedFrameTimeBeforeSleepMS());
	StrC = " ms";
	StrComb = StrA + StrB + StrC;
	Render.DrawBitmapText(StrComb, 0.01, 0.96, 0xFFFFFF, "Source/data/fonts/dosclassic.ttf", 18); //0xB89D3F

	StrA = "Total Time: ";
	StrB = std::to_string((real16)PerformanceQuery->GetTotalTimeMS());
	StrC = " ms";
	StrComb = StrA + StrB + StrC;
	Render.DrawBitmapText(StrComb, 0.01, 0.93, 0xFFFFFF, "Source/data/fonts/dosclassic.ttf", 18);

	StrA = "Entities: ";
	StrB = std::to_string(DataCollector.GetVariable0());
	StrComb = StrA + StrB;
	Render.DrawBitmapText(StrComb, 0.01, 0.90, 0xFFFFFF, "Source/data/fonts/dosclassic.ttf", 18);

	StrA = "FPS: ";
	StrB = std::to_string((int16)PerformanceQuery->GetFPS());
	StrComb = StrA + StrB;
	Render.DrawBitmapText(StrComb, 0.01, 0.87, 0xFFFFFF, "Source/data/fonts/dosclassic.ttf", 18);
	// NOTE(temp): Draw title.
	Render.DrawBitmapText("Poor Man's Game Render Engine", 0.78, 0.96, 0xFFFFFF, "Source/data/fonts/dosclassic.ttf", 22);
}

void debug_display::ShowTimedMessages()
{
	game_timing Timing;
	real64 CurrentTime = Timing.GetWallClock();
	render_base Render;
	real32 YOffset = 0.78;
	for (std::vector<debug_message>::iterator
		It = DebugMessages.begin(); It != DebugMessages.end(); It++)
	{
		if (It->Time < CurrentTime)
		{
			It->~debug_message();
		}
		else
		{
			Render.DrawBitmapText(It->Message, 0.01, YOffset, 0xFFFFFF, "Source/data/fonts/dosclassic.ttf", 18);
			YOffset -= 0.02;
		}
	}
}

void debug_display::PushMessage(std::string Message, real64 TimeSeconds)
{
	game_timing Timing;
	real64 CurrentTime = Timing.GetWallClock();

	debug_message MessageStruct;
	MessageStruct.Message = Message;
	MessageStruct.Time = (TimeSeconds * 1000.0) + CurrentTime;

	DebugMessages.push_back(MessageStruct);
}