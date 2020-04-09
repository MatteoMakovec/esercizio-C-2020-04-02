//il programma svolge le attività sotto descritte fino a quando incontra EOF su stdin.
//
//1: il programma legge caratteri da stdin.
//Quando incontra EOF, il programma scrive quanti processi figli ha lanciato in tutto e poi termina.
//
//Il programma accumula i caratteri letti da stdin in un array di dimensione 80 chiamato char_array.
//(introdurre nel codice un #define NUM_CHARS 80).
//
//Quando char_array è pieno, passa tutto l'array ad un nuovo processo figlio
//che fa delle analisi che scrive su stdout (analisi sotto riportate).
//
//Dopo aver lanciato il processo figlio, il processo principale azzera char_array ed il programma continua
//da 1:
//
//
//*analisi svolte dai processi figlio (sull'array di 80 caratteri ricevuto)*
//carattere minimo (mostrare il primo minimo, si applica a chi risolve dal 3/4)
//carattere massimo (mostrare il primo massimo, si applica a chi risolve dal 3/4)
//carattere con più occorrenze (il primo, a parità di occorrenze, si applica a chi risolve dal 3/4)
//carattere con meno occorrenze (il primo, a parità di occorrenze, si applica a chi risolve dal 3/4)
//
//fatta l'analisi e scritto i risultati , il processo figlio termina.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define NUM_CHARS 5
#define ALPHABET 25

void readFromSTDIN(char *char_array);
int count_chars(char *char_array_copy, char ch);
void occurences(char *char_array);

int main(int argc, char *argv[]) {
	char *char_array = calloc(NUM_CHARS, sizeof(char));
	readFromSTDIN(char_array);

	return 0;
}

void readFromSTDIN(char *char_array){
	int c;
	int count = 0;

	while(((c = getchar()) != EOF)){
		if(count < NUM_CHARS){
			char_array[count] = (char) c;
			count++;
		}
		else{
			scanf("%*s");
			break;
		}
	}

	switch(fork()){
		case 0:		occurences(char_array);
					printf("\n\n  ----------------------------------------  \n\n");
					break;

		default:	memset(char_array, "", NUM_CHARS * sizeof(char));
					readFromSTDIN(char_array);
					break;
	}
}

int count_chars(char *char_array_copy, char ch){
	int occurence = 0;

	for(int i=0; i < NUM_CHARS; i++){
		if(char_array_copy[i] == ch){
			occurence += 1;
			char_array_copy[i] = "";
		}
	}

	return occurence;
}

void occurences(char *char_array){
	char *char_array_copy = calloc(NUM_CHARS, sizeof(char));
	int *occurences = calloc(ALPHABET, sizeof(int));;
	memcpy(char_array_copy, char_array, NUM_CHARS * sizeof(char));
	for(int i=0; i < NUM_CHARS; i++){
		if(char_array_copy[i] != ""){
			int position = (int) char_array_copy[i]-97;
			occurences[position] = count_chars(char_array_copy, char_array_copy[i]);
		}
	}

	printf("Occurences:\n");
	for(int i=0; i<ALPHABET; i++){
		if(occurences[i] != 0){
			printf("%c: %d\n", i+97, occurences[i]);
		}
	}
}
