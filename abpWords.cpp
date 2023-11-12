#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
	char word[20];
	int timesAppears;
	struct Node *left;
	struct Node *right; 
	struct Node *father;
	
};
typedef Node NODE;

NODE* newNode(char word[], NODE* father){
    NODE* node = (NODE*)malloc(sizeof(NODE));
    strcpy(node->word, word);
    node->left = NULL;
    node->right = NULL;
    node->father = father;
    
    node->timesAppears = 1;
    
    return(node);

}

// used to determine the hash position of the word
int getHashPosition(char word[]){
	return word[0] - 'a';
}

//-------------------------------------------
//region insertion
void insert(NODE** current, char word[]) {
    if (*current == NULL) {
        *current = newNode(word, NULL);
        return;
    }

    int comparedString = strcmp(word, (*current)->word);

    if (comparedString > 0) {
        if ((*current)->right == NULL) {
            (*current)->right = newNode(word, *current);
        } else {
            insert(&(*current)->right, word);
        }

    } else if (comparedString < 0) {
        if ((*current)->left == NULL) {
            (*current)->left = newNode(word, *current);
        } else {
            insert(&(*current)->left, word);
        }

    } else {
        (*current)->timesAppears++;
    }
}

void insertWord(NODE* alphabet[], char word[]){
	int hashPos = getHashPosition(word);
	insert(&alphabet[hashPos], word);	
	
}

//-------------------------------------------

//-------------------------------------------
//region total words in tree
void countWordLetter(NODE* root, int* totalWords) {
    if (root == NULL) {
        return;
    }
    
    (*totalWords)++;    
    countWordLetter(root->left, totalWords);
    countWordLetter(root->right, totalWords);
}

void countWordsAlphabet(NODE* alphabet[]) {
    int totalWords = 0, i;

    for (i = 0; i < 26; i++) {
        countWordLetter(alphabet[i], &totalWords);
    }

    printf("Total de palavras: %d\n", totalWords);
}

//-------------------------------------------

//-------------------------------------------
//region total occurences in tree
void countTotalOccurencesLetter(NODE* root, int* totalOccurences) {
    if (root == NULL) {
        return;
    }
    
    (*totalOccurences) += root->timesAppears;
    countTotalOccurencesLetter(root->left, totalOccurences);
    countTotalOccurencesLetter(root->right, totalOccurences);
}

void countTotalOccurencesAlphabet(NODE* alphabet[]) {
    int totalOccurences = 0, i;

    for (i = 0; i < 26; i++) {
        countTotalOccurencesLetter(alphabet[i], &totalOccurences);
    }

    printf("Total de ocorrencias: %d\n", totalOccurences);
}

//-------------------------------------------

//-------------------------------------------
//region show words in alphabet
void centralA(NODE* root){
	if(root == NULL){
	  return;
		
	}
	
	centralA(root->left);
	printf("%s - %d\n",root->word, root->timesAppears);
	centralA(root->right);
	
}

void centralD(NODE* root){
	if(root == NULL){
	  return;
		
	}
	centralD(root->right);
	printf("%s - %d\n",root->word, root->timesAppears);
	centralD(root->left);
	
}

// reverse = 0 for alphabetical, 1 = for reverse alphabetical
void showAlphabet(NODE* alphabet[], int reverse = 0){
	int i;
	printf("\n");
	if(reverse){
		for(i = 25; i >= 0; i--){
			centralD(alphabet[i]);	
		}
		
	}else {
		for(i = 0; i < 26; i++){
			 centralA(alphabet[i]);	
		}
		
	}
}

//-------------------------------------------

//-------------------------------------------
//region show words with 1 occurence
void centralAOneOcurrence(NODE* root){
	if(root == NULL){
	  return;
		
	}
	
	centralAOneOcurrence(root->left);
	if(root->timesAppears == 1){
		printf("%s - %d\n",root->word, root->timesAppears);
		
	}
	centralAOneOcurrence(root->right);
	
}

void showAlphabetOneOccurence(NODE* alphabet[]){
	int i;
	for(i = 0; i < 26; i++){
		centralAOneOcurrence(alphabet[i]);	
	}		
}

//-------------------------------------------

//-------------------------------------------
//region search in tree
NODE* searchWord(NODE* current, char word[]){
	NODE* res = NULL;
	if(current != NULL){
		int resultCmp = strcmp(word, current->word);
	
		if(resultCmp == 0){
			res = current;
		}else {
			if(resultCmp > 0){
				res = searchWord(current->right, word);
			}else {
				res = searchWord(current->left, word);
			}
		}		
	}		
	return res;	
}

void searchWordAlphabet(NODE* alphabet[], char word[]){	
	NODE* res = searchWord(alphabet[getHashPosition(word)], word);
	
	if(res != NULL){
		printf("Total de ocorrencias: %d\n", res->timesAppears);
	}else {		
		printf("Palavra nao encontrada!");
	}
			
}

//-------------------------------------------

//-------------------------------------------
//region words with most appear times
void showWordsByAppearTime(NODE* current, int mostTimesAppeared){
	
	if(current == NULL){
	  return;
		
	}
	
	showWordsByAppearTime(current->left, mostTimesAppeared);
	if(current->timesAppears == mostTimesAppeared){
		printf("%s - %d\n", current->word, current->timesAppears);
	}
	showWordsByAppearTime(current->right, mostTimesAppeared);
	
}

void getBiggestAppearTime(NODE* current, int* mostTimesAppeared){
	if(current == NULL){
	  return;
		
	}
	
	getBiggestAppearTime(current->left, mostTimesAppeared);
	if(current->timesAppears > *mostTimesAppeared){
		*mostTimesAppeared = current->timesAppears;
	}
	getBiggestAppearTime(current->right, mostTimesAppeared);
}

void searchWordMostOccurAlphabet(NODE* alphabet[]){
	int mostTimesAppeared = 0, i;
	
	for(i = 0; i < 26; i++){	
		getBiggestAppearTime(alphabet[i], &mostTimesAppeared);
	
	}
	
	for(i = 0; i < 26; i++){	
		showWordsByAppearTime(alphabet[i], mostTimesAppeared);
	
	}
				
}

//-------------------------------------------

//-------------------------------------------
//region prefix

void prefix(NODE* root){
	if(root == NULL){
	  return;
		
	}
	
	printf("%s - %d\n",root->word, root->timesAppears);
	prefix(root->left);
	prefix(root->right);
	
}

void showAlphabetPrefix(NODE* alphabet[]){
	int i;	
	
	for(i = 0; i < 26; i++){
		prefix(alphabet[i]);	
	}

}

//-------------------------------------------

//-------------------------------------------
//region prefix

void posfix(NODE* root){
	if(root == NULL){
	  return;
		
	}
	posfix(root->left);
	posfix(root->right);
	printf("%s - %d\n",root->word, root->timesAppears);
	
}

void showAlphabetPosfix(NODE* alphabet[]){
	int i;	
	
	for(i = 0; i < 26; i++){
		posfix(alphabet[i]);	
	}

}

//-------------------------------------------

//-------------------------------------------
//region remove

void removeLeaf(NODE* alphabet[], NODE* word){
	NODE* father = word->father;
	
	if(father == NULL){ //then its the root
		alphabet[getHashPosition(word->word)] = NULL;
	}else {
		if(father->left == word){
			father->left = NULL;
		}else {
			father->right = NULL;
		}
	}
	free(word);
}

void removeChild(NODE* alphabet[], NODE* word){
	NODE* father = word->father;
	
	if(father == NULL){ //then its the root
		if(word->left != NULL){
			alphabet[getHashPosition(word->word)] = word->left;
		}else {
			alphabet[getHashPosition(word->word)] = word->right;
		}
		alphabet[getHashPosition(word->word)]->father = NULL;
	}else {
		if(word->left == NULL){
			if(father->right == word){
				father->right = word->right;
			}else{
				father->left = word->left;
			}
			word->right->father = father;
		}else {
			if (father->right == word){
				father->right = word->left;
			}else {
				father->left = word->left;
			}
			word->left->father = father;
		}
		free(word);
	}
}

void removeChildren(NODE* alphabet[], NODE* word){
	NODE* aux = word->left;
	NODE* father = NULL;
	
	while(aux->right != NULL){
		aux = aux->right;
	}
	strcpy(word->word, aux->word);
	
	if(aux->left == NULL && aux->right == NULL){
		removeLeaf(alphabet, aux);
	}else {
		removeChild(alphabet, aux);
	}
}

void remove(NODE* alphabet[], char word[]){
	NODE* res = searchWord(alphabet[getHashPosition(word)], word);
	
	if (res == NULL){
		printf("Palavra nao encontrada!");
		return;
	}
	
	if(res->timesAppears > 1){
		res->timesAppears--;
		return;
	}
	
	if(res->left == NULL && res->right == NULL){
		removeLeaf(alphabet, res);
	}else {
		if(res->left != NULL && res->right != NULL){
			removeChildren(alphabet, res);
		}else {
			removeChild(alphabet, res);
		}
	}
}

//-------------------------------------------

//used to initiate the alphabet array with NULL
void initRootArray(NODE* alphabet[]){
	int i;
	
	for(i = 0; i < 26; i++){
		alphabet[i] = NULL;	
	}
}

void showMenu(){
	printf("\n|--------- MENU ---------|\n");
	printf(" 1 -> Inserir palavra\n");
	printf(" 2 -> Consultar palavra\n");
	printf(" 3 -> Remover palavra\n");
	printf(" 4 -> Total de palavras diferentes na arvore\n");
	printf(" 5 -> Total de ocorrencias na arvore\n");
	printf(" 6 -> Exibir palavras\n");
	printf(" 7 -> Exibir palavras por letra inicial\n");
	printf(" 8 -> Exibir palavras com mais ocorrencia\n");
	printf(" 9 -> Exibir palavras com uma ocorrencia\n");
	printf("10 -> Percurso pre-fixado\n");
	printf("11 -> Percurso pos-fixado\n");
	printf(" 0 -> Sair\n");
	printf("\nOpcao: ");
}

int main(){
	
	NODE* alphabet[26];	
	initRootArray(alphabet);
	
	insertWord(alphabet, "lorenzo");
	insertWord(alphabet, "alisson");
	insertWord(alphabet, "felipe");
	insertWord(alphabet, "antonio");
	insertWord(alphabet, "mateus");
	insertWord(alphabet, "gustavo");
	insertWord(alphabet, "joao");
	insertWord(alphabet, "joao");
	insertWord(alphabet, "joao");
	insertWord(alphabet, "lucas");
	insertWord(alphabet, "lucas");
	insertWord(alphabet, "lucas");
	
	int opc = 0;
	
	do{
		showMenu();
		scanf("%d", &opc);
		char word[20];
		
		switch(opc){
			case 1:				
				getchar();
				printf("Digite a palavra para inserir: ");
				gets(word);
				insertWord(alphabet, word);
				break;
			case 2:
				getchar();
				printf("Digite a palavra para consultar: ");
				gets(word);
				searchWordAlphabet(alphabet, word);
				break;
			case 3:
				getchar();
				printf("Digite a palavra para remover: ");
				gets(word);
				remove(alphabet, word);
				break;
			case 4:
				countWordsAlphabet(alphabet);
				break;
			case 5:
				countTotalOccurencesAlphabet(alphabet);
				break;
			case 6:
				int ord;
				printf("0 - Ordem alfabetica\n1 - Ordem alfabetica reversa:");
				scanf("%d", &ord);
				showAlphabet(alphabet, ord);
				break;
			case 7:
				getchar();
				char letter;
				int ord2;
				printf("Digite a letra inicial das palavras: ");
				scanf("%c", &letter);
				getchar();
				printf("0 - Ordem alfabetica\n1 - Ordem alfabetica reversa");
				scanf("%d", &ord2);
				if(ord2){
					centralD(alphabet[letter - 'a']);
				}else {
					centralA(alphabet[letter - 'a']);
				}
				break;
			case 8:
				searchWordMostOccurAlphabet(alphabet);
				break;
			case 9:
				showAlphabetOneOccurence(alphabet);
				break;
			case 10:
				showAlphabetPrefix(alphabet);
				break;
			case 11:
				showAlphabetPosfix(alphabet);
				break;
			default:
				break;
		}
		
		
	}while(opc != 0);
			

}
