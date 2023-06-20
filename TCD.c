#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    char nome[25];
    int pontos;
    int empates;
    int derrotas;
}Jogador;

void Atualizar_Ranking(Jogador j);

int check_linha(int a[][3]);

int check_coluna(int a[][3]);

int check_diagonal(int a[][3]);

int check_velha(int a[][3]);

void limpar_buff();

#if defined(_WIN32)
    #define WINDOWS_SYSTEM
    #include <Windows.h>
#else
    #define UNIX_SYSTEM
    #include <unistd.h>
#endif

void my_sleep(int sleepms);

void IA4_Jogo_da_Velha(int a[][3], int rodada);

Jogador *listaDeJogadores(char *arq, int *qtd);

void reescreverArquivo(Jogador *LDJ, int qtd);

Jogador *ordenarLista(char *arq, char tipo);

void jogo_solo ();

void jogo_local();

void main ()
{
    int menu;
    char infinidade = '0';

    do {
        system("cls");

        printf(" 1 - Jogar\n");
        printf(" 2 - Ranking\n");
        printf(" 3 - Sobre\n");
        printf(" 4 - Sair\n\n\n");

        setbuf(stdin,NULL);

        scanf("%d", &menu);

        switch (menu) {
            case 1:
                system ("cls");

                int modalidade;
                printf(" 1 - Jogar contra uma IA\n");
                printf(" 2 - Jogo local\n\n\n");

                setbuf(stdin,NULL);

                scanf("%d", &modalidade);

                switch (modalidade){
                    case 1:
                        jogo_solo();
                        break;
                    case 2:
                        jogo_local();
                        break;
                    default:
                        system("cls");

                        printf("Valor invalido!");
                        setbuf(stdin,NULL);
                        getchar();
                }
                break;
            case 2:
                system ("cls");
                char tipo;
                int qtd;

                printf("No menu abaixo escolha uma opcao de ranking.\n\n");
                printf("E - ordenado por empates.\n");
                printf("V - ordenado por vitorias.\n");
                printf("D - ordenado por derrotas.\n");

                setbuf(stdin,NULL);

                scanf("%c", &tipo);

                Jogador *cu = ordenarLista("Ranking.txt", tipo);
                
                listaDeJogadores("Ranking.txt", &qtd);

                if(tipo == 'V'){
                    system ("cls");

                    printf("Ranking por Vitorias:\n");

                    for (int i = 0; i < qtd; i++){
                        printf("%d - %s  %d\n",  i+1, cu[i].nome, cu[i].pontos);
                    }
                    setbuf(stdin,NULL);
                    getchar();
                }else if(tipo == 'D'){
                    system ("cls");

                    printf("Ranking por derrotas:\n");

                    for (int i = 0; i < qtd; i++){
                        printf("%d - %s  %d\n",  i+1, cu[i].nome, cu[i].derrotas);
                    }
                    setbuf(stdin,NULL);
                    getchar();
                }else if(tipo == 'E'){
                    system ("cls");

                    printf("Ranking por empates:\n");

                    for (int i = 0; i < qtd; i++){
                        printf("%d - %s  %d\n",  i+1, cu[i].nome, cu[i].empates);
                    }
                    setbuf(stdin,NULL);
                    getchar();
                }
                break;
            case 3:
                setbuf(stdin,NULL);
                system("cls");
                

                printf("Esse foi o Trabalho de Conclusao de Disciplina (TCD) da diciplina de Programacao Procedimental, realizado no primeiro semestre do curso de Bacharelado em Ciencia da Computacao na Universidade Federal de Uberlandia (UFU).\n\n\n");

                printf("Creditos:\n");
                printf("Andre Polimanti Mensquiari Lemos\n\n\n");
                getchar();
                break;
            case 4:
                infinidade = 'N';
                break;
            default:
                system("cls");

                printf("Valor invalido!");
                setbuf(stdin,NULL);
                getchar();
        }
    }while (infinidade != 'N');
}

void jogo_solo (){
    int matriz[3][3], rodada, qtd, check = 0;
    char loop = '0';
    char l, c;
    Jogador jogador, *LDJ;

    system("cls");

    setbuf(stdin, NULL);

    printf("Digite o seu nome: ");
    fgets(jogador.nome, 25, stdin);
    jogador.nome[strcspn(jogador.nome, "\n")] = '\0';

    
    
    do{
        LDJ = listaDeJogadores("Ranking.txt", &qtd);

        jogador.pontos = 0;
        jogador.derrotas = 0;
        jogador.empates = 0;

        for (int i = 0; i < qtd; i++) {
            if (!(strcmp(jogador.nome, LDJ[i].nome))) {
                jogador.pontos = LDJ[i].pontos;
                jogador.derrotas = LDJ[i].derrotas;
                jogador.empates = LDJ[i].empates;
                check = 1;
            }
        }
        system("cls");

        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                matriz[i][j] = 0;
                //printf("%d ", matriz[i][j]);
            }
        //printf("\n");
        }

        printf("          _           _        \n");
        if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf(" __  __\n");}else{printf("   ___  \n");}
        if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf(" \\ \\/ /\n");}else{printf("  / _ \\ \n");}
        if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf("  >  < \n");}else{printf(" | (_) |\n");}
        if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf(" /_/\\_\\ \n");}else{printf("  \\___/ \n");}
        printf(" ________| |_________| |________\n");
        printf("|________   _________   ________|\n");
        if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf(" __  __\n");}else{printf("   ___  \n");}
        if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf(" \\ \\/ /\n");}else{printf("  / _ \\ \n");}            
        if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf("  >  < \n");}else{printf(" | (_) |\n");}
        if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf(" /_/\\_\\ \n");}else{printf("  \\___/ \n");}
        printf(" ________| |_________| |________\n");
        printf("|________   _________   ________|\n");
        if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf(" __  __\n");}else{printf("   ___  \n");}
        if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf(" \\ \\/ /\n");}else{printf("  / _ \\ \n");}
        if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf("  >  < \n");}else{printf(" | (_) |\n");}
        if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf(" /_/\\_\\ \n");}else{printf("  \\___/ \n");}
        printf("         |_|         |_|        \n");

        rodada = 0;

        while(1){
        
            printf("\n\nJogador, faca sua jogada!\n\n");

            while(1){
                printf("Linha: ");
                scanf(" %c", &l);
                limpar_buff();
                printf("Coluna: ");
                scanf(" %c", &c);
                limpar_buff();

                l -= '0';
                c -= '0';
                
                if((matriz[l-1][c-1] == 0) && (c >= 1) && (c <= 3) && (l >= 1) && (l <= 3)){
                    break;
                }else if(matriz[l-1][c-1] != 0 && (c >= 1) && (c <= 3) && (l >= 1) && (l <= 3)){
                    printf("\nVoce nao pode sobreescrever o adversario ou a si mesmo. Tente novamente!\n");
                }else{
                    printf("\nPelo menos uma coordenada invalida. Insira coordenadas com valores de 1 a 3.\n");
                }
            }

            rodada += 1;

            matriz[l-1][c-1] = 1;

            system ("cls");


            /*for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                printf("%d ", matriz[i][j]);
            }
            printf("\n");
            }*/
        
            printf("          _           _        \n");
            if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf(" __  __\n");}else{printf("   ___  \n");}
            if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf(" \\ \\/ /\n");}else{printf("  / _ \\ \n");}
            if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf("  >  < \n");}else{printf(" | (_) |\n");}
            if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf(" /_/\\_\\ \n");}else{printf("  \\___/ \n");}
            printf(" ________| |_________| |________\n");
            printf("|________   _________   ________|\n");
            if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf(" __  __\n");}else{printf("   ___  \n");}
            if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf(" \\ \\/ /\n");}else{printf("  / _ \\ \n");}            
            if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf("  >  < \n");}else{printf(" | (_) |\n");}
            if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf(" /_/\\_\\ \n");}else{printf("  \\___/ \n");}
            printf(" ________| |_________| |________\n");
            printf("|________   _________   ________|\n");
            if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf(" __  __\n");}else{printf("   ___  \n");}
            if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf(" \\ \\/ /\n");}else{printf("  / _ \\ \n");}
            if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf("  >  < \n");}else{printf(" | (_) |\n");}
            if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf(" /_/\\_\\ \n");}else{printf("  \\___/ \n");}
            printf("         |_|         |_|        \n");

            
            if(check_linha(matriz) || check_coluna(matriz) || check_diagonal(matriz)){
                printf("\n\nO Jogador venceu!");
                jogador.pontos++;
                break;
            }else if(check_velha(matriz)){
                printf("\n\nDeu velha!");
                jogador.empates++;
                break;
            }

            printf("\nTurno da IA...");

            my_sleep(1500);

            system ("cls");

            /*for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                printf("%d ", matriz[i][j]);
            }
            printf("\n");
            }*/


            IA4_Jogo_da_Velha(matriz, rodada);
            
            printf("          _           _        \n");
            if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf(" __  __\n");}else{printf("   ___  \n");}
            if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf(" \\ \\/ /\n");}else{printf("  / _ \\ \n");}
            if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf("  >  < \n");}else{printf(" | (_) |\n");}
            if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf(" /_/\\_\\ \n");}else{printf("  \\___/ \n");}
            printf(" ________| |_________| |________\n");
            printf("|________   _________   ________|\n");
            if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf(" __  __\n");}else{printf("   ___  \n");}
            if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf(" \\ \\/ /\n");}else{printf("  / _ \\ \n");}            
            if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf("  >  < \n");}else{printf(" | (_) |\n");}
            if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf(" /_/\\_\\ \n");}else{printf("  \\___/ \n");}
            printf(" ________| |_________| |________\n");
            printf("|________   _________   ________|\n");
            if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf(" __  __\n");}else{printf("   ___  \n");}
            if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf(" \\ \\/ /\n");}else{printf("  / _ \\ \n");}
            if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf("  >  < \n");}else{printf(" | (_) |\n");}
            if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf(" /_/\\_\\ \n");}else{printf("  \\___/ \n");}
            printf("         |_|         |_|        \n");


            if(check_linha(matriz) || check_coluna(matriz) || check_diagonal(matriz)){
                printf("\n\nA IA venceu!");
                jogador.derrotas++;
                break;
            }else if(check_velha(matriz)){
                printf("\n\nDeu velha!");
                break;
            }
        }

        if (check == 0) {
            Atualizar_Ranking(jogador);
        } 
        else {
            for (int i = 0; i < qtd; i++) {
                if (!(strcmp(jogador.nome, LDJ[i].nome))) {
                    LDJ[i].pontos = jogador.pontos;
                    LDJ[i].empates = jogador.empates;
                    LDJ[i].derrotas = jogador.derrotas;
                }
            }

            reescreverArquivo(LDJ, qtd);
        }

        printf("\n\nDeseja jogar novamente? Insira \"N\" para retornar ao menu ou qualquer outra coisa para continuar jogando.\n");
        loop = getchar();
        limpar_buff();
    }while (loop != 'N');

}

void jogo_local (){
    int matriz[3][3];
    char loop = '0';
    char l, c;

    do{
        system("cls");

        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                matriz[i][j] = 0;
                //printf("%d ", matriz[i][j]);
            }
        //printf("\n");
        }

        printf("          _           _        \n");
            if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf(" __  __\n");}else{printf("   ___  \n");}
            if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf(" \\ \\/ /\n");}else{printf("  / _ \\ \n");}
            if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf("  >  < \n");}else{printf(" | (_) |\n");}
            if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf(" /_/\\_\\ \n");}else{printf("  \\___/ \n");}
            printf(" ________| |_________| |________\n");
            printf("|________   _________   ________|\n");
            if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf(" __  __\n");}else{printf("   ___  \n");}
            if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf(" \\ \\/ /\n");}else{printf("  / _ \\ \n");}            
            if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf("  >  < \n");}else{printf(" | (_) |\n");}
            if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf(" /_/\\_\\ \n");}else{printf("  \\___/ \n");}
            printf(" ________| |_________| |________\n");
            printf("|________   _________   ________|\n");
            if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf(" __  __\n");}else{printf("   ___  \n");}
            if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf(" \\ \\/ /\n");}else{printf("  / _ \\ \n");}
            if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf("  >  < \n");}else{printf(" | (_) |\n");}
            if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf(" /_/\\_\\ \n");}else{printf("  \\___/ \n");}
            printf("         |_|         |_|        \n");



        while(1){
        
            printf("\n\nJogador 1, faca sua jogada!\n");

            while(1){
                printf("Linha: ");
                scanf(" %c", &l);
                limpar_buff();
                printf("Coluna: ");
                scanf(" %c", &c);
                limpar_buff();

                l -= '0';
                c -= '0';
                
                if((matriz[l-1][c-1] == 0) && (c >= 1) && (c <= 3) && (l >= 1) && (l <= 3)){
                    break;
                }else if(matriz[l-1][c-1] != 0 && (c >= 1) && (c <= 3) && (l >= 1) && (l <= 3)){
                    printf("Voce nao pode sobreescrever o adversario ou a si mesmo. Tente novamente!\n");
                }else{
                    printf("Pelo menos uma coordenada invalida. Insira coordenadas com valores de 1 a 3.\n");
                }
            }

            matriz[l-1][c-1] = 1;

            system ("cls");


            /*for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                printf("%d ", matriz[i][j]);
            }
            printf("\n");
            }*/
        
            printf("          _           _        \n");
            if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf(" __  __\n");}else{printf("   ___  \n");}
            if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf(" \\ \\/ /\n");}else{printf("  / _ \\ \n");}
            if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf("  >  < \n");}else{printf(" | (_) |\n");}
            if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf(" /_/\\_\\ \n");}else{printf("  \\___/ \n");}
            printf(" ________| |_________| |________\n");
            printf("|________   _________   ________|\n");
            if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf(" __  __\n");}else{printf("   ___  \n");}
            if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf(" \\ \\/ /\n");}else{printf("  / _ \\ \n");}            
            if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf("  >  < \n");}else{printf(" | (_) |\n");}
            if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf(" /_/\\_\\ \n");}else{printf("  \\___/ \n");}
            printf(" ________| |_________| |________\n");
            printf("|________   _________   ________|\n");
            if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf(" __  __\n");}else{printf("   ___  \n");}
            if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf(" \\ \\/ /\n");}else{printf("  / _ \\ \n");}
            if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf("  >  < \n");}else{printf(" | (_) |\n");}
            if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf(" /_/\\_\\ \n");}else{printf("  \\___/ \n");}
            printf("         |_|         |_|        \n");

            
            if(check_linha(matriz) || check_coluna(matriz) || check_diagonal(matriz)){
                printf("\n\nO Jogador 1 venceu!");
                break;
            }else if(check_velha(matriz)){
                printf("\n\nDeu velha!");
                break;
            }


            printf("\n\nJogador 2, faca sua jogada!\n");

            while(1){
                printf("Linha: ");
                scanf(" %c", &l);
                limpar_buff();
                printf("Coluna: ");
                scanf(" %c", &c);
                limpar_buff();

                l -= '0';
                c -= '0';

                if((matriz[l-1][c-1] == 0) && (c >= 1) && (c <= 3) && (l >= 1) && (l <= 3)){
                    break;
                }else if(matriz[l-1][c-1] != 0 && (c >= 1) && (c <= 3) && (l >= 1) && (l <= 3)){
                    printf("Voce nao pode sobreescrever o adversario ou a si mesmo. Tente novamente!\n");
                }else{
                    printf("Pelo menos uma coordenada invalida. Insira coordenadas com valores de 1 a 3.\n");
                }
            }


            matriz[l-1][c-1] = 2;

            system ("cls");

            /*for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                printf("%d ", matriz[i][j]);
            }
            printf("\n");
            }*/

            
            printf("          _           _        \n");
            if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf(" __  __\n");}else{printf("   ___  \n");}
            if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf(" \\ \\/ /\n");}else{printf("  / _ \\ \n");}
            if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf("  >  < \n");}else{printf(" | (_) |\n");}
            if(matriz[0][0] == 0){printf("         | |");}else if(matriz[0][0] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[0][1] == 0){printf("         | |");}else if(matriz[0][1] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[0][2] == 0){printf("       \n");}else if(matriz[0][2] == 1){printf(" /_/\\_\\ \n");}else{printf("  \\___/ \n");}
            printf(" ________| |_________| |________\n");
            printf("|________   _________   ________|\n");
            if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf(" __  __\n");}else{printf("   ___  \n");}
            if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf(" \\ \\/ /\n");}else{printf("  / _ \\ \n");}            
            if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf("  >  < \n");}else{printf(" | (_) |\n");}
            if(matriz[1][0] == 0){printf("         | |");}else if(matriz[1][0] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[1][1] == 0){printf("         | |");}else if(matriz[1][1] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[1][2] == 0){printf("       \n");}else if(matriz[1][2] == 1){printf(" /_/\\_\\ \n");}else{printf("  \\___/ \n");}
            printf(" ________| |_________| |________\n");
            printf("|________   _________   ________|\n");
            if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("  __  __ | |");}else{printf("   ___   | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf(" __  __\n");}else{printf("   ___  \n");}
            if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("  \\ \\/ / | |");}else{printf("  / _ \\  | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf(" \\ \\/ /\n");}else{printf("  / _ \\ \n");}
            if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("   >  <  | |");}else{printf(" | (_) | | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf("  >  < \n");}else{printf(" | (_) |\n");}
            if(matriz[2][0] == 0){printf("         | |");}else if(matriz[2][0] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[2][1] == 0){printf("         | |");}else if(matriz[2][1] == 1){printf("  /_/\\_\\ | |");}else{printf("  \\___/  | |");} if(matriz[2][2] == 0){printf("       \n");}else if(matriz[2][2] == 1){printf(" /_/\\_\\ \n");}else{printf("  \\___/ \n");}
            printf("         |_|         |_|        \n");


            if(check_linha(matriz) || check_coluna(matriz) || check_diagonal(matriz)){
                printf("\n\nO Jogador 2 venceu!");
                break;
            }else if(check_velha(matriz)){
                printf("\n\nDeu velha!");
                break;
            }
        }
        printf("\n\nDesejam jogar novamente? Insira \"N\" para voltar ao menu ou qualquer outra coisa para continuar.\n");
        loop = getchar();
        limpar_buff();
    }while (loop != 'N');
}

Jogador *listaDeJogadores(char *arq, int *qtd) {
    FILE *x;
    Jogador *temp;
    int count = 0;
    char c;
    x = fopen(arq, "r");

    while ((c = fgetc(x)) != EOF) {
        if (c == '\n') {
            count++;
        }
    }

    temp = (Jogador *) malloc(count*sizeof(Jogador));

    rewind(x);

    for (int i = 0; i < count; i++) {
        fscanf(x, "%s %d %d %d", &temp[i].nome, &temp[i].pontos, &temp[i].empates, &temp[i].derrotas);
    }

    fclose(x);

    *qtd = count;
    return temp;
}

void reescreverArquivo(Jogador *LDJ, int qtd) {
    FILE *x;
    x = fopen("Ranking.txt", "w");

    for (int i = 0; i < qtd; i++) {
        fprintf(x, "%s %d %d %d\n", LDJ[i].nome, LDJ[i].pontos, LDJ[i].empates, LDJ[i].derrotas);
    }

    fclose(x);
}

Jogador *ordenarLista(char *arq, char tipo) {
    int qtd, index;
    Jogador *temp, *LDJ = listaDeJogadores(arq, &qtd);

    temp = (Jogador *) malloc(qtd*sizeof(Jogador));

    switch (tipo) {
        case 'V':
            for (int i = 0; i < qtd; i++) {
                
                index = 0;
                for (int j = 1; j < qtd; j++) {
                    if (LDJ[index].pontos < LDJ[j].pontos) {
                        index = j;
                    }
                }

                temp[i] = LDJ[index];
                LDJ[index].pontos = -1;
            }
            break;
        case 'D':
            for (int i = 0; i < qtd; i++) {
                
                index = 0;
                for (int j = 1; j < qtd; j++) {
                    if (LDJ[index].derrotas < LDJ[j].derrotas) {
                        index = j;
                    }
                }

                temp[i] = LDJ[index];
                LDJ[index].derrotas = -1;
            }
            break;
        case 'E':
            for (int i = 0; i < qtd; i++) {
                
                index = 0;
                for (int j = 1; j < qtd; j++) {
                    if (LDJ[index].empates < LDJ[j].empates) {
                        index = j;
                    }
                }

                temp[i] = LDJ[index];
                LDJ[index].empates = -1;
            }
            break;
        default:
            system("cls");

            printf("Caractere invalido!");
            setbuf(stdin,NULL);
            getchar();
    }
    return temp;
}

void Atualizar_Ranking(Jogador j) {
    FILE* file = fopen("ranking.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    //Jogador jogadores[10];

    fprintf(file, "%s %d %d %d\n", j.nome, j.pontos, j.empates, j.derrotas);

    fclose(file);
}

int check_linha(int a[][3]){
    for (int i = 0, j = 0; i < 3; i++){
        if ((a[i][j] == a[i][j+1]) && (a[i][j] == a[i][j+2]) && a[i][j] != 0){
                return 1;
        }
    } 
return 0;
}

int check_coluna(int a[][3]){
    for (int i = 0, j = 0; j < 3; j++){
        if ((a[i][j] == a[i+1][j]) && (a[i][j] == a[i+2][j]) && a[i][j] != 0){
                return 1;
        }
    } 
return 0;
}

int check_diagonal(int a[][3]){
    int i = 0, j = 0;
    if ((((a[i][j] == a[i+1][j+1]) && (a[i][j] == a[i+2][j+2])) && ((a[i][j] != 0))) || ((a[i][j+2] == a[i+1][j+1]) && (a[i][j+2] == a[i+2][j]) && (a[i+2][j] != 0))){
        return 1;
    }
return 0;
}

int check_velha(int a[][3]){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if(a[i][j] == 0){
                return 0;
            }
        }
    }
return 1;
}

void limpar_buff(){ 
    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n'){} 
}

void my_sleep(int sleepms)
{
    #ifdef WINDOWS_SYSTEM
        Sleep(sleepms);
    #else
        usleep(sleepms * 1000);
    #endif
}

void IA4_Jogo_da_Velha(int a[][3], int rodada){
    srand(time(NULL));
    int linha, coluna;

    //Vê se a primeira jogada do jogador foi no centro e age caso sim.
    if((rodada == 1) && (a[1][1] == 1)){
        while (1){
            linha = rand() % 3;
            coluna = rand() % 3;
            if((linha != 1) && (coluna !=1)){
                break;
            }
        }
        a[linha][coluna] = 2;

    //Vê se a primeira jogada do jogador foi em uma canto central e age caso sim.
    }else if((rodada == 1) && ((a[0][1] == 1) || (a[1][0] == 1) || (a[2][1] == 1) || (a[1][2] == 1))){
        if(a[0][1] == 1){
            while (1){
                linha = rand() % 3;
                coluna = rand() % 3;
                if((linha == 0) && ((coluna ==2) || (coluna == 0 ))){
                    break;
                }
            }
        a[linha][coluna] = 2;
        }
        else if(a[1][0] == 1){
            while (1){
                linha = rand() % 3;
                coluna = rand() % 3;
                if((coluna == 0) && ((linha ==2) || (linha == 0 ))){
                    break;
                }
            }
        a[linha][coluna] = 2;
        }
        else if(a[2][1] == 1){
            while (1){
                linha = rand() % 3;
                coluna = rand() % 3;
                if((linha == 2) && ((coluna ==2) || (coluna == 0 ))){
                    break;
                }
            }
        a[linha][coluna] = 2;
        }
        else if(a[1][2] == 1){
            while (1){
                linha = rand() % 3;
                coluna = rand() % 3;
                if((coluna == 2) && ((linha ==2) || (linha == 0 ))){
                    break;
                }
            }
        a[linha][coluna] = 2;
        }
    //Vê se a primeira jogada do jogador foi em uma quina e age caso sim.
    }else if((rodada == 1) && ((a[0][0] == 1) || (a[0][2] == 1) || (a[2][0] == 1) || (a[2][2] == 1))){
        a[1][1] = 2;

    }else if(rodada == 2){
        if(a[1][1] == 0){
            a[1][1] = 2;
        }

        //Quina e centro

        else if (a[1][1] == 1 && a[0][0] == 1 && a[2][2] == 2){
            a[0][2] = 2;
        }else if (a[1][1] == 1 && a[2][2] == 1 && a[0][0] == 2){
            a[0][2] = 2;
        }else if (a[1][1] == 1 && a[0][2] == 1 && a[2][0] == 2){
            a[2][2] = 2;
        }else if (a[1][1] == 1 && a[2][0] == 1 && a[0][2] == 2){
            a[2][2] = 2;
        }
        //Duas quinas opostas.
        else if((a[0][0] == 1) && (a[2][2] == 1)){
            while (1){
                linha = rand() % 3;
                coluna = rand() % 3;
                if(((((linha == 2) && (coluna ==1)) || ((linha == 0 ) && ( coluna == 1))) && (a[linha][coluna] == 0))){
                    break;
                }
            }
        a[linha][coluna] = 2;
        }else if((a[0][2] == 1) && (a[2][0] == 1)){
            while (1){
                linha = rand() % 3;
                coluna = rand() % 3;
                if(((((linha == 0) && (coluna ==1)) || ((linha == 2 ) && ( coluna == 1))) && (a[linha][coluna] == 0))){
                    break;
                }
            }
        a[linha][coluna] = 2;

        //Quina esquerda superior e outra quina não oposta.
        }else if((a[0][0] == 1) && (a[0][2] == 1)){
            a[0][1] = 2;
        }else if((a[0][0] == 1) && (a[2][0] == 1)){
            a[1][0] = 2;
        
        //Quina esquerda superior em um canto central.
        }else if((a[0][0] == 1) && (a[0][1] == 1)){
            if(a[0][2] == 0){
                a[0][2] = 2;
            }else{
                a[1][1] = 2;
            }
        }else if((a[0][0] == 1) && (a[1][0] == 1)){
            if(a[2][0] == 0){
                a[2][0] = 2;
            }else{
                a[1][1] = 2;
            }
        }else if((a[0][0] == 1) && (a[2][1] == 1)){
            if(a[2][0] == 0){
                a[2][0] = 2;
            }else{
                a[1][1] = 2;
            }
        }else if((a[0][0] == 1) && (a[1][2] == 1)){
            if(a[0][2] == 0){
                a[0][2] = 2;
            }else{
                a[1][1] = 2;
            }
        }



        //Quina direita supeior e outra quina não oposta.
        else if((a[0][2] == 1) && (a[0][0] == 1)){
            a[0][1] = 2;
        }else if((a[0][2] == 1) && (a[2][2] == 1)){
            a[1][2] = 2;

        //Quina direita superior em um canto central.
        }else if((a[0][2] == 1) && (a[1][2] == 1)){
            if(a[2][2] == 0){
                a[2][2] = 2;
            }else{
                a[1][1] = 2;
            }
        }else if((a[0][2] == 1) && (a[2][1] == 1)){
            if(a[2][2] == 0){
                a[2][2] = 2;
            }else{
                a[1][1] = 2;
            }
        }else if((a[0][2] == 1) && (a[0][1] == 1)){
            if(a[0][0] == 0){
                a[0][0] = 2;
            }else{
                a[1][1] = 2;
            }
        }else if((a[0][2] == 1) && (a[1][0] == 1)){
            if(a[0][0] == 0){
                a[0][0] = 2;
            }else{
                a[1][1] = 2;
            }
        }



        //Quina esquerda inferior e outra quina não oposta.
        else if((a[2][0] == 1) && (a[0][0] == 1)){
            a[1][0] = 2;
        }else if((a[2][0] == 1) && (a[2][2] == 1)){
            a[2][1] = 2;

        //Quina esquerda inferior em um canto central.
        }else if((a[2][0] == 1) && (a[1][0] == 1)){
            if(a[0][0] == 0){
                a[0][0] = 2;
            }else{
                a[1][1] = 2;
            }
        }else if((a[2][0] == 1) && (a[2][1] == 1)){
            if(a[2][2] == 0){
                a[2][2] = 2;
            }else{
                a[1][1] = 2;
            }
        }else if((a[2][0] == 1) && (a[0][1] == 1)){
            if(a[0][0] == 0){
                a[0][0] = 2;
            }else{
                a[1][1] = 2;
            }
        }else if((a[2][0] == 1) && (a[1][2] == 1)){
            if(a[2][2] == 0){
                a[2][2] = 2;
            }else{
                a[1][1] = 2;
            }
        }

        //Quina direita inferior e outra quina não oposta.
        else if((a[2][2] == 1) && (a[2][0] == 1)){
            a[2][1] = 2;
        }else if((a[2][2] == 1) && (a[0][2] == 1)){
            a[1][2] = 2;
        
        
        //Quina direita inferior em um canto central.
        }else if((a[2][2] == 1) && (a[2][1] == 1)){
            if(a[2][0] == 0){
                a[2][0] = 2;
            }else{
                a[1][1] = 2;
            }
        }else if((a[2][2] == 1) && (a[1][2] == 1)){
            if(a[0][2] == 0){
                a[0][2] = 2;
            }else{
                a[1][1] = 2;
            }
        }else if((a[2][2] == 1) && (a[1][0] == 1)){
            if(a[2][0] == 0){
                a[2][0] = 2;
            }else{
                a[1][1] = 2;
            }
        }else if((a[2][2] == 1) && (a[0][1] == 1)){
            if(a[2][0] == 0){
                a[2][0] = 2;
            }else{
                a[1][1] = 2;
            }
        }else if(a[2][0] == 1 && a[1][1] == 1 && a[0][2] == 0){
            a[0][2] = 2;
        }else if(a[2][0] == 1 && a[0][2] == 1 && a[1][1] == 0){
            a[1][1] = 2;
        }else if(a[1][1] == 1 && a[0][2] == 1 && a[2][0] == 0){
            a[2][0] = 2;
        
        
        //Na diagonal principal.
        }else if(a[0][0] == 1 && a[1][1] == 1 && a[2][2] == 0){
            a[2][2] = 2;
        }else if(a[0][0] == 1 && a[2][2] == 1 && a[1][1] == 0){
            a[1][1] = 2;
        }else if(a[1][1] == 1 && a[2][2] == 1 && a[0][0] == 0){
            a[0][0] = 2;
        //Por coluna.
        }else if(a[0][0] == 1 && a[1][0] == 1 && a[2][0] == 0){
            a[2][0] = 2;
        }else if(a[0][0] == 1 && a[2][0] == 1 && a[1][0] == 0){
            a[1][0] = 2;
        }else if(a[2][0] == 1 && a[1][0] == 1 && a[0][0] == 0){
            a[0][0] = 2;
        }
        else if(a[0][1] == 1 && a[1][1] == 1 && a[2][1] == 0){
            a[2][1] = 2;
        }else if(a[0][1] == 1 && a[2][1] == 1 && a[1][1] == 0){
            a[1][1] = 2;
        }else if(a[1][1] == 1 && a[2][1] == 1 && a[0][1] == 0){
            a[0][1] = 2;
        }
        else if(a[0][2] == 1 && a[1][2] == 1 && a[2][2] == 0){
            a[2][2] = 2;
        }else if(a[0][2] == 1 && a[2][2] == 1 && a[1][2] == 0){
            a[1][2] = 2;
        }else if(a[1][2] == 1 && a[2][2] == 1 && a[0][2] == 0){
            a[0][2] = 2;
        

        //Por linha.
        }else if(a[0][0] == 1 && a[0][1] == 1 && a[0][2] == 0){
            a[0][2] = 2;
        }else if(a[0][0] == 1 && a[0][2] == 1 && a[0][1] == 0){
            a[0][1] = 2;
        }else if(a[0][1] == 1 && a[0][2] == 1 && a[0][0] == 0){
            a[0][0] = 2;
        }
        else if(a[1][2] == 1 && a[1][1] == 1 && a[1][0] == 0){
            a[1][0] = 2;
        }else if(a[1][0] == 1 && a[1][1] == 1 && a[1][2] == 0){
            a[1][2] = 2;
        }else if(a[1][2] == 1 && a[1][0] == 1 && a[1][1] == 0){
            a[1][1] = 2;
        }
        else if(a[2][0] == 1 && a[2][1] == 1 && a[2][2] == 0){
            a[2][2] = 2;
        }else if(a[2][0] == 1 && a[2][2] == 1 && a[2][1] == 0){
            a[2][1] = 2;
        }else if(a[2][2] == 1 && a[2][1] == 1 && a[2][0] == 0){
            a[2][0] = 2;
        }

    }else if(rodada == 2 || rodada == 3 || rodada == 4 || rodada == 5 || rodada == 6){
        //Ganha.
        //Fecha a diagonal secundária.
        if(a[2][0] == 2 && a[1][1] == 2 && a[0][2] == 0){
            a[0][2] = 2;
        }else if(a[2][0] == 2 && a[0][2] == 2 && a[1][1] == 0){
            a[1][1] = 2;
        }else if(a[1][1] == 2 && a[0][2] == 2 && a[2][0] == 0){
            a[2][0] = 2;
        
        //Fecha a diagonal principal.
        }else if(a[0][0] == 2 && a[1][1] == 2 && a[2][2] == 0){
            a[2][2] = 2;
        }else if(a[0][0] == 2 && a[2][2] == 2 && a[1][1] == 0){
            a[1][1] = 2;
        }else if(a[1][1] == 2 && a[2][2] == 2 && a[0][0] == 0){
            a[0][0] = 2;
        
        //Fecha colunas.
        }else if(a[0][0] == 2 && a[1][0] == 2 && a[2][0] == 0){
            a[2][0] = 2;
        }else if(a[0][0] == 2 && a[2][0] == 2 && a[1][0] == 0){
            a[1][0] = 2;
        }else if(a[2][0] == 2 && a[1][0] == 2 && a[0][0] == 0){
            a[0][0] = 2;
        }
        else if(a[0][1] == 2 && a[1][1] == 2 && a[2][1] == 0){
            a[2][1] = 2;
        }else if(a[0][1] == 2 && a[2][1] == 2 && a[1][1] == 0){
            a[1][1] = 2;
        }else if(a[1][1] == 2 && a[2][1] == 2 && a[0][1] == 0){
            a[0][1] = 2;
        }
        else if(a[0][2] == 2 && a[1][2] == 2 && a[2][2] == 0){
            a[2][2] = 2;
        }else if(a[0][2] == 2 && a[2][2] == 2 && a[1][2] == 0){
            a[1][2] = 2;
        }else if(a[1][2] == 2 && a[2][2] == 2 && a[0][2] == 0){
            a[0][2] = 2;
        }

        //Fecha lihas.
        else if(a[0][0] == 2 && a[0][1] == 2 && a[0][2] == 0){
            a[0][2] = 2;
        }else if(a[0][0] == 2 && a[0][2] == 2 && a[0][1] == 0){
            a[0][1] = 2;
        }else if(a[0][1] == 2 && a[0][2] == 2 && a[0][0] == 0){
            a[0][0] = 2;
        }
        else if(a[1][0] == 2 && a[1][1] == 2 && a[1][2] == 0){
            a[1][2] = 2;
        }else if(a[1][0] == 2 && a[1][1] == 2 && a[1][2] == 0){
            a[1][2] = 2;
        }else if(a[1][0] == 2 && a[1][1] == 2 && a[1][2] == 0){
            a[1][2] = 2;
        }
        else if(a[2][0] == 2 && a[2][1] == 2 && a[2][2] == 0){
            a[2][2] = 2;
        }else if(a[2][0] == 2 && a[2][2] == 2 && a[2][1] == 0){
            a[2][1] = 2;
        }else if(a[2][2] == 2 && a[2][1] == 2 && a[2][0] == 0){
            a[2][0] = 2;
    


        //Impede que o jogador ganhe.
        
        
        //Na diagonal secundária.
        }else if(a[2][0] == 1 && a[1][1] == 1 && a[0][2] == 0){
            a[0][2] = 2;
        }else if(a[2][0] == 1 && a[0][2] == 1 && a[1][1] == 0){
            a[1][1] = 2;
        }else if(a[1][1] == 1 && a[0][2] == 1 && a[2][0] == 0){
            a[2][0] = 2;
        
        
        //Na diagonal principal.
        }else if(a[0][0] == 1 && a[1][1] == 1 && a[2][2] == 0){
            a[2][2] = 2;
        }else if(a[0][0] == 1 && a[2][2] == 1 && a[1][1] == 0){
            a[1][1] = 2;
        }else if(a[1][1] == 1 && a[2][2] == 1 && a[0][0] == 0){
            a[0][0] = 2;


        //Por coluna.
        }else if(a[0][0] == 1 && a[1][0] == 1 && a[2][0] == 0){
            a[2][0] = 2;
        }else if(a[0][0] == 1 && a[2][0] == 1 && a[1][0] == 0){
            a[1][0] = 2;
        }else if(a[2][0] == 1 && a[1][0] == 1 && a[0][0] == 0){
            a[0][0] = 2;
        }
        else if(a[0][1] == 1 && a[1][1] == 1 && a[2][1] == 0){
            a[2][1] = 2;
        }else if(a[0][1] == 1 && a[2][1] == 1 && a[1][1] == 0){
            a[1][1] = 2;
        }else if(a[1][1] == 1 && a[2][1] == 1 && a[0][1] == 0){
            a[0][1] = 2;
        }
        else if(a[0][2] == 1 && a[1][2] == 1 && a[2][2] == 0){
            a[2][2] = 2;
        }else if(a[0][2] == 1 && a[2][2] == 1 && a[1][2] == 0){
            a[1][2] = 2;
        }else if(a[1][2] == 1 && a[2][2] == 1 && a[0][2] == 0){
            a[0][2] = 2;
        

        //Por linha.
        }else if(a[0][0] == 1 && a[0][1] == 1 && a[0][2] == 0){
            a[0][2] = 2;
        }else if(a[0][0] == 1 && a[0][2] == 1 && a[0][1] == 0){
            a[0][1] = 2;
        }else if(a[0][1] == 1 && a[0][2] == 1 && a[0][0] == 0){
            a[0][0] = 2;
        }
        else if(a[1][2] == 1 && a[1][1] == 1 && a[1][0] == 0){
            a[1][0] = 2;
        }else if(a[1][0] == 1 && a[1][1] == 1 && a[1][2] == 0){
            a[1][2] = 2;
        }else if(a[1][2] == 1 && a[1][0] == 1 && a[1][1] == 0){
            a[1][1] = 2;
        }
        else if(a[2][0] == 1 && a[2][1] == 1 && a[2][2] == 0){
            a[2][2] = 2;
        }else if(a[2][0] == 1 && a[2][2] == 1 && a[2][1] == 0){
            a[2][1] = 2;
        }else if(a[2][2] == 1 && a[2][1] == 1 && a[2][0] == 0){
            a[2][0] = 2;
        }

        //Caso não dê pra vencer ou pra travar o jogador.

        else if((a[1][1] == 2) && ((a[0][1] == 0) || (a[2][1] == 0))){
            while(1){
                linha = rand() % 3;
                if(linha != 1 && a[linha][1] == 0){
                    break;
                }
            }
            a[linha][1] = 2;
        }else if((a[1][1] == 2) && ((a[1][0] == 0) || (a[1][2] == 0))){
            while(1){
                coluna = rand() % 3;
                if(coluna != 1 && a[1][coluna] == 0){
                    break;
                }
            }
            a[1][coluna] = 2;
        }else if((a[1][1] == 2) && ((a[0][0] == 0) || (a[0][2] == 0))){
            while(1){
                coluna = rand() % 3;
                if(coluna != 1 && a[0][coluna] == 0){
                    break;
                }
            }
            a[0][coluna] = 2;
        }else if(a[0][1] == 1 && (a[2][0] == 1 || a[2][2] == 1) && a[2][1] == 0){
            a[2][1] = 2;
        }else if(a[1][2] == 1 && (a[2][0] == 1 || a[0][0] == 1) && a[1][0] == 0){
            a[1][0] = 2;
        }else if(a[2][1] == 1 && (a[0][0] == 1 || a[0][2] == 1) && a[0][1] == 0){
            a[0][1] = 2;
        }else if(a[1][0] == 1 && (a[0][2] == 1 || a[2][2] == 1) && a[2][1] == 0){
            a[2][1] = 2;
        }else{
            while(1){
                coluna = rand() % 3;
                linha = rand() % 3;
                if(a[linha][coluna] == 0){
                    break;
                }
            }
        a[linha][coluna] = 2;
        }
    }
}