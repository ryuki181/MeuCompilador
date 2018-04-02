#include <stdio.h>
#include <ctype.h>


FILE *fpRead, *fpWrite;

const int true = 1;
const int false = 0;

struct TOKEN
{
	char* type;
	char* attr;
};

main() 
{	
    fpRead = fopen("C:/Users/Rafael/Documents/code.txt", "r");
    fpWrite = fopen("C:/Users/Rafael/Documents/tokens.txt", "w+");
        
	int state = 0;
	
	char c = ' ';
	char lookahead = fgetc(fpRead);
		
	while (true)
	{		
		//CHECA SE ARQUIVO TERMINOU
		if (feof(fpRead))
		{
			fclose(fpRead);
			fclose(fpWrite);
			exit(0);
		}
		
		c = lookahead;
		lookahead = fgetc(fpRead);
		
		printf("%c ", c);
				
		switch(state)
		{
			case 0:
					 if (c == 'a') state = 1;
				else if (c == 'e') state = 9;
				else if (c == 'f') state = 25;
				else if (c == 'i') state = 49;
				else if (c == 'l') state = 59;
				else if (c == 'm') state = 64;
				else if (c == 'o') state = 66;
				else if (c == 's') state = 67;
				else if (c == 'v') state = 71;
				else if (c == '>') state = 81;				
				else if (c == '<') state = 83;
				else if (c == '=')
				{
						addToken((struct TOKEN) {"comparador", "igual"});
						state = 0;
				}
				else if (c == '+')
				{
						addToken((struct TOKEN) {"arit-op", "mais"});
						state = 0;
				}
				else if (c == '-')
				{
						addToken((struct TOKEN) {"arit-op", "menos"});
						state = 0;
				}
				else if (c == '*')
				{
						addToken((struct TOKEN) {"arit-op", "mult"});
						state = 0;
				}
				else if (c == '/')
				{
						addToken((struct TOKEN) {"arit-op", "div"});
						state = 0;
				}
				else if (c == ',')
				{
						addToken((struct TOKEN) {"pont", "virg"});
						state = 0;
				}
				else if (c == ';') 
				{
						addToken((struct TOKEN) {"pont", "pt-virg"});
						state = 0;
				}	
				else if (c == ':') 
				{
						addToken((struct TOKEN) {"pont", "dois-pt"});
						state = 0;
				}			
				else if (c == '(')
				{
						addToken((struct TOKEN) {"pont", "parent-abre"});
						state = 0;
				}	
				else if (c == ')')
				{
						addToken((struct TOKEN) {"pont", "parent-fecha"});
						state = 0;
				}
				
				//IGNORA ESPACO EM BRANCO
				else if (c == ' ') state = 0;
							
				//DIGITOS
				else if (isdigit(c)) state = 98;
				
				//NOME DE VARIAVEL
				else if (isalpha(c)) state = 99;
				
				//NAO RECONHECIDO
				else error(c);
				break;
				
			//LETRA A
			case 1:
				if (c == 'l') state = 2;
				else state = 99;
				break;
				
			case 2:
				if (c == 'g') state = 3;
				else state = 99;
				break;
				
			case 3:
				if (c == 'o') state = 4;
				else state = 99;
				break;
				
			case 4:
				if (c == 'r') state = 5;
				else state = 99;
				break;
				
			case 5:
				if (c == 'i') state = 6;
				else state = 99;
				break;
				
			case 6:
				if (c == 't') state = 7;
				else state = 99;
				break;
				
			case 7:
				if (c == 'm') state = 8;
				else state = 99;
				break;
				
			case 8:
				if (c == 'o') 
				{
					if (isalnum(lookahead) == false)
					{
						addToken((struct TOKEN) {"reservado", "algoritmo"});
						state = 0;
					}
					else state = 99;
				}
				else state = 99;
				break;
				
			//LETRA E
			case 9:
				if (isalnum(lookahead) == false)
				{
					printf("entrou");
					addToken((struct TOKEN) {"logic-op", "e"});
					state = 0;
				}
				else if (c == 's') state = 10;
				else if (c == 'n') state = 21;
				else if (c == 'x') state = 24;
				else state = 99;
				break;
				
			case 10:
				if (c == 'c') state = 11;
				else state = 99;
				break;
				
			case 11:
				if (c == 'r') state = 12;
				else state = 99;
				break;
				
			case 12:
				if (c == 'e') state = 13;
				else state = 99;
				break;
				
			case 13:
				if (c == 'v') state = 14;
				else state = 99;
				break;
				
			case 14:
				if (c == 'a') 
				{
					if (isalnum(lookahead) == false)
					{
						addToken((struct TOKEN) {"reservado", "escreva"});
						state = 0;
					}
					else state = 99;
				}
				else state = 99;
				break;
				
			case 15:
				if (c == 'q') state = 16;
				else if (c == 't') state = 21;
				else state = 99;
				break;
				
			case 16:
				if (c == 'u') state = 17;
				else state = 99;
				break;
				
			case 17:				
				if (c == 'a') state = 18;
				else state = 99;
				break;
				
			case 18:
				if (c == 'n') state = 29;
				else state = 99;
				break;
				
			case 19:
				if (c == 't') state = 20;
				else state = 99;
				break;
				
			case 20:
				if (c == 'o') 
				{
					if (isalnum(lookahead) == false)
					{
						addToken((struct TOKEN) {"reservado", "enquanto"});
						state = 0;
					}
					else state = 99;
				}
				else state = 99;
				break;
				
			case 21:
				if (c == 't') state = 22;
				else state = 99;
				break;
				
			case 22:
				if (c == 'a') state = 23;
				else state = 99;
				break;
				
			case 23:
				if (c == 'o')
				{
					if (isalnum(lookahead) == false)
					{
						addToken((struct TOKEN) {"reservado", "entao"});
						state = 0;
					}
					else state = 99;
				}
				else state = 99;
				break;
			
			case 24:
				if (c == 'p')
				{
					if (isalnum(lookahead) == false)
					{
						addToken((struct TOKEN) {"arit-op", "exp"});
						state = 0;
					}
					else state = 99;
				}
				break;
				
			//LETRA F
			case 25:
				if (c == 'a') state = 26;
				else if (c == 'i') state = 31;
				else state = 99;
				break;
				
			case 26:
				if (c == 'l') state = 27;
				else if (c == 'c') state = 29;
				else state = 99;
				break;
				
			case 27:
				if (c == 's') state = 28;
				else state = 99;
				break;
				
			case 28:
				if (c == 'o')
				{
					if (isalnum(lookahead) == false)
					{
						addToken((struct TOKEN) {"reservado", "falso"});
						state = 0;
					}
					else state = 99;
				}
				else state = 99;
				break;
				
			case 29:
				if (c == 'a')
				{
					if (isalnum(lookahead) == false)
					{
						addToken((struct TOKEN) {"reservado", "faca"});
						state = 0;
					}
					else state = 99;
				}
				else state = 99;
				break;
				
			case 31:
				if (c == 'm') state = 32;
				else state = 99;
				break;
				
			case 32:
				if (c == 's') state = 33;
				else if (c == 'a') state = 34;
				else if (c == 'e') state = 42;
				else state = 99;
				break;
				
			case 33:
				if (c == 'e')
				{
					if (isalnum(lookahead) == false)
					{
						addToken((struct TOKEN) {"reservado", "fimse"});
						state = 0;
					}
					else state = 99;
				}
				else state = 99;
				break;
				
			case 34:
				if (c == 'l') state = 35;
				else state = 99;
				break;
				
			case 35:
				if (c == 'g') state = 36;
				else state = 99;
				break;
				
			case 36:
				if (c == 'o') state = 37;
				else state = 99;
				break;
				
			case 37:
				if (c == 'r') state = 38;
				else state = 99;
				break;
				
			case 38:
				if (c == 'i') state = 39;
				else state = 99;
				break;
				
			case 39:
				if (c == 't') state = 40;
				else state = 99;
				break;
				
			case 40:
				if (c == 'm') state = 41;
				else state = 99;
				break;
				
			case 41:
				if (c == 'o') 
				{
					if (isalnum(lookahead) == false)
					{
						addToken((struct TOKEN) {"reservado", "fimalgoritmo"});
						state = 0;
					}
					else state = 99;
				}
				else state = 99;
				break;
				
			case 42:
				if (c == 'n') state = 43;
				else state = 99;
				break;
				
			case 43:
				if (c == 'q') state = 44;
				else state = 99;
				break;
				
			case 44:
				if (c == 'u') state = 45;
				else state = 99;
				break;
				
			case 45:
				if (c == 'a') state = 46;
				else state = 99;
				break;
				
			case 46:
				if (c == 'n') state = 47;
				else state = 99;
				break;
				
			case 47:
				if (c == 't') state = 48;
				else state = 99;
				break;
				
			case 48:
				if (c == 'o') 
				{
					if (isalnum(lookahead) == false)
					{
						addToken((struct TOKEN) {"reservado", "fimenquanto"});
						state = 0;
					}
					else state = 99;
				}
				else state = 99;
				break;
				
			// LETRA I
			case 49:
				if (c == 'n') state = 50;
				else state = 99;
				break;
				
			case 50:
				if (c == 'i') state = 51;
				if (c == 't') state = 54;
				else state = 99;
				break;
				
			case 51:
				if (c == 'c') state = 52;
				else state = 99;
				break;
				
			case 52:
				if (c == 'i') state = 53;
				else state = 99;
				break;
				
			case 53:
				if (c == 'o') 	
				{				
					if (isalnum(lookahead) == false)
					{
						addToken((struct TOKEN) {"reservado", "inicio"});
						state = 0;
					}
					else state = 99;
				}
				else state = 99;
				break;
				
			case 54:
				if (c == 't') state = 55;
				else state = 99;
				break;
				
			case 55:
				if (c == 'e') state = 56;
				else state = 99;
				break;
				
			case 56:
				if (c == 'i') state = 57;
				else state = 99;
				break;
				
			case 57:
				if (c == 'r') state = 58;
				else state = 99;
				break;
				
			case 58:
				if (c == 'o') 	
				{				
					if (isalnum(lookahead) == false)
					{
						addToken((struct TOKEN) {"reservado", "inteiro"});
						state = 0;
					}
					else state = 99;
				}
				else state = 99;
				break;
				
			// LETRA L
			case 59:
				if (c == 'o') state = 60;
				else state = 99;
				break;
				
			case 60:
				if (c == 'g') state = 61;
				else state = 99;
				break;
				
			case 61:
				if (c == 'i') state = 62;
				else state = 99;
				break;
				
			case 62:
				if (c == 'c') state = 63;
				else state = 99;
				break;
				
			case 63:
				if (c == 'o') 	
				{				
					if (isalnum(lookahead) == false)
					{
						addToken((struct TOKEN) {"reservado", "logico"});
						state = 0;
					}
					else state = 99;
				}
				else state = 99;
				break;
				
			//LETRA M
			case 64:
				if (c == 'o') state = 65;
				else state = 99;
				break;
				
			case 65:
				if (c == 'd') 	
				{				
					if (isalnum(lookahead) == false)
					{
						addToken((struct TOKEN) {"arit-op", "mod"});
						state = 0;
					}
					else state = 99;
				}
				else state = 99;
				break;
				
			// LETRA O
			case 66:
				if (c == 'u') 	
				{				
					if (isalnum(lookahead) == false)
					{
						addToken((struct TOKEN) {"logic-op", "ou"});
						state = 0;
					}
					else state = 99;
				}
				else state = 99;
				break;
				
			//LETRA S
			case 67:
				if (c == 'e') 	
				{				
					if (isalnum(lookahead) == false)
					{
						addToken((struct TOKEN) {"reservado", "se"});
						state = 0;
				 	}
					else state = 68;
				}
				else state = 99;
				break;
				
			case 68:
				if (c == 'n') state = 69;
				else state = 99;
				break;
				
			case 69:
				if (c == 'a') state = 70;
				else state = 99;
				break;
				
			case 70:
				if (c == 'o') 	
				{				
					if (isalnum(lookahead) == false)
					{
						addToken((struct TOKEN) {"reservado", "senao"});
						state = 0;
					}
					else state = 99;
				}
				else state = 99;
				break;	
											
			//LETRA V
			case 71:
				if (c == 'a') state = 72;
				else if (c == 'e') state = 73;
				else state = 99;
				break;	
						
			case 72:
				if (c == 'r') 	
				{				
					if (isalnum(lookahead) == false)
					{
						addToken((struct TOKEN) {"reservado", "var"});
						state = 0;
					}
					else state = 99;
				}
				else state = 99;
				break;
					
			case 73:
				if (c == 'r') state = 74;
				else state = 99;
				break;
				
			case 74:
				if (c == 'd') state = 75;
				else state = 99;
				break;
				
			case 75:
				if (c == 'a') state = 76;
				else state = 99;
				break;
				
			case 76:
				if (c == 'd') state = 77;
				else state = 99;
				break;
				
			case 77:
				if (c == 'e') state = 78;
				else state = 99;			
				break;
				
			case 78:
				if (c == 'i') state = 79;
				else state = 99;			
				break;
				
			case 79:
				if (c == 'r') state = 80;
				else state = 99;
				break;
				
			case 80:
				if (c == 'o') 	
				{				
					if (isalnum(lookahead) == false)
					{
						addToken((struct TOKEN) {"reservado", "verdadeiro"});
						state = 0;
					}
					else state = 99;
				}
				else state = 99;
				break;
				
			//MAIOR IGUAL
			case 81:
				if (lookahead == '=')
				{
					state = 82;
				}
				else
				{
					addToken((struct TOKEN) {"comparador", "maior"});
					state = 0;	
				}
				break;
				
			case 82:				
				addToken((struct TOKEN) {"comparador", "maior-igual"});
				state = 0;			
				break;
				
			//MENOR IGUAL
			case 83:
				if (lookahead == '=')
				{
					state = 84;
				}
				else if (lookahead == '-')
				{
					state = 85;
				}
				else if (lookahead == '>')
				{
					state = 86;
				}
				else
				{
					addToken((struct TOKEN) {"comparador", "menor"});
					state = 0;	
				}
				break;	
				
			case 84:
				addToken((struct TOKEN) {"comparador", "menor-igual"});
				state = 0;
			
			case 85:
				addToken((struct TOKEN) {"pont", "atribuicao"});
				state = 0;
			
			case 86:
				addToken((struct TOKEN) {"comparador", "dif"});
				state = 0;
					
			// NUMEROS INTEIROS
			case 98:
				if (isdigit(lookahead) == false)
				{
						addToken((struct TOKEN) {"num", "teste"});
						state = 0;
				}
				else state = 98;
				break;
								
			// NOME DE VARIAVEL
			case 99:
				if (isalnum(lookahead) == false)
				{
					addToken((struct TOKEN) {"id", "teste"});
					state = 0;
				}
				else state = 99;
				break;
		}
	}
}

void error(char c)
{
	fclose(fpRead);
	fclose(fpWrite);
	printf("*********************************\nERRO: caractere nao reconhecido \"%c\"\n*********************************\n", c);
	exit(1);
}

void addToken(struct TOKEN t)
{
	char str[100];
	strcat(str, "<");
	
	if (strcmp(t.type, "reservado")!=0)
	{
		strcat(str, t.type);
		strcat(str, ",");
	}
	
	strcat(str, t.attr);
	strcat(str, ">\n");	
	fputs(str, fpWrite);
}

