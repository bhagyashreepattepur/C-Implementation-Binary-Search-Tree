#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    char name[50];
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* insert(TreeNode* root, char* name) {
    if (root == NULL) {
        TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
        strcpy(new_node->name, name);
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }
    int cmp = strcmp(name, root->name);
    if (cmp < 0) {
        root->left = insert(root->left, name);
    } else if (cmp > 0) {
        root->right = insert(root->right, name);
    }
    return root;
}

TreeNode* search(TreeNode* root, char* name) {
    if (root == NULL) {
        return NULL;
    }
    int cmp = strcmp(name, root->name);
    if (cmp == 0) {
        return root;
    } else if (cmp < 0) {
        return search(root->left, name);
    } else {
        return search(root->right, name);
    }
}

TreeNode* delete(TreeNode* root, char* name) {
    if (root == NULL) {
        return NULL;
    }
    int cmp = strcmp(name, root->name);
    if (cmp < 0) {
        root->left = delete(root->left, name);
    } else if (cmp > 0) {
        root->right = delete(root->right, name);
    } else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        } else {
            TreeNode* temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            strcpy(root->name, temp->name);
            root->right = delete(root->right, temp->name);
        }
    }
    return root;
}

void display(TreeNode* root, int level) {
    if (root != NULL) {
        display(root->right, level + 1);
        printf("\n");
        for (int i = 0; i < level; i++) {
            printf("    ");
        }
        printf("%s", root->name);
        display(root->left, level + 1);
    }
}

int main() {
    TreeNode* root = NULL;
    char command[10], name[50];
    while (1) {
        printf("\n> ");
        scanf("%s", command);
        if (strcmp(command, "insert") == 0) {
            scanf("%s", name);
            root = insert(root, name);
            printf("%s inserted", name);
        } else if (strcmp(command, "search") == 0) {
            scanf("%s", name);
            TreeNode* node = search(root, name);
            if (node == NULL) {
                printf("%s not found", name);
            } else {
                printf("%s found", name);
            }
        } else if (strcmp(command, "delete") == 0) {
            scanf("%s", name);
            root = delete(root, name);
            printf("%s deleted", name);
        } else if (strcmp(command, "display") == 0) {
            printf("\nDirectory Structure:\n");
            display(root,0);
        }
    }
}
