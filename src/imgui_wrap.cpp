/* imgui_wrap.cpp */

#include "in/imgui_wrap.h"
#include "in/imgui/imgui.h"
#include "in/imgui/backends/imgui_impl_glfw.h"
#include "in/imgui/backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>

extern "C" {

int imgui_init(GLFWwindow *win, char *buf) {
	printf("Init imgui...\n");

	IMGUI_CHECKVERSION();
	if (!ImGui::CreateContext()) {
		fprintf(stderr, "Failed to create ImgGui context\n");
		return -1;
	}

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();

	// renderer backends
	const char *glsl_version = "#version 330";
	if (!ImGui_ImplGlfw_InitForOpenGL(win, true)) {
		fprintf(stderr, "Failed to init ImGui GLFW backend\n");
		ImGui::DestroyContext();
		return -1;
	}

	if (!ImGui_ImplOpenGL3_Init(glsl_version)) {
		fprintf(stderr, "Failed to init ImGui OpenGL3 backend\n");
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		return -1;
	}

	printf("Imgui init success\n");
	return 1;
}

void imgui_shutdown() {
	printf("Shutting down ImGui...\n");
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	
}

void imgui_new_frame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void imgui_render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void imgui_draw_data() {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int imgui_draw_input(char *buf, int buf_size, int *changed, int *submited) {
	if (!buf || !changed || buf_size <= 0) {
		fprintf(stderr, "Invalid params for drawing input field\n");
		return -1;
	}

	int ch = 0;
	static char info[256] = {0};

	ImGuiViewport *viewport = ImGui::GetMainViewport();
	ImVec2 win_pos = ImVec2(viewport->Pos.x + viewport->Size.x - 320, viewport->Pos.y + 20);
	ImVec2 win_pos_pivot = ImVec2(0.0f, 0.0f);

	ImGui::SetNextWindowPos(win_pos, ImGuiCond_Always, win_pos_pivot);
	ImGui::SetNextWindowSize(ImVec2(200, 80));

	ImGuiWindowFlags win_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;

	static int was_focused = false;
	int is_focused = ImGui::IsItemFocused();
	// int is_focused = ImGui::IsItemActive()

	if (ImGui::Begin("Functions", NULL, win_flags)) {
		ImGui::Text("f(x): y = ");
		ImGui::SameLine(0, 4.0f);
		if (ImGui::InputText("x", buf, buf_size, ImGuiInputTextFlags_EnterReturnsTrue)) {
			*changed = 1;
			ch = 1;
			*submited = 1;

			if (strlen(buf) == 0) {
				strcpy(info, "");
			    } else if (!strchr(buf, 'x')) {
				strcpy(info, "Tip: Use 'x' as variable");
			    } else {
				strcpy(info, "");
			    }
			}

		if (was_focused && !is_focused && strlen(buf) > 0) {
			*submited = 1;
			ch = 1;
		}
		was_focused = is_focused;
        
		// Display info message
		if (strlen(info) > 0) {
		    ImGui::TextColored(ImVec4(0.7f, 0.8f, 1.0f, 1.0f), "%s", info);
		}
		
		// Quick examples
		if (ImGui::Button("sin(x)")) {
		    strncpy(buf, "sin(x)", buf_size - 1);
		    buf[buf_size - 1] = '\0';
		    ch = 1;
		    *changed = 1;
		}
		ImGui::SameLine();
		if (ImGui::Button("x^2")) {
		    strncpy(buf, "x^2", buf_size - 1);
		    buf[buf_size - 1] = '\0';
		    ch = 1;
		    *changed = 1;
		}
	    }
	ImGui::End();
	return ch;

}

}
