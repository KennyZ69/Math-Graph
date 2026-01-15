/* imgui_wrap.h */

#pragma once

#include "util.h"

#ifdef __cplusplus
extern "C" {
#endif

int imgui_init(GLFWwindow *win, char *buf);

void imgui_shutdown();

void imgui_render();

void imgui_draw_data();

void imgui_new_frame();

/* ImGui wrapper function to draw out the input box and handle input + submission */
int imgui_draw_input(char *buf, int buf_size, int *changed, int *submited);

#ifdef __cplusplus
}
#endif
