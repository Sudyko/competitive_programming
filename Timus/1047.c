#include <stdio.h>
#include <stdlib.h>

int main(){
    int N;
    scanf("%d", &N);
    float* c = (float*)malloc(N * sizeof(float));
    float a0, an, sum = 0;
    scanf("%f%f", &a0, &an);
    int n = N + 1;
    for (int i = 0; i < N; i++) {
        scanf("%f", &c[i]);
        sum += ((N - i) << 1)*c[i];
    }
    float a1 = (an + a0*N - sum)/n;
    printf("%.2f", a1);
    free(c);
    return 0;
}