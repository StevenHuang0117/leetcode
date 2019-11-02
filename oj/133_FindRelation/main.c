#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBER_NUM			26
#define MAX_RELATION_NUM		500

#define RESULT_SUCC			0
#define RESULT_FAIL_INCONSISTENCY	-1
#define RESULT_FAIL_NOT_SORT		-2

char *StrFail0 = "Inconsistency found after %d relations";
char *StrFail1 = "Sorted sequency cannot be determined.";
char *StrSucc  = "Sorted sequency determined after %d relations:%s";

int SortSequency(int MemberNum, int *RelationMap, int *InDegree)
{
	
}

int main(void)
{
	int RelationMap[MAX_MEMBER_NUM][MAX_MEMBER_NUM];
	int InDegree[MAX_MEMBER_NUM];
	int MemberNum;
	int MemberIndex0;
	int MemberIndex1;
	int RelationNum;
	char Relation[4];
	int Result;
	int ret;
	int i;

	while (scanf("%d%d", &MemberNum, &RelationNum) == 2) {
		if ((MemberNum < 2) || (MemberNum > MAX_MEMBER_NUM)) {
			printf("MemberNum wrong:%d \n", MemberNum);
			continue;
		}

		if (RelationNum > MAX_RELATION_NUM) {
			printf("RelationNum wrong:%d \n", RelationNum);
			continue;
		}

		if (RelationNum < (MemberNum - 1)) {
			printf("Sorted sequency cannot be determined.\n");
			continue;
		}
		
		/* Initial result */
		Result = RESULT_FAIL_NOT_SORT;

		memset(RelationMap, 0, sizeof(RelationMap));
		memset(InDegree, 0, sizeof(InDegree));
		
		for (i = 0; i < RelationNum; i++) {
			ret = scanf("%s", Relation);
			if (ret != 1) {
				printf("relation input error.\n");
				break;
			}
			
			MemberIndex0 = Relation[0] - 'A';
			MemberIndex1 = Relation[1] - 'A';
			
			InDegree[MemberIndex1] += 1;
			RelationMap[MemberIndex0][MemberIndex1] = 1;
			
			if (i < (RelationNum - 1))
				continue;
			
			Result = SortSequency(MemberNum,
					      RelationMap,
					      InDegree);
			if (Result != RESULT_FAIL_NOT_SORT)
				break;
		}
		
		switch (Result) {
		case RESULT_SUCC:
			printf("Sorted sequency determined after %d relations:%s\n");
			break;
			
		case RESULT_FAIL_INCONSISTENCY:
			printf("Inconsistency found after %d relations\n", i);
			break;
			
		case RESULT_FAIL_NOT_SORT:
			printf("Sorted sequency cannot be determined.\n", i);
			break;
			
		default: break;
		}


	}
}
