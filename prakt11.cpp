#include <stdio.h>  
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <termios.h>

static struct termios oldt;

void restore_terminal_settings(void)
{
tcsetattr(0, TCSANOW, &oldt); /* Apply saved settings */
}

void disable_waiting_for_enter(void)
{
struct termios newt;

/* Make terminal read 1 char at a time */
tcgetattr(0, &oldt); /* Save terminal settings */
newt = oldt; /* Init new settings */
newt.c_lflag &= ~(ICANON | ECHO); /* Change settings */
tcsetattr(0, TCSANOW, &newt); /* Apply settings */
atexit(restore_terminal_settings); /* Make sure settings will be restored when program ends */
}

void clean_stdin(void)
{
int p;
do {
p = getchar();
} while (p != '\n' && p != EOF);
}

void makeSpiral1(int num1, int num2, bool &count1, bool &count2, bool &countfailure, int result[20][20]){
            int g = 1;
            int z = 0;
            bool finish = false;
            if (count1 == false || count2 == false) countfailure = true;
            else {
                while(g <= (num1 * num2)){
            for (int i = 0+z; i < num1-z; i++)
            {
                if (finish == false)
                result[i][0+z] = g;
                if(g == num1*num2) {finish = true; break;}
                g++;
            }
            for (int j = 1+z; j < num2-z; j++)
            {
                if (finish == false)
                result[num1-1-z][j] = g;
                if(g == num1*num2) {finish = true; break;}
                g++;
            }
            for(int f = num1-2-z; f > -1+z; f--)
            {
                if (finish == false)
                result[f][num2-1-z] = g;
                if(g == num1*num2) {finish = true; break;}
                g++;
            }
            for(int v = num2-1-z; v > 1+z; v--)
            {
                if (finish == false)
                result[0+z][v-1] = g;
                if(g == num1*num2) {finish = true; break;}
                g++;
            }
            if (finish == true) break;
            else z++;
                }
            }
}

void changeLine(int num1, int num2, int result[20][20])
{
    int res2[20];    
    for(int i = 0; i < num2; i++)
    {
        int l = 0;
        for(int j = num1-1; j > -1; j--, l++)
        {
            res2[l] = result[j][i];
        }
        l = 0;
        for(int k = 0; k < num1; k++, l++)
        {
            result[k][i] = res2[l];
        }
    }
}

int main()
{
    int pos = 1, num1 = 0, num2 = 0, a = 0, i = 0, g = 1, z = 0, counter = 0;
    char check;
    bool r = false, count1 = false, count2 = false, inputfailure = false, start = true, overf = false, countfailure = false, finish = false, toolow = false;
    int result[20][20];
    while(1){
    if (inputfailure == true) printf("Введен неправильный символ, число образано до последнего знака перед неверным символом\n\n");
    if (overf == true) printf("Максимальное число - 20. Любое число больше 20 принимается за 20.\n\n");
    if (countfailure == true) printf("Для начала введите значения обеих переменных\n\n");
    if (toolow == true) printf("Спираль не может быть нарисована, т.к. размеры столбцов и строк не равны\n\n");
    toolow = false;
    if (pos == 1) printf("1. Ввод первого числа <--\n"); else printf("1. Ввод первого числа\n");
    if (pos == 2) printf("2. Ввод второго числа <--\n"); else printf("2. Ввод второго числа\n");
    if (pos == 3) printf("3. Спираль номер 1 (Снаружи по часовой) <--\n"); else printf("3. Спираль номер 1 (Снаружи по часовой) \n");
    if (pos == 4) printf("4. Спираль номер 2 (Снаружи против часовой)  <--\n"); else printf("4. Спираль номер 2 (Снаружи против часовой) \n");
    if (pos == 5) printf("5. Спираль номер 3 (Изнутри против часовой) <--\n"); else printf("5. Спираль номер 3 (Изнутри против часовой)\n");
    if (pos == 6) printf("6. Спираль номер 4 (Изнутри по часовой) <--\n"); else printf("6. Спираль номер 4 (Изнутри по часовой)\n");
    if (pos == 7) printf("7. Вывод последней сохраненной спирали <--\n"); else printf("7. Вывод последней сохраненной спирали\n");
    if (pos == 8) printf("8. Выход из программы <--\n"); else printf("8. Выход из программы\n");
    printf ("\nЧисло 1 = %d Число 2 = %d\n\n", num1, num2);
    printf("Для спиарлей 3 и 4 число столбцов и строк должно быть равно\n\n");
    if(pos != 7) printf ("Выберите пункт меню нажатием стрелочек вверх-вниз или нажатием соответствующей цифры\n");
    if(pos == 8) break;
    countfailure = false;
    disable_waiting_for_enter();
    a = getchar();
    restore_terminal_settings();
    if (a == 27) 
    {
        system("clear");
        if (getchar() == '[')
        check = getchar();
        switch(check)
        {
            case 'A':
            if (pos != 1) pos--;
            else printf("Невозможно сместить стрелочку в указанном направлении\n\n");
            break;
            case 'B':
            if (pos != 9) pos++;
            else printf("Невозможно сместить стрелочку в указанном направлении\n\n");
            break;
        }
    }
    else {
        system("clear");
        switch(a)
        {
            case 49: pos = 1; break;
            case 50: pos = 2; break;
            case 51: pos = 3; break;
            case 52: pos = 4; break;
            case 53: pos = 5; break;
            case 54: pos = 6; break;
            case 55: pos = 7; break;
            case 56: pos = 8; break;
            case 10: break;
            default: printf("Input failure\n\n"); start = false; break;
        }
        
    }
    
    if(start == true){
        overf = false;
        inputfailure = false;
        if (pos == 1){
            printf("Введите число 1\n\n");
            num1 = 0;        
            while(1)        
            {
                inputfailure = false;
                char c = '\0';
                scanf("%c", &c);
                if (c < '0' || c > '9')                 
                {
                    if (c != '\n') {inputfailure = true; clean_stdin(); break;} 
                    else {count1 = true; break;} 
                }
                if (num1*10+c-'0' > 20) {overf = true; r = true; num1 = 20; count1 = true; clean_stdin(); break;}
                else r = false;
                if(r == false)
                num1 = num1*10+c-'0';        
            }  
            system("clear");
        }
        
        if (pos == 2){ 
            printf("Введите число 2\n\n");
            num2 = 0;        
            while(1)        
            {
                inputfailure = false;
                char c = '\0';
                scanf("%c", &c);
                if (c < '0' || c > '9')                 
                {
                    if (c != '\n') {inputfailure = true; clean_stdin(); break;} 
                    else {count2 = true; break;} 
                }
                if (num2*10+c-'0' > 20) {overf = true; r = true; num2 = 20; count2 = true; clean_stdin(); break;}
                else r = false;
                if(r == false)
                num2 = num2*10+c-'0';        
            }  
            system("clear");
        }

        if(pos == 3){
            makeSpiral1(num1, num2, count1, count2, countfailure, result);
            if(!countfailure)
            {
            system("clear");
            for(int j = 0; j < num2; j++)
            {
            for(int i = 0; i < num1; i++)
            {
            if(result[i][j] < 10) printf("  %d ", result[i][j]);
            else{
            if(result[i][j] < 100) printf(" %d ", result[i][j]);
            else printf("%d ", result[i][j]);
            }
            }
            printf("\n");
            }
            printf("Нажмите t для сохранения спирали в текстовом формате\n");
            disable_waiting_for_enter();
            char ift = getchar();
            restore_terminal_settings();
            if(ift == 116)
            {
                FILE* in;
                in = fopen("spiral.txt", "wb");
                if(!in) printf("Ошибка при открытии файла\n");
                else 
                {
                    int ifwritten = 0;
                    fwrite(&num1, sizeof(num1), 1, in);
                    fwrite(&num2, sizeof(num2), 1, in);
                    ifwritten = fwrite(result, sizeof(int), sizeof(result), in);
                    if(!ifwritten) printf("Ошибка при записи\n");
                    else printf("Успешно\n");
                    fclose(in);
                }
            }
            getchar();
            printf("\n\n");    
            }  
        }  

        } 

        if(pos == 4){
            makeSpiral1(num1, num2, count1, count2, countfailure, result);
            changeLine(num1, num2, result);
            if(!countfailure)
            {
                system("clear");
                for(int j = 0; j < num2; j++)
                {
                for(int i = 0; i < num1; i++)
                {
                if(result[i][j] < 10) printf("  %d ", result[i][j]);
                else{
                if(result[i][j] < 100) printf(" %d ", result[i][j]);
                else printf("%d ", result[i][j]);
                }
                }
                printf("\n");
                }
                printf("\n\n");  
            }        
        } 

        if(pos == 5){
            if (count1 == false || count2 == false) countfailure = true;
            else {
            if (num1 != num2) toolow = true;
            else{
            int cx = 0, cy = 0;
            if (num1 % 2 == 0) cx = (num1/2)-1; else cx = (num1/2);
            if (num2 % 2 == 0) cy = (num2/2)-1; else cy = (num2/2);
            g = 1;
            result[cx][cy] = g;
            g++;
            z = 0;
            counter = 0;
            finish = false;            
                while(g <= (num1 * num2)){
            for (i = 0; i < 1+z; i++)
            {
                if (finish == false)
                result[cx-counter][cy+1+i-counter] = g;
                if(g == num1*num2) {finish = true; break;}
                g++;
            }
            for (int j = 0; j < 1+z; j++)
            {
                if (finish == false)
                result[cx+1-counter+j][cy+1+counter] = g;
                if(g == num1*num2) {finish = true; break;}
                g++;
            }
            for(int f = 0; f < 2+z; f++)
            {
                if (finish == false)
                result[cx+1+counter][cy-f+z-counter] = g;
                if (g == 17) 
                r = false;
                if(g == num1*num2) {finish = true; break;}
                g++;
            }
            for(int v = 0; v < 2+z; v++)
            {
                if (finish == false)
                result[cx-v+counter][cy-1-counter] = g;
                if(g == num1*num2) {finish = true; break;}
                g++;
            }
            if (finish == true) break;
            else {z+=2; counter++;}
                }
            for(int j = 0; j < num2; j++)
            {
            for(int i = 0; i < num1; i++)
            {
            if(result[i][j] < 10) printf("  %d ", result[i][j]);
            else{
            if(result[i][j] < 100) printf(" %d ", result[i][j]);
            else printf("%d ", result[i][j]);
            }
            }
            printf("\n");   
            }
            printf("\n\n");
            }
            }
    }

        if(pos == 6){
            if (count1 == false || count2 == false) countfailure = true;
            else {
            if (num1 != num2) toolow = true;
            else{
            int cx = 0, cy = 0;
            if (num1 % 2 == 0) cx = (num1/2)-1; else cx = (num1/2);
            if (num2 % 2 == 0) cy = (num2/2)-1; else cy = (num2/2);
            g = 1;
            result[cx][cy] = g;
            g++;
            z = 0;
            counter = 0;
            finish = false;            
                while(g <= (num1 * num2)){
            for (i = 0; i < 1+z; i++)
            {
                if (finish == false)
                result[cx+1+i-counter][cy-counter] = g;
                if(g == num1*num2) {finish = true; break;}
                g++;
            }
            for (int j = 0; j < 1+z; j++)
            {
                if (finish == false)
                result[cx+1+counter][cy+1+j-counter] = g;
                if(g == num1*num2) {finish = true; break;}
                g++;
            }
            for(int f = 0; f < 2+z; f++)
            {
                if (finish == false)
                result[cx+counter-f][cy+1+counter] = g;
                if (g == 17) 
                r = false;
                if(g == num1*num2) {finish = true; break;}
                g++;
            }
            for(int v = 0; v < 2+z; v++)
            {
                if (finish == false)
                result[cx-1-counter][cy+counter-v] = g;
                if(g == num1*num2) {finish = true; break;}
                g++;
            }
            if (finish == true) break;
            else {z+=2; counter++;}
                }
            for(int j = 0; j < num2; j++)
            {
            for(int i = 0; i < num1; i++)
            {
            if(result[i][j] < 10) printf("  %d ", result[i][j]);
            else{
            if(result[i][j] < 100) printf(" %d ", result[i][j]);
            else printf("%d ", result[i][j]);
            }
            }
            printf("\n");   
            }
            printf("\n\n");
            }
            }
        }
        if (pos == 7)
        {
            FILE* out;
                out = fopen("spiral.txt", "rb");
                if(!out) printf("Ошибка при открытии файла\n");
                else 
                {
                    int ifwritten = 0, sizex = 0, sizey = 0;
                    fread(&sizex, sizeof(sizex), 1, out);
                    fread(&sizey, sizeof(sizey), 1, out);
                    ifwritten = fread(result, sizeof(int), sizeof(result), out);
                    if(!ifwritten) printf("Ошибка при чтении\n");
                    else {
                        printf("Успешно\n");
                        for(int j = 0; j < sizey; j++)
                        {
                        for(int i = 0; i < sizex; i++)
                        {
                        if(result[i][j] < 10) printf("  %d ", result[i][j]);
                        else{
                        if(result[i][j] < 100) printf(" %d ", result[i][j]);
                        else printf("%d ", result[i][j]);
                        }
                        }
                        printf("\n");   
                        }
                        fclose(out);
                    }                    
                }            
        }
    }
    return 0;
}
