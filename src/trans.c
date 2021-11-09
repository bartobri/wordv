#include <string.h>

static char leet_table[128];

void trans_init(void) {
	
	// Init my leet speak table
	leet_table['e'] = '3';
	leet_table['i'] = '1';
	leet_table['a'] = '4';
	leet_table['o'] = '0';
	//leet_table['s'] = '$';
	//leet_table['t'] = '7';
}

char *trans_leet(char *word) {
	size_t i;

	if (strlen(word) >= 3) {
		for (i = 0; i < strlen(word); ++i) {
			if (leet_table[(int)word[i]] > 0) {
				word[i] = leet_table[(int)word[i]];
			}
		}
	}
	
	return word;
}

char *trans_upper(char *word) {
	if (word[0] >= 97 && word[0] <= 122) {
		word[0] -= 32;
	}
	
	return word;
}

char *trans_all_upper(char *word) {
	size_t i;

	for (i = 0; i < strlen(word); ++i) {
		if (word[i] >= 97 && word[i] <= 122) {
			word[i] -= 32;
		}
	}
	
	return word;
}
