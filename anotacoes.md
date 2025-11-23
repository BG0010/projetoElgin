## exibirMenu() — Exibição do Menu Principal

Exibe todas as opções disponíveis para o usuário.

### O que faz:

-> Imprime um menu textual no terminal.
-> Mostra todas as ações possíveis que o usuário pode executar (configurar, abrir conexão, imprimir, etc.).
-> Solicita que o usuário digite uma opção.

### Detalhes importantes:

-> É chamada dentro do loop principal do `main()`.
-> Não realiza nenhuma validação — apenas mostra o menu.
-> Simplesmente organiza a interface do usuário.

-----------------------------------------------------------------------------------------------------------------------------

## configurarConexao() — Configuração dos Parâmetros de Conexão

Permite que o usuário possa modificar manualmente os dados usados para conectar à impressora.

### O que lê e configura:

-> `g_tipo` <-> Tipo de comunicação (USB, Serial, Ethernet).
-> `g_modelo` <-> Modelo da impressora (ex.: i9).
-> `g_conexao` <-> Nome/porta do tipo de conexão.
-> `g_parametro` <-> Parâmetro numérico extra requerido por certos modelos. (ex. Elgin L42 Pro / L42 DT)

### Detalhes importantes:

-> Essas variáveis são globais e usadas diretamente na função `abrirConexao()`.
-> Não valida se os dados são válidos — assume que o usuário sabe o que digita.

-----------------------------------------------------------------------------------------------------------------------------

## abrirConexao() — Conectar à Impressora

Realiza a tentativa de conexão com a impressora carregada pela DLL.

### Funcionamento:

1. Verifica se a variável global `g_conectada` já está ativa.
2. Caso não esteja conectada, chama:

   ```
   AbreConexaoImpressora(g_tipo, g_modelo, g_conexao, g_parametro);
   ```
3. Se o retorno for 0, a conexão foi bem-sucedida.
4. Marca `g_conectada = 1`.

### Detalhes importantes:

-> `AbreConexaoImpressora` é uma função carregada dinamicamente via DLL.
-> A função é crítica — sem ela, nenhuma impressão é possível.
-> Caso a conexão falhe, não encerra o programa — apenas avisa o usuário.

-----------------------------------------------------------------------------------------------------------------------------

## fecharConexao() — Encerrar Conexão com a Impressora

Fecha a conexão ativa com a impressora.

### Funcionamento:

1. Verifica se `g_conectada` é 0 (não conectada).
2. Caso conectada, chama `FechaConexaoImpressora()`.
3. Atualiza `g_conectada = 0`.
4. Exibe mensagem de finalização.

### Detalhes importantes:

-> Mesmo se a impressora estiver desconectada fisicamente, a função apenas chama a DLL.
-> Evita erros de "dupla desconexão".

-----------------------------------------------------------------------------------------------------------------------------

## imprimirTexto() — Impressão de Texto

Realiza a impressão de um texto digitado pelo usuário.

### Funcionamento:

1. Lê uma linha de texto usando `fgets`.
2. Envia esse texto para:

   ```
   ImpressaoTexto(texto, 0, 0, 0);
   ```
   -> Alinhamento: 0 (esquerda)
   -> Negrito: 0
   -> Expansão: 0
3. Avança o papel (`AvancaPapel(5)`).
4. Executa o corte (`Corte(0)`).

### Detalhes importantes:

-> Exige que a conexão já esteja aberta.
-> Usa configuração mínima da API — simplificado para estudantes.
-> Avança o papel antes de cortar para evitar corte sobre o texto.

-----------------------------------------------------------------------------------------------------------------------------

## imprimirQRCode() — Impressão de QRCode

Imprime um QRCode baseado no conteúdo digitado.

### Funcionamento:

1. Solicita o texto que será convertido em QRCode.
2. Chama:

   ```
   ImpressaoQRCode(texto, 6, 4);
   ```
   -> 6 = tamanho do QRCode
   -> 4 = nível de correção de erro
3. Avança papel.
4. Corta.

### Detalhes importantes:

-> QRCode exige que o conteúdo não seja vazio.
-> Impressoras Elgin têm limitações de tamanho e formato, por isso os parâmetros fixos.

-----------------------------------------------------------------------------------------------------------------------------

## imprimirCodigoBarras() — Código de Barras

Imprime um código de barras padrão, modelo Code128.

### Funcionamento:

-> Usa valores fixos para demonstrar a função.
-> Código enviado:

  ```
  "{A012345678912}"
  ```
  -> 8 → Tipo Code128 (código de barras linear, geralmente ler o preço do produto)
  -> Altura = 100
  -> Largura = 2
  -> Fonte = 3

Após isso, avança o papel e corta.

-----------------------------------------------------------------------------------------------------------------------------

## imprimirXMLSAT() — Impressão do XML SAT (Venda)

Imprime um arquivo `.xml` contendo informações fiscais.

### Funcionamento:

1. Abre `XMLSAT.xml`.
2. Lê todo o arquivo para um buffer. (armazenamento temporário)
3. Chama a função da DLL:

   ```
   ImprimeXMLSAT(buffer, 0);
   ```
4. Avança papel e corta.

### Detalhes importantes:

-> O arquivo precisa existir.
-> O XML é impresso formatado segundo a lógica da DLL.

-----------------------------------------------------------------------------------------------------------------------------

## imprimirXMLCancelamentoSAT() — Impressão do XML de Cancelamento

-> O XML de cancelamento
-> Uma assinatura digital fixa

### Funcionamento:

1. Lê `CANC_SAT.xml`.
2. Carrega uma string contendo a assinatura.
3. Chama:

   ```
   ImprimeXMLCancelamentoSAT(buffer, assinatura, 0);
   ```
4. Avança e corta.

### Detalhes importantes:

-> A assinatura é obrigatória para impressão de cancelamento.
-> O arquivo deve estar no mesmo diretório do projeto.

-----------------------------------------------------------------------------------------------------------------------------

## abrirGavetaElginOpc() — Abrir Gaveta 

Aciona a gaveta da impressora

### Funcionamento:

Chama:

```
AbreGavetaElgin(1, 50, 50);
```
-> 1 → Habilitado
-> 50 ms pulso ON
-> 50 ms pulso OFF

### Detalhes importantes:

-> Só funciona se a impressora tiver porta de gaveta.

-----------------------------------------------------------------------------------------------------------------------------

## abrirGavetaOpc() — Abrir Gaveta Genérica

Parecido com anterior, mas usando outra função.

### Chamado:

```
AbreGaveta(1, 5, 10);
```

-> Tempo menor de pulso
-> Compatível com outros modelos

-----------------------------------------------------------------------------------------------------------------------------

## emitirSinalSonoro() — 

Emite um som através do buzzer da impressora.

### Chamado:

```
SinalSonoro(4, 50, 5);
```

-> 4 → quantidade de bipes
-> 50 → duração
-> 5 → intervalo

-----------------------------------------------------------------------------------------------------------------------------

##  main() — Fluxo Principal do Programa

Controla todo os void's.

### Lógica:

1. Carrega a DLL.
2. Entra em loop infinito.
3. Exibe o menu.
4. Lê opção do usuário.
5. Chama a função correspondente.
6. Sai apenas quando o usuário escolhe "0".

### Importante:

* Centraliza toda a execução do programa.
* Se a DLL não carregar, o programa termina imediatamente.