/* renderer.c */

#include "in/glad/glad.h"
#include "in/renderer.h"
#include "in/shader.h"
#include "in/util.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

static float axis_vertices[] = {
	// X axis
	-HORIZONTAL_EDGE, 0.0f, 0.0f,
	HORIZONTAL_EDGE, 0.0f, 0.0f,

	// Y axis
	0.0f, -VERTICAL_EDGE, 0.0f,
	0.0f, VERTICAL_EDGE, 0.0f,
};

static float projection_matrix[16] = {
	2.0f / HORIZONTAL_EDGE, 0.0f, 0.0f, 0.0f,
	0.0f, 2.0f / VERTICAL_EDGE, 0.0f, 0.0f,
	0.0f, 0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};

int renderer_init(Renderer *renderer) {
	// set VAO and VBO for the axis
	glGenVertexArrays(1, (uint*)&renderer->axisVAO);
	glGenBuffers(1, (uint*)&renderer->axisVBO);

	renderer->axisShader = load_shaders("shaders/axis.vs", "shaders/axis.fs");
	// printf("Axis Shader ID: %d\n", (uint)renderer->axisShader);
	
	glBindVertexArray(renderer->axisVAO);
	glBindBuffer(GL_ARRAY_BUFFER, renderer->axisVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(axis_vertices), axis_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	// set projection matrix
	for (int i = 0; i < 16; i++) {
		renderer->projection[i] = projection_matrix[i];
	}

	glUseProgram((uint)renderer->axisShader);
	int proj_loc = glGetUniformLocation((uint)renderer->axisShader, "uProjection");
	// printf("Projection loc: %d\n", proj_loc);
	glUniformMatrix4fv(proj_loc, 1, false, renderer->projection);

	return 0;
}

void renderer_destroy(Renderer *renderer) {
	glDeleteVertexArrays(1, (uint*)&renderer->axisVAO);
	glDeleteBuffers(1, (uint*)&renderer->axisVBO);
	glDeleteProgram((uint)renderer->axisShader);
}

void draw_axis(Renderer *renderer) {
	glUseProgram((uint)renderer->axisShader);
	int color_loc = glGetUniformLocation((uint)renderer->axisShader, "uColor");
	// printf("Color loc: %d\n", color_loc);
	glUniform3f(color_loc, 1.0f, 1.0f, 1.0f); // white color for axis

	glBindVertexArray((uint)renderer->axisVAO);
	glDrawArrays(GL_LINES, 0, 4); // 4 vertices for 2 lines
	
	glBindVertexArray(0); // unbind vao
}

void draw(Renderer *renderer) {
	draw_axis(renderer);
}
