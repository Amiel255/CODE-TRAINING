#include <stdio.h>
int main() {

    int tv = 400;
    int vcr = 220;
    float control = 35.20;
    int cd = 300; 
    int tape = 150;

    float tv1, vcr1, control1, cd1, tape1;
    printf("ENTER HOW MANY TV YOU PURCHASED; ");
    scanf("%f", &tv1);

    printf("ENTER HOW MANY VCR YOU PURCHASED; ");
    scanf("%f", &vcr1);

    printf("ENTER HOW MANY REMOTE CONTROL YOU PURCHASED; ");
    scanf("%f", &control1);

    printf("ENTER HOW MANY CD PLAYER YOU PURCHASED; ");
    scanf("%f", &cd1);

    printf("ENTER HOW MANY TAPE RECORDER YOU PURCHASED; ");
    scanf("%f", &tape1);
    
    float totalt = tv1 * tv;
    float totalv = vcr1 * vcr;
    float totalc = control1 * control;
    float totalcd = cd1 * cd;
    float totalta = tape1 * tape;

    float subtotal = totalt + totalv + totalc + totalcd + totalta;
    float aftertax = subtotal * 0.0825;
    float total = subtotal * 1.0825;

    printf("QTY     DESCRIPTION     UNIT PRICE      TOTAL PRICE\n");
    printf("---------------------------------------------------\n");
    printf("%.0f    TV              %d              %.2f       \n", tv1, tv, totalt);
    printf("%.0f    VCR             %d              %.2f       \n", vcr1, vcr, totalv);
    printf("%.0f    REMOTE CTRLR    %f              %.2f       \n", control1, control, totalc);
    printf("%.0f    CD PLAYER       %d              %.2f       \n", cd1, cd, totalcd);
    printf("%.0f    TAPE RECORDER   %d              %.2f       \n", tape1, tape, totalta);
    printf("                        SUBTOTAL        %.2f       \n", subtotal);
    printf("                        TAX             %.2f       \n", aftertax);
    printf("                        TOTAL           %.2f       \n", total);





    system("pause");
    return 0;
}