#include <string.h>
#include <stdio.h>

void init_next(const char *pattern, int *next)
{
	const int len = strlen(pattern);
	next[0] = -1;
	int j = -1;
	for (int i=1; i<len; ++i) {
		while (j > -1 && pattern[j+1] != pattern[i]) {
			j = next[j];
		}
		if (next[j+1] == next[i]) {
			++j;
		}
		next[i] = j;
	}
}

int kmp(const char *text, const char *pattern)
{
	if (text == NULL || pattern == NULL) {
		return -1;
	}
	
	const int text_len = strlen(text);
	const int pattern_len = strlen(pattern);
	int next[pattern_len];
	init_next(pattern, next);
	
	int j = -1;
	for (int i=0; i<text_len; ++i) {
		while (j > -1 && text[i] != pattern[j+1]) {
			j = next[j];
		}
		if (text[i] == pattern[j+1]) {
			++j;
		}
		if (j+1 == pattern_len) {
			return (i - j);
		}
	}
	
	return -1;	
}

int main(int argc, char **argv) {
	if (argc != 3) {
		printf("Usage:%s [text] [pattern]\n", argv[0]);
		return -1;
	}
	 char *text = argv[1];
	 char *pattern = argv[2];
	int pos = kmp(text, pattern);
	printf("text=%s, pattern=%s, pos=%d\n", text, pattern, pos);
	if (pos > -1) {
		int m = strlen(pattern);
		char t = text[pos + m];
		text[pos + m ] = '\0';
		printf("match is %s\n", text+pos); 
		text[pos + m ] = t;
	}
	
	return 0;
}
