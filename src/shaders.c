/* shader.c */

#include "in/shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

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

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, (const char**)&vertex_data, 0);
}
