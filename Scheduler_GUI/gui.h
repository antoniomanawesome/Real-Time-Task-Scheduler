#pragma once
#include "DynamicArray.h"
#include "MinHeap.h"
#include "Scheduler.h"
#include <iostream>
#include <vector>
#include <unordered_map>

namespace gui{
	void RenderUI();
	void GanttChart(const std::vector<TickCounter> tickHistory);
}