# 🧵 Sistema de Gestão para Ateliê de Costura

Este é um sistema de linha de comando (CLI) desenvolvido em **Linguagem C** voltado para o gerenciamento de serviços e clientes em um ateliê de costura. O projeto foi projetado com foco em **Modularização Avançada** e **Persistência de Dados em Arquivos Planos (.txt)**, aplicando conceitos fundamentais de engenharia de software do 3º semestre de computação.

---

## 🎯 Funcionalidades Principais

* **Catálogo de Serviços (CRUD Completo):** Cadastro, listagem, edição e exclusão lógica de serviços oferecidos pelo ateliê (com geração automática de IDs).
* **Lançamento de Pedidos Flexível:** Permite à costureira registrar ordens de serviço vinculando **múltiplos serviços** a um único cliente na mesma nota.
* **Cálculo Automático de Subtotais:** O sistema soma os valores do catálogo em tempo real à medida que os serviços são adicionados.
* **Emissão de Nota de Serviço:** Gera um layout formatado de comprovante na tela com os dados fixos do ateliê (Nome e Contato) e os detalhes da entrega.
* **Relatório Analítico:** Filtragem e listagem de ordens de serviço com base na **Data de Entrega** especificada.

---

## 🛠️ Arquitetura do Projeto (Modularização)

O sistema foi estruturado seguindo o princípio da **Separação de Responsabilidades**, dividindo o código em módulos isolados com baixo acoplamento:

* `dados.h`: Camada de modelagem global. Contém as definições de estruturas (`structs`) como `Pedido`, `Servico` e `Data`.
* `interface.c` / `interface.h`: Responsável pela experiência visual e estabilidade. Controla a limpeza dinâmica da tela (compatível com Windows e Linux) e o tratamento do buffer de entrada.
* `catalogo.c` / `catalogo.h`: Módulo focado na manipulação do arquivo `catalogo.txt` (Regras de negócio do catálogo de preços).
* `pedidos.c` / `pedidos.h`: Módulo inteligente responsável pelo processamento de notas e gerenciamento do arquivo `pedidos.txt`.
* `main.c`: O controlador central. Contém apenas o menu interativo e direciona o fluxo de execução para os respectivos módulos.

---

## 🧠 Destaques Técnicos

### 1. Simulação de Banco de Dados Relacional em TXT

Para permitir múltiplos serviços por cliente sem usar alocação dinâmica complexa ou bancos SQL, o sistema compacta os IDs selecionados em uma string delimitada por vírgulas (ex: `"1,3,4"`) e salva no arquivo. Na hora da leitura, a função nativa `strtok` é utilizada para "fatiar" o texto e buscar individualmente os dados de cada serviço no catálogo.

### 2. Blindagem contra Lixo de Buffer

Evitando o bug clássico do `scanf` que pula a leitura de strings ao capturar o caractere `\n` (Enter), foi desenvolvida uma rotina robusta de limpeza baseada em `getchar()`, garantindo que o teclado esteja sempre limpo antes de capturar nomes com espaços.

### 3. Captura de Textos Longos com Espaços

Utilização da máscara de leitura ` %[^\n]` em detrimento do `%s` tradicional, permitindo que a dona do ateliê digite nomes de clientes e de serviços com espaços de forma totalmente natural.

---

## 🚀 Como Compilar e Executar

Certifique-se de ter o compilador `gcc` instalado em sua máquina. No terminal, navegue até a pasta do projeto e execute o comando abaixo para compilar todos os módulos juntos:

```bash
gcc main.c catalogo.c pedidos.c interface.c -o sistema_atelie

```

Para rodar a aplicação:

```bash
# No Linux / Mac:
./sistema_atelie

# No Windows:
sistema_atelie.exe

```

---

## 📄 Licença

Este projeto foi desenvolvido para fins estritamente acadêmicos. Sinta-se livre para clonar, estudar e sugerir melhorias!
