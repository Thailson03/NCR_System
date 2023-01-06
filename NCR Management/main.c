//ARQUIVOS DE CABEÇALHO
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"
#include "windows.h"
#include "locale.h"
#include "time.h"

#include "header.h"
#include "resource.h"


//FUNÇÃO PRINCIPAL (PROGRAMA)
int main(){
    tutorial();
    login(&dados);
    saudacao();
    tutorialAdmin();
    menuPrincipal();
}
