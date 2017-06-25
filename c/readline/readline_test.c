#include <stdio.h>
#include <editline/readline.h>

int main() {
	const char *prompt = "$";
	char *line;

	for (;;) {
		line = readline(prompt);
		printf("%s\n", line);
		add_history(line);
	}

}
