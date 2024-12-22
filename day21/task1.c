#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void resolve_numerical(char* input, char* output){
    int x = num_pos['A'][0];
    int y = num_pos['A'][1];
    int i=0;

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

void resolve_directional(char* input, char* output){
    int x=dir_pos['A'][0];
    int y=dir_pos['A'][1];
    int i=0;

    while(*input){
        int new_x=dir_pos[(int)*input][0], new_y=dir_pos[(int)*input][1];
        while(new_x > x){ output[i++]='>'; x++;}
        while(new_y > y){ output[i++]='v'; y++;}
        while(new_y < y){ output[i++]='^'; y--;}
        while(new_x < x){ output[i++]='<'; x--;}
        output[i++]='A';
        input++;
    }
    output[i]='\0';
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
    
    char buff[MAPPING_SIZE], input[MAX_OUTPUT_SIZE], output[MAX_OUTPUT_SIZE];
    int result=0, d;
    while(fscanf(result, "%s", buff) == 1){
        sscanf(buff, "%d", &d);
        resolve_numerical(buff, input);
        for(int i=0;i<ROBOTS_NUMBER;i++){
            resolve_directional(input, output);
            strcpy(input,output);
        }

        result += d * strlen(output);
    }

    fclose(result);

    printf("%d\n", result);

    return 0;
}