#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

#define MAX_OUTPUT_SIZE 1024
#define MAPPING_SIZE 256
#define ROBOTS_NUMBER 2
#define FILENAME "input.txt"

char nums[4][3] = {
    { '7' , '8', '9' },
    { '4' , '5', '6' },
    { '1' , '2', '3' },
    { 'X' , '0', 'A' }};

char dirs[2][3] = {
    { 'X' , '^' , 'A' },
    { '<' , 'v' , '>' }};

char num_pos[MAPPING_SIZE][2];
char dir_pos[MAPPING_SIZE][2];
char cache[MAX_OUTPUT_SIZE][MAPPING_SIZE];
long long counts[MAX_OUTPUT_SIZE];
int c = 0;

void resolve_numerical(char* input, char* output){
    int x = num_pos['A'][0];
    int y = num_pos['A'][1];
    int i = 0;

    output[i++]='A';
    while(*input){
        int new_x=num_pos[(int)*input][0], new_y=num_pos[(int)*input][1];
        if(y<3 || (y==3 && new_x>0)) while(new_x < x){ output[i++]='<'; x--;}
        if(x>0 || (x==0 && new_y<3)) while(new_y > y){ output[i++]='v'; y++;}
        while(new_x > x){ output[i++]='>'; x++;}
        while(new_y < y){ output[i++]='^'; y--;}
        while(new_x < x){ output[i++]='<'; x--;}
        while(new_y > y){ output[i++]='v'; y++;}
        output[i++]='A';
        input++;
    }
    output[i]='\0';
}

long long resolve_dirs(char a, char b, int recursion_depth) {
    int x = dir_pos[(int)a][0];
    int y = dir_pos[(int)a][1]; 
    int new_x = dir_pos[(int)b][0];
    int new_y = dir_pos[(int)b][1];
    int len = 0;

    char output[MAPPING_SIZE];
    output[len++]='A';
    if(y == 1 || new_x > 0) while(new_x < x){ output[len++]='<'; x--;}
    if(x > 0) while(new_y < y){ output[len++]='^'; y--;}
    while(new_y > y){ output[len++]='v'; y++;}
    while(new_x < x){ output[len++]='<'; x--;}
    while(new_x > x){ output[len++]='>'; x++;}
    while(new_y < y){ output[len++]='^'; y--;}
    output[len++]='A';
    output[len]='\0';

    if (recursion_depth == 1)
        return strlen(output) - 1;

    char key[MAPPING_SIZE];
    sprintf(key, "%c%c%d", a, b, recursion_depth);
    ENTRY entry = {.key = key}, *found_entry;

    if((found_entry=hsearch(entry, FIND)) != NULL)
        return *( (long long *) found_entry->data);

    long long total=0;
    for(int i=0;i<(int)strlen(output)-1;i++)
        total += resolve_dirs(output[i], 
        output[i+1],
        recursion_depth - 1
    );

    strcpy(cache[c], key);
    counts[c] = total;
    entry.key = cache[c];
    entry.data = &counts[c];
    if(hsearch(entry, ENTER) == NULL)
        fprintf(stderr, "hsearch ENTER failed for \"%s\"\n", cache[c]);
    c++;

    return total;
}

void init_mappings() {
    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            num_pos[(int)nums[j][i]][0] = i;
            num_pos[(int)nums[j][i]][1] = j;
        }
        for(int j=0;j<2;j++){
            dir_pos[(int)dirs[j][i]][0] = i;
            dir_pos[(int)dirs[j][i]][1] = j;
        }
    }
}

int main(int argc, char* argv[]) {
    FILE* fin = fopen(FILENAME, "r");
    init_mappings();
    
    hcreate(MAX_OUTPUT_SIZE);
    char buff[MAPPING_SIZE], input[MAX_OUTPUT_SIZE];
    long long result = 0, d;

    while(fscanf(fin,"%s", buff) == 1){
        sscanf(buff, "%lld", &d);
        resolve_numerical(buff, input);
        long long len=0;
        for(int i=0; i< (int)strlen(input) - 1; i++)
            len += resolve_dirs(input[i],input[i+1], ROBOTS_NUMBER);

        result += d*len;
    }

    fclose(fin);
    hdestroy();

    printf("%d\n", result);

    return 0;
}