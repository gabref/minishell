#include "../../inc/lexer.h"

/*LEXER_________________________________________________________________________
COSA FA: Alloca  la struct t_lexer e la riempie chiamando il tokenizer
RETURN:  Restituisce la struct t_lexer (contenente la lista di token)
			o NULL in caso di errore

LINEE:   - dichiaro e alloco un puntatore a t_lexer
			- inizializzo a NULL o 0 gli elementi di t_lexer
			(se restituisce 0 dealloco la struct e ritorno NULL)
			- inserisco il nodo finale contenente l'END_OF_FILE
			(se fallische dealloco la struct e ritorno NULL)
			- restituisco la struct lex_struct
*/

t_lexer	*lexer(char *input)
{
	t_lexer	*lex_struct;
	int		end_list;

	lex_struct = (t_lexer *)malloc(sizeof(t_lexer));
	if (init_lexer(lex_struct) != 0)
		return (NULL);
	end_list = tokenizer(lex_struct, input);
	if (end_list == 0)
	{
		return (NULL);
	}
	if (add_end(&(lex_struct->tokens), NULL, end_list, end_list, END_OF_FILE))
	{
		free_and_quit(lex_struct, NULL);
		return (NULL);
	}
	lex_struct->size = end_list;
	return (lex_struct);
}
