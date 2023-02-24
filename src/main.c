#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#include "main.h"
#include "wordlist.h"
#include "trans.h"

// Function prototypes
void main_show_word_lists(void);
void main_shutdown(const char *);

int main(int argc, char *argv[]) {
	int o, i;
	size_t n;
	char *word = NULL;
	char *word2 = NULL;
	char tmp[BUFSIZ];
	char tmp2[BUFSIZ];
	//char *tmp2 = NULL;
	char *wordListName = DEFAULT_WORD_LIST;
	char *wordListPath = NULL;
	FILE *wordList;
	
	// Initialize my word list
	wordlist_init();
	trans_init();
	
	// Check command options
	while ((o = getopt(argc, argv, "l:s")) != -1) {
		switch (o) {
			case 'l':
				wordListName = optarg;
				break;
			case 's':
				main_show_word_lists();
				return 0;
			case '?':
				if (isprint(optopt))
					fprintf (stderr, "Unknown option '-%c'.\n", optopt);
				else
					fprintf (stderr, "Unknown option character '\\x%x'.\n", optopt);
				main_shutdown("Invalid command option(s).");
		}
	}
	
	// Generate full word list path
	wordListPath = malloc(strlen(WORD_LIST_DIR) + strlen(wordListName) + 1);
	strcpy(wordListPath, WORD_LIST_DIR);
	strcat(wordListPath, wordListName);
	
	// Open word file
	if ((wordList = fopen(wordListPath, "r")) == NULL) {
		main_shutdown("Word list not found.");
	}
	
	// Load all words in the list
	while (getline(&word, &n, wordList) > 0) {
		if (word[strlen(word) - 1] == '\n') {
			word[strlen(word) - 1] = '\0';
		}
		wordlist_add(word);
		word = NULL;
		n = 0;
	}
	
	// Free wordListPath since we don't need it anymore
	free(wordListPath);
	
	/************************
	 * PLAIN WORD VARIATIONS
	 ************************/

	// Print plain word list
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		printf("%s\n", word);
	}
	
	// Print plain word with a single digit at the end
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (i = 0; i <= 9; ++i) {
			printf("%s%i\n", word, i);
		}
	}
	
	// Print plain word with a recent date at the end (2-digit and 4-digit)
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (i = 2022; i >= 1965; --i) {
			printf("%s%i\n", word, i);
		}
		for (i = 22; i >= 0; --i) {
			printf("%s%02i\n", word, i);
		}
		for (i = 99; i >= 65; --i) {
			printf("%s%i\n", word, i);
		}
	}
	
	// Print plain word with a special character at the end
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		printf("%s!\n", word);
		printf("%s@\n", word);
		printf("%s#\n", word);
		printf("%s$\n", word);
		printf("%s%%\n", word);
		printf("%s&\n", word);
	}

	// Print plain word with a single digit and special char at the end
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (i = 0; i <= 9; ++i) {
			printf("%s%i!\n", word, i);
			printf("%s%i@\n", word, i);
			printf("%s%i#\n", word, i);
			printf("%s%i$\n", word, i);
			printf("%s%i%%\n", word, i);
			printf("%s%i&\n", word, i);
		}
	}
	
	// Print plain word with a recent date and special char at the end (2-digit and 4-digit)
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (i = 2022; i >= 1965; --i) {
			printf("%s%i!\n", word, i);
			printf("%s%i@\n", word, i);
			printf("%s%i#\n", word, i);
			printf("%s%i$\n", word, i);
			printf("%s%i%%\n", word, i);
			printf("%s%i&\n", word, i);
		}
		for (i = 22; i >= 0; --i) {
			printf("%s%i!\n", word, i);
			printf("%s%i@\n", word, i);
			printf("%s%i#\n", word, i);
			printf("%s%i$\n", word, i);
			printf("%s%i%%\n", word, i);
			printf("%s%i&\n", word, i);
		}
		for (i = 99; i >= 65; --i) {
			printf("%s%i!\n", word, i);
			printf("%s%i@\n", word, i);
			printf("%s%i#\n", word, i);
			printf("%s%i$\n", word, i);
			printf("%s%i%%\n", word, i);
			printf("%s%i&\n", word, i);
		}
	}

	/************************
	 * FIRST UPPER WORD VARIATIONS
	 ************************/

	// Print upper-transformed word list
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		memset(tmp, 0, BUFSIZ);
		strcpy(tmp, word);
		printf("%s\n", trans_upper(tmp));
	}
	
	// Print upper-transformed word with a single digit at the end
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		memset(tmp, 0, BUFSIZ);
		strcpy(tmp, word);
		for (i = 0; i <= 9; ++i) {
			printf("%s%i\n", trans_upper(tmp), i);
		}
	}
	
	// Print upper-transformed word with a recent date at the end (2-digit and 4-digit)
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		memset(tmp, 0, BUFSIZ);
		strcpy(tmp, word);
		for (i = 2022; i >= 1965; --i) {
			printf("%s%i\n", trans_upper(tmp), i);
		}
		for (i = 22; i >= 0; --i) {
			printf("%s%02i\n", trans_upper(tmp), i);
		}
		for (i = 99; i >= 65; --i) {
			printf("%s%i\n", trans_upper(tmp), i);
		}
	}
	
	// Print upper-transformed word with a special character at the end
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		memset(tmp, 0, BUFSIZ);
		strcpy(tmp, word);
		printf("%s!\n", trans_upper(tmp));
		printf("%s@\n", trans_upper(tmp));
		printf("%s#\n", trans_upper(tmp));
		printf("%s$\n", trans_upper(tmp));
		printf("%s%%\n", trans_upper(tmp));
		printf("%s&\n", trans_upper(tmp));
	}

	// Print upper-transformed word with a single digit and special char at the end
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		memset(tmp, 0, BUFSIZ);
		strcpy(tmp, word);
		for (i = 0; i <= 9; ++i) {
			printf("%s%i!\n", trans_upper(tmp), i);
			printf("%s%i@\n", trans_upper(tmp), i);
			printf("%s%i#\n", trans_upper(tmp), i);
			printf("%s%i$\n", trans_upper(tmp), i);
			printf("%s%i%%\n", trans_upper(tmp), i);
			printf("%s%i&\n", trans_upper(tmp), i);
		}
	}
	
	// Print upper-transformed word with a recent date and special char at the end (2-digit and 4-digit)
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		memset(tmp, 0, BUFSIZ);
		strcpy(tmp, word);
		for (i = 2022; i >= 1965; --i) {
			printf("%s%i!\n", trans_upper(tmp), i);
			printf("%s%i@\n", trans_upper(tmp), i);
			printf("%s%i#\n", trans_upper(tmp), i);
			printf("%s%i$\n", trans_upper(tmp), i);
			printf("%s%i%%\n", trans_upper(tmp), i);
			printf("%s%i&\n", trans_upper(tmp), i);
		}
		for (i = 22; i >= 0; --i) {
			printf("%s%i!\n", trans_upper(tmp), i);
			printf("%s%i@\n", trans_upper(tmp), i);
			printf("%s%i#\n", trans_upper(tmp), i);
			printf("%s%i$\n", trans_upper(tmp), i);
			printf("%s%i%%\n", trans_upper(tmp), i);
			printf("%s%i&\n", trans_upper(tmp), i);
		}
		for (i = 99; i >= 65; --i) {
			printf("%s%i!\n", trans_upper(tmp), i);
			printf("%s%i@\n", trans_upper(tmp), i);
			printf("%s%i#\n", trans_upper(tmp), i);
			printf("%s%i$\n", trans_upper(tmp), i);
			printf("%s%i%%\n", trans_upper(tmp), i);
			printf("%s%i&\n", trans_upper(tmp), i);
		}
	}

	/************************
	 * ALL UPPER WORD VARIATIONS
	 ************************/

	// Print all upper-transformed word list
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		memset(tmp, 0, BUFSIZ);
		strcpy(tmp, word);
		printf("%s\n", trans_all_upper(tmp));
	}
	
	// Print all upper-transformed word with a single digit at the end
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		memset(tmp, 0, BUFSIZ);
		strcpy(tmp, word);
		for (i = 0; i <= 9; ++i) {
			printf("%s%i\n", trans_all_upper(tmp), i);
		}
	}
	
	// Print all upper-transformed word with a recent date at the end (2-digit and 4-digit)
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		memset(tmp, 0, BUFSIZ);
		strcpy(tmp, word);
		for (i = 2022; i >= 1965; --i) {
			printf("%s%i\n", trans_all_upper(tmp), i);
		}
		for (i = 22; i >= 0; --i) {
			printf("%s%02i\n", trans_all_upper(tmp), i);
		}
		for (i = 99; i >= 65; --i) {
			printf("%s%i\n", trans_all_upper(tmp), i);
		}
	}
	
	// Print all upper-transformed word with a special character at the end
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		memset(tmp, 0, BUFSIZ);
		strcpy(tmp, word);
		printf("%s!\n", trans_all_upper(tmp));
		printf("%s@\n", trans_all_upper(tmp));
		printf("%s#\n", trans_all_upper(tmp));
		printf("%s$\n", trans_all_upper(tmp));
		printf("%s%%\n", trans_all_upper(tmp));
		printf("%s&\n", trans_all_upper(tmp));
	}

	// Print all upper-transformed word with a single digit and special char at the end
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		memset(tmp, 0, BUFSIZ);
		strcpy(tmp, word);
		for (i = 0; i <= 9; ++i) {
			printf("%s%i!\n", trans_all_upper(tmp), i);
			printf("%s%i@\n", trans_all_upper(tmp), i);
			printf("%s%i#\n", trans_all_upper(tmp), i);
			printf("%s%i$\n", trans_all_upper(tmp), i);
			printf("%s%i%%\n", trans_all_upper(tmp), i);
			printf("%s%i&\n", trans_all_upper(tmp), i);
		}
	}
	
	// Print all upper-transformed word with a recent date at the end (2-digit and 4-digit)
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		memset(tmp, 0, BUFSIZ);
		strcpy(tmp, word);
		for (i = 2022; i >= 1965; --i) {
			printf("%s%i!\n", trans_all_upper(tmp), i);
			printf("%s%i@\n", trans_all_upper(tmp), i);
			printf("%s%i#\n", trans_all_upper(tmp), i);
			printf("%s%i$\n", trans_all_upper(tmp), i);
			printf("%s%i%%\n", trans_all_upper(tmp), i);
			printf("%s%i&\n", trans_all_upper(tmp), i);
		}
		for (i = 22; i >= 0; --i) {
			printf("%s%i!\n", trans_all_upper(tmp), i);
			printf("%s%i@\n", trans_all_upper(tmp), i);
			printf("%s%i#\n", trans_all_upper(tmp), i);
			printf("%s%i$\n", trans_all_upper(tmp), i);
			printf("%s%i%%\n", trans_all_upper(tmp), i);
			printf("%s%i&\n", trans_all_upper(tmp), i);
		}
		for (i = 99; i >= 65; --i) {
			printf("%s%i!\n", trans_all_upper(tmp), i);
			printf("%s%i@\n", trans_all_upper(tmp), i);
			printf("%s%i#\n", trans_all_upper(tmp), i);
			printf("%s%i$\n", trans_all_upper(tmp), i);
			printf("%s%i%%\n", trans_all_upper(tmp), i);
			printf("%s%i&\n", trans_all_upper(tmp), i);
		}
	}

	/*****************************
	 * DUAL PLAIN WORD VARIATIONS
	 *****************************/

	// Print dual plain word list
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (wordlist_reset2(); (word2 = wordlist_get2()) != NULL; ) {
			printf("%s%s\n", word, word2);
		}
	}
	
	// Print dual plain word with a single digit at the end
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (wordlist_reset2(); (word2 = wordlist_get2()) != NULL; ) {
			for (i = 0; i <= 9; ++i) {
				printf("%s%s%i\n", word, word2, i);
			}
		}
	}
	
	// Print dual plain word with a recent date at the end (2-digit and 4-digit)
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (wordlist_reset2(); (word2 = wordlist_get2()) != NULL; ) {
			for (i = 2022; i >= 1965; --i) {
				printf("%s%s%i\n", word, word2, i);
			}
			for (i = 22; i >= 0; --i) {
				printf("%s%s%02i\n", word, word2, i);
			}
			for (i = 99; i >= 65; --i) {
				printf("%s%s%i\n", word, word2, i);
			}
		}
	}
	
	// Print dual plain word with a special character at the end
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (wordlist_reset2(); (word2 = wordlist_get2()) != NULL; ) {
			printf("%s%s!\n", word, word2);
			printf("%s%s@\n", word, word2);
			printf("%s%s#\n", word, word2);
			printf("%s%s$\n", word, word2);
			printf("%s%s%%\n", word, word2);
			printf("%s%s&\n", word, word2);
		}
	}

	// Print dual plain word with a single digit at the end
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (wordlist_reset2(); (word2 = wordlist_get2()) != NULL; ) {
			for (i = 0; i <= 9; ++i) {
				printf("%s%s%i!\n", word, word2, i);
				printf("%s%s%i@\n", word, word2, i);
				printf("%s%s%i#\n", word, word2, i);
				printf("%s%s%i$\n", word, word2, i);
				printf("%s%s%i%%\n", word, word2, i);
				printf("%s%s%i&\n", word, word2, i);
			}
		}
	}
	
	// Print dual plain word with a recent date at the end (2-digit and 4-digit)
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (wordlist_reset2(); (word2 = wordlist_get2()) != NULL; ) {
			for (i = 2022; i >= 1965; --i) {
				printf("%s%s%i!\n", word, word2, i);
				printf("%s%s%i@\n", word, word2, i);
				printf("%s%s%i#\n", word, word2, i);
				printf("%s%s%i$\n", word, word2, i);
				printf("%s%s%i%%\n", word, word2, i);
				printf("%s%s%i&\n", word, word2, i);
			}
			for (i = 22; i >= 0; --i) {
				printf("%s%s%i!\n", word, word2, i);
				printf("%s%s%i@\n", word, word2, i);
				printf("%s%s%i#\n", word, word2, i);
				printf("%s%s%i$\n", word, word2, i);
				printf("%s%s%i%%\n", word, word2, i);
				printf("%s%s%i&\n", word, word2, i);
			}
			for (i = 99; i >= 65; --i) {
				printf("%s%s%i!\n", word, word2, i);
				printf("%s%s%i@\n", word, word2, i);
				printf("%s%s%i#\n", word, word2, i);
				printf("%s%s%i$\n", word, word2, i);
				printf("%s%s%i%%\n", word, word2, i);
				printf("%s%s%i&\n", word, word2, i);
			}
		}
	}

	/*****************************
	 * DUAL FIRST UPPER WORD VARIATIONS
	 *****************************/

	// Print upper-transformed dual word list
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (wordlist_reset2(); (word2 = wordlist_get2()) != NULL; ) {
			memset(tmp, 0, BUFSIZ);
			memset(tmp2, 0, BUFSIZ);
			strcpy(tmp, word);
			strcpy(tmp2, word2);
			printf("%s%s\n", trans_upper(tmp), trans_upper(tmp2));
		}
	}
	
	// Print upper-transformed dual word with a single digit at the end
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (wordlist_reset2(); (word2 = wordlist_get2()) != NULL; ) {
			memset(tmp, 0, BUFSIZ);
			memset(tmp2, 0, BUFSIZ);
			strcpy(tmp, word);
			strcpy(tmp2, word2);
			for (i = 0; i <= 9; ++i) {
				printf("%s%s%i\n", trans_upper(tmp), trans_upper(tmp2), i);
			}
		}
	}
	
	// Print upper-transformed dual word with a recent date at the end (2-digit and 4-digit)
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (wordlist_reset2(); (word2 = wordlist_get2()) != NULL; ) {
			memset(tmp, 0, BUFSIZ);
			memset(tmp2, 0, BUFSIZ);
			strcpy(tmp, word);
			strcpy(tmp2, word2);
			for (i = 2022; i >= 1965; --i) {
				printf("%s%s%i\n", trans_upper(tmp), trans_upper(tmp2), i);
			}
			for (i = 22; i >= 0; --i) {
				printf("%s%s%02i\n", trans_upper(tmp), trans_upper(tmp2), i);
			}
			for (i = 99; i >= 65; --i) {
				printf("%s%s%i\n", trans_upper(tmp), trans_upper(tmp2), i);
			}
		}
	}
	
	// Print upper-transformed dual word with a special character at the end
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (wordlist_reset2(); (word2 = wordlist_get2()) != NULL; ) {
			memset(tmp, 0, BUFSIZ);
			memset(tmp2, 0, BUFSIZ);
			strcpy(tmp, word);
			strcpy(tmp2, word2);
			printf("%s%s!\n", trans_upper(tmp), trans_upper(tmp2));
			printf("%s%s@\n", trans_upper(tmp), trans_upper(tmp2));
			printf("%s%s#\n", trans_upper(tmp), trans_upper(tmp2));
			printf("%s%s$\n", trans_upper(tmp), trans_upper(tmp2));
			printf("%s%s%%\n", trans_upper(tmp), trans_upper(tmp2));
			printf("%s%s&\n", trans_upper(tmp), trans_upper(tmp2));
		}
	}

	// Print upper-transformed dual word with a single digit at the end
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (wordlist_reset2(); (word2 = wordlist_get2()) != NULL; ) {
			memset(tmp, 0, BUFSIZ);
			memset(tmp2, 0, BUFSIZ);
			strcpy(tmp, word);
			strcpy(tmp2, word2);
			for (i = 0; i <= 9; ++i) {
				printf("%s%s%i!\n", trans_upper(tmp), trans_upper(tmp2), i);
				printf("%s%s%i@\n", trans_upper(tmp), trans_upper(tmp2), i);
				printf("%s%s%i#\n", trans_upper(tmp), trans_upper(tmp2), i);
				printf("%s%s%i$\n", trans_upper(tmp), trans_upper(tmp2), i);
				printf("%s%s%i%%\n", trans_upper(tmp), trans_upper(tmp2), i);
				printf("%s%s%i&\n", trans_upper(tmp), trans_upper(tmp2), i);
			}
		}
	}
	
	// Print upper-transformed dual word with a recent date at the end (2-digit and 4-digit)
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (wordlist_reset2(); (word2 = wordlist_get2()) != NULL; ) {
			memset(tmp, 0, BUFSIZ);
			memset(tmp2, 0, BUFSIZ);
			strcpy(tmp, word);
			strcpy(tmp2, word2);
			for (i = 2022; i >= 1965; --i) {
				printf("%s%s%i!\n", trans_upper(tmp), trans_upper(tmp2), i);
				printf("%s%s%i@\n", trans_upper(tmp), trans_upper(tmp2), i);
				printf("%s%s%i#\n", trans_upper(tmp), trans_upper(tmp2), i);
				printf("%s%s%i$\n", trans_upper(tmp), trans_upper(tmp2), i);
				printf("%s%s%i%%\n", trans_upper(tmp), trans_upper(tmp2), i);
				printf("%s%s%i&\n", trans_upper(tmp), trans_upper(tmp2), i);
			}
			for (i = 22; i >= 0; --i) {
				printf("%s%s%i!\n", trans_upper(tmp), trans_upper(tmp2), i);
				printf("%s%s%i@\n", trans_upper(tmp), trans_upper(tmp2), i);
				printf("%s%s%i#\n", trans_upper(tmp), trans_upper(tmp2), i);
				printf("%s%s%i$\n", trans_upper(tmp), trans_upper(tmp2), i);
				printf("%s%s%i%%\n", trans_upper(tmp), trans_upper(tmp2), i);
				printf("%s%s%i&\n", trans_upper(tmp), trans_upper(tmp2), i);
			}
			for (i = 99; i >= 65; --i) {
				printf("%s%s%i!\n", trans_upper(tmp), trans_upper(tmp2), i);
				printf("%s%s%i@\n", trans_upper(tmp), trans_upper(tmp2), i);
				printf("%s%s%i#\n", trans_upper(tmp), trans_upper(tmp2), i);
				printf("%s%s%i$\n", trans_upper(tmp), trans_upper(tmp2), i);
				printf("%s%s%i%%\n", trans_upper(tmp), trans_upper(tmp2), i);
				printf("%s%s%i&\n", trans_upper(tmp), trans_upper(tmp2), i);
			}
		}
	}

	/*****************************
	 * DUAL ALL UPPER WORD VARIATIONS
	 *****************************/

	// Print all upper-transformed dual word list
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (wordlist_reset2(); (word2 = wordlist_get2()) != NULL; ) {
			memset(tmp, 0, BUFSIZ);
			memset(tmp2, 0, BUFSIZ);
			strcpy(tmp, word);
			strcpy(tmp2, word2);
			printf("%s%s\n", trans_all_upper(tmp), trans_all_upper(tmp2));
		}
	}
	
	// Print all upper-transformed dual word with a single digit at the end
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (wordlist_reset2(); (word2 = wordlist_get2()) != NULL; ) {
			memset(tmp, 0, BUFSIZ);
			memset(tmp2, 0, BUFSIZ);
			strcpy(tmp, word);
			strcpy(tmp2, word2);
			for (i = 0; i <= 9; ++i) {
				printf("%s%s%i\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
			}
		}
	}
	
	// Print all upper-transformed dual word with a recent date at the end (2-digit and 4-digit)
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (wordlist_reset2(); (word2 = wordlist_get2()) != NULL; ) {
			memset(tmp, 0, BUFSIZ);
			memset(tmp2, 0, BUFSIZ);
			strcpy(tmp, word);
			strcpy(tmp2, word2);
			for (i = 2022; i >= 1965; --i) {
				printf("%s%s%i\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
			}
			for (i = 22; i >= 0; --i) {
				printf("%s%s%02i\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
			}
			for (i = 99; i >= 65; --i) {
				printf("%s%s%i\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
			}
		}
	}
	
	// Print all upper-transformed dual word with a special character at the end
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (wordlist_reset2(); (word2 = wordlist_get2()) != NULL; ) {
			memset(tmp, 0, BUFSIZ);
			memset(tmp2, 0, BUFSIZ);
			strcpy(tmp, word);
			strcpy(tmp2, word2);
			printf("%s%s!\n", trans_all_upper(tmp), trans_all_upper(tmp2));
			printf("%s%s@\n", trans_all_upper(tmp), trans_all_upper(tmp2));
			printf("%s%s#\n", trans_all_upper(tmp), trans_all_upper(tmp2));
			printf("%s%s$\n", trans_all_upper(tmp), trans_all_upper(tmp2));
			printf("%s%s%%\n", trans_all_upper(tmp), trans_all_upper(tmp2));
			printf("%s%s&\n", trans_all_upper(tmp), trans_all_upper(tmp2));
		}
	}

	// Print all upper-transformed dual word with a single digit at the end
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (wordlist_reset2(); (word2 = wordlist_get2()) != NULL; ) {
			memset(tmp, 0, BUFSIZ);
			memset(tmp2, 0, BUFSIZ);
			strcpy(tmp, word);
			strcpy(tmp2, word2);
			for (i = 0; i <= 9; ++i) {
				printf("%s%s%i!\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
				printf("%s%s%i@\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
				printf("%s%s%i#\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
				printf("%s%s%i$\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
				printf("%s%s%i%%\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
				printf("%s%s%i&\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
			}
		}
	}
	
	// Print all upper-transformed dual word with a recent date at the end (2-digit and 4-digit)
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (wordlist_reset2(); (word2 = wordlist_get2()) != NULL; ) {
			memset(tmp, 0, BUFSIZ);
			memset(tmp2, 0, BUFSIZ);
			strcpy(tmp, word);
			strcpy(tmp2, word2);
			for (i = 2022; i >= 1965; --i) {
				printf("%s%s%i!\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
				printf("%s%s%i@\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
				printf("%s%s%i#\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
				printf("%s%s%i$\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
				printf("%s%s%i%%\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
				printf("%s%s%i&\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
			}
			for (i = 22; i >= 0; --i) {
				printf("%s%s%i!\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
				printf("%s%s%i@\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
				printf("%s%s%i#\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
				printf("%s%s%i$\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
				printf("%s%s%i%%\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
				printf("%s%s%i&\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
			}
			for (i = 99; i >= 65; --i) {
				printf("%s%s%i!\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
				printf("%s%s%i@\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
				printf("%s%s%i#\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
				printf("%s%s%i$\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
				printf("%s%s%i%%\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
				printf("%s%s%i&\n", trans_all_upper(tmp), trans_all_upper(tmp2), i);
			}
		}
	}

	/************************
	 * LEET WORD VARIATIONS
	 ************************/

	/*

	// Print leet-transformed word list
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		tmp = malloc(strlen(word) + 1);
		strcpy(tmp, word);
		printf("%s\n", trans_leet(tmp));
		free(tmp);
	}
	
	// Print leet-transformed word with a single digit at the end
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		tmp = malloc(strlen(word) + 1);
		strcpy(tmp, word);
		for (i = 0; i <= 9; ++i) {
			printf("%s%i\n", trans_leet(tmp), i);
		}
		free(tmp);
	}
	
	// Print leet-transformed word with a recent date at the end (2-digit and 4-digit)
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		tmp = malloc(strlen(word) + 1);
		strcpy(tmp, word);
		for (i = 2017; i >= 1965; --i) {
			printf("%s%i\n", trans_leet(tmp), i);
		}
		for (i = 17; i >= 0; --i) {
			printf("%s%02i\n", trans_leet(tmp), i);
		}
		for (i = 99; i >= 65; --i) {
			printf("%s%i\n", trans_leet(tmp), i);
		}
		free(tmp);
	}
	
	// Print leet-transformed word with a special character at the end
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		tmp = malloc(strlen(word) + 1);
		strcpy(tmp, word);
		printf("%s!\n", trans_leet(tmp));
		printf("%s@\n", trans_leet(tmp));
		printf("%s#\n", trans_leet(tmp));
		printf("%s$\n", trans_leet(tmp));
		printf("%s%%\n", trans_leet(tmp));
		printf("%s&\n", trans_leet(tmp));
		free(tmp);
	}

	*/

	/*****************************
	 * DUAL LEET WORD VARIATIONS
	 *****************************/

	/*

	// Print dual plain word list
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (wordlist_reset2(); (word2 = wordlist_get2()) != NULL; ) {
			tmp = malloc(strlen(word) + 1);
			tmp2 = malloc(strlen(word2) + 1);
			strcpy(tmp, word);
			strcpy(tmp2, word2);
			printf("%s%s\n", trans_leet(tmp), trans_leet(tmp2));
			free(tmp);
			free(tmp2);
		}
	}
	
	// Print dual plain word with a single digit at the end
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (wordlist_reset2(); (word2 = wordlist_get2()) != NULL; ) {
			tmp = malloc(strlen(word) + 1);
			tmp2 = malloc(strlen(word2) + 1);
			strcpy(tmp, word);
			strcpy(tmp2, word2);
			for (i = 0; i <= 9; ++i) {
				printf("%s%s%i\n", trans_leet(tmp), trans_leet(tmp2), i);
			}
			free(tmp);
			free(tmp2);
		}
	}
	
	// Print dual plain word with a recent date at the end (2-digit and 4-digit)
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (wordlist_reset2(); (word2 = wordlist_get2()) != NULL; ) {
			tmp = malloc(strlen(word) + 1);
			tmp2 = malloc(strlen(word2) + 1);
			strcpy(tmp, word);
			strcpy(tmp2, word2);
			for (i = 2017; i >= 1965; --i) {
				printf("%s%s%i\n", trans_leet(tmp), trans_leet(tmp2), i);
			}
			for (i = 17; i >= 0; --i) {
				printf("%s%s%02i\n", trans_leet(tmp), trans_leet(tmp2), i);
			}
			for (i = 99; i >= 65; --i) {
				printf("%s%s%i\n", trans_leet(tmp), trans_leet(tmp2), i);
			}
			free(tmp);
			free(tmp2);
		}
	}
	
	// Print dual plain word with a special character at the end
	for (wordlist_reset(); (word = wordlist_get()) != NULL; ) {
		for (wordlist_reset2(); (word2 = wordlist_get2()) != NULL; ) {
			tmp = malloc(strlen(word) + 1);
			tmp2 = malloc(strlen(word2) + 1);
			strcpy(tmp, word);
			strcpy(tmp2, word2);
			printf("%s%s!\n", trans_leet(tmp), trans_leet(tmp2));
			printf("%s%s@\n", trans_leet(tmp), trans_leet(tmp2));
			printf("%s%s#\n", trans_leet(tmp), trans_leet(tmp2));
			printf("%s%s$\n", trans_leet(tmp), trans_leet(tmp2));
			printf("%s%s%%\n", trans_leet(tmp), trans_leet(tmp2));
			printf("%s%s&\n", trans_leet(tmp), trans_leet(tmp2));
			free(tmp);
			free(tmp2);
		}
	}

	*/
	
	// Close word file
	fclose(wordList);

	return 0;
}

void main_show_word_lists(void) {
	DIR *dp;
	struct dirent *ep;

	dp = opendir(WORD_LIST_DIR);
	if (dp != NULL) {
		while ((ep = readdir(dp))) {
			if ((ep->d_name)[0] == '.') {
				continue;
			}
			puts(ep->d_name);
		}
		closedir (dp);
	} else {
		main_shutdown("Couldn't open word list directory.");
	}
}

void main_shutdown(const char *errmsg) {
	
	// Log a shutdown message
	fprintf (stderr, "Shutting down. Reason: %s\n", errmsg);
	
	// Shutdown
	exit(1);
}
