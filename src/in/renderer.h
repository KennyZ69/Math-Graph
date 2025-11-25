/* renderer.h */

#pragma once

#include "util.h"

typedef struct {
	i8 axisVAO;
	i8 axisVBO;
	i8 axisShader;

	float projection[16]; // projection matrix
} Renderer;

int renderer_init(Renderer *renderer);

void renderer_destroy(Renderer *renderer);

void draw(Renderer *renderer);
