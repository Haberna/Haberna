
#include <stdio.h>
#include <string.h>

#define MAX_CARTAS 100

typedef struct {
    char codigo[5];
    char estado[30];
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    float densidade_populacional;
    float pib_per_capita;
    float super_poder;
} Cidade;

void calcularPropriedades(Cidade* c) {
    c->densidade_populacional = (c->area > 0) ? c->populacao / c->area : 0;
    c->pib_per_capita = (c->populacao > 0) ? (c->pib * 1000000000) / c->populacao : 0;
    c->super_poder = c->populacao + c->area + c->pib + c->pontos_turisticos +
                     c->densidade_populacional + c->pib_per_capita;
}

void mostrarCarta(Cidade c) {
    printf("\nCarta %s - Estado: %s\n", c.codigo, c.estado);
    printf("População: %d\n", c.populacao);
    printf("Área: %.2f km²\n", c.area);
    printf("PIB: %.2f bilhões\n", c.pib);
    printf("Pontos Turísticos: %d\n", c.pontos_turisticos);
    printf("Densidade Populacional: %.2f hab/km²\n", c.densidade_populacional);
    printf("PIB per Capita: R$ %.2f\n", c.pib_per_capita);
    printf("Super Poder: %.2f\n", c.super_poder);
}

int encontrarIndice(Cidade cartas[], int total, char codigo[]) {
    for (int i = 0; i < total; i++) {
        if (strcmp(cartas[i].codigo, codigo) == 0) {
            return i;
        }
    }
    return -1;
}

void comparar(Cidade a, Cidade b) {
    printf("\n🔍 Comparando %s e %s:\n", a.codigo, b.codigo);

    if (a.densidade_populacional < b.densidade_populacional)
        printf("✅ Densidade Populacional: %s vence\n", a.codigo);
    else if (a.densidade_populacional > b.densidade_populacional)
        printf("✅ Densidade Populacional: %s vence\n", b.codigo);
    else
        printf("⚖️ Densidade Populacional: Empate\n");

    struct {
        char* nome;
        float va, vb;
    } props[] = {
        {"População", a.populacao, b.populacao},
        {"Área", a.area, b.area},
        {"PIB", a.pib, b.pib},
        {"Pontos Turísticos", a.pontos_turisticos, b.pontos_turisticos},
        {"PIB per Capita", a.pib_per_capita, b.pib_per_capita},
        {"Super Poder", a.super_poder, b.super_poder},
    };

    for (int i = 0; i < 6; i++) {
        if (props[i].va > props[i].vb)
            printf("✅ %s: %s vence\n", props[i].nome, a.codigo);
        else if (props[i].va < props[i].vb)
            printf("✅ %s: %s vence\n", props[i].nome, b.codigo);
        else
            printf("⚖️ %s: Empate\n", props[i].nome);
    }
}

void adicionarCarta(Cidade cartas[], int* total) {
    if (*total >= MAX_CARTAS) {
        printf("❌ Limite de cartas atingido!\n");
        return;
    }

    Cidade nova;
    printf("\n🔧 Adicionando nova carta:\n");

    printf("Código (ex: SP01): ");
    scanf(" %4s", nova.codigo);
    printf("Estado: ");
    scanf(" %29[^
]", nova.estado);
    printf("População: ");
    scanf("%d", &nova.populacao);
    printf("Área (km²): ");
    scanf("%f", &nova.area);
    printf("PIB (em bilhões): ");
    scanf("%f", &nova.pib);
    printf("Pontos turísticos: ");
    scanf("%d", &nova.pontos_turisticos);

    calcularPropriedades(&nova);
    cartas[*total] = nova;
    (*total)++;

    printf("✅ Carta adicionada com sucesso!\n");
}

int main() {
    Cidade cartas[MAX_CARTAS] = {
        {"AC01", "Acre", 407319, 8835.0, 3.4, 5},
        {"BA01", "Bahia", 2873000, 12345.0, 58.2, 12},
        {"CE01", "Ceará", 2687000, 9910.3, 49.1, 10},
        {"ES01", "Espírito Santo", 1800000, 9500.0, 55.3, 8},
        {"GO01", "Goiás", 1536000, 7520.0, 32.7, 7},
        {"MA01", "Maranhão", 1100000, 8300.2, 28.5, 6},
        {"MT01", "Mato Grosso", 800000, 10500.5, 26.1, 4},
        {"PA01", "Pará", 1468000, 10600.3, 34.9, 9},
        {"PE01", "Pernambuco", 2800000, 9100.4, 51.7, 11},
        {"PR01", "Paraná", 1930000, 9970.2, 59.8, 10},
        {"RJ01", "Rio de Janeiro", 6748000, 1200.0, 411.5, 15},
        {"RS01", "Rio Grande do Sul", 1490000, 9900.6, 48.6, 7}
    };

    int total = 12;
    for (int i = 0; i < total; i++) {
        calcularPropriedades(&cartas[i]);
    }

    int opcao;
    char cod1[5], cod2[5];

    do {
        printf("\n===== SUPER TRUNFO - PAÍSES =====\n");
        printf("1. Ver todas as cartas\n");
        printf("2. Comparar duas cartas\n");
        printf("3. Adicionar nova carta\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                for (int i = 0; i < total; i++) {
                    mostrarCarta(cartas[i]);
                }
                break;

            case 2:
                printf("Digite o código da primeira carta: ");
                scanf(" %4s", cod1);
                printf("Digite o código da segunda carta: ");
                scanf(" %4s", cod2);
                {
                    int i1 = encontrarIndice(cartas, total, cod1);
                    int i2 = encontrarIndice(cartas, total, cod2);
                    if (i1 == -1 || i2 == -1) {
                        printf("❌ Código inválido!\n");
                    } else {
                        mostrarCarta(cartas[i1]);
                        mostrarCarta(cartas[i2]);
                        comparar(cartas[i1], cartas[i2]);
                    }
                }
                break;

            case 3:
                adicionarCarta(cartas, &total);
                break;

            case 4:
                printf("👋 Encerrando o jogo. Até mais!\n");
                break;

            default:
                printf("❌ Opção inválida!\n");
        }

    } while (opcao != 4);

    return 0;
}
