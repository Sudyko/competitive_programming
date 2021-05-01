#include <stdio.h>

int main() {
    char str[51] = { 0 };
    int letters[27] = { 0 }, maxi = 0, i = 0;
    scanf("%s", str);
    while (str[i]) { 
        ++letters[str[i] - 97];
        if (letters[str[i] - 97] > letters[maxi]) maxi = str[i] - 97;
        ++i;
    }
    printf("%c", (char)maxi + 'a');
    return 0;
}