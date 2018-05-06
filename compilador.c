//Andrey Ryuki Imaguma - TIA 31540406
//Daniela de Freitas Lugli - TIA 31512585
//Rafael Carmo da Silva - TIA 31581560
//Wendell de Camillo Duque - TIA 31580475


#include <stdio.h>
#include <ctype.h>

#define MAX_VAR_NAME_SIZE 100
#define MAX_VAR_IDS 1000
#define true 1
#define false 0

FILE *fpReadCode, *fpWriteCode, *fpReadCode, *fpRead, *fpWrite;

char c;
char lookahead;
int rollback = false;
char currentWord[MAX_VAR_NAME_SIZE];
int currentWordIndex = 0;
char **varIds;
int currentVarId = 0;

main() 
{	
	fpReadCode = fopen("code.txt", "r");
    fpWriteCode = fopen("cleanCode.txt", "w+");
    fpRead = fopen("cleanCode.txt", "r");
    fpWrite = fopen("tokens.txt", "w+");
        
	int state = 0;
	
	cleanCode();
	
	c = ' ';
	lookahead = fgetc(fpRead);
	
	varIds = malloc(MAX_VAR_NAME_SIZE*MAX_VAR_IDS);
		
	while (true)
	{			
		if (rollback == false)
		{
			c = lookahead;
			lookahead = fgetc(fpRead);
		}
		else
		{
			rollback = false;	
		}	
		
		if (state != 0)
		{			
				currentWord[currentWordIndex++] = c;
				currentWord[currentWordIndex] = '\0';
		}
		else
		{
				cleanCurrentWord();
				currentWord[0] = c;
				currentWord[1] = '\0';
				currentWordIndex = 1;
		}
		
		printf("Current word: %s\n", currentWord);
				
		switch(state)
		{
			case 0:
					 if (c == 'a') state = 1;
				else if (c == 'e')
				{
					if (isalnum(lookahead) == false)
					{
						addToken("logic-op", "e");
						state = 0;
					}
					else
					{
						state = 9;
					}				
				}
				else if (c == 'f') state = 25;
				else if (c == 'i') state = 49;
				else if (c == 'l') state = 59;
				else if (c == 'm') state = 64;
				else if (c == 'o') state = 66;
				else if (c == 's') state = 67;
				else if (c == 'v') state = 71;				
				else if (c == '>') 
				{
					if (lookahead == '=')
					{
						state = 81;
					}
					else
					{
						addToken("comparador", "maior");
						state = 0;	
					}						
				}				
				else if (c == '<')
				{
					if (lookahead == '=')
					{
						state = 82;
					}
					else if (lookahead == '-')
					{
						state = 83;
					}
					else if (lookahead == '>')
					{
						state = 84;
					}
					else
					{
						addToken("comparador", "menor");
						state = 0;	
					}
				}
				else if (c == '=')
				{
						addToken("comparador", "igual");
						state = 0;
				}
				else if (c == '+')
				{
						addToken("arit-op", "mais");
						state = 0;
				}
				else if (c == '-')
				{
						addToken("arit-op", "menos");
						state = 0;
				}
				else if (c == '*')
				{
						addToken("arit-op", "mult");
						state = 0;
				}
				else if (c == '/')
				{
						addToken("arit-op", "div");
						state = 0;
				}
				else if (c == ',')
				{
						addToken("pontuacao", "virg");
						state = 0;
				}
				else if (c == ';') 
				{
						addToken("pontuacao", "pt-virg");
						state = 0;
				}	
				else if (c == ':') 
				{
						addToken("pontuacao", "dois-pt");
						state = 0;
				}			
				else if (c == '(')
				{
						addToken("pontuacao", "parent-abre");
						state = 0;
				}	
				else if (c == ')')
				{
						addToken("pontuacao", "parent-fecha");
						state = 0;
				}
				
				//IGNORA ESPACO EM BRANCO
				else if (c == ' ') state = 0;
				
				//NOME PROGRAMA
				else if (c == '"') state = 97;
							
				//DIGITOS
				else if (isdigit(c)) state = 98;
				
				//NOME DE VARIAVEL
				else if (isalpha(c)) state = 99;
				
				//NAO RECONHECIDO
				else writeError(c);
				break;
				
			//LETRA A
			case 1:
				if (c == 'l') state = 2;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 2:
				if (c == 'g') state = 3;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 3:
				if (c == 'o') state = 4;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 4:
				if (c == 'r') state = 5;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 5:
				if (c == 'i') state = 6;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 6:
				if (c == 't') state = 7;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 7:
				if (c == 'm') state = 8;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 8:
				if (c == 'o') 
				{
					if (isalnum(lookahead) == false)
					{
						addToken("reservado", "algoritmo");
						state = 0;
					}
					else 
					{
						rollback = true;
						state = 99;
					}
				}
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			//LETRA E
			case 9:
				if (c == 's') state = 10;
				else if (c == 'n') state = 15;
				else if (c == 'x') state = 24;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 10:
				if (c == 'c') state = 11;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 11:
				if (c == 'r') state = 12;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 12:
				if (c == 'e') state = 13;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 13:
				if (c == 'v') state = 14;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 14:
				if (c == 'a') 
				{
					if (isalnum(lookahead) == false)
					{
						addToken("reservado", "escreva");
						state = 0;
					}
					else 
				{
					rollback = true;
					state = 99;
				}
				}
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 15:
				if (c == 'q') state = 16;
				else if (c == 't') state = 21;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 16:
				if (c == 'u') state = 17;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 17:				
				if (c == 'a') state = 18;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 18:
				if (c == 'n') state = 19;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 19:
				if (c == 't') state = 20;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 20:
				if (c == 'o') 
				{
					if (isalnum(lookahead) == false)
					{
						addToken("reservado", "enquanto");
						state = 0;
					}
					else 
				{
					rollback = true;
					state = 99;
				}
				}
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 21:
				if (c == 't') state = 22;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 22:
				if (c == 'a') state = 23;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 23:
				if (c == 'o')
				{
					if (isalnum(lookahead) == false)
					{
						addToken("reservado", "entao");
						state = 0;
					}
					else 
				{
					rollback = true;
					state = 99;
				}
				}
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
			
			case 24:
				if (c == 'p')
				{
					if (isalnum(lookahead) == false)
					{
						addToken("arit-op", "exp");
						state = 0;
					}
					else 
				{
					rollback = true;
					state = 99;
				}
				}
				break;
				
			//LETRA F
			case 25:
				if (c == 'a') state = 26;
				else if (c == 'i') state = 31;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 26:
				if (c == 'l') state = 27;
				else if (c == 'c') state = 29;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 27:
				if (c == 's') state = 28;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 28:
				if (c == 'o')
				{
					if (isalnum(lookahead) == false)
					{
						addToken("reservado", "falso");
						state = 0;
					}
					else 
				{
					rollback = true;
					state = 99;
				}
				}
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 29:
				if (c == 'a')
				{
					if (isalnum(lookahead) == false)
					{
						addToken("reservado", "faca");
						state = 0;
					}
					else 
				{
					rollback = true;
					state = 99;
				}
				}
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 31:
				if (c == 'm') state = 32;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 32:
				if (c == 's') state = 33;
				else if (c == 'a') state = 34;
				else if (c == 'e') state = 42;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 33:
				if (c == 'e')
				{
					if (isalnum(lookahead) == false)
					{
						addToken("reservado", "fimse");
						state = 0;
					}
					else 
				{
					rollback = true;
					state = 99;
				}
				}
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 34:
				if (c == 'l') state = 35;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 35:
				if (c == 'g') state = 36;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 36:
				if (c == 'o') state = 37;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 37:
				if (c == 'r') state = 38;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 38:
				if (c == 'i') state = 39;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 39:
				if (c == 't') state = 40;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 40:
				if (c == 'm') state = 41;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 41:
				if (c == 'o') 
				{
					if (isalnum(lookahead) == false)
					{
						addToken("reservado", "fimalgoritmo");
						state = 0;
					}
					else 
				{
					rollback = true;
					state = 99;
				}
				}
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 42:
				if (c == 'n') state = 43;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 43:
				if (c == 'q') state = 44;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 44:
				if (c == 'u') state = 45;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 45:
				if (c == 'a') state = 46;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 46:
				if (c == 'n') state = 47;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 47:
				if (c == 't') state = 48;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 48:
				if (c == 'o') 
				{
					if (isalnum(lookahead) == false)
					{
						addToken("reservado", "fimenquanto");
						state = 0;
					}
					else 
				{
					rollback = true;
					state = 99;
				}
				}
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			// LETRA I
			case 49:
				if (c == 'n') state = 50;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 50:
				if (c == 'i') state = 51;
				if (c == 't') state = 55;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 51:
				if (c == 'c') state = 52;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 52:
				if (c == 'i') state = 53;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 53:
				if (c == 'o') 	
				{				
					if (isalnum(lookahead) == false)
					{
						addToken("reservado", "inicio");
						state = 0;
					}
					else 
				{
					rollback = true;
					state = 99;
				}
				}
				else 
				{
					rollback = true;
					state = 99;
				}
				break;				
				
			case 55:
				if (c == 'e') state = 56;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 56:
				if (c == 'i') state = 57;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 57:
				if (c == 'r') state = 58;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 58:
				if (c == 'o') 	
				{				
					if (isalnum(lookahead) == false)
					{
						addToken("reservado", "inteiro");
						state = 0;
					}
					else 
				{
					rollback = true;
					state = 99;
				}
				}
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			// LETRA L
			case 59:
				if (c == 'o') state = 60;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 60:
				if (c == 'g') state = 61;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 61:
				if (c == 'i') state = 62;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 62:
				if (c == 'c') state = 63;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 63:
				if (c == 'o') 	
				{				
					if (isalnum(lookahead) == false)
					{
						addToken("reservado", "logico");
						state = 0;
					}
					else 
				{
					rollback = true;
					state = 99;
				}
				}
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			//LETRA M
			case 64:
				if (c == 'o') state = 65;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 65:
				if (c == 'd') 	
				{				
					if (isalnum(lookahead) == false)
					{
						addToken("arit-op", "mod");
						state = 0;
					}
					else 
				{
					rollback = true;
					state = 99;
				}
				}
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			// LETRA O
			case 66:
				if (c == 'u') 	
				{				
					if (isalnum(lookahead) == false)
					{
						addToken("logic-op", "ou");
						state = 0;
					}
					else 
				{
					rollback = true;
					state = 99;
				}
				}
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			//LETRA S
			case 67:
				if (c == 'e') 	
				{				
					if (isalnum(lookahead) == false)
					{
						addToken("reservado", "se");
						state = 0;
				 	}
					else state = 68;
				}
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 68:
				if (c == 'n') state = 69;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 69:
				if (c == 'a') state = 70;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 70:
				if (c == 'o') 	
				{				
					if (isalnum(lookahead) == false)
					{
						addToken("reservado", "senao");
						state = 0;
					}
					else 
				{
					rollback = true;
					state = 99;
				}
				}
				else 
				{
					rollback = true;
					state = 99;
				}
				break;	
											
			//LETRA V
			case 71:
				if (c == 'a') state = 72;
				else if (c == 'e') state = 73;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;	
						
			case 72:
				if (c == 'r') 	
				{				
					if (isalnum(lookahead) == false)
					{
						addToken("reservado", "var");
						state = 0;
					}
					else 
				{
					rollback = true;
					state = 99;
				}
				}
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
					
			case 73:
				if (c == 'r') state = 74;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 74:
				if (c == 'd') state = 75;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 75:
				if (c == 'a') state = 76;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 76:
				if (c == 'd') state = 77;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 77:
				if (c == 'e') state = 78;
				else 
				{
					rollback = true;
					state = 99;
				}			
				break;
				
			case 78:
				if (c == 'i') state = 79;
				else 
				{
					rollback = true;
					state = 99;
				}			
				break;
				
			case 79:
				if (c == 'r') state = 80;
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
				
			case 80:
				if (c == 'o') 	
				{				
					if (isalnum(lookahead) == false)
					{
						addToken("reservado", "verdadeiro");
						state = 0;
					}
					else 
				{
					rollback = true;
					state = 99;
				}
				}
				else 
				{
					rollback = true;
					state = 99;
				}
				break;
	
				
			// MAIOR IGUAL 
			case 81:
				addToken("comparador", "maior-igual");
				state = 0;
				break;
			
			// MENOR IGUAL 
			case 82:
				addToken("comparador", "menor-igual");
				state = 0;
				break;
				
			// ATRIBUICAO
			case 83:
				addToken("comparador", "atribuicao");
				state = 0;
				break;		
				
			// DIFERENTE
			case 84:
				addToken("comparador", "diferente");
				state = 0;
				break;
				
			// STRING
			case 97:
				if (c == '"')
				{			
					addToken("string", currentWord);
					state = 0;
				}
				else state = 97;
				break;								
																
			// NUMEROS INTEIROS
			case 98:
				if(isdigit(c) == false)
				{
					rollback = true;
					addToken("num", currentWord);
					state = 0;

				}
				else if  (isdigit(lookahead) == false)
				{			

					addToken("num", currentWord);
					state = 0;
				}
				else state = 98;
				break;
								
			// NOME DE VARIAVEL
			case 99:
				if (isalnum(c) == false)
				{			
					rollback = true;
					addTokenVar("id", getId());
					state = 0;
				}
				else if (isalnum(lookahead) == false)
				{
					addTokenVar("id", getId());
					state = 0;
				}
				else state = 99;
				break;
		}
		
		//CHECA SE ARQUIVO TERMINOU
		if (feof(fpRead))
		{
			fclose(fpRead);
			fclose(fpWrite);
			exit(0);
		}
	}
}

void cleanCode()
{
	char c;
	char lookahead = fgetc(fpReadCode);
	int isComment = false;
	
	while (true)
	{
		c = lookahead;
		lookahead = fgetc(fpReadCode);		
		
		if ((c == '\r' && lookahead == '\n') || (c == ' ' && lookahead == ' '))
		{	
			fputc(' ', fpWriteCode);
			lookahead = fgetc(fpReadCode);
			isComment = false;
		}
		else if (c == '/' && lookahead == '/')
		{
			isComment = true;
		}
		else
		{
			if (c != '\n')
			{
				if (!isComment)
				fputc(c, fpWriteCode);	
			}
			else
			{
				if (lookahead != ' ')
					fputc(' ', fpWriteCode);
				
				isComment = false;
			}
		}
		
		if (feof(fpReadCode))
		{
			fclose(fpReadCode);
			fclose(fpWriteCode);
			return;
		}			
	}
}

void writeError(char c)
{
	fclose(fpRead);
	fclose(fpWrite);
	printf("**********************************************************\nERRO: caractere nao reconhecido %c\nCurrent Word: %s\n**********************************************************\n", c,currentWord);
	exit(1);
}

void addToken(char *type, char *attr)
{
	if (rollback == true)
	{
		attr[currentWordIndex-1] = '\0';
		currentWordIndex = currentWordIndex -2;	
	}
	
	fputc('<', fpWrite);
	
	if (strcmp(type, "reservado")!=0)
	{
		fputs(type, fpWrite);
		fputc(',', fpWrite);
	}
	
	fputs(attr, fpWrite);
	fputs(">\n", fpWrite);	
}

void addTokenVar(char *type, int idVar)
{
	char buffer[20];
	fputc('<', fpWrite);
	
	if (strcmp(type, "reservado")!=0)
	{
		fputs(type, fpWrite);
		fputc(',', fpWrite);
	}
	
	sprintf(buffer, "%d", idVar);
  	fputs(buffer, fpWrite);
	fputs(">\n", fpWrite);	
}

void cleanCurrentWord()
{
	int i = 0;
	for (i = 0; i < MAX_VAR_NAME_SIZE; i++){
		currentWord[i] = '\0';
	}	
}

int getId()
{
	int i;
	
	if (rollback)
	{
		currentWord[currentWordIndex--] = '\0';	
	}
	
	for (i = 0; i < currentVarId; i++)
	{
		if (strcmp(varIds[i], currentWord) == 0)
		{
			printf("Var ID %d já existente: %s\n", currentVarId, varIds[i]);
			return i;
		}
	}
	
	varIds[currentVarId] = malloc(MAX_VAR_NAME_SIZE);
	strcpy(varIds[currentVarId], currentWord);
	printf("Var ID %d gravado: %s\n", currentVarId, varIds[currentVarId]);
	return currentVarId++;
}
