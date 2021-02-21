#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char str[10000];
    int n, k, index, jumps, max_jumps = -1, max;
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= k; ++i){
        memset(str, 0, 10000);
        jumps = 0;
        for(int j = 0; j < n; ++j){
            scanf("%d", &index);
            str[index - 1] = 1;
            for(int k = index; k < n; ++k)
				jumps += str[k];
        }
        if (jumps > max_jumps){
            max = i;
            max_jumps = jumps;
        }
    }
    printf("%d", max);
    return 0;
}