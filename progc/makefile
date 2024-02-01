INCLUDE_DIR = include

all: executable1 executable2 executable 3 main_script_permissions

executable1: src/noEnter.c src/fichier.c
	gcc -o src/noEnter src/noEnter.c src/fichier.c -I$(INCLUDE_DIR)

executable2: src/main_s.c src/avl.c src/fichier.c
	gcc -o src/main_s src/main_s.c src/avl.c src/fichier.c -I$(INCLUDE_DIR)

executable3: src/main_t.c src/avl.c src/fichier.c
	gcc -o src/main_t src/main_t.c src/avl.c src/fichier.c -I$(INCLUDE_DIR)
	
main_script_permissions:
	chmod 000 ../main_script.sh

clean:
	rm -f src/noEnter src/main_s

