#include "utils.h"

char *find_path(char *cmd) {
	char *path_env = getenv("PATH");
	char *path = strdup(cmd);

	if (path_env) {
		char *tok = strtok(path_env, ":");

		while (access(path, X_OK) != 0 && tok) {
			free(path);
			path = malloc(strlen(tok) + strlen(cmd) + 2);
			if (!path) {
				syserr("malloc");
			}
			strcpy(path, tok);
			strcat(path, "/");
			strcat(path, cmd);

			tok = strtok(NULL, ":");
		}
	}

	return (path);
}