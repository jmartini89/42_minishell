all : libft.a libftprintf.a

libft.a :
	@make -s -C ./libft
	@cp ./libft/libft.a .
	@make fclean -C ./libft
	@echo "\e[32m"$@" compilation successfull\e[0m"

libftprintf.a :
	@make -C ./libftprintf
	@cp ./libftprintf/libftprintf.a .
	@make fclean -C ./libftprintf
	@echo "\e[32m"$@" compilation successfull\e[0m"

clean :
	@rm -f libft.a libftprintf.a
	@echo "\e[33mlibraries clean completed\e[0m"