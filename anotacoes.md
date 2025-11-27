
---

# 🖨️ Integração C com Impressora Elgin i9

### *(Impressora C)*

---
## Passo a passo de como usar
Baixe o projeto

Entre no link do GitHub.

Clique em Code → Download ZIP.

Extraia a pasta em algum lugar do seu PC.

Abra o Dev-C++

Vá em File → New → Project.

Escolha Empty Project.

Marque C++ Project.

Dê um nome e salve.

Adicione os arquivos do projeto

No Dev-C++, clique Project → Add to Project.

Vá até a pasta que você extraiu.

Adicione o arquivo .c do projeto (ex: projeto.c ou main.c).

Coloque as DLL na pasta do programa

Pegue as DLLs do GitHub (ex: E1_Impressora01.dll).

Copie para a mesma pasta onde o Dev-C++ cria o .exe
(geralmente PastaDoProjeto\Debug).

Compile

Clique em Execute → Compile.

Execute

Clique em Execute → Run.

## 📘 Sobre o Projeto

Trabalho em grupo para o desenvolvimento e integração com a Impressora Elgin.

---

## 🧰 Tecnologias Utilizadas

* 	#include <stdio.h>
*	#include <stdlib.h>
*	#include <string.h>
*	#include <windows.h>

---

## 🧪 Testes

* Teste de conexão com a impressora
* Impressão de texto simples
* Envio de comandos **ESC/POS**
* Verificação das portas de comunicação
* Teste com várias mensagens

---

# 📖 Documentação das Funções Implementadas

*(baseada na especificação original do projeto em C)*

---

## ## exibirMenu() — Exibição do Menu Principal

Exibe todas as opções disponíveis para o usuário.

### O que faz:

* Imprime um menu textual no terminal.
* Mostra todas as ações possíveis que o usuário pode executar (configurar, abrir conexão, imprimir, etc.).
* Solicita que o usuário digite uma opção.

### Detalhes importantes:

* É chamada dentro do loop principal do `main()`.
* Não realiza nenhuma validação — apenas mostra o menu.
* Organiza a interface do usuário.

---

## ## configurarConexao() — Configuração dos Parâmetros de Conexão

Permite que o usuário possa modificar manualmente os dados usados para conectar à impressora.

### O que lê e configura:

* `g_tipo` → Tipo de comunicação (USB, Serial, Ethernet).
* `g_modelo` → Modelo da impressora (ex.: i9).
* `g_conexao` → Nome/porta do tipo de conexão.
* `g_parametro` → Parâmetro numérico extra.

### Detalhes importantes:

* Variáveis globais usadas posteriormente em `abrirConexao()`.
* Não valida se os dados são válidos.

---

## abrirConexao() — Conectar à Impressora

Realiza a tentativa de conexão com a impressora carregada pela DLL.

### Funcionamento:

1. Verifica se `g_conectada` já está ativa.
2. Caso não esteja, executa:

   ```
   AbreConexaoImpressora(g_tipo, g_modelo, g_conexao, g_parametro);
   ```
3. Se o retorno for 0 → Conexão bem-sucedida.
4. Atualiza `g_conectada = 1`.

### Detalhes importantes:

* Sem conexão, nenhuma impressão pode ser feita.
* Em falha, apenas informa ao usuário.

---

## fecharConexao() — Encerrar Conexão com a Impressora

### Funcionamento:

1. Verifica se `g_conectada` == 0.
2. Caso conectada, chama `FechaConexaoImpressora()`.
3. Define `g_conectada = 0`.
4. Exibe mensagem de finalização.

### Detalhes importantes:

* Evita erros de desconexão dupla.

---

## imprimirTexto() — Impressão de Texto

### Funcionamento:

1. Lê texto com `fgets`.
2. Envia para:

   ```
   ImpressaoTexto(texto, 0, 0, 0);
   ```
3. Avança papel.
4. Executa o corte.

### Detalhes importantes:

* Exige conexão ativa.
* Avança antes de cortar para não danificar o conteúdo.

---

## imprimirQRCode() — Impressão de QRCode

### Funcionamento:

1. Solicita o conteúdo.
2. Executa:

   ```
   ImpressaoQRCode(texto, 6, 4);
   ```
3. Avança e corta.

### Detalhes importantes:

* Conteúdo não pode ser vazio.

---

## imprimirCodigoBarras() — Código de Barras Code128

### Funcionamento:

Código fixo utilizado:

```
"{A012345678912}"
```

Configuração:

* Tipo: 8 (Code128)
* Altura: 100
* Largura: 2
* Fonte: 3

Após isso, avança e corta.

---

## imprimirXMLSAT() — Impressão do XML SAT

### Funcionamento:

1. Abre `XMLSAT.xml`.
2. Lê o conteúdo para um buffer.
3. Chama:

   ```
   ImprimeXMLSAT(buffer, 0);
   ```
4. Avança e corta.

### Detalhes importantes:

* O arquivo deve existir.

---

## imprimirXMLCancelamentoSAT() — Impressão do XML de Cancelamento

### Funcionamento:

1. Lê `CANC_SAT.xml`.
2. Carrega assinatura digital.
3. Chama:

   ```
   ImprimeXMLCancelamentoSAT(buffer, assinatura, 0);
   ```
4. Avança e corta.

### Detalhes importantes:

* A assinatura é obrigatória.

---

## abrirGavetaElginOpc() — Abrir Gaveta Elgin

Chama:

```
AbreGavetaElgin(1, 50, 50);
```

---

## abrirGavetaOpc() — Abrir Gaveta Genérica

Chama:

```
AbreGaveta(1, 5, 10);
```

---

## emitirSinalSonoro()

Chama:

```
SinalSonoro(4, 50, 5);
```

---

## main() — Fluxo Principal

### Lógica:

1. Carrega a DLL.
2. Entra no loop principal.
3. Exibe o menu.
4. Lê a opção.
5. Executa a função correspondente.
6. Encerra somente ao selecionar “0”.

---

# 👥 Autores

*Camila Santos;
*Gabriel Alves;
*Guilherme Pereira;
*Vinicius Alves;
*Vinicius Borges.

---


