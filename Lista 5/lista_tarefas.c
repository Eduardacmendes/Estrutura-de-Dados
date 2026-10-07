#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_tarefas.h"

ListaTarefas* cria_lista(){
    ListaTarefas* li = (ListaTarefas*) malloc(sizeof(ListaTarefas));

    if(li != NULL)
        *li = NULL;

    return li;
}

void libera_lista(ListaTarefas* li){
    if(li != NULL){
        Elem* no;

        while(*li != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }

        free(li);
    }
}

int insere_tarefa_inicio(ListaTarefas* li, struct tarefa t){
    if(li == NULL)
        return 0;

    Elem* no = (Elem*) malloc(sizeof(Elem));

    if(no == NULL)
        return 0;

    no->dados = t;
    no->prox = *li;
    *li = no;

    return 1;
}

int insere_tarefa_final(ListaTarefas* li, struct tarefa t){
    if(li == NULL)
        return 0;

    Elem* no = (Elem*) malloc(sizeof(Elem));

    if(no == NULL)
        return 0;

    no->dados = t;
    no->prox = NULL;

    if(*li == NULL){
        *li = no;
    }else{
        Elem* aux = *li;

        while(aux->prox != NULL)
            aux = aux->prox;

        aux->prox = no;
    }

    return 1;
}

int insere_tarefa_ordenada(ListaTarefas* li, struct tarefa t){
    if(li == NULL)
        return 0;

    Elem* no = (Elem*) malloc(sizeof(Elem));

    if(no == NULL)
        return 0;

    no->dados = t;

    if(*li == NULL){
        no->prox = NULL;
        *li = no;
        return 1;
    }

    Elem* ant = NULL;
    Elem* atual = *li;

    while(atual != NULL && atual->dados.prioridade < t.prioridade){
        ant = atual;
        atual = atual->prox;
    }

    if(atual == *li){
        no->prox = *li;
        *li = no;
    }else{
        no->prox = atual;
        ant->prox = no;
    }

    return 1;
}

int remove_tarefa(ListaTarefas* li, int codigo){
    if(li == NULL || *li == NULL)
        return 0;

    Elem* ant = NULL;
    Elem* no = *li;

    while(no != NULL && no->dados.codigo != codigo){
        ant = no;
        no = no->prox;
    }

    if(no == NULL)
        return 0;

    if(ant == NULL)
        *li = no->prox;
    else
        ant->prox = no->prox;

    free(no);
    return 1;
}

int remove_tarefa_inicio(ListaTarefas* li){
    if(li == NULL || *li == NULL)
        return 0;

    Elem* no = *li;
    *li = no->prox;
    free(no);

    return 1;
}

int remove_tarefa_final(ListaTarefas* li){
    if(li == NULL || *li == NULL)
        return 0;

    Elem* ant = NULL;
    Elem* no = *li;

    while(no->prox != NULL){
        ant = no;
        no = no->prox;
    }

    if(ant == NULL)
        *li = NULL;
    else
        ant->prox = NULL;

    free(no);
    return 1;
}

int tamanho_lista(ListaTarefas* li){
    if(li == NULL)
        return -1;

    int cont = 0;
    Elem* no = *li;

    while(no != NULL){
        cont++;
        no = no->prox;
    }

    return cont;
}

int lista_vazia(ListaTarefas* li){
    if(li == NULL)
        return -1;

    return *li == NULL;
}

int lista_cheia(ListaTarefas* li){
    if(li == NULL)
        return -1;

    return 0;
}

int busca_tarefa_cod(ListaTarefas* li, int codigo, struct tarefa *t){
    if(li == NULL || *li == NULL || t == NULL)
        return 0;

    Elem* no = *li;

    while(no != NULL){
        if(no->dados.codigo == codigo){
            *t = no->dados;
            return 1;
        }

        no = no->prox;
    }

    return 0;
}

int busca_tarefa_pos(ListaTarefas* li, int pos, struct tarefa *t){
    if(li == NULL || *li == NULL || t == NULL || pos < 1)
        return 0;

    Elem* no = *li;
    int atual = 1;

    while(no != NULL && atual < pos){
        no = no->prox;
        atual++;
    }

    if(no == NULL)
        return 0;

    *t = no->dados;
    return 1;
}

int conta_tarefas_prioridade(ListaTarefas* li, int prioridade){
    if(li == NULL)
        return -1;

    int cont = 0;
    Elem* no = *li;

    while(no != NULL){
        if(no->dados.prioridade == prioridade)
            cont++;

        no = no->prox;
    }

    return cont;
}

int tarefa_mais_urgente(ListaTarefas* li, struct tarefa *t){
    if(li == NULL || *li == NULL || t == NULL)
        return 0;

    Elem* no = *li;
    *t = no->dados;

    while(no != NULL){
        if(no->dados.prioridade < t->prioridade)
            *t = no->dados;

        no = no->prox;
    }

    return 1;
}

int busca_tarefa_desc(ListaTarefas* li, char *texto, struct tarefa *t){
    if(li == NULL || *li == NULL || texto == NULL || t == NULL)
        return 0;

    Elem* no = *li;

    while(no != NULL){
        if(strstr(no->dados.descricao, texto) != NULL){
            *t = no->dados;
            return 1;
        }

        no = no->prox;
    }

    return 0;
}

int insere_tarefa_final_prioridade(ListaTarefas* li, struct tarefa t){
    if(li == NULL)
        return 0;

    Elem* no = (Elem*) malloc(sizeof(Elem));

    if(no == NULL)
        return 0;

    no->dados = t;
    no->prox = NULL;

    if(*li == NULL){
        *li = no;
        return 1;
    }

    Elem* atual = *li;
    Elem* ultima = NULL;

    while(atual != NULL){
        if(atual->dados.prioridade == t.prioridade)
            ultima = atual;

        atual = atual->prox;
    }

    if(ultima != NULL){
        no->prox = ultima->prox;
        ultima->prox = no;
    }else{
        atual = *li;

        while(atual->prox != NULL)
            atual = atual->prox;

        atual->prox = no;
    }

    return 1;
}

int remove_tarefas_prioridade(ListaTarefas* li, int prioridade){
    if(li == NULL)
        return -1;

    int cont = 0;
    Elem* ant = NULL;
    Elem* no = *li;

    while(no != NULL){
        if(no->dados.prioridade == prioridade){
            Elem* removido = no;

            if(ant == NULL)
                *li = no->prox;
            else
                ant->prox = no->prox;

            no = no->prox;
            free(removido);
            cont++;
        }else{
            ant = no;
            no = no->prox;
        }
    }

    return cont;
}

int inverte_lista(ListaTarefas* li){
    if(li == NULL)
        return 0;

    Elem* ant = NULL;
    Elem* atual = *li;
    Elem* prox;

    while(atual != NULL){
        prox = atual->prox;
        atual->prox = ant;
        ant = atual;
        atual = prox;
    }

    *li = ant;

    return 1;
}

int remove_tarefa_pos(ListaTarefas* li, int pos){
    if(li == NULL || *li == NULL || pos < 1)
        return 0;

    Elem* ant = NULL;
    Elem* no = *li;
    int atual_pos = 1;

    while(no != NULL && atual_pos < pos){
        ant = no;
        no = no->prox;
        atual_pos++;
    }

    if(no == NULL)
        return 0;

    if(ant == NULL)
        *li = no->prox;
    else
        ant->prox = no->prox;

    free(no);

    return 1;
}

int mescla_tarefas(ListaTarefas* dst, ListaTarefas* src){
    if(dst == NULL || src == NULL)
        return -1;

    if(dst == src)
        return 0;

    if(*src == NULL)
        return 0;

    int cont = 0;
    Elem* no = *src;

    while(no != NULL){
        cont++;
        no = no->prox;
    }

    if(*dst == NULL){
        *dst = *src;
    }else{
        Elem* ultimo = *dst;

        while(ultimo->prox != NULL)
            ultimo = ultimo->prox;

        ultimo->prox = *src;
    }

    *src = NULL;

    return cont;
}
