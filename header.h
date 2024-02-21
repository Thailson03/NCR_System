#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#define ADMIN "ADMIN @NCRadmin"

//Teclas da tabela ASCII
#define ENTER 13    // CÓDIGO ASCII DA TECLA ENTER
#define BACKSPACE 8 // CÓDIGO ASCII DA TECLA BACKSPACE
#define SPACE 32    // CÓDIGO ASCII DA TECLA BARRA DE ESPACO
#define TAB 9       // CÓDIGO ASCII DA TECLA BACKSPACE
#define ESC 27      // CÓDIGO ASCII DA TECLA ESC

//ESTRUTURAS
struct LOGIN //Estrutura que guarda o usuario e senha
{
    char usuario[50];
    char senha[50];
};

struct TEMA //Estrutura que recupera o tema do usuário
{
    char fundo[2];
    char texto[2];
    char tema[10];
};

struct FUNCIONARIO
{
    unsigned long int id;
    char nome[51];
    char funcao[51];
    char data_de_nascimento[11];
    double salario;
    char cargo[7];
    char data_de_inicio[11];
    char situacao[10];
};

struct CLIENTE
{
    unsigned long int id;
    char nome[51];
    char tipo_pessoa[9];
    char telefone[51];
    char email[51];
    double faturamento;
    double despesas;
    double saldo;

};

//VARIÁVEIS GLOBAIS
struct LOGIN dados; //Variável struct que armazena o usuario e senha inserido pelo usuário

struct TEMA tema; //Variável struct que recupera o tema do usuário

struct FUNCIONARIO funcionario; //Váriavel struct que armazena dados do funcionário

struct CLIENTE cliente; //Váriavel struct que armazena dados do cliente

char horario[50]; //Variável que armazenará o dia da semana atual - data atual - horario atual com a função getTime(horario);

char mensagem[255]; //Váriavel que armazenará a mensagem para o registro de log

//FUNÇÕES AUXILIARES
void cls(void); // Limpar tela

void setColor(int color); //Muda a cor das próximas impressões

void setPosition(int linha, int coluna); //Posiciona o local do ponteiro do console

void createBox( int linha1, int coluna1, int linha2, int coluna2); //Cria uma caixinha

void getTime(char *str); //Armazena o dia da semana atual - data atual - horario atual em uma String

int pergunta(char pergunta[40], int linha, int coluna); //Abre uma caixinha de pergunta com sim ounão para o usuário

void limparPergunta(int linha, int coluna);

void limparLinha(int linha); //Limpa a informação de uma linha (Muito usado na linha de ERRO);

void registrarNoLog(char mensagem[255]);

//FUNÇÕES UTILIZADAS NA FUNÇÃO PRINCIPAL
void tutorial();
void tutorialAdmin ();
struct LOGIN login(struct LOGIN *dados);
void saudacao();
void menuPrincipal();

//FUNÇÕES UTILIZADAS NO MENU PRINCIPAL
void gerenciarFuncionarios();
void gerenciarClientes();
void gerenciarUsuarios();
void registrosDeLog();
void sobreNCRSystem();
void ajustes();

//GERENCIAR FUNCIONÁRIOS
void cadastrarFuncionario();
void removerFuncionario();
void listarFuncionarios();
void ativarDesligarFuncionario();
void relatorioFuncionario();

//GERENCIAR CLIENTES
void cadastrarClientes();
void removerClientes();
void listarClientes();
void relatorioCliente();
void modificarCliente();
void modificarClienteAtivo();
void modificarClientePassivo();

//GERENCIAR USUÁRIOS
void cadastrarUsuario();
void removerUsuario();
void listarUsuarios();

//REGISTRO DE LOG
void lerRegistros();
void limparRegistro();

//AJUSTES
void redefinirSenha();
void redefinirTema();

#endif // HEADER_H_INCLUDED
