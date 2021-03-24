#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node_type{
    char key;
    struct node_type *left, *right;
}BSTNodeT;

BSTNodeT *createNode(char key)
{
    BSTNodeT *p = (BSTNodeT*)malloc(sizeof(BSTNodeT));

    if(p != NULL)
    {
        p->key = key;
        p->left = NULL;
        p->right = NULL;
    }
    return p;
}

void getTheOperation(char operation, char secondoperation, BSTNodeT *root, FILE *fo)
{
    switch(operation)
    {

    case 'i':
        {
            insertNode(root, secondoperation, fo);
            break;
        }


    case 'd':
        {
            delNode(root, secondoperation, fo);
            break;
        }

    case 'f':
        {
            if(find(root, secondoperation) != NULL)
                fprintf(fo, "\nThe key = %c is present in a node\n", secondoperation);
            else
                fprintf(fo, "The key %c was not found", secondoperation);
            break;
        }
    case 't':
        {
            switch(secondoperation)
            {
            case 'p':
                {
                    preorder(root, fo);
                    fprintf(fo, "\n");
                    break;
                }

            case 'P':
                {
                    postorder(root, fo);
                    fprintf(fo, "\n");
                    break;
                }

            case 'i':
                {
                    inorder(root, fo);
                    fprintf(fo, "\n");
                    break;
                }

            default:
                {
                    fprintf(fo, "\nSomething's wrong!\n");
                    break;
                }
            }
        }

    case 'g':
        {
            switch(secondoperation)
            {

            case 'm':
                {
                    BSTNodeT* min = findMin(root);
                    fprintf(fo, "\nThe minimum is %c\n", min->key);
                    break;
                }

            case 'M':
                {
                    BSTNodeT* max = findMax(root);
                    fprintf(fo, "\nThe maximum is %c\n", max->key);
                    break;
                }

            default:
                {
                    fprintf(fo, "\nSomething's wrong!\n");
                    break;
                }
            }
        }

    default:
        {
            fprintf(fo, "\nSomething's wrong!\n");
            break;
        }
    }
}

BSTNodeT *insertNode(BSTNodeT *root, char key, FILE *fo)
{
    if(root == NULL)
        root = createNode(key);
    else
    {
        if(key < root->key)
            root->left = insertNode(root->left, key, fo);
        else if(key > root->key)
            root->right = insertNode(root->right, key, fo);
        else
            printf( "\nNode with key = %c already exists in the tree\n", key);

    }
    return root;
}

BSTNodeT *find(BSTNodeT *root, char givenKey)
{
    if(root == NULL)
        return NULL;
    for(BSTNodeT *p = root; p!=NULL;)
    {
        if(givenKey == p->key)
            return p;
        else
            if(givenKey < p->key)
            p = p->left;
            else
                p = p->right;
    }
    return NULL;
}

BSTNodeT *findMin(BSTNodeT* node)
{
    if(node == NULL)
    {
        return NULL;
    }
    if(node->left)
        return findMin(node->left);
    else
        return node;
}

BSTNodeT *findMax(BSTNodeT *node)
{
    if(node == NULL)
    {
        return NULL;
    }
    if(node->right)
        return findMax(node->right);
    else
        return node;
}

BSTNodeT *delNode(BSTNodeT* node, char key, FILE *fo)
{
    if(node == NULL)
    {
        fprintf(fo, "Element was not found");
    }
    else if(key < node->key)
    {
        node->left = delNode(node->left, key, fo);
    }
    else if(key > node->key)
    {
        node->right = delNode(node->right, key, fo);
    }
    else
    {
        if(node->right && node->left)
        {
            BSTNodeT *temp = findMin(node->right);
            node->key = temp->key;
            node->right = delNode(node->right, temp->key, fo);
        }
        else
        {
            BSTNodeT *temp = node;
            if(node->left == NULL)
                node = node->right;
            else if(node->right == NULL)
                node = node->left;
            free(temp);
        }
    }
    return node;
}

void preorder(BSTNodeT *p, FILE *fo)
{
    if(p != NULL)
    {
        fprintf(fo, "%c ", p->key);
        preorder(p->left, fo);
        preorder(p->right, fo);
    }
}

void inorder(BSTNodeT *p, FILE *fo)
{
    if(p != NULL)
    {
        inorder(p->left, fo);
        fprintf(fo, "%c ", p->key);
        inorder(p->right, fo);
    }
}

void postorder(BSTNodeT *p, FILE *fo)
{
    if(p != NULL)
    {
        postorder(p->left, fo);
        postorder(p->right, fo);
        fprintf(fo, "%c ", p->key);
    }
}

int main(int argc, char* argv[])
{
    char fileOperation[5];

    FILE *fi = fopen(argv[1], "r");
    FILE *fo = fopen(argv[2], "w");

    BSTNodeT *root = createNode(' ');

    while(fscanf(fi, "%s", &fileOperation) != EOF)
    {
        getTheOperation(fileOperation[0], fileOperation[1], root, fo);
    }

    fclose(fo);
    fclose(fi);

    return 0;
}
