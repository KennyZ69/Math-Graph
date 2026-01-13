/* app.c
*
*/


#include "in/glad/glad.h"

#include "in/imgui_wrap.h"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include "in/app.h"
#include "in/renderer.h"

static void framebuffer_size_callback(GLFWwindow *win, int width, int height) {
	glViewport(0, 0, width, height);
}

static GLFWwindow *win;
static Renderer *renderer;

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

	renderer = malloc(sizeof(Renderer));
	if (renderer_init(renderer) == -1) {
		fprintf(stderr, "Failed to init renderer\n");
		return -1;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // dark gray background
	
	if (imgui_init(win) == -1) {
		fprintf(stderr,"Failed to init imgui lib\n");
		return -1;
	}

	return 0;
}

void app_run() {
	i8 running = true;

	printf("Running the app...\n");
	while (running && !glfwWindowShouldClose(win)) {

		// TODO: input events and rendering

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		handle_keys(win, &running);

		// draw the gl content
		draw(renderer);

		// draw the imgui content (input handling for now)
		imgui_render();

		glfwSwapBuffers(win);
		glfwPollEvents();
	}
}

void cleanup() {
	printf("Closing up the app and cleaning...\n");
	imgui_shutdown();
	glfwDestroyWindow(win);
	glfwTerminate();
}
