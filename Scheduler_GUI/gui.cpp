#include "gui.h"
#include "imgui.h"

namespace gui {
	void RenderUI()
	{
		//making the next window fill the entire viewport
		//ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
		//ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Size);
		
		//Task Table

		//look into useful flags in the Begin function (ImGuiWindowFlags)
		
		ImGui::Begin("Task Table");
		ImGui::Button("Look at this pretty button");
		ImGui::Text("This is some useful text.");
		ImGui::End();

		//Scheduler Controls
		ImGui::Begin("Scheduler Controls");
		ImGui::End();

		//Timeline
		ImGui::Begin("Timeline");
		ImGui::End();

		//Benchmark Results
		ImGui::Begin("Benchmark Results");
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
}