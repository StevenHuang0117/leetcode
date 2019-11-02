#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN			1000

/* judge whether is */
int isPalindrome(char *s, int StartIndex, int EndIndex)
{
	int i = StartIndex;
	int j = EndIndex;
	
	if ((i >= j))
		return 0;

	do {
		if (s[i] != s[j]) {
			return 0;
		}

		if ((j - i) > 2) {
			i++;
			j--;
		} else {
			break;
		}
	}while (i < j);

	return 1;
}

int main(void)
{
	char s[MAX_STR_LEN + 1];
	char Palindrome[MAX_STR_LEN + 1];
	int Longest_Start = 0;
	int Longest_Len = 0;
	int MatchLen;
	int StrLen;
	int i, j;

	memset(s, 0, sizeof(s));
	while (scanf("%s", s) == 1) {
		StrLen = strlen(s);
		if (StrLen < 2)
			continue;

		for(i = 0; i < (StrLen - 1); i++) {
			/* 如果剩余的字符串比已找到的短，则退出*/
			if ((StrLen - i) < Longest_Len)
				break;
			
			for (j = StrLen - 1; i < j; j-- ) {
				/* 如果剩余的字符串比已找到的短，则退出*/
				if ((j - i) < Longest_Len)
					break;
				
				if (isPalindrome(s, i, j)) {
					MatchLen = j - i + 1;
					
					/* 如果找到，判断是否比之前找到的长*/
					if (MatchLen > Longest_Len) {
						Longest_Start = i;
						Longest_Len = MatchLen;
					}
					
					break;
				}

			}
		}
		
		memset(Palindrome, 0, sizeof(Palindrome));
		for (i = 0; i < Longest_Len; i++)
			Palindrome[i] = s[Longest_Start + i];
		Palindrome[i] = '\0';
		printf("%s\n", Palindrome);
		
		memset(s, 0, sizeof(s));
		Longest_Start = 0;
		Longest_Len = 0;
	}
}
