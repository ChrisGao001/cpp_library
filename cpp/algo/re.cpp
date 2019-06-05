#include <stdio.h>

bool is_match_v1(const char *s, const char *p) {
	if (*p == '*') {
		while (*p == '*') ++p;
		if (*p == '\0') return true;
		while (*s != '\0' && !is_match_v1(s, p)) ++s;
		return *s != '\0';
	} else if (*p == '\0' || *s == '\0') {
		return *s == *p;
	} else if (*s == *p || *p =='?') {
		return is_match_v1(++s, ++p);
	} else {
		return false;
	}
}

bool is_match(const char *s, const char *p) {
	bool star = false;
	const char *str = NULL;
	const char *ptr = NULL;
	for (str = s,ptr = p; *str; ++str, ++ptr) {
		//printf("case 3 %s,%s\n", str, ptr);
		switch(*ptr) {
			case '?':
				break;
			case '*': {
				star = true;
				s = str;
				p = ptr;
				while (*p == '*') ++p;
				if (*p == '\0') return true;
				//printf("case 1 %s,%s\n", s, p);
				str = s - 1;
				ptr = p - 1;
				//printf("case 2 %s,%s\n", str, ptr);
				break;
			}
			default:{
				if (*ptr != *str) {
					if (!star) return false;
					++s;
					str = s - 1;
					ptr = p - 1;

				}
				break;
			}
		}
	}
	while (*ptr == '*') ++ptr;
	return '\0' == *ptr;
}

int main(int argc, char **argv) {
	const char *s = argv[1];
	const char *p = argv[2];
	bool rc = is_match(s, p);
	bool rc1 = is_match_v1(s, p);
	printf("v0 %s,%s,rc=%d\n", s, p, rc);
	printf("v1 %s,%s,rc=%d\n", s, p, rc1);

	return 0;
}	
