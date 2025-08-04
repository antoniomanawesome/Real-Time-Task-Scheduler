#include "gui.h"
#include "imgui.h"
#include <sstream>
#include <string>
#include <iostream>

namespace gui {
	void RenderUI()
	{
		//making the next window fill the entire viewport
		//ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
		//ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Size);

		//look into useful flags in the Begin function (ImGuiWindowFlags)
		
		//Task Table
		//After generating random tasks or adding/removing manually, want to display a table with all of the tasks.
		//This table should have columns for Task ID, Priority, Next Run Time, and Period
		//Want a button to add a task and randomly generate them (like we did in vscode)
		const int NUM_TASKS = 10000;
		const int SIM_END = 5000;

		// ─── 1) Generate one master list of random tasks ───────────────────
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
		static std::string lastOutput;

		ImGui::Begin("Task Table");
		ImGui::Text("After generating/adding tasks, displays a table of all tasks before running the scheduler.");
		
		//generates random tasks and adds them to the scheduler
		//ImGui::Button("Add a task"); //opens a dialog to add a task (ID, priority, period, next_run_time)
	
		// Random generation
		if (ImGui::Button("Randomly Generate Tasks")) {
			
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
		if (showTaskTable ) {
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
			// ─── 2) Time the Array Scheduler ──────────────────────────────────
			auto startA = std::chrono::high_resolution_clock::now();
			Array_Scheduler(arrayTasks, SIM_END);
			auto endA = std::chrono::high_resolution_clock::now();
			auto array_ms = std::chrono::duration_cast<std::chrono::milliseconds>(endA - startA).count();
			std::cout << "Array Scheduler Time: " << array_ms << " ms\n\n";

			// ─── 3) Time the Heap Scheduler ───────────────────────────────────
			auto startH = std::chrono::high_resolution_clock::now();
			Heap_Scheduler(heapTasks, SIM_END);
			auto endH = std::chrono::high_resolution_clock::now();
			auto heap_ms = std::chrono::duration_cast<std::chrono::milliseconds>(endH - startH).count();
			std::cout << "Heap Scheduler Time : " << heap_ms << " ms\n";

			std::cout.rdbuf(oldBuf);
			lastOutput = oss.str();

		}
		if (ImGui::Button("Timeline")) { //opens a new window showing the timeline of the simulation (which task ran at which tick)

		}
		if (ImGui::Button("Reset Simulation")) { //resets the simulation

		}

		ImGui::End();

		//Timeline
		//Maybe we want a visual of which tasks ran at each tick (using ImDrawList)
		ImGui::Begin("Timeline");
		ImGui::End();

		//Benchmark Results
		//Want a table showing the time difference between the Heap and the Array (or a bar chart to compare them)
		// Benchmark Results
		ImGui::Begin("Benchmark Results");
		// Display captured text in a scrollable region
		ImGui::BeginChild("ResultsScroll", ImVec2(0, 200), true);
		ImGui::TextUnformatted(lastOutput.c_str());
		ImGui::EndChild();
		ImGui::End();


		ImGui::ShowDemoWindow();
	}
}