//ARQUIVOS DE CABE�ALHO
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"
#include "windows.h"
#include "locale.h"
#include "time.h"

#include "header.h"
#include "resource.h"


//FUN��O PRINCIPAL (PROGRAMA)
int main(){
    tutorial();
    login(&dados);
    saudacao();
    tutorialAdmin();
    menuPrincipal();
}
