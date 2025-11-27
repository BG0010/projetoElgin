	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <windows.h>
	
	/* ======================= Config DLL ======================= */
	static HMODULE g_hDll = NULL;
	
	/* Convenção de chamada (Windows): __stdcall */
	#ifndef CALLCONV
	#  define CALLCONV WINAPI
	#endif
	
	/* ======================= Assinaturas da DLL ======================= */
	typedef int (CALLCONV *AbreConexaoImpressora_t)(int, const char *, const char *, int);
	typedef int (CALLCONV *FechaConexaoImpressora_t)(void);
	typedef int (CALLCONV *ImpressaoTexto_t)(const char *, int, int, int);
	typedef int (CALLCONV *Corte_t)(int);
	typedef int (CALLCONV *ImpressaoQRCode_t)(const char *, int, int);
	typedef int (CALLCONV *ImpressaoCodigoBarras_t)(int, const char *, int, int, int);
	typedef int (CALLCONV *AvancaPapel_t)(int);
	typedef int (CALLCONV *AbreGavetaElgin_t)(int, int, int);
	typedef int (CALLCONV *AbreGaveta_t)(int, int, int);
	typedef int (CALLCONV *SinalSonoro_t)(int, int, int);
	typedef int (CALLCONV *ImprimeXMLSAT_t)(const char *, int);
	typedef int (CALLCONV *ImprimeXMLCancelamentoSAT_t)(const char *, const char *, int);
	typedef int (CALLCONV *InicializaImpressora_t)(void);
	
	/* ======================= Ponteiros ======================= */
	static AbreConexaoImpressora_t        AbreConexaoImpressora        = NULL;
	static FechaConexaoImpressora_t       FechaConexaoImpressora       = NULL;
	static ImpressaoTexto_t               ImpressaoTexto               = NULL;
	static Corte_t                        Corte                        = NULL;
	static ImpressaoQRCode_t              ImpressaoQRCode              = NULL;
	static ImpressaoCodigoBarras_t        ImpressaoCodigoBarras        = NULL;
	static AvancaPapel_t                  AvancaPapel                  = NULL;
	static AbreGavetaElgin_t              AbreGavetaElgin              = NULL;
	static AbreGaveta_t                   AbreGaveta                   = NULL;
	static SinalSonoro_t                  SinalSonoro                  = NULL;
	static ImprimeXMLSAT_t                ImprimeXMLSAT                = NULL;
	static ImprimeXMLCancelamentoSAT_t    ImprimeXMLCancelamentoSAT    = NULL;
	static InicializaImpressora_t         InicializaImpressora         = NULL;
	
	/* ======================= Configuração ======================= */
	static int   g_tipo      = 1;
	static char  g_modelo[64] = "i9";
	static char  g_conexao[128] = "USB";
	static int   g_parametro = 0;
	static int   g_conectada = 0;
	
	/* ======================= Utilidades ======================= */
	#define LOAD_FN(h, name)                                                         \
	    do {                                                                         \
	        name = (name##_t)GetProcAddress((HMODULE)(h), #name);                    \
	        if (!(name)) {                                                           \
	            fprintf(stderr, "Falha ao resolver símbolo %s (erro=%lu)\n",         \
	                    #name, GetLastError());                                      \
	            return 0;                                                            \
	        }                                                                        \
	    } while (0)
	
	static void flush_entrada(void) {
	    int c;
	    while ((c = getchar()) != '\n' && c != EOF) { }
	}
	
	/* ======================= Funções para manipular a DLL ======================= */
	static int carregarFuncoes(void)
	{
	    g_hDll = LoadLibraryA("E1_Impressora01.dll");
	    if (!g_hDll) {
	        fprintf(stderr, "Erro ao carregar E1_Impressora01.dll (erro=%lu)\n", GetLastError());
	        return 0;
	    }
	
	    LOAD_FN(g_hDll, AbreConexaoImpressora);
	    LOAD_FN(g_hDll, FechaConexaoImpressora);
	    LOAD_FN(g_hDll, ImpressaoTexto);
	    LOAD_FN(g_hDll, Corte);
	    LOAD_FN(g_hDll, ImpressaoQRCode);
	    LOAD_FN(g_hDll, ImpressaoCodigoBarras);
	    LOAD_FN(g_hDll, AvancaPapel);
	    LOAD_FN(g_hDll, AbreGavetaElgin);
	    LOAD_FN(g_hDll, AbreGaveta);
	    LOAD_FN(g_hDll, SinalSonoro);
	    LOAD_FN(g_hDll, ImprimeXMLSAT);
	    LOAD_FN(g_hDll, ImprimeXMLCancelamentoSAT);
	    LOAD_FN(g_hDll, InicializaImpressora);
	
	    return 1;
	}
	
	static void liberarBiblioteca(void)
	{
	    if (g_hDll) {
	        FreeLibrary(g_hDll);
	        g_hDll = NULL;
	    }
	}
	
	/* ======================= Funções a serem implementadas pelos alunos ======================= */
	
	static void exibirMenu(void)
	{
	    // TODO: implementar exibição do menu principal com as opções de impressão
	    //Impressão das opções
	    printf("\n--------- MENU ---------\n");
	    printf("[1] - Configurar Conexao\n");
	    printf("[2] - Abrir Conexao\n");
	    printf("[3] - Imprimir Texto\n");
	    printf("[4] - Imprimir QRCODE\n");
	    printf("[5] - Imprimir Codigo de Barras\n");
	    printf("[6] - Imprimir XML SAT\n");
	    printf("[7] - Imprimir XML Canc SAT\n");
	    printf("[8] - Abrir Gaveta Elgin\n");
	    printf("[9] - Abrir Gaveta\n");
	    printf("[10] - Emitir Som\n");
	    printf("[0] - Fechar Conexao e Sair\n");
	    printf("Opcao: ");
	} 
	
	static void configurarConexao(void)
	{
	    // TODO: pedir ao usuário tipo, modelo, conexão e parâmetro
	    printf("Tipo padrao [1]: ");
    	scanf("%d", &g_tipo);
    

    	printf("Modelo (I9): ");
    	scanf("%s", g_modelo);
	    
	    printf("Conexao [USB / COM / ETH]: ");
	    scanf("%s", g_conexao);
	    
	    printf("Parametro padrao [0]: ");
	    scanf("%d", &g_parametro);
	    
	    printf("Configuração salva!\n");
	}
	
	static void abrirConexao(void)
	{
	    // TODO: chamar AbreConexaoImpressora e validar retorno
	    
	    if (g_conectada) {
	    	printf("Está conectada!\n");
		}
		
		int ret = AbreConexaoImpressora(g_tipo, g_modelo, g_conexao, g_parametro);
		
		if (ret == 0) {
			printf("Conexao Aberta!\n");
			g_conectada = 1;
		} else {
			printf("Erro ao abrir conexao\n");
		}
	}
	
	static void fecharConexao(void)
	{
	    // TODO: chamar FechaConexaoImpressora e tratar retorno
		if (!g_conectada) { //Se não estiver conectado, mostre a mensagem
			printf("Nenhuma conexao para fechar!\n");
		}

		//Caso tiver um conexão, chame a função "FecharConexão"
		FechaConexaoImpressora();
		g_conectada = 0;

		printf("Conexao encerrada. \n");
	}
	
	static void imprimirTexto(void)
	{
	    // TODO: solicitar texto do usuário e chamar ImpressaoTexto
	    // incluir AvancaPapel e Corte no final
		
		char texto[256];
		int ret = ImpressaoTexto(texto, 0, 0, 0);
		
		if (ret != 0) {
			printf("Erro ao gerar codigo de barras.", ret);
			return;
		}
		
		printf("Conteudo do texto:\n");
		fgets(texto, sizeof(texto), stdin);

		ImpressaoTexto(texto, 0, 0, 0);
		AvancaPapel(5);
		Corte(0);

		printf("Texto impresso!\n");
	}
	
	static void imprimirQRCode(void)
	{
	    // TODO: solicitar conteúdo do QRCode e chamar ImpressaoQRCode(texto, 6, 4)
	    // incluir AvancaPapel e Corte no final
		char texto[256];
		int ret = ImpressaoQRCode(texto, 6, 4);
		
		if (ret != 0) {
			printf("Erro ao gerar codigo de barras.", ret);
			return;
		}

		printf("Conteudo do QRCODE: ");
		fgets(texto, sizeof(texto), stdin);

		ImpressaoQRCode(texto, 6, 4);
		AvancaPapel(5);
		Corte(0);

		printf("QRCode impresso!\n");
	}
	
	static void imprimirCodigoBarras(void)
	{
	    // TODO: usar ImpressaoCodigoBarras(8, "{A012345678912", 100, 2, 3)
	    // incluir AvancaPapel e Corte no final
	    int ret = ImpressaoCodigoBarras(8, "{A012345678912", 100, 2, 3);
		
		if (ret != 0) {
			printf("Erro ao gerar codigo de barras.", ret);
			return;
		}
	 
	    ImpressaoCodigoBarras(8, "{A012345678912", 100, 2, 3);
    	AvancaPapel(5);
    	Corte(0);
    	

    	printf("Codigo de barras impresso!\n");
	}
	
	static void imprimirXMLSAT(void)
	{
	    // TODO: ler o arquivo ./XMLSAT.xml e enviar via ImprimeXMLSAT
	    // incluir AvancaPapel e Corte no final
	     FILE *f = fopen("./XMLSAT.xml", "rb");
    if (!f) {
        printf("Erro: não foi possível abrir o arquivo XMLSAT.xml\n");
        return;
    }

    fseek(f, 0, SEEK_END);
    long tamanho = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buffer = (char *)malloc(tamanho + 1);
    fread(buffer, 1, tamanho, f);
    buffer[tamanho] = '\0';
    fclose(f);

    int ret = ImprimeXMLSAT(buffer, 0);
    free(buffer);

    if (ret != 0) {
        printf("Erro ao imprimir XML SAT (código %d)\n", ret);
        return;
    }

    AvancaPapel(5);
    Corte(0);

    printf("XML SAT impresso!\n");
	}
	
	static void imprimirXMLCancelamentoSAT(void)
	{
	    // TODO: ler o arquivo ./CANC_SAT.xml e chamar ImprimeXMLCancelamentoSAT
	    // incluir AvancaPapel e Corte no final
	    
		/*usar assinatura abaixo:
	        "Q5DLkpdRijIRGY6YSSNsTWK1TztHL1vD0V1Jc4spo/CEUqICEb9SFy82ym8EhBRZ"
	        "jbh3btsZhF+sjHqEMR159i4agru9x6KsepK/q0E2e5xlU5cv3m1woYfgHyOkWDNc"
	        "SdMsS6bBh2Bpq6s89yJ9Q6qh/J8YHi306ce9Tqb/drKvN2XdE5noRSS32TAWuaQE"
	        "Vd7u+TrvXlOQsE3fHR1D5f1saUwQLPSdIv01NF6Ny7jZwjCwv1uNDgGZONJdlTJ6"
	        "p0ccqnZvuE70aHOI09elpjEO6Cd+orI7XHHrFCwhFhAcbalc+ZfO5b/+vkyAHS6C"
	        "YVFCDtYR9Hi5qgdk31v23w==";
	        */
	        
	        FILE *f = fopen("./CANC_SAT.xml", "rb");
    if (!f) {
        printf("Erro: nao foi possivel abrir o arquivo CANC_SAT.xml\n");
        return;
    }

    fseek(f, 0, SEEK_END);
    long tamanho = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buffer = (char *)malloc(tamanho + 1);
    fread(buffer, 1, tamanho, f);
    buffer[tamanho] = '\0';
    fclose(f);

    const char *assinatura =
        "Q5DLkpdRijIRGY6YSSNsTWK1TztHL1vD0V1Jc4spo/CEUqICEb9SFy82ym8EhBRZ"
        "jbh3btsZhF+sjHqEMR159i4agru9x6KsepK/q0E2e5xlU5cv3m1woYfgHyOkWDNc"
        "SdMsS6bBh2Bpq6s89yJ9Q6qh/J8YHi306ce9Tqb/drKvN2XdE5noRSS32TAWuaQE"
        "Vd7u+TrvXlOQsE3fHR1D5f1saUwQLPSdIv01NF6Ny7jZwjCwv1uNDgGZONJdlTJ6"
        "p0ccqnZvuE70aHOI09elpjEO6Cd+orI7XHHrFCwhFhAcbalc+ZfO5b/+vkyAHS6C"
        "YVFCDtYR9Hi5qgdk31v23w==";

    int ret = ImprimeXMLCancelamentoSAT(buffer, assinatura, 0);
    free(buffer);

    if (ret != 0) {
        printf("Erro ao imprimir XML de Cancelamento SAT (codigo %d)\n", ret);
        return;
    }

    AvancaPapel(5);
    Corte(0);

    printf("XML de Cancelamento SAT impresso!\n");
	}
	
	static void abrirGavetaElginOpc(void)
	{
		int ret = AbreGavetaElgin(1, 50, 50);
		
		if (ret != 0) {
			printf("Erro ao abrir gaveta", ret);
			return;
		}
	    // TODO: chamar AbreGavetaElgin(1, 50, 50)
	    AbreGavetaElgin(1, 50, 50);
    	printf("Gaveta Elgin aberta!\n");
	}
	
	static void abrirGavetaOpc(void)
	{
		
		int ret = AbreGavetaElgin(1, 50, 50);
		
		if (ret != 0) {
			printf("Erro ao abrir gavetaOPV", ret);
			return;
		}
	    // TODO: chamar AbreGaveta(1, 5, 10)
	    AbreGaveta(1, 5, 10);
    	printf("Gaveta aberta!\n");
	}
	
	static void emitirSinalSonoro(void)
	{
	    // TODO: chamar SinalSonoro(4, 50, 5)
	    SinalSonoro(4, 50, 5);
    	printf("Sinal sonoro enviado!\n");
	}
	
	/* ======================= Função principal ======================= */
	int main(void)
{
    if (!carregarFuncoes())
        return 1;

    int opcao;

    while (1)
    {
        exibirMenu();
        scanf("%d", &opcao);
        flush_entrada();

        switch (opcao)
        {
        case 1: configurarConexao(); break;
        case 2: abrirConexao(); break;
        case 3: imprimirTexto(); break;
        case 4: imprimirQRCode(); break;
        case 5: imprimirCodigoBarras(); break;
        case 6: imprimirXMLSAT(); break;
        case 7: imprimirXMLCancelamentoSAT(); break;
        case 8: abrirGavetaElginOpc(); break;
        case 9: abrirGavetaOpc(); break;
        case 10: emitirSinalSonoro(); break;
        case 0:
            fecharConexao();
            printf("Saindo...\n");
            return 0;
        default:
            printf("Opção inválida!\n");
        }
    }

    return 0;
}
