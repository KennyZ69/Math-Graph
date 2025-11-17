/* app.c
*
*/

#include "in/glad/glad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "in/app.h"

static void framebuffer_size_callback(GLFWwindow *win, int width, int height) {
	glViewport(0, 0, width, height);
}

static GLFWwindow *win;

int app_init(const char *title) {
	printf("Initializing the %s app...\n", title);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title, 0, 0);
	if (!win) {
		glfwTerminate();
		fprintf(stderr, "Error creating glfw widnow\n");
		return -1;
	}
	glfwMakeContextCurrent(win); // when I was using SDL I had to have the context in a variable
	// feels weird to just have it on the thread, not sure whether that wont be a setback later on
	glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		fprintf(stderr, "Failed to load GLAD\n");
		return -1;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	return 0;
}

void app_run() {
	i8 running = true;

	printf("Running the app...\n");
	while (running && !glfwWindowShouldClose(win)) {

		// TODO: input events and rendering
		
		glClear(GL_COLOR_BUFFER_BIT);

		handle_keys(win, &running);

		glfwSwapBuffers(win);
		glfwPollEvents();
	}
}

void cleanup() {
	printf("Closing up the app and cleaning...\n");
	glfwDestroyWindow(win);
	glfwTerminate();
}
