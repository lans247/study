#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

#define max_len 1000001

FILE *f, *o;

void min_insert(int *a, int data, int len){
    int i = len + 1;
    while(data < a[i/2] && (i != 1)){              //맨 처음 heap이 아니며, 넣고자 하는 data가 부모보다 작은 경우(minheap은 부모 < 자식)
        a[i] = a[i/2];                      
        i = i/2;
    }
    a[i] = data;
}

void max_insert(int *a, int data, int len){
    int i = len + 1;
    while(data > a[i/2] && (i != 1)){              //맨 처음 heap이 아니며, 넣고자 하는 data가 부모보다 큰 경우(maxheap은 부모 > 자식)
        a[i] = a[i/2];                      
        i = i/2;
    }
    a[i] = data;
}

void copy(int *a, int *b, int len){
    int i;
    for(i = 1; i <= len; i++){
        a[i] = b[i];
    }
    return;
}

void ascend_print(int *a, int len)         //min_heap
{
    if(len == 0) return; 
    fprintf(o, "%d ", a[1]);
    a[1] = a[len];
    a[len] = 0;
    len--;
 
    int p = 1;
    int c = 2;
    int temp;
    while(c <= len){
        if(a[c] > a[c+1]) c++;      //둘 중 작은 곳으로 가야함
        if(c > len) c--;
        if(a[p] < a[c]) break; 
        temp = a[p];
        a[p] = a[c];
        a[c] = temp;
        p = c;
        c = c*2;
    }
    ascend_print(a, len);
}
void descend_print(int *a, int len)         //max_heap
{
    if(len == 0) return; 
    fprintf(o, "%d ", a[1]);
    a[1] = a[len];
    a[len] = 0;
    len--;

    int p = 1;
    int c = 2;
    int temp;
    while(c <= len){
        if(a[c] < a[c+1]) c++;      //둘 중 큰 곳으로 가야함
        if(c > len) c--;
        if(a[p] > a[c]) break;
        temp = a[p];
        a[p] = a[c];
        a[c] = temp;
        p = c;
        c = c*2;
    }
    descend_print(a, len);
}


int main(int argc, char **argv)
{
    char command[10];


    int *min_sort_heap = (int*)calloc(max_len, sizeof(int));
    int *max_sort_heap = (int*)calloc(max_len, sizeof(int));

    int *min_copy = (int*)calloc(max_len, sizeof(int));
    int *max_copy = (int*)calloc(max_len, sizeof(int));


    int len = 0;

    int command_num;

    f = fopen(argv[1], "r");    
    o = fopen("hw2_result.txt", "w"); 

    if(f == NULL || o == NULL){
		printf("usage: ./hw2 input_filename\n");
		return -1;
	}

    double start = clock();
    while(1)
    {
        if(feof(f)) break;
        if(fscanf(f, "%s", command) == EOF) break;

        if(!strcmp(command, "INSERT"))
        {
            fscanf(f, "%d", &command_num);
            max_insert(max_sort_heap, command_num, len);
            min_insert(min_sort_heap, command_num, len);
            len++;
        }
        else if(!strcmp(command, "ASCEND"))
        {
            copy(min_copy, min_sort_heap, len);
            ascend_print(min_copy, len);
            fprintf(o, "\n");
        }
        else if(!strcmp(command, "DESCEND"))
        {
            copy(max_copy, max_sort_heap, len);
            descend_print(max_copy, len);
            fprintf(o, "\n");
        }
        else break;
    }
    double finish = clock();

    printf("output written to hw2_result.txt.\n");
    printf("running time: %lf seconds\n", (finish - start) / CLOCKS_PER_SEC);

    fclose(o);
    fclose(f);

    free(min_sort_heap);
    free(max_sort_heap);
    free(min_copy);
    free(max_copy);

    return 0;
}