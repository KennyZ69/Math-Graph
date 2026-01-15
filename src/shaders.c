/* shader.c */

#include "in/glad/glad.h"
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "in/shader.h"
#include <GL/glext.h>

static char *read_file(const char *path) {
	FILE *f = fopen(path, "rb");
	if (!f) {
		fprintf(stderr, "Error reading file: %s\n", path);
		return NULL;
	}

	// getting the length of a file
	fseek(f, 0, SEEK_END);
	long len = ftell(f);
	rewind(f);

	char *buf = malloc(len + 1);
	if (!buf) {
		fprintf(stderr, "Memory allocation error\n");
		fclose(f);
		return NULL;
	}
	fread(buf, 1, len, f);
	buf[len] = '\0';

	fclose(f);
	return buf;
}

i32 load_shaders(const char *vertex_path, const char *fragment_path) {
	char *vertex_data = read_file(vertex_path);
	char *fragment_data = read_file(fragment_path);

	if (!vertex_data || !fragment_data) {
		fprintf(stderr, "Error getting shader file data\n");
		return -1;
	}

	// get and compile the shaders
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	const char *vsrc = vertex_data;
	glShaderSource(vs, 1, &vsrc, NULL);
	glCompileShader(vs);

	// check the compilation
	int success;
	char log[512];
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vs, 512, NULL, log);
		fprintf(stderr, "Vertex shader compilation error: %s\n", log);
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	const char *fsrc = fragment_data;
	glShaderSource(fs, 1, &fsrc, NULL);
	glCompileShader(fs);

	// check the compilation
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vs, 512, NULL, log);
		fprintf(stderr, "Fragment shader compilation error: %s\n", log);
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, log);
		fprintf(stderr, "Program linking error: %s\n", log);
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	free(vertex_data);
	free(fragment_data);

	return program;
}
