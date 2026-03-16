default:
	gcc -o md_frag main.c best_fit.c first_fit.c next_fit.c worst_fit.c common.c

test: default
	./md_frag -c chunks -s sizes

debug: 
	gcc -o md_frag main.c best_fit.c first_fit.c next_fit.c worst_fit.c common.c -g
	gdb md_frag
