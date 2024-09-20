#include <stdio.h>


int main () {

char str[80];
int i;

printf("Name >> ");
scanf("%s",str);
printf("Age >> ");
scanf("%d",&i);
printf("Hello %s (%d)",str,i);

return 0;
}