#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <direct.h>


int lista;

FILE *fp;
FILE *fc;

typedef struct
{
    char login[15];
    char senha[15];
}

pessoa; pessoa p[1];

void main()
{
    char login[15] = "admin";
    char login1[15];
    char senha[15] = "admin";
    char senha1[15];

    int login_efetuado = 0;

    while(!login_efetuado)
      {
        printf("Digite o Login: ");
        scanf("%s", login1);

        printf("Digite a Senha: ");
        scanf("%s", senha1);

        if (strcmp(login, login1) == 0 && strcmp(senha, senha1) == 0)
           {
            printf("\n\nAcesso Permitido\n\n");
            printf("\n\nAperte Enter para acessar o Sistema\n\n");
            login_efetuado = 1;
           }

         else
             printf("\n\nAcesso Negado, revise os dados\n\n");
       }

    getch();

    char
        nome[50],
        cpf[14],
        endereco_rua[30],
        endereco_numero[10],
        endereco_bairro[30],
        endereco_cidade[30],
        endereco_uf[4],
        endereco_cep[20],
        email[30],
        telefone[20],
        strIdade[4],
        dataDiagnostico[30],
        comorbidade[30];
    int idade, separaComorbidade;


    do

	{
	    printInfoBase();
        printf("\n\n\nOpcao 1 - Cadastro de Paciente\n");
        printf("\nOpcao 2 - Lista Pacientes Fora do Grupo de Risco\n");
        printf("\nOpcao 3 - Lista Pacientes Grupo de Risco\n");
        printf("\nOpcao 0 - Fechar Sistema\n\n");
        scanf("%d", &lista);
        fflush(stdin);

        switch(lista)
        {
            case 0:;
                printInfoBase();
                printf("\n\n\nSaindo do sistema.\n");
                getch();
                break;

            case 1:;

                bool continuaValido = true;

                struct tm *data_hora_atual;
                time_t segundos;
                time(&segundos);
                data_hora_atual = localtime(&segundos);
                data_hora_atual = localtime(&segundos);
                int diaA = data_hora_atual->tm_mday;
                int mesA = data_hora_atual->tm_mon+1;
                int anoA = data_hora_atual->tm_year+1900;

                printInfoBase();
                fp=fopen("pacientes_geral.txt","a");
                printf("\nDigite o nome completo do paciente: ");
                fgets(nome, 50, stdin);
                fputs(nome,fp);


                if(strlen(nome) == 0)
                    {
                     continuaValido = false;
                    }

                if (continuaValido)
                    {
                      printf("\nDigite o CPF do paciente: ");
                      fgets(cpf, 14, stdin);
                      fputs(cpf,fp);

                     }

                printf("\n Endereço *Rua : ");
                fgets(endereco_rua, 30, stdin);

                printf("\nEndereço *Num: ");
                fgets(endereco_numero, 10, stdin);

                printf("\nEndereco *Bairro: ");
                fgets(endereco_bairro, 50, stdin);

                printf("\nCEP: ");
                fgets(endereco_cep, 50, stdin);

                printf("\nTelefone: ");
                fgets(telefone, 50, stdin);

                printf("\nData de Diagnostico *Padrao (dd/mm/aaaa)*\n");
                fgets(dataDiagnostico,50,stdin);


                int diaN, mesN, anoN, idade;

                printf("\nData de Nascimento: *Padrao (dd/mm/aaaa) *\n");
                scanf("%d/%d/%d", &diaN, &mesN, &anoN);

                if ((mesN > mesA) || ((mesN = mesA) && (diaN > diaA)))

                  {
                   idade = anoA - anoN ;
                   printf("Idade do Paciente: %d", idade);
                  }

                else

                   {
                    idade = anoA - anoN;
                    printf("Idade do Paciente: %d", idade);
                   }


                printf("\nPaciente possui alguma comorbidade? (Sim: 1 / Nao: 2): ");
                scanf("%d",&separaComorbidade);

                if(separaComorbidade == 1) {
                    printf("\nInforme a Comorbidade: ");
                    fgets(comorbidade,30,stdin);
                }

                if((separaComorbidade == 1)||(idade >= 65))

                 {
                   fc=fopen("paciente_positivos.txt","a");
                   fprintf(fc,"Nome; %s",nome);
                   fprintf(fc,"CEP; %s",endereco_cep);
                   fprintf(fc,"Idade; %d\n",idade);
                   fprintf(fc,"Comorbidade; %s \n\n",comorbidade);

                    fclose(fc);

                    printInfoBase();
                    printf("\n\nPaciente Cadastrado com Sucesso!\n");
                    getch();
                }

                else if ((separaComorbidade == 2)||(idade < 65))

                 {
                   fp=fopen("pacientes_geral.txt","a");
                   fprintf(fp,"Nome; %s",nome);
                   fprintf(fp,"CPF; %s",cpf);
                   fprintf(fp,"Bairro; %s",endereco_bairro);
                   fprintf(fp,"CEP; %s",endereco_cep);
                   fprintf(fp,"Telefone; %s",telefone);
                   fprintf(fp,"Idade; %d\n\n",idade);
                   fclose(fp);

                    printInfoBase();
                    printf("\n\n\n *- Paciente Cadastrado com Sucesso!\n *-");
                    getch();

                 }
                   else

                    {
                      printInfoBase();
                      printf("\nFalha no cadastro.\n ");
                      getch();
                    }

                break;

            case 2:
                printInfoBase();

                char ch;
                fp = fopen("pacientes_geral.txt", "r");
                if(fp == NULL)

                {
                    printInfoBase();
                    printf("\nNao foi possivel abrir o arquivo\n");
                    exit(EXIT_FAILURE);
                }

                else do

                {
                   ch = fgetc(fp);
                    putchar(ch);
                }

                while(ch != EOF);


                fclose(fp);


                printf("\n\n\n********************");
                printf("\nFim da pesquisa");
                getch();
                break;


              case 3:
                printInfoBase();

                char ch1;
                fc = fopen("paciente_positivos.txt", "r");
                if(fc == NULL)

                {   printInfoBase();
                    printf("Nao foi possivel abrir o arquivo.\n");
                    exit(EXIT_FAILURE);
                }
                else do
                {
                   ch1 = fgetc(fc);
                    putchar(ch1);
                }
                while(ch1 != EOF);

                fclose(fc);


                printf("\n\n\n*******************");
                printf("\nFim da pesquisa.");
                getch();
                break;

            default:;
                printInfoBase();
                printf("Opcao Invalida\n");
                getch();
                break;
            }
    } while(lista != 0);

    system('cls');
}

void printInfoBase(){
    system("cls");

    printf("\n -*  Sistema de Cadastro - Pacientes COVID-19 *- ");

}
