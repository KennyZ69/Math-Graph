/* input.c */

#include <stdio.h>
#include "in/input.h"
#include "in/imgui_wrap.h"
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
	//
	// INFO: well it seems like I will do at least the submitting in cpp wrappers
}

// Draws out the input box with written texts and returns
int input_box(char *in_buf, int buf_size, int *in_changed, int *submited) {
	// printf("Trying to draw the input box from C calling Cpp\n");
	return imgui_draw_input(in_buf, buf_size, in_changed, submited);
}
