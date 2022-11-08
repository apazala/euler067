#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define MAXLEN 32768

int64_t buf1[2000];
int64_t buf2[2000];
char line[MAXLEN];

int main()
{
    char *endptr;
    FILE* fp;
    int64_t *curr_row = buf1;
    int64_t *prev_row = buf2;
    int64_t *swap_aux;

    fp = fopen("data.txt", "r");
    if(!fp){
        fprintf(stderr, "Can't open data file\n");
        return 1;
    }

    int linecounter = 0;
    while(fgets(line, MAXLEN, fp)){
        linecounter++;
        
        //Read line
        endptr = line;
        for(int i = 0; i < linecounter; i++){
            curr_row[i] = strtol(endptr, &endptr, 10);
        }


        curr_row[0]+=prev_row[0];
        curr_row[linecounter-1]+=prev_row[linecounter-2];
        int lim = linecounter-1;
        for(int i = 1; i < lim; i++){
            curr_row[i]+= (prev_row[i]>prev_row[i-1]?prev_row[i]:prev_row[i-1]);
        }

        swap_aux = curr_row;
        curr_row = prev_row;
        prev_row = swap_aux;
    }

    fclose(fp);

    int64_t max_path = prev_row[0];
    for(int i = 1; i < linecounter; i++){
        if(prev_row[i]>max_path){
            max_path = prev_row[i];
        }
    }

    printf("%" PRId64 "\n", max_path);

    return 0;
}