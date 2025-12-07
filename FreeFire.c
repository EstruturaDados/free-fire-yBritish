#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constantes Globais ---   
#define TAM_NOME 30
#define TAM_TIPO 10
#define TAM_MOCHILA 10

// --- Struct ---
typedef struct No{
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
    struct No* proximo;
}Item;

// Função que limpa após scanf
void Limpascanf(){
    while (getchar() != '\n'); // Limpa o buffer APÓS o scanf("%d") para garantir que o input do próximo ciclo seja lido corretamente
}

void ListarItens(Item *Armazenamento){
   Item* atual = Armazenamento;
   // Verificação se a lista está vazia
   if (atual == NULL){
        printf("A mochila esta vazia.\n");
        return ;
   }
   int contador = 1;
   printf("========= Mochila =========\n");
   // Enquanto o item atual não for NULL, ele imprime o atual e atualiza para o proximo.
   while(atual != NULL){
        printf("%d° Item : Nome:%s // Tipo:%s // Quantidade:%d\n", contador, atual -> nome, atual -> tipo, atual ->quantidade);// continuar a função de exibir a mochila
        atual = atual -> proximo;
        // Apenas estético para ficar mais bonito
        contador += 1;
        
    }
    printf("===============================\n");
}

// Função que insere no final da lista
void InserirItem(Item ** Insercao){
    // Alocação de memória com malloc no ponteiro "novo".
    Item* novo = (Item *) malloc(sizeof(Item));
    // Apenas uma medida de segurança para alertar algum problema de alocação.
    if (novo == NULL) {
        printf("Erro ao alocar memória para o novo item.\n");
        return;
    }
    // Isso limpa o cache do scanf %d 
    Limpascanf();
    // Aqui é a fase do usuário digitar os elementos
    printf("Qual item deseja adicionar: ");
    fgets(novo -> nome, TAM_NOME, stdin);
    novo -> nome[strcspn(novo -> nome, "\n")] = '\0';

    printf("Qual tipo de item deseja adicionar: ");
    fgets(novo->tipo, TAM_TIPO,stdin);
    novo->tipo[strcspn(novo -> tipo, "\n")] = '\0';

    printf("Qual quantidade deste item deseja adicionar: ");
    scanf("%d", &novo -> quantidade);
    
    // Isso é para fazer a lista ser crescente, com o próximo elemento apontando para o final da lista.
    novo -> proximo = NULL;
    // Adicionando o elemento na posição 0 da lista
    if (*Insercao == NULL){
        *Insercao = novo;
        printf("Item adicionado com sucesso! \n");
        return;
    }
    // Aqui terá inicio ao loop para encontrar o último nó
    Item* atual = *Insercao;
    while(atual -> proximo != NULL){
        atual = atual -> proximo;
    }
    // Aqui coloca o último nó no seu lugar
    atual -> proximo = novo;
    printf("Item adicionado com sucesso! \n");
  
}

void RemoverItem(Item ** Remover,char *Nome){
    // Aqui tem a declaração de 2 ponteiros "atual" e "anterior".
    // Eles permitem a sobreposição do elemento digitado no char nome, a técnica de remoção se baseia em ignorar o elemento que vai ser removido.
    Item* atual = *Remover;
    Item* anterior = NULL;
    // Aqui inicia um loop que verifica todos os elementos da lista.
    while(atual != NULL){
        // Aqui é um if que compara o ponteiro.nome analisado com o parâmetro do elemento a ser retirado.
        if(strcmp(atual -> nome, Nome) == 0){
            break;
        }
        // Parte importante: Aqui permite que o "anterior" sempre seja atualizado para o elemento analisado pelo strcmp.
        anterior = atual;
        // e o "atual" seja atualizado para o proximo elemento da lista.
        atual = atual -> proximo;
        }
    // Fora do loop: Se chegar no final da lista e não encontrar o elemento, imprime uma mensagem de erro e sai da função.
    if (atual == NULL){
        printf("O item não foi encontrado!\n");
        return;
        }
    // Isso aqui só é executado se o elemento a ser removido estiver no início da lista.
    if(anterior == NULL){
        // Parte crucial: Atual é descartado, fazendo com que a lista inicie no próximo elemento.
        *Remover = atual -> proximo;
    } else{
        // Parte crucial: Aqui é executado se o elemento a ser removido estiver no meio ou final da lista.
        // O anterior que aponta para o proximo (que seria o atual) passa a apontar diretamente para o ponteiro antes apontado pelo atual, assim descartando atual.
        anterior -> proximo = atual -> proximo;
    }
    printf("O item %s foi removido com sucesso!\n", atual -> nome);
    // Aqui desaloca a memória do elemento removido.
    free(atual);    
}

Item* BuscarItem(Item *Procura, char *nome_em_procura){
    Item *atual = Procura;
    // Aqui segue um padrão semelhante a remoção de itens.
    // Aqui tem um loop que percorre todos os ponteiros da lista.
    while (atual != NULL){
        // Comparação do item atual e o item procurado.
        if (strcmp(atual -> nome, nome_em_procura) == 0){
            // Retorna o ponteiro atual
            return atual;
        }
        // Atualiza o atual para o próximo a ser analisado
        atual = atual -> proximo; 
    }
    // Retorna nada quando o elemento não está na lista
    printf("Erro: Item não encontrado na lista.\n");
    return NULL;
}
int main(){
    // Declaração do inventário
    Item *Inventario = NULL;

    int total_itens = 0;
    int opcao;
    int Qtd_Itens;
    char escolha[TAM_NOME];
    do{
        // MENU INTERATIVO
        printf("Inventário\n");
        printf("0. Buscar item\n");
        printf("1. Adicionar item \n");
        printf("2. Remover item \n");
        printf("3. Sair\n");
        scanf("%d", &opcao);
        Limpascanf();

        switch (opcao)
        {
        case 0:
        // Apenas uma verificação de segurança para quebrar o case antes de executar o resto se a lista estiver vazia.
        if(total_itens == 0){
            printf("A mochila está vazia.");
            break;
        }
        // Aqui coleta os dados do usuário.
        printf("Digite o nome do item que deseja buscar separadamente: ");
        fgets(escolha, TAM_NOME, stdin);
        escolha[strcspn(escolha, "\n")] = '\0';

        // Armazena no ponteiro "item_encontrado" o valor retornado na função.
        Item* item_encontrado = BuscarItem(Inventario, escolha);
        // Se o item for encontrado na lista, imprime os dados armazenados.
        if (item_encontrado != NULL){
            printf("\n ===== ITEM ENCONTRADO =====\n");
            printf("Nome: %s\n", item_encontrado -> nome);
            printf("Tipo: %s\n", item_encontrado -> tipo);
            printf("Quantidade: %d\n", item_encontrado -> quantidade);
            printf("===============================\n");
        } else{
            printf("O nome não foi encontrado!\n");
        }

        break;

        case 1:
            // Aqui pede a quantidade de itens a ser adicionado.
            printf("Quantos itens deseja adicionar: ");
            scanf("%d", &Qtd_Itens);
            // Verificação se a quantidade de itens a ser adicionado extrapole o tamanho da mochila.
            if((total_itens + Qtd_Itens) > 10){
                printf("Sua mochila está cheia!");
                break;
            }

            // Loop que chama a função a quantidade de vezes q o usuário deseja
            for(int i = 0; i < Qtd_Itens; i++){
                InserirItem(&Inventario);
                total_itens += 1;
            } 
            // Apenas para o usuário ficar ciente do espaço já ocupado na mochila.
            printf("Há um total de %d itens na sua mochila\n", total_itens);
            ListarItens(Inventario);

            break;
        case 2:
            // Verifica se a mochila está vazia para não executar o resto do case.
            if(total_itens == 0){
            printf("A mochila está vazia.");
            break;
            }

            printf("Digite o nome do item que deseja remover: ");
            scanf("%s", escolha);
            RemoverItem(&Inventario, escolha);
            total_itens -= 1;
            ListarItens(Inventario);
            printf("Há um total de %d itens na sua mochila\n", total_itens);
            
        default:
            
            break;
        }

    } while(opcao != 3);
    ListarItens(Inventario);
    // Limpa a alocação de memória alocado.
    free(Inventario);
}