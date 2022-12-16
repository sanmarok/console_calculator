#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>
#include <windows.h>

#define ESC 27
#define ENTER 13
#define RETROCESO 8


/*Variables globales*/

    //Define la estructura de cada nodo de la lista
        struct stack{
            char expression [50];
            struct stack *next;
        };

    //Almacena la direccion del ultimo stack ingresado
        struct stack *lastInputStack;
    //Almacena la cadena que se muestra en la consola
        char consoleView [50];
    //Almacena la cantidad de stacks que hay almacenados
        int counterStacks = 0;
    //Registra que tecla se presiono
        char pressedKey = 0;
    //Almacena la posicion del cursor
        int positionCursor = 0;
    //Almacena la posicion del stack seleccionado
        int selectedStack = 0;
    //Lleva el control del ultimo elemento a mostrar
        int lastStack = 10;
    //Array auxiliar para calcular expresiones
        char transformedExpression[400];

/*Prototipado de funciones*/

        /*Imprime el esquema de la calculadora*/
            void printCalculator();

        /*Imprime los stacks en funcion de las variables de control*/
            void printStacks();

        /*Editor de consola*/
            void consoleEditor();

        /*Si la expresion es correcta se agrega el stack y limpia la consola*/
            int addStack(char *consoleView);

        /*Borra el stack seleccionado*/
            void deleteSelectedStack();

        /*Cambia el contenido de la expresion con el que esta arriba.*/
            void swapStacks();

        /*Maximiza la pantalla simulando que se presiono ALT ENTER*/
            void fullScreen();

        /*Cambia el contenido de la expresion del stack seleccionado con el el primer stack*/
            void swapStacksToFirtsPosition();

        /*Elimina todos los stacks*/
            void deleteAllStacks();

        /*Verifica si la expresion es correcta*/
            int checkExpression(char *expression);

        /*Calcula expresiones simples del formato entre '' y un solo signo*/
            double calculateSimpleExpressions(char *expression);

        /*Reemplaza los signos "-" por "-1*" y lo almacena en transformedExpression*/
            void expressionsTransformer (char *expression);

        /*Utiliza las funcion expressionsTransformer para luego resolver las operaciones en el orden correspondiente con calculateSimpleExpressions*/
            double calculateExpressions (char *expression);
/*Desarrollo de funcioness*/

        /*Imprime el esquema de la calculadora*/
            void printCalculator(){
            /*Imprime las lineas dependiendo si son pares o no segun corresponda*/
                _setcursortype(_NOCURSOR);
                gotoxy(1,1);
                for(int index = 1; index < 24; index++){
                    if(index%2 != 0){
                        for (int indexa=0; indexa<50; indexa++){
                            printf("_");
                        }
                        printf("\n");
                    }else{
                        printf("|");
                        gotoxy(51,index);
                        printf("|\n");
                    }
                }
                printf("\n|     1     |     2     |     3     | + | DROP[F] |\n");

                for (int indexa=0; indexa<50; indexa++){
                    printf("_");
                }
                printf("\n|     4     |     5     |     6     | - | [S]WAP  |\n");

                for (int indexa=0; indexa<50; indexa++){
                    printf("_");
                }
                printf("\n|     7     |     8     |     9     | * | DEL[P]  |\n");

                for (int indexa=0; indexa<50; indexa++){
                    printf("_");
                }
                printf("\n|     ;     |     0     |    EXE    | / | [N]UM   |\n");

                for (int indexa=0; indexa<50; indexa++){
                    printf("_");
                }
                printf("\n|     '     | ARRIBA [W]| ABAJO [S] |   | SWAP1[Q]|\n");
                for (int indexa=0; indexa<50; indexa++){
                    printf("_");
                }
                gotoxy(1,35);
                printf("|");
                gotoxy(51,35);
                printf("|");
                gotoxy(1,36);
                for (int indexa=0; indexa<50; indexa++){
                    printf("_");
                }

                gotoxy(80-20,1);
                printf("\t\t\t\t\t\t");
                textbackground(WHITE);
                textcolor(BLACK);
                printf("INSTRUCCIONES");
                textbackground(BLACK);
                textcolor(WHITE);
                gotoxy(80-20,3);
                printf("\t\t\t\t\t\t OPERACIONES");
                gotoxy(80-20,5);
                textbackground(CYAN);
                textcolor(CYAN);
                printf("  ");
                textbackground(BLACK);
                textcolor(WHITE);
                printf(" Una expresion es validad cuando se encuentra entre '' ademas debe tener una redaccion correcta");
                gotoxy(80-20,7);
                printf("\t\tEjemplo: ");
                textcolor(GREEN);
                printf("'2+3*(5.133-1E2/(-3.5+25))'");
                textcolor(WHITE);

                gotoxy(80-20,9);
                textbackground(CYAN);
                textcolor(CYAN);
                printf("  ");
                textbackground(BLACK);
                textcolor(WHITE);
                printf(" Las operaciones basicas \" + \" , \" - \" , \" * \" y \" / \" operan con el stack 1 y 2");

                gotoxy(80-20,11);
                textbackground(CYAN);
                textcolor(CYAN);
                printf("  ");
                textbackground(BLACK);
                textcolor(WHITE);
                printf(" Las operaciones basicas \" + \" , \" - \" , \" * \" y \" / \" pueden operar con el stack 1 y una expresion");
                gotoxy(80-20,13);
                printf("\t\tEjemplo: ");
                textcolor(GREEN);
                printf("10+STACK1 ; 10-STACK1 ; 10*STACK1 ; 10/STACK1");
                textcolor(WHITE);
                gotoxy(80-20,15);
                printf("\t\t\t\t\t\t    TECLAS");
                gotoxy(121-15,17);
                printf("SUBIR STACK");
                gotoxy(125-15,19);
                textbackground(5);
                textcolor(WHITE);
                printf(" W ");
                textbackground(BLACK);
                textcolor(WHITE);
                gotoxy(125-15,21);
                textbackground(5);
                textcolor(WHITE);
                printf(" S ");
                textbackground(BLACK);
                textcolor(WHITE);
                gotoxy(120-15,21);
                textbackground(10);
                textcolor(WHITE);
                printf(" A ");
                textbackground(BLACK);
                textcolor(WHITE);
                gotoxy(102-15,21);
                printf("CURSOR IZQUIERDA");
                gotoxy(130-15,21);
                textbackground(10);
                textcolor(WHITE);
                printf(" D ");
                textbackground(BLACK);
                textcolor(WHITE);
                gotoxy(135-15,21);
                printf("CURSOR DERECHA");
                gotoxy(121-15,23);
                printf("BAJAR STACK");
                gotoxy(80-15,27);
                textbackground(RED);
                textcolor(WHITE);
                printf(" P ");
                textbackground(BLACK);
                textcolor(WHITE);
                printf(" BORRAR TODOS LOS STACKS");
                gotoxy(115-20,27);
                textbackground(RED);
                textcolor(WHITE);
                printf(" F ");
                textbackground(BLACK);
                textcolor(WHITE);
                printf(" BORRAR STACK SELECCIONADO");
                gotoxy(150-20,27);
                textbackground(RED);
                textcolor(WHITE);
                printf(" ENTER ");
                textbackground(BLACK);
                textcolor(WHITE);
                printf(" GUARDAR EXPRESION");

                gotoxy(80-15,29);
                textbackground(RED);
                textcolor(WHITE);
                printf(" N ");
                textbackground(BLACK);
                textcolor(WHITE);
                printf(" CALCULAR EXPRESION");
                gotoxy(115-20,29);
                textbackground(RED);
                textcolor(WHITE);
                printf(" Q ");
                textbackground(BLACK);
                textcolor(WHITE);
                printf(" SWAP AL STACK 1");
                gotoxy(150-20,29);
                textbackground(RED);
                textcolor(WHITE);
                printf(" Z ");
                textbackground(BLACK);
                textcolor(WHITE);
                printf(" SWAP AL STACK N+1");

            }

        /*Imprime los stacks en funcion de las variables de control*/
            void printStacks(){
                int indexPrint = 0;
                for(int index = 0; index < 10; index++){
                    indexPrint+=2;
                    _setcursortype(_NOCURSOR);
                    gotoxy(2,indexPrint);
                    clreol();
                    gotoxy(51,indexPrint);
                    printf("|");
                    //Posiciona el cursor al principio del stack correspondiente
                        gotoxy(2,indexPrint);
                        printf("%d:\t",lastStack-index);
                }
                if(counterStacks > 0){
                    struct stack *indexStack = lastInputStack;
                    indexPrint = 22;
                    for(int index = 0; index <counterStacks; index++){
                        if( index >= (lastStack - 10) && index < lastStack){
                            indexPrint-=2;
                            if(index +1 == selectedStack){
                                textcolor(BLACK);
                                textbackground(YELLOW);
                                if(strlen((indexStack->expression))>15){
                                    gotoxy(32,indexPrint);
                                    for(int indexa = 0; indexa < 15; indexa++){
                                        printf("%c",indexStack->expression[indexa]);
                                    }
                                   printf("...");
                                }else{
                                    gotoxy((50-strlen(indexStack->expression)),indexPrint);
                                    printf("%s",indexStack->expression);
                                }
                                textcolor(WHITE);
                                textbackground(BLACK);
                            }else{
                                if(strlen((indexStack->expression))>15){
                                    gotoxy(32,indexPrint);
                                    for(int indexa = 0; indexa < 15; indexa++){
                                        printf("%c",indexStack->expression[indexa]);
                                    }
                                   printf("...");
                                }else{
                                    gotoxy((50-strlen(indexStack->expression)),indexPrint);
                                    printf("%s",indexStack->expression);
                                }

                            }
                        }
                        indexStack = indexStack->next;
                    }
                }
                /*Simula que el focus siempre esta en la consola*/
                    _setcursortype(_NORMALCURSOR);
                    gotoxy((50-positionCursor),22);
            }

        /*Imprime lo en la posicion de la consola lo que se este escribiendo*/
            void consoleEditor(){
                if(strlen(consoleView) < 48){
                    _setcursortype(_NOCURSOR);
                    gotoxy(2,22);
                    clreol();
                    gotoxy(51,22);
                    printf("|");
                    gotoxy((50-(strlen(consoleView))),22);
                    printf("%s",consoleView);
                    gotoxy((50-positionCursor),22);
                    _setcursortype(_NORMALCURSOR);

                    switch(pressedKey){
                        case 'd':
                            {
                                if (positionCursor > 0){
                                    positionCursor--;
                                }else{
                                    positionCursor = 0;
                                }
                                gotoxy((50-positionCursor),22);
                                break;
                            }
                        case 'D':
                            {
                                if (positionCursor > 0){
                                    positionCursor--;
                                }else{
                                    positionCursor = 0;
                                }
                                gotoxy((50-positionCursor),22);
                                break;
                            }
                        case 'a':
                            {
                                if(positionCursor >= strlen(consoleView)){
                                    positionCursor = strlen(consoleView);
                                }else{
                                    positionCursor++;
                                }
                                gotoxy((50-positionCursor),22);
                                break;
                            }
                        case 'A':
                            {
                                if(positionCursor >= strlen(consoleView)){
                                    positionCursor = strlen(consoleView);
                                }else{
                                    positionCursor++;
                                }
                                gotoxy((50-positionCursor),22);
                                break;
                            }
                        case RETROCESO:
                            {
                                if (positionCursor >= 0){
                                    for(int index = (strlen(consoleView) - positionCursor - 1); index <(strlen(consoleView)); index++){
                                        consoleView[index] = consoleView[index+1];
                                    }
                                }else{
                                    positionCursor = 0;
                                    gotoxy((50-positionCursor),22);
                                }
                                    _setcursortype(_NOCURSOR);
                                    gotoxy(2,22);
                                    clreol();
                                    gotoxy(51,22);
                                    printf("|");
                                    gotoxy((50-(strlen(consoleView))),22);
                                    printf("%s",consoleView);
                                    gotoxy((50-positionCursor),22);
                                break;
                            }
                        default:
                            {
                                if (strlen(consoleView) < 48){
                                    for(int index = strlen(consoleView); index > (strlen(consoleView) - positionCursor - 1); index--){
                                        consoleView[index+1] = consoleView[index];
                                    }
                                    consoleView[(strlen(consoleView) - positionCursor)] = pressedKey;
                                    consoleView[(strlen(consoleView))+1] = '\0';
                                    gotoxy((50-(strlen(consoleView))),22);
                                    if(strlen(consoleView) < 48){
                                        gotoxy((50-(strlen(consoleView))),22);
                                        printf("%s",consoleView);
                                        gotoxy((50-positionCursor),22);
                                    }else{
                                        gotoxy((50-(strlen(consoleView))),22);
                                        printf("%s",consoleView);
                                        gotoxy((50-positionCursor),22);
                                    }
                                }
                                break;
                            }
                    }
                }else{
                /*Cambia a modo insercion*/
                    _setcursortype(_NOCURSOR);
                    gotoxy(2,22);
                    clreol();
                    gotoxy(51,22);
                    printf("|");
                    gotoxy((50-(strlen(consoleView))),22);
                    printf("%s",consoleView);
                    gotoxy((50-positionCursor),22);
                    _setcursortype(_NORMALCURSOR);

                    switch(pressedKey){
                        case 'D':
                            {
                                if (positionCursor >= 1){
                                    positionCursor--;
                                }else{
                                    positionCursor = 1;
                                }
                                gotoxy((50-positionCursor),22);
                                break;
                            }
                        case 'A':
                            {
                                if(positionCursor == strlen(consoleView)){
                                    positionCursor = strlen(consoleView);
                                }else{
                                    positionCursor++;
                                }
                                gotoxy((50-positionCursor),22);
                                break;
                            }
                        case RETROCESO:
                            {
                                if (positionCursor >= 0){
                                    for(int index = (strlen(consoleView) - positionCursor - 1); index <(strlen(consoleView)); index++){
                                        consoleView[index] = consoleView[index+1];
                                    }
                                }else{
                                    positionCursor = 0;
                                    gotoxy((50-positionCursor),22);
                                }
                                    _setcursortype(_NOCURSOR);
                                    gotoxy(2,22);
                                    clreol();
                                    gotoxy(51,22);
                                    printf("|");
                                    gotoxy((50-(strlen(consoleView))),22);
                                    printf("%s",consoleView);
                                    gotoxy((50-positionCursor),22);
                                break;
                            }
                        default:
                            {
                                if (strlen(consoleView) == 48){
                                    consoleView[(strlen(consoleView) - positionCursor)] = pressedKey;
                                    consoleView[48] = '\0';
                                    gotoxy((50-(strlen(consoleView))),22);
                                    if(strlen(consoleView) == 48){
                                        gotoxy((50-(strlen(consoleView))),22);
                                        printf("%s",consoleView);
                                        gotoxy((50-positionCursor),22);
                                    }
                                }
                                break;
                            }
                    }
                }
            }

        /*Si la expresion es correcta se agrega el stack y limpia la consola*/
            int addStack(char *consoleView){
            //Variable auxiliar para crear stacks
                struct stack *newStack;
                if(counterStacks == 0){
                    newStack = (struct stack*)malloc(sizeof(struct stack));
                    if (newStack == NULL){
                        /*Informa donde esta el error*/
                           {
                                _setcursortype(_NOCURSOR);
                                textcolor(RED);
                                gotoxy(2,35);
                                printf("ERROR: ");
                                textcolor(WHITE);
                                printf("NO SE PUDO GUARDAR");
                                delay(500);
                                gotoxy(2,35);
                                clreol();
                                gotoxy(51,35);
                                printf("|");
                                gotoxy((50-(strlen(consoleView))),22);
                                printf("%s",consoleView);
                                gotoxy((50-positionCursor),22);
                                _setcursortype(_NORMALCURSOR);
                           }
                           return 0;
                    }else{
                        strcpy(newStack->expression,consoleView);
                        newStack->next = NULL;
                        lastInputStack = newStack;
                        counterStacks++;
                        for(int index = 0; index < 50; index++){
                            consoleView[index] = '\0';
                        }
                        positionCursor = 0;
                        {
                            _setcursortype(_NOCURSOR);
                            gotoxy(2,22);
                            clreol();
                            gotoxy(51,22);
                            printf("|");
                            gotoxy((50-(strlen(consoleView))),22);
                            printf("%s",consoleView);
                            gotoxy((50-positionCursor),22);
                            _setcursortype(_NORMALCURSOR);
                        }
                        return 1;
                    }
                }else{
                    newStack = (struct stack*)malloc(sizeof(struct stack));
                    if (newStack == NULL){
                        /*Informa donde esta el error*/
                           {
                                _setcursortype(_NOCURSOR);
                                textcolor(RED);
                                gotoxy(2,35);
                                printf("ERROR: ");
                                textcolor(WHITE);
                                printf("NO SE PUDO GUARDAR");
                                delay(500);
                                gotoxy(2,35);
                                clreol();
                                gotoxy(51,35);
                                printf("|");
                                gotoxy((50-(strlen(consoleView))),22);
                                printf("%s",consoleView);
                                gotoxy((50-positionCursor),22);
                                _setcursortype(_NORMALCURSOR);
                           }
                           return 0;
                    }else{
                        strcpy(newStack->expression,consoleView);
                        newStack->next = lastInputStack;
                        lastInputStack = newStack;
                        counterStacks++;
                        for(int index = 0; index < 50; index++){
                            consoleView[index] = '\0';
                        }
                        positionCursor = 0;
                        {
                            _setcursortype(_NOCURSOR);
                            gotoxy(2,22);
                            clreol();
                            gotoxy(51,22);
                            printf("|");
                            gotoxy((50-(strlen(consoleView))),22);
                            printf("%s",consoleView);
                            gotoxy((50-positionCursor),22);
                            _setcursortype(_NORMALCURSOR);
                        }
                        return 1;
                    }
                }
            }

        /*Borra el stack seleccionado*/
            void deleteSelectedStack(){
                if(counterStacks > 0 && selectedStack > 0){
                    struct stack *targetedStack = lastInputStack;
                    struct stack *previousTargetedStack = lastInputStack;

                    for(int index = 0; index < selectedStack - 1; index++){
                        previousTargetedStack = targetedStack;
                        targetedStack = targetedStack->next;
                    }

                    if(targetedStack!= NULL){
                        previousTargetedStack->next = targetedStack->next;

                        if(targetedStack == lastInputStack){
                            lastInputStack = targetedStack->next;
                        }

                        free(targetedStack);
                        counterStacks--;
                        if(counterStacks == 0){
                            selectedStack = 0;
                        }else{
                            selectedStack--;
                            lastStack--;
                            if(selectedStack < 1){
                                selectedStack = 1;
                            }

                            if (lastStack <=10){
                                lastStack = 10;
                            }
                        }
                    }
                }else{
                    return;
                }
            }


        /*Cambia el stack seleccionado con el que esta arriba.*/
            void swapStacks(){

                if(counterStacks > 1 && selectedStack > 0){
                    struct stack *previousTargetedStack = lastInputStack;
                    struct stack *targetedStack = lastInputStack;
                    struct stack *saveDirection;
                    for(int index = 0; index < selectedStack - 1; index++){
                        previousTargetedStack = targetedStack;
                        targetedStack = targetedStack->next;
                    }

                    if(targetedStack == lastInputStack){
                        saveDirection = targetedStack->next;
                        targetedStack->next = (targetedStack->next)->next;
                        saveDirection->next = targetedStack;
                        lastInputStack = saveDirection;
                    }else{
                        if(targetedStack != NULL && (targetedStack->next) != NULL){
                            (previousTargetedStack->next) = targetedStack->next;
                            saveDirection = (targetedStack->next)->next;
                            (targetedStack->next)->next = targetedStack;
                            (targetedStack->next) = saveDirection;
                        }
                    }


                        selectedStack++;

                        if(selectedStack <= counterStacks){
                            if(selectedStack > lastStack){
                                lastStack++;
                            }
                        }else{
                            selectedStack = counterStacks;
                            lastStack = counterStacks;
                            if(lastStack<10){
                                lastStack = 10;
                            }
                        }
                    }else{
                        return;
                    }

            }

        /*Maximiza la pantalla simulando que se presiono ALT ENTER*/
            void fullScreen(){
            keybd_event(VK_MENU,0x38,0,0);
            keybd_event(VK_RETURN,0x1c,0,0);
            keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
            keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
            return;
        }

        /*Cambia el contenido de la expresion del stack seleccionado con el el primer stack*/
            void swapStacksToFirtsPosition(){
                if(counterStacks > 1 && selectedStack > 1){
                    struct stack *previousTargetedStack = lastInputStack;
                    struct stack *targetedStack = lastInputStack;
                    struct stack *saveDirection;
                    for(int index = 0; index < selectedStack - 1; index++){
                        previousTargetedStack = targetedStack;
                        targetedStack = targetedStack->next;
                    }
                    if(targetedStack != NULL){
                        previousTargetedStack->next = lastInputStack;
                        saveDirection = targetedStack->next;
                        targetedStack->next = lastInputStack->next;
                        lastInputStack->next = saveDirection;

                        lastInputStack = targetedStack;
                    }else{
                        return;
                    }
                }else{
                    return;
                }
            }

        /*Elimina todos los stacks*/
            void deleteAllStacks(){
                struct stack *indexStack = lastInputStack;
                struct stack *targetedStack;
                while(indexStack != NULL){
                    targetedStack = indexStack;
                    free(targetedStack);
                    indexStack = indexStack->next;
                }
                counterStacks = 0;
                selectedStack = 0;
                lastStack = 10;

            }

        /*Verifica si la expresion es correcta*/
            int checkExpression(char *expression){
                int counterSingleQuotes = 0;
                int counterOpenParenthesis = 0;
                int counterCloseParenthesis = 0;
                int closeParenthesis;
                int openParenthesis;

                if(expression[0] == '\'' && expression[strlen(expression)-1] == '\'' && strlen(expression) > 2){
                    for(int index = 0; index < strlen(expression); index++){
                        if(expression[index] == '('){
                            counterOpenParenthesis++;
                            closeParenthesis = 0;
                            for (int indexa = index; indexa < strlen(expression); indexa++){
                                if(expression[indexa] == ')'){
                                    closeParenthesis++;
                                    break;
                                }
                            }
                            if(closeParenthesis == 0){
                                return 0;
                            }
                            if((expression[index-1] != '+' && expression[index-1] != '-' && expression[index-1] != '*' && expression[index-1] != '/' && expression[index-1] != 'e'&& expression[index-1] != 'E' && expression[index-1] != '\'' && expression[index-1] != '(')|| expression[index - 1] == ')' || expression[index - 1] == '.'){
                              /*Informa donde esta el error*/
                                   {
                                        _setcursortype(_NOCURSOR);
                                        textcolor(RED);
                                        gotoxy(2,35);
                                        printf("ERROR: ");
                                        textcolor(WHITE);
                                        printf("...");
                                        textcolor(RED);
                                        printf("%c%c",expression[index-1],expression[index]);
                                        textcolor(WHITE);
                                        printf("...");
                                        delay(500);
                                        gotoxy(2,35);
                                        clreol();
                                        gotoxy(51,35);
                                        printf("|");
                                        gotoxy((50-(strlen(consoleView))),22);
                                        printf("%s",consoleView);
                                        gotoxy((50-positionCursor),22);
                                        _setcursortype(_NORMALCURSOR);
                                   }
                                return 0;
                            }
                            if(expression[index+1] == '+' || expression[index+1] == '*' || expression[index+1] == '/' || expression[index+1] == 'e'|| expression[index+1] == 'E' || expression[index+1] == ')' || expression[index+1] == '\''
                            || expression[index+1] == '.'){
                              /*Informa donde esta el error*/
                                   {
                                        _setcursortype(_NOCURSOR);
                                        textcolor(RED);
                                        gotoxy(2,35);
                                        printf("ERROR: ");
                                        textcolor(WHITE);
                                        printf("...");
                                        textcolor(RED);
                                        printf("%c%c",expression[index],expression[index+1]);
                                        textcolor(WHITE);
                                        printf("...");
                                        delay(500);
                                        gotoxy(2,35);
                                        clreol();
                                        gotoxy(51,35);
                                        printf("|");
                                        gotoxy((50-(strlen(consoleView))),22);
                                        printf("%s",consoleView);
                                        gotoxy((50-positionCursor),22);
                                        _setcursortype(_NORMALCURSOR);
                                   }
                                return 0;
                            }
                        }

                        if(expression[index] == ')'){
                            counterCloseParenthesis++;
                            openParenthesis = 0;
                            for (int indexa = index; indexa > 0; indexa--){
                                if(expression[indexa] == '('){
                                    openParenthesis++;
                                    break;
                                }
                            }
                            if(openParenthesis == 0){
                                return 0;
                            }
                            if(expression[index-1] == '+' || expression[index-1] == '-' || expression[index-1] == '*' || expression[index-1] == '/' || expression[index-1] == 'e'|| expression[index-1] == 'E' || expression[index-1] == '\''
                                || expression[index - 1] == '(' || expression[index - 1] == '.'){
                                /*Informa donde esta el error*/
                                   {
                                        _setcursortype(_NOCURSOR);
                                        textcolor(RED);
                                        gotoxy(2,35);
                                        printf("ERROR: ");
                                        textcolor(WHITE);
                                        printf("...");
                                        textcolor(RED);
                                        printf("%c%c",expression[index-1],expression[index]);
                                        textcolor(WHITE);
                                        printf("...");
                                        delay(500);
                                        gotoxy(2,35);
                                        clreol();
                                        gotoxy(51,35);
                                        printf("|");
                                        gotoxy((50-(strlen(consoleView))),22);
                                        printf("%s",consoleView);
                                        gotoxy((50-positionCursor),22);
                                        _setcursortype(_NORMALCURSOR);
                                   }
                                return 0;
                            }
                            if((expression[index+1] != '+' && expression[index+1] != '-' && expression[index+1] != '*' && expression[index+1] != '/' && expression[index+1] != 'e' && expression[index+1] != 'E' && expression[index+1] != '\'' && expression[index+1] != ')')|| expression[index+1] == '.'){
                                /*Informa donde esta el error*/
                                   {
                                        _setcursortype(_NOCURSOR);
                                        textcolor(RED);
                                        gotoxy(2,35);
                                        printf("ERROR: ");
                                        textcolor(WHITE);
                                        printf("...");
                                        textcolor(RED);
                                        printf("%c%c",expression[index],expression[index+1]);
                                        textcolor(WHITE);
                                        printf("...");
                                        delay(500);
                                        gotoxy(2,35);
                                        clreol();
                                        gotoxy(51,35);
                                        printf("|");
                                        gotoxy((50-(strlen(consoleView))),22);
                                        printf("%s",consoleView);
                                        gotoxy((50-positionCursor),22);
                                        _setcursortype(_NORMALCURSOR);
                                   }
                                return 0;
                            }
                        }

                        if(expression[index] == '+'){
                            if(expression[index-1] == '+' || expression[index-1] == '*' || expression[index-1] == '/' || expression[index-1] == '\'' || expression[index - 1] == '('
                              || expression[index-1] == '.'||expression[index-1] == '-'){
                               /*Informa donde esta el error*/
                                    {
                                        _setcursortype(_NOCURSOR);
                                        textcolor(RED);
                                        gotoxy(2,35);
                                        printf("ERROR: ");
                                        textcolor(WHITE);
                                        printf("...");
                                        textcolor(RED);
                                        printf("%c%c",expression[index-1],expression[index]);
                                        textcolor(WHITE);
                                        printf("...");
                                        delay(500);
                                        gotoxy(2,35);
                                        clreol();
                                        gotoxy(51,35);
                                        printf("|");
                                        gotoxy((50-(strlen(consoleView))),22);
                                        printf("%s",consoleView);
                                        gotoxy((50-positionCursor),22);
                                        _setcursortype(_NORMALCURSOR);
                                   }
                                return 0;
                            }
                            if(expression[index+1] == '+' || expression[index+1] == '*' || expression[index+1] == '/' || expression[index+1] == 'e'|| expression[index+1] == 'E' || expression[index+1] == '\'' || expression[index + 1] == ')'
                            || expression[index+1] == '.'){
                                /*Informa donde esta el error*/
                                   {
                                        _setcursortype(_NOCURSOR);
                                        textcolor(RED);
                                        gotoxy(2,35);
                                        printf("ERROR: ");
                                        textcolor(WHITE);
                                        printf("...");
                                        textcolor(RED);
                                        printf("%c%c",expression[index],expression[index+1]);
                                        textcolor(WHITE);
                                        printf("...");
                                        delay(500);
                                        gotoxy(2,35);
                                        clreol();
                                        gotoxy(51,35);
                                        printf("|");
                                        gotoxy((50-(strlen(consoleView))),22);
                                        printf("%s",consoleView);
                                        gotoxy((50-positionCursor),22);
                                        _setcursortype(_NORMALCURSOR);
                                   }
                                return 0;
                            }
                        }
                        if(expression[index] == '*'){
                            if(expression[index-1] == '+' || expression[index-1] == '*' || expression[index-1] == '/' || expression[index-1] == 'e'|| expression[index-1] == 'E' || expression[index-1] == '\'' || expression[index - 1] == '('
                            || expression[index-1] == '.' ||expression[index-1] == '-'){
                                /*Informa donde esta el error*/
                                   {
                                        _setcursortype(_NOCURSOR);
                                        textcolor(RED);
                                        gotoxy(2,35);
                                        printf("ERROR: ");
                                        textcolor(WHITE);
                                        printf("...");
                                        textcolor(RED);
                                        printf("%c%c",expression[index-1],expression[index]);
                                        textcolor(WHITE);
                                        printf("...");
                                        delay(500);
                                        gotoxy(2,35);
                                        clreol();
                                        gotoxy(51,35);
                                        printf("|");
                                        gotoxy((50-(strlen(consoleView))),22);
                                        printf("%s",consoleView);
                                        gotoxy((50-positionCursor),22);
                                        _setcursortype(_NORMALCURSOR);
                                   }
                                return 0;
                            }
                            if(expression[index+1] == '+' || expression[index+1] == '*' || expression[index+1] == '/' || expression[index+1] == 'e'|| expression[index+1] == 'E' || expression[index+1] == '\'' || expression[index + 1] == ')'
                            || expression[index+1] == '.'){
                                /*Informa donde esta el error*/
                                   {
                                        _setcursortype(_NOCURSOR);
                                        textcolor(RED);
                                        gotoxy(2,35);
                                        printf("ERROR: ");
                                        textcolor(WHITE);
                                        printf("...");
                                        textcolor(RED);
                                        printf("%c%c",expression[index],expression[index+1]);
                                        textcolor(WHITE);
                                        printf("...");
                                        delay(500);
                                        gotoxy(2,35);
                                        clreol();
                                        gotoxy(51,35);
                                        printf("|");
                                        gotoxy((50-(strlen(consoleView))),22);
                                        printf("%s",consoleView);
                                        gotoxy((50-positionCursor),22);
                                        _setcursortype(_NORMALCURSOR);
                                   }
                                return 0;
                            }
                        }
                        if(expression[index] == '/'){
                            if(expression[index-1] == '+' || expression[index-1] == '*' || expression[index-1] == '/' || expression[index-1] == 'e'|| expression[index-1] == 'E' || expression[index-1] == '\'' || expression[index - 1] == '('
                            || expression[index-1] == '.' ||expression[index-1] == '-'){
                                /*Informa donde esta el error*/
                                   {
                                        _setcursortype(_NOCURSOR);
                                        textcolor(RED);
                                        gotoxy(2,35);
                                        printf("ERROR: ");
                                        textcolor(WHITE);
                                        printf("...");
                                        textcolor(RED);
                                        printf("%c%c",expression[index-1],expression[index]);
                                        textcolor(WHITE);
                                        printf("...");
                                        delay(500);
                                        gotoxy(2,35);
                                        clreol();
                                        gotoxy(51,35);
                                        printf("|");
                                        gotoxy((50-(strlen(consoleView))),22);
                                        printf("%s",consoleView);
                                        gotoxy((50-positionCursor),22);
                                        _setcursortype(_NORMALCURSOR);
                                   }
                                return 0;
                            }
                            if(expression[index+1] == '+' || expression[index+1] == '*' || expression[index+1] == '/' || expression[index+1] == 'e'|| expression[index+1] == 'E' || expression[index+1] == '\'' || expression[index + 1] == ')'
                            || expression[index+1] == '.'){
                                /*Informa donde esta el error*/
                                   {
                                        _setcursortype(_NOCURSOR);
                                        textcolor(RED);
                                        gotoxy(2,35);
                                        printf("ERROR: ");
                                        textcolor(WHITE);
                                        printf("...");
                                        textcolor(RED);
                                        printf("%c%c",expression[index],expression[index+1]);
                                        textcolor(WHITE);
                                        printf("...");
                                        delay(500);
                                        gotoxy(2,35);
                                        clreol();
                                        gotoxy(51,35);
                                        printf("|");
                                        gotoxy((50-(strlen(consoleView))),22);
                                        printf("%s",consoleView);
                                        gotoxy((50-positionCursor),22);
                                        _setcursortype(_NORMALCURSOR);
                                   }
                                return 0;
                            }
                        }
                        if(expression[index] == '-'){
                            if(expression [index - 1] == '.'){
                                /*Informa donde esta el error*/
                                   {
                                        _setcursortype(_NOCURSOR);
                                        textcolor(RED);
                                        gotoxy(2,35);
                                        printf("ERROR: ");
                                        textcolor(WHITE);
                                        printf("...");
                                        textcolor(RED);
                                        printf("%c%c",expression[index-1],expression[index]);
                                        textcolor(WHITE);
                                        printf("...");
                                        delay(500);
                                        gotoxy(2,35);
                                        clreol();
                                        gotoxy(51,35);
                                        printf("|");
                                        gotoxy((50-(strlen(consoleView))),22);
                                        printf("%s",consoleView);
                                        gotoxy((50-positionCursor),22);
                                        _setcursortype(_NORMALCURSOR);
                                   }
                                return 0;
                            }
                            if(expression[index+1] == '+' || expression[index+1] == '*' || expression[index+1] == '/' || expression[index+1] == 'e'|| expression[index+1] == 'E' || expression[index+1] == '\'' || expression[index + 1] == ')'
                            || expression[index+1] == '.'){
                                /*Informa donde esta el error*/
                                   {
                                        _setcursortype(_NOCURSOR);
                                        textcolor(RED);
                                        gotoxy(2,35);
                                        printf("ERROR: ");
                                        textcolor(WHITE);
                                        printf("...");
                                        textcolor(RED);
                                        printf("%c%c",expression[index],expression[index+1]);
                                        textcolor(WHITE);
                                        printf("...");
                                        delay(500);
                                        gotoxy(2,35);
                                        clreol();
                                        gotoxy(51,35);
                                        printf("|");
                                        gotoxy((50-(strlen(consoleView))),22);
                                        printf("%s",consoleView);
                                        gotoxy((50-positionCursor),22);
                                        _setcursortype(_NORMALCURSOR);
                                   }
                                return 0;
                            }
                        }

                        if(expression[index] == 'E'){
                            if(expression[index-1] == '+' || expression[index-1] == '*' || expression[index-1] == '/' || expression[index-1] == 'e'|| expression[index-1] == 'E' || expression[index-1] == '\'' || expression[index - 1] == '('
                            || expression[index-1] == '.' ||expression[index-1] == '-'){
                                /*Informa donde esta el error*/
                                   {
                                        _setcursortype(_NOCURSOR);
                                        textcolor(RED);
                                        gotoxy(2,35);
                                        printf("ERROR: ");
                                        textcolor(WHITE);
                                        printf("...");
                                        textcolor(RED);
                                        printf("%c%c",expression[index-1],expression[index]);
                                        textcolor(WHITE);
                                        printf("...");
                                        delay(500);
                                        gotoxy(2,35);
                                        clreol();
                                        gotoxy(51,35);
                                        printf("|");
                                        gotoxy((50-(strlen(consoleView))),22);
                                        printf("%s",consoleView);
                                        gotoxy((50-positionCursor),22);
                                        _setcursortype(_NORMALCURSOR);
                                   }
                                return 0;
                            }
                            if(expression[index+1] == '*' || expression[index+1] == '/' || expression[index+1] == 'e'|| expression[index+1] == 'E' || expression[index+1] == '\'' || expression[index + 1] == ')'
                            || expression[index+1] == '.' || (expression[index +1] == '-' && expression[index+2] == '-')){
                                /*Informa donde esta el error*/
                                   {
                                        _setcursortype(_NOCURSOR);
                                        textcolor(RED);
                                        gotoxy(2,35);
                                        printf("ERROR: ");
                                        textcolor(WHITE);
                                        printf("...");
                                        textcolor(RED);
                                        printf("%c%c",expression[index],expression[index+1]);
                                        textcolor(WHITE);
                                        printf("...");
                                        delay(500);
                                        gotoxy(2,35);
                                        clreol();
                                        gotoxy(51,35);
                                        printf("|");
                                        gotoxy((50-(strlen(consoleView))),22);
                                        printf("%s",consoleView);
                                        gotoxy((50-positionCursor),22);
                                        _setcursortype(_NORMALCURSOR);
                                   }
                                return 0;
                            }
                        }

                        if(expression[index] == '\''){
                            counterSingleQuotes++;
                            if(counterSingleQuotes > 2){
                                /*Informa donde esta el error*/
                                   {
                                        _setcursortype(_NOCURSOR);
                                        textcolor(RED);
                                        gotoxy(2,35);
                                        printf("ERROR: ");
                                        textcolor(WHITE);
                                        printf("DEMASIADAS COMILLAS");
                                        delay(500);
                                        gotoxy(2,35);
                                        clreol();
                                        gotoxy(51,35);
                                        printf("|");
                                        gotoxy((50-(strlen(consoleView))),22);
                                        printf("%s",consoleView);
                                        gotoxy((50-positionCursor),22);
                                        _setcursortype(_NORMALCURSOR);
                                   }
                                return 0;
                            }
                        }
                    }

                    if (counterCloseParenthesis != counterOpenParenthesis){
                        /*Informa donde esta el error*/
                           {
                                _setcursortype(_NOCURSOR);
                                textcolor(RED);
                                gotoxy(2,35);
                                printf("ERROR: ");
                                textcolor(WHITE);
                                printf("PARENTESIS INCOMPLETOS");
                                delay(500);
                                gotoxy(2,35);
                                clreol();
                                gotoxy(51,35);
                                printf("|");
                                gotoxy((50-(strlen(consoleView))),22);
                                printf("%s",consoleView);
                                gotoxy((50-positionCursor),22);
                                _setcursortype(_NORMALCURSOR);
                           }
                           return 0;
                    }

                    return 1;
            }else{
                /*Informa donde esta el error*/
                   {
                        _setcursortype(_NOCURSOR);
                        textcolor(RED);
                        gotoxy(2,35);
                        printf("ERROR: ");
                        textcolor(WHITE);
                        printf("EXPRESION INVALIDA");
                        delay(500);
                        gotoxy(2,35);
                        clreol();
                        gotoxy(51,35);
                        printf("|");
                        gotoxy((50-(strlen(consoleView))),22);
                        printf("%s",consoleView);
                        gotoxy((50-positionCursor),22);
                        _setcursortype(_NORMALCURSOR);
                   }
                   return 0;
            }
        }

        /*Calcula expresiones simples del formato entre '' y un solo signo*/
            double calculateSimpleExpressions(char *expression){

                double storagedNumbers [50];
                char storagedOperators [50];

                int indexStoragedNumbers = 0;
                int indexStoragedOperators = 0;
                int indexa = 0;
                int counterOperators = 0;
                int counterPriorityOperators = 0;
                int counterNumbers = 0;
                char auxiliarString[50];

                double auxiliarResult;

                /*Almacena los numeros y los operadores en sus correspondientes array*/
                    for(int index = 1; index < strlen(expression); index++){
                        auxiliarString[indexa] = expression[index];
                        if( expression[index]== '+' || expression[index]== '-' ||expression[index]== '*' || expression[index]== '/' || expression[index]== '\''){
                            if(expression[index] == '-' && (expression[index - 1]== '+' || expression[index - 1]== '-' ||expression[index - 1]== '*' || expression[index - 1]== '/' || expression[index - 1]== '\''
                                || expression[index - 1]== 'E')){
                                indexa++;
                            }else{
                                if(expression[index] == '+' && expression[index - 1] == 'E'){
                                    indexa++;
                                }else{
                                    auxiliarString[indexa]='\0';
                                    storagedNumbers[indexStoragedNumbers] = strtod(auxiliarString,NULL);
                                    for(int indexa = 0; indexa<50; indexa++){
                                        auxiliarString[indexa] = '\0';
                                    }
                                    indexa = 0;
                                    indexStoragedNumbers++;
                                    counterNumbers++;
                                    if( expression[index]== '+' || expression[index]== '-' ||expression[index]== '*' || expression[index]== '/'){
                                        storagedOperators[indexStoragedOperators] = expression[index];
                                        indexStoragedOperators++;
                                        counterOperators++;
                                    }
                                }
                            }
                        }else{
                            indexa++;
                        }

                    }

                for(int index = 0; index < counterOperators; index++){
                    if(storagedOperators[index] == '*' || storagedOperators[index] == '/'){
                        counterPriorityOperators++;
                    }
                }

                while(counterPriorityOperators != 0){
                    for (int index = 0; index < counterOperators; index++){
                        if(storagedOperators[index] == '*' || storagedOperators[index] == '/' ){
                            switch (storagedOperators[index]){
                                case '*':
                                    {
                                        auxiliarResult = storagedNumbers[index] * storagedNumbers[index+1];

                                        for (int indexa = index; indexa < counterOperators; indexa++){
                                            storagedOperators[indexa] = storagedOperators[indexa + 1];
                                        }

                                        storagedNumbers[index] = auxiliarResult;

                                        for (int indexa = index+1; indexa < counterNumbers; indexa++){
                                            storagedNumbers[indexa] = storagedNumbers[indexa + 1];
                                        }
                                        counterNumbers--;
                                        counterOperators--;
                                        counterPriorityOperators--;
                                        break;
                                    }
                                case '/':
                                    {
                                        if(storagedNumbers[index+1] == 0){
                                        /*Informa donde esta el error*/
                                           {
                                                _setcursortype(_NOCURSOR);
                                                textcolor(RED);
                                                gotoxy(2,35);
                                                printf("ERROR: ");
                                                textcolor(WHITE);
                                                printf("DIVISION POR 0");
                                                delay(500);
                                                gotoxy(2,35);
                                                clreol();
                                                gotoxy(51,35);
                                                printf("|");
                                                gotoxy((50-(strlen(consoleView))),22);
                                                printf("%s",consoleView);
                                                gotoxy((50-positionCursor),22);
                                                _setcursortype(_NORMALCURSOR);
                                           }
                                            return;
                                        }else{
                                            auxiliarResult = storagedNumbers[index] / storagedNumbers[index+1];
                                        }


                                        for (int indexa = index; indexa < counterOperators; indexa++){
                                            storagedOperators[indexa] = storagedOperators[indexa + 1];
                                        }

                                        storagedNumbers[index] = auxiliarResult;

                                        for (int indexa = index+1; indexa < counterNumbers; indexa++){
                                            storagedNumbers[indexa] = storagedNumbers[indexa + 1];
                                        }
                                        counterNumbers--;
                                        counterOperators--;
                                        counterPriorityOperators--;
                                        break;
                                    }
                            }
                            break;
                        }
                    }
                }

                while(counterOperators != 0){
                    for (int index = 0; index < counterOperators; index++){
                        if(storagedOperators[index] == '+' || storagedOperators[index] == '-' ){
                            switch (storagedOperators[index]){
                                case '+':
                                    {
                                        auxiliarResult = storagedNumbers[index] + storagedNumbers[index+1];

                                        for (int indexa = index; indexa < counterOperators; indexa++){
                                            storagedOperators[indexa] = storagedOperators[indexa + 1];
                                        }

                                        storagedNumbers[index] = auxiliarResult;

                                        for (int indexa = index+1; indexa < counterNumbers; indexa++){
                                            storagedNumbers[indexa] = storagedNumbers[indexa + 1];
                                        }
                                        counterNumbers--;
                                        counterOperators--;
                                        break;
                                    }
                                case '-':
                                    {
                                        auxiliarResult = storagedNumbers[index] - storagedNumbers[index+1];

                                        for (int indexa = index; indexa < counterOperators; indexa++){
                                            storagedOperators[indexa] = storagedOperators[indexa + 1];
                                        }

                                        storagedNumbers[index] = auxiliarResult;

                                        for (int indexa = index+1; indexa < counterNumbers; indexa++){
                                            storagedNumbers[indexa] = storagedNumbers[indexa + 1];
                                        }
                                        counterNumbers--;
                                        counterOperators--;

                                        break;
                                    }
                            }
                            break;
                        }
                    }
                }


                return storagedNumbers[0];
            }

        /*Reemplaza los signos "-" por "-1*" y lo almacena en transformedExpression*/
            void expressionsTransformer (char *expression){

                int indexTransformedExpression = 0;

                for(int  index = 0; index <strlen(expression); index++){
                    if(expression[index] == '-' && expression[index-1]!= 'E'){
                        transformedExpression[indexTransformedExpression] = '-';
                        indexTransformedExpression++;
                        transformedExpression[indexTransformedExpression] = '1';
                        indexTransformedExpression++;
                        transformedExpression[indexTransformedExpression] = '*';
                        indexTransformedExpression++;
                    }else{
                            transformedExpression[indexTransformedExpression] = expression[index];
                            indexTransformedExpression++;
                        }
                }
                transformedExpression[indexTransformedExpression+1]='\0';

            }

        /*Utiliza las funcion expressionsTransformer para luego resolver las operaciones en el orden correspondiente con calculateSimpleExpressions*/
            double calculateExpressions (char *expression){

                int counterParenthesis = 0;
                int lastOpenParenthesis;
                int firtsCloseParenthesis;
                int indexAuxiliarExpression;
                int auxiliarClose;
                int indexlastPartTransformedExpression;

                expressionsTransformer(expression);

                for(int index = 0; index<strlen(transformedExpression);index++){
                    if(transformedExpression[index] == '('){
                            counterParenthesis++;
                    }
                }

                while(counterParenthesis > 0){

                    indexAuxiliarExpression = 1;
                    char auxiliarExpression [400];
                    char lastPartTransformedExpression [400];

                    for(int index = 0; index<strlen(transformedExpression);index++){
                        if(transformedExpression[index] == '('){
                                lastOpenParenthesis = index;
                        }
                    }

                    auxiliarExpression[0] = '\'';
                    for(int index = lastOpenParenthesis+1; transformedExpression[index] != ')'; index++){
                        auxiliarExpression[indexAuxiliarExpression] = transformedExpression[index];
                        indexAuxiliarExpression++;
                    }
                    firtsCloseParenthesis = indexAuxiliarExpression+lastOpenParenthesis;

                    auxiliarExpression[indexAuxiliarExpression] = '\'';
                    auxiliarExpression[indexAuxiliarExpression+1] = '\0';

                    sprintf(auxiliarExpression, "%f", calculateSimpleExpressions(auxiliarExpression));

                    indexlastPartTransformedExpression = 0;

                    for(int index = firtsCloseParenthesis+1; index <strlen(transformedExpression); index++){
                        lastPartTransformedExpression[indexlastPartTransformedExpression] = transformedExpression[index];
                        indexlastPartTransformedExpression++;
                    }
                    lastPartTransformedExpression[indexlastPartTransformedExpression]='\0';
                    indexAuxiliarExpression = 0;

                    for(int index = lastOpenParenthesis; index<(lastOpenParenthesis + strlen(auxiliarExpression)); index++){
                        transformedExpression[index] = auxiliarExpression[indexAuxiliarExpression];
                        indexAuxiliarExpression++;
                        firtsCloseParenthesis = index;
                    }

                    indexlastPartTransformedExpression = 0;

                    for(int index = firtsCloseParenthesis; index <(firtsCloseParenthesis + strlen(lastPartTransformedExpression)); index++){
                        transformedExpression[index] = lastPartTransformedExpression[indexlastPartTransformedExpression];
                        indexlastPartTransformedExpression++;
                        auxiliarClose = index;
                    }
                    transformedExpression[auxiliarClose+1]= '\0';
                    counterParenthesis--;

                }
                return calculateSimpleExpressions(transformedExpression);
            }

        /*Verifica si es una expresion o un numero*/
            int isanumberoraexpression (char *consoleView){
                if(consoleView[0] == '\''){
                    return 0;
                }else{
                    return 1;
                }
            }
int main()
{

    /*Se imprime por primera vez la calculadora*/
        fullScreen();
        printCalculator();
        printStacks();

    while (pressedKey != ESC){

        pressedKey = getch();

        pressedKey = toupper(pressedKey);

        switch (pressedKey){
            case 'N':
                {
                    if(checkExpression(consoleView)==1){
                        char stringResult [50];
                        sprintf(stringResult,"%G",calculateExpressions(consoleView));
                        char *numberError;
                        strtod(stringResult,&numberError);
                        if(strlen(numberError)==0){
                            addStack(stringResult);
                            for(int index = 0; index < 50; index++){
                                consoleView[index] = '\0';
                            }
                            positionCursor = 0;
                            _setcursortype(_NOCURSOR);
                            gotoxy(2,22);
                            clreol();
                            gotoxy(51,22);
                            printf("|");
                            gotoxy((50-(strlen(consoleView))),22);
                            printf("%s",consoleView);
                            gotoxy((50-positionCursor),22);
                            _setcursortype(_NORMALCURSOR);
                            printStacks();
                            break;
                        }else{
                            {
                                _setcursortype(_NOCURSOR);
                                textcolor(RED);
                                gotoxy(2,35);
                                printf("ERROR: ");
                                textcolor(WHITE);
                                printf("EN EL RESULTADO");
                                delay(500);
                                gotoxy(2,35);
                                clreol();
                                gotoxy(51,35);
                                printf("|");
                                gotoxy((50-(strlen(consoleView))),22);
                                printf("%s",consoleView);
                                gotoxy((50-positionCursor),22);
                                _setcursortype(_NORMALCURSOR);
                           }
                           break;
                        }

                    }else{
                        /*Informa donde esta el error*/
                           {
                                _setcursortype(_NOCURSOR);
                                textcolor(RED);
                                gotoxy(2,35);
                                printf("ERROR: ");
                                textcolor(WHITE);
                                printf("EN LA EXPRESION");
                                delay(500);
                                gotoxy(2,35);
                                clreol();
                                gotoxy(51,35);
                                printf("|");
                                gotoxy((50-(strlen(consoleView))),22);
                                printf("%s",consoleView);
                                gotoxy((50-positionCursor),22);
                                _setcursortype(_NORMALCURSOR);
                           }
                           break;
                    }
                }

            case 'P':
                {
                    if(counterStacks > 0){
                        deleteAllStacks();
                        printStacks();
                    }
                    break;
                }

            case 'Q':
                {
                    if(counterStacks > 1){
                        swapStacksToFirtsPosition();
                        printStacks();
                    }
                    break;
                }

            case 'Z':
                {
                    if(counterStacks > 1){
                        swapStacks();
                        printStacks();
                    }

                    break;
                }

            case 'F':
                {
                    if(counterStacks > 0){
                        deleteSelectedStack();
                        printStacks();
                    }
                    break;
                }

            case ENTER:
                {
                    if(isanumberoraexpression(consoleView)== 0){
                        if(checkExpression(consoleView)==1){
                            if(addStack(consoleView)==1){
                                selectedStack++;
                                printStacks();
                                break;
                            }else{
                                break;
                            }
                        }else{
                            /*Informa donde esta el error*/
                               {
                                    _setcursortype(_NOCURSOR);
                                    textcolor(RED);
                                    gotoxy(2,35);
                                    printf("ERROR: ");
                                    textcolor(WHITE);
                                    printf("EXPRESION INVALIDA");
                                    delay(500);
                                    gotoxy(2,35);
                                    clreol();
                                    gotoxy(51,35);
                                    printf("|");
                                    gotoxy((50-(strlen(consoleView))),22);
                                    printf("%s",consoleView);
                                    gotoxy((50-positionCursor),22);
                                    _setcursortype(_NORMALCURSOR);
                                   break;
                               }
                               break;
                        }
                    }else{
                    //Almacena el resultado del calculo
                        float result;
                        char *numberError = NULL;
                        result = strtod(consoleView,&numberError);
                        if(strlen(numberError)==0){
                            sprintf(consoleView,"%G",result);
                            addStack(consoleView);
                            selectedStack++;
                            printStacks();
                            _setcursortype(_NOCURSOR);
                            gotoxy(2,22);
                            clreol();
                            gotoxy(51,22);
                            printf("|");
                            gotoxy((50-(strlen(consoleView))),22);
                            printf("%s",consoleView);
                            gotoxy((50-positionCursor),22);
                            _setcursortype(_NORMALCURSOR);
                            break;
                        }else{
                            _setcursortype(_NOCURSOR);
                            textcolor(RED);
                            gotoxy(2,35);
                            printf("ERROR: ");
                            textcolor(WHITE);
                            printf("%s",numberError);
                            delay(500);
                            gotoxy(2,35);
                            clreol();
                            gotoxy(51,35);
                            printf("|");
                            gotoxy((50-(strlen(consoleView))),22);
                            printf("%s",consoleView);
                            gotoxy((50-positionCursor),22);
                            _setcursortype(_NORMALCURSOR);
                           break;
                        }
                    }
                }

            case 'W':
                {
                    selectedStack++;

                    if(selectedStack <= counterStacks){
                        if(selectedStack > lastStack){
                            lastStack++;
                        }
                    }else{
                        selectedStack = counterStacks;
                        lastStack = counterStacks;
                        if(lastStack<10){
                            lastStack = 10;
                        }
                    }

                    printStacks();
                    break;
                }

            case 'S':
                {
                    selectedStack--;
                    if(selectedStack < 1){
                        selectedStack = 1;
                    }
                    if(!(lastStack > selectedStack && selectedStack > (lastStack -10))){
                        lastStack --;
                        if(lastStack < 10){
                            lastStack = 10;
                        }
                    }
                    printStacks();
                    break;
                }

            case 'A':
                {
                    consoleEditor();
                    break;
                }

            case 'D':
                {
                    consoleEditor();
                    break;
                }

            case '0':
                {
                    consoleEditor();
                    break;
                }

            case '1':
                {
                    consoleEditor();
                    break;
                }

            case '2':
                {
                    consoleEditor();
                    break;
                }

            case '3':
                {
                    consoleEditor();
                    break;
                }

            case '4':
                {
                    consoleEditor();
                    break;
                }

            case '5':
                {
                    consoleEditor();
                    break;
                }

            case '6':
                {
                    consoleEditor();
                    break;
                }

            case '7':
                {
                    consoleEditor();
                    break;
                }

            case '8':
                {
                    consoleEditor();
                    break;
                }

            case '9':
                {
                    consoleEditor();
                    break;
                }

            case '+':
                {
                    if(counterStacks >= 2 && strlen(consoleView)==0){
                        if(isanumberoraexpression(lastInputStack->expression)== 1){
                            if(isanumberoraexpression((lastInputStack->next)->expression)== 1){
                                float result;
                                result = (strtod((lastInputStack->next)->expression, NULL) + strtod(lastInputStack->expression, NULL));
                                sprintf(lastInputStack->expression,"%G",result);
                                int saveSelectStack = selectedStack;
                                selectedStack = 2;
                                deleteSelectedStack();
                                selectedStack = saveSelectStack - 1;
                                if(selectedStack <= 0){
                                    selectedStack = 1;
                                }
                                printStacks();
                                break;
                            }else{
                                _setcursortype(_NOCURSOR);
                                textcolor(RED);
                                gotoxy(2,35);
                                printf("ERROR: ");
                                textcolor(WHITE);
                                printf("STACK 2 ES UNA EXPRESION ");
                                delay(500);
                                gotoxy(2,35);
                                clreol();
                                gotoxy(51,35);
                                printf("|");
                                gotoxy((50-(strlen(consoleView))),22);
                                printf("%s",consoleView);
                                gotoxy((50-positionCursor),22);
                                _setcursortype(_NORMALCURSOR);
                               break;
                            }
                        }else{
                            {
                                _setcursortype(_NOCURSOR);
                                textcolor(RED);
                                gotoxy(2,35);
                                printf("ERROR: ");
                                textcolor(WHITE);
                                printf("STACK 1 ES UNA EXPRESION ");
                                delay(500);
                                gotoxy(2,35);
                                clreol();
                                gotoxy(51,35);
                                printf("|");
                                gotoxy((50-(strlen(consoleView))),22);
                                printf("%s",consoleView);
                                gotoxy((50-positionCursor),22);
                                _setcursortype(_NORMALCURSOR);
                               break;
                            }
                        }
                    }else{
                        if(counterStacks >= 1 && strlen(consoleView) > 0 && consoleView[strlen(consoleView)-1]!= 'E'
                           && consoleView[0]!= '\'' && isanumberoraexpression(lastInputStack->expression)!= 0){
                            float result;
                            char *numberError;
                            result = strtod(consoleView,&numberError);
                            if(strlen(numberError)==0){
                                result += strtod(lastInputStack->expression, NULL);
                                sprintf(lastInputStack->expression,"%G",result);
                                printStacks();
                                for(int index = 0; index < 50; index++){
                                    consoleView[index] = '\0';
                                }
                                positionCursor = 0;
                                _setcursortype(_NOCURSOR);
                                gotoxy(2,22);
                                clreol();
                                gotoxy(51,22);
                                printf("|");
                                gotoxy((50-(strlen(consoleView))),22);
                                printf("%s",consoleView);
                                gotoxy((50-positionCursor),22);
                                _setcursortype(_NORMALCURSOR);
                                break;
                            }else{
                                _setcursortype(_NOCURSOR);
                                textcolor(RED);
                                gotoxy(2,35);
                                printf("ERROR: ");
                                textcolor(WHITE);
                                printf("%s",numberError);
                                delay(500);
                                gotoxy(2,35);
                                clreol();
                                gotoxy(51,35);
                                printf("|");
                                gotoxy((50-(strlen(consoleView))),22);
                                printf("%s",consoleView);
                                gotoxy((50-positionCursor),22);
                                _setcursortype(_NORMALCURSOR);
                                break;
                            }
                        }else{
                            consoleEditor();
                            break;
                        }
                    }
                }

            case '-':
                {
                    if(counterStacks >= 2 && strlen(consoleView)==0){
                        if(isanumberoraexpression(lastInputStack->expression)== 1){
                            if(isanumberoraexpression((lastInputStack->next)->expression)== 1){
                                float result;
                                result = (strtod((lastInputStack->next)->expression, NULL) - strtod(lastInputStack->expression, NULL));
                                sprintf(lastInputStack->expression,"%G",result);
                                int saveSelectStack = selectedStack;
                                selectedStack = 2;
                                deleteSelectedStack();
                                selectedStack = saveSelectStack - 1;
                                if(selectedStack <= 0){
                                    selectedStack = 1;
                                }
                                printStacks();
                                break;
                            }else{
                                _setcursortype(_NOCURSOR);
                                textcolor(RED);
                                gotoxy(2,35);
                                printf("ERROR: ");
                                textcolor(WHITE);
                                printf("STACK 2 ES UNA EXPRESION ");
                                delay(500);
                                gotoxy(2,35);
                                clreol();
                                gotoxy(51,35);
                                printf("|");
                                gotoxy((50-(strlen(consoleView))),22);
                                printf("%s",consoleView);
                                gotoxy((50-positionCursor),22);
                                _setcursortype(_NORMALCURSOR);
                               break;
                            }
                        }else{
                            {
                                _setcursortype(_NOCURSOR);
                                textcolor(RED);
                                gotoxy(2,35);
                                printf("ERROR: ");
                                textcolor(WHITE);
                                printf("STACK 1 ES UNA EXPRESION ");
                                delay(500);
                                gotoxy(2,35);
                                clreol();
                                gotoxy(51,35);
                                printf("|");
                                gotoxy((50-(strlen(consoleView))),22);
                                printf("%s",consoleView);
                                gotoxy((50-positionCursor),22);
                                _setcursortype(_NORMALCURSOR);
                               break;
                            }
                        }
                    }else{
                        if(counterStacks >= 1 && strlen(consoleView) > 0 && consoleView[strlen(consoleView)-1]!= 'E'
                           && consoleView[0]!= '\'' && isanumberoraexpression(lastInputStack->expression)!= 0){
                            float result;
                            char *numberError;
                            result = strtod(consoleView,&numberError);
                            if(strlen(numberError)==0){
                                result -= strtod(lastInputStack->expression, NULL);
                                sprintf(lastInputStack->expression,"%G",result);
                                printStacks();
                                for(int index = 0; index < 50; index++){
                                    consoleView[index] = '\0';
                                }
                                positionCursor = 0;
                                _setcursortype(_NOCURSOR);
                                gotoxy(2,22);
                                clreol();
                                gotoxy(51,22);
                                printf("|");
                                gotoxy((50-(strlen(consoleView))),22);
                                printf("%s",consoleView);
                                gotoxy((50-positionCursor),22);
                                _setcursortype(_NORMALCURSOR);
                                break;
                            }else{
                                _setcursortype(_NOCURSOR);
                                textcolor(RED);
                                gotoxy(2,35);
                                printf("ERROR: ");
                                textcolor(WHITE);
                                printf("%s",numberError);
                                delay(500);
                                gotoxy(2,35);
                                clreol();
                                gotoxy(51,35);
                                printf("|");
                                gotoxy((50-(strlen(consoleView))),22);
                                printf("%s",consoleView);
                                gotoxy((50-positionCursor),22);
                                _setcursortype(_NORMALCURSOR);
                                break;
                            }
                        }else{
                            consoleEditor();
                            break;
                        }
                    }
                }

            case '*':
                {
                    if(counterStacks >= 2 && strlen(consoleView)==0){
                        if(isanumberoraexpression(lastInputStack->expression)== 1){
                            if(isanumberoraexpression((lastInputStack->next)->expression)== 1){
                                float result;
                                result = (strtod((lastInputStack->next)->expression, NULL) * strtod(lastInputStack->expression, NULL));
                                sprintf(lastInputStack->expression,"%G",result);
                                int saveSelectStack = selectedStack;
                                selectedStack = 2;
                                deleteSelectedStack();
                                selectedStack = saveSelectStack - 1;
                                if(selectedStack <= 0){
                                    selectedStack = 1;
                                }
                                printStacks();
                                break;
                            }else{
                                _setcursortype(_NOCURSOR);
                                textcolor(RED);
                                gotoxy(2,35);
                                printf("ERROR: ");
                                textcolor(WHITE);
                                printf("STACK 2 ES UNA EXPRESION ");
                                delay(500);
                                gotoxy(2,35);
                                clreol();
                                gotoxy(51,35);
                                printf("|");
                                gotoxy((50-(strlen(consoleView))),22);
                                printf("%s",consoleView);
                                gotoxy((50-positionCursor),22);
                                _setcursortype(_NORMALCURSOR);
                               break;
                            }
                        }else{
                            {
                                _setcursortype(_NOCURSOR);
                                textcolor(RED);
                                gotoxy(2,35);
                                printf("ERROR: ");
                                textcolor(WHITE);
                                printf("STACK 1 ES UNA EXPRESION ");
                                delay(500);
                                gotoxy(2,35);
                                clreol();
                                gotoxy(51,35);
                                printf("|");
                                gotoxy((50-(strlen(consoleView))),22);
                                printf("%s",consoleView);
                                gotoxy((50-positionCursor),22);
                                _setcursortype(_NORMALCURSOR);
                               break;
                            }
                        }
                    }else{
                        if(counterStacks >= 1 && strlen(consoleView) > 0 && consoleView[0]!= '\'' && isanumberoraexpression(lastInputStack->expression)!= 0){
                            float result;
                            char *numberError;
                            result = strtod(consoleView,&numberError);
                            if(strlen(numberError)==0){
                                result = result * strtod(lastInputStack->expression, NULL);
                                sprintf(lastInputStack->expression,"%G",result);
                                printStacks();
                                for(int index = 0; index < 50; index++){
                                    consoleView[index] = '\0';
                                }
                                positionCursor = 0;
                                _setcursortype(_NOCURSOR);
                                gotoxy(2,22);
                                clreol();
                                gotoxy(51,22);
                                printf("|");
                                gotoxy((50-(strlen(consoleView))),22);
                                printf("%s",consoleView);
                                gotoxy((50-positionCursor),22);
                                _setcursortype(_NORMALCURSOR);
                                break;
                            }else{
                                _setcursortype(_NOCURSOR);
                                textcolor(RED);
                                gotoxy(2,35);
                                printf("ERROR: ");
                                textcolor(WHITE);
                                printf("%s",numberError);
                                delay(500);
                                gotoxy(2,35);
                                clreol();
                                gotoxy(51,35);
                                printf("|");
                                gotoxy((50-(strlen(consoleView))),22);
                                printf("%s",consoleView);
                                gotoxy((50-positionCursor),22);
                                _setcursortype(_NORMALCURSOR);
                                break;
                            }
                        }else{
                            consoleEditor();
                            break;
                        }
                    }
                }

            case '/':
                {
                    if(counterStacks >= 2 && strlen(consoleView)==0){
                        if(isanumberoraexpression(lastInputStack->expression)== 1){
                            if(isanumberoraexpression((lastInputStack->next)->expression)== 1){
                                float result;
                                result = strtod(lastInputStack->expression, NULL);
                                if (result == 0){
                                    _setcursortype(_NOCURSOR);
                                    textcolor(RED);
                                    gotoxy(2,35);
                                    printf("ERROR: ");
                                    textcolor(WHITE);
                                    printf("DIVISION POR 0");
                                    delay(500);
                                    gotoxy(2,35);
                                    clreol();
                                    gotoxy(51,35);
                                    printf("|");
                                    gotoxy((50-(strlen(consoleView))),22);
                                    printf("%s",consoleView);
                                    gotoxy((50-positionCursor),22);
                                    _setcursortype(_NORMALCURSOR);
                                   break;
                                }
                                result = (strtod((lastInputStack->next)->expression, NULL) / strtod(lastInputStack->expression, NULL));
                                sprintf(lastInputStack->expression,"%G",result);
                                int saveSelectStack = selectedStack;
                                selectedStack = 2;
                                deleteSelectedStack();
                                selectedStack = saveSelectStack - 1;
                                if(selectedStack <= 0){
                                    selectedStack = 1;
                                }
                                printStacks();
                                break;
                            }else{
                                _setcursortype(_NOCURSOR);
                                textcolor(RED);
                                gotoxy(2,35);
                                printf("ERROR: ");
                                textcolor(WHITE);
                                printf("STACK 2 ES UNA EXPRESION ");
                                delay(500);
                                gotoxy(2,35);
                                clreol();
                                gotoxy(51,35);
                                printf("|");
                                gotoxy((50-(strlen(consoleView))),22);
                                printf("%s",consoleView);
                                gotoxy((50-positionCursor),22);
                                _setcursortype(_NORMALCURSOR);
                               break;
                            }
                        }else{
                            {
                                _setcursortype(_NOCURSOR);
                                textcolor(RED);
                                gotoxy(2,35);
                                printf("ERROR: ");
                                textcolor(WHITE);
                                printf("STACK 1 ES UNA EXPRESION ");
                                delay(500);
                                gotoxy(2,35);
                                clreol();
                                gotoxy(51,35);
                                printf("|");
                                gotoxy((50-(strlen(consoleView))),22);
                                printf("%s",consoleView);
                                gotoxy((50-positionCursor),22);
                                _setcursortype(_NORMALCURSOR);
                               break;
                            }
                        }
                    }else{
                        if(counterStacks >= 1 && strlen(consoleView) > 0 && consoleView[0]!= '\'' && isanumberoraexpression(lastInputStack->expression)!= 0){
                            float result;
                            char *numberError;
                            result = strtod(lastInputStack->expression, NULL);
                            if (result == 0){
                                _setcursortype(_NOCURSOR);
                                textcolor(RED);
                                gotoxy(2,35);
                                printf("ERROR: ");
                                textcolor(WHITE);
                                printf("DIVISION POR 0");
                                delay(500);
                                gotoxy(2,35);
                                clreol();
                                gotoxy(51,35);
                                printf("|");
                                gotoxy((50-(strlen(consoleView))),22);
                                printf("%s",consoleView);
                                gotoxy((50-positionCursor),22);
                                _setcursortype(_NORMALCURSOR);
                               break;
                            }
                            result = strtod(consoleView,&numberError);
                            if(strlen(numberError)==0){
                                result = result / strtod(lastInputStack->expression, NULL);
                                sprintf(lastInputStack->expression,"%G",result);
                                printStacks();
                                for(int index = 0; index < 50; index++){
                                    consoleView[index] = '\0';
                                }
                                positionCursor = 0;
                                _setcursortype(_NOCURSOR);
                                gotoxy(2,22);
                                clreol();
                                gotoxy(51,22);
                                printf("|");
                                gotoxy((50-(strlen(consoleView))),22);
                                printf("%s",consoleView);
                                gotoxy((50-positionCursor),22);
                                _setcursortype(_NORMALCURSOR);
                                break;
                            }else{
                                _setcursortype(_NOCURSOR);
                                textcolor(RED);
                                gotoxy(2,35);
                                printf("ERROR: ");
                                textcolor(WHITE);
                                printf("%s",numberError);
                                delay(500);
                                gotoxy(2,35);
                                clreol();
                                gotoxy(51,35);
                                printf("|");
                                gotoxy((50-(strlen(consoleView))),22);
                                printf("%s",consoleView);
                                gotoxy((50-positionCursor),22);
                                _setcursortype(_NORMALCURSOR);
                                break;
                            }
                        }else{
                            consoleEditor();
                            break;
                        }
                    }
                }

            case 'E':
                {
                    consoleEditor();
                    break;
                }

            case ',':
                {
                    pressedKey = '.';
                    consoleEditor();
                    break;
                }

            case '.':
                {
                    consoleEditor();
                    break;
                }

            case '(':
                {
                    consoleEditor();
                    break;
                }

            case ')':
                {
                    consoleEditor();
                    break;
                }

            case '\'':
                {
                    consoleEditor();
                    break;
                }

            case RETROCESO:
                {
                    consoleEditor();
                    break;
                }
        }
    }

    system("cls");
    printf("Se ha finalizado el programa");

    return 0;
}
