#include "debug_datacollector.h"

size_t debug_datacollector::Variable0 = 0;
size_t debug_datacollector::Variable1 = 0;
size_t debug_datacollector::Variable2 = 0;
size_t debug_datacollector::Variable3 = 0;
size_t debug_datacollector::Variable4 = 0;
size_t debug_datacollector::Variable5 = 0;

size_t debug_datacollector::GetVariable0() const
{
	return debug_datacollector::Variable0;
}

size_t debug_datacollector::GetVariable1() const
{
	return debug_datacollector::Variable1;
}

size_t debug_datacollector::GetVariable2() const
{
	return debug_datacollector::Variable2;
}

size_t debug_datacollector::GetVariable3() const
{
	return debug_datacollector::Variable3;
}

size_t debug_datacollector::GetVariable4() const
{
	return debug_datacollector::Variable4;
}

size_t debug_datacollector::GetVariable5() const
{
	return debug_datacollector::Variable5;
}

debug_datacollector::debug_datacollector()
{
}

debug_datacollector::debug_datacollector(int16 AttachTo, size_t InVariable)
{
	if		(AttachTo == 0) { Variable0 = InVariable; }
	else if (AttachTo == 1) { Variable1 = InVariable; }
	else if (AttachTo == 2) { Variable2 = InVariable; }
	else if (AttachTo == 3) { Variable3 = InVariable; }
	else if (AttachTo == 4) { Variable4 = InVariable; }
	else if (AttachTo == 5) { Variable5 = InVariable; }
}