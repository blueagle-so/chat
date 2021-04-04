all:
	gcc filestruct.c -o base
	g++ insertknuth.c -o insertknuth
	g++ quicksort.c  -o quick
	g++ merge.cpp -o merge
	g++ mergeknuth.cpp -o mergeknuth
	g++ mergeknuth1.cpp -o mergeknuth1
	g++ shellknuth.cpp -o shellknuth
	git apply fib
	g++ shellknuth.cpp -o shellknuthfib	 
	git apply unfib
	#compile complite.
	./base
	#wait ten seconds.
	./insertknuth
	./quick
	./merge
	./mergeknuth
	./mergeknuth1
	#wait 5 sec.
	./shellknuth
	#wain 4 sec.
	./shellknuthfib
