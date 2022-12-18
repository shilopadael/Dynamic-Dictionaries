/***********************
* Shilo Padael
* 318469830
* ex_5
***********************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define COMMA ","

typedef struct Word{
    char** translations;
    struct Word* next;
} Word;
typedef struct {
    char** languages;
    int numOfLanguages;
    Word* wordList;
} Dictionary;

/***********************************************************************************
* Function name: lastChance
* Input: None.
* Output: True or False(1 or 0).
* Function Operation: the function asking the users if there are sure with there choice:
***********************************************************************************/
int lastChance() {
    char sureDelWord;
    printf("Are you sure? (y/n)\n");
    scanf(" %c", &sureDelWord);
    if (sureDelWord == 'y') {
        return 1;
    } else {
        return 0;
    }
}

/***********************************************************************************
* Function name: inputString
* Input: None.
* Output: arr(the address of the string).
* Function Operation: the function take from the users a string and allocate this
 * string in the heap, and return the address of that string:
***********************************************************************************/
char *inputString(){
    int i = 0;
    char *baceUp;

    // allocate the first char.
    char *arr = (char *) malloc(sizeof (char));
    if(arr == NULL) {
        return NULL;
    }
    //store the first char in the allocated space
    scanf(" %c",&arr[i]);

    //loop to store all the string until scanning enter.
    while (arr[i] != '\n'){
        i++;
        //allocate one more place.
        baceUp = arr;
        arr =(char*) realloc(arr, (i+1)*sizeof (char));
        if(arr == NULL) {
            arr=baceUp;
            return NULL;
        }
        scanf("%c",&arr[i]);
    }
    //replace the last digit \n to \0.
    if (arr[i] == '\n'){
        arr[i] = '\0';
    }
    //allocate one more place
    baceUp =arr;
    arr = (char *) realloc(arr, (i+1)*sizeof (char));
    if(arr == NULL) {
        arr=baceUp;
        return NULL;
    }
    return arr;
}

/***********************************************************************************
* Function name: creatLang
* Input: int *numOfLanguages, int islang(or translation).
* Output: char **item(if fail with the allocations return NULL).
* Function Operation: the function call to inputString and sort the string that the
 * users give to nano strings and spit it depand of the times of the commas in the
 * original string and each nano string get place in the heap, if not failed its
 * return the address of the arrays of pointers(item):
***********************************************************************************/
char** creatLang(int *numOfLanguages, int islang) {
    char *token,**item,*toFree,**newItem ,**backUp;
    int counter = 0;

    //getting a string from the user.
    token = inputString();
    //save the arr to free it after using.
    toFree = token;
    if(token == NULL){
        return NULL;
    }
    token = strtok(token, COMMA);
    unsigned long long len = strlen(token);
    //allocating the first string(until the digits is comma) by the size of token.
    char *temp = (char *) malloc(sizeof(char) * (len + 1));
    if(temp == NULL) {
        free(toFree);
        return NULL;
    }
    strcpy(temp, token);
    //allocate the first place for the arrays of the opinter(that point to the strings).
    item = (char **) malloc(sizeof(char *));
    if(item== NULL) {
        free(toFree);
        return NULL;
    }
    //store the first pointer to the first place in item.
    item[0] = temp;

    ///loop until there is no more commas.
    while (token != NULL) {
        if (islang) {
            ///if this function get called by adding new dic so adding 1 to num of lang.
            (*numOfLanguages)++;
        }
        counter++;
        token = strtok(NULL, COMMA);
        ///if token == to NULL ther is no need to allocate more place for string so its will go out of loop.
        if (token != NULL) {
            backUp=newItem;
            newItem = (char **) realloc(item,(counter + 1) * sizeof(char *));
            ///if the realloc failed its will exit from this function.
            if(newItem== NULL) {
                free(toFree);
                newItem = backUp;
                return NULL;
            }
            item = newItem;
            len = strlen(token);
            ///allocating new place for string and copy it.
            temp = (char *) malloc(sizeof(char) * (len + 1));
            if(temp == NULL) {
                free(toFree);
                return NULL;
            }
            strcpy(temp, token);
            item[counter] = temp;
        }
    }
    // after using with the inputString, free this array.
    free(toFree);
    return item;
}

/***********************************************************************************
* Function name: printLang
* Input: Dictionary **dictionaries,int *numOfDictionaries
* Output: None.
* Function Operation: the function print all the dictionaries that sored by order
 * with the languages in each dictionaries:
***********************************************************************************/
void printLang(Dictionary **dictionaries, int *numOfDictionaries){
    printf("Choose a dictionary:\n");
    for (int i = 0; i < *numOfDictionaries; ++i) {
        for (int j = 0; j < (*dictionaries + i)->numOfLanguages; ++j) {
            if (j == 0){
                printf("%d. ",i+1);
            }
            printf("%s",(*dictionaries + i)->languages[j]);
            if (j != ((*dictionaries + i)->numOfLanguages)-1){
                printf(",");
            }
        }
        printf("\n");
    }
}

/***********************************************************************************
* Function name: createDiction
* Input: Dictionary **dictionaries,int *numOfDictionaries.
* Output: True or false( 1 or 0).
* Function Operation: this function creat new dictionaries and update the data :
***********************************************************************************/
int createDiction(Dictionary **dictionaries,int *numOfDictionaries){
    char **item = NULL;
    Dictionary *backUp;
    int numOfLanguages =0, islang = 1;

    // if it's the first dic its allocate one place in the heap by malloc.
    if(numOfDictionaries == 0){
        *dictionaries = (Dictionary *) malloc(sizeof(Dictionary));
        if(*dictionaries == NULL) {
            return 0;
        }
    }else{
        backUp = *dictionaries;
        *dictionaries = (Dictionary *) realloc(backUp,((*numOfDictionaries)+1)*sizeof (Dictionary));
        if(*dictionaries == NULL){
            *dictionaries = backUp;
            return 0;
        }
    }
    printf("Define a new dictionary:\n");
    numOfLanguages = 0;
    //creating an array of pointers to languages and counting the numOfLanguages.
    item = creatLang(&numOfLanguages,islang);
    if(item == NULL) {
        printf("The creation of the dictionary has failed!\n");
        return 0;
    }
    //updating the data to the new dic.
    (*dictionaries+*numOfDictionaries)->languages = item;
    (*dictionaries+*numOfDictionaries)->wordList = NULL;
    (*dictionaries+*numOfDictionaries)->numOfLanguages = numOfLanguages;
    (*numOfDictionaries)++;
    //return success.
    return 1;
}

/***********************************************************************************
* Function name: creat_word
* Input: Dictionary **dictionaries,int *chosenDic(chosenDic to add the word in specific dic).
* Output: True or False(1 or 0).
* Function Operation: this function creat new word and add this word to the
 * specific dic with a linked list of word, returning 1 or 0 depend of success of the operation:
***********************************************************************************/
int creat_word(Dictionary **dictionaries,int *chosenDic){
    int isTran = 0;
    char **trans=NULL;

    int numOflag = (*dictionaries+*chosenDic)->numOfLanguages;
    printf("Enter a word in ");
    //this loop  print the lang that the dic is support.
    for (int i = 0; i < numOflag; ++i) {
        if (i != numOflag - 1) {
            printf("%s,", (*dictionaries + *chosenDic)->languages[i]);
        } else{
            printf("%s:\n", (*dictionaries + *chosenDic)->languages[i]);
        }
    }
    //creating array of pointers by calling creatLang
    //numOfLanguages is not relevant in this case so its 0.
    trans = creatLang( 0, isTran);
    if(trans == NULL){
        return 0;
    }
    //if its success to allocate in trans then allocate place to Word.
    Word *word = (Word *) malloc(sizeof (Word));
    if(word == NULL){
        return 0;
    }
    ///updating data to the new word
    word->translations=trans;
    word->next=NULL;
    //if it is the first word.
    if((*dictionaries+(*chosenDic))->wordList == NULL){
        (*dictionaries+(*chosenDic))->wordList= word;
    }
    else {
        Word *spider;
        spider = (*dictionaries+(*chosenDic))->wordList;

        //lopping until spider is in the last word.
        while(spider->next != NULL){
            spider = spider->next;
        }
        // then connect the new word to the last one.
        spider->next = word;
        spider =NULL;
    }
    return 1;
}

/***********************************************************************************
* Function name: searchWord
* Input: Dictionary **dictionaries,int chosenDic,int isDeleteWord(chosenDic to add the word in specific dic).
* Output: False or True(-1 mean the deletion has canceled or 0 mean fail in allocate
 * or counter(int) the place that the word is store).
* Function Operation: this function check if word is in specific dic:
***********************************************************************************/
int searchWord(Dictionary **dictionaries,int chosenDic,int isDeleteWord){
    char *findThiStr, *maybe, *strToFree;
    int counter = 0,i = 0,keepgoing =0;
    Word * spider = (*dictionaries+(chosenDic))->wordList;
    int numOflag = (*dictionaries+chosenDic)->numOfLanguages;

    printf("Enter a word in %s:\n",(*dictionaries + chosenDic)->languages[0]);
    findThiStr = inputString();
    strToFree = findThiStr;
    if (findThiStr == NULL){
        free(findThiStr);
        if(isDeleteWord){
            return 0;
        }
        printf("The search has failed successfully!\n");
        return 0;
    }
    if(isDeleteWord){
        keepgoing = lastChance();
        if(!keepgoing){
            free(findThiStr);
            return -1;
        }

    }
    //loop the spider all over the words and compare "maybe" to "findThisStr".
    while (spider != NULL){
        counter++;
        //store the trans of the word.
        maybe = spider->translations[0];
        // check the len and the if they are equal compare the context by strcmp.
        if(strlen(findThiStr) == strlen(maybe) && strcmp(maybe,findThiStr) == 0 ){
            if(isDeleteWord){
                free(strToFree);
                //return the place of the word
                return counter;
            }
            //if its not to delete, its print the lang with there trans.
            printf("The translations are:\n");
            for (i = 1; i < numOflag; ++i) {
                printf("%s:", (*dictionaries + chosenDic)->languages[i]);
                printf(" %s", spider->translations[i]);
                if (i != numOflag - 1) {
                    printf(", ");
                }
            }
            printf("\n");
            free(strToFree);
            return 0;
        }else {
            spider = spider->next;
        }
    }
    //if the word is not in the list.
    if(isDeleteWord){
        free(strToFree);
        return 0;
    }
    printf("There are no translations for \"%s\" in this dictionary.\n",findThiStr);
    free(strToFree);
    return 0;
}

/***********************************************************************************
* Function name: freeLang
* Input: Dictionary **dictionaries,int chosenDic, char **strToDele.
* Output: None.
* Function Operation: this function delete the **lang or **trans(in other words string
* of pointers with the strings that the pointers point to:
***********************************************************************************/
void freeLang(Dictionary **dictionaries,int chosenDic, char **strToDele){
    int lenLang = (*dictionaries + chosenDic)->numOfLanguages;

    //loop for delete all the strings.
    for (int i = 0; i < lenLang; ++i) {
        free(strToDele[i]);
    }
    //after delete the strings can to delete the str of pointers.
    free(strToDele);
    strToDele =NULL;
}

/***********************************************************************************
* Function name: deleteWord
* Input: Dictionary **dictionaries,int chosenDic(chosenDic to delete a specific word in the list).
* Output: None.
* Function Operation: this function delete block of type Word(include **trans,*next)
 * without break the linked list:
***********************************************************************************/
void deleteWord(Dictionary **dictionaries,int chosenDic){
    int isToDele = 1, wordIn = 0;
    wordIn = searchWord(dictionaries,chosenDic,isToDele);
    //if the user canceled the deletion.
    if(wordIn == -1){
        printf("The deletion of the word has been canceled.\n");
        return;
    }
    if( wordIn == 0){
        printf("The deletion of the word has failed!\n");
        return;
    }else{
        Word *spider = (*dictionaries+chosenDic)->wordList;
        Word *head = (*dictionaries+chosenDic)->wordList;

        // if the word is in the first place in the list
         if(wordIn == 1){
             //updating the wordlist to NULL,then free the word by temp spider.
            (*dictionaries+chosenDic)->wordList = spider->next;
            freeLang(dictionaries,chosenDic,spider->translations);
            free(spider);
            spider = NULL;
            //if its not in the first place.
         }else{
             //looping until spider is point to the place that we want to delete and head is one place before.
            while (wordIn != 1){
                head = spider;
                spider = spider->next;
                wordIn--;
            }
            head->next = spider->next;
            freeLang(dictionaries,chosenDic,spider->translations);
            free(spider);
            spider= NULL;
        }
        printf("The word has been deleted successfully!\n");
    }
}

/***********************************************************************************
* Function name: freeWordList
* Input: Dictionary **dictionaries,int chosenDic(chosenDic to delete list of specific words in dic).
* Output: None.
* Function Operation: this function delete complete list linked of words.
***********************************************************************************/
void freeWordList(Dictionary **dictionaries,int chosenDic){
    Word *spider = (*dictionaries + chosenDic)->wordList;
    Word *head = (*dictionaries + chosenDic)->wordList;

    //loop to delete all the list by FIFO.
    while (spider != NULL){
        spider = spider->next;
        freeLang(dictionaries,chosenDic,head->translations);
        free(head);
        head = spider;
    }
}

/***********************************************************************************
* Function name: freeChosenDic
* Input: Dictionary **dictionaries,int chosenDic,int *numOfDictionaries)
* Output: True or False(1 or 0 if its succeed or not).
* Function Operation: this function delete full dictionary.
***********************************************************************************/
int freeChosenDic(Dictionary **dictionaries,int chosenDic,int *numOfDictionaries){
    char **strToDele =(*dictionaries + chosenDic)->languages;
    Dictionary *backUp;

    //first freeing the word list and the translation.
    freeWordList(dictionaries,chosenDic);
    freeLang(dictionaries,chosenDic,strToDele);

    ///loop from the chosen dic to end of the arr of dic and copy the next dic to the one before.
    for (int i = chosenDic; i < *numOfDictionaries - 1; ++i) {
        (*dictionaries + chosenDic)->languages = (*dictionaries + (chosenDic+1))->languages;
        (*dictionaries + chosenDic)->numOfLanguages = (*dictionaries + (chosenDic+1))->numOfLanguages;
        (*dictionaries + chosenDic)->wordList = (*dictionaries + (chosenDic+1))->wordList;
        chosenDic++;
    }
    ///after the loop the last dic is not relevant and we can realloc
    backUp = *dictionaries;
    *dictionaries = (Dictionary *) realloc(*dictionaries,(*numOfDictionaries-1)*sizeof (Dictionary ));
    if (*dictionaries == NULL && *numOfDictionaries != 1){
        *dictionaries = backUp;
        return 1;
    }
    (*numOfDictionaries)--;
    return 0;
}

/***********************************************************************************
* Function name: leaveProgram
* Input: Dictionary **dictionaries,int numOfDictionaries.
* Output: None.
* Function Operation: this function free all the allocated memory and exit.
***********************************************************************************/
void leaveProgram(Dictionary **dictionaries,int numOfDictionaries){
    //each round the int numOfDictionaries get descend in 1 in the function freeChosenDic
    //and always the first dic deleted until numOfdic is 0.
    for (int i = 0; i < numOfDictionaries;) {
        freeChosenDic(dictionaries,i,&numOfDictionaries);
    }
    free(*dictionaries);
}

/***********************************************************************************
* Function name: menu
* Input: Dictionary **dictionaries,int numOfDictionaries.
* Output: return 1 or 0(True or False/keep lopping the main or not).
* Function Operation: this function asking the user for command.
***********************************************************************************/
int menu(Dictionary **dictionaries,int *numOfDictionaries){
    char option, key,isSureToDele,addDic = 0,isNotDelWor=0,addWord = 0;
    int counter = 0,chosenDic =0,didIt=0;

    scanf(" %c", &option);
    key = option;
    // clean the buffer after storing the key.
    while (option != '\n'){
        scanf("%c",&option);
        counter++;
    }
    //if the user enter more than 1 digit it's going by default
    if (counter > 1){
        key = 'a';
    //if there is no dic initialize can't press 1-5, return to the options.
    } else if(*numOfDictionaries == 0 && key > '1' && key < '6'){
        printf("This option is not available right now, try again:\n");
        menu(dictionaries,numOfDictionaries);
        return 1;
    }

    switch (key) {
        case '1':
            addDic = createDiction(dictionaries,numOfDictionaries);
            if (addDic){
                printf("The dictionary has been created successfully!\n");
            }
            //if addDic got failed in the way.
            else{
                printf("The creation of the dictionary has failed!\n");
            }
            return 1;
        case '2':
            printLang(dictionaries, numOfDictionaries);
            scanf("%d",&chosenDic);
            //if the user asking dic that is not available.
            if(chosenDic > *numOfDictionaries || chosenDic < 1){
                printf("This option is not available right now, try again:\n");
                return 1;
            }
            //dec chosenDic for getting the correct index in list.
            chosenDic--;
            addWord = creat_word(dictionaries,&chosenDic);
            if (addWord){
                printf("The word has been added successfully!\n");
            }else {
                printf("The addition of the word has failed!\n");
            }
            return 1;
        case '3':
            printLang(dictionaries, numOfDictionaries);
            scanf("%d",&chosenDic);
            //if the user asking dic than is not available.
            if(chosenDic > *numOfDictionaries || chosenDic < 1){
                printf("This option is not available right now, try again:\n");
                return 1;
            }
            chosenDic--;
            deleteWord(dictionaries,chosenDic);
            return 1;

        case '4':
            printLang(dictionaries, numOfDictionaries);
            scanf("%d",&chosenDic);
            //if the user asking dic than is not available.
            if(chosenDic > *numOfDictionaries|| chosenDic < 1){
                printf("This option is not available right now, try again:\n");
                return 1;
            }
            chosenDic--;
            searchWord(dictionaries,chosenDic,isNotDelWor);
            return 1;
        case '5':
            printLang(dictionaries, numOfDictionaries);
            scanf("%d",&chosenDic);
            //if the user asking dic than is not available.
            if(chosenDic > *numOfDictionaries || chosenDic < 1){
                printf("This option is not available right now, try again:\n");
                return 1;
            }
            chosenDic--;
            printf("Are you sure? (y/n)\n");
            scanf(" %c",&isSureToDele);
            if( isSureToDele == 'y'){
                didIt = freeChosenDic(dictionaries,chosenDic,numOfDictionaries);
                if(didIt){
                    printf("The deletion of the dictionary has failed!\n");
                    return 1;
                }
                printf("The dictionary has been deleted successfully!\n");
            }else {
                printf("The deletion of the dictionary has been canceled.\n");
            }


            return 1;
        case '6':
            leaveProgram(dictionaries,*numOfDictionaries);
            printf("Bye!\n");
            return 0;
        default:
            printf("Wrong option, try again:\n");
            return 1;
    }
}
int main() {
    Dictionary* dictionaries = NULL;
    int numOfDictionaries = 0, isOn = 1;

    while (isOn != 0){
        printf("Welcome to the dictionaries manager!\nChoose an option:\n1. Create a new dictionary."
               "\n2. Add a word to a dictionary.\n3. Delete a word from a dictionary.\n"
               "4. Find a word in a dictionary.\n5. Delete a dictionary.\n6. Exit.\n");
        isOn = menu(&dictionaries,&numOfDictionaries);
    }
    return 0;
}
