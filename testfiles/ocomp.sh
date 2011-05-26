mips-elf-gcc -O3 -o $1 $1.c
mips-elf-objdump -D $1 | gensimcode > $1.sim
rm $1
rm _temp
