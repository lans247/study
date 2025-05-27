#include<stdio.h>
#include<string.h>

char p[3001];
char s[10000001];
int f[3001] = {-1, };		//failure의 처음은 -1
int o[10000001];

void fail(char *p)
{
	int i, j, n = strlen(p);		

	for (j = 1; j < n; j++){
		
		i = f[j-1] + 1;
		
		while((i != 0) && (p[j] != p[i])) {			//현재의 것(i)이 순서(j)와 같다면 exit
				i = f[i-1] + 1;						//다르다면 그 위치로 이동해 비교
		}
		
		if(p[j] == p[i]) {					//위치와 순서를 비교
			f[j] = i;							//다음 순서로
		}
		else f[j] = -1;							//다 틀리면 -1
	}
}

int main()
{
	int i = 0, j = 0, s_len, p_len, start;
	int out_len = 0;
	FILE *string_fp, *pattern_fp, *out;
	
	//file 오픈
	string_fp = fopen("string.txt", "r");
	pattern_fp = fopen("pattern.txt", "r");
	out = fopen("result_kmp.txt", "w");

	if(string_fp == NULL){
		printf("string file not found");
		return -1;
	}
	if(pattern_fp == NULL){
		printf("pattern file not found");
		return -1;
	} 
	if(out == NULL){
		printf("out file not found");
		return -1;
	}

	fgets(s, 10000001, string_fp);
	fgets(p, 3001, pattern_fp);

	s_len = strlen(s);
	p_len = strlen(p);	

	fail(p);
	
	while(i < s_len && j <= p_len){
		if(s[i] == p[j]){
			i++;
			j++;			 	
			if(j == p_len){	
				o[out_len++] = i - p_len; //패턴이 맞더라도 연산은 동일, 
				j = f[j-1] + 1;	 //i는 그대로, j는 f[j-1] + 1위치로 이동후 비교
			}
		}
		else if(j == 0) {					//아예 실패시
			i++;
		}
		else {								//f가 가르키는 위치와 값이 일치하지 않을 때
			j = f[j-1] + 1;
		}
	}

	fprintf(out, "%d\n", out_len);
	for(i = 0; i<out_len; i++)
	{
		fprintf(out, "%d ", o[i]);
	}
	fprintf(out, "\n");

	printf("progream complete. Result saved to retult_kmp.txt\n");

	fclose(string_fp);
	fclose(pattern_fp);
	fclose(out);
	return 0;
}