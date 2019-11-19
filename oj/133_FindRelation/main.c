#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG					1

#define MAX_MEMBER_NUM			26
#define MAX_RELATION_NUM		500

#define RESULT_SUCC					0
#define RESULT_FAIL_INCONSISTENCY	-1
#define RESULT_FAIL_NOT_SORT		-2

#define INVALID_VALUE			0x7FFFFFFF

char *StrFail0 = "Inconsistency found after %d relations";
char *StrFail1 = "Sorted sequency cannot be determined.";
char *StrSucc  = "Sorted sequency determined after %d relations:%s";

int SortSequency(int MemberNum, int *RelationMap, int *InDegree, char *SortResult)
{
	int Top = INVALID_VALUE;
	int i;
	
	#if DEBUG==1
	printf("SortSequency SortResult=0x%x \n", SortResult);
	#endif

	/* find the only one top point, if more than one then means no top point */
	for (i = 0; i < MemberNum; i++) {
		if (InDegree[i] == 0) {
			if (Top == INVALID_VALUE) {
				Top = i;
			} else {
				return RESULT_FAIL_NOT_SORT;
			}
		} else {
			continue;
		}
	}

	if (Top == INVALID_VALUE) {
		return RESULT_FAIL_INCONSISTENCY;
	}

	*SortResult = Top + 'A';
	InDegree[Top] = INVALID_VALUE;
	RelationMap += Top * MAX_MEMBER_NUM;
	for (i = 0; i < MemberNum; i++) {
		if (*(RelationMap + i) != 0) {
			InDegree[i] -= 1;
		}
	}

	/* check whether finish all point */
	for (i = 0; i < MemberNum; i++) {
		if (InDegree[i] != INVALID_VALUE)
			break;
	}
	if (i == MemberNum) {
		*(SortResult + 1) = '\0';
		return RESULT_SUCC;
	}

	return SortSequency(MemberNum, RelationMap, InDegree, SortResult + 1);
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
	char RelationSort[MAX_MEMBER_NUM + 1];
	int Result;
	int ret;
	int i;
	
	#if DEBUG==1
	printf("RelationSort addr=0x%x \n", RelationSort);
	#endif

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
		memset(RelationSort, 0, sizeof(RelationSort));

		for (i = 1; i <= RelationNum; i++) {
			ret = scanf("%s", Relation);
			if (ret != 1) {
				printf("relation input error.\n");
				break;
			}
			
			#if DEBUG==1
			printf("Relation=%s \n", Relation);
			#endif

			MemberIndex0 = Relation[0] - 'A';
			MemberIndex1 = Relation[2] - 'A';

			InDegree[MemberIndex1] += 1;
			RelationMap[MemberIndex0][MemberIndex1] = 1;

			if (i < (MemberNum - 1))
				continue;

			#if DEBUG==1
			printf("InDegree 0=%d, 1=%d, 2=%d, 3=%d \n",
					InDegree[0], InDegree[1], InDegree[2], InDegree[3]);
			#endif

			Result = SortSequency(MemberNum,
					      RelationMap,
					      InDegree,
					      RelationSort);
			if (Result != RESULT_FAIL_NOT_SORT)
				break;
		}

		switch (Result) {
		case RESULT_SUCC:
			printf("Sorted sequency determined after %d relations:%s\n", RelationSort);
			break;

		case RESULT_FAIL_INCONSISTENCY:
			printf("Inconsistency found after %d relations\n", i);
			break;

		case RESULT_FAIL_NOT_SORT:
			printf("Sorted sequency cannot be determined.\n");
			break;

		default: break;
		}


	}
}
