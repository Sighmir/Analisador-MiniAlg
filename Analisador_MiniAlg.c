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
////////////////////////////////////// DECLARACAO DE FUNCOES E VARIAVEIS //////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

// VARIAVEIS DO ANALISADOR SINTATICO

// Define arquivos de saida e de entrada
#define MINIALG "MiniAlg.txt"
#define LEXICO "Lexico.txt"
#define SINTATICO "Sintatico.txt"

// Declara variaveis globais necessarias
char **tokens;
int n_tokens;
int i_tokens = -1;

// Declara funcoes que precisam ser declaradas
bool expressao_simples();
bool comando_composto();
bool bloco();

///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// FUNCOES DO ANALISADOR //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

// Funcao que le o arquivo do codigo
char * lerCodigo(char *nome) {
    FILE *arquivo = fopen(nome, "r");
    char *codigo;
    size_t n = 0;
    int c, last;

    if (arquivo == NULL) return NULL;
    fseek(arquivo, 0, SEEK_END);
    int tam = ftell(arquivo);
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

// Funcao que conta quantidade de linhas em um arquivo
int countLines(char *nome) {
    FILE *arquivo = fopen(nome, "r");
	int lines = 0;
	char c;
	while (!feof(arquivo))
	{
		c = fgetc(arquivo);
		if (c == '\n')
		{
			lines++;
		}
	}
	fclose(arquivo);
	return lines;
}

// Funcao que le o arquivo de tokens
char ** lerTokens(char *nome) {
	n_tokens = countLines(nome);
    FILE *arquivo = fopen(nome, "r");
	size_t n = 0;
	ssize_t read;
	int i, j = 0, k = 0;
	char c;

    if (arquivo == NULL) return NULL;
	tokens = (char **)malloc(n_tokens * sizeof(char *));
	
	for (i = 0; i < n_tokens; i++) {
		tokens[i] = (char *)malloc(255 * sizeof(char));
		k = 0;
		while ((c = fgetc(arquivo)) != EOF) {
			if (c == '\n')
			{
				break;
			} else if (c != ' ' && c != '\t' && c != 0){
        		(tokens[i])[k++] = (char)c;
			}
    	}
	}

    fclose(arquivo);

    return tokens;
}

// Funcao que escreve em um arquivo
void escrever(char *nome, char *texto)
{
	FILE *arquivo = fopen(nome, "a");

	fprintf(arquivo, texto);
	fclose(arquivo);
}

// Funcao que limpa um arquivo
void limpar(char *nome)
{
	FILE *arquivo = fopen(nome, "w");

	fprintf(arquivo, "");
	fclose(arquivo);
}

// Funcao que deleta o ultimo char de um char*
char* deleteLastChar(char* word)
{
    int i = 0;
    while(word[i] != '\0')
    {
        i++;
         
    }
    word[i-1] = '\0';
    return word;
}

// Divide um token dado um separador, no caso ,
char **splitToken(char *string, int *num, char *sep)
{
	char *pch;
	char **out = 0;
	int i = 0;
	if (strcmp(string,sep) != 0) {
		pch = strtok(string, sep);

		while (pch != 0)
		{
			out = realloc(out, (i + 1) * sizeof(char *));
			out[i] = malloc(strlen(pch) + 1);
			strcpy(out[i], pch);
			++i;
			pch = strtok(NULL, sep);
		}
		if (i > 1) {
			sprintf(string, "%s,%s", out[0], out[1]);
		} else {
			sprintf(string, "%s", out[0]);
		}
	} else {
		out = realloc(out, (i + 1) * sizeof(char *));
		out[i] = malloc(strlen(sep) + 1);
		strcpy(out[i], sep);
		++i;
	}
	*num = i;
	return out;
}

// Funcao que verifica o proximo token sem consumi-lo.
bool lookahead(char *token){
	int num = 0;
	char *tk = tokens[i_tokens+1];
	char **spt = splitToken(tk, &num, ",");
	if (strcmp(tk,token) == 0) {
		spt[0] = tk;
	}
	if (strcmp(token, spt[0]) == 0) {
		return true;
	} else {
		return false;
	}
}

// Funcao que verifica o proximo token consumindo-o.
bool match(char *token){
	int num = 0;
	char *tk = tokens[i_tokens+1];
	char * aux = (char *) malloc(255 * sizeof(char));
	char **spt = splitToken(tk, &num, ","); // Tratamento para argumentos do token Ex: "identificador,correto" => ["identificador","correto"]
	if (strcmp(tk,token) == 0) {
		spt[0] = tk;
	}
	if (strcmp(token, spt[0]) == 0) {
		if (num > 1) {
			sprintf(aux, "%s,%s\n", spt[0], spt[1]);
		} else {
			sprintf(aux, "%s\n", spt[0]);
		}
		escrever(SINTATICO, aux);
		printf("%s",aux);
		i_tokens++;
		return true;
	} else {
		sprintf(aux, "ERRO SINTATICO,%s\n", token);
		printf("%s",aux);
		return false;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// ANALISADOR LEXICO //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

// Funcao do analisador lexico que representa o automato, utilizando goto
bool analisadorLexico(char *input, char *output){
	limpar(output);
	char *codigo = lerCodigo(input);
	char *palavra = (char *)malloc(255 * sizeof(char));
	printf("PROGRAMA LIDO (Espacos extras, tabs e enters sao ignorados):\n\n%s\n\n\n", codigo);
	printf("GERANDO TOKENS:\n\n");
	int i = 0;
	int j = 0;
q0:
	j = 0;
	memset(palavra, 0, 255);
	palavra[j++] = codigo[i];
	if (codigo[i] == ';') {
		i++;
		goto q129;
	} else if (codigo[i] == ':') {
		i++;
		goto q129;
	} else if (codigo[i] == ',') {
		i++;
		goto q129;
	} else if (codigo[i] == '(') {
		i++;
		goto q129;
	} else if (codigo[i] == ')') {
		i++;
		goto q129;
	} else if (codigo[i] == '<') {
		i++;
		goto q133;
	} else if (codigo[i] == '>') {
		i++;
		goto q134;
	} else if (codigo[i] == '=') {
		i++;
		goto q135;
	} else if (codigo[i] == 'v') {
		i++;
		goto q106;
	} else if (codigo[i] == 'b') {
		i++;
		goto q97;
	} else if (codigo[i] == 'i') {
		i++;
		goto q89;
	} else if (codigo[i] == 's') {
		i++;
		goto q82;
	} else if (codigo[i] == 'p') {
		i++;
		goto q1;
	} else if (codigo[i] == 'f') {
		i++;
		goto q20;
	} else if (codigo[i] == 'e') {
		i++;
		goto q62;
	} else if (codigo[i] == 'd') {
		i++;
		goto q121;
	} else if (codigo[i] == 'm') {
		i++;
		goto q125;
	} else if (
		codigo[i] == 'a' || codigo[i] == 'A' ||
		/* codigo[i] == 'b' || */ codigo[i] == 'B' ||
		codigo[i] == 'c' || codigo[i] == 'C' ||
		/* codigo[i] == 'd' || */ codigo[i] == 'D' ||
		codigo[i] == 'e' || codigo[i] == 'E' ||
		/* codigo[i] == 'f' || */ codigo[i] == 'F' ||
		codigo[i] == 'g' || codigo[i] == 'G' ||
		codigo[i] == 'h' || codigo[i] == 'H' ||
		/* codigo[i] == 'i' || */ codigo[i] == 'I' ||
		codigo[i] == 'j' || codigo[i] == 'J' ||
		codigo[i] == 'k' || codigo[i] == 'K' ||
		codigo[i] == 'l' || codigo[i] == 'L' ||
		/* codigo[i] == 'm' || */ codigo[i] == 'M' ||
		codigo[i] == 'n' || codigo[i] == 'N' ||
		codigo[i] == 'o' || codigo[i] == 'O' ||
		/* codigo[i] == 'p' || */ codigo[i] == 'P' ||
		codigo[i] == 'q' || codigo[i] == 'Q' ||
		codigo[i] == 'r' || codigo[i] == 'R' ||
		/* codigo[i] == 's' || */ codigo[i] == 'S' ||
		codigo[i] == 't' || codigo[i] == 'T' ||
		codigo[i] == 'u' || codigo[i] == 'U' ||
		/* codigo[i] == 'v' || */ codigo[i] == 'V' ||
		codigo[i] == 'w' || codigo[i] == 'W' ||
		codigo[i] == 'x' || codigo[i] == 'X' ||
		codigo[i] == 'y' || codigo[i] == 'Y' ||
		codigo[i] == 'z' || codigo[i] == 'Z'
	) {
		i++;
		goto q117;
	} else if (
		codigo[i] == '0' ||
		codigo[i] == '1' ||
		codigo[i] == '2' ||
		codigo[i] == '3' ||
		codigo[i] == '4' ||
		codigo[i] == '5' ||
		codigo[i] == '6' || 
		codigo[i] == '7' ||
		codigo[i] == '8' ||
		codigo[i] == '9'
	) {
		i++;
		goto q119;
	} else if (codigo[i] == '+') {
		i++;
		goto q129;
	} else if (codigo[i] == '-') {
		i++;
		goto q129;
	} else if (codigo[i] == '/') {
		i++;
		goto q157;
	} else if (i == strlen(codigo)) {
		return true;
	} else {
		char * aux = (char *) malloc(255 * sizeof(char));
		sprintf(aux, "ERRO LEXICO,%s\n", deleteLastChar(palavra));
		printf("%s",aux);
		escrever(output, aux);
		return false;
	}
q1:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'r') {
		i++;
		goto q2;
	} else {
		goto q117;
	}
q2:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'o') {
		i++;
		goto q3;
	} else {
		goto q117;
	}
q3:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'g') {
		i++;
		goto q4;
	} else if (codigo[i] == 'c') {
		i++;
		goto q10;
	} else {
		goto q117;
	}
q4:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'r') {
		i++;
		goto q5;
	} else {
		goto q117;
	}
q5:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'a') {
		i++;
		goto q6;
	} else {
		goto q117;
	}
q6:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'm') {
		i++;
		goto q7;
	} else {
		goto q117;
	}
q7:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'a') {
		i++;
		goto q9;
	} else {
		goto q117;
	}
q9:
	palavra[j++] = codigo[i];
	if (codigo[i] == ' ') {
		sprintf(palavra, "%s\n", palavra);
		printf("%s",palavra);
		escrever(output, palavra);
		i++;
		goto q0;
	} else {
		goto q117;
	}
q10:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'e') {
		i++;
		goto q11;
	} else {
		goto q117;
	}
q11:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'd') {
		i++;
		goto q12;
	} else {
		goto q117;
	}
q12:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'i') {
		i++;
		goto q13;
	} else {
		goto q117;
	}
q13:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'm') {
		i++;
		goto q14;
	} else {
		goto q117;
	}
q14:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'e') {
		i++;
		goto q15;
	} else {
		goto q117;
	}
q15:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'n') {
		i++;
		goto q16;
	} else {
		goto q117;
	}
q16:
	palavra[j++] = codigo[i];
	if (codigo[i] == 't') {
		i++;
		goto q17;
	} else {
		goto q117;
	}
q17:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'o') {
		i++;
		goto q9;
	} else {
		goto q117;
	}
q82:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'e') {
		i++;
		goto q83;
	} else {
		goto q117;
	}
q83:
	palavra[j++] = codigo[i];
	if (codigo[i] == ' ') {
		goto q9;
	} else if (codigo[i] == 'n') {
		i++;
		goto q85;
	} else {
		goto q117;
	}
q85:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'a') {
		i++;
		goto q86;
	} else {
		goto q117;
	}
q86:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'o') {
		i++;
		goto q9;
	} else {
		goto q117;
	}
q20:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'a') {
		i++;
		goto q54;
	} else if (codigo[i] == 'i') {
		i++;
		goto q21;
	} else {
		goto q117;
	}
q54:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'c') {
		i++;
		goto q55;
	} else if (codigo[i] == 'l') {
		i++;
		goto q58;
	} else {
		goto q117;
	}
q55:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'a') {
		i++;
		goto q9;
	} else {
		goto q117;
	}
q58:
	palavra[j++] = codigo[i];
	if (codigo[i] == 's') {
		i++;
		goto q59;
	} else {
		goto q117;
	}
q59:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'o') {
		i++;
		goto q9;
	} else {
		goto q117;
	}
q21:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'm') {
		i++;
		goto q22;
	} else {
		goto q117;
	}
q22:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'p') {
		i++;
		goto q1;
	} else if (codigo[i] == 's') {
		i++;
		goto q51;
	} else if (codigo[i] == 'e') {
		i++;
		goto q42;
	} else {
		goto q117;
	}
q51:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'e') {
		i++;
		goto q9;
	} else {
		goto q117;
	}
q42:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'n') {
		i++;
		goto q43;
	} else {
		goto q117;
	}
q43:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'q') {
		i++;
		goto q44;
	} else {
		goto q117;
	}
q44:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'u') {
		i++;
		goto q45;
	} else {
		goto q117;
	}
q45:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'a') {
		i++;
		goto q46;
	} else {
		goto q117;
	}
q46:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'n') {
		i++;
		goto q47;
	} else {
		goto q117;
	}
q47:
	palavra[j++] = codigo[i];
	if (codigo[i] == 't') {
		i++;
		goto q48;
	} else {
		goto q117;
	}
q48:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'o') {
		i++;
		goto q9;
	} else {
		goto q117;
	}
q62:
	palavra[j++] = codigo[i];
	if (codigo[i] == 's') {
		i++;
		goto q71;
	} else if (codigo[i] == 'n') {
		i++;
		goto q63;
	} else {
		goto q117;
	}
q71:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'c') {
		i++;
		goto q72;
	} else {
		goto q117;
	}
q72:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'r') {
		i++;
		goto q73;
	} else {
		goto q117;
	}
q73:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'e') {
		i++;
		goto q74;
	} else {
		goto q117;
	}
q74:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'v') {
		i++;
		goto q75;
	} else {
		goto q117;
	}
q75:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'a') {
		i++;
		goto q9;
	} else {
		goto q117;
	}
q63:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'q') {
		i++;
		goto q44;
	} else if (codigo[i] == 't') {
		i++;
		goto q78;
	} else {
		goto q117;
	}
q78:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'a') {
		i++;
		goto q79;
	} else {
		goto q117;
	}
q79:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'o') {
		i++;
		goto q9;
	} else {
		goto q117;
	}
q119:
	palavra[j++] = codigo[i];
	if (
		codigo[i] == '0' ||
		codigo[i] == '1' ||
		codigo[i] == '2' ||
		codigo[i] == '3' ||
		codigo[i] == '4' ||
		codigo[i] == '5' ||
		codigo[i] == '6' ||
		codigo[i] == '7' ||
		codigo[i] == '8' ||
		codigo[i] == '9'
	) {
		i++;
		goto q119;
	} else if (codigo[i] == ' ') {
		char * aux = (char *) malloc(255 * sizeof(char));
		sprintf(aux, "numero,%s\n", palavra);
		printf("%s",aux);
		escrever(output, aux);
		i++;
		goto q0;
	} else {
		char * aux = (char *) malloc(255 * sizeof(char));
		sprintf(aux, "ERRO LEXICO,%s\n", deleteLastChar(palavra));
		printf("%s",aux);
		escrever(output, aux);
		return false;
	}
q121:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'i') {
		i++;
		goto q122;
	} else {
		goto q117;
	}
q122:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'v') {
		i++;
		goto q9;
	} else {
		goto q117;
	}
q125:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'u') {
		i++;
		goto q126;
	} else {
		goto q117;
	}
q126:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'l') {
		i++;
		goto q9;
	} else {
		goto q117;
	}
q129:
	palavra[j++] = codigo[i];
	if (codigo[i] == ' ') {
		sprintf(palavra, "%s\n", palavra);
		printf("%s",palavra);
		escrever(output, palavra);
		i++;
		goto q0;
	} else {
		char * aux = (char *) malloc(255 * sizeof(char));
		sprintf(aux, "ERRO LEXICO,%s\n", deleteLastChar(palavra));
		printf("%s",aux);
		escrever(output, aux);
		return false;
	}
q157:
	palavra[j++] = codigo[i];
	if (codigo[i] == '*') {
		i++;
		goto q164;
	} else {
		char * aux = (char *) malloc(255 * sizeof(char));
		sprintf(aux, "ERRO LEXICO,%s\n", deleteLastChar(palavra));
		printf("%s",aux);
		escrever(output, aux);
		return false;
	}
q89:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'n') {
		i++;
		goto q90;
	} else {
		goto q117;
	}
q90:
	palavra[j++] = codigo[i];
	if (codigo[i] == 't') {
		i++;
		goto q91;
	} else {
		goto q117;
	}
q91:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'e') {
		i++;
		goto q92;
	} else {
		goto q117;
	}
q92:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'i') {
		i++;
		goto q93;
	} else {
		goto q117;
	}
q93:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'r') {
		i++;
		goto q94;
	} else {
		goto q117;
	}
q94:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'o') {
		i++;
		goto q163;
	} else {
		goto q117;
	}
q97:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'o') {
		i++;
		goto q98;
	} else {
		goto q117;
	}
q98:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'o') {
		i++;
		goto q99;
	} else {
		goto q117;
	}
q99:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'l') {
		i++;
		goto q100;
	} else {
		goto q117;
	}
q100:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'e') {
		i++;
		goto q101;
	} else {
		goto q117;
	}
q101:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'a') {
		i++;
		goto q102;
	} else {
		goto q117;
	}
q102:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'n') {
		i++;
		goto q103;
	} else {
		goto q117;
	}
q103:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'o') {
		i++;
		goto q163;
	} else {
		goto q117;
	}
q106:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'e') {
		i++;
		goto q107;
	} else {
		goto q117;
	}
q107:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'r') {
		i++;
		goto q108;
	} else {
		goto q117;
	}
q108:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'd') {
		i++;
		goto q109;
	} else {
		goto q117;
	}
q109:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'a') {
		i++;
		goto q110;
	} else {
		goto q117;
	}
q110:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'd') {
		i++;
		goto q111;
	} else {
		goto q117;
	}
q111:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'e') {
		i++;
		goto q112;
	} else {
		goto q117;
	}
q112:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'i') {
		i++;
		goto q113;
	} else {
		goto q117;
	}
q113:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'r') {
		i++;
		goto q114;
	} else {
		goto q117;
	}
q114:
	palavra[j++] = codigo[i];
	if (codigo[i] == 'o') {
		i++;
		goto q9;
	} else {
		goto q117;
	}
	
q117:
	palavra[j++] = codigo[i];
	if (
		codigo[i] == 'a' || codigo[i] == 'A' ||
		codigo[i] == 'b' || codigo[i] == 'B' ||
		codigo[i] == 'c' || codigo[i] == 'C' ||
		codigo[i] == 'd' || codigo[i] == 'D' ||
		codigo[i] == 'e' || codigo[i] == 'E' ||
		codigo[i] == 'f' || codigo[i] == 'F' ||
		codigo[i] == 'g' || codigo[i] == 'G' ||
		codigo[i] == 'h' || codigo[i] == 'H' ||
		codigo[i] == 'i' || codigo[i] == 'I' ||
		codigo[i] == 'j' || codigo[i] == 'J' ||
		codigo[i] == 'k' || codigo[i] == 'K' ||
		codigo[i] == 'l' || codigo[i] == 'L' ||
		codigo[i] == 'm' || codigo[i] == 'M' ||
		codigo[i] == 'n' || codigo[i] == 'N' ||
		codigo[i] == 'o' || codigo[i] == 'O' ||
		codigo[i] == 'p' || codigo[i] == 'P' ||
		codigo[i] == 'q' || codigo[i] == 'Q' ||
		codigo[i] == 'r' || codigo[i] == 'R' ||
		codigo[i] == 's' || codigo[i] == 'S' ||
		codigo[i] == 't' || codigo[i] == 'T' ||
		codigo[i] == 'u' || codigo[i] == 'U' ||
		codigo[i] == 'v' || codigo[i] == 'V' ||
		codigo[i] == 'w' || codigo[i] == 'W' ||
		codigo[i] == 'x' || codigo[i] == 'X' ||
		codigo[i] == 'y' || codigo[i] == 'Y' ||
		codigo[i] == 'z' || codigo[i] == 'Z'
	) {
		i++;
		goto q117;
	} else if (codigo[i] == ' ') {
		char * aux = (char *) malloc(255 * sizeof(char));
		sprintf(aux, "identificador,%s\n", palavra);
		printf("%s",aux);
		escrever(output, aux);
		i++;
		goto q0;
	} else {
		char * aux = (char *) malloc(255 * sizeof(char));
		sprintf(aux, "ERRO LEXICO,%s\n", deleteLastChar(palavra));
		printf("%s",aux);
		escrever(output, aux);
		return false;
	}
q133:
	palavra[j++] = codigo[i];
	if (codigo[i] == '=') {
		i++;
		goto q129;
	} else if (codigo[i] == '>') {
		i++;
		goto q129;
	} else if (codigo[i] == ' ') {
		sprintf(palavra, "%s\n", palavra);
		printf("%s",palavra);
		escrever(output, palavra);
		i++;
		goto q0;
	} else {
		char * aux = (char *) malloc(255 * sizeof(char));
		sprintf(aux, "ERRO LEXICO,%s\n", deleteLastChar(palavra));
		printf("%s",aux);
		escrever(output, aux);
		return false;
	}
q134:
	palavra[j++] = codigo[i];
	if (codigo[i] == '=') {
		i++;
		goto q129;
	} else if (codigo[i] == ' ') {
		sprintf(palavra, "%s\n", palavra);
		printf("%s",palavra);
		escrever(output, palavra);
		i++;
		goto q0;
	} else {
		char * aux = (char *) malloc(255 * sizeof(char));
		sprintf(aux, "ERRO LEXICO,%s\n", deleteLastChar(palavra));
		printf("%s",aux);
		escrever(output, aux);
		return false;
	}
q135:
	palavra[j++] = codigo[i];
	if (codigo[i] == '=') {
		i++;
		goto q129;
	} else if (codigo[i] == ' ') {
		sprintf(palavra, "%s\n", palavra);
		printf("%s",palavra);
		escrever(output, palavra);
		i++;
		goto q0;
	} else {
		char * aux = (char *) malloc(255 * sizeof(char));
		sprintf(aux, "ERRO LEXICO,%s\n", deleteLastChar(palavra));
		printf("%s",aux);
		escrever(output, aux);
		return false;
	}
q163:
	palavra[j++] = codigo[i];
	if (codigo[i] == ' ') {
		char * aux = (char *) malloc(255 * sizeof(char));
		sprintf(aux, "tipo,%s\n", palavra);
		printf("%s", aux);
		escrever(output, aux);
		i++;
		goto q0;
	} else {
		goto q117;
	}
q164:
	if (codigo[i] == '*') {
		i++;
		if (codigo[i] == '/') {
			i++;
			if (codigo[i] == ' ') {
				i++;
				goto q0;
			}
		}
	}
	i++;
	goto q164;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// ANALISADOR SINTATICO ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <fator>
bool fator(){
	if (lookahead("numero")) {
		match("numero");
		return true;
	} else if (lookahead("verdadeiro")) {
		match("verdadeiro");
		return true;
	} else if (lookahead("falso")) {
		match("falso");
		return true;
	} else if (lookahead("(")) {
		match("(");
		if (expressao_simples()) {
			if (match(")")) {
				return true;
			}
		}
	} else if (lookahead("identificador")) {
		match("identificador");
		return true;
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <termo>
bool termo(){
	fator:
	if (fator()) {
		if (lookahead("mul")) {
			match("mul");
			goto fator;
		}else if (lookahead("div")) {
			match("div");
			goto fator;
		}
		return true;
	} 
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <expressao simples>
bool expressao_simples(){
	if (lookahead("+")) {
		match("+");
	} else if (lookahead("-")) {
		match("-");
	}
	if (termo()) {
		while(lookahead("+") || lookahead("-")){
			if (lookahead("+")) {
				match("+");
				termo();
			} else if (lookahead("-")) {
				match("-");
				termo();
			}
		}
		return true;
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <relacao>
bool relacao(){
	if (lookahead("==")){
		match("==");
		return true;
	} else if (lookahead("<")) {
		match("<");
		return true;
	} else if (lookahead(">")) {
		match(">");
		return true;
	} else if (lookahead("<=")) {
		match("<=");
		return true;
	} else if (lookahead(">=")) {
		match(">=");
		return true;
	} else if (lookahead("<>")) {
		match("<>");
		return true;
	} 
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <expressao>
bool expressao(){
	if (expressao_simples()){
		if (relacao()) {
			if (expressao_simples()) {
				return true;
			}
		}
		return true;
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <comando repetitivo>
bool comando_repetitivo(){
	if (lookahead("enquanto")) {
		match("enquanto");
		if (match("(")) {
			if (expressao()) {
				if (match(")")) {
					if (match("faca")) {
						if (comando_composto()){
							if (match("fimenquanto")) {
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <comando condicional>
bool comando_condicional(){
	if (lookahead("se")) {
		match("se");
		if (match("(")) {
			if (expressao()) {
				if (match(")")) {
					if (match("entao")) {
						if (comando_composto()){
							if (lookahead("senao")) {
								match("senao");
								if (!comando_composto()){
									return false;
								}	
							}
							if (match("fimse")) {
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <lista de parametros>
bool lista_de_parametros(){
	if (match("(")) {
		param:
		if (lookahead("identificador")) {
			match("identificador");
			match(",");
			goto param;
		} else if (lookahead("numero")) {
			match("numero");
			match(",");
			goto param;
		} else if (lookahead("falso")) {
			match("falso");
			match(",");
			goto param;
		} else if (lookahead("verdadeiro")) {
			match("verdadeiro");
			match(",");
			goto param;
		} else if (lookahead(")")) {
			match(")");
			return true;
		}
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <chamada de procedimento>
bool chamada_de_procedimento(){
	if (lookahead("identificador")){
		if (match("identificador")) {
			if (lista_de_parametros()) {
				if (match(";")) {
					return true;
				}
			}
		}
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <atribuicao>
bool atribuicao(){
	if (lookahead("identificador")){
		if (match("identificador")) {
			if (match("=")) {
				if (expressao()) {
					if (match(";")) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <comando>
bool comando(){
	if (lookahead("escreva")) {
		if (match("escreva")) {
			if (match("(")) {
				if (match("identificador")){
					if (match(")")) {
						if (match(";")) {
							return true;
						}
					}
				}
			}
		}
	} else if (comando_repetitivo()) {
		return true;
	} else if (comando_condicional()) {
		return true;
	} else if (atribuicao()) {
		return true;
	} else if (chamada_de_procedimento()){
		return true;
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <comando composto>
bool comando_composto(){
	if (comando()) {
		while (comando()){
			continue;
		} 
		return true;
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <parametro formal>
bool parametro_formal(){
	if (match("tipo")) {
		if (match(":")) {
			if (match("identificador")) {
				return true;
			}
		}
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <parametros formais>
bool parametros_formais(){
	if (match("(")) {
		if (lookahead(")")) {
			match(")");
			return true;
		} else if (parametro_formal()){
			while (lookahead(",")) {
				match(",");
				parametro_formal();
			}
			if (match(")")) {
				return true;
			}
		}
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <declaracao de procedimento>
bool declaracao_de_procedimento(){
	if (lookahead("procedimento")) {
		match("procedimento");
		if (match("identificador")) {
			if (parametros_formais()) {
				if (bloco()) {
					if (match("fimprocedimento")) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <parte de declaracao de subrotinas>
bool parte_de_declaracoes_de_subrotinas(){
	while (declaracao_de_procedimento()){
		continue;
	} 
	return true;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <lista de identificadores>
bool lista_de_identificadores(){
	if (match("identificador")){
		while (lookahead(",")) {
			match(",");
			match("identificador");
		}
		if (match(";")) {
			return true;
		}
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <declaracao de variaveis>
bool declaracao_de_variaveis(){
	if (lookahead("tipo")) {
		if (match("tipo")) {
			if (match(":")) {
				if (lista_de_identificadores()) {
					return true;
				}
			}
		}
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <parte de declaracao de variaveis>
bool parte_de_declaracoes_de_variaveis(){
	while (declaracao_de_variaveis()){
		continue;
	} 
	return true;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <bloco>
bool bloco(){
	if (parte_de_declaracoes_de_variaveis()) {
		if (parte_de_declaracoes_de_subrotinas()) {
			if (comando_composto()) {
				return true;
			}
		}
	}
	return false;
}

// Funcao que verifica se a proxima sequencia sintatica existente equivale a <programa>
bool programa(){
	if (match("programa")) {
		if (match("identificador")) {
			if ((bloco())) {
				if (match("fimprograma")) {
					return true;
				}
			}
		}
	}
	return false;
}

// Funcao que imprime lista de tokens lidos no terminal
void printTokens() {
	int i;
	for (i = 0; i < n_tokens; i++) {
		printf("Token %d: %s\n", i, tokens[i]);
	}
}

// Funcao do analisador sintatico que retorna o resultado da analise
bool analisadorSintatico(char *input, char *output){
	limpar(output);
	printf("\n\n\nINICIANDO ANALISE SINTATICA\n");
	tokens = lerTokens(input);
	printf("\nTOKENS LIDOS:\n\n");
	printTokens();
	printf("\nGERANDO TOKENS:\n\n");
	return programa();
}

void alunosResponsaveis(){
	printf("\n\nALUNOS RESPONSAVEIS:\n\n");
	printf("///////////////////////////////////////////////////////////////////////////////////////////////////////\n\
//////                             Guilherme Caulada - 31416489                                  //////\n\
//////                             Guilherme Wentz - 31540929                                    //////\n\
//////                             Lucas Paulosky - 31442412                                     //////\n\
///////////////////////////////////////////////////////////////////////////////////////////////////////");
}

// Funcao main que chama as funcaoes para inicializar a analise lexica e sintatica.
int main(){
	if (analisadorLexico(MINIALG, LEXICO)) {
		analisadorSintatico(LEXICO, SINTATICO);
	}
	alunosResponsaveis();
	return 0;
}
