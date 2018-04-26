///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// ALUNOS RESPONSAVEIS ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
//////                             Guilherme Caulada - 31416489                                  //////
//////                             Guilherme Wentz - 31540929                                    //////
//////                             Lucas Paulosky - 31442412                                     //////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// INCLUDES NECESSARIOS ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>



///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// CONFIGURACAO DOS ARQUIVOS //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
#define ENTRADA "MiniAlg.txt" // Arquivo com o codigo MiniAlg a ser analisado.
#define SAIDA "Tokens.txt" // Arquivo que sera gerado com os Tokens.



///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// DECLARACAO DE FUNCOES E VARIAVEIS //////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

// Variaveis do analisador
int i; // Index do elemento a ser analisado
char * codigo; // Codigo ou String a ser analisada
long tam; // Tamanho dessa string

// Funcoes do analisador (Descricao esta acima da funcao)
char * _ler(char * nome); // Funcao que le o arquivo configurado na linha 25 como ENTRADA
void _escrever(char * nome, char *texto); // Funcao que escreve no arquivo configurado na linha 26 como SAIDA
char _lookahead(); // Funcao que retorna o valor do proximo simbolo lexico sem consumi-lo.
char _match(); // Funcao que retorna o valor do proximo simbolo lexico consumindo-o.
bool _matchAny(char * check); // Funcao que verifica se o valor do proximo simbolo lexico se iguala a qualquer um dos simbolos passados no argumento check como um array de simbolos.

// Funcoes do analisador lexico
bool verdadeiro(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'verdadeiro '
bool falso(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'falso '
bool booleano(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'booleano '
bool inteiro(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'inteiro '
bool palavra_programa(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'programa '
bool fimprograma(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'fimprograma '
bool procedimento(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'procedimento '
bool fimprocedimento(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'fimprocedimento '
bool enquanto(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'enquanto '
bool escreva(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'escreva '
bool faca(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'faca '
bool fimenquanto(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'fimenquanto '
bool se(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'se '
bool fimse(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'fimse '
bool senao(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'senao '
bool entao(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'entao '
bool virgula(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a ', '
bool ponto_e_virgula(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a '; '
bool dois_pontos(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a ': '
bool parenteses_esquerda(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a '( '
bool parenteses_direita(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a ') '
bool operador_div(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'div '
bool operador_mul(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'mul '
bool operador_mais(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a '+ '
bool operador_menos(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a '- '
bool operador_igual(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a '= '
bool relacao_menor(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a '< '
bool relacao_maior(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a '> '
bool relacao_igual(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a '== '
bool relacao_diferente(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a '<> '
bool relacao_menor_igual(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a '<= '
bool relacao_maior_igual(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a '>= '
bool palavra_reservada(bool write, bool error); // Funcao que verifica se a proxima sequencia lexica existente tem valor igual a qualquer uma das palavras reservadas

// Funcoes do analisador sintatico
bool letra(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <letra>
bool digito(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <digito>
bool numero(bool write,bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <numero>
bool boolean(bool write,bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <boolean>
bool identificador(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <identificador>
bool variavel(bool write,bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <variavel>
bool fator(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <fator>
bool expressao_simples(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <expressao simples>
bool relacao(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <relacao>
bool expressao(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <expressao>
bool comando_repetitivo(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <comando repetitivo>
bool comando_condicional(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <comando condicional>
bool lista_de_parametros(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <lista de paremtros>
bool chamada_de_procedimento(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <chamada de procedimento>
bool atribuicao(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <atribuicao>
bool comando(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <comando>
bool comando_composto(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <comando composto>
bool parametro_formal(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <paremetro formal>
bool parametros_formais(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <parametros formais>
bool declaracao_de_procedimento(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <declaracao de procedimento>
bool parte_de_declaracoes_de_subrotinas(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <parte de declaracoes de subrotinas>
bool lista_de_identificadores(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <lista de identificadores>
bool tipo(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <tipo>
bool declaracao_de_variaveis(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <declaracao de variaveis>
bool parte_de_declaracoes_de_variaveis(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <parte de declaracoes de variaveis>
bool bloco(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <bloco>
bool programa(bool write, bool error); // Funcao que verifica se a proxima sequencia sintatica existente equivale a <programa>

// Argumentos: bool write, bool error
// bool write -> Define se o token sera escrito em caso de sucesso.
// bool error -> Define se o token sera escrito em caso de erro.
// Esta opcao e util por que muitas vezes um token e parte para gerar outro token, e portanto ele nao deve ser escrito.



///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// FUNCOES DO ANALISADOR //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

// Funcao que le o arquivo configurado na linha 25 como ENTRADA
char * _ler(char * nome) {
    FILE *arquivo = fopen(nome, "r");
    char *codigo;
    size_t n = 0;
    int c, last;

    if (arquivo == NULL) return NULL;
    fseek(arquivo, 0, SEEK_END);
    tam = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);
    codigo = malloc(tam);

    while ((c = fgetc(arquivo)) != EOF) {
    	if (c != '\n' && c != '\t') { // Aqui ignoramos enters e tabs
    		if (!(c == ' ' && last == ' ')){ // Aqui ignoramos um espaco depois do outro como '  '
        		codigo[n++] = (char)c;
        		last = c;
			}
		}
    }

    codigo[n] = '\0';
    fclose(arquivo);

    return codigo;
}

// Funcao que escreve no arquivo configurado na linha 26 como SAIDA
void _escrever(char * nome, char *texto) {
    FILE *arquivo = fopen(nome, "a");

    fprintf(arquivo, texto);
    fclose(arquivo);
}

// Funcao que retorna o valor do proximo simbolo lexico sem consumi-lo.
char _lookahead(){
	return codigo[i+1];
}

// Funcao que retorna o valor do proximo simbolo lexico consumindo-o.
char _match(){
	return codigo[++i];
}

// Funcao que verifica se o valor do proximo simbolo lexico se iguala a qualquer um dos simbolos passados no argumento check como um array de simbolos.
bool _matchAny(char * check){
	size_t len = strlen(check);
	int j;
	for (j = 0; j<len; j++){
		if (_match() == check[j]) return true;
		i--;
	}
	return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// ANALISADOR LEXICO //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'verdadeiro '
bool verdadeiro(bool write, bool error){
	int j = i;
	if ((_lookahead() == 'v') &&
		(_match() == 'v') &&
		(_lookahead() == 'e') &&
		(_match() == 'e') &&
		(_lookahead() == 'r') &&
		(_match() == 'r') &&
		(_lookahead() == 'd') &&
		(_match() == 'd') &&
		(_lookahead() == 'a') &&
		(_match() == 'a') &&
		(_lookahead() == 'd') &&
		(_match() == 'd') &&
		(_lookahead() == 'e') &&
		(_match() == 'e') &&
		(_lookahead() == 'i') &&
		(_match() == 'i') &&
		(_lookahead() == 'r') &&
		(_match() == 'r') &&
		(_lookahead() == 'o') &&
		(_match() == 'o') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("verdadeiro ");
			_escrever(SAIDA, "verdadeiro ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,verdadeiro ");
			_escrever(SAIDA, "ERRO LEXICO,verdadeiro ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'falso '
bool falso(bool write, bool error){
	int j = i;
	if ((_lookahead() == 'f') &&
		(_match() == 'f') &&
		(_lookahead() == 'a') &&
		(_match() == 'a') &&
		(_lookahead() == 'l') &&
		(_match() == 'l') &&
		(_lookahead() == 's') &&
		(_match() == 's') &&
		(_lookahead() == 'o') &&
		(_match() == 'o') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("falso ");
			_escrever(SAIDA, "falso ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,falso ");
			_escrever(SAIDA, "ERRO LEXICO,falso ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'booleano '
bool booleano(bool write, bool error){
	int j = i;
	if ((_lookahead() == 'b') &&
		(_match() == 'b') &&
		(_lookahead() == 'o') &&
		(_match() == 'o') &&
		(_lookahead() == 'o') &&
		(_match() == 'o') &&
		(_lookahead() == 'l') &&
		(_match() == 'l') &&
		(_lookahead() == 'e') &&
		(_match() == 'e') &&
		(_lookahead() == 'a') &&
		(_match() == 'a') &&
		(_lookahead() == 'n') &&
		(_match() == 'n') &&
		(_lookahead() == 'o') &&
		(_match() == 'o') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("booleano ");
			_escrever(SAIDA, "booleano ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,booleano ");
			_escrever(SAIDA, "ERRO LEXICO,booleano ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'inteiro '
bool inteiro(bool write, bool error){
	int j = i;
	if ((_lookahead() == 'i') &&
		(_match() == 'i') &&
		(_lookahead() == 'n') &&
		(_match() == 'n') &&
		(_lookahead() == 't') &&
		(_match() == 't') &&
		(_lookahead() == 'e') &&
		(_match() == 'e') &&
		(_lookahead() == 'i') &&
		(_match() == 'i') &&
		(_lookahead() == 'r') &&
		(_match() == 'r') &&
		(_lookahead() == 'o') &&
		(_match() == 'o') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("inteiro ");
			_escrever(SAIDA, "inteiro ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,inteiro ");
			_escrever(SAIDA, "ERRO LEXICO,inteiro ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'programa '
bool palavra_programa(bool write, bool error){
	int j = i;
	if ((_lookahead() == 'p') &&
		(_match() == 'p') &&
		(_lookahead() == 'r') &&
		(_match() == 'r') &&
		(_lookahead() == 'o') &&
		(_match() == 'o') &&
		(_lookahead() == 'g') &&
		(_match() == 'g') &&
		(_lookahead() == 'r') &&
		(_match() == 'r') &&
		(_lookahead() == 'a') &&
		(_match() == 'a') &&
		(_lookahead() == 'm') &&
		(_match() == 'm') &&
		(_lookahead() == 'a') &&
		(_match() == 'a') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("programa ");
			_escrever(SAIDA, "programa ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,programa ");
			_escrever(SAIDA, "ERRO LEXICO,programa ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'fimprograma '
bool fimprograma(bool write, bool error){
	int j = i;
	if ((_lookahead() == 'f') &&
		(_match() == 'f') &&
		(_lookahead() == 'i') &&
		(_match() == 'i') &&
		(_lookahead() == 'm') &&
		(_match() == 'm') &&
		(_lookahead() == 'p') &&
		(_match() == 'p') &&
		(_lookahead() == 'r') &&
		(_match() == 'r') &&
		(_lookahead() == 'o') &&
		(_match() == 'o') &&
		(_lookahead() == 'g') &&
		(_match() == 'g') &&
		(_lookahead() == 'r') &&
		(_match() == 'r') &&
		(_lookahead() == 'a') &&
		(_match() == 'a') &&
		(_lookahead() == 'm') &&
		(_match() == 'm') &&
		(_lookahead() == 'a') &&
		(_match() == 'a') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("fimprograma ");
			_escrever(SAIDA, "fimprograma ");
			printf("\n");
			_escrever(SAIDA, "\n");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,fimprograma ");
			_escrever(SAIDA, "ERRO LEXICO,fimprograma ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'procedimento '
bool procedimento(bool write, bool error){
	int j = i;
	if ((_lookahead() == 'p') &&
		(_match() == 'p') &&
		(_lookahead() == 'r') &&
		(_match() == 'r') &&
		(_lookahead() == 'o') &&
		(_match() == 'o') &&
		(_lookahead() == 'c') &&
		(_match() == 'c') &&
		(_lookahead() == 'e') &&
		(_match() == 'e') &&
		(_lookahead() == 'd') &&
		(_match() == 'd') &&
		(_lookahead() == 'i') &&
		(_match() == 'i') &&
		(_lookahead() == 'm') &&
		(_match() == 'm') &&
		(_lookahead() == 'e') &&
		(_match() == 'e') &&
		(_lookahead() == 'n') &&
		(_match() == 'n') &&
		(_lookahead() == 't') &&
		(_match() == 't') &&
		(_lookahead() == 'o') &&
		(_match() == 'o') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("procedimento ");
			_escrever(SAIDA, "procedimento ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,procedimento ");
			_escrever(SAIDA, "ERRO LEXICO,procedimento ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'fimprocedimento '
bool fimprocedimento(bool write, bool error){
	int j = i;
	if ((_lookahead() == 'f') &&
		(_match() == 'f') &&
		(_lookahead() == 'i') &&
		(_match() == 'i') &&
		(_lookahead() == 'm') &&
		(_match() == 'm') &&
		(_lookahead() == 'p') &&
		(_match() == 'p') &&
		(_lookahead() == 'r') &&
		(_match() == 'r') &&
		(_lookahead() == 'o') &&
		(_match() == 'o') &&
		(_lookahead() == 'c') &&
		(_match() == 'c') &&
		(_lookahead() == 'e') &&
		(_match() == 'e') &&
		(_lookahead() == 'd') &&
		(_match() == 'd') &&
		(_lookahead() == 'i') &&
		(_match() == 'i') &&
		(_lookahead() == 'm') &&
		(_match() == 'm') &&
		(_lookahead() == 'e') &&
		(_match() == 'e') &&
		(_lookahead() == 'n') &&
		(_match() == 'n') &&
		(_lookahead() == 't') &&
		(_match() == 't') &&
		(_lookahead() == 'o') &&
		(_match() == 'o') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("fimprocedimento ");
			_escrever(SAIDA, "fimprocedimento ");
			printf("\n");
			_escrever(SAIDA, "\n");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,fimprocedimento ");
			_escrever(SAIDA, "ERRO LEXICO,fimprocedimento ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'enquanto '
bool enquanto(bool write, bool error){
	int j = i;
	if ((_lookahead() == 'e') &&
		(_match() == 'e') &&
		(_lookahead() == 'n') &&
		(_match() == 'n') &&
		(_lookahead() == 'q') &&
		(_match() == 'q') &&
		(_lookahead() == 'u') &&
		(_match() == 'u') &&
		(_lookahead() == 'a') &&
		(_match() == 'a') &&
		(_lookahead() == 'n') &&
		(_match() == 'n') &&
		(_lookahead() == 't') &&
		(_match() == 't') &&
		(_lookahead() == 'o') &&
		(_match() == 'o') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("enquanto ");
			_escrever(SAIDA, "enquanto ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,enquanto ");
			_escrever(SAIDA, "ERRO LEXICO,enquanto ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'escreva '
bool escreva(bool write, bool error){
	int j = i;
	if ((_lookahead() == 'e') &&
		(_match() == 'e') &&
		(_lookahead() == 's') &&
		(_match() == 's') &&
		(_lookahead() == 'c') &&
		(_match() == 'c') &&
		(_lookahead() == 'r') &&
		(_match() == 'r') &&
		(_lookahead() == 'e') &&
		(_match() == 'e') &&
		(_lookahead() == 'v') &&
		(_match() == 'v') &&
		(_lookahead() == 'a') &&
		(_match() == 'a') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("escreva ");
			_escrever(SAIDA, "escreva ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,escreva ");
			_escrever(SAIDA, "ERRO LEXICO,escreva ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'faca '
bool faca(bool write, bool error){
	int j = i;
	if ((_lookahead() == 'f') &&
		(_match() == 'f') &&
		(_lookahead() == 'a') &&
		(_match() == 'a') &&
		(_lookahead() == 'c') &&
		(_match() == 'c') &&
		(_lookahead() == 'a') &&
		(_match() == 'a') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("faca ");
			_escrever(SAIDA, "faca ");
			printf("\n");
			_escrever(SAIDA, "\n");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,faca ");
			_escrever(SAIDA, "ERRO LEXICO,faca ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'fimenquanto '
bool fimenquanto(bool write, bool error){
	int j = i;
	if ((_lookahead() == 'f') &&
		(_match() == 'f') &&
		(_lookahead() == 'i') &&
		(_match() == 'i') &&
		(_lookahead() == 'm') &&
		(_match() == 'm') &&
		(_lookahead() == 'e') &&
		(_match() == 'e') &&
		(_lookahead() == 'n') &&
		(_match() == 'n') &&
		(_lookahead() == 'q') &&
		(_match() == 'q') &&
		(_lookahead() == 'u') &&
		(_match() == 'u') &&
		(_lookahead() == 'a') &&
		(_match() == 'a') &&
		(_lookahead() == 'n') &&
		(_match() == 'n') &&
		(_lookahead() == 't') &&
		(_match() == 't') &&
		(_lookahead() == 'o') &&
		(_match() == 'o') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("fimenquanto ");
			_escrever(SAIDA, "fimenquanto ");
			printf("\n");
			_escrever(SAIDA, "\n");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,fimenquanto ");
			_escrever(SAIDA, "ERRO LEXICO,fimenquanto ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'se '
bool se(bool write, bool error){
	int j = i;
	if ((_lookahead() == 's') &&
		(_match() == 's') &&
		(_lookahead() == 'e') &&
		(_match() == 'e') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("se ");
			_escrever(SAIDA, "se ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,se ");
			_escrever(SAIDA, "ERRO LEXICO,se ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'fimse '
bool fimse(bool write, bool error){
	int j = i;
	if ((_lookahead() == 'f') &&
		(_match() == 'f') &&
		(_lookahead() == 'i') &&
		(_match() == 'i') &&
		(_lookahead() == 'm') &&
		(_match() == 'm') &&
		(_lookahead() == 's') &&
		(_match() == 's') &&
		(_lookahead() == 'e') &&
		(_match() == 'e') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("fimse ");
			_escrever(SAIDA, "fimse ");
			printf("\n");
			_escrever(SAIDA, "\n");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,fimse ");
			_escrever(SAIDA, "ERRO LEXICO,fimse ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'senao '
bool senao(bool write, bool error){
	int j = i;
	if ((_lookahead() == 's') &&
		(_match() == 's') &&
		(_lookahead() == 'e') &&
		(_match() == 'e') &&
		(_lookahead() == 'n') &&
		(_match() == 'n') &&
		(_lookahead() == 'a') &&
		(_match() == 'a') &&
		(_lookahead() == 'o') &&
		(_match() == 'o') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("senao ");
			_escrever(SAIDA, "senao ");
			printf("\n");
			_escrever(SAIDA, "\n");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,senao ");
			_escrever(SAIDA, "ERRO LEXICO,senao ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'entao '
bool entao(bool write, bool error){
	int j = i;
	if ((_lookahead() == 'e') &&
		(_match() == 'e') &&
		(_lookahead() == 'n') &&
		(_match() == 'n') &&
		(_lookahead() == 't') &&
		(_match() == 't') &&
		(_lookahead() == 'a') &&
		(_match() == 'a') &&
		(_lookahead() == 'o') &&
		(_match() == 'o') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("entao ");
			_escrever(SAIDA, "entao ");
			printf("\n");
			_escrever(SAIDA, "\n");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,entao ");
			_escrever(SAIDA, "ERRO LEXICO,entao ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a ', '
bool virgula(bool write, bool error){
	int j = i;
	if ((_lookahead() == ',') &&
		(_match() == ',') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf(", ");
			_escrever(SAIDA, ", ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,, ");
			_escrever(SAIDA, "ERRO LEXICO,, ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a '; '
bool ponto_e_virgula(bool write, bool error){
	int j = i;
	if ((_lookahead() == ';') &&
		(_match() == ';') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("; ");
			_escrever(SAIDA, "; ");
			printf("\n");
			_escrever(SAIDA, "\n");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,; ");
			_escrever(SAIDA, "ERRO LEXICO,; ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a ': '
bool dois_pontos(bool write, bool error){
	int j = i;
	if ((_lookahead() == ':') &&
		(_match() == ':') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf(": ");
			_escrever(SAIDA, ": ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,: ");
			_escrever(SAIDA, "ERRO LEXICO,: ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a '( '
bool parenteses_esquerda(bool write, bool error){
	int j = i;
	if ((_lookahead() == '(') &&
		(_match() == '(') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("( ");
			_escrever(SAIDA, "( ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,( ");
			_escrever(SAIDA, "ERRO LEXICO,( ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a ') '
bool parenteses_direita(bool write, bool error){
	int j = i;
	if ((_lookahead() == ')') &&
		(_match() == ')') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf(") ");
			_escrever(SAIDA, ") ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,) ");
			_escrever(SAIDA, "ERRO LEXICO,) ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'div '
bool operador_div(bool write, bool error){
	int j = i;
	if ((_lookahead() == 'd') &&
		(_match() == 'd') &&
		(_lookahead() == 'i') &&
		(_match() == 'i') &&
		(_lookahead() == 'v') &&
		(_match() == 'v') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("div ");
			_escrever(SAIDA, "div ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,div ");
			_escrever(SAIDA, "ERRO LEXICO,div ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'mul '
bool operador_mul(bool write, bool error){
	int j = i;
	if ((_lookahead() == 'm') &&
		(_match() == 'm') &&
		(_lookahead() == 'u') &&
		(_match() == 'u') &&
		(_lookahead() == 'l') &&
		(_match() == 'l') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("mul ");
			_escrever(SAIDA, "mul ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,mul ");
			_escrever(SAIDA, "ERRO LEXICO,mul ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a '+ '
bool operador_mais(bool write, bool error){
	int j = i;
	if ((_lookahead() == '+') &&
		(_match() == '+') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("+ ");
			_escrever(SAIDA, "+ ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,+ ");
			_escrever(SAIDA, "ERRO LEXICO,+ ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a '- '
bool operador_menos(bool write, bool error){
	int j = i;
	if ((_lookahead() == '-') &&
		(_match() == '-') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("- ");
			_escrever(SAIDA, "- ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,- ");
			_escrever(SAIDA, "ERRO LEXICO,- ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a '= '
bool operador_igual(bool write, bool error){
	int j = i;
	if ((_lookahead() == '=') &&
		(_match() == '=') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("= ");
			_escrever(SAIDA, "= ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,= ");
			_escrever(SAIDA, "ERRO LEXICO,= ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a '< '
bool relacao_menor(bool write, bool error){
	int j = i;
	if ((_lookahead() == '<') &&
		(_match() == '<') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("< ");
			_escrever(SAIDA, "< ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,< ");
			_escrever(SAIDA, "ERRO LEXICO,< ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a '> '
bool relacao_maior(bool write, bool error){
	int j = i;
	if ((_lookahead() == '>') &&
		(_match() == '>') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("> ");
			_escrever(SAIDA, "> ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,> ");
			_escrever(SAIDA, "ERRO LEXICO,> ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a '== '
bool relacao_igual(bool write, bool error){
	int j = i;
	if ((_lookahead() == '=') &&
		(_match() == '=') &&
		(_lookahead() == '=') &&
		(_match() == '=') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("== ");
			_escrever(SAIDA, "== ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,== ");
			_escrever(SAIDA, "ERRO LEXICO,== ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a '<> '
bool relacao_diferente(bool write, bool error){
	int j = i;
	if ((_lookahead() == '<') &&
		(_match() == '<') &&
		(_lookahead() == '>') &&
		(_match() == '>') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("<> ");
			_escrever(SAIDA, "<> ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,<> ");
			_escrever(SAIDA, "ERRO LEXICO,<> ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a '<= '
bool relacao_menor_igual(bool write, bool error){
	int j = i;
	if ((_lookahead() == '<') &&
		(_match() == '<') &&
		(_lookahead() == '=') &&
		(_match() == '=') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf("<= ");
			_escrever(SAIDA, "<= ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,<= ");
			_escrever(SAIDA, "ERRO LEXICO,<= ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a '>= '
bool relacao_maior_igual(bool write, bool error){
	int j = i;
	if ((_lookahead() == '>') &&
		(_match() == '>') &&
		(_lookahead() == '=') &&
		(_match() == '=') &&
		(_lookahead() == ' ') &&
		(_match() == ' ')) {
		if (write) {
   			printf(">= ");
			_escrever(SAIDA, ">= ");
		}
		return true;
	} else {
		i = j;
		if (error) {
   			printf("ERRO LEXICO,>= ");
			_escrever(SAIDA, "ERRO LEXICO,>= ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia lexica existente tem valor igual a 'qualquer uma das palavras reservadas
bool palavra_reservada(bool write, bool error) {
	int j = i;
	if (palavra_programa(write,error) ||
		fimprograma(write,error) ||
		procedimento(write,error) ||
		fimprocedimento(write,error) ||
		enquanto(write,error) ||
		fimenquanto(write,error) ||
		se(write,error) ||
		fimse(write,error) ||
		inteiro(write,error) ||
		booleano(write,error) ||
		entao(write,error) ||
		senao(write,error) ||
		escreva(write,error) ||
		verdadeiro(write,error) ||
		falso(write,error) ||
		faca(write,error)) {
			i = j;
			return true;
		}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// ANALISADOR SINTATICO ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <letra>
bool letra(bool write, bool error){
	if (_matchAny("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")){
		if (write) {
			printf("<letra> ");
			_escrever(SAIDA, "<letra> ");
		}
		return true;
	} else if (error) {
   		printf("<ERRO SINTATICO,letra> ");
		_escrever(SAIDA, "<ERRO SINTAXE,letra> ");
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <digito>
bool digito(bool write, bool error){
	if (_matchAny("0123456789")){
		if (write) {
			printf("<digito> ");
			_escrever(SAIDA, "<digito> ");
		}
		return true;
	} else if (error) {
   		printf("<ERRO SINTATICO,digito> ");
		_escrever(SAIDA, "<ERRO SINTAXE,digito> ");
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <numero>
bool numero(bool write,bool error){
	bool ultima = false;
	char *token;
 	token = (char*) calloc (256, sizeof(char));
	strcpy(token, "<numero,");
	size_t len = strlen(token);
	numero_digito: 
	if (_lookahead() == ' ') {
		ultima = true;
	}
	if (ultima){
		if (_match() == ' ') {
			if (write) {
				token[len++] = '>';
				token[len++] = ' ';
				printf("%s", token);
				_escrever(SAIDA, token);
			}
			return true;
		} else {
			if (error) {
	  			printf("<ERRO SINTATICO,numero> ");
				_escrever(SAIDA, "<ERRO SINTATICO,numero> ");
			}
			return false;
			}
	} else {
		if (digito(false,false)) {
			token[len++] = codigo[i];
			goto numero_digito;
		}
	}
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <bool>
bool boolean(bool write,bool error){
	if (verdadeiro(false, false)) {
		if (write) {
			printf("<bool,verdadeiro> ");
			_escrever(SAIDA, "<bool,verdadeiro> ");
		}
		return true;
	} else if (falso(false, false)) {
		if (write) {
			printf("<bool,falso> ");
			_escrever(SAIDA, "<bool,falso> ");
		}
		return true;
	} else if (error) {
   		printf("<ERRO SINTATICO,bool> ");
		_escrever(SAIDA, "<ERRO SINTATICO,bool> ");
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <identificador>
bool identificador(bool write, bool error){
	if (palavra_reservada(false,false)) {
		return false;
	}
	bool ultima = false;
	char *token;
 	token = (char*) calloc (256, sizeof(char));
	strcpy(token, "<identificador,");
	size_t len = strlen(token);
	ident_letra: 
	if (_lookahead() == ' ') {
		ultima = true;
	}
	if (ultima){
		if (_match() == ' ') {
			if (write) {
				token[len++] = '>';
				token[len++] = ' ';
				printf("%s", token);
				_escrever(SAIDA, token);
			}
			return true;
		} else {
			if (error) {
	  			printf("<ERRO SINTATICO,identificador> ");
				_escrever(SAIDA, "<ERRO SINTATICO,identificador> ");
			}
			return false;
			}
	} else {
		if (letra(false,false)) {
			token[len++] = codigo[i];
			goto ident_letra;
		}
	}
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <variavel>
bool variavel(bool write,bool error){
	if (identificador(true,false)) {
		if (write) {
			printf("<variavel> ");
			_escrever(SAIDA, "<variavel> ");
		}
		return true;
	} else if (error) {
   		printf("<ERRO SINTATICO,variavel> ");
		_escrever(SAIDA, "<ERRO SINTATICO,variavel> ");
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <fator>
bool fator(bool write, bool error){
	if (numero(true,false)) {
		if (write) {
			printf("<fator,numero> ");
			_escrever(SAIDA, "<fator,numero> ");
		}
		return true;
	} else if (boolean(true,false)) {
		if (write) {
			printf("<fator,boolean> ");
			_escrever(SAIDA, "<fator,boolean> ");
		}
		return true;
	} else if (parenteses_esquerda(true,false)) {
		if (expressao_simples(true,false)) {
			if (parenteses_direita(true,false)) {
				if (write) {
					printf("<fator,expressao simples> ");
					_escrever(SAIDA, "<fator,expressao simples> ");
				}
				return true;
			}
		}
	} else if (variavel(false,false)) {
		if (write) {
			printf("<fator,variavel> ");
			_escrever(SAIDA, "<fator,variavel> ");
		}
		return true;
	}
	if (error) {
   		printf("<ERRO SINTATICO,fator> ");
		_escrever(SAIDA, "<ERRO SINTATICO,fator> ");
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <termo>
bool termo(bool write, bool error){
	while (fator(false,false)) {
		if (operador_mul(true,false)) {
			continue;
		}else if (operador_div(true,false)) {
			continue;
		} else {
			if (write) {
				printf("<termo> ");
				_escrever(SAIDA, "<termo> ");
			}
			return true;
		}
	} 
   	if (error) {
		printf("<ERRO SINTATICO,termo> ");
		_escrever(SAIDA, "<ERRO SINTATICO,termo> ");
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <expressao simples>
bool expressao_simples(bool write, bool error){
	bool tem_um = false;
	exp_smp: 
	if (operador_mais(true,false)) {
		if (termo(false,false)) {
			tem_um = true;
			goto exp_smp;
		}
	} else if (operador_menos(true,false)) {
			if (termo(false,false)) {
				tem_um = true;
				goto exp_smp;
			}
	} else {
		if (termo(false,false)) {
			tem_um = true;
			goto exp_smp;
		}
	}
	if (tem_um){
		if (write) {
			printf("<expressao simples> ");
			_escrever(SAIDA, "<expressao simples> ");
		}
		return true;
	} else {
		if (error) {
			printf("<ERRO SINTATICO,expressao simples> ");
			_escrever(SAIDA, "<ERRO SINTATICO,expressao simples> ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <relacao>
bool relacao(bool write, bool error){
	if (relacao_igual(false,false)){
		if (write) {
			printf("<relacao,eq> ");
			_escrever(SAIDA, "<relacao,eq> ");
		}
		return true;
	} else if (relacao_menor(false,false)) {
		if (write) {
			printf("<relacao,sm> ");
			_escrever(SAIDA, "<relacao,sm> ");
		}
		return true;
	} else if (relacao_maior(false,false)) {
		if (write) {
			printf("<relacao,bg> ");
			_escrever(SAIDA, "<relacao,bg> ");
		}
		return true;
	} else if (relacao_menor_igual(false,false)) {
		if (write) {
			printf("<relacao,smeq> ");
			_escrever(SAIDA, "<relacao,smeq> ");
		}
		return true;
	} else if (relacao_maior_igual(false,false)) {
		if (write) {
			printf("<relacao,bgeq> ");
			_escrever(SAIDA, "<relacao,bgeq> ");
		}
		return true;
	} else if (relacao_diferente(false,false)) {
		if (write) {
			printf("<relacao,dif> ");
			_escrever(SAIDA, "<relacao,dif> ");
		}
		return true;
	} else {
		if (error) {
			printf("<ERRO SINTATICO,relacao> ");
			_escrever(SAIDA, "<ERRO SINTATICO,relacao> ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <expressao>
bool expressao(bool write, bool error){
	exp_simples:
	if (expressao_simples(false,false)){
		if (relacao(true,false)) {
			goto exp_simples;
		} else {
			if (write) {
				printf("<expressao> ");
				_escrever(SAIDA, "<expressao> ");
			}
			return true;
		}
	} else {
		if (error) {
			printf("<ERRO SINTATICO,expressao> ");
			_escrever(SAIDA, "<ERRO SINTATICO,expressao> ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <comando repetitivo>
bool comando_repetitivo(bool write, bool error){
	if (enquanto(true,false)) {
		if (parenteses_esquerda(true,false)) {
			if (expressao(false,false)) {
				if (parenteses_direita(true,false)) {
					if (faca(true,false)) {
						if (comando_composto(false,false)){
							if (fimenquanto(true,false)) {
								if (write) {
   									printf("<comando repetitivo> ");
									_escrever(SAIDA, "<comando repetitivo> ");
								}
								return true;
							}
						}
					}
				}
			}
		}
	}
	if (error) {
   		printf("<ERRO SINTATICO,comando repetitivo> ");
		_escrever(SAIDA, "<ERRO SINTATICO,comando repetitivo> ");
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <comando condicional>
bool comando_condicional(bool write, bool error){
	if (se(true,false)) {
		if (parenteses_esquerda(true,false)) {
			if (expressao(false,false)) {
				if (parenteses_direita(true,false)) {
					if (entao(true,false)) {
						if (comando_composto(false,false)){
							if (senao(true,false)) {
								if (!comando_composto(false,false)){
									if (error) {
		   								printf("<ERRO SINTATICO,comando condicional> ");
										_escrever(SAIDA, "<ERRO SINTATICO,comando condicional> ");
									}
									return false;
								}	
							}
							if (fimse(true,false)) {
								if (write) {
   									printf("<comando condicional> ");
									_escrever(SAIDA, "<comando condicional> ");
								}
								return true;
							}
						}
					}
				}
			}
		}
	}
	if (error) {
   		printf("<ERRO SINTATICO,comando condicional> ");
		_escrever(SAIDA, "<ERRO SINTATICO,comando condicional> ");
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <lista de parametros>
bool lista_de_parametros(bool write, bool error){
	if (parenteses_esquerda(true,false)) {
		param: if (identificador(true,false) || numero(true,false) || boolean(true,false)) {
			if (virgula(true,false)){
				goto param;
			} else if (parenteses_direita(true,false)) {
				if (write) {
   					printf("<lista de parametros> ");
					_escrever(SAIDA, "<lista de parametros> ");
				}
				return true;
			}
		}
	}
	if (error) {
   		printf("<ERRO SINTATICO,lista de parametros> ");
		_escrever(SAIDA, "<ERRO SINTATICO,lista de parametros> ");
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <chamada de procedimento>
bool chamada_de_procedimento(bool write, bool error){
	if ((identificador(true,false)) && 
		(lista_de_parametros(true,false)) &&
		(ponto_e_virgula(true,false))) {
		if (write) {
   			printf("<chamada de procedimento> ");
			_escrever(SAIDA, "<chamada de procedimento> ");
		}
		return true;
	}
	if (error) {
   		printf("<ERRO SINTATICO,chamada de procedimento> ");
		_escrever(SAIDA, "<ERRO SINTATICO,chamada de procedimento> ");
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <atribuicao>
bool atribuicao(bool write, bool error){
	if (variavel(false,false)) {
		if (operador_igual(true,false)) {
			if (expressao(false,false)) {
				if (ponto_e_virgula(true,false)) {
					if (write) {
			   			printf("<atribuicao> ");
						_escrever(SAIDA, "<atribuicao> ");
					}
					return true;
				}
			}
		}
	}
	if (error) {
		printf("<ERRO SINTATICO,atribuicao> ");
		_escrever(SAIDA, "<ERRO SINTATICO,atribuicao> ");
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <comando>
bool comando(bool write, bool error){
	if (escreva(true,false)) {
		if (parenteses_esquerda(true,false)) {
			if (identificador(true,false)){
				if (parenteses_direita(true,false)) {
					if (ponto_e_virgula(true,false)) {
						if (write) {
	  							printf("<comando,escreva> ");
							_escrever(SAIDA, "<comando,escreva> ");
						}
						return true;
					}
				}
			}
		}
	} else if (comando_repetitivo(false,false)) {
			if (write) {
	  			printf("<comando,repetitivo> ");
			_escrever(SAIDA, "<comando,repetitivo> ");
		}
		return true;
	} else if (comando_condicional(false,false)) {
		if (write) {
	  			printf("<comando,condicional> ");
			_escrever(SAIDA, "<comando,condicional> ");
		}
		return true;
	} else if (atribuicao(false,false)) {
		if (write) {
   			printf("<comando,atribuicao> ");
			_escrever(SAIDA, "<comando,atribuicao> ");
		}
		return true;
	} else if (chamada_de_procedimento(false,false)){
		if (write) {
	  			printf("<comando,chamada de procedimento> ");
			_escrever(SAIDA, "<comando,chamada de procedimento> ");
		}
		return true;
	}	
	if (error) {
   		printf("<ERRO SINTATICO,comando> ");
		_escrever(SAIDA, "<ERRO SINTATICO,comando> ");
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <comando composto>
bool comando_composto(bool write, bool error){
	bool tem_um = false;
	while (comando(false,false)){
		tem_um = true;
		if (!ponto_e_virgula(true,false)) {
			if (error) {
   				printf("<ERRO SINTATICO,comando composto> ");
				_escrever(SAIDA, "<ERRO SINTATICO,comando composto> ");
			}
		}
	}
	if (tem_um) {
		if (write) {
	   		printf("<comando composto> ");
			_escrever(SAIDA, "<comando composto> ");
		}
		return true;
	} else if (error) {
   		printf("<ERRO SINTATICO,comando composto> ");
		_escrever(SAIDA, "<ERRO SINTATICO,comando composto> ");
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <parametro formal>
bool parametro_formal(bool write, bool error){
	if ((tipo(true,false)) &&
		(dois_pontos(true,false))) {
		if (identificador(true,false)) {
			if (write) {
	   			printf("<parametro formal> ");
				_escrever(SAIDA, "<parametro formal> ");
			}
			return true;
		}
	}
	if (error) {
   		printf("<ERRO SINTATICO,parametro formal> ");
		_escrever(SAIDA, "<ERRO SINTATICO,parametro formal> ");
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <parametros formais>
bool parametros_formais(bool write, bool error){
	while (parametro_formal(false,false)){
		if (!virgula(true,false)) {
			break;
		}
	}
	if (write) {
		printf("<parametros formais> ");
		_escrever(SAIDA, "<parametros formais> ");
	}
	return true;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <declaracao de procedimento>
bool declaracao_de_procedimento(bool write, bool error){
	if (procedimento(true,false)) {
		if ((identificador(true,false)) &&
			(parenteses_esquerda(true,false))) {
			if ((parametros_formais(false,false)) &&
				(parenteses_direita(true,false))) {
				printf("\n");
				_escrever(SAIDA, "\n");
				if (bloco(false,false)) {
					if (fimprocedimento(true,false)) {
						if (write) {
				   			printf("<declaracao de procedimento> ");
							_escrever(SAIDA, "<declaracao de procedimento> ");
						}
						return true;
					}
				}
			}
		}
	}
	if (error) {
   		printf("<ERRO SINTATICO,declaracao de procedimento> ");
		_escrever(SAIDA, "<ERRO SINTATICO,declaracao de procedimento> ");
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <parte de declaracao de subrotinas>
bool parte_de_declaracoes_de_subrotinas(bool write, bool error){
	while (declaracao_de_procedimento(false,false)){
		if (!ponto_e_virgula(true,false)) {
			if (error) {
   				printf("<ERRO SINTATICO,parte de declaracao de subrotinas> ");
				_escrever(SAIDA, "<ERRO SINTATICO,parte de declaracao de subrotinas> ");
			}
			return false;
		}
	} 
	if (write) {
		printf("<parte de declaracao de subrotinas> ");
		_escrever(SAIDA, "<parte de declaracao de subrotinas> ");
	}
	return true;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <lista de identificadores>
bool lista_de_identificadores(bool write, bool error){
	bool ultimo = false;
	lista_identificador: 
	if (identificador(true,false)){
		if (!virgula(true,false)) {
			ultimo = true;
		}
		if (!ultimo) {
			goto lista_identificador;
		} else {
			if (write) {
		   		printf("<lista de identificadores> ");
				_escrever(SAIDA, "<lista de identificadores> ");
			}
			return true;
		}
	} 
	if (error) {
   		printf("<ERRO SINTATICO,lista de identificadores> ");
		_escrever(SAIDA, "<ERRO SINTATICO,lista de identificadores> ");
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <tipo>
bool tipo(bool write, bool error){
	if (inteiro(false,false)) {
		if (write) {
			printf("<tipo,inteiro> ");
			_escrever(SAIDA, "<tipo,inteiro> ");
		}
		return true;
	} else if (booleano(false,false)) {
		if (write) {
			printf("<tipo,booleano> ");
			_escrever(SAIDA, "<tipo,booleano> ");
		}
		return true;
	} else if (error) {
   		printf("<ERRO SINTATICO,tipo> ");
		_escrever(SAIDA, "<ERRO SINTATICO,tipo> ");
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <declaracao de variaveis>
bool declaracao_de_variaveis(bool write, bool error){
	if ((tipo(true,false)) &&
		(dois_pontos(true,false))) {
		if ((lista_de_identificadores(false,false)) &&
			(ponto_e_virgula(true,false))) {
			if (write) {
		  		printf("<declaracao de variaveis> ");
				_escrever(SAIDA, "<declaracao de variaveis> ");
			}
			return true;
		}
	}
	if (error) {
   		printf("<ERRO SINTATICO,declaracao de variaveis> ");
		_escrever(SAIDA, "<ERRO SINTATICO,declaracao de variaveis> ");
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <parte de declaracao de variaveis>
bool parte_de_declaracoes_de_variaveis(bool write, bool error){
	bool tem_um = false;
	while (declaracao_de_variaveis(false,false)){
		tem_um = true;
	} 
	if (tem_um){
		if (write) {
			printf("<parte de declaracao de variaveis> ");
			_escrever(SAIDA, "<parte de declaracao de variaveis> ");
		}
		return true;
	}else {
		if (error) {
   			printf("<ERRO SINTATICO,parte de declaracao de variaveis> ");
			_escrever(SAIDA, "<ERRO SINTATICO,parte de declaracao de variaveis> ");
		}
		return false;
	}
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <bloco>
bool bloco(bool write, bool error){
	parte_de_declaracoes_de_variaveis(false,false);
	parte_de_declaracoes_de_subrotinas(false,false);
	if (comando_composto(false,false)) {
		if (write) {
			printf("<bloco> ");
			_escrever(SAIDA, "<bloco> ");
		}
		return true;
	} else {
		if (error) {
			printf("<ERRO SINTATICO,bloco> ");
			_escrever(SAIDA, "<ERRO SINTATICO,bloco> ");
		}
		return true;
	}
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <programa>
bool programa(bool write, bool error){
	if (palavra_programa(true,false)) {
		if (identificador(true,false)) {
			printf("\n");
			_escrever(SAIDA, "\n");
			if ((bloco(false,false)) &&
				(fimprograma(true,false))) {
				if (write) {
   					printf("<programa> ");
					_escrever(SAIDA, "<programa> ");
				}
				return true;
			}
		}
	}
	if (error) {
   		printf("<ERRO SINTATICO,programa> ");
		_escrever(SAIDA, "<ERRO SINTATICO,programa> ");
	}
	return false;
}

// Funcao main que chama a funcao programa para inicializar a analise lexica e sintetica.
int main(){
	i = -1;
	codigo = _ler(ENTRADA);
    printf("PROGRAMA LIDO (Espacos extras, tabs e enters sao ignorados):\n\n%s\n\n\n",codigo);
    printf("TOKENS GERADOS (Lembre-se de deletar ou renomear o arquivo):\n\n");
    programa(false, true);
    printf("\n\nALUNOS RESPONSAVEIS:\n\n");
    printf("///////////////////////////////////////////////////////////////////////////////////////////////////////\n\
//////                             Guilherme Caulada - 31416489                                  //////\n\
//////                             Guilherme Wentz - 31540929                                    //////\n\
//////                             Lucas Paulosky - 31442412                                     //////\n\
///////////////////////////////////////////////////////////////////////////////////////////////////////");
    return 0;
}
