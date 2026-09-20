#include <stdio.h>

int main()
{
    char vowels, choice;

    do
    {   
        printf("Enter an alphabet: ");
        scanf(" %c", &vowels); 

        switch (vowels)
        {
        case 'a': case 'e': case 'i': case 'o': case 'u':
        case 'A': case 'E': case 'I': case 'O': case 'U':
            printf("%c is a vowel.\n", vowels);
            break;
        default:
            if ((vowels >= 'a' && vowels <= 'z') || (vowels >= 'A' && vowels <= 'Z'))
            {
                printf("%c is a consonant\n", vowels);
            }
            else
            {
                printf("TRY AGAIN!\n");
            }
        }

        printf("DO YOU WANT TO TRY AGAIN? (y/n): ");
        scanf(" %c", &choice);
    
    } while (choice == 'y' || choice == 'Y');
    
    printf("THANKYOU FOR USING THIS!\n");
    system("pause");
    return 0;
}