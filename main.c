/* main.c */

#include "src/in/app.h"
#include <stdio.h>

int main() {
	if (app_init("Graphing") == -1) {
		fprintf(stderr, "Failed to initialize the app\n");
		return -1;
	}

	app_run();
	cleanup();

	return 0;
}
