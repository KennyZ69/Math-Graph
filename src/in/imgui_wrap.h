/* imgui_wrap.h */

#pragma once

#include "util.h"

int imgui_init(GLFWwindow *win, char *buf);
void imgui_shutdown();
void imgui_render();
void imgui_draw_data();
void imgui_new_frame();
