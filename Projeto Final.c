#include <stdio.h>
#include <string.h>

#define MAX 100     
#define MAX_DESC 50 

char descricao[MAX][MAX_DESC]; 
float valor[MAX];              
int tipo[MAX];
int mes[MAX];                 
int totalLancamentos = 0;

void clear() {
    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
}

void adicionarReceita() {
    if (totalLancamentos < MAX) {
        float v;
        int m;
        printf("Digite 0 no valor para cancelar.\n");

        printf("Mês da receita (1 à 12): ");
        scanf("%d", &m);
        if (m == 0) {
            printf("Operacao cancelada.\n");
            return;
        } else if (m > 12) {
            printf("Mês Inválido!");
            return;
        }

        printf("Valor da receita: ");
        scanf("%f", &v);
        if (v == 0) {
            printf("Operacao cancelada.\n");
            return;
        }

        getchar();
        printf("Descricao da receita: ");
        fgets(descricao[totalLancamentos], MAX_DESC, stdin);
        descricao[totalLancamentos][strcspn(descricao[totalLancamentos], "\n")] = '\0';

        mes[totalLancamentos] = m;
        valor[totalLancamentos] = v;
        tipo[totalLancamentos] = 1;
        totalLancamentos++;

        printf("Receita registrada!\n");
    } else {
        printf("Limite de lancamentos atingido!\n");
    }
}

void adicionarDespesa() {
    if (totalLancamentos < MAX) {
        float v;
        int m;
        printf("Digite 0 no valor para cancelar.\n");

        printf("Mês da despesa (1 à 12): ");
        scanf("%d", &m);
        if (m == 0) {
            printf("Operacao cancelada.\n");
            return;
        } else if (m > 12) {
            printf("Mês Inválido!");
            return;
        }
        printf("Valor da despesa: ");
        scanf("%f", &v);
        if (v == 0) {
            printf("Operacao cancelada.\n");
            return;
        }

        getchar();
        printf("Descricao da despesa: ");
        fgets(descricao[totalLancamentos], MAX_DESC, stdin);
        descricao[totalLancamentos][strcspn(descricao[totalLancamentos], "\n")] = '\0';

        mes[totalLancamentos] = m;
        valor[totalLancamentos] = v;
        tipo[totalLancamentos] = 2;
        totalLancamentos++;

        printf("Despesa registrada!\n");
    } else {
        printf("Limite de lancamentos atingido!\n");
    }
}

int listarLancamentosPorMes(int m, int indices[]) {
    float saldo = 0;
    int counter = 1;
    int total = 0;

    clear();
    printf("\n===== LANCAMENTOS DO MES %d =====\n", m);

    for (int i = 0; i < totalLancamentos; i++) {
        if (tipo[i] == 1 && mes[i] == m) {
            printf("%d - Receita: %s | \033[0;32mR$ %.2f\033[0m\n", counter, descricao[i], valor[i]);
            saldo += valor[i];
            indices[total] = i;  
            counter++;
            total++;
        }
    }

    for (int i = 0; i < totalLancamentos; i++) {
        if (tipo[i] == 2 && mes[i] == m) {
            printf("%d - Despesa: %s | \033[0;31mR$ %.2f\033[0m\n", counter, descricao[i], valor[i]);
            saldo -= valor[i];
            indices[total] = i;  
            counter++;
            total++;
        }
    }

    printf("------------------------------\n");

    if (saldo >= 0)
        printf("Saldo atual: \033[0;32mR$ %.2f\033[0m\n", saldo);
    else
        printf("Saldo atual: \033[0;31mR$ %.2f\033[0m\n", saldo);

    return total; // retorna quantos lançamentos foram listados
}

void listarLancamentos() {
    int m;
    printf("\n1 - Janeiro \t2 - Fevereiro \n3 - Março \t4 - Abril \n5 - Maio \t6 - Junho \n7 - Julho \t8 - Agosto \n9 - Setembro \t10 - Outubro \n11 - Novembro \t12 - Dezembro");
    printf("\nDigite 0 para cancelar.\n");
    printf("Selecione o mês: ");
    scanf("%d", &m);

    if (m == 0) {
        printf("\nOperacao cancelada.\n");
        return;
    } else if (m > 12) {
        printf("\nMês Inválido!");
        return;
    }

    int indices[MAX];
    listarLancamentosPorMes(m, indices);
}

void excluirLancamentos() {
    if (totalLancamentos == 0) {
        printf("Nao ha lancamentos para excluir.\n");
        return;
    }

    int m;
    printf("\nDigite o mês (1 a 12, ou 0 para cancelar): ");
    scanf("%d", &m);

    if (m == 0) {
        printf("Operacao cancelada.\n");
        return;
    }
    if (m < 1 || m > 12) {
        printf("Mes invalido.\n");
        return;
    }

    int indices[MAX]; 
    int total = listarLancamentosPorMes(m, indices);

    if (total == 0) {
        printf("\nNao ha lancamentos nesse mes.\n");
        return;
    }

    int x;
    printf("------------------------------\n");
    printf("Selecione o lancamento para excluir (1 a %d, ou 0 para cancelar): ", total);
    scanf("%d", &x);

    if (x == 0) {
        printf("Operacao cancelada.\n");
        return;
    }

    if (x < 1 || x > total) {
        printf("Indice invalido.\n");
        return;
    }

    int idxReal = indices[x - 1]; // índice real

    for (int i = idxReal; i < totalLancamentos - 1; i++) {
        strcpy(descricao[i], descricao[i + 1]);
        mes[i] = mes[i + 1];
        valor[i] = valor[i + 1];
        tipo[i] = tipo[i + 1];
    }

    totalLancamentos--;
    printf("\nLancamento excluido!\n");
}

void listarSaldoTotal() {
    float saldo = 0;
    clear();
    printf("\n===== SALDO TOTAL DO ANO =====\n");

    for (int i = 0; i < totalLancamentos; i++) {
        if (tipo[i] == 1) {
            printf("Receita (%02d): %-20s | \033[0;32mR$ %.2f\033[0m\n",
                   mes[i], descricao[i], valor[i]);
            saldo += valor[i];
        }
    }

    for (int i = 0; i < totalLancamentos; i++) {
        if (tipo[i] == 2) {
            printf("Despesa (%02d): %-20s | \033[0;31mR$ %.2f\033[0m\n",
                   mes[i], descricao[i], valor[i]);
            saldo -= valor[i];
        }
    }

    printf("------------------------------\n");
    if (saldo >= 0)
        printf("Saldo TOTAL do ano: \033[0;32mR$ %.2f\033[0m\n", saldo);
    else
        printf("Saldo TOTAL do ano: \033[0;31mR$ %.2f\033[0m\n", saldo);
}

int main() {
    int opcao;

    do {
        printf("\n===== CONTROLE DE FINANCAS =====\n");
        printf("1 - Adicionar Receita\n");
        printf("2 - Adicionar Despesa\n");
        printf("3 - Listar Lancamentos e Saldo\n");
        printf("4 - Excluir Lancamentos\n");
        printf("5 - Listar Saldo TOTAL do Ano\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                clear();
                adicionarReceita();
                break;
            case 2:
                clear();
                adicionarDespesa();
                break;
            case 3:
                clear();
                listarLancamentos();
                break;
            case 4:
                clear();
                excluirLancamentos();
                break;
            case 5:
                clear();
                listarSaldoTotal();
                break;
            case 0:
                clear();
                printf("Encerrando o programa...\n");
                break;
            default:
                clear();
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
