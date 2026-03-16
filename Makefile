default:
	gcc -o md_frag main.c best_fit.c first_fit.c next_fit.c worst_fit.c common.c

test:
	./md_frag -c chunks -s sizes
