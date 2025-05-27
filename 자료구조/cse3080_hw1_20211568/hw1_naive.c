#include<stdio.h>
#include<string.h>

char p[3001];
char s[10000001];
int o[10000001];

int main()
{
	int i = 0, j = 0, s_len, p_len, start;
	int out_len = 0;
	FILE *string_fp, *pattern_fp, *out;
	
	//file 오픈
	string_fp = fopen("string.txt", "r");
	pattern_fp = fopen("pattern.txt", "r");
	out = fopen("result_naive.txt", "w");

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

	
    for(i = 0; i < s_len; i++)
    {
        if(s[i] == p[j])
        {
                for(j = 0; j < p_len && i < s_len; ){
                    if(s[i] != p[j]) {
                        break;
                    }
                    i++;
                    j++;
                }
                i = i - j;
                if(j == p_len){
                    o[out_len++] = i;
                }
                j = 0;
        }
    }

	fprintf(out, "%d\n", out_len);
	for(i = 0; i<out_len; i++)
	{
		fprintf(out, "%d ", o[i]);
	}
	fprintf(out, "\n");

	printf("progream complete. Result saved to retult_naive.txt\n");

	fclose(string_fp);
	fclose(pattern_fp);
	fclose(out);
	return 0;
}