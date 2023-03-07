calculette : calculetteBison.y calculetteFlex.l
															# d'abord yacc pour y.tab.h puis lex puis gcc
	@echo debut $(YACC)-compil : calculetteBison.y
	$(YACC) $(YACCFLAGS) calculetteBison.y -d
	@echo debut $(LEX)-compil : calculetteFlex.l
	$(LEX) calculetteFlex.l
	@echo debut compil c avec edition de liens
	$(CC) -g -Wall -o calculette y.tab.c lex.yy.c -lm 		#lib math
	@echo fin compil : vous pouvez executer calculette