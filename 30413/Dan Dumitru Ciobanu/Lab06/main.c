#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*I've realised at the end that I have forgotten to modify the delete function, as it can not function if there is only one element in the list of the indexed array.
I have used a simple hash function based on the alphabet, such that I would not get a nasty number of collision, but the chance of collision is still 1 in 26 for the first try:))
I will make the delete function to work properly, unfortunately, after the deadline. I wanted to try a different type of reading, but it did not work and I've wasted some precious time on it
I'm sorry for not having a lot of comments and for the bad-looking code.*/

typedef struct node
{
    char firstName[15];
    char lastName[15];
    struct node* next;
}Node;

Node* first[26];

unsigned int hashFunction(const char* firstName)
{
    //printf(" Pentru hash avem numele %s\n", firstName);
    //printf("%d", tolower(firstName[0])-'a');
    return tolower(firstName[0])-'a';
}

void insert(unsigned int key, const char* firstName, const char* lastName)
{
    Node* newptr = (Node*)malloc(sizeof(Node));

    strcpy(newptr -> lastName, lastName);
    strcpy(newptr -> firstName, firstName);
    newptr -> next = NULL;
    //printf("inserare: %s", newptr->firstName);
    //printf("%s\n", newptr->lastName);

    if(first[key] == NULL)
    {
        first[key] = newptr;
        /*strcpy(first[key] -> firstName, newptr -> firstName);
        strcpy(first[key] -> lastName, newptr -> lastName);
        first[key] -> next = newptr -> next;*/
    }
    else
    {
        Node* temp = (Node*)malloc(sizeof(Node));
        strcpy(temp -> firstName, first[key] -> firstName);
        strcpy(temp -> lastName, first[key] -> lastName);
        temp -> next = NULL;

        newptr -> next = first[key] -> next;
        first[key] -> next = newptr;
        strcpy(first[key] -> firstName, newptr -> firstName);
        strcpy(first[key] -> lastName, newptr -> lastName);

        strcpy(newptr -> firstName, temp -> firstName);
        strcpy(newptr -> lastName, temp -> lastName);

        free(temp);
    }
}

void deleteNodeByName(unsigned int key, const char* firstNameToDelete, const char* lastNameToDelete, FILE* fOut)
{
    if(first[key] == NULL)
    {
        fprintf(fOut,"Not found\n");
    }
    else
    {
        Node* pretracker = first[key];
        Node* tracker = first[key] -> next;

        while(tracker != NULL && ( (strcmp(tracker -> lastName, lastNameToDelete) != 0) && (strcmp(tracker -> firstName, firstNameToDelete) != 0) ))
        {
            pretracker = tracker;
            tracker = tracker -> next;
        }
        if(tracker == NULL)
        {
            fprintf(fOut, "Not found!\n");
        }
        else
        {
            pretracker -> next = tracker -> next;
            free(tracker);
            return;
        }
    }
}

void findByName(int key, const char* firstNameToFind, const char* lastNameToFind, FILE* fOut)
{
    if(first[key] == NULL)
    {
        fprintf(fOut, "No\n");
        return;
    }
    else
    {
        Node* tracker = first[key];
        int index = 0;
        while(tracker != NULL)
        {
            if((strcmp(tracker -> lastName, lastNameToFind) == 0) && (strcmp(tracker -> firstName, firstNameToFind) == 0))
            {
                fprintf(fOut, "Yes, row: %d, place: %d\n", key, index);
                return;
            }
            else
            {
                tracker = tracker -> next;
                index++;
            }
        }
        fprintf(fOut, "No\n");
    }
}

void list(FILE* fOut)
{
    int index;
    Node* head;

    for(index = 0; index < 26; index++)
    {
        if(first[index] == NULL)
        {
            //printf("ERROR(Nothing) on row: %d\n", index);
            fprintf(fOut, "ERROR(Nothing) on row: %d\n", index);
        }
        else
        {
            head = first[index];
            int index2 = 0;
            while(head != NULL)
            {
                fprintf(fOut, "%d.%d: %s %s\n", index, index2, head -> firstName, head -> lastName);
                index2++;
                head = head -> next;
            }
        }
    }
}

/*void getTheOperations(FILE* fIn, FILE* fOut)
{
    char firstN[25];
    char lastN[25];
    char option;

    while(fscanf(fIn, "%c%s %s", &option, firstN, lastN))
    {
        unsigned int localHash = hashFunction(firstN, lastN);
        switch(option)
        {
            case 'i':
                {
                    insert(localHash, firstN, lastN);
                    break;
                }

            case 'f':
                {
                    findByName(localHash, firstN, lastN, fOut);
                    break;
                }

            case 'd':
            {
                deleteNodeByName(localHash, firstN, lastN, fOut);
                break;
            }

            case 'l':
            {
                list(fOut);
                break;
            }

            default:
                {
                    fprintf(fOut, "There is no such option!\n");
                }

          }
    }
}*/

void readInstructions(FILE* fIn, FILE* fOut)
{
    char string[50];
    char* firstN;
    char* lastN;
    while(fgets(string, 50, fIn))
    {
        if(string[0] != 'l')
        {string[strlen(string)-1] = '\0';
        firstN = strtok(string+1, " ");
        //printf("\n%s ", firstN);
        lastN = strtok(NULL, " ");
        //printf("%s\n", lastN);
        //if(string[0] != '')
        //unsigned int localHash = hashFunction(firstN);
        //printf("\n%c\n", string[0]);

        switch(string[0])
        {
            case 'i':
                {
                    unsigned int localHash = hashFunction(firstN);
                    insert(localHash, firstN, lastN);
                    break;
                }

            case 'f':
                {
                    unsigned int localHash = hashFunction(firstN);
                    findByName(localHash, firstN, lastN, fOut);
                    break;
                }

            case 'd':
            {
                unsigned int localHash = hashFunction(firstN);
                deleteNodeByName(localHash, firstN, lastN, fOut);
                break;
            }

            default:
                {
                    fprintf(fOut, "There is no such option!\n");
                }

          }}
          else
          {
              list(fOut);
          }

    }
}

int main()
{
    FILE* fIn = fopen("datain.txt", "r");
    FILE* fOut = fopen("dataout.txt", "w");
    if(fIn == NULL || fOut == NULL)
    {
        printf("error");
        exit(0);
    }
    readInstructions(fIn, fOut);
    fclose(fIn);
    fclose(fOut);
    return 0;
}
