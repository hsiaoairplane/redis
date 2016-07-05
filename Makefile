all:
	gcc -Wall example-sub1.c -L/usr/include -levent -lhiredis -o example-sub1
	gcc -Wall example-sub2.c -L/usr/include -levent -lhiredis -o example-sub2
	gcc -Wall example-pub-sync.c -L/usr/include -levent -lhiredis -o example-pub-sync
	gcc -Wall example-pub-async.c -L/usr/include -levent -lhiredis -o example-pub-async
clean:
	rm example-sub1
	rm example-sub2
	rm example-pub-sync
	rm example-pub-async
