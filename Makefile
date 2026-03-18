default:
	gcc -o md_frag main.c best_fit.c first_fit.c next_fit.c worst_fit.c common.c

test: default
	./md_frag -c chunks -s sizes

debug: 
	gcc -o md_frag main.c best_fit.c first_fit.c next_fit.c worst_fit.c common.c -g
	gdb md_frag

chunks_large_back_sizes_large:
	@echo "TEST(1): chunks_large_back + sizes_large"
	./md_frag -c tests/chunks_large_back -s tests/sizes_large
chunks_large_back_sizes_random:
	@echo "TEST(2): chunks_large_back + sizes_random"
	./md_frag -c tests/chunks_large_back -s tests/sizes_random
chunks_large_back_sizes_small:
	@echo "TEST(3): chunks_large_back + sizes_small"
	./md_frag -c tests/chunks_large_back -s tests/sizes_small
chunks_large_front_sizes_large:
	@echo "TEST(4): chunks_large_front + sizes_small"
	./md_frag -c tests/chunks_large_front -s tests/sizes_large
chunks_large_front_sizes_random:
	@echo "TEST(5): chunks_large_front + sizes_random"
	./md_frag -c tests/chunks_large_front -s tests/sizes_random
chunks_large_front_sizes_small:
	@echo "TEST(6): chunks_large_front + sizes_small"
	./md_frag -c tests/chunks_large_front -s tests/sizes_small
chunks_random_sizes_large:
	@echo "TEST(7): chunks_random + sizes_large"
	./md_frag -c tests/chunks_random -s tests/sizes_large
chunks_random_sizes_random:
	@echo "TEST(8): chunks_random + sizes_random"
	./md_frag -c tests/chunks_random -s tests/sizes_random
chunks_random_sizes_small:
	@echo "TEST(9): chunks_random + sizes_large"
	./md_frag -c tests/chunks_random -s tests/sizes_large
benchmark: default
	make chunks_large_back_sizes_large
	make chunks_large_back_sizes_random
	make chunks_large_back_sizes_small
	make chunks_large_front_sizes_large
	make chunks_large_front_sizes_random
	make chunks_large_front_sizes_small
	make chunks_random_sizes_large
	make chunks_random_sizes_random
	make chunks_random_sizes_small
