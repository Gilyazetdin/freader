cd src 
gcc -c freader.c freader-lib.c 
gcc -o ../bin/freader freader.o freader-lib.o 
rm *.o 
cd ..