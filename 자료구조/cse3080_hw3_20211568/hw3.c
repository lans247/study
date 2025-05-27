#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _edge
{
    int weight;
    int a, b;       //a to b
}edge;

int len = 0;                //edge내부 값들
int *vertex;                //vertex끼리 union한 값 들어감 -> cycle판별
int vertex_num;
int edge_num;
int connected_check = 0;    //connected체크위한 변수
int path_len = 0;           //path의 길이

edge *Edge;                 //edge의 값들이 저장될 주소

int sum_weight;             //경로의 합


edge min_back(){            //min_heap에서 뺴면서 최솟값 반환
    edge re = Edge[1];
    Edge[1] = Edge[len];
    Edge[len].weight = 0;
    Edge[len].a = 0; Edge[len].b = 0;
    len--;
 
    int p = 1;
    int c = 2;
    edge temp;
    while(c <= len){
        if(Edge[c].weight > Edge[c+1].weight) c++;      //둘 중 작은 곳으로 가야함
        if(c > len) c--;
        if(Edge[p].weight < Edge[c].weight) break; 
        temp = Edge[p];
        Edge[p] = Edge[c];
        Edge[c] = temp;
        p = c;
        c = c*2;
    }  
    return re;
}

void insert(int a, int b, int weight){          //min_heap으로 insert
    edge new; 
    new.a = a;
    new.b = b;
    new.weight = weight;
    
    int i = ++len;
    while(weight < Edge[i/2].weight && (i != 1)){
        Edge[i] = Edge[i/2];
        i = i/2;
    }
    Edge[i] = new;
}

int find(int a){
    int i = a;
    int j = vertex[i];
    while(j >= 0){
        i = j;
        j = vertex[i];
    }
    return i;
}



void vertex_union(int a, int b){
    int a_parent = find(a);
    int b_parent = find(b);
    int sum = vertex[a_parent] + vertex[b_parent];

    if(vertex[a_parent] > vertex[b_parent]){
        vertex[a_parent] = b_parent;
        vertex[b_parent] = sum;
    }
    else{
        vertex[b_parent] = a_parent;
        vertex[a_parent] = sum;
    }
}


edge* kruskal(){
    edge *path = (edge*)malloc(sizeof(edge) * (vertex_num-1));

    while(path_len < vertex_num - 1 && len > 0){           //path가 다 채워질 떄까지 혹은 경로가 다 비기 전까지
        edge line = min_back();
        if(find(line.a) != find(line.b)){           //부모가 동일하지 않다면.
            path[path_len] = line;
            path_len++;
            sum_weight += line.weight;
            vertex_union(line.a, line.b);   //kruskual에 투입되었으며 union.
        }
        else continue;                     //동일하면 다음 값.
    }

    if(path_len == vertex_num - 1) connected_check = 1;        //연결된 edge의 값이 v - 1이면 point가 전부 연결된 것.

    return path;
}



int main(int argc, char *argv[])
{
    int a, b, weight, i;

    double start = clock();         //타임 시작

    //값이 저장될 장소
    edge *path;

    FILE *read  = fopen(argv[1], "r");
    FILE *write = fopen("hw3_result.txt", "w");

    if(argv[1] == NULL){
        printf("usage: ./hw3 input_filename\n");
        return -1;
    }
    if(read == NULL) {
        printf("The input file does not exist.\n");
        return -1;
    }

    //정점 읽기
    fscanf(read, "%d", &vertex_num);
    vertex = (int*)malloc(sizeof(int) * vertex_num);            //0부터 시작
    for(i = 0; i < vertex_num; i++) vertex[i] = -1;

    //경로 읽기
    fscanf(read, "%d", &edge_num);
    Edge = (edge*)malloc(sizeof(edge) * (edge_num+1));          //1부터 시작 
    for(i = 0; i < edge_num; i++){
        fscanf(read, "%d %d %d", &a, &b, &weight);    
        insert(a, b, weight);
    }

    path = kruskal();
    
    
    for(i = 0; i < path_len; i++) fprintf(write, "%d %d %d\n", path[i].a, path[i].b, path[i].weight);       //path 출력
    fprintf(write, "%d\n", sum_weight);                                                                         //총 weight출력
    if(connected_check) fprintf(write, "CONNECTED\n");                                                          //연결, 비 연결 출력
    else fprintf(write, "DISCONNECTED\n");

    double end = clock();           //타임 끝

    printf("output written to hw3_result.txt.\n");
    printf("running time: %lf seconds\n", (end - start) / CLOCKS_PER_SEC);

    fclose(write);
    fclose(read);
    free(vertex);
    free(Edge);
    free(path);

    return 0;
}