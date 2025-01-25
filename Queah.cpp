#include <raylib.h>
#include <cmath>
#include <cstring>
#include <cstdio>

#define MAX_INPUT_CHARS 16 // Define o tamanho maximo do texto digitado
#define MAX_LINHA 1024  // Define o tamanho máximo da linha do arquivo
#define MAX_LINHAS 20   // Define o número máximo de linhas a serem exibidas na tela

enum tela {
    acaoInicio,
    acaoJogar,
    acaoJogarDois,
    acaoQueah,
    acaoCriadores,
    acaoRegras,
    acaoVitoria,
    acaoHistorico,
    acaoA
};

void AbaJogadorUm();
void AbaJogadorDois();
void AbaQueah();
void AbaVencedor();
void AbaCriadores();
void AbaRegras();
void AbaHistorico();
void escreverNomeJogador1(const char *nome);
void escreverNomeJogador2(const char *nome);
void escreverNomeVencedor(const char *nome);
void lerConteudoDoArquivoPara1(char linhas[MAX_LINHAS][MAX_LINHA]);
void lerConteudoDoArquivoPara2(char linhas[MAX_LINHAS][MAX_LINHA]);
void lerConteudoDoArquivoPara3(char linhas[MAX_LINHAS][MAX_LINHA]);

bool IsPointInCircle(Vector2 point, Vector2 circleCenter, float radius);
bool IsPositionOccupied(Vector2 position, Vector2 pecasPosicao1[], Vector2 pecasPosicao2[], int contarPeca1, int contarPeca2);
bool verificarEReporPecas(char tabuleiro[5][5], char jogadorPerdeu, int fimX, int fimY, int &total1, int &total2);
bool capturarPeca(char tabuleiro[5][5], int paraX, int paraY, int fimX, int fimY, char jogador, int &pecasX, int &pecasY,int &pecasAtivas1, int &pecasAtivas2);
void alternarJogador(char &jogadorAtual);
void realizarMovimento(char tabuleiro[5][5], int paraX, int paraY, int fimX, int fimY);
bool movimentoValido(char tabuleiro[5][5], int paraX, int paraY, int fimX, int fimY, char jogador);
int conversorLixeira(int posX, int posY, bool tipoXouY);
int conversorLixeira(int posX, int posY);
int conversorTabuleiro(int fimX, int fimY, bool tipoXouY);
int conversorTabuleiro(int fimX, int fimY);

int main(){
    const int screenWidth = 720;
    const int screenHeight = 800;
    InitWindow(screenWidth , screenHeight , "Queah");
    Font font = GetFontDefault();
    tela janelaExibir = acaoInicio;

    float spaceBetween = 10.0f;
    int victories = 0;
    float elapsedTime = 0.0f;

    Rectangle jogar = {200 , 360, 300, 100 };
    Rectangle criadores = {250 , jogar.y + jogar.height + spaceBetween + 10, 200, 70 };
    Rectangle regras = {250 , criadores.y + criadores.height + spaceBetween, 200, 70 };
    Rectangle historico = {250, regras.y + regras.height + spaceBetween, 200, 70};
    Rectangle voltar = {screenWidth - 110, 10, 100, 30};
    Rectangle confirmar = {250,360,200,100};
    Rectangle confirmarDois = {250,360,200,100};
    Rectangle tabuleiroTela = {70,150,580,580};
    Rectangle criadoresfinal {100,650,200,70};
    
    Rectangle fundoHistorico = {70,150,580,580};
    
    float rotation = 45.0f;
    Vector2 origin = {50, 50};
    Rectangle quadrado1 = {360, 440, 100, 100};
    Rectangle quadrado2 = {219, 440, 100, 100};
    Rectangle quadrado3 = {501, 440, 100, 100};

    Rectangle quadrado4 = {430.5, 510.5, 100, 100};
    Rectangle quadrado5 = {289.5, 510.5, 100, 100};

    Rectangle quadrado6 = {360, 581, 100, 100};
    Rectangle quadrado7 = {219, 581, 100, 100};
    Rectangle quadrado8 = {501, 581, 100, 100};

    Rectangle quadrado9 = {360, 299, 100, 100};
    Rectangle quadrado10 = {219, 299, 100, 100};
    Rectangle quadrado11 = {501, 299, 100, 100};

    Rectangle quadrado12 = {430.5, 369.5, 100, 100};
    Rectangle quadrado13 = {289.5, 369.5, 100, 100};

    Rectangle quadrados[13] = {quadrado1,quadrado2,quadrado3,quadrado4,quadrado5,quadrado6,quadrado7,quadrado8,quadrado9,quadrado10,quadrado11,quadrado12,quadrado13};

    Color retColorJogar = LIGHTGRAY;
    Color retColorCriadores = LIGHTGRAY;
    Color retColorRegras = LIGHTGRAY;
    Color retColorHistorico = LIGHTGRAY;
    Color retColorVoltar = LIGHTGRAY;
    Color retColorConfirmar = LIGHTGRAY;
    Color retColorConfirmarDois = LIGHTGRAY;
    Color retColorCriadoresFinal = LIGHTGRAY;

    Color colorJogar = BLACK;
    Color colorCriadores = BLACK;
    Color colorRegras = BLACK;
    Color colorHistorico = BLACK;
    Color colorVoltar = BLACK;
    Color colorConfirmar = BLACK;
    Color colorConfirmarDois = BLACK;
    Color colorCriadoresFinal = BLACK;

    Rectangle verde = {320,250,20,20};
    Rectangle azul = {360,250,20,20};
    Rectangle purpura = {400,250,20,20};
    Rectangle gold = {440,250,20,20};
    Rectangle red = {480,250,20,20};

    Color clickedColor = DARKGRAY; // Inicialmente sem cor selecionada
    Color corPecaJogador1 = DARKGRAY;
    Color corPecaJogador2 = DARKGRAY;
    const char *colorMessage = "Selecione a cor da sua peça";  // Mensagem inicial
    int tamanhoTextSelecionarPeca = MeasureText("Selecione a cor da sua peça", 20);
    int textXSelecionar = (screenWidth - tamanhoTextSelecionarPeca)/2;

    Rectangle quadrado = { screenWidth / 2 - 100, screenHeight / 2 - 100, 200, 80 }; // Posição e tamanho
    float roundness = 0.6f; // Proporção de arredondamento (entre 0.0 e 1.0)
    int segments = 10;      // Número de segmentos para suavizar os cantos

    char nomePara1[MAX_INPUT_CHARS + 1] = "\0";
    char nomePara2[MAX_INPUT_CHARS + 1] = "\0";
    int letterCount = 0;

    Rectangle textBox = { 300, 195, 200, 30 };

    char nomeJogador1[100] = "\0";  // Variável para armazenar o texto exibido após o Enter
    char nomeJogador2[100] = "\0";  // Variável para armazenar o texto exibido após o Enter
    char nomeVencedor[100];
    

    int totalPecasJogador1 = 10;
    int totalPecasJogador2 = 10;

    Vector2 posicaoCirculos[] = {
        {219, 299}, {360, 299}, {501, 299},
            {289, 369}, {430, 369},
        {219, 440}, {360, 440}, {501, 440},
            {289, 510}, {430, 510},
        {219, 581}, {360, 581}, {501, 581},
            {70,70}, {650,70}
    };

    const int circleCount = sizeof(posicaoCirculos) / sizeof(posicaoCirculos[0]);
    const float largeCircleRadius = 50.0f;

    int origemX, origemY, destinoX, destinoY;
    char jogadorAtual = 'X';
    //                        0   1   2   3   4
    char tabuleiro[5][5] = {{'.','.','X','.','.'},//0
                            {'.',' ','X','X','.'},//1
                            {' ','Y',' ','X',' '},//2
                            {'.','Y','Y',' ','.'},//3
                            {'.','.','Y','.','.'}/*4*/};
                            
    Vector2 pecasPosicao1[10] = {
        posicaoCirculos[2],
        posicaoCirculos[4],
        posicaoCirculos[7],
        posicaoCirculos[9],

        posicaoCirculos[14],
        posicaoCirculos[14],
        posicaoCirculos[14],
        posicaoCirculos[14],
        posicaoCirculos[14],
        posicaoCirculos[14]

    };
    bool pieceSelected1[10] = {false,false,false,false, false,false,false,false,false,false};
    const int contarPeca1 = 10;
    Color corPeca1 = corPecaJogador1; 

    Vector2 pecasPosicao2[10] = {
        posicaoCirculos[3],
        posicaoCirculos[5],
        posicaoCirculos[8],
        posicaoCirculos[10],

        posicaoCirculos[14],
        posicaoCirculos[14],
        posicaoCirculos[14],
        posicaoCirculos[14],
        posicaoCirculos[14],
        posicaoCirculos[14]
    };
    bool pieceSelected2[10] = {false,false,false,false, false,false,false,false,false,false};
    const int contarPeca2 = 10;
    Color corPeca2 = corPecaJogador2;

    int turn = 1;  
    int pecasX, pecasY;
    int total1 = 6, total2 = 6;

    int pecasAtivas1 = 10, pecasAtivas2 = 10;
    bool repor1 = false, repor2 = false; // Flags de capturas
    bool pecaCapturada;
    char texto1[50], texto[50];

    Texture uma,duas,tres,quatro,cinco,seis,sete,oito,nove,dez,onze;
    uma = LoadTexture("./EstrelaVitoria0035.png");
    duas = LoadTexture("./EstrelaVitoria0025.png");
    tres = LoadTexture("./EstrelaVitoria0035.png");
    quatro = LoadTexture("./EstrelaVitoria0035.png");
    cinco = LoadTexture("./EstrelaVitoria.png");
    seis = LoadTexture("./EstrelaVitoria0035.png");
    sete = LoadTexture("./EstrelaVitoria0035.png");
    oito = LoadTexture("./EstrelaVitoria0035.png");
    nove = LoadTexture("./EstrelaVitoria0035.png");
    dez = LoadTexture("./EstrelaVitoria0015.png");
    onze = LoadTexture("./EstrelaVitoria0035.png");

    // Loop principal do jogo
    SetTargetFPS(60); // Limita a 60 frames por segundo, é só pra evitar o pc pipocar, vai q
    while (!WindowShouldClose()) {
        bool isMouseOverJogar = CheckCollisionPointRec(GetMousePosition(), jogar);
        bool isMouseOverCriadores = CheckCollisionPointRec(GetMousePosition(), criadores);
        bool isMouseOverRegras = CheckCollisionPointRec(GetMousePosition(), regras);
        bool isMouseOverHistorico = CheckCollisionPointRec(GetMousePosition(), historico); 
        bool isMouseOverVoltar = CheckCollisionPointRec(GetMousePosition(), voltar);
        bool isMouseOverConfirmar = CheckCollisionPointRec(GetMousePosition(), confirmar);
        bool isMouseOverConfirmarDois = CheckCollisionPointRec(GetMousePosition(), confirmarDois);
        bool isMouseOverCriadoresFinal = CheckCollisionPointRec(GetMousePosition(), criadoresfinal);

         //Definir um If para jogador1 e outro para jogador2
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            bool isMouseOverAzul = CheckCollisionPointRec(GetMousePosition(), azul);
            bool isMouseOverVerde = CheckCollisionPointRec(GetMousePosition(), verde);
            bool isMouseOverRed = CheckCollisionPointRec(GetMousePosition(), red);
            bool isMouseOverGold = CheckCollisionPointRec(GetMousePosition(), gold);
            bool isMouseOverPurpura = CheckCollisionPointRec(GetMousePosition(), purpura);
            if(janelaExibir == acaoJogar){
        
                if (isMouseOverAzul) {
                    corPecaJogador1 = BLUE;
                    colorMessage = "            Azul";
                }
                else if (isMouseOverVerde) {
                    corPecaJogador1 = GREEN;
                    colorMessage = "            Verde";
                }
                else if (isMouseOverRed) {
                    corPecaJogador1 = RED;
                    colorMessage = "            Vermelha";
                }
                else if (isMouseOverGold) {
                    corPecaJogador1 = GOLD;
                    colorMessage = "            Amarela";
                }
                else if (isMouseOverPurpura) {
                    corPecaJogador1 = PURPLE;
                    colorMessage = "            Purpura";
                }
                corPeca1 = corPecaJogador1;
            } else if (janelaExibir == acaoJogarDois){
                if (isMouseOverAzul) {
                    corPecaJogador2 = BLUE;
                    colorMessage = "            Azul";
                }
                else if (isMouseOverVerde) {
                    corPecaJogador2 = GREEN;
                    colorMessage = "            Verde";
                }
                else if (isMouseOverRed) {
                    corPecaJogador2 = RED;
                    colorMessage = "            Vermelha";
                }
                else if (isMouseOverGold) {
                    corPecaJogador2 = GOLD;
                    colorMessage = "            Amarela";
                }
                else if (isMouseOverPurpura) {
                    corPecaJogador2 = PURPLE;
                    colorMessage = "            Purpura";
                }
                corPeca2 = corPecaJogador2;
            }
        }

        if (isMouseOverJogar) {
            retColorJogar = DARKGRAY;
            colorJogar = WHITE;
        } else {
            retColorJogar = LIGHTGRAY;
            colorJogar = BLACK;
        }
        if (isMouseOverCriadores) {
            retColorCriadores = DARKGRAY;
            colorCriadores = WHITE;
        } else {
            retColorCriadores = LIGHTGRAY;
            colorCriadores = BLACK;
        }
        if (isMouseOverRegras) {
            retColorRegras = DARKGRAY;
            colorRegras = WHITE;
        } else {
            retColorRegras = LIGHTGRAY;
            colorRegras = BLACK;
        }
        if (isMouseOverHistorico) {
            retColorHistorico = DARKGRAY;
            colorHistorico = WHITE;
        } else {
            retColorHistorico = LIGHTGRAY;
            colorHistorico = BLACK;
        }
        if(isMouseOverVoltar){
            retColorVoltar = DARKGRAY;
            colorVoltar = WHITE;
        } else {
            retColorVoltar = LIGHTGRAY;
            colorVoltar = BLACK;
        }
        if(isMouseOverConfirmar){
            retColorConfirmar = DARKGRAY;
            colorConfirmar = WHITE;
        } else {
            retColorConfirmar = LIGHTGRAY;
            colorConfirmar = BLACK;
        }
        if(isMouseOverConfirmar){
            retColorConfirmarDois = DARKGRAY;
            colorConfirmarDois = WHITE;
        } else {
            retColorConfirmarDois = LIGHTGRAY;
            colorConfirmarDois = BLACK;
        }
        if(isMouseOverCriadoresFinal){
            retColorCriadoresFinal = DARKGRAY;
            colorCriadoresFinal = WHITE;
        } else {
            retColorCriadoresFinal = LIGHTGRAY;
            colorCriadoresFinal = BLACK;
        }

        if(janelaExibir == acaoQueah){
            // Verifica o clique do mouse; essa parte deu trabalho kkkk
            if(!repor1 && !repor2){
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    Vector2 mousePosition = GetMousePosition();
                    bool pecaFoiMovida = false;

                    // Verifica se alguma peça da lista 1 (vermelha) está selecionada no turno 1
                    if (turn == 1) {
                        for (int i = 0; i < contarPeca1; i++) {
                            if (pieceSelected1[i]) {
                                // Tenta mover a peça selecionada da lista 1 para um grande círculo
                                origemX = pecasPosicao1[i].x; // Armazena a origem uma para X e a outra para Y
                                origemY = pecasPosicao1[i].y;
                                for (int j = 0; j < circleCount; j++) {
                                    if (IsPointInCircle(mousePosition, posicaoCirculos[j], largeCircleRadius) &&
                                        !IsPositionOccupied(posicaoCirculos[j], pecasPosicao1, pecasPosicao2, contarPeca1, contarPeca2)) {
                                        destinoX = posicaoCirculos[j].x; // Armazena o destino agora as dados serão convertidos ai embaixo
                                        destinoY = posicaoCirculos[j].y;
                                        // Verifica se há uma peça adversária no destino e Atualize as verificações de captura

                                        if (movimentoValido(tabuleiro, origemX, origemY, destinoX, destinoY, jogadorAtual)) {
                                            realizarMovimento(tabuleiro, origemX, origemY, destinoX, destinoY);
                                            pecaCapturada = capturarPeca(tabuleiro, origemX, origemY, destinoX, destinoY, jogadorAtual, pecasX, pecasY, pecasAtivas1, pecasAtivas2);

                                            if (pecaCapturada) {
                                                int x = conversorLixeira(pecasX, pecasY, true);//Aqui acontece a conversao das peças para a lixeira e elas saem da tela logo em seguida
                                                int y = conversorLixeira(pecasX, pecasY);
                                                for (int p = 0; p < contarPeca2; p++) {
                                                    if (pecasPosicao2[p].x == x && pecasPosicao2[p].y == y){
                                                        pecasPosicao2[p].x = 70; // Peça movida para lixeira
                                                        pecasPosicao2[p].y = 70;
                                                    }
                                                }
                                                if(total2 > 0)repor2 = true;
                                            }
                                            alternarJogador(jogadorAtual);           // Alterna o turno, se for X vira Y...
                                            pecasPosicao1[i] = posicaoCirculos[j]; // Move a peça para circulo invisivel
                                            pieceSelected1[i] = false;               // Deseleciona a peça
                                            pecaFoiMovida = true;
                                        }
                                        break;
                                    }
                                }
                            }
                            if (pecaFoiMovida) break;
                        }

                        if (!pecaFoiMovida) {
                            // Seleciona uma peça da lista 1 se o clique estiver dentro dela
                            for (int i = 0; i < contarPeca1; i++) {
                                if (IsPointInCircle(mousePosition, pecasPosicao1[i], 10.0f)) {
                                    // Deseleciona todas as outras peças da lista 1
                                    for (int k = 0; k < contarPeca1; k++) {
                                        pieceSelected1[k] = false;
                                    }
                                    pieceSelected1[i] = true; // Seleciona a peça clicada da lista 1
                                    break;
                                }
                            }
                        }
                    }
                    // Verifica se alguma peça da lista 2 (azul) está selecionada no turno 2
                    if (turn == 2 && !pecaFoiMovida) {
                        for (int i = 0; i < contarPeca2; i++) {
                            if (pieceSelected2[i]) {
                                // Tenta mover a peça selecionada da lista 2 para um grande círculo
                                origemX = pecasPosicao2[i].x; // Armazena a origem uma para X e a outra para Y
                                origemY = pecasPosicao2[i].y;
                                for (int j = 0; j < circleCount; j++) {
                                    if (IsPointInCircle(mousePosition, posicaoCirculos[j], largeCircleRadius) &&
                                        !IsPositionOccupied(posicaoCirculos[j], pecasPosicao1, pecasPosicao2, contarPeca1, contarPeca2)) {
                                        destinoX = posicaoCirculos[j].x; // Armazena o destino agora as dados serão convertidos ai embaixo
                                        destinoY = posicaoCirculos[j].y;
                                        // Verifica se há uma peça adversária no destino e Atualize as verificações de captura

                                        if (movimentoValido(tabuleiro, origemX, origemY, destinoX, destinoY, jogadorAtual)) {
                                            realizarMovimento(tabuleiro, origemX, origemY, destinoX, destinoY);
                                            pecaCapturada = capturarPeca(tabuleiro, origemX, origemY, destinoX, destinoY, jogadorAtual, pecasX, pecasY, pecasAtivas1, pecasAtivas2);
                                            if (pecaCapturada) {
                                                int x = conversorLixeira(pecasX, pecasY, true); // Aqui acontece a conversao das peças para a lixeira e elas saem da tela logo em seguida
                                                int y = conversorLixeira(pecasX, pecasY);
                                                for (int p = 0; p < contarPeca1; p++) {
                                                    if (pecasPosicao1[p].x == x && pecasPosicao1[p].y == y){
                                                        pecasPosicao1[p].x = 70; // Peça movida para lixeira
                                                        pecasPosicao1[p].y = 70;
                                                    }
                                                }
                                                if(total1 > 0) repor1 = true;
                                            }
                                            alternarJogador(jogadorAtual); // Alterna o turno, se for Y vira X...
                                            pecasPosicao2[i] = posicaoCirculos[j]; // Move a peça para circulo invisivel
                                            pieceSelected2[i] = false;               // Deseleciona a peça
                                            pecaFoiMovida = true;
                                        }
                                        break;
                                    }
                                }
                            }
                            if (pecaFoiMovida) break;
                        }
                        if (!pecaFoiMovida) {
                            // Seleciona uma peça da lista 2 se o clique estiver dentro dela
                            for (int i = 0; i < contarPeca2; i++) {
                                if (IsPointInCircle(mousePosition, pecasPosicao2[i], 10.0f)) {
                                    // Deseleciona todas as outras peças da lista 2
                                    for (int k = 0; k < contarPeca2; k++) {
                                        pieceSelected2[k] = false;
                                    }
                                    pieceSelected2[i] = true; // Seleciona a peça clicada da lista 2
                                    break;
                                }
                            }
                        }
                    }
                    // Alterna os turnos
                    if (pecaFoiMovida) {
                        if (turn == 1) {
                            turn = 2; // Passa para o turno 2 
                        } else {
                            turn = 1; // Passa para o turno 1 
                        }
                    }
                }
            } else if (repor1){ //Primeiro verifica se alguma peça do jogador1 foi comida e depois jogador2
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePosition = GetMousePosition();
                    for (int j = 0; j < circleCount; j++) {
                        if (IsPointInCircle(mousePosition, posicaoCirculos[j], largeCircleRadius)) {
                            int novaPosicaoX, novaPosicaoY;
                            novaPosicaoX = posicaoCirculos[j].x; // Conversão do clique na tela para a posição no tabuleiro guia
                            novaPosicaoY = posicaoCirculos[j].y;
                            if (verificarEReporPecas(tabuleiro, jogadorAtual, novaPosicaoX, novaPosicaoY, total1, total2)){
                                for (int p = 0; p < contarPeca1; p++) {
                                    if (pecasPosicao1[p].x == posicaoCirculos[14].x && pecasPosicao1[p].y == posicaoCirculos[14].y){
                                        pecasPosicao1[p].x = posicaoCirculos[j].x; // São reposicionadas 
                                        pecasPosicao1[p].y = posicaoCirculos[j].y;
                                        repor1 = false;
                                        alternarJogador(jogadorAtual);
                                        if (turn == 1) {
                                            turn = 2; // Passa para o turno 2 
                                        } else {
                                            turn = 1; // Passa para o turno 1 
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePosition = GetMousePosition();
                    for (int j = 0; j < circleCount; j++) {
                        if (IsPointInCircle(mousePosition, posicaoCirculos[j], largeCircleRadius)) {
                            int novaPosicaoX, novaPosicaoY;
                            novaPosicaoX = posicaoCirculos[j].x; // Conversão do clique na tela para a posição no tabuleiro guia
                            novaPosicaoY = posicaoCirculos[j].y;
                            if (verificarEReporPecas(tabuleiro, jogadorAtual, novaPosicaoX, novaPosicaoY, total1, total2)){
                                for (int p = 0; p < contarPeca2; p++) {
                                    if (pecasPosicao2[p].x == posicaoCirculos[14].x && pecasPosicao2[p].y == posicaoCirculos[14].y){
                                        pecasPosicao2[p].x = posicaoCirculos[j].x; // São reposicionadas 
                                        pecasPosicao2[p].y = posicaoCirculos[j].y;
                                        repor2 = false;
                                        alternarJogador(jogadorAtual);
                                        if (turn == 1) {
                                            turn = 2; // Passa para o turno 2 
                                        } else {
                                            turn = 1; // Passa para o turno 1 
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if(pecasAtivas1 > 0 && pecasAtivas2 < 1){
                const char *nome3 = nomeJogador1;
                escreverNomeVencedor(nome3);
                janelaExibir = acaoVitoria;
            }else if (pecasAtivas1 < 1 && pecasAtivas2 > 0){
                const char *nome3 = nomeJogador2;
                escreverNomeVencedor(nome3);
                janelaExibir = acaoVitoria;
            }
        }
        if(janelaExibir == acaoJogarDois){
            int key = GetCharPressed();
            while (key > 0){
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS)){
                    nomePara2[letterCount] = (char)key;
                    nomePara2[letterCount + 1] = '\0';
                    letterCount++;
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE)){
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                nomePara2[letterCount] = '\0';
            }
            if (IsKeyPressed(KEY_ENTER)){
                strcpy(nomeJogador2, nomePara2);  // Copia o texto de name para JOGADOR2
                const char *nome2 = nomeJogador2;
                escreverNomeJogador2(nome2);
                letterCount = 0;
            }
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                Vector2 mousePosition = GetMousePosition();
                if (CheckCollisionPointRec(mousePosition, confirmarDois)) colorMessage = "Selecione a cor da sua peça";
                if (CheckCollisionPointRec(mousePosition, confirmarDois)) janelaExibir = acaoQueah;
            }
        }
        if(janelaExibir == acaoJogar){
            int key = GetCharPressed();
            while (key > 0){
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS)){
                    nomePara1[letterCount] = (char)key;
                    nomePara1[letterCount + 1] = '\0';
                    letterCount++;
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE)){
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                nomePara1[letterCount] = '\0';
            }
            if (IsKeyPressed(KEY_ENTER)){
                strcpy(nomeJogador1, nomePara1);  // Copia o texto de name para JOGADOR1
                const char *nome1 = nomeJogador1;
                escreverNomeJogador1(nome1);
                letterCount = 0;
            }
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                Vector2 mousePosition = GetMousePosition();
                if (CheckCollisionPointRec(mousePosition, confirmar)) colorMessage = "Selecione a cor da sua peça";
                if (CheckCollisionPointRec(mousePosition, confirmar)) janelaExibir = acaoJogarDois;
            }
        }

        if(janelaExibir == acaoInicio){
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 mousePosition = GetMousePosition();
                if (CheckCollisionPointRec(mousePosition, jogar)) janelaExibir = acaoJogar;
                if (CheckCollisionPointRec(mousePosition, criadores)) janelaExibir = acaoCriadores;
                if (CheckCollisionPointRec(mousePosition, regras)) janelaExibir = acaoRegras;
                if(CheckCollisionPointRec(mousePosition, historico)) janelaExibir = acaoHistorico;
            }
        } else {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                Vector2 mousePosition = GetMousePosition();
                if(CheckCollisionPointRec(mousePosition, voltar)) janelaExibir = acaoInicio;
            }
        }
        if(janelaExibir == acaoVitoria){
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 mousePosition = GetMousePosition();
                if (CheckCollisionPointRec(mousePosition, criadoresfinal)) janelaExibir = acaoCriadores;
            }
        }
        int tamanhoQueah = MeasureText("Queah", 150);
        int textQ = (screenWidth - tamanhoQueah)/2;

        BeginDrawing();
        ClearBackground(WHITE);

        switch (janelaExibir) {
            case acaoInicio:
                DrawText("Queah", textQ, 150, 150, BLACK);
                DrawRectangleRounded(jogar, roundness, segments, retColorJogar);
                DrawRectangleRounded(criadores, roundness, segments, retColorCriadores);
                DrawRectangleRounded(regras, roundness, segments, retColorRegras);
                DrawRectangleRounded(historico, roundness, segments, retColorHistorico);

                DrawTextEx(font, "Jogar", (Vector2){ jogar.x + 100, jogar.y + 25 }, 40, 2, colorJogar);
                DrawTextEx(font, "Criadores", (Vector2){ criadores.x + 50, criadores.y + 25 }, 20, 2, colorCriadores);
                DrawTextEx(font, "Regras", (Vector2){ regras.x + 65, regras.y + 25 }, 20, 2, colorRegras);
                DrawTextEx(font, "Historico", (Vector2){historico.x + 60, historico.y + 25}, 20, 2, colorHistorico);
                break;

            case acaoJogar:
                AbaJogadorUm();
                DrawRectangleRec(verde,GREEN);
                DrawRectangleRec(azul,BLUE);
                DrawRectangleRec(purpura,PURPLE);
                DrawRectangleRec(gold,GOLD);
                DrawRectangleRec(red,RED);
                DrawText(colorMessage, textXSelecionar, 150, 20, corPecaJogador1);

                DrawRectangleRounded(voltar, roundness, segments, retColorVoltar);
                DrawText("Voltar", voltar.x + 18, voltar.y + 7, 20, colorVoltar);

                DrawRectangleRounded(confirmar, roundness, segments, retColorConfirmar);
                DrawTextEx(font, "Confirmar", (Vector2){ confirmar.x + 55, confirmar.y + 40 }, 20, 2, colorConfirmar);

                DrawRectangleRec(textBox, LIGHTGRAY);
                DrawText(nomePara1, (int)textBox.x + 5, (int)textBox.y + 8, 20, MAROON);

                // Exibe o texto abaixo da caixa de entrada após pressionar Enter
                if (nomeJogador1[0] != '\0')
                {
                    DrawText(TextFormat("Nome: %s", nomeJogador1), 280, 280, 20, DARKGREEN);
                }
                break;

                case acaoJogarDois:
                AbaJogadorDois();
                DrawRectangleRec(verde,GREEN);
                DrawRectangleRec(azul,BLUE);
                DrawRectangleRec(purpura,PURPLE);
                DrawRectangleRec(gold,GOLD);
                DrawRectangleRec(red,RED);
                DrawText(colorMessage, textXSelecionar, 150, 20, corPecaJogador2);

                DrawRectangleRounded(voltar, roundness, segments, retColorVoltar);
                DrawText("Voltar", voltar.x + 18, voltar.y + 7, 20, colorVoltar);

                DrawRectangleRounded(confirmarDois, roundness, segments, retColorConfirmarDois);
                DrawTextEx(font, "Confirmar", (Vector2){ confirmarDois.x + 55, confirmarDois.y + 40 }, 20, 2, colorConfirmarDois);

                DrawRectangleRec(textBox, LIGHTGRAY);
                DrawText(nomePara2, (int)textBox.x + 5, (int)textBox.y + 8, 20, MAROON);

                // Exibe o texto abaixo da caixa de entrada após pressionar Enter
                if (nomeJogador2[0] != '\0')
                {
                    DrawText(TextFormat("Nome: %s", nomeJogador2), 280, 280, 20, DARKGREEN);
                }
                break;
            case acaoQueah:
                AbaQueah();
                DrawRectangleRounded(voltar, roundness, segments, retColorVoltar);
                DrawText("Voltar", voltar.x + 18, voltar.y + 7, 20, colorVoltar);

                DrawRectangleRec(tabuleiroTela, LIGHTGRAY);
                DrawRectanglePro(quadrado1, origin, rotation, BLACK);
                DrawRectanglePro(quadrado2, origin, rotation, BLACK);
                DrawRectanglePro(quadrado3, origin, rotation, BLACK);

                DrawRectanglePro(quadrado4, origin, rotation, WHITE);
                DrawRectanglePro(quadrado5, origin, rotation, WHITE);

                DrawRectanglePro(quadrado6, origin, rotation, BLACK);
                DrawRectanglePro(quadrado7, origin, rotation, BLACK);
                DrawRectanglePro(quadrado8, origin, rotation, BLACK);
                DrawRectanglePro(quadrado9, origin, rotation, BLACK);
                DrawRectanglePro(quadrado10, origin, rotation, BLACK);
                DrawRectanglePro(quadrado11, origin, rotation, BLACK);

                DrawRectanglePro(quadrado12, origin, rotation, WHITE);
                DrawRectanglePro(quadrado13, origin, rotation, WHITE);

                // Desenha as peças da lista 1 
                for (int i = 0; i < contarPeca1; i++) {
                    if (pecasPosicao1[i].y != 70) {  // Se a peça não foi removida, desenha ela
                        DrawCircleV(pecasPosicao1[i], 20.0f, pieceSelected1[i] ? DARKGREEN : corPeca1);
                    }
                }

                // Desenha as peças da lista 2 
                for (int i = 0; i < contarPeca2; i++) {
                    if (pecasPosicao2[i].y != 70) {  // Se a peça não foi removida, desenha ela
                        DrawCircleV(pecasPosicao2[i], 20.0f, pieceSelected2[i] ? DARKGREEN : corPeca2);
                    }
                }

                DrawText("Vez do jogador ", 70, 730, 20, BLACK);
                if(turn == 1){
                    DrawText(TextFormat("%s", nomeJogador1), 235, 730, 20, BLACK);
                }else{
                    DrawText(TextFormat("%s", nomeJogador2), 235, 730, 20, BLACK);
                }

                if(repor1){
                    DrawText("Clique para repor peça ",71,150,20,DARKGRAY);
                    DrawText(TextFormat("%s", nomeJogador1), 320, 150, 20, DARKGRAY);
                }else if (repor2){
                    DrawText("Clique para repor peça ",71,150,20,DARKGRAY);
                    DrawText(TextFormat("%s", nomeJogador2), 320, 150, 20, DARKGRAY);
                }
                if(pecasAtivas1 > 0 && pecasAtivas2 < 1 || pecasAtivas1 < 1 && pecasAtivas2 > 0){
                    janelaExibir = acaoVitoria;
                }

                sprintf(texto1, "Peças ativas: %d", pecasAtivas1);
                DrawText(texto1, 70, 100, 20, BLACK);
                sprintf(texto, "Peças ativas: %d", pecasAtivas2);
                DrawText(texto, screenWidth/2, 100, 20, BLACK);

                break;
            case acaoCriadores:
                AbaCriadores();
                DrawRectangleRounded(voltar, roundness, segments, retColorVoltar);
                DrawText("Voltar", voltar.x + 18, voltar.y + 7, 20, colorVoltar);
                break;
            case acaoRegras:
                AbaRegras();
                DrawRectangleRounded(voltar, roundness, segments, retColorVoltar);
                DrawText("Voltar", voltar.x + 18, voltar.y + 7, 20, colorVoltar);
                break;
            case acaoHistorico:{
                AbaHistorico();
                DrawRectangleRounded(voltar, roundness, segments, retColorVoltar);
                DrawText("Voltar", voltar.x + 18, voltar.y + 7, 20, colorVoltar);
                DrawRectangleRec(fundoHistorico, LIGHTGRAY);
                
                DrawText("Jogador 1", 85,155,20,BLACK);
                DrawText("||", 240,155,20,BLACK);
                DrawText("Jogador 2", 305,155,20,BLACK);
                DrawText("||", 450,155,20,BLACK);
                DrawText("Vencedor", 500,155,20,BLACK);
                char linhasPara1[MAX_LINHAS][MAX_LINHA] = {0};
                char linhasPara2[MAX_LINHAS][MAX_LINHA] = {0};
                char linhasPara3[MAX_LINHAS][MAX_LINHA] = {0};
                lerConteudoDoArquivoPara1(linhasPara1);
                lerConteudoDoArquivoPara2(linhasPara2);
                lerConteudoDoArquivoPara3(linhasPara3);
                int yPos1 = 185;  // Posição inicial para desenhar as linhas
                for (int i = 0; i < MAX_LINHAS; i++) {
                    DrawText(linhasPara1[i], 85, yPos1, 20, DARKGREEN);
                    yPos1 += 30;  // Incrementa a posição para a próxima linha
                }
                int yPos2 = 185;  // Posição inicial para desenhar as linhas
                for (int i = 0; i < MAX_LINHAS; i++) {
                    DrawText(linhasPara2[i], 305, yPos2, 20, DARKGREEN);
                    yPos2 += 30;  // Incrementa a posição para a próxima linha
                }
                int yPos3 = 185;  // Posição inicial para desenhar as linhas
                for (int i = 0; i < MAX_LINHAS; i++) {
                    DrawText(linhasPara3[i], 500, yPos3, 20, DARKGREEN);
                    yPos3 += 30;  // Incrementa a posição para a próxima linha
                }
                break;
            }
            case acaoVitoria:
                AbaVencedor();
                DrawRectangleRounded(criadoresfinal, roundness, segments, retColorCriadoresFinal);
                DrawTextEx(font, "Criadores", (Vector2){ criadoresfinal.x + 50, criadoresfinal.y + 25 }, 20, 2, colorCriadoresFinal);

                DrawTexture(uma,90,80, WHITE);
                DrawTexture(duas,50,250, WHITE);
                DrawTexture(tres,50,600, WHITE);
                DrawTexture(quatro,300,680, WHITE);
                DrawTexture(cinco,280,150, WHITE);

                DrawTexture(seis,600,400, WHITE);
                DrawTexture(sete,600,70, WHITE);
                DrawTexture(oito,500,500, WHITE);
                DrawTexture(nove,580,700, WHITE);
                DrawTexture(dez,280,500, WHITE);

                DrawTexture(onze,100,400, WHITE);

                DrawRectangleRounded(voltar, roundness, segments, retColorVoltar);
                DrawText("Voltar", voltar.x + 18, voltar.y + 7, 20, colorVoltar);

                if (pecasAtivas1 > 0 && pecasAtivas2 < 1) {
                    sprintf(texto, "Jogador %s venceu!!!", nomeJogador1);
                    int tamanhoTextGanhador = MeasureText(texto, 40);
                    int textXGanhador = (screenWidth - tamanhoTextGanhador) / 2;
                    DrawText(texto, textXGanhador, 300, 40, BLACK);
                } else if(pecasAtivas1 < 1 && pecasAtivas2 > 0){
                    sprintf(texto, "Jogador %s venceu!!!", nomeJogador2);
                    int tamanhoTextGanhador = MeasureText(texto, 40);
                    int textXGanhador = (screenWidth - tamanhoTextGanhador) / 2;
                    DrawText(texto, textXGanhador, 300, 40, BLACK);
                }
                int tamanhoParabens = MeasureText("Parabéns!", 30);
                int textXParabens = (screenWidth - tamanhoParabens) / 2;
                DrawText("Parabéns!",textXParabens, 370, 30, BLACK);
                
                break;
        }
       
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
//cc jogolinus2.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

// Função para verificar se uma posição está dentro de um círculo
bool IsPointInCircle(Vector2 point, Vector2 circleCenter, float radius) {
    float distance = sqrt(pow(point.x - circleCenter.x, 2) + pow(point.y - circleCenter.y, 2));
    return distance <= radius;
}

int conversorTabuleiro(int fimX, int fimY, bool tipoXouY){
    int convertidoX;
    if(fimX == 501 && fimY == 299)convertidoX = 0;

    if(fimX == 360 && fimY == 299)convertidoX = 1;
    if(fimX == 430 && fimY == 369)convertidoX = 1;
    if(fimX == 501 && fimY == 440)convertidoX = 1;

    if(fimX == 219 && fimY == 299)convertidoX = 2;
    if(fimX == 289 && fimY == 369)convertidoX = 2;
    if(fimX == 360 && fimY == 440)convertidoX = 2;
    if(fimX == 430 && fimY == 510)convertidoX = 2;
    if(fimX == 501 && fimY == 581)convertidoX = 2;

    if(fimX == 219 && fimY == 440)convertidoX = 3;
    if(fimX == 289 && fimY == 510)convertidoX = 3;
    if(fimX == 360 && fimY == 581)convertidoX = 3;

    if(fimX == 219 && fimY == 581)convertidoX = 4;

    return convertidoX;
}
int conversorTabuleiro(int fimX, int fimY){
    int convertidoY;
    if(fimX == 501 && fimY == 299)convertidoY = 2;

    if(fimX == 360 && fimY == 299)convertidoY = 1;
    if(fimX == 430 && fimY == 369)convertidoY = 2;
    if(fimX == 501 && fimY == 440)convertidoY = 3;

    if(fimX == 219 && fimY == 299)convertidoY = 0;
    if(fimX == 289 && fimY == 369)convertidoY = 1;
    if(fimX == 360 && fimY == 440)convertidoY = 2;
    if(fimX == 430 && fimY == 510)convertidoY = 3;
    if(fimX == 501 && fimY == 581)convertidoY = 4;


    if(fimX == 219 && fimY == 440)convertidoY = 1;
    if(fimX == 289 && fimY == 510)convertidoY = 2;
    if(fimX == 360 && fimY == 581)convertidoY = 3;


    if(fimX == 219 && fimY == 581)convertidoY = 2;

    return convertidoY;
}

int conversorLixeira(int posX, int posY, bool tipoXouY){
    int convertidoX;
    if(posX == 0 && posY == 2)convertidoX = 501;

    if(posX == 1 && posY == 1)convertidoX = 360;
    if(posX == 1 && posY == 2)convertidoX = 430;
    if(posX == 1 && posY == 3)convertidoX = 501;

    if(posX == 2 && posY == 0)convertidoX = 219;
    if(posX == 2 && posY == 1)convertidoX = 289;
    if(posX == 2 && posY == 2)convertidoX = 360;
    if(posX == 2 && posY == 3)convertidoX = 430;
    if(posX == 2 && posY == 4)convertidoX = 501;

    if(posX == 3 && posY == 1)convertidoX = 219;
    if(posX == 3 && posY == 2)convertidoX = 289;
    if(posX == 3 && posY == 3)convertidoX = 360;

    if(posX == 4 && posY == 2)convertidoX = 219;

    return convertidoX;
}
int conversorLixeira(int posX, int posY){
    int convertidoY;
    if(posX == 0 && posY == 2)convertidoY = 299;

    if(posX == 1 && posY == 1)convertidoY = 299;
    if(posX == 1 && posY == 2)convertidoY = 369;
    if(posX == 1 && posY == 3)convertidoY = 440;

    if(posX == 2 && posY == 0)convertidoY = 299;
    if(posX == 2 && posY == 1)convertidoY = 369;
    if(posX == 2 && posY == 2)convertidoY = 440;
    if(posX == 2 && posY == 3)convertidoY = 510;
    if(posX == 2 && posY == 4)convertidoY = 581;

    if(posX == 3 && posY == 1)convertidoY = 440;
    if(posX == 3 && posY == 2)convertidoY = 510;
    if(posX == 3 && posY == 3)convertidoY = 581;

    if(posX == 4 && posY == 2)convertidoY = 581;

    return convertidoY;
}

bool movimentoValido(char tabuleiro[5][5], int paraX, int paraY, int fimX, int fimY, char jogador) {
    int origemX,origemY,destinoX,destinoY;

    origemX = conversorTabuleiro(paraX,paraY, true);
    origemY = conversorTabuleiro(paraX,paraY);

    destinoX = conversorTabuleiro(fimX,fimY, true);
    destinoY = conversorTabuleiro(fimX,fimY);

    // Verificar se as coordenadas estão dentro dos limites do tabuleiro
    if (origemX < 0 || origemX >= 5 || origemY < 0 || origemY >= 5 || destinoX < 0 || destinoX >= 5 || destinoY < 0 || destinoY >= 5)
        return false; // Fora do tabuleiro

    // Verificar se a origem tem a peça do jogador
    if (tabuleiro[origemX][origemY] != jogador)
        return false; // Não é uma peça do jogador

    // Verificar se o destino é uma casa válida e está vazia
    if (tabuleiro[destinoX][destinoY] != ' ')
        return false; // Destino não está vazio

    // Verificar se o movimento é válido (uma casa ou captura)
    int deltaX = abs(destinoX - origemX);
    int deltaY = abs(destinoY - origemY);

    // Movimento simples: uma casa ortogonal
    if ((deltaX == 1 && deltaY == 0) || (deltaX == 0 && deltaY == 1))
        return true;

    // Movimento de captura: duas casas e há uma peça adversária no meio
    if ((deltaX == 2 && deltaY == 0) || (deltaX == 0 && deltaY == 2)) {
        int meioX = origemX + (destinoX - origemX) / 2;
        int meioY = origemY + (destinoY - origemY) / 2;
        if (tabuleiro[meioX][meioY] != jogador && tabuleiro[meioX][meioY] != ' ')
            return true; // Movimento de captura válido
    }

    return false; // Movimento inválido
}

void realizarMovimento(char tabuleiro[5][5], int paraX, int paraY, int fimX, int fimY) {
    int origemX,origemY,destinoX,destinoY;

    origemX = conversorTabuleiro(paraX,paraY, true);
    origemY = conversorTabuleiro(paraX,paraY);

    destinoX = conversorTabuleiro(fimX,fimY, true);
    destinoY = conversorTabuleiro(fimX,fimY);

    tabuleiro[destinoX][destinoY] = tabuleiro[origemX][origemY];//Move a peça
    tabuleiro[origemX][origemY] = ' ';//Limpa o local de origem
}

void alternarJogador(char &jogadorAtual) {
    jogadorAtual = (jogadorAtual == 'X') ? 'Y' : 'X';
}

bool capturarPeca(char tabuleiro[5][5], int paraX, int paraY, int fimX, int fimY, char jogador, int &pecasX, int &pecasY,int &pecasAtivas1, int &pecasAtivas2) {
    int origemX,origemY,destinoX,destinoY;

    origemX = conversorTabuleiro(paraX,paraY, true);
    origemY = conversorTabuleiro(paraX,paraY);

    destinoX = conversorTabuleiro(fimX,fimY, true);
    destinoY = conversorTabuleiro(fimX,fimY);

    int deltaX = destinoX - origemX;
    int deltaY = destinoY - origemY;

    // Checar se o movimento é válido para captura
    if ((abs(deltaX) == 2 && abs(deltaY) == 0) || (abs(deltaX) == 0 && abs(deltaY) == 2)) {
        int meioX = origemX + deltaX / 2;
        int meioY = origemY + deltaY / 2;

        if (tabuleiro[meioX][meioY] != jogador && tabuleiro[meioX][meioY] != ' ') {
            if(tabuleiro[meioX][meioY] == 'X') pecasAtivas1--;
            if(tabuleiro[meioX][meioY] == 'Y') pecasAtivas2--;
            // Remover a peça do adversário
            tabuleiro[meioX][meioY] = ' ';
            pecasX = meioX; // Atualiza posição da peça capturada
            pecasY = meioY;
            return true; // Captura válida
        }
    }

    return false; // Sem captura
}

bool verificarEReporPecas(char tabuleiro[5][5], char jogadorPerdeu, int fimX, int fimY, int &total1, int &total2){
    int destinoX,destinoY;

    destinoX = conversorTabuleiro(fimX,fimY, true);
    destinoY = conversorTabuleiro(fimX,fimY);

    if (total1 > 0 && jogadorPerdeu == 'X'){
        if (tabuleiro[destinoX][destinoY] == ' '){
            tabuleiro[destinoX][destinoY] = 'X';
            total1--;
            return true;
        }else{
            return false;
        }
    }
    else if (total2 > 0 && jogadorPerdeu == 'Y'){
        if (tabuleiro[destinoX][destinoY] == ' '){
            tabuleiro[destinoX][destinoY] = 'Y';
            total2--;
            return true;
        }else{
            return false;
        }
    }
}
// Função para verificar se uma posição está ocupada por outra peça
bool IsPositionOccupied(Vector2 position, Vector2 pecasPosicao1[], Vector2 pecasPosicao2[], int contarPeca1, int contarPeca2) {
    // Verifica se a posição está ocupada por uma peça da lista 1
    for (int i = 0; i < contarPeca1; i++) {
        if (position.x == pecasPosicao1[i].x && position.y == pecasPosicao1[i].y) {
            return true;
        }
    }
    // Verifica se a posição está ocupada por uma peça da lista 2
    for (int i = 0; i < contarPeca2; i++) {
        if (position.x == pecasPosicao2[i].x && position.y == pecasPosicao2[i].y) {
            return true;
        }
    }
    return false; // A posição não está ocupada
}

void AbaJogadorUm(){
    int tamanhoText = MeasureText("Queah", 40);
    int textX = (720 - tamanhoText)/2;
    DrawText("Queah", textX, 10, 40, BLACK);
    DrawText("Nome do Jogador 1: ",100,200,20, DARKGRAY);
    DrawText("Selecione uma cor: ",100,250,20,DARKGRAY);
}

void AbaJogadorDois(){
    int tamanhoText = MeasureText("Queah", 40);
    int textX = (720 - tamanhoText)/2;
    DrawText("Queah", textX, 10, 40, BLACK);
    DrawText("Nome do Jogador 2: ",100,200,20, DARKGRAY);
    DrawText("Selecione uma cor: ",100,250,20,DARKGRAY);
}

void AbaQueah(){
    int tamanhoText = MeasureText("Queah", 40);
    int textX = (720 - tamanhoText)/2;
    DrawText("Queah", textX, 10, 40, BLACK);

    DrawText("Jogador ", 70,70,20,BLACK);
    DrawText("Jogador ", 720/2, 70,20,BLACK);
}

void AbaVencedor(){
    int tamanhoText = MeasureText("Queah", 40);
    int textX = (720 - tamanhoText)/2;
    DrawText("Queah", textX, 10, 40, BLACK);
}

void AbaCriadores(){
    int tamanhoText = MeasureText("Queah", 40);
    int textX = (720 - tamanhoText)/2;
    DrawText("Queah", textX, 10, 40, BLACK);
    int tamanhoCria = MeasureText("Criadores", 40);
    int textC = (720 - tamanhoCria)/2;
    DrawText("Criadores", textC,100,40, BLACK);
    const char* texto = "• Arthur Soares Barbosa Leal\n• Yami Nascimento Rodrigues\n• Yasmim Passos Alves De Araujo\n• Matheus Santiago Silva\n• Savio Lourenco De Oliveira Lira \n• Wallace Da Silva Barreto";

    Vector2 position = { 175, 250 };
    DrawTextEx(GetFontDefault(), texto, position, 20, 2.0f, BLACK);

    DrawText("Esperamos que a prova esteja mais facil.", 50, 750, 20, BLACK);
}

void AbaRegras(){
    int tamanhoText = MeasureText("Queah", 40);
    int textX = (720 - tamanhoText)/2;
    DrawText("Queah", textX, 10, 40, BLACK);
    int tamanhoCria = MeasureText("Regras", 50);
    int textC = (720 - tamanhoCria)/2;
    DrawText("Regras", textC, 100, 50, BLACK);
    const char* texto = "   Em Queah, cada jogador tem 10 peças: 4 começam \nno tabuleiro e 6 ficam na reserva.\n\n   As peças movem-se em linhas diagonais para casas\nvazias, e capturam pulando sobre peças adversárias\npara uma casa vazia logo depois.\n\n   Sempre deve haver 4 peças no tabuleiro, e peças \ncapturadas são repostas com as reservas, se disponíveis. \n   Se um jogador não tiver reservas, joga apenas com\nas peças restantes no tabuleiro.\n\n   O objetivo é capturar todas as peças do adversário\npara vencer o jogo.";
    Vector2 position = { 75, 200 };
    DrawTextEx(GetFontDefault(), texto, position, 20, 2.0f, BLACK);
    DrawText("Bom jogo!!", 50, 750, 20, BLACK);
}
void AbaHistorico(){
    int tamanhoText = MeasureText("Queah", 40);
    int textX = (720 - tamanhoText)/2;
    DrawText("Queah", textX, 10, 40, BLACK);
    int tamanhoHistorico = MeasureText("Histórico", 50);
    int tamH = (720 - tamanhoHistorico) / 2;
    DrawText("Histórico", tamH, 90, 50, BLACK);
}

void escreverNomeJogador1(const char *nome){
    FILE *arquivo = fopen("jogador1.txt", "a");
    if (arquivo != NULL) {
      // Escreva no arquivo
        fprintf(arquivo, "%s\n", nome);
    }
    fclose(arquivo);
}
void escreverNomeJogador2(const char *nome){
    FILE *arquivo = fopen("jogador2.txt", "a");
    if (arquivo != NULL) {
      // Escreva no arquivo
        fprintf(arquivo, "%s\n", nome);
    }
    fclose(arquivo);
}
void escreverNomeVencedor(const char *nome){
    FILE *arquivo = fopen("vencedor.txt", "a");
    if (arquivo != NULL) {
      // Escreva no arquivo
        fprintf(arquivo, "%s\n", nome);
    }
    fclose(arquivo);
}
void lerConteudoDoArquivoPara1(char linhas[MAX_LINHAS][MAX_LINHA]) {
    FILE *arquivo = fopen("jogador1.txt", "r");
    int i = 0;
    char linha[MAX_LINHA];  // Array para armazenar uma linha lida
    // Lê o arquivo linha por linha
    while (fgets(linha, MAX_LINHA, arquivo) && i < MAX_LINHAS) {
// Remove o caractere de nova linha, se presente
// e apos isso armazena no array
        linha[strcspn(linha, "\n")] = '\0';
        strncpy(linhas[i], linha, MAX_LINHA);
        i++;
    }
    fclose(arquivo);
}
void lerConteudoDoArquivoPara2(char linhas[MAX_LINHAS][MAX_LINHA]) {
    FILE *arquivo = fopen("jogador2.txt", "r");
    int i = 0;
    char linha[MAX_LINHA];  // Array para armazenar uma linha lida
    // Lê o arquivo linha por linha
    while (fgets(linha, MAX_LINHA, arquivo) && i < MAX_LINHAS) {
// Remove o caractere de nova linha, se presente
// e apos isso armazena no array
        linha[strcspn(linha, "\n")] = '\0';
        strncpy(linhas[i], linha, MAX_LINHA);
        i++;
    }
    fclose(arquivo);
}
void lerConteudoDoArquivoPara3(char linhas[MAX_LINHAS][MAX_LINHA]) {
    FILE *arquivo = fopen("vencedor.txt", "r");
    int i = 0;
    char linha[MAX_LINHA];  // Array para armazenar uma linha lida
    // Lê o arquivo linha por linha
    while (fgets(linha, MAX_LINHA, arquivo) && i < MAX_LINHAS) {
// Remove o caractere de nova linha, se presente
// e apos isso armazena no array
        linha[strcspn(linha, "\n")] = '\0';
        strncpy(linhas[i], linha, MAX_LINHA);
        i++;
    }
    fclose(arquivo);
}

