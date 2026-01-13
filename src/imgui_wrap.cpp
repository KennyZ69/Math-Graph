/* imgui_wrap.cpp */

#include "in/imgui_wrap.h"
#include "in/imgui/imgui.h"
#include "in/imgui/backends/imgui_impl_glfw.h"
#include "in/imgui/backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

int imgui_init(GLFWwindow *win, char *buf) {
	printf("Init imgui...\n");

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
}
