/* input.c */

#include "in/input.h"
#include "in/util.h"

void handle_keys(GLFWwindow* win, i8 *running) {
	if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		*running = false;
		return;
	}

	if (glfwGetKey(win, GLFW_KEY_R) == GLFW_PRESS) {
		// TODO: reset logic
	}

	// TODO: think about more possibilities of key controls
}

void input_box() {}
