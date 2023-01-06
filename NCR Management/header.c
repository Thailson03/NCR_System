//ARQUIVOS DE CABE�ALHO
#include "header.h"
#include "stdio.h"
#include "windows.h"
#include "time.h"
#include "locale.h"
#include "conio.h"

//PONTEIRO GLOBAL
FILE *file; //Ponteiro para acessar arquivo texto

//FUN��ES AUXILIARES
void cls(void)
{
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, TEXT(' '),
                               dwConSize, coordScreen, &cCharsWritten);

    GetConsoleScreenBufferInfo(hConsole, &csbi);

    FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
                               dwConSize, coordScreen, &cCharsWritten);

    SetConsoleCursorPosition(hConsole, coordScreen);
}

/*
void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
*/

void setPosition(int linha, int coluna)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD)
    {
        coluna-1, linha-1
    });
}

void createBox( int linha1, int coluna1, int linha2, int coluna2)
{

    int i;

    // Monta o box
    for(i=coluna1; i<=coluna2; i++)   //Linhas
    {
        setPosition( linha1, i );
        printf("%c", 196);
        setPosition( linha2, i );
        printf("%c", 196);
    }

    for(i=linha1; i<=linha2; i++)   //Laterais
    {
        setPosition(i, coluna1);
        printf("%c",179);
        setPosition( i, coluna2);
        printf("%c",179);
    }

    // Posicoes dos cantos.
    setPosition(linha1, coluna1);
    printf("%c", 218);
    setPosition(linha1, coluna2);
    printf("%c", 191);
    setPosition(linha2, coluna1);
    printf("%c", 192);
    setPosition(linha2, coluna2);
    printf("%c", 217);
}

void getTime(char *str)
{

    char horario[50];
    char horarioCat[50];

    memset(horario, '\0', sizeof(horario));
    memset(horarioCat, '\0', sizeof(horarioCat));

    time_t agora = 0;
    struct tm *info;

    time(&agora);
    info = localtime(&agora);

    switch(info->tm_wday)
    {
    case 0:
        strcat(horario, "Domingo - ");
        break;

    case 1:
        strcat(horario, "Segunda-Feira - ");
        break;

    case 2:
        strcat(horario, "Ter�a-Feira - ");
        break;

    case 3:
        strcat(horario, "Quarta-Feira - ");
        break;

    case 4:
        strcat(horario, "Quinta-Feira - ");
        break;

    case 5:
        strcat(horario, "Sexta-Feira - ");
        break;

    case 6:
        strcat(horario, "S�bado - ");
        break;
    }

    //Colocando o dia na String principal
    itoa(info->tm_mday, horarioCat, 10); //Transforma inteiro para String
    if(info->tm_mday < 10)
    {
        strcat(horario, "0");
        strcat(horario, horarioCat);
    }
    else
    {
        strcat(horario, horarioCat);
    }
    strcat(horario, "/");
    memset(horarioCat, '\0', sizeof(horario));

    //Colocando o m�s na String principal
    itoa(info->tm_mon+1, horarioCat, 10); //Transforma inteiro para String
    if(info->tm_mon+1 < 10)
    {
        strcat(horario, "0");
        strcat(horario, horarioCat);
    }
    else
    {
        strcat(horario, horarioCat);
    }
    strcat(horario, "/");
    memset(horarioCat, '\0', sizeof(horario));

    //Colocando o ano na String principal
    itoa(info->tm_year+1900, horarioCat, 10); //Transforma inteiro para String
    strcat(horario, horarioCat);
    strcat(horario, " - ");
    memset(horarioCat, '\0', sizeof(horario));

    //Colocando a hora na String principal
    itoa(info->tm_hour, horarioCat, 10); //Transforma inteiro para String
    if(info->tm_hour == 0)
    {
        strcat(horario, "00");
    }
    else if (info->tm_hour < 10)
    {
        strcat(horario, "0");
        strcat(horario, horarioCat);
    }
    else
    {
        strcat(horario, horarioCat);
    }
    strcat(horario, ":");
    memset(horarioCat, '\0', sizeof(horario));

    //Colocando os minutos na String principal
    itoa(info->tm_min, horarioCat, 10); //Transforma inteiro para String
    if(info->tm_min == 0)
    {
        strcat(horario, "00");
    }
    else if (info->tm_min < 10)
    {
        strcat(horario, "0");
        strcat(horario, horarioCat);
    }
    else
    {
        strcat(horario, horarioCat);
    }
    strcat(horario, ":");
    memset(horarioCat, '\0', sizeof(horario));

    //Colocando os segundos na String principal
    itoa(info->tm_sec, horarioCat, 10); //Transforma inteiro para String
    if(info->tm_sec == 0)
    {
        strcat(horario, "00");
    }
    else if (info->tm_sec < 10)
    {
        strcat(horario, "0");
        strcat(horario, horarioCat);
    }
    else
    {
        strcat(horario, horarioCat);
    }
    memset(horarioCat, '\0', sizeof(horario));

    strcpy(str, horario);
}

int pergunta(char pergunta[40], int linha, int coluna)
{
    int tecla;
    int simnao=1;

    // Monta a tela
    createBox(linha, coluna, linha+6, coluna+22);
    setlocale(LC_ALL, "Portuguese");
    setPosition(linha+2,coluna+2);
    printf( "%s", pergunta );
    setPosition(linha+4,coluna+4);
    printf( "SIM" );
    setPosition(linha+4,coluna+14);
    printf( "n�o" );
    setlocale(LC_ALL, "C");

    setPosition(linha+4, coluna+7); //Indicando o ponteiro no SIM

    while(1)
    {
        fflush(stdin);
        tecla=getch();
        if(tecla == 27)   // ESC
        {
            simnao=0;
            break;
        }
        else if (tecla==13)   // Enter
        {
            break;
        }

        // Colocou S ou N direto?
        if(tecla==83 || tecla == 115) return ( 1 ); //// Sim!
        if(tecla==78 || tecla==110) return ( 0 ); //// Nao!

        // Alterna entre o sim e o n�o
        if(tecla == 75)
        {
            setlocale(LC_ALL, "Portuguese");
            setPosition(linha+4,coluna+4);
            printf("SIM");
            setPosition(linha+4,coluna+14);
            printf("n�o");
            simnao=1;
            setPosition(linha+4, coluna+7);
            setlocale(LC_ALL, "C");
        }

        else if(tecla==77)
        {
            setlocale(LC_ALL, "Portuguese");
            setPosition(linha+4,coluna+4);
            printf("sim");
            setPosition(linha+4,coluna+14);
            printf("N�O");
            setPosition(linha+4, coluna+17);
            simnao=0;
            setlocale(LC_ALL, "C");
        }


    }
    return (simnao);
}

void limparPergunta(int linha, int coluna)
{
    int i, j;

    for(i = linha; i < linha+7; i++)
    {
        for(j = coluna; j < coluna+23; j++)
        {
            setPosition(i, j);
            printf(" ");
        }
    }

}

void limparLinha(int linha)
{
    int i;
    for(i = 1; i <= 100; i++)
    {
        setPosition(linha, i);
        printf(" ");
    }
}

void getTema(char usuario[100])
{
    memset(tema.fundo, '\0', sizeof(tema.fundo));
    memset(tema.texto, '\0', sizeof(tema.texto));
    memset(tema.tema, '\0', sizeof(tema.tema));

    tema.fundo[0] = usuario[strlen(usuario)-2];
    tema.texto[0] = usuario[strlen(usuario)-1];
    strcat(tema.tema, "color ");
    tema.tema[6] = tema.fundo[0];
    tema.tema[7] = tema.texto[0];
}

void registrarNoLog(char mensagem[255])
{
    file = fopen("./Registros/reg.txt", "a");
    getTime(horario);
    fprintf(file, "%s: %s - %s\n", dados.usuario, mensagem, horario);
    fclose(file);
}

//FUN��ES USADA NA FUN��O PRINCIPAL
void tutorial()
{

    system("color f0");
    cls();

    int totalPg = 19;
    char tecla;
    int pagina = 1;

    do
    {

        cls();

        switch(pagina)
        {
        case 1:
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("---------- COMO NAVEGAR NO TUTORIAL? ----------");
            setPosition(4, 3);
            printf("Pressione a tecla \"ENTER\" para acessar a tela de login.");
            setPosition(5, 3);
            printf("Pressione a tecla \"%c\" ou \"->\" para avan�ar p�gina.", 24);
            setPosition(6, 3);
            printf("Pressione a tecla \"%c\" ou \"<-\" para voltar p�gina.", 25);
            setPosition(8, 3);
            printf("---------- P�gina 1/%d ----------", totalPg);
            setlocale(LC_ALL, "C");
            break;

        case 2:
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("---------- COMO FUNCIONA O SISTEMA? ----------");
            setPosition(4, 3);
            printf("O programa � composto por um menu interativo.");
            setPosition(5, 3);
            printf("Utilize a seta ou os n�meros do teclado para navegar sobre as op��es.");
            setPosition(6, 3);
            printf("Pressione a tecla \"ENTER\" para acessar a op��o selecionada.");
            setPosition(7, 3);
            printf("Pressione a tecla \"ESC\" a qualquer momento para voltar.");
            setPosition(9, 3);
            printf("---------- P�gina 2/%d ----------", totalPg);
            setlocale(LC_ALL, "C");
            break;

        case 3:
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("---------- TELA DE LOGIN ----------");
            setPosition(4, 3);
            printf("H� duas caixas a ser preenchida, s�o eles: \"Usu�rio\" e \"Senha\".");
            setPosition(5, 3);
            printf("Para acessar o menu principal, voc� precisa ter um cadastro no sistema.");
            setPosition(7, 3);
            printf("---------- P�gina 3/%d ----------", totalPg);
            setlocale(LC_ALL, "C");
            break;

        case 4:
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("---------- O QUE D� PRA FAZER COM O PROGRAMA? ----------");
            setPosition(4, 3);
            printf("- Gerenciar funcion�rios");
            setPosition(5, 3);
            printf("- Gerenciar clientes");
            setPosition(6, 3);
            printf("- Gerenciar usu�rios");
            setPosition(7, 3);
            printf("- Administrar registro de log (APENAS PARA O ADMINISTRADOR)");
            setPosition(8, 3);
            printf("- Ler sobre a NCR System");
            setPosition(9, 3);
            printf("- Configurar ajustes");
            setPosition(11, 3);
            printf("---------- P�gina 4/%d ----------", totalPg);
            setlocale(LC_ALL, "C");
            break;

        case 5:
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("---------- O QUE D� PRA FAZER EM GERENCIAR FUNCION�RIOS? ----------");
            setPosition(4, 3);
            printf("- Cadastrar funcion�rio");
            setPosition(5, 3);
            printf("- Remover funcion�rio (APENAS PARA O ADMINISTRADOR)");
            setPosition(6, 3);
            printf("- Listar funcion�rios");
            setPosition(7, 3);
            printf("- Ativar/Desligar funcion�rio");
            setPosition(8, 3);
            printf("- Relat�rio dos funcion�rios (APENAS PARA O ADMINISTRADOR)");
            setPosition(10, 3);
            printf("---------- P�gina 5/%d ----------", totalPg);
            setlocale(LC_ALL, "C");
            break;

        case 6:
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("---------- CADASTRAR FUNCION�RIO ----------");
            setPosition(4, 3);
            printf("Preencha todos os campos e confirme no final para cadastrar o funcion�rio.");
            setPosition(5, 3);
            printf("A cada preenchimento, ser� solicitado a sua confirma��o, se precisar corrigir o campo selecione a op��o \"N�O\".");
            setPosition(6, 3);
            printf("Se quiser cancelar o cadastro, basta pressionar a tecla \"ESC\".");
            setPosition(8, 3);
            printf("---------- P�gina 6/%d ----------", totalPg);
            setlocale(LC_ALL, "C");
            break;

        case 7:
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("---------- LISTAR FUNCION�RIOS ----------");
            setPosition(4, 3);
            printf("Ser�o exibidas as seguintes informa��es dos funcion�rios:");
            setPosition(6, 3);
            printf("- ID");
            setPosition(7, 3);
            printf("- Nome");
            setPosition(8, 3);
            printf("- Fun��o");
            setPosition(9, 3);
            printf("- Data de nascimento (APENAS PARA O ADMINISTRADOR)");
            setPosition(10, 3);
            printf("- N�vel de Cargo");
            setPosition(11, 3);
            printf("- Sal�rio (APENAS PARA O ADMINISTRADOR)");
            setPosition(12, 3);
            printf("- Data de in�cio");
            setPosition(13, 3);
            printf("- Situa��o");
            setPosition(15, 3);
            printf("---------- P�gina 7/%d ----------", totalPg);
            setlocale(LC_ALL, "C");
            break;

        case 8:
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("---------- ATIVAR/DESLIGAR FUNCION�RIO ----------");
            setPosition(4, 3);
            printf("Haver� um campo a ser preenchido, � ele: Pesquisar ID.");
            setPosition(5, 3);
            printf("Se um ID for encontrado, voc� poder� desligar aquele funcion�rio ou ativ�-lo de volta.");
            setPosition(6, 3);
            printf("Se quiser cancelar o ativamento/desligamento, basta pressionar a tecla \"ESC\".");
            setPosition(8, 3);
            printf("---------- P�gina 8/%d ----------", totalPg);
            setlocale(LC_ALL, "C");
            break;

        case 9:
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("---------- O QUE D� PRA FAZER EM GERENCIAR CLIENTES? ----------");
            setPosition(4, 3);
            printf("- Cadastrar Cliente");
            setPosition(5, 3);
            printf("- Remover Cliente (APENAS PARA O ADMINISTRADOR)");
            setPosition(6, 3);
            printf("- Listar Clientes");
            setPosition(7, 3);
            printf("- Modificar Cliente (APENAS PARA O ADMINISTRADOR)");
            setPosition(9, 3);
            printf("---------- P�gina 9/%d ----------", totalPg);
            setlocale(LC_ALL, "C");
            break;

        case 10:
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("---------- CADASTAR CLIENTE ----------");
            setPosition(4, 3);
            printf("Preencha todos os campos e confirme no final para cadastrar o cliente.");
            setPosition(5, 3);
            printf("A cada preenchimento, ser� solicitado a sua confirma��o, se precisar corrigir o campo selecione a op��o \"N�O\".");
            setPosition(6, 3);
            printf("Se quiser cancelar o cadastro, basta pressionar a tecla \"ESC\".");
            setPosition(8, 3);
            printf("---------- P�gina 10/%d ----------", totalPg);
            setlocale(LC_ALL, "C");
            break;

        case 11:
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("---------- LISTAR CLIENTES ----------");
            setPosition(4, 3);
            printf("Ser�o exibidas as seguintes informa��es dos clientes:");
            setPosition(6, 3);
            printf("- ID");
            setPosition(7, 3);
            printf("- Nome");
            setPosition(8, 3);
            printf("- Email");
            setPosition(9, 3);
            printf("- Telefone");
            setPosition(10, 3);
            printf("- Tipo de Pessoa");
            setPosition(11, 3);
            printf("- Ativo (APENAS PARA O ADMINISTRADOR)");
            setPosition(12, 3);
            printf("- Passivo (APENAS PARA O ADMINISTRADOR)");
            setPosition(13, 3);
            printf("- Saldo (APENAS PARA O ADMINISTRADOR)");
            setPosition(15, 3);
            printf("---------- P�gina 11/%d ----------", totalPg);
            setlocale(LC_ALL, "C");
            break;

        case 12:
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("---------- O QUE D� PRA FAZER EM GERENCIAR USU�RIOS? ----------");
            setPosition(4, 3);
            printf("- Cadastrar usu�rio");
            setPosition(5, 3);
            printf("- Remover usu�rio (APENAS PARA O ADMINISTRADOR)");
            setPosition(6, 3);
            printf("- Listar usu�rios");
            setPosition(8, 3);
            printf("---------- P�gina 12/%d ----------", totalPg);
            setlocale(LC_ALL, "C");
            break;

        case 13:
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("---------- CADASTRAR USU�RIO ----------");
            setPosition(4, 3);
            printf("Haver� tr�s campos a serem preenchidos, s�o eles: Usu�rio, Senha e Confirmar senha.");
            setPosition(6, 3);
            printf("N�o ser� permitido o cadastro caso:");
            setPosition(8, 3);
            printf("- O campo de usu�rio estiver v�zio.");
            setPosition(9, 3);
            printf("- O nome de usu�rio j� existir.");
            setPosition(10, 3);
            printf("- A senha tiver menos que 8 d�gitos.");
            setPosition(11, 3);
            printf("- A senha e confirma��o de senha n�o se coincidirem.");
            setPosition(13, 3);
            printf("Se quiser cancelar o cadastro, basta pressionar a tecla \"ESC\".");
            setPosition(15, 3);
            printf("---------- P�gina 13/%d ----------", totalPg);
            setlocale(LC_ALL, "C");
            break;

        case 14:
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("---------- LISTAR USU�RIOS ----------");
            setPosition(4, 3);
            printf("Ser�o exibidas as seguintes informa��es dos usu�rios:");
            setPosition(6, 3);
            printf("- Usu�rio");
            setPosition(7, 3);
            printf("- Senha (APENAS PARA O ADMINISTRADOR)");
            setPosition(9, 3);
            printf("---------- P�gina 14/%d ----------", totalPg);
            setlocale(LC_ALL, "C");
            break;

        case 15:
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("---------- SOBRE A NCR SYSTEM ----------");
            setPosition(4, 3);
            printf("Ser�o exibidas as seguintes informa��es sobre a NCR System:");
            setPosition(6, 3);
            printf("- Miss�o e Vis�o");
            setPosition(7, 3);
            printf("- Valores");
            setPosition(9, 3);
            printf("---------- P�gina 15/%d ----------", totalPg);
            setlocale(LC_ALL, "C");
            break;

        case 16:
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("---------- O QUE D� PRA FAZER EM AJUSTES ----------");
            setPosition(4, 3);
            printf("- Redefinir senha");
            setPosition(5, 3);
            printf("- Redefinir tema");
            setPosition(7, 3);
            printf("---------- P�gina 16/%d ----------", totalPg);
            setlocale(LC_ALL, "C");
            break;

        case 17:
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("---------- REDEFINIR SENHA ----------");
            setPosition(4, 3);
            printf("Haver� tr�s campos a serem preenchidos, s�o eles: Senha atual, Nova senha e Confirmar nova senha.");
            setPosition(6, 3);
            printf("N�o ser� permitida a redefini��o de senha caso:");
            setPosition(8, 3);
            printf("- O campo de Senha atual n�o corresponder realmente com a senha atual.");
            setPosition(9, 3);
            printf("- A senha tiver menos que 8 d�gitos.");
            setPosition(10, 3);
            printf("- A senha e confirma��o de senha n�o se coincidirem.");
            setPosition(12, 3);
            printf("Se quiser cancelar a redefini��o de senha, basta pressionar a tecla \"ESC\".");
            setPosition(14, 3);
            printf("---------- P�gina 17/%d ----------", totalPg);
            setlocale(LC_ALL, "C");
            break;

        case 18:
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("---------- REDEFINIR TEMA ----------");
            setPosition(4, 3);
            printf("Haver� dois campos a serem preenchidos, s�o eles: Fundo e Texto.");
            setPosition(5, 3);
            printf("Para preencher os campos utilize a tabela de cores ao lado.");
            setPosition(6, 3);
            printf("Se quiser cancelar a redefini��o de tema, basta pressionar a tecla \"ESC\".");
            setPosition(8, 3);
            printf("---------- P�gina 18/%d ----------", totalPg);
            setlocale(LC_ALL, "C");
            break;

        case 19:
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("---------- ENCERRAR SESS�O ----------");
            setPosition(4, 3);
            printf("Neste m�dulo o programa ser� finalizado.");
            setPosition(6, 3);
            printf("---------- P�gina 19/%d ----------", totalPg);
            setlocale(LC_ALL, "C");
            break;
        }

        while(1)
        {
            tecla = getch();

            if(tecla == ENTER)
            {
                break;
            }

            if(tecla == 72 || tecla == 77)   //Seta seta para ou seta para direita
            {
                if(pagina < totalPg)   //Quantidade m�xima de p�gina
                {
                    pagina++;
                    break;
                }
                else
                {
                    continue;
                }
            }

            if(tecla == 80 || tecla == 75)   //Seta para baixo ou seta para esquerda
            {
                if(pagina > 1)   //Quantidade m�nima de p�gina
                {
                    pagina--;
                    break;
                }
                else
                {
                    continue;
                }
            }


        }


    }
    while (tecla != ENTER);


}

void tutorialAdmin ()
{
    //VERIFICANDO ADMINISTRADOR
    char analisador[100];
    memset(analisador, '\0', sizeof(analisador));
    strcat(analisador, dados.usuario);
    strcat(analisador, " ");
    strcat(analisador, dados.senha);

    if(strcmp(ADMIN, analisador) == 0)
    {

        int totalPg = 10;
        char tecla;
        int pagina = 1;

        do
        {

            cls();

            switch(pagina)
            {
            case 1:
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("---------- INFORMA��ES EXCLUSIVAS DO ADMIN ----------");
                setPosition(4, 3);
                printf("Informa��es como senhas e finan�as s�o tratadas com sigilo,");
                setPosition(5, 3);
                printf("portanto somente o usu�rio ADMIN ter� acesso.");
                setPosition(7, 3);
                printf("---------- P�gina 1/%d ----------", totalPg);
                setlocale(LC_ALL, "C");
                break;

            case 2:
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("---------- FUNCIONALIDADES EXLUSIVAS DO ADMIN ----------");
                setPosition(4, 3);
                printf("- Remover funcion�rio, Relat�rio dos funcion�rios.");
                setPosition(5, 3);
                printf("- Remover cliente, Modificar cliente.");
                setPosition(6, 3);
                printf("- Remover usu�rio.");
                setPosition(7, 3);
                printf("- Registro de log.");
                setPosition(9, 3);
                printf("---------- P�gina 2/%d ----------", totalPg);
                setlocale(LC_ALL, "C");
                break;

            case 3:
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("---------- REMOVER FUNCION�RIO ----------");
                setPosition(4, 3);
                printf("Neste bloco o usu�rio identifica o funcion�rio desejado pelo id,");
                setPosition(5, 3);
                printf("caso n�o esteja ciente do ID desejado, basta identificar no");
                setPosition(6, 3);
                printf("m�dulo Listar Funcion�rios.");
                setPosition(8, 3);
                printf("---------- P�gina 3/%d ----------", totalPg);
                setlocale(LC_ALL, "C");
                break;

            case 4:
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("---------- RELAT�RIO DOS FUNCION�RIOS ----------");
                setPosition(4, 3);
                printf("Neste m�dulo ser� apresentado informa��es �teis,");
                setPosition(5, 3);
                printf("baseado no banco de dados do NCR Management.");
                setPosition(7, 3);
                printf("---------- P�gina 4/%d ----------", totalPg);
                setlocale(LC_ALL, "C");
                break;

            case 5:
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("---------- REMOVER CLIENTE ----------");
                setPosition(4, 3);
                printf("Neste bloco, o usu�rio identifica o cliente desejado atrav�s do ID, caso");
                setPosition(5, 3);
                printf("n�o esteja ciente do ID do cliente, basta identificar no m�dulo listar cliente.");
                setPosition(7, 3);
                printf("---------- P�gina 5/%d ----------", totalPg);
                setlocale(LC_ALL, "C");
                break;

            case 6:
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("---------- MODIFICAR CLIENTE ----------");
                setPosition(4, 3);
                printf("Neste m�dulo o usu�rio identifica o cliente desejado atrav�s do ID.");
                setPosition(5, 3);
                printf("Ser� apresentado duas op��es para modifica��o, ATIVO/PASSIVO.");
                setPosition(6, 3);
                printf("Ap�s a modifica��o ser� calculado um novo saldo.");
                setPosition(8, 3);
                printf("---------- P�gina 6/%d ----------", totalPg);
                setlocale(LC_ALL, "C");
                break;

            case 7:
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("---------- REMOVER USU�RIO ----------");
                setPosition(4, 3);
                printf("Neste bloco o ADMIN identifica o usu�rio desejado atrav�s do nome.");
                setPosition(5, 3);
                printf("Ser� feito uma pergunta de seguran�a para realmente deletar.");
                setPosition(7, 3);
                printf("---------- P�gina 7/%d ----------", totalPg);
                setlocale(LC_ALL, "C");
                break;

            case 8:
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("---------- O QUE D� PARA FAZER EM REGISTRO DE LOG? ----------");
                setPosition(4, 3);
                printf("- Ler registro");
                setPosition(5, 3);
                printf("- Limpar registro");
                setPosition(7, 3);
                printf("---------- P�gina 8/%d ----------", totalPg);
                setlocale(LC_ALL, "C");
                break;

            case 9:
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("---------- LER REGISTRO ----------");
                setPosition(4, 3);
                printf("Neste m�dulo o usu�rio tem acesso a todas a��es");
                setPosition(5, 3);
                printf("feitas no programa, quem fez e quando fez.");
                setPosition(7, 3);
                printf("---------- P�gina 9/%d ----------", totalPg);
                setlocale(LC_ALL, "C");
                break;

            case 10:
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("---------- LIMPAR REGISTRO ----------");
                setPosition(4, 3);
                printf("Neste m�dulo ser� apresentado uma pergunta de seguran�a,");
                setPosition(5, 3);
                printf("para realmente limpar todas atividas registradas");
                setPosition(7, 3);
                printf("---------- P�gina 10/%d ----------", totalPg);
                setlocale(LC_ALL, "C");
                break;
            }

            while(1)
            {
                tecla = getch();

                if(tecla == ENTER)
                {
                    break;
                }

                if(tecla == 72 || tecla == 77)   //Seta seta para ou seta para direita
                {
                    if(pagina < totalPg)   //Quantidade m�xima de p�gina (At� agora)
                    {
                        pagina++;
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }

                if(tecla == 80 || tecla == 75)   //Seta para baixo ou seta para esquerda
                {
                    if(pagina > 1)   //Quantidade m�nima de p�gina
                    {
                        pagina--;
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }


            }


        }
        while (tecla != ENTER);


    }
}

struct LOGIN login(struct LOGIN *dados)
{
    cls();

    //LIMPANDO VARI�VEL QUE ARMAZENA LOGIN E SENHA
    memset(dados->usuario, '\0', sizeof(dados->usuario));
    memset(dados->senha, '\0', sizeof(dados->senha));

    //LAYOUT DA TELA DE LOGIN
    createBox(1, 2, 3, 50);
    setPosition(2, 23);
    printf("LOGIN");
    createBox(3, 2, 12, 50);
    setPosition(3, 2);
    printf("%c", 195);
    setPosition(3, 50);
    printf("%c", 180);

    //LAYOUT USUARIO
    setlocale(LC_ALL, "Portuguese");
    setPosition(4, 4);
    printf("Usu�rio: ");
    setlocale(LC_ALL, "C");
    createBox(5, 3, 7,49 );

    //LAYOUT SENHA
    setlocale(LC_ALL, "Portuguese");
    setPosition(8, 4);
    printf("Senha: ");
    setlocale(LC_ALL, "C");
    createBox(9, 3, 11,49 );

    //ENTRADA DE DADOS DO CAMPO USU�RIO
    char ch = '\0';
    int ctecla = 0;

    setPosition(6, 4);
    while(ctecla<45)
    {
        ch = getch();

        switch(ch)
        {
        case BACKSPACE:
            if(ctecla>0)
            {
                fflush(stdin);
                putch(BACKSPACE);
                ch = '\0';
                dados->usuario[ctecla-1] = ch;
                ctecla--;
                putch(SPACE);
                putch(BACKSPACE);
            }
            break;
        case TAB:
            putch(TAB);
            ctecla = 50;
            break;
        case ENTER:
            putch(ENTER);
            ctecla = 50;
            break;
        default:
            dados->usuario[ctecla] = ch;
            putch(ch);
            ctecla++;
            break;
        }
    }

    //ENTRADA DE DADOS DO CAMPO senha
    ctecla = 0;
    ch = '\0';

    setPosition(10, 4);
    while(ctecla<45)
    {
        ch = getch();

        switch(ch)
        {
        case BACKSPACE:
            if(ctecla>0)
            {
                fflush(stdin);
                putch(BACKSPACE);
                ch = '\0';
                dados->senha[ctecla-1] = ch;
                ctecla--;
                putch(SPACE);
                putch(BACKSPACE);
            }
            break;
        case TAB:
            putch(TAB);
            ctecla = 50;
            break;
        case ENTER:
            putch(ENTER);
            ctecla = 50;
            break;
        default:
            dados->senha[ctecla] = ch;
            putch('*');
            ctecla++;
            break;
        }
    }

    if(strcmp(dados->usuario, "") == 0)   //SE DEIXAR O CAMPO DE USU�RIO EM BRANCO...
    {
        strcat(dados->usuario,"........................................");
    }

    if(strcmp(dados->senha, "") == 0)   //SE DEIXAR O CAMPO DE SENHA EM BRANCO....
    {
        strcat(dados->senha,"........................................");
    }

    //ANALISANDO OS DADOS
    char analisador[100];
    char leitor[100];

    memset(analisador, '\0', sizeof(analisador));
    memset(leitor, '\0', sizeof(leitor));

    strcat(analisador, dados->usuario);
    strcat(analisador, " ");
    strcat(analisador, dados->senha);


    file = fopen("./Users/us.txt", "r"); //ABRINDO O ARQUIVO TEXTO QUE ARMAZENA OS DADOS DOSUSU�RIOS CADASTRADOS EM MODO LEITURA
    while (fgets(leitor, 100, file) != NULL)
    {

        if(leitor[strlen(leitor)-1] == '\n')   //SE A O �LTIMO CARACTERE DA LINHA LIDA, FOR UM '\N' SER� ANULADO.
        {
            leitor[strlen(leitor)-1] = '\0';
        }

        getTema(leitor); //REPECUPERANDO O TEMA DO USU�RIO

        //ANULANDO O TEMA PARA SER VERIFICADO APENAS O USU�RIO E SENHA
        leitor[strlen(leitor)-1] = '\0';
        leitor[strlen(leitor)-1] = '\0';
        leitor[strlen(leitor)-1] = '\0';


        if(strcmp(leitor,analisador) == 0)   //QUEBRA O LA�O WHILE CASO O USU�RIO SEJA ENCONTRADO
        {
            break;
        }

    }
    fclose(file); //FECHANDO O ARQUIVO TEXTO QUE ESTAVA SENDO LIDO

    if(strcmp(ADMIN, analisador) == 0)   //COMPARANDO OS DADOS RECEBIDOS COM A CONTA DO ADMINISTRADOR
    {
        strcpy(tema.tema, "color F0");
        return *dados;
    }
    else if(strcmp(leitor,analisador) == 0)     //COMPARANDO OS DADOS RECEBIDOS COM AS CONTAS DE USU�RIOS COMUNS
    {
        system(tema.tema);
        return *dados;
    }
    else     //CASO NENHUMA CONTA FOR ENCONTRADA
    {
        setPosition(14, 3);
        setlocale(LC_ALL, "Portuguese");
        printf("ERRO: USU�RIO OU SENHA EST� INCORRETA!");
        setlocale(LC_ALL, "C");
        getch();
        login(dados);
    }

    return *dados;
}

void saudacao()
{
    cls();
    setPosition(2, 3);
    printf("Seja bem-vindo, %s!", dados.usuario);
    getch();
}

void menuPrincipal()
{
    cls();

    //LAYOUT DO MENU PRINCIPAL
    createBox(1, 2, 3, 41);
    createBox(3, 2, 11, 41);
    setPosition(3, 2);
    printf("%c", 195);
    setPosition(3, 41);
    printf("%c", 180);

    //POSICIONANDO AS OP��ES
    setlocale(LC_ALL, "Portuguese");
    setPosition(2, 15);
    printf("MENU PRINCIPAL");
    setPosition(4, 3);
    printf("  1 - Gerenciar funcion�rios");
    setPosition(5, 3);
    printf("  2 - Gerenciar clientes");
    setPosition(6, 3);
    printf("  3 - Gerenciar usu�rios");
    setPosition(7, 3);
    printf("  4 - Registros de log");
    setPosition(8, 3);
    printf("  5 - Sobre a NCR System");
    setPosition(9, 3);
    printf("  6 - Ajustes");
    setPosition(10, 3);
    printf("  7 - Encerrar sess�o");
    setPosition(4, 3);
    printf("�");
    setPosition(4, 5);
    printf("1 - GERENCIAR FUNCION�RIOS");
    setlocale(LC_ALL, "C");

    //SISTEMA DE ANIMA��O PARA A INTERATIVIDADE
    int tecla;
    int opcao = 1;

    while(1)
    {
        setbuf(stdin, NULL);
        tecla = getch();

        if (tecla == ESC)
        {
            opcao = 7;
            setlocale(LC_ALL, "C");
            break;
        }

        if (tecla == ENTER)
        {
            break;
        }

        if(tecla == 80 || tecla == 77)   //SETA PARA BAIXO OU SETA PARA DIREITA
        {
            switch(opcao)
            {
            case 1:
                tecla = 50;
                break;

            case 2:
                tecla = 51;
                break;

            case 3:
                tecla = 52;
                break;

            case 4:
                tecla = 53;
                break;

            case 5:
                tecla = 54;
                break;

            case 6:
                tecla = 55;
                break;

            case 7:
                tecla = 49;
                break;
            }
        }

        if(tecla == 72 || tecla == 75)   //SETA PARA CIMA OU SETA PARA ESQUERDA
        {
            switch(opcao)
            {
            case 1:
                tecla = 55;
                break;

            case 2:
                tecla = 49;
                break;

            case 3:
                tecla = 50;
                break;

            case 4:
                tecla = 51;
                break;

            case 5:
                tecla = 52;
                break;

            case 6:
                tecla = 53;
                break;

            case 7:
                tecla = 54;
                break;
            }
        }

        setlocale(LC_ALL, "Portuguese");
        if(tecla == 49)
        {
            setPosition(4, 3);
            printf("  1 - Gerenciar funcion�rios");
            setPosition(5, 3);
            printf("  2 - Gerenciar clientes");
            setPosition(6, 3);
            printf("  3 - Gerenciar usu�rios");
            setPosition(7, 3);
            printf("  4 - Registros de log");
            setPosition(8, 3);
            printf("  5 - Sobre a NCR System");
            setPosition(9, 3);
            printf("  6 - Ajustes");
            setPosition(10, 3);
            printf("  7 - Encerrar sess�o");
            setPosition(4, 3);
            printf("�");
            setPosition(4, 5);
            printf("1 - GERENCIAR FUNCION�RIOS");
            opcao = 1;
        }
        else if (tecla == 50)
        {
            setPosition(4, 3);
            printf("  1 - Gerenciar funcion�rios");
            setPosition(5, 3);
            printf("  2 - Gerenciar clientes");
            setPosition(6, 3);
            printf("  3 - Gerenciar usu�rios");
            setPosition(7, 3);
            printf("  4 - Registros de log");
            setPosition(8, 3);
            printf("  5 - Sobre a NCR System");
            setPosition(9, 3);
            printf("  6 - Ajustes");
            setPosition(10, 3);
            printf("  7 - Encerrar sess�o");
            setPosition(5, 3);
            printf("�");
            setPosition(5, 5);
            printf("2 - GERENCIAR CLIENTES");
            opcao = 2;
        }
        else if (tecla == 51)
        {
            setPosition(4, 3);
            printf("  1 - Gerenciar funcion�rios");
            setPosition(5, 3);
            printf("  2 - Gerenciar clientes");
            setPosition(6, 3);
            printf("  3 - Gerenciar usu�rios");
            setPosition(7, 3);
            printf("  4 - Registros de log");
            setPosition(8, 3);
            printf("  5 - Sobre a NCR System");
            setPosition(9, 3);
            printf("  6 - Ajustes");
            setPosition(10, 3);
            printf("  7 - Encerrar sess�o");
            setPosition(6, 3);
            printf("�");
            setPosition(6, 5);
            printf("3 - GERENCIAR USU�RIOS");
            opcao = 3;
        }
        else if (tecla == 52)
        {
            setPosition(4, 3);
            printf("  1 - Gerenciar funcion�rios");
            setPosition(5, 3);
            printf("  2 - Gerenciar clientes");
            setPosition(6, 3);
            printf("  3 - Gerenciar usu�rios");
            setPosition(7, 3);
            printf("  4 - Registros de log");
            setPosition(8, 3);
            printf("  5 - Sobre a NCR System");
            setPosition(9, 3);
            printf("  6 - Ajustes");
            setPosition(10, 3);
            printf("  7 - Encerrar sess�o");
            setPosition(7, 3);
            printf("�");
            setPosition(7, 5);
            printf("4 - REGISTROS DE LOG");
            opcao = 4;
        }
        else if (tecla == 53)
        {
            setPosition(4, 3);
            printf("  1 - Gerenciar funcion�rios");
            setPosition(5, 3);
            printf("  2 - Gerenciar clientes");
            setPosition(6, 3);
            printf("  3 - Gerenciar usu�rios");
            setPosition(7, 3);
            printf("  4 - Registros de log");
            setPosition(8, 3);
            printf("  5 - Sobre a NCR System");
            setPosition(9, 3);
            printf("  6 - Ajustes");
            setPosition(10, 3);
            printf("  7 - Encerrar sess�o");
            setPosition(8, 3);
            printf("�");
            setPosition(8, 5);
            printf("5 - SOBRE A NCR SYSTEM");
            opcao = 5;
        }
        else if (tecla == 54)
        {
            setPosition(4, 3);
            printf("  1 - Gerenciar funcion�rios");
            setPosition(5, 3);
            printf("  2 - Gerenciar clientes");
            setPosition(6, 3);
            printf("  3 - Gerenciar usu�rios");
            setPosition(7, 3);
            printf("  4 - Registros de log");
            setPosition(8, 3);
            printf("  5 - Sobre a NCR System");
            setPosition(9, 3);
            printf("  6 - Ajustes");
            setPosition(10, 3);
            printf("  7 - Encerrar sess�o");
            setPosition(9, 3);
            printf("�");
            setPosition(9, 5);
            printf("6 - AJUSTES");
            opcao = 6;
        }
        else if (tecla == 55)
        {
            setPosition(4, 3);
            printf("  1 - Gerenciar funcion�rios");
            setPosition(5, 3);
            printf("  2 - Gerenciar clientes");
            setPosition(6, 3);
            printf("  3 - Gerenciar usu�rios");
            setPosition(7, 3);
            printf("  4 - Registros de log");
            setPosition(8, 3);
            printf("  5 - Sobre a NCR System");
            setPosition(9, 3);
            printf("  6 - Ajustes");
            setPosition(10, 3);
            printf("  7 - Encerrar sess�o");
            setPosition(10, 3);
            printf("�");
            setPosition(10, 5);
            printf("7 - ENCERRAR SESS�O");
            opcao = 7;
        }
        setlocale(LC_ALL, "C");
    }

    switch(opcao)
    {
    case 1:
        gerenciarFuncionarios();
        break;
    case 2:
        gerenciarClientes();
        break;
    case 3:
        gerenciarUsuarios();
        break;
    case 4:
        registrosDeLog();
        break;
    case 5:
        sobreNCRSystem();
        break;
    case 6:
        ajustes();
        break;
    case 7:
        if(pergunta("Finalizar programa?", 1, 42) == 0)
        {
            menuPrincipal();
        }
        cls();
        setPosition(2,3);
        printf("PROGRAMA FINALIZADO COM SUCESSO!");
        getch();
        exit(1);
        break;
    }
}

// ---------- FUN��ES DO MENU PRINCIPAL ----------

//GERENCIAR FUNCION�RIO
void gerenciarFuncionarios()
{
    cls();

    //LAYOUT DE GERENCIAR FUNCION�RIOS
    createBox(1, 2, 3, 41);
    createBox(3, 2, 10, 41);
    setPosition(3, 2);
    printf("%c", 195);
    setPosition(3, 41);
    printf("%c", 180);

    //POSICIONANDO AS OP��ES
    setlocale(LC_ALL, "Portuguese");
    setPosition(2, 11);
    printf("GERENCIAR FUNCION�RIOS");
    setPosition(4, 3);
    printf("  1 - Cadastrar funcion�rio");
    setPosition(5, 3);
    printf("  2 - Remover funcion�rio");
    setPosition(6, 3);
    printf("  3 - Listar funcion�rios");
    setPosition(7, 3);
    printf("  4 - Ativar/Desligar funcion�rio");
    setPosition(8, 3);
    printf("  5 - Relat�rio dos funcion�rios");
    setPosition(9, 3);
    printf("  6 - Voltar");
    setPosition(4, 3);
    printf("�");
    setPosition(4, 5);
    printf("1 - CADASTRAR FUNCION�RIO");
    setlocale(LC_ALL, "C");

    //SISTEMA DE ANIMA��O PARA A INTERATIVIDADE
    int tecla;
    int opcao = 1;

    while(1)
    {
        setbuf(stdin, NULL);
        tecla = getch();

        if(tecla == ESC)
        {
            setlocale(LC_ALL, "C");
            menuPrincipal();
        }

        if (tecla==13)   // Enter
        {
            break;
        }

        if(tecla == 80 || tecla == 77)   //SETA PARA BAIXO OU SETA PARA DIREITA
        {
            switch(opcao)
            {
            case 1:
                tecla = 50;
                break;

            case 2:
                tecla = 51;
                break;

            case 3:
                tecla = 52;
                break;

            case 4:
                tecla = 53;
                break;

            case 5:
                tecla = 54;
                break;

            case 6:
                tecla = 49;
                break;
            }
        }

        if(tecla == 72 || tecla == 75)   //SETA PARA CIMA OU SETA PARA ESQUERDA
        {
            switch(opcao)
            {
            case 1:
                tecla = 54;
                break;

            case 2:
                tecla = 49;
                break;

            case 3:
                tecla = 50;
                break;

            case 4:
                tecla = 51;
                break;

            case 5:
                tecla = 52;
                break;

            case 6:
                tecla = 53;
                break;
            }
        }


        setlocale(LC_ALL, "Portuguese");
        if(tecla == 49)
        {
            setPosition(4, 3);
            printf("  1 - Cadastrar funcion�rio");
            setPosition(5, 3);
            printf("  2 - Remover funcion�rio");
            setPosition(6, 3);
            printf("  3 - Listar funcion�rios");
            setPosition(7, 3);
            printf("  4 - Ativar/Desligar funcion�rio");
            setPosition(8, 3);
            printf("  5 - Relat�rio dos funcion�rios");
            setPosition(9, 3);
            printf("  6 - Voltar");
            setPosition(4, 3);
            printf("�");
            setPosition(4, 5);
            printf("1 - CADASTRAR FUNCION�RIO");
            opcao = 1;
        }
        else if (tecla == 50)
        {
            setPosition(4, 3);
            printf("  1 - Cadastrar funcion�rio");
            setPosition(5, 3);
            printf("  2 - Remover funcion�rio");
            setPosition(6, 3);
            printf("  3 - Listar funcion�rios");
            setPosition(7, 3);
            printf("  4 - Ativar/Desligar funcion�rio");
            setPosition(8, 3);
            printf("  5 - Relat�rio dos funcion�rios");
            setPosition(9, 3);
            printf("  6 - Voltar");
            setPosition(5, 3);
            printf("�");
            setPosition(5, 5);
            printf("2 - REMOVER FUNCION�RIO");
            opcao = 2;
        }
        else if (tecla == 51)
        {
            setPosition(4, 3);
            printf("  1 - Cadastrar funcion�rio");
            setPosition(5, 3);
            printf("  2 - Remover funcion�rio");
            setPosition(6, 3);
            printf("  3 - Listar funcion�rios");
            setPosition(7, 3);
            printf("  4 - Ativar/Desligar funcion�rio");
            setPosition(8, 3);
            printf("  5 - Relat�rio dos funcion�rios");
            setPosition(9, 3);
            printf("  6 - Voltar");
            setPosition(6, 3);
            printf("�");
            setPosition(6, 5);
            printf("3 - LISTAR FUNCION�RIOS");
            opcao = 3;
        }
        else if (tecla == 52)
        {
            setPosition(4, 3);
            printf("  1 - Cadastrar funcion�rio");
            setPosition(5, 3);
            printf("  2 - Remover funcion�rio");
            setPosition(6, 3);
            printf("  3 - Listar funcion�rios");
            setPosition(7, 3);
            printf("  4 - Ativar/Desligar funcion�rio");
            setPosition(8, 3);
            printf("  5 - Relat�rio dos funcion�rios");
            setPosition(9, 3);
            printf("  6 - Voltar");
            setPosition(7, 3);
            printf("�");
            setPosition(7, 5);
            printf("4 - ATIVAR/DESLIGAR FUNCION�RIO");
            opcao = 4;
        }
        else if (tecla == 53)
        {
            setPosition(4, 3);
            printf("  1 - Cadastrar funcion�rio");
            setPosition(5, 3);
            printf("  2 - Remover funcion�rio");
            setPosition(6, 3);
            printf("  3 - Listar funcion�rios");
            setPosition(7, 3);
            printf("  4 - Ativar/Desligar funcion�rio");
            setPosition(8, 3);
            printf("  5 - Relat�rio dos funcion�rios");
            setPosition(9, 3);
            printf("  6 - Voltar");
            setPosition(8, 3);
            printf("�");
            setPosition(8, 5);
            printf("5 - RELAT�RIO DOS FUNCION�RIOS");
            opcao = 5;
        }
        else if (tecla == 54)
        {
            setPosition(4, 3);
            printf("  1 - Cadastrar funcion�rio");
            setPosition(5, 3);
            printf("  2 - Remover funcion�rio");
            setPosition(6, 3);
            printf("  3 - Listar funcion�rios");
            setPosition(7, 3);
            printf("  4 - Ativar/Desligar funcion�rio");
            setPosition(8, 3);
            printf("  5 - Relat�rio dos funcion�rios");
            setPosition(9, 3);
            printf("  6 - Voltar");
            setPosition(9, 3);
            printf("�");
            setPosition(9, 5);
            printf("6 - VOLTAR");
            opcao = 6;
        }
        setlocale(LC_ALL, "C");
    }

    switch(opcao)
    {
    case 1:
        cadastrarFuncionario();
        break;
    case 2:
        removerFuncionario();
        break;
    case 3:
        listarFuncionarios();
        break;
    case 4:
        ativarDesligarFuncionario();
        break;
    case 5:
        relatorioFuncionario();
        break;
    case 6:
        menuPrincipal();
        break;
    }
}

void cadastrarFuncionario()
{

    cls();

    //VARI�VEIS USADAS NESSA FUN��O
    int i;
    char ch = '\0';
    int ctecla = 0;
    char dia[3];
    char mes[3];
    char ano[5];
    char salarioStr[10];
    char salarioVirgula[3];


    createBox(1, 2, 3, 55);
    setlocale(LC_ALL, "Portuguese");
    setPosition(2, 18);
    printf("CADASTRAR FUNCION�RIO");
    setlocale(LC_ALL, "C");
    createBox(3, 2, 20, 55);
    setPosition(3, 2);
    printf("%c", 195);
    setPosition(3, 55);
    printf("%c", 180);

    setlocale(LC_ALL, "Portuguese");
    setPosition(4, 4);
    printf("Nome:");
    setlocale(LC_ALL, "C");
    createBox(5, 3, 7, 54);
    setlocale(LC_ALL, "Portuguese");
    setPosition(8, 4);
    printf("Fun��o:");
    setlocale(LC_ALL, "C");
    createBox(9, 3, 11, 54);
    setlocale(LC_ALL, "Portuguese");
    setPosition(12, 4);
    printf("Data de nascimento:");
    setPosition(14, 6);
    printf("/");
    setPosition(14, 9);
    printf("/");
    setlocale(LC_ALL, "C");
    createBox(13, 3, 15, 14);
    setlocale(LC_ALL, "Portuguese");
    setPosition(12, 32);
    printf("N�vel de cargo:");
    setlocale(LC_ALL, "C");
    createBox(13, 31, 15, 38);
    setlocale(LC_ALL, "Portuguese");
    setPosition(16, 4);
    printf("Sal�rio:");
    setlocale(LC_ALL, "C");
    createBox(17, 3, 19, 12);
    setPosition(18, 13);
    printf(",");
    createBox(17, 14, 19, 17);
    setlocale(LC_ALL, "Portuguese");
    setPosition(16, 32);
    printf("Data de in�cio:");
    setPosition(18, 34);
    printf("/");
    setPosition(18, 37);
    printf("/");
    setlocale(LC_ALL, "C");
    createBox(17, 31, 19, 42);

    //INPUT DO NOME
    do
    {

        limparPergunta(1, 56);

        memset(funcionario.nome, '\0', sizeof(funcionario.nome));

        for(i = 4; i < 54; i++)
        {
            setPosition(6, i);
            printf(" ");
        }

        setlocale(LC_ALL, "Portuguese");
        ch = '\0';
        ctecla = 0;
        setPosition(6, 4);
        while(ctecla<50)
        {
            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    funcionario.nome[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarFuncionarios();
                break;
            case '_':
                //VAI FAZER NADA
                break;
            default:
                funcionario.nome[ctecla] = ch;
                putch(ch);
                ctecla++;
                break;
            }
        }
        setlocale(LC_ALL, "C");

    }
    while(pergunta(" Confirmar nome?", 1, 56) == 0);
    limparPergunta(1, 56);
    for(i = 0; i < strlen(funcionario.nome); i++)
    {
        if(funcionario.nome[i] == ' ')
        {
            funcionario.nome[i] = '_';
        }
    }

    //INPUT DA FUN��O
    do
    {

        limparPergunta(1, 56);

        memset(funcionario.funcao, '\0', sizeof(funcionario.funcao));

        for(i = 4; i < 54; i++)
        {
            setPosition(10, i);
            printf(" ");
        }

        setlocale(LC_ALL, "Portuguese");
        ch = '\0';
        ctecla = 0;
        setPosition(10, 4);
        while(ctecla<50)
        {
            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    funcionario.funcao[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarFuncionarios();
                break;
            case '_':
                //VAI FAZER NADA
                break;
            default:
                funcionario.funcao[ctecla] = ch;
                putch(ch);
                ctecla++;
                break;
            }
        }
        setlocale(LC_ALL, "C");

    }
    while(pergunta(" Confirmar fun��o?", 1, 56) == 0);
    limparPergunta(1, 56);
    for(i = 0; i < strlen(funcionario.funcao); i++)
    {
        if(funcionario.funcao[i] == ' ')
        {
            funcionario.funcao[i] = '_';
        }
    }

    //INPUT DA DATA DE NASCIMENTO
    do
    {

        limparPergunta(1, 56);

        setPosition(14, 4);
        printf(" ");
        setPosition(14, 5);
        printf(" ");
        setPosition(14, 7);
        printf(" ");
        setPosition(14, 8);
        printf(" ");
        setPosition(14, 10);
        printf(" ");
        setPosition(14, 11);
        printf(" ");
        setPosition(14, 12);
        printf(" ");
        setPosition(14, 13);
        printf(" ");

        ch = '\0';
        ctecla = 0;
        setPosition(14, 4);
        memset(dia, '\0', sizeof(dia));
        while(ctecla<2)
        {
            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    dia[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarFuncionarios();
                break;
            default:
                if((ch == '0') || (ch =='1') || (ch =='2') || (ch =='3') || (ch =='4') || (ch =='5') || (ch =='6') || (ch =='7') || (ch =='8') || (ch =='9'))
                {
                    dia[ctecla] = ch;
                    putch(ch);
                    ctecla++;
                }
                break;
            }
        }

        ch = '\0';
        ctecla = 0;
        setPosition(14, 7);
        memset(mes, '\0', sizeof(mes));
        while(ctecla<2)
        {
            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    mes[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarFuncionarios();
                break;
            default:
                if((ch == '0') || (ch =='1') || (ch =='2') || (ch =='3') || (ch =='4') || (ch =='5') || (ch =='6') || (ch =='7') || (ch =='8') || (ch =='9'))
                {
                    mes[ctecla] = ch;
                    putch(ch);
                    ctecla++;
                }
                break;
            }
        }

        ch = '\0';
        ctecla = 0;
        setPosition(14, 10);
        memset(ano, '\0', sizeof(ano));
        while(ctecla<4)
        {
            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    ano[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarFuncionarios();
                break;
            default:
                if((ch == '0') || (ch =='1') || (ch =='2') || (ch =='3') || (ch =='4') || (ch =='5') || (ch =='6') || (ch =='7') || (ch =='8') || (ch =='9'))
                {
                    ano[ctecla] = ch;
                    putch(ch);
                    ctecla++;
                }
                break;
            }
        }

        if(strcmp(dia, "") == 0)
        {
            strcpy(dia, "00");
        }

        if(strlen(dia) == 1)
        {
            dia[1] = dia[0];
            dia[0] = '0';
        }

        if(strcmp(mes, "") == 0)
        {
            strcpy(mes, "00");
        }

        if(strlen(mes) == 1)
        {
            mes[1] = mes[0];
            mes[0] = '0';
        }

        if(strcmp(ano, "") == 0)
        {
            strcpy(ano, "0000");
        }

        if(strlen(ano) == 1)
        {
            ano[3] = ano[0];
            ano[2] = '0';
            ano[1] = '0';
            ano[0] = '0';
        }
        else if(strlen(ano) == 2)
        {
            ano[3] = ano[1];
            ano[2] = ano[0];
            ano[1] = '0';
            ano[0] = '0';
        }
        else if(strlen(ano) == 3)
        {
            ano[3] = ano[2];
            ano[2] = ano[1];
            ano[1] = ano[0];
            ano[0] = '0';
        }

    }
    while (pergunta(" Confirmar data?", 1, 56) == 0);
    limparPergunta(1, 56);
    memset(funcionario.data_de_nascimento, '\0', sizeof(funcionario.data_de_nascimento));
    strcpy(funcionario.data_de_nascimento, dia);
    strcat(funcionario.data_de_nascimento, "/");
    strcat(funcionario.data_de_nascimento, mes);
    strcat(funcionario.data_de_nascimento, "/");
    strcat(funcionario.data_de_nascimento, ano);

    //INPUT DO NIVEL DE CARGO
    do
    {

        limparPergunta(1, 56);

        setPosition(14, 32);
        printf(" ");
        setPosition(14, 33);
        printf(" ");
        setPosition(14, 34);
        printf(" ");
        setPosition(14, 35);
        printf(" ");
        setPosition(14, 36);
        printf(" ");
        setPosition(14, 37);
        printf(" ");

        createBox(1, 56, 3, 75);
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 59);
        printf("N�VEL DE CARGO");
        setlocale(LC_ALL, "C");
        createBox(3, 56, 9, 75);
        setPosition(3, 56);
        printf("%c", 195);
        setPosition(3, 75);
        printf("%c", 180);

        setlocale(LC_ALL, "Portuguese");
        setPosition(4, 57);
        printf("  1 - J�nior");
        setPosition(5, 57);
        printf("  2 - Pleno");
        setPosition(6, 57);
        printf("  3 - S�nior");
        setPosition(7, 57);
        printf("  4 - Master");
        setPosition(8, 57);
        printf("  5 - Outro");
        setPosition(4, 57);
        printf("�");
        setPosition(4, 59);
        printf("1 - J�NIOR");
        setlocale(LC_ALL, "C");

        int tecla;
        int opcao = 1;

        while(1)
        {
            setbuf(stdin, NULL);
            tecla = getch();

            if (tecla == ESC)
            {
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarFuncionarios();
                break;
            }

            if (tecla==13)   // Enter
            {
                break;
            }

            if(tecla == 80 || tecla == 77)   //Seta para baixo ou seta direita
            {
                switch(opcao)
                {
                case 1:
                    tecla = 50;
                    break;

                case 2:
                    tecla = 51;
                    break;

                case 3:
                    tecla = 52;
                    break;

                case 4:
                    tecla = 53;
                    break;

                case 5:
                    tecla = 49;
                    break;
                }
            }

            if(tecla == 72 || tecla == 75)   //Seta seta para cima ou esquerda
            {
                switch(opcao)
                {
                case 1:
                    tecla = 53;
                    break;

                case 2:
                    tecla = 49;
                    break;

                case 3:
                    tecla = 50;
                    break;

                case 4:
                    tecla = 51;
                    break;

                case 5:
                    tecla = 52;
                    break;
                }
            }

            setlocale(LC_ALL, "Portuguese");
            if(tecla == 49)
            {
                setPosition(4, 57);
                printf("  1 - J�nior");
                setPosition(5, 57);
                printf("  2 - Pleno");
                setPosition(6, 57);
                printf("  3 - S�nior");
                setPosition(7, 57);
                printf("  4 - Master");
                setPosition(8, 57);
                printf("  5 - Outro");
                setPosition(4, 57);
                printf("�");
                setPosition(4, 59);
                printf("1 - J�NIOR");
                opcao = 1;
            }
            else if (tecla == 50)
            {
                setPosition(4, 57);
                printf("  1 - J�nior");
                setPosition(5, 57);
                printf("  2 - Pleno");
                setPosition(6, 57);
                printf("  3 - S�nior");
                setPosition(7, 57);
                printf("  4 - Master");
                setPosition(8, 57);
                printf("  5 - Outro");
                setPosition(5, 57);
                printf("�");
                setPosition(5, 59);
                printf("2 - PLENO");
                opcao = 2;
            }
            else if (tecla == 51)
            {
                setPosition(4, 57);
                printf("  1 - J�nior");
                setPosition(5, 57);
                printf("  2 - Pleno");
                setPosition(6, 57);
                printf("  3 - S�nior");
                setPosition(7, 57);
                printf("  4 - Master");
                setPosition(8, 57);
                printf("  5 - Outro");
                setPosition(6, 57);
                printf("�");
                setPosition(6, 59);
                printf("3 - S�NIOR");
                opcao = 3;
            }
            else if (tecla == 52)
            {
                setPosition(4, 57);
                printf("  1 - J�nior");
                setPosition(5, 57);
                printf("  2 - Pleno");
                setPosition(6, 57);
                printf("  3 - S�nior");
                setPosition(7, 57);
                printf("  4 - Master");
                setPosition(8, 57);
                printf("  5 - Outro");
                setPosition(7, 57);
                printf("�");
                setPosition(7, 59);
                printf("4 - MASTER");
                opcao = 4;
            }
            else if (tecla == 53)
            {
                setPosition(4, 57);
                printf("  1 - J�nior");
                setPosition(5, 57);
                printf("  2 - Pleno");
                setPosition(6, 57);
                printf("  3 - S�nior");
                setPosition(7, 57);
                printf("  4 - Master");
                setPosition(8, 57);
                printf("  5 - Outro");
                setPosition(8, 57);
                printf("�");
                setPosition(8, 59);
                printf("5 - OUTRO");
                opcao = 5;
            }
            setlocale(LC_ALL, "C");
        }

        memset(funcionario.cargo, '\0', sizeof(funcionario.cargo));

        setlocale(LC_ALL, "Portuguese");
        switch(opcao)
        {
        case 1:
            setPosition(14, 32);
            printf("J�nior");
            strcpy(funcionario.cargo, "J�nior");
            break;
        case 2:
            setPosition(14, 32);
            printf("Pleno");
            strcpy(funcionario.cargo, "Pleno");
            break;
        case 3:
            setPosition(14, 32);
            printf("S�nior");
            strcpy(funcionario.cargo, "S�nior");
            break;
        case 4:
            setPosition(14, 32);
            printf("Master");
            strcpy(funcionario.cargo, "Master");
            break;
        case 5:
            setPosition(14, 32);
            printf("Outro");
            strcpy(funcionario.cargo, "Outro");
            break;
        }
        setlocale(LC_ALL, "C");

        limparPergunta(1, 56);
        limparPergunta(7, 56);

    }
    while(pergunta(" Confirmar cargo?", 1, 56) == 0);
    limparPergunta(1, 56);

    //INPUT DO SAL�RIO
    do
    {

        limparPergunta(1,56);
        setPosition(18,4);
        printf(" ");
        setPosition(18,5);
        printf(" ");
        setPosition(18,6);
        printf(" ");
        setPosition(18,7);
        printf(" ");
        setPosition(18,8);
        printf(" ");
        setPosition(18,9);
        printf(" ");
        setPosition(18,10);
        printf(" ");
        setPosition(18,11);
        printf(" ");
        setPosition(18,15);
        printf(" ");
        setPosition(18,16);
        printf(" ");

        memset(salarioStr, '\0', sizeof(salarioStr));
        memset(salarioVirgula, '\0', sizeof(salarioVirgula));

        ch = '\0';
        ctecla = 0;
        setPosition(18, 4);
        while(ctecla<8)
        {
            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    salarioStr[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarFuncionarios();
                break;
            default:
                if((ch == '0') || (ch =='1') || (ch =='2') || (ch =='3') || (ch =='4') || (ch =='5') || (ch =='6') || (ch =='7') || (ch =='8') || (ch =='9'))
                {
                    salarioStr[ctecla] = ch;
                    putch(ch);
                    ctecla++;
                }
                break;
            }
        }

        strcat(salarioStr, ".");

        ch = '\0';
        ctecla = 0;
        setPosition(18, 15);
        while(ctecla<2)
        {

            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    salarioVirgula[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarFuncionarios();
                break;
            default:
                if((ch == '0') || (ch =='1') || (ch =='2') || (ch =='3') || (ch =='4') || (ch =='5') || (ch =='6') || (ch =='7') || (ch =='8') || (ch =='9'))
                {
                    salarioVirgula[ctecla] = ch;
                    putch(ch);
                    ctecla++;
                }
                break;
            }
        }

    }
    while (pergunta("Confirmar salario?", 1, 56) == 0);
    limparPergunta(1, 56);
    if((strcmp(salarioStr, "") == 0) && (strcmp(salarioVirgula, "") == 0))   //Caso um dos valores de salario tiver vazio ent�o retornar� como zero
    {
        strcpy(salarioStr, "0");
        strcpy(salarioVirgula, "00");
    }
    strcat(salarioStr, salarioVirgula);
    funcionario.salario = strtod(salarioStr, NULL);

    //INPUT DA DATA DE INICIO
    do
    {

        limparPergunta(1, 56);

        setPosition(18, 32);
        printf(" ");
        setPosition(18, 33);
        printf(" ");
        setPosition(18, 35);
        printf(" ");
        setPosition(18, 36);
        printf(" ");
        setPosition(18, 38);
        printf(" ");
        setPosition(18, 39);
        printf(" ");
        setPosition(18, 40);
        printf(" ");
        setPosition(18, 41);
        printf(" ");

        ch = '\0';
        ctecla = 0;
        setPosition(18, 32);
        memset(dia, '\0', sizeof(dia));
        while(ctecla<2)
        {
            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    dia[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarFuncionarios();
                break;
            default:
                if((ch == '0') || (ch =='1') || (ch =='2') || (ch =='3') || (ch =='4') || (ch =='5') || (ch =='6') || (ch =='7') || (ch =='8') || (ch =='9'))
                {
                    dia[ctecla] = ch;
                    putch(ch);
                    ctecla++;
                }
                break;
            }
        }

        ch = '\0';
        ctecla = 0;
        setPosition(18, 35);
        memset(mes, '\0', sizeof(mes));
        while(ctecla<2)
        {
            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    mes[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarFuncionarios();
                break;
            default:
                if((ch == '0') || (ch =='1') || (ch =='2') || (ch =='3') || (ch =='4') || (ch =='5') || (ch =='6') || (ch =='7') || (ch =='8') || (ch =='9'))
                {
                    mes[ctecla] = ch;
                    putch(ch);
                    ctecla++;
                }
                break;
            }
        }

        ch = '\0';
        ctecla = 0;
        setPosition(18, 38);
        memset(ano, '\0', sizeof(ano));
        while(ctecla<4)
        {
            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    ano[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarFuncionarios();
                break;
            default:
                if((ch == '0') || (ch =='1') || (ch =='2') || (ch =='3') || (ch =='4') || (ch =='5') || (ch =='6') || (ch =='7') || (ch =='8') || (ch =='9'))
                {
                    ano[ctecla] = ch;
                    putch(ch);
                    ctecla++;
                }
                break;
            }
        }

        if(strcmp(dia, "") == 0)
        {
            strcpy(dia, "00");
        }

        if(strcmp(mes, "") == 0)
        {
            strcpy(mes, "00");
        }

        if(strcmp(ano, "") == 0)
        {
            strcpy(ano, "0000");
        }

    }
    while (pergunta(" Confirmar data?", 1, 56) == 0);
    limparPergunta(1, 56);
    memset(funcionario.data_de_inicio, '\0', sizeof(funcionario.data_de_inicio));
    strcpy(funcionario.data_de_inicio, dia);
    strcat(funcionario.data_de_inicio, "/");
    strcat(funcionario.data_de_inicio, mes);
    strcat(funcionario.data_de_inicio, "/");
    strcat(funcionario.data_de_inicio, ano);

    double salarioTotal;

    if(pergunta("Confirmar cadastro?", 1, 56) == 1)
    {
        cls();
        setlocale(LC_ALL, "Portuguese");
        //RECUPERANDO E IMPLEMENTANDO REGISTRO
        file = fopen("./Funcionarios/reg.txt", "r");
        fscanf(file, "%lu", &funcionario.id);
        fclose(file);
        file = fopen("./Funcionarios/reg.txt", "w");
        fprintf(file, "%lu", ++funcionario.id);
        fclose(file);

        //RECUPERANDO E SOMANDO O SALARIO TOTAL
        file = fopen("./Funcionarios/sal.txt", "r");
        fscanf(file, "%lf", &salarioTotal);
        fclose(file);
        salarioTotal += funcionario.salario;
        file = fopen("./Funcionarios/sal.txt", "w");
        fprintf(file, "%.2lf", salarioTotal);
        fclose(file);

        //CADASTRANDO FUNCIONARIO
        file = fopen("./Funcionarios/func.txt", "a");
        fprintf(file, "%lu %s %s %s %s %.2lf %s %s\n", funcionario.id, funcionario.nome, funcionario.funcao, funcionario.data_de_nascimento, funcionario.cargo, funcionario.salario, funcionario.data_de_inicio, "ATIVO");
        fclose(file);

        //MENSAGEM QUE FUNCION�RIO FOI CADASTRADO
        memset(mensagem, '\0', sizeof(mensagem));
        strcpy(mensagem, "CADASTROU O(A) FUNCIONARIO(A) \"");
        for(i = 0; i < strlen(funcionario.nome); i++)
        {
            if(funcionario.nome[i] == '_')
            {
                funcionario.nome[i] = ' ';
            }
        }
        strcat(mensagem, funcionario.nome);
        strcat(mensagem, "\"");
        registrarNoLog(mensagem);
        setPosition(2, 3);
        printf("CADASTRAMENTO DE FUNCION�RIO FEITO SUCESSO!");
        setlocale(LC_ALL, "C");
        getch();
        gerenciarFuncionarios();
    }
    else
    {
        cls();
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 3);
        printf("CADASTRAMENTO DE FUNCION�RIO CANCELADO COM SUCESSO!");
        setlocale(LC_ALL, "C");
        getch();
        gerenciarFuncionarios();
    }
    getch();
}

void removerFuncionario()
{

    char leitor[200];
    char analisador[200];
    memset(leitor, '\0', sizeof(leitor));
    memset(analisador, '\0', sizeof(analisador));
    strcat(analisador, dados.usuario);
    strcat(analisador, " ");
    strcat(analisador, dados.senha);
    if(strcmp(ADMIN, analisador) == 0)
    {
        memset(analisador, '\0', sizeof(analisador));
        FILE *fileTemp;

        unsigned int i;
        unsigned int beforePositionSpace;
        unsigned int afterPositionSpace;
        char salarioStr[20];
        double salarioTotal;

        memset(salarioStr, '\0', sizeof(salarioStr));
        memset(funcionario.nome, '\0', sizeof(funcionario.nome));
        memset(funcionario.funcao, '\0', sizeof(funcionario.funcao));
        memset(funcionario.data_de_nascimento, '\0', sizeof(funcionario.data_de_nascimento));
        memset(funcionario.cargo, '\0', sizeof(funcionario.cargo));
        memset(funcionario.data_de_inicio, '\0', sizeof(funcionario.data_de_inicio));
        memset(funcionario.situacao, '\0', sizeof(funcionario.situacao));

        cls();

        createBox(1, 2, 3, 55);
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 19);
        printf("REMOVER FUNCION�RIO");
        setlocale(LC_ALL, "C");
        createBox(3, 2, 24, 55);
        setPosition(3, 2);
        printf("%c", 195);
        setPosition(3, 55);
        printf("%c", 180);

        setlocale(LC_ALL, "Portuguese");
        setPosition(4, 4);
        printf("Pesquisar ID:");
        setlocale(LC_ALL, "C");
        createBox(5, 3, 7, 24);
        setlocale(LC_ALL, "Portuguese");
        setPosition(8, 4);
        printf("Nome:");
        setlocale(LC_ALL, "C");
        createBox(9, 3, 11, 54);
        setlocale(LC_ALL, "Portuguese");
        setPosition(12, 4);
        printf("Fun��o:");
        setlocale(LC_ALL, "C");
        createBox(13, 3, 15, 54);
        setlocale(LC_ALL, "Portuguese");
        setPosition(16, 4);
        printf("Data de nascimento:");
        setPosition(18, 6);
        printf("/");
        setPosition(18, 9);
        printf("/");
        setlocale(LC_ALL, "C");
        createBox(17, 3, 19, 14);
        setlocale(LC_ALL, "Portuguese");
        setPosition(16, 32);
        printf("Nivel de cargo:");
        setlocale(LC_ALL, "C");
        createBox(17, 31, 19, 38);
        setlocale(LC_ALL, "Portuguese");
        setPosition(20, 4);
        printf("Sal�rio:");
        setlocale(LC_ALL, "C");
        createBox(21, 3, 23, 17);
        setlocale(LC_ALL, "Portuguese");
        setPosition(20, 32);
        printf("Data de in�cio:");
        setPosition(22, 34);
        printf("/");
        setPosition(22, 37);
        printf("/");
        setlocale(LC_ALL, "C");
        createBox(21, 31, 23, 42);

        char id[21];
        memset(id, '\0', sizeof(id));

        char ch = '\0';
        int ctecla = 0;
        ch = '\0';
        ctecla = 0;
        setPosition(6, 4);
        while(ctecla<20)
        {
            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    id[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarFuncionarios();
                break;
            default:
                if((ch == '0') || (ch =='1') || (ch =='2') || (ch =='3') || (ch =='4') || (ch =='5') || (ch =='6') || (ch =='7') || (ch =='8') || (ch =='9'))
                {
                    id[ctecla] = ch;
                    putch(ch);
                    ctecla++;
                }
                break;
            }
        }

        strcat(id, " ");

        file = fopen("./Funcionarios/func.txt", "r");
        while(fgets(leitor, 200, file) != NULL)
        {

            for(i = 0; i < strlen(id); i++)
            {
                analisador[i] = leitor[i];
            }

            if(strcmp(analisador, id) == 0)
            {

                for(i = 0; i < strlen(leitor); i++)
                {
                    if(leitor[i] == ' ')
                    {
                        beforePositionSpace = i;
                        break;
                    }
                }

                for(i = ++beforePositionSpace; i < strlen(leitor); i++)
                {
                    if(leitor[i] == ' ')
                    {
                        afterPositionSpace = i;
                        break;
                    }
                }

                for(i = beforePositionSpace; i < afterPositionSpace; i++)
                {
                    if(leitor[i] != '_')
                    {
                        funcionario.nome[i - beforePositionSpace] = leitor[i];
                    }
                    else
                    {
                        funcionario.nome[i - beforePositionSpace] = ' ';
                    }
                }

                beforePositionSpace = afterPositionSpace;

                for(i = ++beforePositionSpace; i < strlen(leitor); i++)
                {
                    if(leitor[i] == ' ')
                    {
                        afterPositionSpace = i;
                        break;
                    }
                }

                for(i = beforePositionSpace; i < afterPositionSpace; i++)
                {
                    if(leitor[i] != '_')
                    {
                        funcionario.funcao[i - beforePositionSpace] = leitor[i];
                    }
                    else
                    {
                        funcionario.funcao[i - beforePositionSpace] = ' ';
                    }
                }

                beforePositionSpace = afterPositionSpace;

                for(i = ++beforePositionSpace; i < strlen(leitor); i++)
                {
                    if(leitor[i] == ' ')
                    {
                        afterPositionSpace = i;
                        break;
                    }
                }

                for(i = beforePositionSpace; i < afterPositionSpace; i++)
                {
                    funcionario.data_de_nascimento[i - beforePositionSpace] = leitor[i];
                }

                beforePositionSpace = afterPositionSpace;

                for(i = ++beforePositionSpace; i < strlen(leitor); i++)
                {
                    if(leitor[i] == ' ')
                    {
                        afterPositionSpace = i;
                        break;
                    }
                }

                for(i = beforePositionSpace; i < afterPositionSpace; i++)
                {
                    funcionario.cargo[i - beforePositionSpace] = leitor[i];
                }

                beforePositionSpace = afterPositionSpace;

                for(i = ++beforePositionSpace; i < strlen(leitor); i++)
                {
                    if(leitor[i] == ' ')
                    {
                        afterPositionSpace = i;
                        break;
                    }
                }

                for(i = beforePositionSpace; i < afterPositionSpace; i++)
                {
                    salarioStr[i - beforePositionSpace] = leitor[i];
                }

                beforePositionSpace = afterPositionSpace;

                for(i = ++beforePositionSpace; i < strlen(leitor); i++)
                {
                    if(leitor[i] == ' ')
                    {
                        afterPositionSpace = i;
                        break;
                    }
                }

                for(i = beforePositionSpace; i < afterPositionSpace; i++)
                {
                    funcionario.data_de_inicio[i - beforePositionSpace] = leitor[i];
                }

                beforePositionSpace = afterPositionSpace;

                for(i = ++beforePositionSpace; i < strlen(leitor); i++)
                {
                    if(leitor[i] == '\n')
                    {
                        afterPositionSpace = i;
                        break;
                    }
                }

                for(i = beforePositionSpace; i < afterPositionSpace; i++)
                {
                    funcionario.situacao[i - beforePositionSpace] = leitor[i];
                }

                break;
            }
            else
            {
                memset(analisador, '\0', sizeof(analisador));
                memset(leitor, '\0', sizeof(leitor));
                continue;
            }

        }
        fclose(file);

        if(strcmp(analisador, id) == 0)
        {

            setlocale(LC_ALL, "Portuguese");
            setPosition(10, 4);
            printf("%s", funcionario.nome);
            setPosition(14, 4);
            printf("%s", funcionario.funcao);
            setPosition(18, 4);
            printf("%s", funcionario.data_de_nascimento);
            setPosition(18, 32);
            printf("%s", funcionario.cargo);
            setPosition(22, 4);
            printf("%s", salarioStr);
            setPosition(22, 32);
            printf("%s", funcionario.data_de_inicio);
            setPosition(6, 30);
            printf("%s", funcionario.situacao);
            setlocale(LC_ALL, "C");


            memset(analisador, '\0', sizeof(analisador));
            memset(leitor, '\0', sizeof(leitor));
            if(pergunta("Confirmar remo��o?", 1, 56) == 1)
            {
                file = fopen("./Funcionarios/func.txt", "r");
                fileTemp = fopen("./Funcionarios/funcTemp.txt", "w");

                while(fgets(leitor, 200, file) != NULL)
                {
                    for(i = 0; i < strlen(id); i++)
                    {
                        analisador[i] = leitor[i];
                    }

                    if(strcmp(analisador, id) != 0)
                    {
                        fprintf(fileTemp, "%s", leitor);
                    }

                    memset(analisador, '\0', sizeof(analisador));
                    memset(leitor, '\0', sizeof(leitor));

                }
                fclose(file);
                fclose(fileTemp);

                remove("./Funcionarios/func.txt");
                rename("./Funcionarios/funcTemp.txt", "./Funcionarios/func.txt");

                file = fopen("./Funcionarios/sal.txt", "r");

                funcionario.salario = strtod(salarioStr, NULL);

                //RECUPERANDO E SUBTRAINDO O SALARIO TOTAL COM O SALARIO DO FUNCIONARIO REMOVIDO
                file = fopen("./Funcionarios/sal.txt", "r");
                fscanf(file, "%lf", &salarioTotal);
                fclose(file);
                salarioTotal -= funcionario.salario;
                file = fopen("./Funcionarios/sal.txt", "w");
                fprintf(file, "%.2lf", salarioTotal);
                fclose(file);

                //REGISTRANDO MENSAGEM NO LOG
                memset(mensagem, '\0', sizeof(mensagem));
                strcpy(mensagem, "REMOVEU O(A) FUNCIONARIO(A) \"");
                strcat(mensagem, funcionario.nome);
                strcat(mensagem, "\"");
                registrarNoLog(mensagem);

                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("REMO��O DE FUNCION�RIO(A) REALIZADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarFuncionarios();

            }
            else
            {
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("REMO��O DE FUNCION�RIO(A) CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarFuncionarios();
            }
        }
        else
        {
            setlocale(LC_ALL, "Portuguese");
            setPosition(26, 3);
            printf("ERRO: FUNCION�RIO N�O ENCONTRADO!");
            setlocale(LC_ALL, "C");
            if(pergunta("Continuar opera��o?", 1, 56) == 1)
            {
                removerFuncionario();
            }
            else
            {
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarFuncionarios();
            }
        }
    }
    else
    {
        cls();
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 3);
        printf("ERRO: ACESSO NEGADO, VOC� N�O TEM PERMISS�O PARA ACESSAR ESTE M�DULO!");
        setlocale(LC_ALL, "C");
        getch();
        gerenciarFuncionarios();
    }
}

void listarFuncionarios()
{

    cls();

    unsigned long int quantFuncionarios = 0;
    unsigned long int linha = 4;
    unsigned int i;
    unsigned int beforePositionSpace;
    unsigned int afterPositionSpace;
    char salarioStr[22];

    char leitor[200];
    char analisador[200];
    memset(leitor, '\0', sizeof(leitor));
    memset(analisador, '\0', sizeof(analisador));
    strcat(analisador, dados.usuario);
    strcat(analisador, " ");
    strcat(analisador, dados.senha);
    if(strcmp(ADMIN, analisador) == 0)
    {
        memset(analisador, '\0', sizeof(analisador));
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 3);
        printf("---------- LISTA DE FUNCION�RIOS ----------");
        setlocale(LC_ALL, "C");

        setlocale(LC_ALL, "Portuguese");
        file = fopen("./Funcionarios/func.txt", "r");
        while(fgets(leitor, 200, file) != NULL)
        {

            memset(funcionario.nome, '\0', sizeof(funcionario.nome));
            memset(funcionario.funcao, '\0', sizeof(funcionario.funcao));
            memset(funcionario.data_de_nascimento, '\0', sizeof(funcionario.data_de_nascimento));
            memset(funcionario.cargo, '\0', sizeof(funcionario.cargo));
            memset(salarioStr, '\0', sizeof(salarioStr));
            memset(funcionario.data_de_inicio, '\0', sizeof(funcionario.data_de_inicio));
            memset(funcionario.situacao, '\0', sizeof(funcionario.situacao));

            for(i = 0; i < strlen(leitor); i++)
            {
                analisador[i] = leitor[i];
                if(leitor[i] == ' ')
                {
                    beforePositionSpace = i;
                    break;
                }
            }

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                if(leitor[i] != '_')
                {
                    funcionario.nome[i - beforePositionSpace] = leitor[i];
                }
                else
                {
                    funcionario.nome[i - beforePositionSpace] = ' ';
                }
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                if(leitor[i] != '_')
                {
                    funcionario.funcao[i - beforePositionSpace] = leitor[i];
                }
                else
                {
                    funcionario.funcao[i - beforePositionSpace] = ' ';
                }
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                funcionario.data_de_nascimento[i - beforePositionSpace] = leitor[i];
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                funcionario.cargo[i - beforePositionSpace] = leitor[i];
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                salarioStr[i - beforePositionSpace] = leitor[i];
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                funcionario.data_de_inicio[i - beforePositionSpace] = leitor[i];
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == '\n')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                funcionario.situacao[i - beforePositionSpace] = leitor[i];
            }

            setPosition(linha,4);
            printf("ID....................: %s", analisador);
            linha++;
            setPosition(linha,4);
            printf("NOME..................: %s", funcionario.nome);
            linha++;
            setPosition(linha,4);
            printf("FUN��O................: %s", funcionario.funcao);
            linha++;
            setPosition(linha,4);
            printf("DATA DE NASCIMENTO....: %s", funcionario.data_de_nascimento);
            linha++;
            setPosition(linha,4);
            printf("N�VEL DE CARGO........: %s", funcionario.cargo);
            linha++;
            setPosition(linha,4);
            printf("SAL�RIO...............: %s", salarioStr);
            linha++;
            setPosition(linha,4);
            printf("DATA DE IN�CIO........: %s", funcionario.data_de_inicio);
            linha++;
            setPosition(linha,4);
            printf("SITUA��O..............: %s", funcionario.situacao);
            linha++;
            linha++;

            quantFuncionarios++;

            memset(analisador, '\0', sizeof(analisador));
            memset(leitor, '\0', sizeof(leitor));
        }
        fclose(file);
    }
    else
    {
        memset(analisador, '\0', sizeof(analisador));
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 3);
        printf("---------- LISTA DE FUNCION�RIOS ----------");
        setlocale(LC_ALL, "C");

        setlocale(LC_ALL, "Portuguese");
        file = fopen("./Funcionarios/func.txt", "r");
        while(fgets(leitor, 200, file) != NULL)
        {

            memset(funcionario.nome, '\0', sizeof(funcionario.nome));
            memset(funcionario.funcao, '\0', sizeof(funcionario.funcao));
            memset(funcionario.data_de_nascimento, '\0', sizeof(funcionario.data_de_nascimento));
            memset(funcionario.cargo, '\0', sizeof(funcionario.cargo));
            memset(salarioStr, '\0', sizeof(salarioStr));
            memset(funcionario.data_de_inicio, '\0', sizeof(funcionario.data_de_inicio));
            memset(funcionario.situacao, '\0', sizeof(funcionario.situacao));

            for(i = 0; i < strlen(leitor); i++)
            {
                analisador[i] = leitor[i];
                if(leitor[i] == ' ')
                {
                    beforePositionSpace = i;
                    break;
                }
            }

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                if(leitor[i] != '_')
                {
                    funcionario.nome[i - beforePositionSpace] = leitor[i];
                }
                else
                {
                    funcionario.nome[i - beforePositionSpace] = ' ';
                }
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                if(leitor[i] != '_')
                {
                    funcionario.funcao[i - beforePositionSpace] = leitor[i];
                }
                else
                {
                    funcionario.funcao[i - beforePositionSpace] = ' ';
                }
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                funcionario.data_de_nascimento[i - beforePositionSpace] = leitor[i];
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                funcionario.cargo[i - beforePositionSpace] = leitor[i];
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                salarioStr[i - beforePositionSpace] = leitor[i];
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                funcionario.data_de_inicio[i - beforePositionSpace] = leitor[i];
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == '\n')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                funcionario.situacao[i - beforePositionSpace] = leitor[i];
            }

            setPosition(linha,4);
            printf("ID....................: %s", analisador);
            linha++;
            setPosition(linha,4);
            printf("NOME..................: %s", funcionario.nome);
            linha++;
            setPosition(linha,4);
            printf("FUN��O................: %s", funcionario.funcao);
            linha++;
            setPosition(linha,4);
            printf("N�VEL DE CARGO........: %s", funcionario.cargo);
            linha++;
            setPosition(linha,4);
            printf("DATA DE IN�CIO........: %s", funcionario.data_de_inicio);
            linha++;
            setPosition(linha,4);
            printf("SITUA��O..............: %s", funcionario.situacao);
            linha++;
            linha++;

            quantFuncionarios++;

            memset(analisador, '\0', sizeof(analisador));
            memset(leitor, '\0', sizeof(leitor));
        }
        fclose(file);
    }
    setPosition(linha, 3);
    printf("-------------------------------------------\n");
    setPosition(linha+1, 3);
    printf("Quantidade de funcion�rios: %lu", quantFuncionarios);
    setPosition(linha+3, 3);
    printf("PRESSIONE QUALQUER TECLA PARA VOLTAR...");
    setlocale(LC_ALL, "C");
    getch();
    gerenciarFuncionarios();
}

void ativarDesligarFuncionario()
{
    char leitor[200];
    char analisador[200];
    memset(leitor, '\0', sizeof(leitor));
    memset(analisador, '\0', sizeof(analisador));

    memset(analisador, '\0', sizeof(analisador));
    FILE *fileTemp;

    unsigned int i;
    unsigned int beforePositionSpace;
    unsigned int afterPositionSpace;
    char salarioStr[20];
    double salarioTotal;

    memset(salarioStr, '\0', sizeof(salarioStr));
    memset(funcionario.nome, '\0', sizeof(funcionario.nome));
    memset(funcionario.funcao, '\0', sizeof(funcionario.funcao));
    memset(funcionario.data_de_nascimento, '\0', sizeof(funcionario.data_de_nascimento));
    memset(funcionario.cargo, '\0', sizeof(funcionario.cargo));
    memset(funcionario.data_de_inicio, '\0', sizeof(funcionario.data_de_inicio));
    memset(funcionario.situacao, '\0', sizeof(funcionario.situacao));

    cls();

    createBox(1, 2, 3, 55);
    setlocale(LC_ALL, "Portuguese");
    setPosition(2, 15);
    printf("ATIVAR/DESLIGAR FUNCION�RIO");
    setlocale(LC_ALL, "C");
    createBox(3, 2, 24, 55);
    setPosition(3, 2);
    printf("%c", 195);
    setPosition(3, 55);
    printf("%c", 180);

    setlocale(LC_ALL, "Portuguese");
    setPosition(4, 4);
    printf("Pesquisar ID:");
    setlocale(LC_ALL, "C");
    createBox(5, 3, 7, 24);
    setlocale(LC_ALL, "Portuguese");
    setPosition(8, 4);
    printf("Nome:");
    setlocale(LC_ALL, "C");
    createBox(9, 3, 11, 54);
    setlocale(LC_ALL, "Portuguese");
    setPosition(12, 4);
    printf("Fun��o:");
    setlocale(LC_ALL, "C");
    createBox(13, 3, 15, 54);
    setlocale(LC_ALL, "Portuguese");
    setPosition(16, 4);
    printf("Data de nascimento:");
    setPosition(18, 6);
    printf("/");
    setPosition(18, 9);
    printf("/");
    setlocale(LC_ALL, "C");
    createBox(17, 3, 19, 14);
    setlocale(LC_ALL, "Portuguese");
    setPosition(16, 32);
    printf("Nivel de cargo:");
    setlocale(LC_ALL, "C");
    createBox(17, 31, 19, 38);
    setlocale(LC_ALL, "Portuguese");
    setPosition(20, 4);
    printf("Sal�rio:");
    setlocale(LC_ALL, "C");
    createBox(21, 3, 23, 17);
    setlocale(LC_ALL, "Portuguese");
    setPosition(20, 32);
    printf("Data de in�cio:");
    setPosition(22, 34);
    printf("/");
    setPosition(22, 37);
    printf("/");
    setlocale(LC_ALL, "C");
    createBox(21, 31, 23, 42);

    char id[21];
    memset(id, '\0', sizeof(id));

    char ch = '\0';
    int ctecla = 0;
    ch = '\0';
    ctecla = 0;
    setPosition(6, 4);
    while(ctecla<20)
    {
        ch = getch();

        switch(ch)
        {
        case BACKSPACE:
            if(ctecla>0)
            {
                fflush(stdin);
                putch(BACKSPACE);
                ch = '\0';
                id[ctecla-1] = ch;
                ctecla--;
                putch(SPACE);
                putch(BACKSPACE);
            }
            break;
        case TAB:
            putch(TAB);
            ctecla = 50;
            break;
        case ENTER:
            putch(ENTER);
            ctecla = 50;
            break;
        case ESC:
            cls();
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("OPERA��O CANCELADA COM SUCESSO!");
            setlocale(LC_ALL, "C");
            getch();
            gerenciarFuncionarios();
            break;
        default:
            if((ch == '0') || (ch =='1') || (ch =='2') || (ch =='3') || (ch =='4') || (ch =='5') || (ch =='6') || (ch =='7') || (ch =='8') || (ch =='9'))
            {
                id[ctecla] = ch;
                putch(ch);
                ctecla++;
            }
            break;
        }
    }

    strcat(id, " ");

    file = fopen("./Funcionarios/func.txt", "r");
    while(fgets(leitor, 200, file) != NULL)
    {

        for(i = 0; i < strlen(id); i++)
        {
            analisador[i] = leitor[i];
        }

        if(strcmp(analisador, id) == 0)
        {

            for(i = 0; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    beforePositionSpace = i;
                    break;
                }
            }

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                if(leitor[i] != '_')
                {
                    funcionario.nome[i - beforePositionSpace] = leitor[i];
                }
                else
                {
                    funcionario.nome[i - beforePositionSpace] = ' ';
                }
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                if(leitor[i] != '_')
                {
                    funcionario.funcao[i - beforePositionSpace] = leitor[i];
                }
                else
                {
                    funcionario.funcao[i - beforePositionSpace] = ' ';
                }
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                funcionario.data_de_nascimento[i - beforePositionSpace] = leitor[i];
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                funcionario.cargo[i - beforePositionSpace] = leitor[i];
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                salarioStr[i - beforePositionSpace] = leitor[i];
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                funcionario.data_de_inicio[i - beforePositionSpace] = leitor[i];
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == '\n')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                funcionario.situacao[i - beforePositionSpace] = leitor[i];
            }

            break;
        }
        else
        {
            memset(analisador, '\0', sizeof(analisador));
            memset(leitor, '\0', sizeof(leitor));
            continue;
        }

    }
    fclose(file);

    char dadosLogin[100];
    strcpy(dadosLogin, dados.usuario);
    strcat(dadosLogin, " ");
    strcat(dadosLogin, dados.senha);

    if(strcmp(analisador, id) == 0)   //SE O ID FOR ENCONTRADO
    {
        setlocale(LC_ALL, "Portuguese");

        if(strcmp(ADMIN, dadosLogin) == 0)  //LIMITANDO AS INFORMA��ES PARA USU�RIO COMUM
        {
            setPosition(18, 4);
            printf("%s", funcionario.data_de_nascimento);
            setPosition(22, 4);
            printf("%s", salarioStr);
        }
        setPosition(10, 4);
        printf("%s", funcionario.nome);
        setPosition(14, 4);
        printf("%s", funcionario.funcao);
        setPosition(18, 32);
        printf("%s", funcionario.cargo);
        setPosition(22, 32);
        printf("%s", funcionario.data_de_inicio);
        setPosition(6, 30);
        printf("%s", funcionario.situacao);
        setlocale(LC_ALL, "C");

        for(i = 0; i < strlen(funcionario.nome); i++)
        {
            if(funcionario.nome[i] == ' ')
            {
                funcionario.nome[i] = '_';
            }
        }

        for(i = 0; i < strlen(funcionario.funcao); i++)
        {
            if(funcionario.funcao[i] == ' ')
            {
                funcionario.funcao[i] = '_';
            }
        }

        funcionario.salario = strtod(salarioStr, NULL);

        if(strcmp(funcionario.situacao, "ATIVO") == 0)  //CASO O FUNCION�RIO ESTIVER ATIVO
        {
            if(pergunta("Deseja deslig�-lo?", 1, 56) == 1)
            {
                strcpy(funcionario.situacao, "DESLIGADO");

                //RECUPERANDO E SUBTRAINDO O SALARIO TOTAL COM O SALARIO DO FUNCIONARIO DESLIGADO
                setlocale(LC_ALL, "Portuguese");
                file = fopen("./Funcionarios/sal.txt", "r");
                fscanf(file, "%lf", &salarioTotal);
                fclose(file);
                salarioTotal -= funcionario.salario;
                file = fopen("./Funcionarios/sal.txt", "w");
                fprintf(file, "%.2lf", salarioTotal);
                fclose(file);
                setlocale(LC_ALL, "C");

                file = fopen("./Funcionarios/func.txt", "r");
                fileTemp = fopen("./Funcionarios/funcTemp.txt", "w");
                while(fgets(leitor, 200, file) != NULL)
                {

                    for(i = 0; i < strlen(id); i++)
                    {
                        analisador[i] = leitor[i];
                    }

                    if(strcmp(analisador, id) == 0)
                    {
                        fprintf(fileTemp, "%s%s %s %s %s %s %s %s\n", id, funcionario.nome, funcionario.funcao, funcionario.data_de_nascimento, funcionario.cargo, salarioStr, funcionario.data_de_inicio, funcionario.situacao);
                    }
                    else
                    {
                        fprintf(fileTemp, "%s", leitor);
                    }

                    memset(analisador, '\0', sizeof(analisador));
                    memset(leitor, '\0', sizeof(leitor));
                }
                fclose(file);
                fclose(fileTemp);

                remove("./Funcionarios/func.txt");
                rename("./Funcionarios/funcTemp.txt", "./Funcionarios/func.txt");

                for(i = 0; i < strlen(funcionario.nome); i++)
                {
                    if(funcionario.nome[i] == '_')
                    {
                        funcionario.nome[i] = ' ';
                    }
                }

                memset(mensagem, '\0', sizeof(mensagem));
                strcpy(mensagem, "DESLIGOU O(A) FUNCIONARIO(A) \"");
                strcat(mensagem, funcionario.nome);
                strcat(mensagem, "\"");
                registrarNoLog(mensagem);

                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("DESLIGAMENTO DE FUNCION�RIO(A) REALIZADO COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarFuncionarios();
            }
            else
            {
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("DESLIGAMENTO DE FUNCION�RIO(A) CANCELADO COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarFuncionarios();
            }
        }
        else     //CASO O FUNCIONARIO ESTIVER DELIGADO
        {
            if(pergunta("Deseja ativ�-lo?", 1, 56) == 1)
            {
                strcpy(funcionario.situacao, "ATIVO");

                //RECUPERANDO E SOMANDO O SALARIO TOTAL COM O SALARIO DO FUNCIONARIO ATIVADO
                setlocale(LC_ALL, "Portuguese");
                file = fopen("./Funcionarios/sal.txt", "r");
                fscanf(file, "%lf", &salarioTotal);
                fclose(file);
                salarioTotal += funcionario.salario;
                file = fopen("./Funcionarios/sal.txt", "w");
                fprintf(file, "%.2lf", salarioTotal);
                fclose(file);
                setlocale(LC_ALL, "C");

                file = fopen("./Funcionarios/func.txt", "r");
                fileTemp = fopen("./Funcionarios/funcTemp.txt", "w");
                while(fgets(leitor, 200, file) != NULL)
                {

                    for(i = 0; i < strlen(id); i++)
                    {
                        analisador[i] = leitor[i];
                    }

                    if(strcmp(analisador, id) == 0)
                    {
                        fprintf(fileTemp, "%s%s %s %s %s %s %s %s\n", id, funcionario.nome, funcionario.funcao, funcionario.data_de_nascimento, funcionario.cargo, salarioStr, funcionario.data_de_inicio, funcionario.situacao);
                    }
                    else
                    {
                        fprintf(fileTemp, "%s", leitor);
                    }

                    memset(analisador, '\0', sizeof(analisador));
                    memset(leitor, '\0', sizeof(leitor));
                }
                fclose(file);
                fclose(fileTemp);

                remove("./Funcionarios/func.txt");
                rename("./Funcionarios/funcTemp.txt", "./Funcionarios/func.txt");

                for(i = 0; i < strlen(funcionario.nome); i++)
                {
                    if(funcionario.nome[i] == '_')
                    {
                        funcionario.nome[i] = ' ';
                    }
                }

                memset(mensagem, '\0', sizeof(mensagem));
                strcpy(mensagem, "ATIVOU NOVAMENTE O(A) FUNCIONARIO(A) \"");
                strcat(mensagem, funcionario.nome);
                strcat(mensagem, "\"");
                registrarNoLog(mensagem);

                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("ATIVAMENTO DE FUNCION�RIO(A) REALIZADO COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarFuncionarios();

            }
            else
            {
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("ATIVAMENTO DE FUNCION�RIO(A) CANCELADO COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarFuncionarios();
            }
        }
    }
    else     //CASO O FUNCION�RIO N�O FOR ENCONTRADO
    {
        setlocale(LC_ALL, "Portuguese");
        setPosition(26, 3);
        printf("ERRO: FUNCION�RIO N�O ENCONTRADO!");
        setlocale(LC_ALL, "C");
        if(pergunta("Continuar opera��o?", 1, 56) == 1)
        {
            ativarDesligarFuncionario();
        }
        else
        {
            cls();
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("OPERA��O CANCELADA COM SUCESSO!");
            setlocale(LC_ALL, "C");
            getch();
            gerenciarFuncionarios();
        }
    }
}

void relatorioFuncionario()
{
    cls();

    unsigned long int quantFuncionarios = 0;
    unsigned long int quantJunior = 0;
    unsigned long int quantPleno = 0;
    unsigned long int quantSenior = 0;
    unsigned long int quantMaster = 0;
    unsigned long int quantOutro = 0;
    double salarioTotalJunior = 0;
    double salarioTotalPleno = 0;
    double salarioTotalSenior = 0;
    double salarioTotalMaster = 0;
    double salarioTotalOutro = 0;
    double mediaSalarial = 0;
    double salarioTotal = 0;

    char salarioStr[20];

    unsigned int i;
    unsigned int beforePositionSpace;
    unsigned int afterPositionSpace;
    char leitor[200];
    char analisador[200];
    memset(leitor, '\0', sizeof(leitor));
    memset(analisador, '\0', sizeof(analisador));
    strcat(analisador, dados.usuario);
    strcat(analisador, " ");
    strcat(analisador, dados.senha);
    if(strcmp(ADMIN, analisador) == 0)
    {
        memset(analisador, '\0', sizeof(analisador));
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 3);
        printf("---------- RELAT�RIO DOS FUNCION�RIOS ----------");
        setlocale(LC_ALL, "C");

        setlocale(LC_ALL, "Portuguese");
        file = fopen("./Funcionarios/func.txt", "r");
        while(fgets(leitor, 200, file) != NULL)
        {

            memset(funcionario.nome, '\0', sizeof(funcionario.nome));
            memset(funcionario.funcao, '\0', sizeof(funcionario.funcao));
            memset(funcionario.data_de_nascimento, '\0', sizeof(funcionario.data_de_nascimento));
            memset(funcionario.cargo, '\0', sizeof(funcionario.cargo));
            memset(salarioStr, '\0', sizeof(salarioStr));
            memset(funcionario.data_de_inicio, '\0', sizeof(funcionario.data_de_inicio));
            memset(funcionario.situacao, '\0', sizeof(funcionario.situacao));

            for(i = 0; i < strlen(leitor); i++)
            {
                analisador[i] = leitor[i];
                if(leitor[i] == ' ')
                {
                    beforePositionSpace = i;
                    break;
                }
            }

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                if(leitor[i] != '_')
                {
                    funcionario.nome[i - beforePositionSpace] = leitor[i];
                }
                else
                {
                    funcionario.nome[i - beforePositionSpace] = ' ';
                }
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                if(leitor[i] != '_')
                {
                    funcionario.funcao[i - beforePositionSpace] = leitor[i];
                }
                else
                {
                    funcionario.funcao[i - beforePositionSpace] = ' ';
                }
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                funcionario.data_de_nascimento[i - beforePositionSpace] = leitor[i];
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                funcionario.cargo[i - beforePositionSpace] = leitor[i];
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                salarioStr[i - beforePositionSpace] = leitor[i];
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                funcionario.data_de_inicio[i - beforePositionSpace] = leitor[i];
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == '\n')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                funcionario.situacao[i - beforePositionSpace] = leitor[i];
            }

            funcionario.salario = strtod(salarioStr, NULL);

            if(strcmp(funcionario.situacao, "ATIVO") == 0)
            {
                quantFuncionarios++;
                salarioTotal += funcionario.salario;
            }
            if((strcmp(funcionario.cargo, "J�nior") == 0) && (strcmp(funcionario.situacao, "ATIVO") == 0))
            {
                quantJunior++;
                salarioTotalJunior += funcionario.salario;
            }

            if((strcmp(funcionario.cargo, "Pleno") == 0) && (strcmp(funcionario.situacao, "ATIVO") == 0))
            {
                quantPleno++;
                salarioTotalPleno += funcionario.salario;
            }

            if((strcmp(funcionario.cargo, "S�nior") == 0) && (strcmp(funcionario.situacao, "ATIVO") == 0))
            {
                quantSenior++;
                salarioTotalSenior += funcionario.salario;
            }

            if((strcmp(funcionario.cargo, "Master") == 0) && (strcmp(funcionario.situacao, "ATIVO") == 0))
            {
                quantMaster++;
                salarioTotalMaster += funcionario.salario;
            }

            if((strcmp(funcionario.cargo, "Outro") == 0) && (strcmp(funcionario.situacao, "ATIVO") == 0))
            {
                quantOutro++;
                salarioTotalOutro += funcionario.salario;
            }

            memset(analisador, '\0', sizeof(analisador));
            memset(leitor, '\0', sizeof(leitor));
        }
        fclose(file);
        setlocale(LC_ALL, "C");

        if(quantFuncionarios == 0)
        {
            mediaSalarial = 0;
        }
        else
        {
            mediaSalarial = salarioTotal/quantFuncionarios;
        }

        setlocale(LC_ALL, "Portuguese");
        setPosition(4, 3);
        printf("QUANTIDADE TOTAL DE FUNCION�RIOS......................: %lu", quantFuncionarios);
        setPosition(5, 3);
        printf("QUANTIDADE DE FUNCION�RIOS NO CARGO DE \"J�NIOR\".......: %lu", quantJunior);
        setPosition(6, 3);
        printf("QUANTIDADE DE FUNCION�RIOS NO CARGO DE \"PLENO\"........: %lu", quantPleno);
        setPosition(7, 3);
        printf("QUANTIDADE DE FUNCION�RIOS NO CARGO DE \"S�NIOR\".......: %lu", quantSenior);
        setPosition(8, 3);
        printf("QUANTIDADE DE FUNCION�RIOS NO CARGO DE \"MASTER\".......: %lu", quantMaster);
        setPosition(9, 3);
        printf("QUANTIDADE DE FUNCION�RIOS NO CARGO DE \"OUTRO\"........: %lu", quantOutro);
        setPosition(10, 3);
        printf("SAL�RIO TOTAL DOS FUNCION�RIOS NO CARGO DE \"J�NIOR\"...: R$%.2lf", salarioTotalJunior);
        setPosition(11, 3);
        printf("SAL�RIO TOTAL DOS FUNCION�RIOS NO CARGO DE \"PLENO\"....: R$%.2lf", salarioTotalPleno);
        setPosition(12, 3);
        printf("SAL�RIO TOTAL DOS FUNCION�RIOS NO CARGO DE \"S�NIOR\"...: R$%.2lf", salarioTotalSenior);
        setPosition(13, 3);
        printf("SAL�RIO TOTAL DOS FUNCION�RIOS NO CARGO DE \"MASTER\"...: R$%.2lf", salarioTotalMaster);
        setPosition(14, 3);
        printf("SAL�RIO TOTAL DOS FUNCION�RIOS NO CARGO DE \"OUTRO\"....: R$%.2lf", salarioTotalOutro);
        setPosition(15, 3);
        printf("M�DIA SALARIAL DE TODOS OS FUNCION�RIOS...............: R$%.2lf", mediaSalarial);
        setPosition(16, 3);
        printf("SAL�RIO TOTAL DE TODOS OS FUNCION�RIOS................: R$%.2lf", salarioTotal);
        setlocale(LC_ALL, "C");

        setlocale(LC_ALL, "Portuguese");
        setPosition(18, 3);
        printf("------------------------------------------------\n");
        setPosition(19, 3);
        printf("PRESSIONE QUALQUER TECLA PARA VOLTAR...");
        setlocale(LC_ALL, "C");
        getch();
        gerenciarFuncionarios();
    }
    else
    {
        cls();
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 3);
        printf("ERRO: ACESSO NEGADO, VOC� N�O TEM PERMISS�O PARA ACESSAR ESTE M�DULO!");
        setlocale(LC_ALL, "C");
        getch();
        gerenciarFuncionarios();
    }
}

//GERENCIAR CLIENTES
void gerenciarClientes()
{
    cls();
    //Criando o layout
    createBox(1, 2, 3, 41);
    createBox(3, 2, 9, 41);
    setPosition(3, 2);
    printf("%c", 195);
    setPosition(3, 41);
    printf("%c", 180);

    setlocale(LC_ALL, "Portuguese");
    setPosition(2, 11);
    printf("GERENCIAR CLIENTES");
    setPosition(4, 3);
    printf("  1 - Cadastrar Cliente");
    setPosition(5, 3);
    printf("  2 - Remover Cliente");
    setPosition(6, 3);
    printf("  3 - Listar Clientes");
    setPosition(7, 3);
    printf("  4 - Modificar Cliente");
    setPosition(8, 3);
    printf("  5 - Voltar");
    setPosition(4, 3);
    printf("�");
    setPosition(4, 5);
    printf("1 - CADASTRAR CLIENTE");
    setlocale(LC_ALL, "C");

    //Anima��o na troca de op��o
    int tecla;
    int opcao = 1;

    while(1)
    {
        setbuf(stdin, NULL);
        tecla = getch();

        if(tecla == ESC)
        {
            menuPrincipal();
        }

        if (tecla==13)   // Enter
        {
            break;
        }

        if(tecla == 80 || tecla == 77)   //Seta para baixo ou seta direita
        {
            switch(opcao)
            {
            case 1:
                tecla = 50;
                break;

            case 2:
                tecla = 51;
                break;

            case 3:
                tecla = 52;
                break;

            case 4:
                tecla = 53;
                break;

            case 5:
                tecla = 49;
                break;
            }
        }

        if(tecla == 72 || tecla == 75)   //Seta seta para cima ou esquerda
        {
            switch(opcao)
            {
            case 1:
                tecla = 53;
                break;

            case 2:
                tecla = 49;
                break;

            case 3:
                tecla = 50;
                break;

            case 4:
                tecla = 51;
                break;

            case 5:
                tecla = 52;
                break;

            }
        }


        setlocale(LC_ALL, "Portuguese");
        if(tecla == 49)
        {
            setPosition(2, 11);
            printf("GERENCIAR CLIENTES");
            setPosition(4, 3);
            printf("  1 - Cadastrar Cliente");
            setPosition(5, 3);
            printf("  2 - Remover Cliente");
            setPosition(6, 3);
            printf("  3 - Listar Clientes");
            setPosition(7, 3);
            printf("  4 - Modificar Cliente");
            setPosition(8, 3);
            printf("  5 - Voltar");
            setPosition(4, 3);
            printf("�");
            setPosition(4, 5);
            printf("1 - CADASTRAR CLIENTE");
            opcao = 1;
        }
        else if (tecla == 50)
        {
            setPosition(2, 11);
            printf("GERENCIAR CLIENTES");
            setPosition(4, 3);
            printf("  1 - Cadastrar Cliente");
            setPosition(5, 3);
            printf("  2 - Remover Cliente");
            setPosition(6, 3);
            printf("  3 - Listar Clientes");
            setPosition(7, 3);
            printf("  4 - Modificar Cliente");
            setPosition(8, 3);
            printf("  5 - Voltar");
            setPosition(5, 3);
            printf("�");
            setPosition(5, 5);
            printf("2 - REMOVER CLIENTE");
            opcao = 2;
        }
        else if (tecla == 51)
        {
            setPosition(2, 11);
            printf("GERENCIAR CLIENTES");
            setPosition(4, 3);
            printf("  1 - Cadastrar Cliente");
            setPosition(5, 3);
            printf("  2 - Remover Cliente");
            setPosition(6, 3);
            printf("  3 - Listar Clientes");
            setPosition(7, 3);
            printf("  4 - Modificar Cliente");
            setPosition(8, 3);
            printf("  5 - Voltar");
            setPosition(6, 3);
            printf("�");
            setPosition(6, 5);
            printf("3 - LISTAR CLIENTES");
            opcao = 3;
        }
        else if (tecla == 52)
        {
            setPosition(2, 11);
            printf("GERENCIAR CLIENTES");
            setPosition(4, 3);
            printf("  1 - Cadastrar Cliente");
            setPosition(5, 3);
            printf("  2 - Remover Cliente");
            setPosition(6, 3);
            printf("  3 - Listar Clientes");
            setPosition(7, 3);
            printf("  4 - Modificar Cliente");
            setPosition(8, 3);
            printf("  5 - Voltar");
            setPosition(7, 3);
            printf("�");
            setPosition(7, 5);
            printf("4 - MODIFICAR CLIENTE");
            opcao = 4;
        }
        else if (tecla == 53)
        {
            setPosition(2, 11);
            printf("GERENCIAR CLIENTES");
            setPosition(4, 3);
            printf("  1 - Cadastrar Cliente");
            setPosition(5, 3);
            printf("  2 - Remover Cliente");
            setPosition(6, 3);
            printf("  3 - Listar Clientes");
            setPosition(7, 3);
            printf("  4 - Modificar Cliente");
            setPosition(8, 3);
            printf("  5 - Voltar");
            setPosition(8, 3);
            printf("�");
            setPosition(8, 5);
            printf("5 - VOLTAR");
            opcao = 5;
        }

        setlocale(LC_ALL, "C");
    }

    switch(opcao)
    {
    case 1:
        cadastrarClientes();
        break;
    case 2:
        removerClientes();
        break;
    case 3:
        listarClientes();
        break;
    case 4:
        modificarCliente();
        break;
    case 5:
        menuPrincipal();
        break;

    }
}
void cadastrarClientes()
{
    cls();
    int i;

    char ch = '\0';
    int ctecla = 0;

    char faturamentoStr[11];
    char faturamentoVirgula[3];
    char despesaStr[11];
    char despesaVirgula[3];


    cls();

    createBox(1, 2, 3, 55);
    setlocale(LC_ALL, "Portuguese");
    setPosition(2, 18);
    printf("CADASTRAR CLIENTE");
    setlocale(LC_ALL, "C");
    createBox(3, 2, 20, 55);
    setPosition(3, 2);
    printf("%c", 195);
    setPosition(3, 55);
    printf("%c", 180);
    setlocale(LC_ALL, "Portuguese");
    setPosition(4, 4);
    printf("Nome:");
    setlocale(LC_ALL, "C");
    createBox(5, 3, 7, 54);
    setlocale(LC_ALL, "Portuguese");
    setPosition(8, 4);
    printf("Email:");
    setlocale(LC_ALL, "C");
    createBox(9, 3, 11, 54);
    setlocale(LC_ALL, "Portuguese");
    setPosition(12, 4);
    printf("Telefone:");
    setlocale(LC_ALL, "C");
    createBox(13, 3, 15, 19);
    setlocale(LC_ALL, "Portuguese");
    setPosition(12, 32);
    printf("Tipo de Pessoa:");
    setlocale(LC_ALL, "C");
    createBox(13, 31, 15, 42);
    setlocale(LC_ALL, "Portuguese");
    setPosition(16, 4);
    printf("Ativo:");
    setlocale(LC_ALL, "C");
    createBox(17, 3, 19, 14);
    setPosition(18, 15);
    printf(",");
    createBox(17, 16, 19, 19);
    setlocale(LC_ALL, "Portuguese");
    setPosition(16, 32);
    printf("Passivo:");
    setlocale(LC_ALL, "C");
    createBox(17, 31, 19, 42);
    setPosition(18, 43);
    printf(",");
    createBox(17, 44, 19, 47);
    setlocale(LC_ALL, "Portuguese");

    //INPUT DO NOME
    do
    {

        limparPergunta(1, 56);

        memset(cliente.nome, '\0', sizeof(cliente.nome));

        for(i = 4; i < 54; i++)
        {
            setPosition(6, i);
            printf(" ");
        }

        setlocale(LC_ALL, "Portuguese");
        ch = '\0';
        ctecla = 0;
        setPosition(6, 4);
        while(ctecla<50)
        {
            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    funcionario.nome[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarClientes();
                break;
            case '_':
                //VAI FAZER NADA
                break;
            default:
                cliente.nome[ctecla] = ch;
                putch(ch);
                ctecla++;
                break;
            }
        }
        setlocale(LC_ALL, "C");

    }
    while(pergunta(" Confirmar nome?", 1, 56) == 0);
    limparPergunta(1, 56);
    for(i = 0; i < strlen(cliente.nome); i++)
    {
        if(cliente.nome[i] == ' ')
        {
            cliente.nome[i] = '_';
        }
    }
    //INPUT DO EMAIL
    do
    {

        limparPergunta(1, 56);

        memset(cliente.email, '\0', sizeof(cliente.email));

        for(i = 4; i < 54; i++)
        {
            setPosition(10, i);
            printf(" ");
        }

        setlocale(LC_ALL, "Portuguese");
        ch = '\0';
        ctecla = 0;
        setPosition(10, 4);
        while(ctecla<50)
        {
            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    cliente.email[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarClientes();
                break;
            case '_':
                cliente.email[ctecla] = ch;
                putch(ch);
                ctecla++;
                break;
            default:
                cliente.email[ctecla] = ch;
                putch(ch);
                ctecla++;
                break;
            }
        }
        setlocale(LC_ALL, "C");

    }
    while(pergunta(" Confirmar email?", 1, 56) == 0);
    limparPergunta(1, 56);
    for(i = 0; i < strlen(cliente.email); i++)
    {
        if(cliente.email[i] == '_')
        {
            cliente.email[i] = '_';
        }
    }

    //INPUT DO TELEFONE
    do
    {

        limparPergunta(1, 56);

        memset(cliente.telefone, '\0', sizeof(cliente.telefone));

        for(i = 4; i < 19; i++)
        {
            setPosition(14, i);
            printf(" ");
        }

        setlocale(LC_ALL, "Portuguese");
        ch = '\0';
        ctecla = 0;
        setPosition(14, 4);
        while(ctecla<15)
        {
            ch = getch();


            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    cliente.telefone[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarClientes();
                break;
            default:
                if((ch == '0') || (ch =='1') || (ch =='2') || (ch =='3') || (ch =='4') || (ch =='5') || (ch =='6') || (ch =='7') || (ch =='8') || (ch =='9') || (ch =='(') || (ch ==')') || (ch =='-') || (ch =='+'))
                {
                    cliente.telefone[ctecla] = ch;
                    putch(ch);
                    ctecla++;
                }
                break;
            }
        }

        setlocale(LC_ALL, "C");

    }
    while(pergunta("Confirmar telefone?", 1, 56) == 0);
    limparPergunta(1, 56);
    for(i = 0; i < strlen(cliente.telefone); i++)
    {
        if(cliente.telefone[i] == ' ')
        {
            cliente.telefone[i] = '_';
        }
    }
    //INPUT DO TIPO DE PESSOA
    do
    {

        limparPergunta(1, 56);

        setPosition(14, 32);
        printf(" ");
        setPosition(14, 33);
        printf(" ");
        setPosition(14, 34);
        printf(" ");
        setPosition(14, 35);
        printf(" ");
        setPosition(14, 36);
        printf(" ");
        setPosition(14, 37);
        printf(" ");
        setPosition(14, 38);
        printf(" ");
        setPosition(14, 39);
        printf(" ");

        createBox(1, 56, 3, 75);
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 59);
        printf("TIPO DE PESSOA");
        setlocale(LC_ALL, "C");
        createBox(3, 56, 6, 75);
        setPosition(3, 56);
        printf("%c", 195);
        setPosition(3, 75);
        printf("%c", 180);

        setlocale(LC_ALL, "Portuguese");
        setPosition(4, 57);
        printf("  1 - F�sica");
        setPosition(5, 57);
        printf("  2 - Jur�dica");
        setPosition(4, 57);
        printf("�");
        setPosition(4, 59);
        printf("1 - F�SICA");
        setlocale(LC_ALL, "C");

        int tecla;
        int opcao = 1;

        while(1)
        {
            setbuf(stdin, NULL);
            tecla = getch();

            if (tecla == ESC)
            {
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarClientes();
                break;
            }

            if (tecla==13)   // Enter
            {
                break;
            }

            if(tecla == 80 || tecla == 77)   //Seta para baixo ou seta direita
            {
                switch(opcao)
                {
                case 1:
                    tecla = 50;
                    break;

                case 2:
                    tecla = 51;
                    break;

                }
            }

            if(tecla == 72 || tecla == 75)   //Seta seta para cima ou esquerda
            {
                switch(opcao)
                {
                case 1:
                    tecla = 53;
                    break;

                case 2:
                    tecla = 49;
                    break;

                }
            }

            setlocale(LC_ALL, "Portuguese");
            if(tecla == 49)
            {
                setPosition(4, 57);
                printf("  1 - F�sica");
                setPosition(5, 57);
                printf("  2 - Jur�dica");
                setPosition(4, 57);
                printf("�");
                setPosition(4, 59);
                printf("1 - F�SICA");
                opcao = 1;
            }
            else if (tecla == 50)
            {
                setPosition(4, 57);
                printf("  1 - F�sica");
                setPosition(5, 57);
                printf("  2 - Jur�dica");
                setPosition(5, 57);
                printf("�");
                setPosition(5, 59);
                printf("2 - JUR�DICA");
                opcao = 2;
            }
            setlocale(LC_ALL, "C");
        }

        memset(cliente.tipo_pessoa, '\0', sizeof(cliente.tipo_pessoa));

        setlocale(LC_ALL, "Portuguese");
        switch(opcao)
        {
        case 1:
            setPosition(14, 32);
            printf("F�sica");
            strcpy(cliente.tipo_pessoa, "F�sica");
            break;
        case 2:
            setPosition(14, 32);
            printf("Jur�dica");
            strcpy(cliente.tipo_pessoa, "Jur�dica");
            break;

        }
        setlocale(LC_ALL, "C");

        limparPergunta(1, 56);
        limparPergunta(7, 56);

    }
    while(pergunta("Confirmar pessoa?", 1, 56) == 0);
    limparPergunta(1, 56);
    //INPUT DO ATIVO
    do
    {

        limparPergunta(1,56);
        setPosition(18,4);
        printf(" ");
        setPosition(18,5);
        printf(" ");
        setPosition(18,6);
        printf(" ");
        setPosition(18,7);
        printf(" ");
        setPosition(18,8);
        printf(" ");
        setPosition(18,9);
        printf(" ");
        setPosition(18,10);
        printf(" ");
        setPosition(18,11);
        printf(" ");
        setPosition(18,12);
        printf(" ");
        setPosition(18,13);
        printf(" ");
        setPosition(18,17);
        printf(" ");
        setPosition(18,18);
        printf(" ");


        memset(faturamentoStr, '\0', sizeof(faturamentoStr));
        memset(faturamentoVirgula, '\0', sizeof(faturamentoVirgula));

        ch = '\0';
        ctecla = 0;
        setPosition(18, 4);
        while(ctecla<10)
        {
            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    faturamentoStr[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarClientes();
                break;
            default:
                if((ch == '0') || (ch =='1') || (ch =='2') || (ch =='3') || (ch =='4') || (ch =='5') || (ch =='6') || (ch =='7') || (ch =='8') || (ch =='9'))
                {
                    faturamentoStr[ctecla] = ch;
                    putch(ch);
                    ctecla++;
                }
                break;
            }
        }

        strcat(faturamentoStr, ".");

        ch = '\0';
        ctecla = 0;
        setPosition(18, 17);
        while(ctecla<2)
        {

            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    faturamentoVirgula[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarClientes();
                break;
            default:
                if((ch == '0') || (ch =='1') || (ch =='2') || (ch =='3') || (ch =='4') || (ch =='5') || (ch =='6') || (ch =='7') || (ch =='8') || (ch =='9'))
                {
                    faturamentoVirgula[ctecla] = ch;
                    putch(ch);
                    ctecla++;
                }
                break;
            }
        }

    }
    while (pergunta("Confirmar ativo?", 1, 56) == 0);
    limparPergunta(1, 56);
    if((strcmp(faturamentoStr, "") == 0) && (strcmp(faturamentoVirgula, "") == 0))   //Caso o valor do ativo tiver vazio ent�o retornar� como zero
    {
        strcpy(faturamentoStr, "0");
        strcpy(faturamentoVirgula, "00");
    }
    strcat(faturamentoStr, faturamentoVirgula);
    cliente.faturamento = strtod(faturamentoStr, NULL);


    //INPUT DO PASSIVO
    do
    {

        limparPergunta(1,56);
        setPosition(18,32);
        printf(" ");
        setPosition(18,33);
        printf(" ");
        setPosition(18,34);
        printf(" ");
        setPosition(18,35);
        printf(" ");
        setPosition(18,36);
        printf(" ");
        setPosition(18,37);
        printf(" ");
        setPosition(18,38);
        printf(" ");
        setPosition(18,39);
        printf(" ");
        setPosition(18,40);
        printf(" ");
        setPosition(18,41);
        printf(" ");
        setPosition(18,45);
        printf(" ");
        setPosition(18,46);
        printf(" ");

        setPosition(18,32);
        printf(" ");

        memset(despesaStr, '\0', sizeof(despesaStr));
        memset(despesaVirgula, '\0', sizeof(despesaVirgula));

        ch = '\0';
        ctecla = 0;
        setPosition(18, 32);
        while(ctecla<10)
        {
            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    despesaStr[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarClientes();
                break;
            default:
                if((ch == '0') || (ch =='1') || (ch =='2') || (ch =='3') || (ch =='4') || (ch =='5') || (ch =='6') || (ch =='7') || (ch =='8') || (ch =='9'))
                {
                    despesaStr[ctecla] = ch;
                    putch(ch);
                    ctecla++;
                }
                break;
            }
        }

        strcat(despesaStr, ".");

        ch = '\0';
        ctecla = 0;
        setPosition(18, 45);
        while(ctecla<2)
        {

            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    despesaVirgula[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarClientes();
                break;
            default:
                if((ch == '0') || (ch =='1') || (ch =='2') || (ch =='3') || (ch =='4') || (ch =='5') || (ch =='6') || (ch =='7') || (ch =='8') || (ch =='9'))
                {
                    despesaVirgula[ctecla] = ch;
                    putch(ch);
                    ctecla++;
                }
                break;
            }
        }

    }
    while (pergunta("Confirmar passivo?", 1, 56) == 0);
    limparPergunta(1, 56);
    if((strcmp(despesaStr, "") == 0) && (strcmp(despesaVirgula, "") == 0))   //Caso um dos valores de despesa tiver vazio ent�o retornar� como zero
    {
        strcpy(despesaStr, "0");
        strcpy(despesaVirgula, "00");
    }
    strcat(despesaStr, despesaVirgula);
    cliente.despesas = strtod(despesaStr, NULL);

    double faturamentoTotal;
    double saldoTotal;

    if(pergunta("Confirmar cadastro?", 1, 56) == 1)
    {
        cls();
        setlocale(LC_ALL, "Portuguese");
        //RECUPERANDO E IMPLEMENTANDO REGISTRO
        file = fopen("./Cliente/reg.txt", "r");
        fscanf(file, "%lu", &cliente.id);
        fclose(file);
        file = fopen("./Cliente/reg.txt", "w");
        fprintf(file, "%lu", ++cliente.id);
        fclose(file);

        //CALCULANDO SALDO
        cliente.saldo = cliente.faturamento - cliente.despesas;

        //RECUPERANDO E SOMANDO O FATURAMENTO TOTAL
        file = fopen("./Cliente/fat.txt", "r");
        fscanf(file, "%lf", &faturamentoTotal);
        fclose(file);
        faturamentoTotal += cliente.faturamento;
        file = fopen("./Cliente/fat.txt", "w");
        fprintf(file, "%.2lf", faturamentoTotal);
        fclose(file);

        //RECUPERANDO E SOMANDO O SALDO TOTAL
        file = fopen("./Cliente/sald.txt", "r");
        fscanf(file, "%lf", &saldoTotal);
        fclose(file);
        saldoTotal += cliente.saldo;
        file = fopen("./Cliente/sald.txt", "w");
        fprintf(file, "%.2lf", saldoTotal);
        fclose(file);

        //CADASTRANDO CLIENTE
        file = fopen("./Cliente/cli.txt", "a");
        fprintf(file, "%lu %s %s %s %s %.2f %.2f %.2f \n", cliente.id, cliente.nome, cliente.email, cliente.telefone, cliente.tipo_pessoa, cliente.faturamento, cliente.despesas, cliente.saldo);
        fclose(file);

        //MENSAGEM QUE FUNCION�RIO FOI CADASTRADO
        memset(mensagem, '\0', sizeof(mensagem));
        strcpy(mensagem, "CADASTROU O(A) CLIENTE \"");
        for(i = 0; i < strlen(cliente.nome); i++)
        {
            if(cliente.nome[i] == '_')
            {
                cliente.nome[i] = ' ';
            }
        }
        strcat(mensagem, cliente.nome);
        strcat(mensagem, "\"");
        registrarNoLog(mensagem);
        setPosition(2, 3);
        printf("CADASTRAMENTO DE CLIENTE FEITO SUCESSO!");
        setlocale(LC_ALL, "C");
        getch();
        gerenciarClientes();
    }
    else
    {
        cls();
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 3);
        printf("CADASTRAMENTO DE CLIENTE CANCELADO COM SUCESSO!");
        setlocale(LC_ALL, "C");
        getch();
        gerenciarClientes();
    }


    getch();
}
void removerClientes()
{
    char leitor[200];
    char analisador[200];
    memset(leitor, '\0', sizeof(leitor));
    memset(analisador, '\0', sizeof(analisador));
    strcat(analisador, dados.usuario);
    strcat(analisador, " ");
    strcat(analisador, dados.senha);
    if(strcmp(ADMIN, analisador) == 0)
    {
        memset(analisador, '\0', sizeof(analisador));
        FILE *fileTemp;

        unsigned int i;
        unsigned int beforePositionSpace;
        unsigned int afterPositionSpace;
        char faturamentoStr[20];
        char despesaStr[20];
        double faturamentoTotal;
        double saldoTotal;

        memset(faturamentoStr, '\0', sizeof(faturamentoStr));
        memset(despesaStr, '\0', sizeof(despesaStr));
        memset(cliente.nome, '\0', sizeof(cliente.nome));
        memset(cliente.email, '\0', sizeof(cliente.email));
        memset(cliente.telefone, '\0', sizeof(cliente.telefone));
        memset(cliente.tipo_pessoa, '\0', sizeof(cliente.tipo_pessoa));

        cls();

        createBox(1, 2, 3, 55);
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 20);
        printf("REMOVER CLIENTE");
        setlocale(LC_ALL, "C");
        createBox(3, 2, 24, 55);
        setPosition(3, 2);
        printf("%c", 195);
        setPosition(3, 55);
        printf("%c", 180);

        setlocale(LC_ALL, "Portuguese");
        setPosition(4, 4);
        printf("Pesquisar ID:");
        setlocale(LC_ALL, "C");
        createBox(5, 3, 7, 24);
        setlocale(LC_ALL, "Portuguese");
        setPosition(8, 4);
        printf("Nome:");
        setlocale(LC_ALL, "C");
        createBox(9, 3, 11, 54);
        setlocale(LC_ALL, "Portuguese");
        setPosition(12, 4);
        printf("Email:");
        setlocale(LC_ALL, "C");
        createBox(13, 3, 15, 54);
        setlocale(LC_ALL, "Portuguese");
        setPosition(16, 4);
        printf("Telefone:");
        setlocale(LC_ALL, "C");
        createBox(17, 3, 19, 19);
        setlocale(LC_ALL, "Portuguese");
        setPosition(16, 32);
        printf("Tipo de Pessoa:");
        setlocale(LC_ALL, "C");
        createBox(17, 31, 19, 42);
        setlocale(LC_ALL, "Portuguese");
        setPosition(20, 4);
        printf("Ativo:");
        setlocale(LC_ALL, "C");
        createBox(21, 3, 23, 17);
        setlocale(LC_ALL, "Portuguese");
        setPosition(20, 32);
        printf("Passivo:");
        setlocale(LC_ALL, "C");
        createBox(21, 31, 23, 45);

        char id[21];
        memset(id, '\0', sizeof(id));

        char ch = '\0';
        int ctecla = 0;
        ch = '\0';
        ctecla = 0;
        setPosition(6, 4);
        while(ctecla<20)
        {
            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    id[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarClientes();
                break;
            default:
                if((ch == '0') || (ch =='1') || (ch =='2') || (ch =='3') || (ch =='4') || (ch =='5') || (ch =='6') || (ch =='7') || (ch =='8') || (ch =='9'))
                {
                    id[ctecla] = ch;
                    putch(ch);
                    ctecla++;
                }
                break;
            }
        }

        strcat(id, " ");

        file = fopen("./Cliente/cli.txt", "r");
        while(fgets(leitor, 200, file) != NULL)
        {

            for(i = 0; i < strlen(id); i++)
            {
                analisador[i] = leitor[i];
            }

            if(strcmp(analisador, id) == 0)
            {

                for(i = 0; i < strlen(leitor); i++)
                {
                    if(leitor[i] == ' ')
                    {
                        beforePositionSpace = i;
                        break;
                    }
                }

                for(i = ++beforePositionSpace; i < strlen(leitor); i++)
                {
                    if(leitor[i] == ' ')
                    {
                        afterPositionSpace = i;
                        break;
                    }
                }

                for(i = beforePositionSpace; i < afterPositionSpace; i++)
                {
                    if(leitor[i] != '_')
                    {
                        cliente.nome[i - beforePositionSpace] = leitor[i];
                    }
                    else
                    {
                        cliente.nome[i - beforePositionSpace] = ' ';
                    }
                }

                beforePositionSpace = afterPositionSpace;

                for(i = ++beforePositionSpace; i < strlen(leitor); i++)
                {
                    if(leitor[i] == ' ')
                    {
                        afterPositionSpace = i;
                        break;
                    }
                }

                for(i = beforePositionSpace; i < afterPositionSpace; i++)
                {
                    cliente.email[i - beforePositionSpace] = leitor[i];
                }

                beforePositionSpace = afterPositionSpace;

                for(i = ++beforePositionSpace; i < strlen(leitor); i++)
                {
                    if(leitor[i] == ' ')
                    {
                        afterPositionSpace = i;
                        break;
                    }
                }

                for(i = beforePositionSpace; i < afterPositionSpace; i++)
                {
                    cliente.telefone[i - beforePositionSpace] = leitor[i];
                }

                beforePositionSpace = afterPositionSpace;

                for(i = ++beforePositionSpace; i < strlen(leitor); i++)
                {
                    if(leitor[i] == ' ')
                    {
                        afterPositionSpace = i;
                        break;
                    }
                }

                for(i = beforePositionSpace; i < afterPositionSpace; i++)
                {
                    cliente.tipo_pessoa[i - beforePositionSpace] = leitor[i];
                }

                beforePositionSpace = afterPositionSpace;

                for(i = ++beforePositionSpace; i < strlen(leitor); i++)
                {
                    if(leitor[i] == ' ')
                    {
                        afterPositionSpace = i;
                        break;
                    }
                }

                for(i = beforePositionSpace; i < afterPositionSpace; i++)
                {
                    faturamentoStr[i - beforePositionSpace] = leitor[i];
                }

                beforePositionSpace = afterPositionSpace;

                for(i = ++beforePositionSpace; i < strlen(leitor); i++)
                {
                    if(leitor[i] == ' ')
                    {
                        afterPositionSpace = i;
                        break;
                    }
                }

                for(i = beforePositionSpace; i < afterPositionSpace; i++)
                {
                    despesaStr[i - beforePositionSpace] = leitor[i];
                }

                break;
            }
            else
            {
                memset(analisador, '\0', sizeof(analisador));
                memset(leitor, '\0', sizeof(leitor));
                continue;
            }

        }
        fclose(file);

        if(strcmp(analisador, id) == 0)
        {

            setlocale(LC_ALL, "Portuguese");
            setPosition(10, 4);
            printf("%s", cliente.nome);
            setPosition(14, 4);
            printf("%s", cliente.email);
            setPosition(18, 4);
            printf("%s", cliente.telefone);
            setPosition(18, 32);
            printf("%s", cliente.tipo_pessoa);
            setPosition(22, 4);
            printf("%s", faturamentoStr);
            setPosition(22, 32);
            printf("%s", despesaStr);
            setlocale(LC_ALL, "C");


            memset(analisador, '\0', sizeof(analisador));
            memset(leitor, '\0', sizeof(leitor));
            if(pergunta("Confirmar remo��o?", 1, 56) == 1)
            {
                file = fopen("./Cliente/cli.txt", "r");
                fileTemp = fopen("./Cliente/cliTemp.txt", "w");

                while(fgets(leitor, 200, file) != NULL)
                {
                    for(i = 0; i < strlen(id); i++)
                    {
                        analisador[i] = leitor[i];
                    }

                    if(strcmp(analisador, id) != 0)
                    {
                        fprintf(fileTemp, "%s", leitor);
                    }

                    memset(analisador, '\0', sizeof(analisador));
                    memset(leitor, '\0', sizeof(leitor));

                }
                fclose(file);
                fclose(fileTemp);

                remove("./Cliente/cli.txt");
                rename("./Cliente/cliTemp.txt", "./Cliente/cli.txt");

                file = fopen("./Cliente/sal.txt", "r");

                cliente.faturamento = strtod(faturamentoStr, NULL);
                cliente.despesas = strtod(despesaStr, NULL);

                //RECUPERANDO E SUBTRAINDO O FATURAMENTO TOTAL COM O FATURAMENTO DO CLIENTE REMOVIDO
                file = fopen("./Cliente/fat.txt", "r");
                fscanf(file, "%lf", &faturamentoTotal);
                fclose(file);
                faturamentoTotal -= cliente.faturamento;
                file = fopen("./Cliente/fat.txt", "w");
                fprintf(file, "%.2lf", faturamentoTotal);
                fclose(file);

                //RECUPERANDO E SUBTRAINDO O SALDO TOTAL COM O SALDO DO CLIENTE REMOVIDO
                file = fopen("./Cliente/sald.txt", "r");
                fscanf(file, "%lf", &saldoTotal);
                fclose(file);
                saldoTotal -= (cliente.faturamento - cliente.despesas);
                file = fopen("./Cliente/sald.txt", "w");
                fprintf(file, "%.2lf", saldoTotal);
                fclose(file);


                memset(mensagem, '\0', sizeof(mensagem));
                strcpy(mensagem, "REMOVEU O(A) CLIENTE \"");
                strcat(mensagem, cliente.nome);
                strcat(mensagem, "\"");
                registrarNoLog(mensagem);

                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("REMO��O DE CLIENTE REALIZADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarClientes();

            }
            else
            {
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("REMO��O DE CLIENTE CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarClientes();
            }
        }
        else
        {
            setlocale(LC_ALL, "Portuguese");
            setPosition(26, 3);
            printf("ERRO: CLIENTE N�O ENCONTRADO!");
            setlocale(LC_ALL, "C");
            if(pergunta("Continuar opera��o?", 1, 56) == 1)
            {
                removerClientes();
            }
            else
            {
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarClientes();
            }
        }
    }
    else
    {
        cls();
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 3);
        printf("ERRO: ACESSO NEGADO, VOC� N�O TEM PERMISS�O PARA ACESSAR ESTE M�DULO!");
        setlocale(LC_ALL, "C");
        getch();
        gerenciarClientes();
    }
}
void listarClientes()
{
    cls();
    unsigned long int quantClientes = 0;
    unsigned long int linha = 4;
    unsigned int i;
    unsigned int beforePositionSpace;
    unsigned int afterPositionSpace;
    char faturamentoStr[22];
    char despesaStr[22];
    char saldoStr[22];

    char leitor[200];
    char analisador[200];
    memset(leitor, '\0', sizeof(leitor));
    memset(analisador, '\0', sizeof(analisador));
    strcat(analisador, dados.usuario);
    strcat(analisador, " ");
    strcat(analisador, dados.senha);
    if(strcmp(ADMIN, analisador) == 0)
    {
        memset(analisador, '\0', sizeof(analisador));
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 3);
        printf("---------- LISTA DE CLIENTES ----------");
        setlocale(LC_ALL, "C");

        setlocale(LC_ALL, "Portuguese");
        file = fopen("./Cliente/cli.txt", "r");
        while(fgets(leitor, 200, file) != NULL)
        {

            memset(cliente.nome, '\0', sizeof(cliente.nome));
            memset(cliente.email, '\0', sizeof(cliente.email));
            memset(cliente.telefone, '\0', sizeof(cliente.telefone));
            memset(cliente.tipo_pessoa, '\0', sizeof(cliente.tipo_pessoa));
            memset(faturamentoStr, '\0', sizeof(faturamentoStr));
            memset(despesaStr, '\0', sizeof(despesaStr));
            memset(saldoStr, '\0', sizeof(saldoStr));

            for(i = 0; i < strlen(leitor); i++)
            {
                analisador[i] = leitor[i];
                if(leitor[i] == ' ')
                {
                    beforePositionSpace = i;
                    break;
                }
            }

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                if(leitor[i] != '_')
                {
                    cliente.nome[i - beforePositionSpace] = leitor[i];
                }
                else
                {
                    cliente.nome[i - beforePositionSpace] = ' ';
                }
            }



            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    cliente.email[i] = leitor[i];
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                cliente.email[i - beforePositionSpace] = leitor[i];
            }


            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                cliente.telefone[i - beforePositionSpace] = leitor[i];
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                cliente.tipo_pessoa[i - beforePositionSpace] = leitor[i];
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                faturamentoStr[i - beforePositionSpace] = leitor[i];
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                despesaStr[i - beforePositionSpace] = leitor[i];
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == '\n')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                saldoStr[i - beforePositionSpace] = leitor[i];
            }

            setPosition(linha,4);
            printf("ID....................: %s", analisador);
            linha++;
            setPosition(linha,4);
            printf("NOME..................: %s", cliente.nome);
            linha++;
            setPosition(linha,4);
            printf("EMAIL.................: %s", cliente.email);
            linha++;
            setPosition(linha,4);
            printf("TELEFONE..............: %s", cliente.telefone);
            linha++;
            setPosition(linha,4);
            printf("TIPO DE PESSOA........: %s", cliente.tipo_pessoa);
            linha++;
            setPosition(linha,4);
            printf("ATIVO.................: %s", faturamentoStr);
            linha++;
            setPosition(linha,4);
            printf("PASSIVO...............: %s", despesaStr);
            linha++;
            setPosition(linha,4);
            printf("SALDO.................: %s", saldoStr);
            linha++;
            linha++;

            quantClientes++;

            memset(analisador, '\0', sizeof(analisador));
            memset(leitor, '\0', sizeof(leitor));
        }
        fclose(file);
    }
    else
    {
        memset(analisador, '\0', sizeof(analisador));
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 3);
        printf("---------- LISTA DE CLIENTES ----------");
        setlocale(LC_ALL, "C");

        setlocale(LC_ALL, "Portuguese");
        file = fopen("./Cliente/cli.txt", "r");
        while(fgets(leitor, 200, file) != NULL)
        {

            memset(cliente.nome, '\0', sizeof(funcionario.nome));
            memset(cliente.email, '\0', sizeof(funcionario.funcao));
            memset(cliente.telefone, '\0', sizeof(cliente.telefone));
            memset(cliente.tipo_pessoa, '\0', sizeof(cliente.tipo_pessoa));


            for(i = 0; i < strlen(leitor); i++)
            {
                analisador[i] = leitor[i];
                if(leitor[i] == ' ')
                {
                    beforePositionSpace = i;
                    break;
                }
            }

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                if(leitor[i] != '_')
                {
                    cliente.nome[i - beforePositionSpace] = leitor[i];
                }
                else
                {
                    cliente.nome[i - beforePositionSpace] = ' ';
                }
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    cliente.email[i] = leitor[i];
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                cliente.email[i - beforePositionSpace] = leitor[i];
            }


            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                cliente.telefone[i - beforePositionSpace] = leitor[i];
            }

            beforePositionSpace = afterPositionSpace;

            for(i = ++beforePositionSpace; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    afterPositionSpace = i;
                    break;
                }
            }

            for(i = beforePositionSpace; i < afterPositionSpace; i++)
            {
                cliente.tipo_pessoa[i - beforePositionSpace] = leitor[i];
            }



            setPosition(linha,4);
            printf("ID....................: %s", analisador);
            linha++;
            setPosition(linha,4);
            printf("NOME..................: %s", cliente.nome);
            linha++;
            setPosition(linha,4);
            printf("EMAIL.................: %s", cliente.email);
            linha++;
            setPosition(linha,4);
            printf("TELEFONE..............: %s", cliente.telefone);
            linha++;
            setPosition(linha,4);
            printf("TIPO DE PESSOA........: %s", cliente.tipo_pessoa);
            linha++;
            linha++;

            quantClientes++;

            memset(analisador, '\0', sizeof(analisador));
            memset(leitor, '\0', sizeof(leitor));
        }
        fclose(file);
    }

    setPosition(linha, 3);
    printf("--------------------------------------\n");
    setPosition(linha+1, 3);
    printf("Quantidade de clientes: %lu", quantClientes);
    setPosition(linha+3, 3);
    printf("PRESSIONE QUALQUER TECLA PARA VOLTAR...");
    setlocale(LC_ALL, "C");
    getch();
    gerenciarClientes();

}
void modificarCliente()
{
    cls();

    char leitor[200];
    char analisador[200];
    memset(leitor, '\0', sizeof(leitor));
    memset(analisador, '\0', sizeof(analisador));
    strcat(analisador, dados.usuario);
    strcat(analisador, " ");
    strcat(analisador, dados.senha);
    if(strcmp(ADMIN, analisador) == 0)
    {
        memset(analisador, '\0', sizeof(analisador));

        unsigned int i;
        unsigned int beforePositionSpace;
        unsigned int afterPositionSpace;
        char faturamentoStr[20];
        char despesaStr[20];

        memset(faturamentoStr, '\0', sizeof(faturamentoStr));
        memset(despesaStr, '\0', sizeof(despesaStr));
        memset(cliente.nome, '\0', sizeof(cliente.nome));
        memset(cliente.email, '\0', sizeof(cliente.email));
        memset(cliente.telefone, '\0', sizeof(cliente.telefone));
        memset(cliente.tipo_pessoa, '\0', sizeof(cliente.tipo_pessoa));

        createBox(1, 2, 3, 55);
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 19);
        printf("MODIFICAR CLIENTE");
        setlocale(LC_ALL, "C");
        createBox(3, 2, 24, 55);
        setPosition(3, 2);
        printf("%c", 195);
        setPosition(3, 55);
        printf("%c", 180);

        setlocale(LC_ALL, "Portuguese");
        setPosition(4, 4);
        printf("Pesquisar ID:");
        setlocale(LC_ALL, "C");
        createBox(5, 3, 7, 24);
        setlocale(LC_ALL, "Portuguese");
        setPosition(8, 4);
        printf("Nome:");
        setlocale(LC_ALL, "C");
        createBox(9, 3, 11, 54);
        setlocale(LC_ALL, "Portuguese");
        setPosition(12, 4);
        printf("Email:");
        setlocale(LC_ALL, "C");
        createBox(13, 3, 15, 54);
        setlocale(LC_ALL, "Portuguese");
        setPosition(16, 4);
        printf("Telefone:");
        setlocale(LC_ALL, "C");
        createBox(17, 3, 19, 19);
        setlocale(LC_ALL, "Portuguese");
        setPosition(16, 32);
        printf("Tipo de Pessoa:");
        setlocale(LC_ALL, "C");
        createBox(17, 31, 19, 42);
        setlocale(LC_ALL, "Portuguese");
        setPosition(20, 4);
        printf("Ativo:");
        setlocale(LC_ALL, "C");
        createBox(21, 3, 23, 17);
        setlocale(LC_ALL, "Portuguese");
        setPosition(20, 32);
        printf("Passivo:");
        setlocale(LC_ALL, "C");
        createBox(21, 31, 23, 45);

        char id[21];
        memset(id, '\0', sizeof(id));

        char ch = '\0';
        int ctecla = 0;
        ch = '\0';
        ctecla = 0;
        setPosition(6, 4);
        while(ctecla<20)
        {
            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    id[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarClientes();
                break;
            default:
                if((ch == '0') || (ch =='1') || (ch =='2') || (ch =='3') || (ch =='4') || (ch =='5') || (ch =='6') || (ch =='7') || (ch =='8') || (ch =='9'))
                {
                    id[ctecla] = ch;
                    putch(ch);
                    ctecla++;
                }
                break;
            }
        }

        cliente.id = atoi(id);
        strcat(id, " ");

        file = fopen("./Cliente/cli.txt", "r");
        while(fgets(leitor, 200, file) != NULL)
        {

            for(i = 0; i < strlen(id); i++)
            {
                analisador[i] = leitor[i];
            }

            if(strcmp(analisador, id) == 0)
            {

                for(i = 0; i < strlen(leitor); i++)
                {
                    if(leitor[i] == ' ')
                    {
                        beforePositionSpace = i;
                        break;
                    }
                }

                for(i = ++beforePositionSpace; i < strlen(leitor); i++)
                {
                    if(leitor[i] == ' ')
                    {
                        afterPositionSpace = i;
                        break;
                    }
                }

                for(i = beforePositionSpace; i < afterPositionSpace; i++)
                {
                    if(leitor[i] != '_')
                    {
                        cliente.nome[i - beforePositionSpace] = leitor[i];
                    }
                    else
                    {
                        cliente.nome[i - beforePositionSpace] = ' ';
                    }
                }

                beforePositionSpace = afterPositionSpace;

                for(i = ++beforePositionSpace; i < strlen(leitor); i++)
                {
                    if(leitor[i] == ' ')
                    {
                        afterPositionSpace = i;
                        break;
                    }
                }

                for(i = beforePositionSpace; i < afterPositionSpace; i++)
                {
                    cliente.email[i - beforePositionSpace] = leitor[i];
                }

                beforePositionSpace = afterPositionSpace;

                for(i = ++beforePositionSpace; i < strlen(leitor); i++)
                {
                    if(leitor[i] == ' ')
                    {
                        afterPositionSpace = i;
                        break;
                    }
                }

                for(i = beforePositionSpace; i < afterPositionSpace; i++)
                {
                    cliente.telefone[i - beforePositionSpace] = leitor[i];
                }

                beforePositionSpace = afterPositionSpace;

                for(i = ++beforePositionSpace; i < strlen(leitor); i++)
                {
                    if(leitor[i] == ' ')
                    {
                        afterPositionSpace = i;
                        break;
                    }
                }

                for(i = beforePositionSpace; i < afterPositionSpace; i++)
                {
                    cliente.tipo_pessoa[i - beforePositionSpace] = leitor[i];
                }

                beforePositionSpace = afterPositionSpace;

                for(i = ++beforePositionSpace; i < strlen(leitor); i++)
                {
                    if(leitor[i] == ' ')
                    {
                        afterPositionSpace = i;
                        break;
                    }
                }

                for(i = beforePositionSpace; i < afterPositionSpace; i++)
                {
                    faturamentoStr[i - beforePositionSpace] = leitor[i];
                }

                beforePositionSpace = afterPositionSpace;

                for(i = ++beforePositionSpace; i < strlen(leitor); i++)
                {
                    if(leitor[i] == ' ')
                    {
                        afterPositionSpace = i;
                        break;
                    }
                }

                for(i = beforePositionSpace; i < afterPositionSpace; i++)
                {
                    despesaStr[i - beforePositionSpace] = leitor[i];
                }

                break;
            }
            else
            {
                memset(analisador, '\0', sizeof(analisador));
                memset(leitor, '\0', sizeof(leitor));
                continue;
            }

        }
        fclose(file);

        if(strcmp(analisador, id) == 0)
        {

            setlocale(LC_ALL, "Portuguese");
            setPosition(10, 4);
            printf("%s", cliente.nome);
            setPosition(14, 4);
            printf("%s", cliente.email);
            setPosition(18, 4);
            printf("%s", cliente.telefone);
            setPosition(18, 32);
            printf("%s", cliente.tipo_pessoa);
            setPosition(22, 4);
            printf("%s", faturamentoStr);
            setPosition(22, 32);
            printf("%s", despesaStr);
            setlocale(LC_ALL, "C");
            if(pergunta("Modificar cliente?", 1, 56) == 1)
            {
                cliente.faturamento = strtod(faturamentoStr, NULL);
                cliente.despesas = strtod(despesaStr, NULL);
                while(1)
                {

                    limparPergunta(1, 56);


                    createBox(1, 56, 3, 75);
                    setlocale(LC_ALL, "Portuguese");
                    setPosition(2, 60);
                    printf("MODIFICAR...");
                    setlocale(LC_ALL, "C");
                    createBox(3, 56, 6, 75);
                    setPosition(3, 56);
                    printf("%c", 195);
                    setPosition(3, 75);
                    printf("%c", 180);

                    setlocale(LC_ALL, "Portuguese");
                    setPosition(4, 57);
                    printf("  1 - Ativo");
                    setPosition(5, 57);
                    printf("  2 - Passivo");
                    setPosition(4, 57);
                    printf("�");
                    setPosition(4, 59);
                    printf("1 - ATIVO");
                    setlocale(LC_ALL, "C");

                    int tecla;
                    int opcao = 1;

                    while(1)
                    {
                        setbuf(stdin, NULL);
                        tecla = getch();

                        if (tecla == ESC)
                        {
                            modificarCliente();
                            break;
                        }

                        if (tecla==13)   // Enter
                        {
                            break;
                        }

                        if(tecla == 80 || tecla == 77)   //Seta para baixo ou seta direita
                        {
                            switch(opcao)
                            {
                            case 1:
                                tecla = 50;
                                break;

                            case 2:
                                tecla = 51;
                                break;

                            }
                        }

                        if(tecla == 72 || tecla == 75)   //Seta seta para cima ou esquerda
                        {
                            switch(opcao)
                            {
                            case 1:
                                tecla = 53;
                                break;

                            case 2:
                                tecla = 49;
                                break;

                            }
                        }

                        setlocale(LC_ALL, "Portuguese");
                        if(tecla == 49)
                        {
                            setPosition(4, 57);
                            printf("  1 - Ativo");
                            setPosition(5, 57);
                            printf("  2 - Passivo");
                            setPosition(4, 57);
                            printf("�");
                            setPosition(4, 59);
                            printf("1 - ATIVO");
                            opcao = 1;
                        }
                        else if (tecla == 50)
                        {
                            setPosition(4, 57);
                            printf("  1 - Ativo");
                            setPosition(5, 57);
                            printf("  2 - Passivo");
                            setPosition(5, 57);
                            printf("�");
                            setPosition(5, 59);
                            printf("2 - PASSIVO");
                            opcao = 2;
                        }
                        setlocale(LC_ALL, "C");
                    }

                    switch(opcao)
                    {
                    case 1:
                        modificarClienteAtivo();
                        break;
                    case 2:
                        modificarClientePassivo();
                        break;

                    }

                }

            }
            else
            {
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("MODIFICA��O DE CLIENTE CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarClientes();
            }
        }
        else
        {
            setlocale(LC_ALL, "Portuguese");
            setPosition(26, 3);
            printf("ERRO: CLIENTE N�O ENCONTRADO!");
            setlocale(LC_ALL, "C");
            if(pergunta("Continuar opera��o?", 1, 56) == 1)
            {
                modificarCliente();
            }
            else
            {
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarClientes();
            }
        }
    }
    else
    {
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 3);
        printf("ERRO: ACESSO NEGADO, VOC� N�O TEM PERMISS�O PARA ACESSAR ESTE M�DULO!");
        setlocale(LC_ALL, "C");
        getch();
        gerenciarClientes();
    }
}
void modificarClienteAtivo()
{
    cls();

    char leitor[200];
    char analisador[200];
    memset(leitor, '\0', sizeof(leitor));
    memset(analisador, '\0', sizeof(analisador));
    strcat(analisador, dados.usuario);
    strcat(analisador, " ");
    strcat(analisador, dados.senha);
    if(strcmp(ADMIN, analisador) == 0)
    {
        memset(analisador, '\0', sizeof(analisador));
        FILE *fileTemp;

        createBox(1, 2, 3, 55);
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 15);
        printf("MODIFICAR ATIVO DO CLIENTE");
        setlocale(LC_ALL, "C");
        createBox(3, 2, 12, 55);
        setPosition(3, 2);
        printf("%c", 195);
        setPosition(3, 55);
        printf("%c", 180);

        setlocale(LC_ALL, "Portuguese");
        setPosition(4, 4);
        printf("Cliente:");
        setPosition(6, 4);
        printf("%s", cliente.nome);
        setlocale(LC_ALL, "C");
        createBox(5, 3, 7, 54);

        setlocale(LC_ALL, "Portuguese");
        setPosition(8, 4);
        printf("Ativo atual:");
        setPosition(10, 4);
        printf("%.2lf", cliente.faturamento);
        setlocale(LC_ALL, "C");
        createBox(9, 3, 11, 19);

        setlocale(LC_ALL, "Portuguese");
        setPosition(8, 32);
        printf("Novo ativo:");
        setlocale(LC_ALL, "C");
        createBox(9, 31, 11, 42);
        setPosition(10, 43);
        printf(",");
        createBox(9, 44, 11, 47);

        char id[21];
        memset(id, '\0', sizeof(id));
        itoa(cliente.id, id, 10);
        strcat(id, " ");

        unsigned int i;

        char ch = '\0';
        int ctecla = 0;

        char faturamentoStr[11];
        char faturamentoVirgula[3];
        double faturamentoTotal;
        double saldoTotal;

        do
        {

            limparPergunta(1,56);
            setPosition(10,32);
            printf(" ");
            setPosition(10,33);
            printf(" ");
            setPosition(10,34);
            printf(" ");
            setPosition(10,35);
            printf(" ");
            setPosition(10,36);
            printf(" ");
            setPosition(10,37);
            printf(" ");
            setPosition(10,38);
            printf(" ");
            setPosition(10,39);
            printf(" ");
            setPosition(10,40);
            printf(" ");
            setPosition(10,41);
            printf(" ");
            setPosition(10,45);
            printf(" ");
            setPosition(10,46);
            printf(" ");


            memset(faturamentoStr, '\0', sizeof(faturamentoStr));
            memset(faturamentoVirgula, '\0', sizeof(faturamentoVirgula));

            ch = '\0';
            ctecla = 0;
            setPosition(10, 32);
            while(ctecla<10)
            {
                ch = getch();

                switch(ch)
                {
                case BACKSPACE:
                    if(ctecla>0)
                    {
                        fflush(stdin);
                        putch(BACKSPACE);
                        ch = '\0';
                        faturamentoStr[ctecla-1] = ch;
                        ctecla--;
                        putch(SPACE);
                        putch(BACKSPACE);
                    }
                    break;
                case TAB:
                    putch(TAB);
                    ctecla = 50;
                    break;
                case ENTER:
                    putch(ENTER);
                    ctecla = 50;
                    break;
                case ESC:
                    cls();
                    setlocale(LC_ALL, "Portuguese");
                    setPosition(2, 3);
                    printf("OPERA��O CANCELADA COM SUCESSO!");
                    setlocale(LC_ALL, "C");
                    getch();
                    gerenciarClientes();
                    break;
                default:
                    if((ch == '0') || (ch =='1') || (ch =='2') || (ch =='3') || (ch =='4') || (ch =='5') || (ch =='6') || (ch =='7') || (ch =='8') || (ch =='9'))
                    {
                        faturamentoStr[ctecla] = ch;
                        putch(ch);
                        ctecla++;
                    }
                    break;
                }
            }

            strcat(faturamentoStr, ".");

            ch = '\0';
            ctecla = 0;
            setPosition(10, 45);
            while(ctecla<2)
            {

                ch = getch();

                switch(ch)
                {
                case BACKSPACE:
                    if(ctecla>0)
                    {
                        fflush(stdin);
                        putch(BACKSPACE);
                        ch = '\0';
                        faturamentoVirgula[ctecla-1] = ch;
                        ctecla--;
                        putch(SPACE);
                        putch(BACKSPACE);
                    }
                    break;
                case TAB:
                    putch(TAB);
                    ctecla = 50;
                    break;
                case ENTER:
                    putch(ENTER);
                    ctecla = 50;
                    break;
                case ESC:
                    cls();
                    setlocale(LC_ALL, "Portuguese");
                    setPosition(2, 3);
                    printf("OPERA��O CANCELADA COM SUCESSO!");
                    setlocale(LC_ALL, "C");
                    getch();
                    gerenciarClientes();
                    break;
                default:
                    if((ch == '0') || (ch =='1') || (ch =='2') || (ch =='3') || (ch =='4') || (ch =='5') || (ch =='6') || (ch =='7') || (ch =='8') || (ch =='9'))
                    {
                        faturamentoVirgula[ctecla] = ch;
                        putch(ch);
                        ctecla++;
                    }
                    break;
                }
            }

        }
        while (pergunta("Confirmar ativo?", 1, 56) == 0);
        limparPergunta(1, 56);
        if((strcmp(faturamentoStr, "") == 0) && (strcmp(faturamentoVirgula, "") == 0))   //Caso o valor do ativo tiver vazio ent�o retornar� como zero
        {
            strcpy(faturamentoStr, "0");
            strcpy(faturamentoVirgula, "00");
        }
        strcat(faturamentoStr, faturamentoVirgula);

        if(pergunta("Modificar ativo?", 1, 56) == 1)
        {
            setlocale(LC_ALL, "Portuguese");
            //RECUPERANDO VALORES DO FATURAMENTO TOTAL E DO SALDO TOTAL DO ARQUIVO TEXTO
            file = fopen("./Cliente/fat.txt", "r");
            fscanf(file, "%lf", &faturamentoTotal);
            fclose(file);
            file = fopen("./Cliente/sald.txt", "r");
            fscanf(file, "%lf", &saldoTotal);
            fclose(file);

            //SUBTRAINDO O VALOR ANTIGO DO FATURAMENTO E DO SALDO ANTERIOR DO CLIENTE
            cliente.saldo = cliente.faturamento - cliente.despesas;
            faturamentoTotal -= cliente.faturamento;
            saldoTotal -= cliente.saldo;
            cliente.faturamento = strtod(faturamentoStr, NULL);
            cliente.saldo = cliente.faturamento - cliente.despesas;
            faturamentoTotal += cliente.faturamento;
            saldoTotal += cliente.saldo;

            //SOMANDO O FATURAMENTO E SALDO TOTAL COM O NOVO VALOR
            file = fopen("./Cliente/fat.txt", "w");
            fprintf(file, "%.2lf", faturamentoTotal);
            fclose(file);
            file = fopen("./Cliente/sald.txt", "w");
            fprintf(file, "%.2lf", saldoTotal);
            fclose(file);

            //ALTERANDO VALOR DIRETAMENTE NO ARQUIVO TEXTO PRINCIPAL DOS CLIENTES
            file = fopen("./Cliente/cli.txt", "r");
            fileTemp = fopen("./Cliente/cliTemp.txt", "w");
            while(fgets(leitor, 200, file) != NULL)
            {
                for(i = 0; i < strlen(id); i++)
                {
                    analisador[i] = leitor[i];
                }

                if(strcmp(analisador, id) == 0)
                {
                    for(i = 0; i < strlen(cliente.nome); i++)
                    {
                        if(cliente.nome[i] == ' ')
                        {
                            cliente.nome[i] = '_';
                        }
                    }
                    fprintf(fileTemp, "%s%s %s %s %s %.2lf %.2lf %.2lf\n", id, cliente.nome, cliente.email, cliente.telefone, cliente.tipo_pessoa, cliente.faturamento, cliente.despesas, cliente.saldo);
                    for(i = 0; i < strlen(cliente.nome); i++)
                    {
                        if(cliente.nome[i] == '_')
                        {
                            cliente.nome[i] = ' ';
                        }
                    }
                }
                else
                {
                    fprintf(fileTemp, "%s", leitor);
                }

                memset(leitor, '\0', sizeof(leitor));
                memset(analisador, '\0', sizeof(analisador));
            }
            fclose(file);
            fclose(fileTemp);

            remove("./Cliente/cli.txt");
            rename("./Cliente/cliTemp.txt", "./Cliente/cli.txt");

            memset(mensagem, '\0', sizeof(mensagem));
            strcpy(mensagem, "ALTEROU O ATIVO DO(A) CLIENTE \"");
            strcat(mensagem, cliente.nome);
            strcat(mensagem, "\"");
            registrarNoLog(mensagem);

            setlocale(LC_ALL, "C");
            cls();
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("MODIFICA��O DE ATIVO DO CLIENTE REALIZADA COM SUCESSO!");
            setlocale(LC_ALL, "C");
            getch();
            gerenciarClientes();
        }
        else
        {
            cls();
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("MODIFICA��O DE ATIVO DO CLIENTE CANCELADA COM SUCESSO!");
            setlocale(LC_ALL, "C");
            getch();
            gerenciarClientes();
        }

    }
    else
    {
        cls();
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 3);
        printf("ERRO: ACESSO NEGADO, VOC� N�O TEM PERMISS�O PARA ACESSAR ESTE M�DULO!");
        setlocale(LC_ALL, "C");
        getch();
        gerenciarClientes();
    }
}
void modificarClientePassivo()
{
    cls();

    char leitor[200];
    char analisador[200];
    memset(leitor, '\0', sizeof(leitor));
    memset(analisador, '\0', sizeof(analisador));
    strcat(analisador, dados.usuario);
    strcat(analisador, " ");
    strcat(analisador, dados.senha);
    if(strcmp(ADMIN, analisador) == 0)
    {
        memset(analisador, '\0', sizeof(analisador));
        FILE *fileTemp;

        createBox(1, 2, 3, 55);
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 14);
        printf("MODIFICAR PASSIVO DO CLIENTE");
        setlocale(LC_ALL, "C");
        createBox(3, 2, 12, 55);
        setPosition(3, 2);
        printf("%c", 195);
        setPosition(3, 55);
        printf("%c", 180);

        setlocale(LC_ALL, "Portuguese");
        setPosition(4, 4);
        printf("Cliente:");
        setPosition(6, 4);
        printf("%s", cliente.nome);
        setlocale(LC_ALL, "C");
        createBox(5, 3, 7, 54);

        setlocale(LC_ALL, "Portuguese");
        setPosition(8, 4);
        printf("Passivo atual:");
        setPosition(10, 4);
        printf("%.2lf", cliente.despesas);
        setlocale(LC_ALL, "C");
        createBox(9, 3, 11, 19);

        setlocale(LC_ALL, "Portuguese");
        setPosition(8, 32);
        printf("Novo passivo:");
        setlocale(LC_ALL, "C");
        createBox(9, 31, 11, 42);
        setPosition(10, 43);
        printf(",");
        createBox(9, 44, 11, 47);

        char id[21];
        memset(id, '\0', sizeof(id));
        itoa(cliente.id, id, 10);
        strcat(id, " ");

        unsigned int i;

        char ch = '\0';
        int ctecla = 0;

        char despesasStr[11];
        char despesasVirgula[3];
        double saldoTotal;

        do
        {

            limparPergunta(1,56);
            setPosition(10,32);
            printf(" ");
            setPosition(10,33);
            printf(" ");
            setPosition(10,34);
            printf(" ");
            setPosition(10,35);
            printf(" ");
            setPosition(10,36);
            printf(" ");
            setPosition(10,37);
            printf(" ");
            setPosition(10,38);
            printf(" ");
            setPosition(10,39);
            printf(" ");
            setPosition(10,40);
            printf(" ");
            setPosition(10,41);
            printf(" ");
            setPosition(10,45);
            printf(" ");
            setPosition(10,46);
            printf(" ");


            memset(despesasStr, '\0', sizeof(despesasStr));
            memset(despesasVirgula, '\0', sizeof(despesasVirgula));

            ch = '\0';
            ctecla = 0;
            setPosition(10, 32);
            while(ctecla<10)
            {
                ch = getch();

                switch(ch)
                {
                case BACKSPACE:
                    if(ctecla>0)
                    {
                        fflush(stdin);
                        putch(BACKSPACE);
                        ch = '\0';
                        despesasStr[ctecla-1] = ch;
                        ctecla--;
                        putch(SPACE);
                        putch(BACKSPACE);
                    }
                    break;
                case TAB:
                    putch(TAB);
                    ctecla = 50;
                    break;
                case ENTER:
                    putch(ENTER);
                    ctecla = 50;
                    break;
                case ESC:
                    cls();
                    setlocale(LC_ALL, "Portuguese");
                    setPosition(2, 3);
                    printf("OPERA��O CANCELADA COM SUCESSO!");
                    setlocale(LC_ALL, "C");
                    getch();
                    gerenciarClientes();
                    break;
                default:
                    if((ch == '0') || (ch =='1') || (ch =='2') || (ch =='3') || (ch =='4') || (ch =='5') || (ch =='6') || (ch =='7') || (ch =='8') || (ch =='9'))
                    {
                        despesasStr[ctecla] = ch;
                        putch(ch);
                        ctecla++;
                    }
                    break;
                }
            }

            strcat(despesasStr, ".");

            ch = '\0';
            ctecla = 0;
            setPosition(10, 45);
            while(ctecla<2)
            {

                ch = getch();

                switch(ch)
                {
                case BACKSPACE:
                    if(ctecla>0)
                    {
                        fflush(stdin);
                        putch(BACKSPACE);
                        ch = '\0';
                        despesasVirgula[ctecla-1] = ch;
                        ctecla--;
                        putch(SPACE);
                        putch(BACKSPACE);
                    }
                    break;
                case TAB:
                    putch(TAB);
                    ctecla = 50;
                    break;
                case ENTER:
                    putch(ENTER);
                    ctecla = 50;
                    break;
                case ESC:
                    cls();
                    setlocale(LC_ALL, "Portuguese");
                    setPosition(2, 3);
                    printf("OPERA��O CANCELADA COM SUCESSO!");
                    setlocale(LC_ALL, "C");
                    getch();
                    gerenciarClientes();
                    break;
                default:
                    if((ch == '0') || (ch =='1') || (ch =='2') || (ch =='3') || (ch =='4') || (ch =='5') || (ch =='6') || (ch =='7') || (ch =='8') || (ch =='9'))
                    {
                        despesasVirgula[ctecla] = ch;
                        putch(ch);
                        ctecla++;
                    }
                    break;
                }
            }

        }
        while (pergunta("Confirmar ativo?", 1, 56) == 0);
        limparPergunta(1, 56);
        if((strcmp(despesasStr, "") == 0) && (strcmp(despesasVirgula, "") == 0))   //Caso o valor do ativo tiver vazio ent�o retornar� como zero
        {
            strcpy(despesasStr, "0");
            strcpy(despesasVirgula, "00");
        }
        strcat(despesasStr, despesasVirgula);

        if(pergunta("Modificar ativo?", 1, 56) == 1)
        {
            setlocale(LC_ALL, "Portuguese");
            //RECUPERANDO O VALOR DO SALDO TOTAL DO ARQUIVO TEXTO
            file = fopen("./Cliente/sald.txt", "r");
            fscanf(file, "%lf", &saldoTotal);
            fclose(file);

            //SUBTRAINDO O VALOR ANTIGO DO SALDO ANTERIOR DOS CLIENTES
            cliente.saldo = cliente.faturamento - cliente.despesas;
            saldoTotal -= cliente.saldo;
            cliente.despesas = strtod(despesasStr, NULL);
            cliente.saldo = cliente.faturamento - cliente.despesas;
            saldoTotal += cliente.saldo;

            //SOMANDO O SALDO TOTAL COM O NOVO VALOR
            file = fopen("./Cliente/sald.txt", "w");
            fprintf(file, "%.2lf", saldoTotal);
            fclose(file);

            //ALTERANDO VALOR DIRETAMENTE NO ARQUIVO TEXTO PRINCIPAL DOS CLIENTES
            file = fopen("./Cliente/cli.txt", "r");
            fileTemp = fopen("./Cliente/cliTemp.txt", "w");
            while(fgets(leitor, 200, file) != NULL)
            {
                for(i = 0; i < strlen(id); i++)
                {
                    analisador[i] = leitor[i];
                }

                if(strcmp(analisador, id) == 0)
                {
                    for(i = 0; i < strlen(cliente.nome); i++)
                    {
                        if(cliente.nome[i] == ' ')
                        {
                            cliente.nome[i] = '_';
                        }
                    }
                    fprintf(fileTemp, "%s%s %s %s %s %.2lf %.2lf %.2lf\n", id, cliente.nome, cliente.email, cliente.telefone, cliente.tipo_pessoa, cliente.faturamento, cliente.despesas, cliente.saldo);
                    for(i = 0; i < strlen(cliente.nome); i++)
                    {
                        if(cliente.nome[i] == '_')
                        {
                            cliente.nome[i] = ' ';
                        }
                    }
                }
                else
                {
                    fprintf(fileTemp, "%s", leitor);
                }

                memset(leitor, '\0', sizeof(leitor));
                memset(analisador, '\0', sizeof(analisador));
            }
            fclose(file);
            fclose(fileTemp);

            remove("./Cliente/cli.txt");
            rename("./Cliente/cliTemp.txt", "./Cliente/cli.txt");

            memset(mensagem, '\0', sizeof(mensagem));
            strcpy(mensagem, "ALTEROU O PASSIVO DO(A) CLIENTE \"");
            strcat(mensagem, cliente.nome);
            strcat(mensagem, "\"");
            registrarNoLog(mensagem);

            setlocale(LC_ALL, "C");
            cls();
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("MODIFICA��O DE PASSIVO DO CLIENTE REALIZADA COM SUCESSO!");
            setlocale(LC_ALL, "C");
            getch();
            gerenciarClientes();
        }
        else
        {
            cls();
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("MODIFICA��O DE PASSIVO DO CLIENTE CANCELADA COM SUCESSO!");
            setlocale(LC_ALL, "C");
            getch();
            gerenciarClientes();
        }

    }
    else
    {
        cls();
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 3);
        printf("ERRO: ACESSO NEGADO, VOC� N�O TEM PERMISS�O PARA ACESSAR ESTE M�DULO!");
        setlocale(LC_ALL, "C");
        getch();
        gerenciarClientes();
    }
}

//GERENCIAR USU�RIOS
void gerenciarUsuarios()
{
    cls();

    //Criando o layout
    createBox(1, 2, 3, 41);
    createBox(3, 2, 8, 41);
    setPosition(3, 2);
    printf("%c", 195);
    setPosition(3, 41);
    printf("%c", 180);

    setlocale(LC_ALL, "Portuguese");
    setPosition(2, 13);
    printf("GERENCIAR USU�RIOS");
    setPosition(4, 3);
    printf("  1 - Cadastrar usu�rio");
    setPosition(5, 3);
    printf("  2 - Remover usu�rio");
    setPosition(6, 3);
    printf("  3 - Listar usu�rios");
    setPosition(7, 3);
    printf("  4 - Voltar");
    setPosition(4, 3);
    printf("�");
    setPosition(4, 5);
    printf("1 - CADASTRAR USU�RIO");
    setlocale(LC_ALL, "C");

    //Anima��o na troca de op��o
    int tecla;
    int opcao = 1;

    while(1)
    {
        setbuf(stdin, NULL);
        tecla = getch();

        if(tecla == ESC)
        {
            menuPrincipal();
        }

        if (tecla==13)   // Enter
        {
            break;
        }

        if(tecla == 80 || tecla == 77)   //Seta para baixo ou seta direita
        {
            switch(opcao)
            {
            case 1:
                tecla = 50;
                break;

            case 2:
                tecla = 51;
                break;

            case 3:
                tecla = 52;
                break;

            case 4:
                tecla = 49;
                break;
            }
        }

        if(tecla == 72 || tecla == 75)   //Seta seta para cima ou esquerda
        {
            switch(opcao)
            {
            case 1:
                tecla = 52;
                break;

            case 2:
                tecla = 49;
                break;

            case 3:
                tecla = 50;
                break;

            case 4:
                tecla = 51;
                break;
            }
        }


        setlocale(LC_ALL, "Portuguese");
        if(tecla == 49)
        {
            setPosition(4, 3);
            printf("  1 - Cadastrar usu�rio");
            setPosition(5, 3);
            printf("  2 - Remover usu�rio");
            setPosition(6, 3);
            printf("  3 - Listar usu�rios");
            setPosition(7, 3);
            printf("  4 - Voltar");
            setPosition(4, 3);
            printf("�");
            setPosition(4, 5);
            printf("1 - CADASTRAR USU�RIO");
            opcao = 1;
        }
        else if (tecla == 50)
        {
            setPosition(4, 3);
            printf("  1 - Cadastrar usu�rio");
            setPosition(5, 3);
            printf("  2 - Remover usu�rio");
            setPosition(6, 3);
            printf("  3 - Listar usu�rios");
            setPosition(7, 3);
            printf("  4 - Voltar");
            setPosition(5, 3);
            printf("�");
            setPosition(5, 5);
            printf("2 - REMOVER USU�RIO");
            opcao = 2;
        }
        else if (tecla == 51)
        {
            setPosition(4, 3);
            printf("  1 - Cadastrar usu�rio");
            setPosition(5, 3);
            printf("  2 - Remover usu�rio");
            setPosition(6, 3);
            printf("  3 - Listar usu�rios");
            setPosition(7, 3);
            printf("  4 - Voltar");
            setPosition(6, 3);
            printf("�");
            setPosition(6, 5);
            printf("3 - LISTAR USU�RIOS");
            opcao = 3;
        }
        else if (tecla == 52)
        {
            setPosition(4, 3);
            printf("  1 - Cadastrar usu�rio");
            setPosition(5, 3);
            printf("  2 - Remover usu�rio");
            setPosition(6, 3);
            printf("  3 - Listar usu�rios");
            setPosition(7, 3);
            printf("  4 - Voltar");
            setPosition(7, 3);
            printf("�");
            setPosition(7, 5);
            printf("4 - VOLTAR");
            opcao = 4;
        }
        setlocale(LC_ALL, "C");
    }

    switch(opcao)
    {
    case 1:
        cadastrarUsuario();
        break;
    case 2:
        removerUsuario();
        break;
    case 3:
        listarUsuarios();
        break;
    case 4:
        menuPrincipal();
        break;
    }
}

void cadastrarUsuario()
{
    cls();

    int i;
    int positionSpace;

    char usuario[50];
    char senha[50];
    char confirmarSenha[50];
    char leitor[100];
    char analisador[50];

    memset(usuario, '\0', sizeof(usuario));
    memset(senha, '\0', sizeof(senha));
    memset(confirmarSenha, '\0', sizeof(confirmarSenha));
    memset(leitor, '\0', sizeof(leitor));
    memset(analisador, '\0', sizeof(analisador));

    //Montando as bordas da tela de cadastrar usu�rio
    createBox(1, 2, 3, 50);
    setlocale(LC_ALL, "Portuguese");
    setPosition(2, 17);
    printf("CADASTRAR USU�RIO");
    setlocale(LC_ALL, "C");
    createBox(3, 2, 16, 50);
    setPosition(3, 2);
    printf("%c", 195);
    setPosition(3, 50);
    printf("%c", 180);

    //Receber senha atual
    setlocale(LC_ALL, "Portuguese");
    setPosition(4, 4);
    printf("Usu�rio: ");
    setlocale(LC_ALL, "C");
    createBox(5, 3, 7,49 );

    //Receber nova senha
    setlocale(LC_ALL, "Portuguese");
    setPosition(8, 4);
    printf("Senha: ");
    setlocale(LC_ALL, "C");
    createBox(9, 3, 11,49 );

    //Receber nova senha
    setlocale(LC_ALL, "Portuguese");
    setPosition(12, 4);
    printf("Confirmar senha: ");
    setlocale(LC_ALL, "C");
    createBox(13, 3, 15,49 );

    char ch = '\0';
    int ctecla = 0;

    setPosition(6, 4);
    while(ctecla<45)
    {
        ch = getch();

        switch(ch)
        {
        case BACKSPACE:
            if(ctecla>0)
            {
                fflush(stdin);
                putch(BACKSPACE);
                ch = '\0';
                usuario[ctecla-1] = ch;
                ctecla--;
                putch(SPACE);
                putch(BACKSPACE);
            }
            break;
        case TAB:
            putch(TAB);
            ctecla = 50;
            break;
        case ENTER:
            putch(ENTER);
            ctecla = 50;
            break;
        case ESC:
            cls();
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("OPERA��O CANCELADA COM SUCESSO!");
            setlocale(LC_ALL, "C");
            getch();
            gerenciarUsuarios();
            break;
        case SPACE:
            //VAI FAZER NADA
            break;
        default:
            usuario[ctecla] = ch;
            putch(ch);
            ctecla++;
            break;
        }
    }

    setPosition(10, 4);
    ch = '\0';
    ctecla = 0;

    while(ctecla<45)
    {
        ch = getch();

        switch(ch)
        {
        case BACKSPACE:
            if(ctecla>0)
            {
                fflush(stdin);
                putch(BACKSPACE);
                ch = '\0';
                senha[ctecla-1] = ch;
                ctecla--;
                putch(SPACE);
                putch(BACKSPACE);
            }
            break;
        case TAB:
            putch(TAB);
            ctecla = 50;
            break;
        case ENTER:
            putch(ENTER);
            ctecla = 50;
            break;
        case ESC:
            cls();
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("OPERA��O CANCELADA COM SUCESSO!");
            setlocale(LC_ALL, "C");
            getch();
            gerenciarUsuarios();
            break;
        default:
            senha[ctecla] = ch;
            putch('*');
            ctecla++;
            break;
        }
    }

    setPosition(14, 4);
    ch = '\0';
    ctecla = 0;

    while(ctecla<45)
    {
        ch = getch();

        switch(ch)
        {
        case BACKSPACE:
            if(ctecla>0)
            {
                fflush(stdin);
                putch(BACKSPACE);
                ch = '\0';
                confirmarSenha[ctecla-1] = ch;
                ctecla--;
                putch(SPACE);
                putch(BACKSPACE);
            }
            break;
        case TAB:
            putch(TAB);
            ctecla = 50;
            break;
        case ENTER:
            putch(ENTER);
            ctecla = 50;
            break;
        case ESC:
            cls();
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("OPERA��O CANCELADA COM SUCESSO!");
            setlocale(LC_ALL, "C");
            getch();
            gerenciarUsuarios();
            break;
        default:
            confirmarSenha[ctecla] = ch;
            putch('*');
            ctecla++;
            break;
        }
    }

    while(1)
    {
        file = fopen("./Users/us.txt", "r");
        while(fgets(leitor, 100, file) != NULL)
        {

            memset(analisador, '\0', sizeof(analisador));

            i = 0;
            while(1)
            {
                if(leitor[i] == ' ')
                {
                    positionSpace = i;
                    break;
                }
                i++;
            }

            for(i = 0; i < positionSpace; i++)
            {
                analisador[i] = leitor[i];
            }

            if(strcmp(analisador, usuario) == 0)
            {
                break;
            }

            memset(leitor, '\0', sizeof(leitor));
        }
        fclose(file);

        if(strcmp(analisador, usuario) == 0)   //Verificando se o usuario j� exite
        {
            setlocale(LC_ALL, "Portuguese");
            setPosition(18, 3);
            printf("ERRO: NOME DE USU�RIO J� EXISTENTE!");
            setlocale(LC_ALL, "C");
            if(pergunta("Continuar opera��o?", 1, 51) == 1)
            {

                limparLinha(18);
                limparPergunta(1, 51);
                setPosition(6, 4);
                for (i = 1; i <= 45; i++)
                {
                    printf(" ");    //Limpando input do usu�rio
                }

                memset(usuario, '\0', sizeof(usuario));

                ch = '\0';
                ctecla = 0;

                setPosition(6, 4);
                while(ctecla<45)
                {
                    ch = getch();

                    switch(ch)
                    {
                    case BACKSPACE:
                        if(ctecla>0)
                        {
                            fflush(stdin);
                            putch(BACKSPACE);
                            ch = '\0';
                            usuario[ctecla-1] = ch;
                            ctecla--;
                            putch(SPACE);
                            putch(BACKSPACE);
                        }
                        break;
                    case TAB:
                        putch(TAB);
                        ctecla = 50;
                        break;
                    case ENTER:
                        putch(ENTER);
                        ctecla = 50;
                        break;
                    case ESC:
                        cls();
                        setlocale(LC_ALL, "Portuguese");
                        setPosition(2, 3);
                        printf("OPERA��O CANCELADA COM SUCESSO!");
                        setlocale(LC_ALL, "C");
                        getch();
                        gerenciarUsuarios();
                        break;
                    case SPACE:
                        //VAI FAZER NADA
                        break;
                    default:
                        usuario[ctecla] = ch;
                        putch(ch);
                        ctecla++;
                        break;
                    }
                }
                continue;
            }
            else
            {
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("CADASTRAMENTO DE USU�RIO CANCELADO COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarUsuarios();
            }
        }

        else if (strcmp(usuario, "") == 0)   //Se o usu�rio deixar o campo de usu�rio estiver vazio
        {
            setlocale(LC_ALL, "Portuguese");
            setPosition(18, 3);
            printf("ERRO: O CAMPO DE USU�RIO EST� VAZIO!");
            setlocale(LC_ALL, "C");
            if(pergunta("Continuar opera��o?", 1, 51) == 1)
            {

                limparLinha(18);
                limparPergunta(1, 51);
                setPosition(6, 4);
                for (i = 1; i <= 45; i++)
                {
                    printf(" ");    //Limpando input do usu�rio
                }

                memset(usuario, '\0', sizeof(usuario));

                ch = '\0';
                ctecla = 0;

                setPosition(6, 4);
                while(ctecla<45)
                {
                    ch = getch();

                    switch(ch)
                    {
                    case BACKSPACE:
                        if(ctecla>0)
                        {
                            fflush(stdin);
                            putch(BACKSPACE);
                            ch = '\0';
                            usuario[ctecla-1] = ch;
                            ctecla--;
                            putch(SPACE);
                            putch(BACKSPACE);
                        }
                        break;
                    case TAB:
                        putch(TAB);
                        ctecla = 50;
                        break;
                    case ENTER:
                        putch(ENTER);
                        ctecla = 50;
                        break;
                    case ESC:
                        cls();
                        setlocale(LC_ALL, "Portuguese");
                        setPosition(2, 3);
                        printf("OPERA��O CANCELADA COM SUCESSO!");
                        setlocale(LC_ALL, "C");
                        getch();
                        gerenciarUsuarios();
                        break;
                    case SPACE:
                        //VAI FAZER NADA
                        break;
                    default:
                        usuario[ctecla] = ch;
                        putch(ch);
                        ctecla++;
                        break;
                    }
                }
                continue;
            }
            else
            {
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("CADASTRAMENTO DE USU�RIO CANCELADO COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarUsuarios();
            }
        }

        else if(strlen(senha) < 8)   //Verificando se a senha tem mais de 8 d�gitos
        {

            setlocale(LC_ALL, "Portuguese");
            setPosition(18, 3);
            printf("ERRO: A SENHA DEVE CONTER NO M�NIMO 8 CARACTERES");
            setlocale(LC_ALL, "C");
            if(pergunta("Continuar opera��o?", 1, 51) == 1)
            {

                limparLinha(18);
                limparPergunta(1, 51);
                setPosition(10, 4);
                for (i = 1; i <= 45; i++)
                {
                    printf(" ");    //Limpando input da senha
                }
                setPosition(14, 4);
                for (i = 1; i <= 45; i++)
                {
                    printf(" ");    //Limpando input do confirmar senha
                }

                memset(senha, '\0', sizeof(senha));
                memset(confirmarSenha, '\0', sizeof(confirmarSenha));

                setPosition(10, 4);
                ctecla = 0;
                ch = '\0';

                while(ctecla<45)
                {
                    ch = getch();

                    switch(ch)
                    {
                    case BACKSPACE:
                        if(ctecla>0)
                        {
                            fflush(stdin);
                            putch(BACKSPACE);
                            ch = '\0';
                            senha[ctecla-1] = ch;
                            ctecla--;
                            putch(SPACE);
                            putch(BACKSPACE);
                        }
                        break;
                    case TAB:
                        putch(TAB);
                        ctecla = 50;
                        break;
                    case ENTER:
                        putch(ENTER);
                        ctecla = 50;
                        break;
                    case ESC:
                        cls();
                        setlocale(LC_ALL, "Portuguese");
                        setPosition(2, 3);
                        printf("OPERA��O CANCELADA COM SUCESSO!");
                        setlocale(LC_ALL, "C");
                        getch();
                        gerenciarUsuarios();
                        break;
                    default:
                        senha[ctecla] = ch;
                        putch('*');
                        ctecla++;
                        break;
                    }
                }

                setPosition(14, 4);
                ctecla = 0;
                ch = '\0';

                while(ctecla<45)
                {
                    ch = getch();

                    switch(ch)
                    {
                    case BACKSPACE:
                        if(ctecla>0)
                        {
                            fflush(stdin);
                            putch(BACKSPACE);
                            ch = '\0';
                            confirmarSenha[ctecla-1] = ch;
                            ctecla--;
                            putch(SPACE);
                            putch(BACKSPACE);
                        }
                        break;
                    case TAB:
                        putch(TAB);
                        ctecla = 50;
                        break;
                    case ENTER:
                        putch(ENTER);
                        ctecla = 50;
                        break;
                    case ESC:
                        cls();
                        setlocale(LC_ALL, "Portuguese");
                        setPosition(2, 3);
                        printf("OPERA��O CANCELADA COM SUCESSO!");
                        setlocale(LC_ALL, "C");
                        getch();
                        gerenciarUsuarios();
                        break;
                    default:
                        confirmarSenha[ctecla] = ch;
                        putch('*');
                        ctecla++;
                        break;
                    }
                }
                continue;
            }
            else
            {
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("CADASTRAMENTO DE USU�RIO CANCELADO COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarUsuarios();
            }
        }

        else if(strcmp(senha, confirmarSenha) != 0)   //Verificando a senha e confirma��o da senha s�o iguais
        {
            setlocale(LC_ALL, "Portuguese");
            setPosition(18, 3);
            printf("ERRO: A NOVA SENHA E A CONFIRMA��O DA NOVA SENHA N�O SE COINCIDEM!");
            setlocale(LC_ALL, "C");
            if(pergunta("Continuar opera��o?", 1, 51) == 1)
            {

                limparLinha(18);
                limparPergunta(1, 51);
                setPosition(10, 4);
                for (i = 1; i <= 45; i++)
                {
                    printf(" ");    //Limpando input da senha
                }
                setPosition(14, 4);
                for (i = 1; i <= 45; i++)
                {
                    printf(" ");    //Limpando input do confirmar senha
                }

                memset(senha, '\0', sizeof(senha));
                memset(confirmarSenha, '\0', sizeof(confirmarSenha));

                setPosition(10, 4);
                ctecla = 0;
                ch = '\0';

                while(ctecla<45)
                {
                    ch = getch();

                    switch(ch)
                    {
                    case BACKSPACE:
                        if(ctecla>0)
                        {
                            fflush(stdin);
                            putch(BACKSPACE);
                            ch = '\0';
                            senha[ctecla-1] = ch;
                            ctecla--;
                            putch(SPACE);
                            putch(BACKSPACE);
                        }
                        break;
                    case TAB:
                        putch(TAB);
                        ctecla = 50;
                        break;
                    case ENTER:
                        putch(ENTER);
                        ctecla = 50;
                        break;
                    case ESC:
                        cls();
                        setlocale(LC_ALL, "Portuguese");
                        setPosition(2, 3);
                        printf("OPERA��O CANCELADA COM SUCESSO!");
                        setlocale(LC_ALL, "C");
                        getch();
                        gerenciarUsuarios();
                        break;
                    default:
                        senha[ctecla] = ch;
                        putch('*');
                        ctecla++;
                        break;
                    }
                }

                setPosition(14, 4);
                ctecla = 0;
                ch = '\0';

                while(ctecla<45)
                {
                    ch = getch();

                    switch(ch)
                    {
                    case BACKSPACE:
                        if(ctecla>0)
                        {
                            fflush(stdin);
                            putch(BACKSPACE);
                            ch = '\0';
                            confirmarSenha[ctecla-1] = ch;
                            ctecla--;
                            putch(SPACE);
                            putch(BACKSPACE);
                        }
                        break;
                    case TAB:
                        putch(TAB);
                        ctecla = 50;
                        break;
                    case ENTER:
                        putch(ENTER);
                        ctecla = 50;
                        break;
                    case ESC:
                        cls();
                        setlocale(LC_ALL, "Portuguese");
                        setPosition(2, 3);
                        printf("OPERA��O CANCELADA COM SUCESSO!");
                        setlocale(LC_ALL, "C");
                        getch();
                        gerenciarUsuarios();
                        break;
                    default:
                        confirmarSenha[ctecla] = ch;
                        putch('*');
                        ctecla++;
                        break;
                    }
                }
                continue;
            }
            else
            {
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("CADASTRAMENTO DE USU�RIO CANCELADO COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarUsuarios();
            }
        }

        else   //Caso n�o tiver nenhum problema
        {
            if (pergunta("Confirmar cadastro?", 1, 51) == 1)
            {

                file = fopen("./Users/us.txt", "a");
                fprintf(file, "%s %s f0\n", usuario, senha);
                fclose(file);

                memset(mensagem, '\0', sizeof(mensagem));
                strcat(mensagem, "CADASTROU O(A) USUARIO(A) \"");
                strcat(mensagem, usuario);
                strcat(mensagem, "\"");
                registrarNoLog(mensagem);

                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("CADASTRO DE USU�RIO CRIADO COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarUsuarios();
            }
            else
            {
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("CADASTRAMENTO DE USU�RIO CANCELADO COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarUsuarios();
            }
        }
    }
}

void removerUsuario()
{

    cls();

    int i;
    int positionSpace;
    char usuario[50];
    char leitor[100];
    char analisador[100];

    FILE *fileTemp;

    memset(usuario, '\0', sizeof(usuario));
    memset(leitor, '\0', sizeof(leitor));
    memset(analisador, '\0', sizeof(analisador));
    strcat(analisador, dados.usuario);
    strcat(analisador, " ");
    strcat(analisador, dados.senha);

    if(strcmp(ADMIN, analisador) !=  0)
    {
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 3);
        printf("ERRO: ACESSO NEGADO, VOC� N�O TEM PERMISS�O PARA ACESSAR ESTE M�DULO!");
        setlocale(LC_ALL, "C");
        getch();
        gerenciarUsuarios();
    }
    else
    {
        //Montando as bordas da tela de redefini��o de senha
        createBox(1, 2, 3, 50);
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 18);
        printf("REMOVER USU�RIO");
        setlocale(LC_ALL, "C");
        createBox(3, 2, 12, 50);
        setPosition(3, 2);
        printf("%c", 195);
        setPosition(3, 50);
        printf("%c", 180);

        //Receber senha atual
        setlocale(LC_ALL, "Portuguese");
        setPosition(4, 4);
        printf("Pesquisar usu�rio: ");
        setlocale(LC_ALL, "C");
        createBox(5, 3, 7,49 );

        //Receber nova senha
        setlocale(LC_ALL, "Portuguese");
        setPosition(8, 4);
        printf("Usu�rio encontrado: ");
        setlocale(LC_ALL, "C");
        createBox(9, 3, 11,49 );

        char ch = '\0';
        int ctecla = 0;

        setPosition(6, 4);
        while(ctecla<45)
        {
            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    usuario[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarUsuarios();
                break;
            default:
                usuario[ctecla] = ch;
                putch(ch);
                ctecla++;
                break;
            }
        }

        if(strcmp(usuario, "") == 0)   //Caso o usu�rio envie o campo em branco
        {
            strcpy(usuario, ".............................................");
        }

        //Fiscalizando pelo nome id�ntico do usu�rio
        file = fopen("./Users/us.txt", "r");
        while(fgets(leitor, 100, file) != NULL)
        {

            memset(analisador, '\0', sizeof(analisador));

            i = 0;
            while(1)
            {
                if(leitor[i] == ' ')
                {
                    positionSpace = i;
                    break;
                }
                i++;
            }

            for(i = 0; i < positionSpace; i++)
            {
                analisador[i] = leitor[i];
            }

            if(strcmp(analisador, usuario) == 0)
            {
                setPosition(10, 4);
                printf("%s", analisador);
                break;
            }
            else
            {
                memset(leitor, '\0', sizeof(leitor));
                memset(analisador, '\0', sizeof(analisador));
                continue;
            }
        }
        fclose(file);

        //Procurando outros usu�rios que come�am com os mesmos caracteres
        if(strcmp(analisador, "") == 0)
        {
            file = fopen("./Users/us.txt", "r");
            while(fgets(leitor, 100, file) != NULL)
            {

                memset(analisador, '\0', sizeof(analisador));

                for(i = 0; i < strlen(usuario); i++)
                {
                    analisador[i] = leitor[i];
                }

                if(strcmp(analisador, usuario) == 0)
                {
                    i = 0;
                    while(1)
                    {
                        if(leitor[i] == ' ')
                        {
                            positionSpace = i;
                            break;
                        }
                        i++;
                    }
                    memset(analisador, '\0', sizeof(analisador));
                    for(i = 0; i < positionSpace; i++)
                    {
                        analisador[i] = leitor[i];
                    }
                    setPosition(10, 4);
                    printf("%s", analisador);
                    break;

                }
                else
                {
                    memset(leitor, '\0', sizeof(leitor));
                    memset(analisador, '\0', sizeof(analisador));
                    continue;
                }
            }
        }

        if(strcmp(analisador, "") == 0)   //Se nenhum usu�rio for encontrado
        {
            setlocale(LC_ALL, "Portuguese");
            setPosition(14, 3);
            printf("ERRO: NENHUM USU�RIO ENCONTRADO!");
            setlocale(LC_ALL, "C");
            if(pergunta("Continuar opera��o?", 1, 51) == 1)
            {
                removerUsuario();
            }
            else
            {
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("REMO��O DE USU�RIO CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarUsuarios();
            }
        }

        else   //Caso seja encontrado
        {
            if(pergunta("Confirmar remo��o?", 1, 51) == 1)
            {
                strcat(analisador, " ");
                strcpy(usuario, analisador);
                memset(analisador, '\0', sizeof(analisador));
                memset(leitor, '\0', sizeof(leitor));
                file = fopen("./Users/us.txt", "r");
                fileTemp = fopen("./Users/usTemp.txt", "w");

                while(fgets(leitor, 100, file) != NULL)
                {

                    for(i = 0; i < positionSpace+1; i++)
                    {
                        analisador[i] = leitor[i];
                    }

                    if(strcmp(analisador, usuario) == 0)
                    {
                        continue;
                    }
                    else
                    {
                        fprintf(fileTemp, "%s", leitor);
                        memset(analisador, '\0', sizeof(analisador));
                        memset(leitor, '\0', sizeof(leitor));
                    }
                }
                fclose(file);
                fclose(fileTemp);

                remove("./Users/us.txt");
                rename("./Users/usTemp.txt", "./Users/us.txt");

                usuario[strlen(usuario) - 1] = '\0';
                memset(mensagem, '\0', sizeof(mensagem));
                strcat(mensagem, "REMOVEU O(A) USUARIO(A) \"");
                strcat(mensagem, usuario);
                strcat(mensagem, "\"");
                registrarNoLog(mensagem);

                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("REMO��O DE USU�RIO FEITA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarUsuarios();

            }
            else
            {
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("REMO��O DE USU�RIO CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                gerenciarUsuarios();
            }

        }
    }
}

void listarUsuarios()
{

    cls();

    unsigned long i;
    unsigned long linha;
    unsigned long quantUsers = 0;
    int positionSpace;
    char leitor[100];
    char analisador[100];
    memset(leitor, '\0', sizeof(leitor));
    memset(analisador, '\0', sizeof(analisador));
    strcat(analisador, dados.usuario);
    strcat(analisador, " ");
    strcat(analisador, dados.senha);
    if(strcmp(ADMIN, analisador) == 0)   //Se for administrador
    {
        linha = 6;
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 3);
        printf("---------- LISTA DE USU�RIOS ----------");
        setPosition(4, 5);
        printf("USU�RIO");
        setPosition(4, 14);
        printf("|");
        setPosition(4, 17);
        printf("SENHA");
        setlocale(LC_ALL, "C");

        memset(analisador, '\0', sizeof(analisador));
        file = fopen("./Users/us.txt", "r");
        while(fgets(leitor, 100, file) != NULL)
        {
            leitor[strlen(leitor)-1] = '\0';
            leitor[strlen(leitor)-1] = '\0';
            leitor[strlen(leitor)-1] = '\0';
            leitor[strlen(leitor)-1] = '\0';

            for(i = 0; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    strcat(analisador, " | ");
                    positionSpace = i;
                    break;
                }
                analisador[i] = leitor[i];
            }

            for(i = positionSpace+1; i < strlen(leitor); i++)
            {
                analisador[i+2] = leitor[i];
            }

            quantUsers++;
            setPosition(linha, 3);
            printf("- %s", analisador);
            linha+=2;

            memset(leitor, '\0', sizeof(leitor));
            memset(analisador, '\0', sizeof(analisador));
        }
        fclose(file);
        setPosition(linha, 3);
        printf("---------------------------------------");
        setlocale(LC_ALL, "Portuguese");
        setPosition(linha+1, 3);
        printf("Quantidade de usu�rios: %lu", quantUsers);
        setPosition(linha+3, 3);
        printf("PRESSIONE QUALQUER TECLA PARA VOLTAR...");
        setlocale(LC_ALL, "C");
        getch();
        gerenciarUsuarios();
    }
    else     //Caso n�o for administrador
    {
        linha = 4;
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 3);
        printf("---------- LISTA DE USU�RIOS ----------");

        setlocale(LC_ALL, "C");

        memset(analisador, '\0', sizeof(analisador));
        file = fopen("./Users/us.txt", "r");
        while(fgets(leitor, 100, file) != NULL)
        {
            leitor[strlen(leitor)-1] = '\0';
            leitor[strlen(leitor)-1] = '\0';
            leitor[strlen(leitor)-1] = '\0';
            leitor[strlen(leitor)-1] = '\0';

            for(i = 0; i < strlen(leitor); i++)
            {
                if(leitor[i] == ' ')
                {
                    break;
                }
                analisador[i] = leitor[i];
            }

            quantUsers++;
            setPosition(linha, 3);
            printf("- %s", analisador);
            linha+=2;

            memset(leitor, '\0', sizeof(leitor));
            memset(analisador, '\0', sizeof(analisador));
        }
        fclose(file);
        setPosition(linha, 3);
        printf("---------------------------------------");
        setlocale(LC_ALL, "Portuguese");
        setPosition(linha+1, 3);
        printf("Quantidade de usu�rios: %lu", quantUsers);
        setPosition(linha+3, 3);
        printf("PRESSIONE QUALQUER TECLA PARA VOLTAR...");
        setlocale(LC_ALL, "C");
        getch();
        gerenciarUsuarios();
    }
}

//REGISTRO DE LOG
void registrosDeLog()
{
    char analisador[100];
    memset(analisador, '\0', sizeof(analisador));
    strcat(analisador, dados.usuario);
    strcat(analisador, " ");
    strcat(analisador, dados.senha);
    if(strcmp(ADMIN, analisador) == 0)
    {
        cls();

        //Criando o layout
        createBox(1, 2, 3, 41);
        createBox(3, 2, 7, 41);
        setPosition(3, 2);
        printf("%c", 195);
        setPosition(3, 41);
        printf("%c", 180);

        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 13);
        printf("REGISTROS DE LOG");
        setPosition(4, 3);
        printf("  1 - Ler registros");
        setPosition(5, 3);
        printf("  2 - Limpar registros");
        setPosition(6, 3);
        printf("  3 - Voltar");
        setPosition(4, 3);
        printf("�");
        setPosition(4, 5);
        printf("1 - LER REGISTROS");
        setlocale(LC_ALL, "C");

        //Anima��o na troca de op��o
        int tecla;
        int opcao = 1;

        while(1)
        {
            setbuf(stdin, NULL);
            tecla = getch();

            if(tecla == ESC)
            {
                menuPrincipal();
            }

            if (tecla==13)   // Enter
            {
                break;
            }

            if(tecla == 80 || tecla == 77)   //Seta para baixo ou seta direita
            {
                switch(opcao)
                {
                case 1:
                    tecla = 50;
                    break;

                case 2:
                    tecla = 51;
                    break;

                case 3:
                    tecla = 49;
                    break;
                }
            }

            if(tecla == 72 || tecla == 75)   //Seta seta para cima ou esquerda
            {
                switch(opcao)
                {
                case 1:
                    tecla = 51;
                    break;

                case 2:
                    tecla = 49;
                    break;

                case 3:
                    tecla = 50;
                    break;
                }
            }

            setlocale(LC_ALL, "Portuguese");
            if(tecla == 49)
            {
                setPosition(4, 3);
                printf("  1 - Ler registros");
                setPosition(5, 3);
                printf("  2 - Limpar registros");
                setPosition(6, 3);
                printf("  3 - Voltar");
                setPosition(4, 3);
                printf("�");
                setPosition(4, 5);
                printf("1 - LER REGISTROS");
                opcao = 1;
            }
            else if (tecla == 50)
            {
                setPosition(4, 3);
                printf("  1 - Ler registros");
                setPosition(5, 3);
                printf("  2 - Limpar registros");
                setPosition(6, 3);
                printf("  3 - Voltar");
                setPosition(5, 3);
                printf("�");
                setPosition(5, 5);
                printf("2 - LIMPAR REGISTROS");
                opcao = 2;
            }
            else if (tecla == 51)
            {
                setPosition(4, 3);
                printf("  1 - Ler registros");
                setPosition(5, 3);
                printf("  2 - Limpar registros");
                setPosition(6, 3);
                printf("  3 - Voltar");
                setPosition(6, 3);
                printf("�");
                setPosition(6, 5);
                printf("3 - VOLTAR");
                opcao = 3;
            }
        }
        setlocale(LC_ALL, "C");

        switch(opcao)
        {
        case 1:
            lerRegistros();
            break;
        case 2:
            limparRegistro();
            break;
        case 3:
            menuPrincipal();
            break;
        }
    }
    else
    {
        cls();
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 3);
        printf("ERRO: ACESSO NEGADO, VOC� N�O TEM PERMISS�O PARA ACESSAR ESTE M�DULO!");
        setlocale(LC_ALL, "C");
        getch();
        menuPrincipal();
    }
}

void lerRegistros()
{

    cls();
    unsigned long int quantRegistros = 0;

    char leitor[255];
    memset(leitor, '\0', sizeof(leitor));
    printf("\n  ---------- REGISTROS DE LOG ---------\n\n");
    file = fopen("./Registros/reg.txt", "r");
    setlocale(LC_ALL, "Portuguese");
    while(fgets(leitor, 255, file) != NULL)
    {
        quantRegistros++;
        printf("  - %s\n", leitor);
    }
    setlocale(LC_ALL, "C");
    fclose(file);
    printf("  -------------------------------------\n");
    printf("  Quantidade de registros: %lu\n\n", quantRegistros);
    printf("  PRESSIONE QUALQUER TECLA PARA VOLTAR...");
    getch();
    registrosDeLog();
}

void limparRegistro()
{
    if (pergunta("Confirmar limpeza?", 1, 42) == 1)
    {
        file = fopen("./Registros/reg.txt", "w");
        fclose(file);
        cls();
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 3);
        printf("LIMPEZA DOS REGISTROS FEITA COM SUCESSO!");
        setlocale(LC_ALL, "C");
        getch();
        registrosDeLog();
    }
    else
    {
        registrosDeLog();
    }
}

//SOBRE A NCR SYSTEM
void sobreNCRSystem()
{
    cls();
    setlocale(LC_ALL, "Portuguese");
    printf("\n  ---------- SOBRE A NCR SYSTEM ----------");
    printf("\n\n  MISS�O E VIS�O");
    printf("\n\n  Nossa miss�o � poder ajudar empreendedores de pequeno a m�dio porte do ");
    printf("\n  Brasil inteiro a prosperarem. Nossa paix�o pelo que fazemos, n�s move a cada dia ");
    printf("\n  no desafio de poder trazer qualidade de trabalho, modernidade e seguran�a para as ");
    printf("\n  empresas que prestamos servi�os. Nossa equipe � constitu�da por seis analistas, ");
    printf("\n  mas temos a pretens�o de crescermos no futuro, podendo expandir para outros ");
    printf("\n  estados. ");
    printf("\n\n  VALORES");
    printf("\n\n  Nossos valores s�o baseados na �tica dentro da organiza��o, respeitando ");
    printf("\n  acima de tudo nossos funcion�rios e clientes; Amor e dedica��o ao trabalho; Cren�a ");
    printf("\n  no neg�cio como fator para empreender e crescer; Humildade para com nossos ");
    printf("\n  funcion�rios e clientes. ");
    printf("\n\n  ----------------------------------------");
    printf("\n  PRESSIONE QUALQUER TECLA PARA VOLTAR...");
    setlocale(LC_ALL, "C");
    getch();
    menuPrincipal();
}

//AJUSTES
void ajustes()
{
    cls();

    //Criando o layout
    createBox(1, 2, 3, 41);
    createBox(3, 2, 7, 41);
    setPosition(3, 2);
    printf("%c", 195);
    setPosition(3, 41);
    printf("%c", 180);

    setlocale(LC_ALL, "Portuguese");
    setPosition(2, 18);
    printf("AJUSTES");
    setPosition(4, 3);
    printf("  1 - Redefinir senha");
    setPosition(5, 3);
    printf("  2 - Redefinir tema");
    setPosition(6, 3);
    printf("  3 - Voltar");
    setPosition(4, 3);
    printf("�");
    setPosition(4, 5);
    printf("1 - REDEFINIR SENHA");
    setlocale(LC_ALL, "C");

    //Anima��o na troca de op��o
    int tecla;
    int opcao = 1;

    while(1)
    {
        setbuf(stdin, NULL);
        tecla = getch();

        if(tecla == ESC)
        {
            menuPrincipal();
        }

        if (tecla==13)   // Enter
        {
            break;
        }

        if(tecla == 80 || tecla == 77)   //Seta para baixo ou seta direita
        {
            switch(opcao)
            {
            case 1:
                tecla = 50;
                break;

            case 2:
                tecla = 51;
                break;

            case 3:
                tecla = 49;
                break;
            }
        }

        if(tecla == 72 || tecla == 75)   //Seta seta para cima ou esquerda
        {
            switch(opcao)
            {
            case 1:
                tecla = 51;
                break;

            case 2:
                tecla = 49;
                break;

            case 3:
                tecla = 50;
                break;
            }
        }

        setlocale(LC_ALL, "Portuguese");
        if(tecla == 49)
        {
            setPosition(4, 3);
            printf("  1 - Redefinir senha");
            setPosition(5, 3);
            printf("  2 - Redefinir tema");
            setPosition(6, 3);
            printf("  3 - Voltar");
            setPosition(4, 3);
            printf("�");
            setPosition(4, 5);
            printf("1 - REDEFINIR SENHA");
            opcao = 1;
        }
        else if (tecla == 50)
        {
            setPosition(4, 3);
            printf("  1 - Redefinir senha");
            setPosition(5, 3);
            printf("  2 - Redefinir tema");
            setPosition(6, 3);
            printf("  3 - Voltar");
            setPosition(5, 3);
            printf("�");
            setPosition(5, 5);
            printf("2 - REDEFINIR TEMA");
            opcao = 2;
        }
        else if (tecla == 51)
        {
            setPosition(4, 3);
            printf("  1 - Redefinir senha");
            setPosition(5, 3);
            printf("  2 - Redefinir tema");
            setPosition(6, 3);
            printf("  3 - Voltar");
            setPosition(6, 3);
            printf("�");
            setPosition(6, 5);
            printf("3 - VOLTAR");
            opcao = 3;
        }
    }
    setlocale(LC_ALL, "C");

    switch(opcao)
    {
    case 1:
        redefinirSenha();
        break;
    case 2:
        redefinirTema();
        break;
    case 3:
        menuPrincipal();
        break;
    }
}

void redefinirSenha()
{


    cls();
    int i;

    char analisador[100];
    memset(analisador, '\0', sizeof(analisador));
    strcat(analisador, dados.usuario);
    strcat(analisador, " ");
    strcat(analisador, dados.senha);
    if(strcmp(ADMIN, analisador) == 0)
    {
        setlocale(LC_ALL, "Portuguese");
        setPosition(2, 3);
        printf("ERRO: O ADMINISTRADOR N�O PODE REDEFINIR A SENHA DIRETAMENTE PELO PROGRAMA.");
        setPosition(4, 3);
        printf("POR FAVOR, ENTRE EM CONTATO COM O SUPORTE!");
        setlocale(LC_ALL, "C");
        getch();
        ajustes();
    }
    else
    {
        //Montando as bordas da tela de redefini��o de senha
        createBox(1, 2, 3, 50);
        setPosition(2, 18);
        printf("REDEFINIR SENHA");
        createBox(3, 2, 16, 50);
        setPosition(3, 2);
        printf("%c", 195);
        setPosition(3, 50);
        printf("%c", 180);

        //Receber senha atual
        setlocale(LC_ALL, "Portuguese");
        setPosition(4, 4);
        printf("Senha atual: ");
        setlocale(LC_ALL, "C");
        createBox(5, 3, 7,49 );

        //Receber nova senha
        setlocale(LC_ALL, "Portuguese");
        setPosition(8, 4);
        printf("Nova senha: ");
        setlocale(LC_ALL, "C");
        createBox(9, 3, 11,49 );

        //Receber nova senha
        setlocale(LC_ALL, "Portuguese");
        setPosition(12, 4);
        printf("Confirmar nova senha: ");
        setlocale(LC_ALL, "C");
        createBox(13, 3, 15,49 );

        char senhaAtual[50];
        char novaSenha[50];
        char confirmarNovaSenha[50];

        memset(senhaAtual, '\0', sizeof(senhaAtual));
        memset(novaSenha, '\0', sizeof(novaSenha));
        memset(confirmarNovaSenha, '\0', sizeof(confirmarNovaSenha));

        char ch = '\0';
        int ctecla = 0;

        setPosition(6, 4);
        while(ctecla<45)
        {
            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    senhaAtual[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                ajustes();
                break;
            default:
                senhaAtual[ctecla] = ch;
                putch('*');
                ctecla++;
                break;
            }
        }

        setPosition(10, 4);
        ctecla = 0;
        ch = '\0';

        while(ctecla<45)
        {
            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    novaSenha[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                ajustes();
                break;
            default:
                novaSenha[ctecla] = ch;
                putch('*');
                ctecla++;
                break;
            }
        }

        setPosition(14, 4);
        ctecla = 0;
        ch = '\0';

        while(ctecla<45)
        {
            ch = getch();

            switch(ch)
            {
            case BACKSPACE:
                if(ctecla>0)
                {
                    fflush(stdin);
                    putch(BACKSPACE);
                    ch = '\0';
                    confirmarNovaSenha[ctecla-1] = ch;
                    ctecla--;
                    putch(SPACE);
                    putch(BACKSPACE);
                }
                break;
            case TAB:
                putch(TAB);
                ctecla = 50;
                break;
            case ENTER:
                putch(ENTER);
                ctecla = 50;
                break;
            case ESC:
                cls();
                setlocale(LC_ALL, "Portuguese");
                setPosition(2, 3);
                printf("OPERA��O CANCELADA COM SUCESSO!");
                setlocale(LC_ALL, "C");
                getch();
                ajustes();
                break;
            default:
                confirmarNovaSenha[ctecla] = ch;
                putch('*');
                ctecla++;
                break;
            }
        }

        while(1)
        {
            if(strcmp(senhaAtual, dados.senha) != 0)   //Se a senha atual n�o for igual a do usu�rio
            {
                setPosition(18, 3);
                setlocale(LC_ALL, "Portuguese");
                printf("ERRO: SENHA ATUAL N�O CORRESPONDE COM A SENHA DO USU�RIO!");
                setlocale(LC_ALL, "C");
                if (pergunta("Continuar opera��o?", 1, 51) == 1)
                {

                    limparPergunta(1, 51);

                    limparLinha(18);
                    setPosition(6, 4);
                    for (i = 1; i <= 45; i++)
                    {
                        printf(" ");    //Limpando input da senha atual
                    }

                    memset(senhaAtual, '\0', sizeof(senhaAtual));

                    ctecla = 0;
                    ch = '\0';
                    setPosition(6, 4);
                    while(ctecla<45)
                    {
                        ch = getch();

                        switch(ch)
                        {
                        case BACKSPACE:
                            if(ctecla>0)
                            {
                                fflush(stdin);
                                putch(BACKSPACE);
                                ch = '\0';
                                senhaAtual[ctecla-1] = ch;
                                ctecla--;
                                putch(SPACE);
                                putch(BACKSPACE);
                            }
                            break;
                        case TAB:
                            putch(TAB);
                            ctecla = 50;
                            break;
                        case ENTER:
                            putch(ENTER);
                            ctecla = 50;
                            break;
                        case ESC:
                            cls();
                            setlocale(LC_ALL, "Portuguese");
                            setPosition(2, 3);
                            printf("OPERA��O CANCELADA COM SUCESSO!");
                            setlocale(LC_ALL, "C");
                            getch();
                            ajustes();
                            break;
                        default:
                            senhaAtual[ctecla] = ch;
                            putch('*');
                            ctecla++;
                            break;
                        }
                    }
                }
                else
                {
                    cls();
                    setlocale(LC_ALL, "Portuguese");
                    setPosition(2, 3);
                    printf("REDEFINI��O DE SENHA CANCELADA COM SUCESSO!");
                    setlocale(LC_ALL, "C");
                    getch();
                    ajustes();
                }
            }
            else if(strlen(novaSenha) < 8)     //Se a nova senha conter menos que 8 caracteres
            {

                setPosition(18, 3);
                setlocale(LC_ALL, "Portuguese");
                printf("ERRO: A NOVA SENHA DEVE CONTER NO M�NIMO 8 CARACTERES!");
                setlocale(LC_ALL, "C");

                if (pergunta("Continuar opera��o?", 1, 51) == 1)
                {

                    limparPergunta(1, 51);

                    limparLinha(18);
                    setPosition(10, 4);
                    for (i = 1; i <= 45; i++)
                    {
                        printf(" ");    //Limpando input da nova sesnha
                    }
                    setPosition(14, 4);
                    for (i = 1; i <= 45; i++)
                    {
                        printf(" ");    //Limpando input da confirma��o de nova senha
                    }


                    memset(novaSenha, '\0', sizeof(novaSenha));
                    memset(confirmarNovaSenha, '\0', sizeof(confirmarNovaSenha));

                    setPosition(10, 4);

                    ctecla = 0;
                    ch = '\0';

                    while(ctecla<45)
                    {
                        ch = getch();

                        switch(ch)
                        {
                        case BACKSPACE:
                            if(ctecla>0)
                            {
                                fflush(stdin);
                                putch(BACKSPACE);
                                ch = '\0';
                                novaSenha[ctecla-1] = ch;
                                ctecla--;
                                putch(SPACE);
                                putch(BACKSPACE);
                            }
                            break;
                        case TAB:
                            putch(TAB);
                            ctecla = 50;
                            break;
                        case ENTER:
                            putch(ENTER);
                            ctecla = 50;
                            break;
                        case ESC:
                            cls();
                            setlocale(LC_ALL, "Portuguese");
                            setPosition(2, 3);
                            printf("OPERA��O CANCELADA COM SUCESSO!");
                            setlocale(LC_ALL, "C");
                            getch();
                            ajustes();
                            break;
                        default:
                            novaSenha[ctecla] = ch;
                            putch('*');
                            ctecla++;
                            break;
                        }
                    }

                    setPosition(14, 4);
                    ctecla = 0;
                    ch = '\0';

                    while(ctecla<45)
                    {
                        ch = getch();

                        switch(ch)
                        {
                        case BACKSPACE:
                            if(ctecla>0)
                            {
                                fflush(stdin);
                                putch(BACKSPACE);
                                ch = '\0';
                                confirmarNovaSenha[ctecla-1] = ch;
                                ctecla--;
                                putch(SPACE);
                                putch(BACKSPACE);
                            }
                            break;
                        case TAB:
                            putch(TAB);
                            ctecla = 50;
                            break;
                        case ENTER:
                            putch(ENTER);
                            ctecla = 50;
                            break;
                        case ESC:
                            cls();
                            setlocale(LC_ALL, "Portuguese");
                            setPosition(2, 3);
                            printf("OPERA��O CANCELADA COM SUCESSO!");
                            setlocale(LC_ALL, "C");
                            getch();
                            ajustes();
                            break;
                        default:
                            confirmarNovaSenha[ctecla] = ch;
                            putch('*');
                            ctecla++;
                            break;
                        }
                    }

                }
                else
                {
                    cls();
                    setlocale(LC_ALL, "Portuguese");
                    setPosition(2, 3);
                    printf("REDEFINI��O DE SENHA CANCELADA COM SUCESSO!");
                    setlocale(LC_ALL, "C");
                    getch();
                    ajustes();
                }

            }
            else if (strcmp(novaSenha, confirmarNovaSenha) != 0)
            {

                setPosition(18, 3);
                setlocale(LC_ALL, "Portuguese");
                printf("ERRO: A NOVA SENHA E A CONFIRMA��O DA NOVA SENHA N�O SE COINCIDEM!");
                setlocale(LC_ALL, "C");

                if (pergunta("Continuar opera��o?", 1, 51) == 1)
                {

                    limparPergunta(1, 51);

                    limparLinha(18);
                    setPosition(10, 4);
                    for (i = 1; i <= 45; i++)
                    {
                        printf(" ");    //Limpando input da nova sesnha
                    }
                    setPosition(14, 4);
                    for (i = 1; i <= 45; i++)
                    {
                        printf(" ");    //Limpando input da confirma��o de nova senha
                    }

                    memset(novaSenha, '\0', sizeof(novaSenha));
                    memset(confirmarNovaSenha, '\0', sizeof(confirmarNovaSenha));

                    setPosition(10, 4);

                    ctecla = 0;
                    ch = '\0';

                    while(ctecla<45)
                    {
                        ch = getch();

                        switch(ch)
                        {
                        case BACKSPACE:
                            if(ctecla>0)
                            {
                                fflush(stdin);
                                putch(BACKSPACE);
                                ch = '\0';
                                novaSenha[ctecla-1] = ch;
                                ctecla--;
                                putch(SPACE);
                                putch(BACKSPACE);
                            }
                            break;
                        case TAB:
                            putch(TAB);
                            ctecla = 50;
                            break;
                        case ENTER:
                            putch(ENTER);
                            ctecla = 50;
                            break;
                        case ESC:
                            cls();
                            setlocale(LC_ALL, "Portuguese");
                            setPosition(2, 3);
                            printf("OPERA��O CANCELADA COM SUCESSO!");
                            setlocale(LC_ALL, "C");
                            getch();
                            ajustes();
                            break;
                        default:
                            novaSenha[ctecla] = ch;
                            putch('*');
                            ctecla++;
                            break;
                        }
                    }

                    setPosition(14, 4);
                    ctecla = 0;
                    ch = '\0';

                    while(ctecla<45)
                    {
                        ch = getch();

                        switch(ch)
                        {
                        case BACKSPACE:
                            if(ctecla>0)
                            {
                                fflush(stdin);
                                putch(BACKSPACE);
                                ch = '\0';
                                confirmarNovaSenha[ctecla-1] = ch;
                                ctecla--;
                                putch(SPACE);
                                putch(BACKSPACE);
                            }
                            break;
                        case TAB:
                            putch(TAB);
                            ctecla = 50;
                            break;
                        case ENTER:
                            putch(ENTER);
                            ctecla = 50;
                            break;
                        case ESC:
                            cls();
                            setlocale(LC_ALL, "Portuguese");
                            setPosition(2, 3);
                            printf("OPERA��O CANCELADA COM SUCESSO!");
                            setlocale(LC_ALL, "C");
                            getch();
                            ajustes();
                            break;
                        default:
                            confirmarNovaSenha[ctecla] = ch;
                            putch('*');
                            ctecla++;
                            break;
                        }
                    }

                }
                else
                {
                    cls();
                    setlocale(LC_ALL, "Portuguese");
                    setPosition(2, 3);
                    printf("REDEFINI��O DE SENHA CANCELADA COM SUCESSO!");
                    setlocale(LC_ALL, "C");
                    getch();
                    ajustes();
                }

            }
            else     //Confirma��o de altera��o do usu�rio
            {

                if (pergunta("Confirma altera��o?", 1, 51) == 1)
                {

                    //Alterando a senha pelo arquivo texto
                    FILE *fileTemp;

                    char leitor[100];
                    char analisador[100];

                    memset(leitor, '\0', sizeof(leitor));
                    memset(analisador, '\0', sizeof(analisador));

                    strcat(analisador, dados.usuario);
                    strcat(analisador, " ");
                    strcat(analisador, dados.senha);
                    strcat(analisador, " ");
                    strcat(analisador, tema.fundo);
                    strcat(analisador, tema.texto);
                    strcat(analisador, "\n");

                    file = fopen("./Users/us.txt", "r");
                    fileTemp = fopen("./Users/usTemp.txt", "w");
                    while(fgets(leitor, 100, file) != NULL)
                    {
                        if(strcmp(leitor, analisador) == 0)
                        {
                            fprintf(fileTemp, "%s %s %s%s\n", dados.usuario, novaSenha, tema.fundo, tema.texto);
                        }
                        else
                        {
                            fprintf(fileTemp, leitor);
                        }
                    }

                    memset(leitor, '\0', sizeof(leitor));
                    fclose(file);
                    fclose(fileTemp);

                    remove("./Users/us.txt");
                    rename("./Users/usTemp.txt", "./Users/us.txt");

                    memset(dados.senha, '\0', sizeof(dados.senha));
                    strcpy(dados.senha, novaSenha);

                    cls();
                    setPosition(2, 3);
                    printf("SENHA REDEFINIDA COM SUCESSO!");
                    getch();
                    ajustes();

                }
                else
                {
                    cls();
                    setlocale(LC_ALL, "Portuguese");
                    setPosition(2, 3);
                    printf("REDEFINI��O DE SENHA CANCELADA COM SUCESSO!");
                    setlocale(LC_ALL, "C");
                    getch();
                    ajustes();
                }
            }

        }
    }
}

void redefinirTema()
{

    cls();

    char fundoTemp = '\0';
    char textoTemp = '\0';
    char temaTemp[10];
    char leitor[100];
    char analisador[100];

    FILE *fileTemp;

    memset(temaTemp, '\0', sizeof(temaTemp));
    memset(leitor, '\0', sizeof(leitor));
    memset(analisador, '\0', sizeof(analisador));

    strcat(analisador, dados.usuario);
    strcat(analisador, " ");
    strcat(analisador, dados.senha);

    if(strcmp(ADMIN, analisador) != 0)
    {
        strcat(analisador, " ");
        strcat(analisador, tema.fundo);
        strcat(analisador, tema.texto);
        strcat(analisador, "\n");
    }

    strcat(temaTemp, "color ");

    //Montando as bordas da tela de redefini��o de tema
    createBox(1, 2, 3, 22);
    setPosition(2, 5);
    printf("REDEFINIR TEMA");
    createBox(3, 2, 7, 22);
    setPosition(3, 2);
    printf("%c", 195);
    setPosition(3, 22);
    printf("%c", 180);

    setPosition(5, 3);
    printf("Fundo:");
    createBox(4, 9, 6, 11);

    setPosition(5, 13);
    printf("Texto:");
    createBox(4, 19, 6, 21);

    //Montando tabela de cores
    createBox(1, 23, 3, 62);
    setPosition(2, 35);
    printf("TABELA DE CORES");
    createBox(3, 23, 12, 62);
    setPosition(3, 23);
    printf("%c", 195);
    setPosition(3, 62);
    printf("%c", 180);

    int i;
    for(i = 4; i < 12; i++)
    {
        setPosition(i, 39);
        printf("%c", 179);
    }
    setPosition(3, 39);
    printf("%c", 194);
    setPosition(12, 39);
    printf("%c", 193);

    setlocale(LC_ALL, "Portuguese");
    setPosition(4, 24);
    printf("0 = Preto");
    setPosition(5, 24);
    printf("1 = Azul");
    setPosition(6, 24);
    printf("2 = Verde");
    setPosition(7, 24);
    printf("3 = Verde-�gua");
    setPosition(8, 24);
    printf("4 = Vermelho");
    setPosition(9, 24);
    printf("5 = Roxo");
    setPosition(10, 24);
    printf("6 = Amarelo");
    setPosition(11, 24);
    printf("7 = Branco");
    setPosition(4, 41);
    printf("8 = Cinza");
    setPosition(5, 41);
    printf("9 = Azul claro");
    setPosition(6, 41);
    printf("A = Verde claro");
    setPosition(7, 41);
    printf("B = Verde-�gua claro");
    setPosition(8, 41);
    printf("C = Vermelho claro");
    setPosition(9, 41);
    printf("D = Lil�s");
    setPosition(10, 41);
    printf("E = Amarelo claro");
    setPosition(11, 41);
    printf("F = Branco brilhante");
    setlocale(LC_ALL, "C");

    if(strcmp(ADMIN, analisador) == 0)
    {
        createBox(13, 2, 16, 67);
        setlocale(LC_ALL, "Portuguese");
        setPosition(14, 4);
        printf("AVISO: O ADMINISTRADOR APENAS REDEFINAR� O TEMA TEMPORIAMENTE,");
        setPosition(15, 11);
        printf("AP�S O ENCERRAMENTO DA SESS�O VOLTAR� A COR PADR�O!");
        setlocale(LC_ALL, "C");
    }

    char ch = '\0';
    int tecla = 0;

    while(tecla < 1)
    {
        setPosition(5,10);
        ch = getch();

        if (ch == ESC)
        {
            cls();
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("OPERA��O CANCELADA COM SUCESSO!");
            setlocale(LC_ALL, "C");
            getch();
            ajustes();
            break;
        }
        if((ch == '0') || (ch == '1') || (ch == '2') || (ch == '3') || (ch == '4') || (ch == '5') || (ch == '6') || (ch == '7') || (ch == '8')  || (ch == '9') || (ch == 'a') || (ch == 'A') || (ch == 'b') || (ch == 'B') || (ch == 'c') || (ch == 'C') || (ch == 'd') || (ch == 'D') || (ch == 'e') || (ch == 'E') || (ch == 'f') || (ch == 'F'))
        {
            putchar(ch);
            setPosition(5, 10);
            fundoTemp = ch;
            tecla++;
        }
    }

    ch = '\0';
    tecla = 0;

    while(tecla < 1)
    {
        setPosition(5,20);
        ch = getch();
        if (ch == ESC)
        {
            cls();
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("OPERA��O CANCELADA COM SUCESSO!");
            setlocale(LC_ALL, "C");
            getch();
            ajustes();
            break;
        }
        if((ch == '0') || (ch == '1') || (ch == '2') || (ch == '3') || (ch == '4') || (ch == '5') || (ch == '6') || (ch == '7') || (ch == '8')  || (ch == '9') || (ch == 'a') || (ch == 'A') || (ch == 'b') || (ch == 'B') || (ch == 'c') || (ch == 'C') || (ch == 'd') || (ch == 'D') || (ch == 'e') || (ch == 'E') || (ch == 'f') || (ch == 'F'))
        {
            putchar(ch);
            setPosition(5, 10);
            textoTemp = ch;
            tecla++;
        }
    }

    temaTemp[6] = fundoTemp;
    temaTemp[7]= textoTemp;

    strupr(&fundoTemp);
    strupr(&textoTemp);

    if(fundoTemp == textoTemp)
    {
        setlocale(LC_ALL, "Portuguese");
        if(strcmp(ADMIN, analisador) == 0)
        {
            limparLinha(13);
            limparLinha(14);
            limparLinha(15);
            limparLinha(16);
        }
        setPosition(14, 3);
        printf("ERRO: COR DE FUNDO N�O PODE SER IGUAL � COR DE TEXTO!");
        setlocale(LC_ALL, "C");
        if (pergunta("Continuar opera��o?", 1, 63) == 1)
        {
            redefinirTema();
        }
        else
        {
            cls();
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("REDEFINI��O DE TEMA CANCELADO COM SUCESSO!");
            setlocale(LC_ALL, "C");
            getch();
            ajustes();
        }
    }
    else
    {
        system(temaTemp);
        if(pergunta("Confirma altera��o?", 1, 63) == 1)
        {
            if(strcmp(ADMIN, analisador) != 0)   //Se n�o for o administrador
            {
                tema.fundo[0] = fundoTemp;
                tema.texto[0] = textoTemp;

                fileTemp = fopen("./Users/usTemp.txt", "w");
                file = fopen("./Users/us.txt", "r");

                while(fgets(leitor, 100, file) != NULL)
                {
                    if(strcmp(leitor, analisador) == 0)
                    {
                        fprintf(fileTemp, "%s %s %c%c\n", dados.usuario, dados.senha, fundoTemp, textoTemp);
                    }
                    else
                    {
                        fprintf(fileTemp, "%s", leitor);
                    }

                    memset(leitor, '\0', sizeof(leitor));
                }

                fclose(fileTemp);
                fclose(file);

                remove("./Users/us.txt");
                rename("./Users/usTemp.txt", "./Users/us.txt");
            }

            strcpy(tema.tema, temaTemp);
            cls();
            setPosition(2, 3);
            printf("TEMA REDEFINIDO COM SUCESSO");
            getch();
            ajustes();
        }
        else
        {
            system(tema.tema);
            cls();
            setlocale(LC_ALL, "Portuguese");
            setPosition(2, 3);
            printf("REDEFINI��O DE TEMA CANCELADO COM SUCESSO!");
            setlocale(LC_ALL, "C");
            getch();
            ajustes();
        }
    }
}

