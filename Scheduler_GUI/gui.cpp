#include "gui.h"
#include "imgui.h"
#include <sstream>
#include <string>
#include <iostream>
#include <cmath> 

namespace gui {
	void RenderUI()
	{
		//making the next window fill the entire viewport
		//ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
		//ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Size);

		//look into useful flags in the Begin function (ImGuiWindowFlags)
		
		static int NUM_TASKS = 10000;
		static int SIM_END = 5000;

		//For the timeline, we need 2 vectors to store the history of the ticks and what tasks are run
		static std::vector<TickCounter> tickHistory_array;
		static std::vector<TickCounter> tickHistory_heap;

		//generate master list of random tasks
		std::srand(static_cast<unsigned>(std::time(nullptr)));
		static DynamicArray arrayTasks;
		static std::vector<Task> heapTasks;
		heapTasks.reserve(NUM_TASKS);
		// temps for user input:
		static int inputID = 0;
		static int inputPriority = 0;
		static int inputPeriod = 0;
		static int inputNextRun = 0;

		// Flag to control table visibility
		static bool showTaskTable = false;
		static bool showTimeline = false;
		

		static std::string lastOutput;
		static float lastArrayMs = 0.0f;
		static float lastHeapMs = 0.0f;

		//How to use the App
		ImGui::Begin("Tutorial");
		ImGui::PushTextWrapPos(ImGui::GetContentRegionAvail().x); //allows text wrapping 
		ImGui::Text("Welcome to the Real-Time Task Scheduler GUI!");
		ImGui::Spacing();

		ImGui::Text("This application allows you to simulate a real-time task scheduler using two different algorithms: Dynamic Array and Min Heap.");
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();

		ImGui::Text("To get started,");
		ImGui::Spacing();
		ImGui::Text("1. Go to the 'Task Table' Window to add a task or generate randomly assigned tasks.You can change the amount of tasks and time. A table will show up displaying all of the tasks generated or added.");
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();

		ImGui::Text("2. Go to the 'Scheduler Controls' window to run the simulation. You can also reset the simulation here if you'd like.");
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();

		ImGui::Text("3. View the 'Benchmark Results' window to inspect the time it took both data structures to run every task.");
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();

		ImGui::Text("4. View the 'Timeline' window to see what tasks ran at each tick with their corresponding ID");
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Text("Thanks for stopping by!");
		ImGui::End();

		
		//ImGui::Begin("Simulation Parameters");
		//ImGui::SliderInt("Number of Tasks", &NUM_TASKS, 1, 10000);
		//ImGui::SliderInt("Simulation End", &SIM_END, 1, 5000);
		////ImGui::SliderFloat("Heap Scale", &heapScale, 1.0f, 20.0f, "%.1fx");
		//ImGui::End();


		//Task Table
		//After generating random tasks or adding/removing manually, want to display a table with all of the tasks.
		//This table should have columns for Task ID, Priority, Next Run Time, and Period
		//Want a button to add a task and randomly generate them (like we did in vscode)
		ImGui::Begin("Task Table");
		
		ImGui::SliderInt("Number of Tasks", &NUM_TASKS, 1, 10000);
		ImGui::SliderInt("Simulation End", &SIM_END, 1, 5000);
		
		//generates random tasks and adds them to the scheduler
		//ImGui::Button("Add a task"); //opens a dialog to add a task (ID, priority, period, next_run_time)
		if (ImGui::Button("Add Task")) {
			// (optional) reset your input fields to defaults whenever the dialog opens
			inputID = 0;
			inputPriority = 0;
			inputPeriod = 0;
			inputNextRun = 0;

			ImGui::OpenPopup("Add Task");

			//if there are no elements in arrayTasks or heapTasks, show table
			if (arrayTasks.get_size() == 0 || heapTasks.size() == 0) showTaskTable = true;
		}
		// Random generation
		if (ImGui::Button("Randomly Generate Tasks")) {
			// Reset containers for a fresh set
			arrayTasks.clear();
			heapTasks.clear();
			
			for (int i = 0; i < NUM_TASKS; ++i) {
				Task t{
					i,                     // ID
					std::rand() % 5,       // priority in [0..4]
					std::rand() % SIM_END, // period in [0..SIM_END-1]
					std::rand() % 10       // next_run_time in [0..9]
				};
				arrayTasks.push_back(t);
				heapTasks.push_back(t);
			
			}
			showTaskTable = true;
		}

		
		// Display table of tasks
		if (showTaskTable) {
			if (ImGui::BeginTable("TaskTable", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
				ImGui::TableSetupColumn("Task ID");
				ImGui::TableSetupColumn("Priority");
				ImGui::TableSetupColumn("Period");
				ImGui::TableSetupColumn("Next Run");
				ImGui::TableHeadersRow();
				for (int i = 0; i < arrayTasks.get_size(); ++i) {
					const Task& t = arrayTasks[i];
					ImGui::TableNextRow();
					ImGui::TableNextColumn(); ImGui::Text("%d", t.ID);
					ImGui::TableNextColumn(); ImGui::Text("%d", t.priority);
					ImGui::TableNextColumn(); ImGui::Text("%d", t.period);
					ImGui::TableNextColumn(); ImGui::Text("%d", t.next_run_time);
				}
				ImGui::EndTable();
			}
		}
		

		
		if (ImGui::BeginPopupModal("Add Task", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
			ImGui::InputInt("ID", &inputID);
			ImGui::InputInt("Priority", &inputPriority);
			ImGui::InputInt("Period", &inputPeriod);
			ImGui::InputInt("Next Run", &inputNextRun);
			ImGui::Separator();
			if (ImGui::Button("OK")) {
				Task t{ inputID, inputPriority, inputPeriod, inputNextRun };
				arrayTasks.push_back(t);
				heapTasks.push_back(t);
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel")) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}


		ImGui::End();

		//Scheduler Controls
		//let the user step through tick by tick, run the simulation in its entirety and to reset the simulation
		//want to run the array and heap version one at a time maybe?
		ImGui::Begin("Scheduler Controls");
		if (ImGui::Button("Run Simulation")) { //runs the entire simulation
			std::ostringstream oss;
			auto* oldBuf = std::cout.rdbuf(oss.rdbuf());

			// timing the Array Scheduler
			auto startA = std::chrono::high_resolution_clock::now();
			Array_Scheduler(arrayTasks, SIM_END, tickHistory_array);
			auto endA = std::chrono::high_resolution_clock::now();
			auto array_ms = std::chrono::duration_cast<std::chrono::milliseconds>(endA - startA).count();
			std::cout << "Array Scheduler Time: " << array_ms << " ms\n\n";

			// timing the Heap Scheduler
			auto startH = std::chrono::high_resolution_clock::now();
			Heap_Scheduler(heapTasks, SIM_END, tickHistory_heap);
			auto endH = std::chrono::high_resolution_clock::now();
			auto heap_ms = std::chrono::duration_cast<std::chrono::milliseconds>(endH - startH).count();
			std::cout << "Heap Scheduler Time : " << heap_ms << " ms\n";

			std::cout.rdbuf(oldBuf);
			lastOutput = oss.str();

			lastArrayMs = array_ms;
			lastHeapMs = heap_ms;
			showTimeline = true;

		}

		//reset simulation
		ImGui::SameLine();
		if (ImGui::Button("Reset Simulation")) {
			showTaskTable = false;
			showTimeline = false;
			lastOutput.clear();
			lastArrayMs = lastHeapMs = 0.0f;
			arrayTasks.clear();
			heapTasks.clear();
		}
		ImGui::End();

		

		//Timeline
		//Maybe we want a visual of which tasks ran at each tick (using ImDrawList)
		ImGui::Begin("Timeline");
		if(showTimeline) GanttChart(tickHistory_array);
		ImGui::End();

		//Benchmark Results
		//Want a table showing the time difference between the Heap and the Array (or a bar chart to compare them)
		// Benchmark Results
		ImGui::Begin("Benchmark Results");
		

		// Results Table
		ImGui::Text("Results Table");
		if (ImGui::BeginTable("ResultsTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
			ImGui::TableSetupColumn("Scheduler");
			ImGui::TableSetupColumn("Time (ms)");
			ImGui::TableHeadersRow();
			ImGui::TableNextRow();
			ImGui::TableNextColumn(); ImGui::Text("Array");
			ImGui::TableNextColumn(); ImGui::Text("%.1f", lastArrayMs);
			ImGui::TableNextRow();
			ImGui::TableNextColumn(); ImGui::Text("Heap");
			ImGui::TableNextColumn(); ImGui::Text("%.1f", lastHeapMs);
			ImGui::EndTable();
		}

		static float heapScale = 1.0f;
		ImGui::SliderFloat("Heap Scale", &heapScale, 1.0f, 50.0f);

		float maxT = std::max(lastArrayMs, lastHeapMs);
		if (maxT > 0.0f) {
			//Bar Chart
			
			ImGui::Text("Array Scheduler: %.1f ms", lastArrayMs);
			//ImGui::ProgressBar(lastArrayMs / maxT, ImVec2(-1, 0), "%.1f ms");
			ImGui::ProgressBar((lastArrayMs) / (lastArrayMs), ImVec2(-1, 0));  // always full scaled
			ImGui::Text("Heap Scheduler: %.1f ms", lastHeapMs);
			//ImGui::ProgressBar(lastHeapMs / maxT, ImVec2(-1, 0), "%.1f ms");
			ImGui::ProgressBar((lastHeapMs * heapScale) / (lastArrayMs), ImVec2(-1, 0) );//scaled


			//Histogram
			// scaled value array
			float rawA = lastArrayMs;
			float rawH = lastHeapMs * heapScale;

			// max bound 
			float histMax = std::max(rawA, rawH);

			// plot the scaled data
			float histValues[2] = { rawA, rawH };
			ImGui::Text("Timing Histogram (Heap × %.1f)", heapScale);
			ImGui::PlotHistogram("##TimingHist", histValues, 2, 0, nullptr, 0.0f, histMax, ImVec2(-1, 80));
			//labels
			ImGui::Columns(2, "HistLabels");
			ImGui::Text("Array"); ImGui::NextColumn();
			ImGui::Text("Heap");
			ImGui::Columns(1);
			//Table
			
			
		}
		
		
		ImGui::End();

		//ImGui::ShowDemoWindow();
	}

	void GanttChart(const std::vector<TickCounter> tickHistory) {
		static float tickWidth = 20.0f;
		static float scrollX = 0.0f;
		static float zoom = 1.0f;
		const float rowHeight = 25.0f;

		//created an array with 6 different colors to represent the tasks in the timeline
		static ImU32 colors[] = {
		IM_COL32(255, 0, 0, 255),
		IM_COL32(0, 255, 0, 255),
		IM_COL32(0, 0, 255, 255),
		IM_COL32(255, 255, 0, 255),
		IM_COL32(255, 0, 255, 255),
		IM_COL32(0, 255, 255, 255)
		};

		std::unordered_map<int, int> taskRowMap;
		int rowCounter = 0;
		for (const auto& event : tickHistory) {
			if (event.taskID != -1 && taskRowMap.find(event.taskID) == taskRowMap.end()) {
				taskRowMap[event.taskID] = rowCounter++;
			}
		}


		ImVec2 canvasSize = ImVec2(ImGui::GetContentRegionAvail().x, rowCounter * rowHeight + 40.0f);
		ImGui::BeginChild("GanttCanvas", canvasSize, true, ImGuiWindowFlags_HorizontalScrollbar);

		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		ImVec2 canvasPos = ImGui::GetCursorScreenPos();

		//zoom n scroll stuff
		if (ImGui::IsWindowHovered()) {
			if (ImGui::GetIO().MouseWheel != 0.0f) {
				zoom += ImGui::GetIO().MouseWheel * 0.1f;
				if (zoom < 0.2f) zoom = 0.2f;
				if (zoom > 3.0f) zoom = 3.0f;
			}
			if (ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
				scrollX += ImGui::GetIO().MouseDelta.x;
			}
		}

		//drawing tick markers every 5 ticks
		const int tickInterval = 5;
		int totalTicks = tickHistory.empty() ? 0 : tickHistory.back().tick + 1;
		for (int t = 0; t <= totalTicks; t += tickInterval) {
			float x = canvasPos.x + t * tickWidth * zoom + scrollX;
			draw_list->AddLine(ImVec2(x, canvasPos.y),
				ImVec2(x, canvasPos.y + rowCounter * rowHeight),
				IM_COL32(200, 200, 200, 100));
			draw_list->AddText(ImVec2(x + 2, canvasPos.y - 15),
				IM_COL32(255, 255, 255, 255),
				std::to_string(t).c_str());
		}

		//task labels on the left
		for (const auto& element : taskRowMap) {
			ImVec2 labelPos(canvasPos.x - 60, canvasPos.y + element.second * rowHeight + 5);
			std::string label = "Task " + std::to_string(element.first);
			draw_list->AddText(labelPos, IM_COL32(255, 255, 0, 255), label.c_str());
		}

		//actually drawing the task
		for (const auto& event : tickHistory) {
			int row = (event.taskID == -1) ? rowCounter : taskRowMap[event.taskID];
			ImU32 color = (event.taskID == -1) ? IM_COL32(100, 100, 100, 255)
				: colors[event.taskID >= 0 ? (event.taskID % 6) : 5];

			float x0 = canvasPos.x + event.tick * tickWidth * zoom + scrollX;
			float y0 = canvasPos.y + row * rowHeight;
			float x1 = x0 + tickWidth * zoom;
			float y1 = y0 + rowHeight - 2;

			draw_list->AddRectFilled(ImVec2(x0, y0), ImVec2(x1, y1), color);
			if (event.taskID != -1) {
				draw_list->AddText(ImVec2(x0 + 2, y0 + 2),
					IM_COL32(255, 255, 255, 255),
					std::to_string(event.taskID).c_str());
			}
		}

		float fullWidth = totalTicks * tickWidth * zoom + 100;
		ImGui::Dummy(ImVec2(fullWidth, rowCounter * rowHeight));
		ImGui::EndChild();
	}
}