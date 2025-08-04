#include "gui.h"
#include "imgui.h"

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
		DynamicArray arrayTasks;
		std::vector<Task> heapTasks;
		heapTasks.reserve(NUM_TASKS);
		// temps for user input:
		static int newID = 0;
		static int newPriority = 0;
		static int newPeriod = 0;
		static int newNextRun = 0;



		ImGui::Begin("Task Table");
		ImGui::Text("After generating/adding tasks, displays a table of all tasks before running the scheduler.");
		
		//generates random tasks and adds them to the scheduler
		ImGui::Button("Add a task"); //opens a dialog to add a task (ID, priority, period, next_run_time)
		if (ImGui::Button("Randomly Generate Tasks")) {
			ImGui::BeginTable("Task Table", 4);
			ImGui::TableSetupColumn("Task ID");
			ImGui::TableSetupColumn("Priority");
			ImGui::TableSetupColumn("Next Run");
			ImGui::TableSetupColumn("Period");
			ImGui::TableHeadersRow();
			ImGui::EndTable();
			

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

		}
		if (ImGui::Button("Add a task")) {

			Task t1{
					i,                     // ID
					std::rand() % 5,       // priority in [0..4]
					std::rand() % SIM_END, // period in [0..SIM_END-1]
					std::rand() % 10       // next_run_time in [0..9]
			};
			arrayTasks.push_back(t);
			heapTasks.push_back(t);

		}

		ImGui::End();

		//Scheduler Controls
		//let the user step through tick by tick, run the simulation in its entirety and to reset the simulation
		//want to run the array and heap version one at a time maybe?
		ImGui::Begin("Scheduler Controls");

		ImGui::End();

		//Timeline
		//Maybe we want a visual of which tasks ran at each tick (using ImDrawList)
		ImGui::Begin("Timeline");
		ImGui::End();

		//Benchmark Results
		//Want a table showing the time difference between the Heap and the Array (or a bar chart to compare them)
		ImGui::Begin("Benchmark Results");
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
}