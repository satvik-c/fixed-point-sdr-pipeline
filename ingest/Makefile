capture: ingestion.c ../lib/fixed_point.c
	gcc -Wall -I../lib ingestion.c ../lib/fixed_point.c -lrtlsdr -o capture

test: ../lib/test_fixed_point.c ../lib/fixed_point.c
	gcc -Wall -I../lib ../lib/test_fixed_point.c ../lib/fixed_point.c -lm -o test

clean:
	rm -f capture test