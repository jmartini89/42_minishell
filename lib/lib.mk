all : libft.a libftprintf.a

libft.a :
	@make -s -C ./libft
	@cp ./libft/libft.a .
	@make fclean -C ./libft
	@echo "\033[32m"$@" compilation successfull\033[0m"

libftprintf.a :
	@make -C ./libftprintf
	@cp ./libftprintf/libftprintf.a .
	@make fclean -C ./libftprintf
	@echo "\033[32m"$@" compilation successfull\033[0m"

clean :
	@rm -f libft.a libftprintf.a
	@echo "\033[33mlibraries clean completed\033[0m"