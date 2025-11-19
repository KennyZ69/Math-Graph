/* app.h */

#pragma once

#include "util.h"
#include "input.h"

// static void framebuffer_size_callback(GLFWwindow *win, int width, int height);

int app_init(const char *title);

void app_run();

void cleanup();
