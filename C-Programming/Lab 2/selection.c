/* A program to illustrate if and switch statements.
 * Richard Lobb, July  2015.
 */

 #include <stdio.h>

 int main(void)
 {
     int value = 0;
     printf("What's the pip-value of your playing card? ");
     scanf("%d", &value);
     if (value < 1 || value > 13) {
         puts("No such card.");
     } else if (value == 1) {
         puts("It's an ace.");
     } else if (value < 11) {
         puts("It's a boring number card.");
     } else {
         printf("It's a face card. Specifically a ");
         switch (value) {
            case 11:
                puts("Jack. ");
                break;
            case 12:
                puts("Queen.");
                break;
            case 13:
                puts("King.");
        }
    }
}

