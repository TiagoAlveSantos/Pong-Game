#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main(void)
{
    const int L = 19;
    const int C = 71;
    int i, j, x, y, player1 = 0, player2 = 0, RaqE = 6, RaqD = 6,
    botDirec, bolaX, bolaY, direcX, direcY, veloc, ponto, raquete;
    char pong[L][C], c, bola;
    srand(time(NULL));

    /***********************************************************
    * i e j são variaveis de controle para alguns "for".
    *
    * x e y são variaveis de controle para o for das raquetes.
    *
    * player1 e player 2 somam o placar do jogo.
    *
    * RaqE e RaqD são respectivamente Raquete Esquerda e Raquete
    * direita.
    *
    * raquete é uma variavel responsavel por reduzir o "while" -
    * unificando o RaqE e RaqD.
    *
    * botDirec controla a direção aleatória da raquete direita q
    * ue é a raquede to bot.
    *
    * valoc é a variavel que controla a velocidade da bolinha.
    *
    * ponto é a variavel que controla o placar do jogo.
    *
    * bolaX e bolaY são as coordenadas da bolinha.
    *
    * derecX e direcY trabalham junto com bolaX e bolaY pois fa-
    * zem o controle de movimentação das coordenadas da bolinha
    * conforme a angulação das raquetes.
    *
    * c é a variavel que ajuda na captação do teclado para movi-
    * mento.
    *
    * bola é a bolinha em si.
    ***********************************************************/


    //Zerando tudo
    for (i = 0; i < L; i++) {
        for (j = 0; j < C; j++) {
            pong[i][j] = ' ';
        }
    }
    //Fazendo a mesa
    for (i = 0; i < C; i++) pong[0][i] = '*';
    for (i = 0; i < C; i++) pong[L-1][i] = '*';
    for (i = 0; i < L; i++) pong[i][0] = '!';
    for (i = 0; i < L; i++) pong[i][C-1] = '!';

    //Jogo
    while (player1 < 10 && player2 < 10) {
        //Sorteia o lado da bola
        bolaX = 36;
        bolaY = 10;
        direcX = 1-(rand() % 2);
        if (direcX == 0) direcX--;
        direcY = 1-(rand() % 2);
        if (direcY == 0) direcY--;
        veloc = 1;
        ponto = 0;
        //Partida
        while (ponto == 0) {
            system("cls");
            //barra do robo
            botDirec = 1 - (rand() % 3);
            RaqD += botDirec;
            if (RaqD < 1 || RaqD > 10) {
                RaqD -= botDirec;
            }
            //Raquete
            for (x = 3, y = 1; y < L-1; y++) pong[y][x] = ' ';
            for (x = 67, y = 1; y < L-1; y++) pong[y][x] = ' ';
            for (x = 3, y = RaqE; y < RaqE+8; y++) pong[y][x] = '#';
            for (x = 67, y = RaqD; y < RaqD+8; y++) pong[y][x] = '#';
            //Velocidade
            for (i = 1; i <= veloc; i++) {
                //Batida da bola
                if (pong[bolaY][bolaX] = '0') pong[bolaY][bolaX] = ' ';
                bolaX += direcX;
                bolaY += direcY;
                if (bolaY <= 1) {
                    bolaY++;
                    direcY *= -1;
                    continue;
                }
                if (bolaY >= 18) {
                    bolaY--;
                    direcY *= -1;
                    continue;
                }
                bola = pong[bolaY][bolaX];
                //Ponto de impacto
                switch (bola) {
                case '*':
                    direcY *= -1;
                    break;
                //Contando o placar
                case '!':
                    if (direcX < 0) player2++;
                    else player1++;
                    ponto++;
                    break;
                case '#':
                    if (direcX < 0)
                        raquete = RaqE;
                    else
                        raquete = RaqD;
                    veloc++;
                    //Angulo de 45
                    if (bolaY == raquete || bolaY == raquete+7) {
                        direcX *= -1;
                        bolaX += direcX;
                        direcY = -direcX;
                        break;
                    }
                    //Angulo de 60
                    else if (bolaY < raquete+3) {
                        direcX *= -1;
                        if (direcY == 1 || direcY == -1) direcY *= 2;
                        else if (direcY == 0) direcY = 2*direcX;
                        bolaX += direcX;
                        bolaY += direcY;
                        break;
                    }
                    //Angulo de 90
                    else if (bolaY < raquete+5) {
                        direcY = 0;
                        direcX *= -1;
                        bolaX += direcX;
                        break;
                    }
                    else {
                        direcX *= -1;
                        if (direcY == 1 || direcY == -1) direcY *= 2;
                        else if (direcY == 0) direcY = -2*direcX;
                        bolaX += direcX;
                        bolaY += direcY;
                        break;
                    }
                //Desenhando o avanço
                case ' ':
                    bola = '0';
                }
                pong[bolaY][bolaX] = bola;
                if (ponto) break;
            }
            //Desenhando a mesa
            for (i = 0; i < L; i++) {
                for (j = 0; j < C; j++) {
                    printf ("%c", pong[i][j]);
                }
                printf("\n");
            }
            //Mostrando o placar
            printf ("PLACAR\nJogador 1: %d\tJogador 2: %d\nPara abortar aperte Q", player1, player2);
            if (ponto) continue;
            //Lendo o movimento da raquete
            if (kbhit() == 1) {
                c = tolower(getch());
                switch (c) {
                case 'w':
                    if (RaqE > 1) RaqE--;
                    break;
                case 's':
                    if (RaqE < 10) RaqE++;
                    break;
                /*case 'o':
                    if (RaqD > 1) RaqD--;
                    break;
                case 'l':
                    if (RaqD < 10) RaqD++;
                    break;*/
                //Saida de emergencia
                case 'q':
                    return 0;
                }
            }
        }
    }
    return 0;
}