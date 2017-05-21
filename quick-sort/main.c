#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_WORDS 2048
#define MAX_CHAR 255

typedef struct word{
    char str[MAX_CHAR];
    int freq;
}word;

void remove_trailing_dot(char str[]){
    int removed = 0;
    for(int i = 0; str[i] != '\0' && i < MAX_CHAR ; i++){
        if (str[i]=='.' && str[i+1]=='\0'){ //if str[i] is a trailing dot
            str[i]='\0'; // remove it
            removed = 1;
        }
    }
    if (removed == 1){
    printf("dot removed: %s\n",str);
    }
}


// This Quick Sort algorithm refers to CLRS book: intro to algorithm.
void swap(word *a, word *b){
    word t = *a;
    *a = *b;
    *b = t;
}

int partition(word words[], int low, int high){
    int pivot = words[high].freq;
    int i = low;

    for(int j = low; j <= high - 1; j++){
        if (words[j].freq >= pivot){
            swap(&words[i], &words[j]);
            i++;
        }
    }
    swap(&words[i], &words[high]);
    return i;
}

void quickSort(word words[], int low, int high){
    if (low < high){
        int pivot_index = partition(words, low, high);
        quickSort(words, low, pivot_index - 1);
        quickSort(words, pivot_index + 1, high);
    }
}

int main(){
    //char *filename = "test.txt";
    //FILE *fp = fopen(filename, "r");
    FILE *fp = fopen("test.txt", "r");
    if(fp==NULL){
        printf("can't open file\n");
        exit(1);
    }

    //char word[MAX_CHAR]="";
    //char words[MAX_WORDS][MAX_CHAR];
    word mywords[MAX_WORDS];
    for(int i = 0; i < MAX_WORDS; i++){
        for(int j = 0; j < MAX_CHAR; j++){
        mywords[i].str[j] = '\0';
        }
        mywords[i].freq = 0;
    }

    //initialize freq(uencies) to zero
    //int freq[MAX_WORDS];
    //for (int i=0;i<MAX_WORDS;i++){
    //    mywords[i].freq = 0;
    //}

    //test copy
    char str_from_file[MAX_CHAR];

    //Copy all str_from_file into words
    int index = 0;
    while(fscanf(fp, "%s", str_from_file)==1){ // read file and store a word one by one (in each loop) in str_from_file variable.

        remove_trailing_dot(str_from_file); // then remove it

        int contd = 0;
        for(int i = 0; i < MAX_WORDS; i++){
            if(strcmp(str_from_file, mywords[i].str)==0){
                mywords[i].freq++;
                contd = 1; // in order to continue while loop;
                break;
            }
        }
        if(contd == 1){
            continue; // if str_from_file already exists in the mywords array, then just increase the frequency by one. Continue to the next loop.
        }

        // if str_from_file does not exist in the mywords array, then create a new one.
        printf("index: %d\n",index);
        printf("%s\n", str_from_file);
        strcpy(mywords[index].str,str_from_file);
        mywords[index].freq++; // this is equivalent to just saying `mywords[index].freq = 1`, as this variable will be initialized to zero.
        index++;
    }

    // Do quick sort from the lowest index to the highest index. Don't get confused; MAX_WORDS-1 is the highest index, whilst MAX_WORDS is the size of the array.
    quickSort(mywords,0,MAX_WORDS-1);

    // print words // disabled as MAX_WORDS too large. You can play around with this function by changing the value of MAX_WORDS from 2048 to something smaller, such as 20.
    /*
    printf(">>>>> print words\n");
    for(int i=0;i<MAX_WORDS;i++){
        printf("%s\n",mywords[i].str);
    }
    */

    // print frequencies // disabled as MAX_WORDS too large. You can play around with this function by changing the value of MAX_WORDS from 2048 to something smaller, such as 20.
    /*
    printf(">>>>> print freq\n");
    for (int i=0;i<MAX_WORDS;i++){
        printf("mywords[%d].freq = %d\n",i, mywords[i].freq);
    }
    */

    // print 5 most frequent words
    printf(">>>> print answers.\n");
    for (int i =0; i<5; i++){
        printf("word: %s // frequency: %d\n", mywords[i].str, mywords[i].freq);
    }

    return 0;
}
