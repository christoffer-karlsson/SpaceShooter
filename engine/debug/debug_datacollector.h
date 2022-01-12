#pragma once

#include "..\..\global_defines.h"

// NOTE: Just a temporary debug tool, storing values so that it can be used
// to print debug messages on the screen. Clean this up eventually!
class debug_datacollector
{
	private:
	static size_t Variable0;
	static size_t Variable1;
	static size_t Variable2;
	static size_t Variable3;
	static size_t Variable4;
	static size_t Variable5;

	public:
	size_t GetVariable0() const;
	size_t GetVariable1() const;
	size_t GetVariable2() const;
	size_t GetVariable3() const;
	size_t GetVariable4() const;
	size_t GetVariable5() const;

	public:
	debug_datacollector();
	debug_datacollector(int16 AttachTo, size_t InVariable);
};