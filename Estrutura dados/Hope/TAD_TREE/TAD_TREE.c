#include "TAD_TREE.h"
#include "../TAD_LISTA/TAD_LISTA.h"
#include <stdlib.h>
#include <stdio.h>

/*IS IT EMPTY?
    respondes this question: is this tree empty?

Params
    root: pointer to a root node of a tree.

Return
    True if the tree is empty, otherwise false.
*/
int tree_empty(Node* root){
    return root == NULL;
}

/* CREATE AN ENPTY TREE
    Creates a empty tree.

Return
    (Node*)NULL, representing a empty tree.
*/
Node* tree_create_empty(){
    return (Node*)NULL;
}

/*CREATE A NODE
    Creates a node with an info and left and right sub-tree.

Params
    info: pointer to a information.
    lst: pointer to a node root of a left sub-tree.
    rst: pointer to a node root of a right sub-tree.

Return
    pointer to a new node (Node*).
*/
Node* tree_create_node(void* info, Node* lst, Node* rst){
    // Allocates memory for the new node
    Node* new_node = (Node*) malloc (sizeof(Node));
    
    if(!new_node){
        printf("We ran out of memory trying to create a node...\n");
        exit(1);
    }

    // Sets the node fields (info, lst and rst)
    new_node->info = info;
    new_node->lst = lst;
    new_node->rst = rst;
 
    // Returns the created node
    return new_node;
}

/*INSERT A NODE
    Inserts a node in a tree based on a comparison.
    If it's true, the new_node will be placed in the left sub-tree, 
    if it's false, the new_node will be in the right sub-tree.

Params
    root: pointer to the root of the tree
    new_node: pointer to the new node
    compare: callback function that compares two elements

Return
    True if the new_node was placed in the tree,
    otherwise false.
*/
Node* tree_insert_node(Node* root, Node* new_node, int (compare)(void*, void*)) {
    if (tree_empty(root)) return new_node;

    if (compare(new_node->info, root->info)) {
        root->lst = tree_insert_node(root->lst, new_node, compare);
    } else {
        root->rst = tree_insert_node(root->rst, new_node, compare);
    }

    return root;
}

/*FREE A TREE
    free memory of all elements in a tree/subtree starting from the "root" node.

Params
    root: a node of a tree/subtree that you would like to free.
*/
void tree_free(Node* root){
    if(root != NULL){
        tree_free(root->lst);
        tree_free(root->rst);
        free(root->info);
        free(root);
    }
}

/*PERFORM OPERATION IN A TREE 
    perform an operation in all elements of a tree. 
Params
    Node* root = receives the head of the tree 
    void (operation)(void*) = callback operation that will be applied to the intere tree
*/ 
void tree_map(Node* root, void (operation)(void*)){
    if (tree_empty(root))
        return; //checks if the tree is empty, if it is, returns.
    
    tree_map(root->lst,operation);//do the operation only on the left side of the root 
    operation(root->info);//apply to the current node 
    tree_map(root->rst,operation);//do all the same but on the right side }
}

/*INSERT ALL ELEMENTS IN A TREE
    insert all elements in a tree/subtree starting from the "root" node.

Params
    source: pointer to the root of the subtree to be copied
    dest: pointer to the root of the destination tree
    copy_node: callback function that returns a copy of the element
    compare: callback function that compares two elements
*/
void insert_all(Node* source, Node** dest, void* (copy_info)(void*), int (compare)(void*, void*)) {
    // Condição de parada, caso a arvore seja vazia ou chegue ao fim
    if (tree_empty(source)) return; 

    // Copia o nó
    Node* copied_node = tree_create_node(copy_info(source->info),tree_create_empty(),tree_create_empty());

    // Insere o nó copiado na arvore na arvore de destino
    *dest = tree_insert_balanced(*dest, copied_node, compare);

    // Chamada recursiva para o filho esquerdo
    insert_all(source->lst, dest, copy_info, compare);

    // Chamada recursiva para o filho direito
    insert_all(source->rst, dest, copy_info, compare);
}

/*COPY A NODE 
    copy a node of a tree.
Params
    original_node: pointer to the original node.

Returns
    pointer to a copied node.
*/


/*FILTER ELEMENTS IN THE TREE INTO A LIST
    Gather together a set of elements that satisfy condition inside the tree, creating a list of nodes.
 
 Params
    root: pointer to the root of the tree
    condition: callback function that returns true if the element satisfies the condition
    copy_node: callback function that returns a copy of the element
 
 Return
    Pointer to the head of a list composed by the elements
    that satisfy the condition.
*/
Lista* tree_filter_as_list(Node* root, int (condition)(void*), void* (copy_info)(void*), int (compare)(void*, void*)){

    if(tree_empty(root))
        return (Lista*)NULL;
    
    Lista* this_level_list = lst_cria();

    
    Lista* leftsubtree_list = tree_filter_as_list(root->lst, condition, copy_info, compare);
    Lista* rightsubtree_list = tree_filter_as_list(root->rst, condition, copy_info, compare);
    this_level_list = lst_merge(leftsubtree_list,rightsubtree_list, compare);
    
    if(condition(root->info)){
        this_level_list = lst_insere(this_level_list,copy_info(root->info),compare);
    }
    
    return this_level_list;
}

/*FILTER ELEMENTS IN THE TREE CREATING A NEW TREE
    Gather together a set of elements that satisfy condition inside the tree.
 
 Params
    root: pointer to the root of the tree
    condition: callback function that returns true if the element satisfies the condition
    copy_node: callback function that returns a copy of the element
    compare: callback function that compares two elements
 
 Return
    Pointer to the root of a tree composed by the elements
    that satisfy the condition.
*/
Node* tree_filter(Node* root, int (condition)(void*), void* (copy_info)(void*), int (compare)(void*, void*)) {
    // Se a arvore for vazia, retorna uma arvore vazia
    if (tree_empty(root)) 
        return tree_create_empty();

    // Cria uma nova arvore para armazenar os elementos filtrados
    Node* filtered_tree = tree_create_empty();

    // Verifica se o elemento atual satisfaz a condicao, se sim
    // copia ele e insere na nova arvore
    if (condition(root->info)) {
        Node* copied_node = tree_create_node(copy_info(root->info),tree_create_empty(),tree_create_empty());

        filtered_tree = tree_insert_balanced(filtered_tree, copied_node, compare);
    }

    // Filtra recursivamente os nós da subárvore esquerda e direita
    Node* left_filtered = tree_filter(root->lst, condition, copy_info, compare);
    Node* right_filtered = tree_filter(root->rst, condition, copy_info, compare);

    // Insere todos os nós filtrados da esquerda e da direita na nova árvore
    insert_all(left_filtered, &filtered_tree, copy_info, compare);
    insert_all(right_filtered, &filtered_tree, copy_info, compare);

    return filtered_tree;
}

/*VERIFIES THE HEIGHT OF THE NODE
    Receives a node that calculates his height on the tree

 Params
    node: pointer to the root of the tree

 Return
    An integer for the height 
*/
int tree_get_height(Node* node) {
    if (tree_empty(node)) return -1; // Altura de NULL é -1 (por convenção)

    int left_height = tree_get_height(node->lst);
    int right_height = tree_get_height(node->rst);

    return 1 + (left_height > right_height ? left_height : right_height);
}

/*ROTATES THE TREE TO THE RIGHT
    Executes a rotation to the right, to fix the imbalance
    when the left subtree is heavier

 Params
    root: pointer to the root of the tree

 Return
    A pointer (Node*) to the new root
*/
Node* rotate_right(Node* root) {
    Node* node_lst = root->lst;          // node_lst é o filho da esquerda de root
    Node* node_lst_rst = node_lst->rst;  // node_lst_rst é a subárvore a direita de node_lst (filho esquerdo de root)

    node_lst->rst = root;                // a direita de node_lst agora aponta para root
    root->lst = node_lst_rst;            // a esquerda de root agora aponta para node_lst_rst (subárvore a direita do filho a esquerda de root)

    return node_lst;                     // node_lst se torna a nova raiz do subárvore
}

/*ROTATES THE TREE TO THE LEFT
    Executes a rotation to the left, to fix the imbalance
    when the right subtree is heavier

 Params
    root: pointer to the root of the tree

 Return
    A pointer (Node*) to the new root
*/
Node* rotate_left(Node* root) {
    Node* node_rst = root->rst;          // node_rst é o filho a direita de root
    Node* node_rst_lst = node_rst->lst;  // node_rst_lst é a subárvore a esquerda de node_rst (filho a direita de root) 

    node_rst->lst = root;                // node_rst agora aponta para root
    root->rst = node_rst_lst;            // a direita de root agora aponta para node_rst_lst (subárvore a esquerda do filho a direita de root)

    return node_rst;                     // node_lst se torna a nova raiz do subárvore
}

/*INSERTS A NEW NODE WHILE BALANCING THE TREE 
    Inserts a new node like a BST, but balancing the tree
    after each insertion to keep it balanced

 Params
    root: pointer to the root of the tree
    new_node: pointer to the new node
    compare: callback function that compares two elements

 Return
    A pointer (Node*) to the new root
*/
Node* tree_insert_balanced(Node* root, Node* new_node, int (compare)(void*, void*)) {
    // Se a arvore estiver vazia, adiciona o novo nó na raiz
    if (tree_empty(root))
        return new_node;

    // Insire o novo nó como uma BST normal
    if (compare(new_node->info, root->info)) {
        root->lst = tree_insert_balanced(root->lst, new_node, compare);
    } else {
        root->rst = tree_insert_balanced(root->rst, new_node, compare);
    }

    // Calcula o fator de balanceamento
    // balance_factor > 1: subárvore esquerda muito pesada
    // balance_factor < -1: subárvore direita muito pesada
    int balance_factor = root ? tree_get_height(root->lst) - tree_get_height(root->rst) : 0;

    // Caso Left Left
    if (balance_factor > 1 && compare(new_node->info, root->lst->info))
        return rotate_right(root);

    // Caso Right Right 
    if (balance_factor < -1 && !compare(new_node->info, root->rst->info))
        return rotate_left(root);

    // Caso Left Right 
    if (balance_factor > 1 && !compare(new_node->info, root->lst->info)) {
        root->lst = rotate_left(root->lst);
        return rotate_right(root);
    }

    // Caso Right Left 
    if (balance_factor < -1 && compare(new_node->info, root->rst->info)) {
        root->rst = rotate_right(root->rst);
        return rotate_left(root);
    }

    return root;
}

/*TREE SEARCH
   Search the first element that satisfies the condition inside the tree.

Parameters
   Node* root - receives the root of the tree.
   int (condition)(void) - a callback that receives the node info
   and returns a non-zero value if the condition is satisfied.

Return
   A pointer (Node*) to the first node that satisfies the condition.
*/
Node* tree_search(Node* root, int (condition)(void*)){
    
    // If tree is empty, return NULL
    if (tree_empty(root))
    {
        return NULL;
    }

    // If current node satisfies the condition, return it
    if(condition(root->info))
    {
        return root;
    }

    //Result to save result of the search
    Node* result;

    // Search in the left subtree
    result = tree_search(root->lst,condition);

    //If you found the result, ok
    if(result != NULL)
    {
        return result;
    }

    // If you haven't found it yet, try the right side
    result = tree_search(root->rst,condition);

    return result;
}

/*WRITE IN ORDER
    Recursively writes the contents of a binary tree to a file using
     symmetric order.
 
Return
  (void) – does not return any value.
 
Parameters
  Node* new_node – current node to process.
  FILE* fp – file pointer to the opened text file where data will be written.
  char* (create_line)(void*) – function that receives the node's info and
  returns a dynamically allocated string to be written into the file.
*/
void write_inorder(Node *new_node, FILE *fp, char* (*create_line)(void*))
{
    if (new_node == NULL)
    return;

    write_inorder(new_node->lst,fp,create_line); //Visit left subtree
    char * line = create_line(new_node->info); // Generate a formatted string from the node's info
    if (line != NULL)
    {
        fprintf(fp,"%s",line); // Write the line to the file
        free(line); // Free the memory allocated by create_line
    }
    write_inorder(new_node->rst,fp,create_line); //Visit right subtree
}

/*TREE TO FILE
    Save all elements from the tree to a text file using in-order traversal.

Parameters
    Node* root - receives the root of the tree.
    char* file_name - receives the name of the file to be created.
    char* (create_line)(void) - function that receives a node’s info,
    returns a formatted string to be saved in the file.
    This function must return a dynamically allocated string,
    which will be freed after being written.

Return
    (void) - does not return anything.
*/
void tree_to_file(Node* root, char* file_name, char* (create_line)(void*)){
    FILE * fp = fopen(file_name,"wt"); //create an anchive
    if(fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    // Start writing from the root
    write_inorder(root,fp,create_line);

    // Close the file
    fclose(fp);
    
}

/*LOAD A BINARY TREE FROM A TEXT FILE 
    Reads a text file line by line, converts each line into data (using read_line),
    creates a node for each data item, and inserts it into the tree in order using the compare function.

Return
    A pointer to the root of the constructed tree (Node*)

Parameters
    file_name: name of the file to read
    read_line: function that converts a line (char*) into generic data (void*)
    compare: function used to order nodes upon insertion
*/
Node* tree_load_from_file(char* file_name, void* (read_line)(char*), int (compare)(void*, void*)){
    // Open the file in text mode for reading
    FILE* fp = fopen(file_name, "rt");

    // Check if the file was opened successfully
    if(!fp){
        printf("Error: file %s could not be opened.\n", file_name);
        exit(1);
    }

    // Buffer to temporarily store each line read from the file
    char recovered_line[121];

    // Create an empty tree
    Node* root = tree_create_empty();

    // Read the file line by line
    while(fgets(recovered_line, 121, fp) != NULL){
        // Remove the newline character if present
        recovered_line[strcspn(recovered_line, "\n")] = '\0';

        // Create a new node with the processed data and insert it into the tree
        Node* new_node = tree_create_node(read_line(recovered_line), NULL, NULL);
        root = tree_insert_node(root, new_node, compare);
    }

    // Close the file
    fclose(fp);

    // Return the root of the constructed tree
    return root;
}