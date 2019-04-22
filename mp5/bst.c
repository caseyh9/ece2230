/* bst.c 
 * Casey Hird
 * crhird@g.clemson.edu
 * ECE 2230 Spring 2019
 * MP 5
 *
 * Implementation of tree interface for basic binary tree
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>

#include "bst.h"

#define MYMAX(a, b) (a > b ? a : b)
// counters for statistics
int CompCalls = 0;
int NumRotations = 0;


/* definitions for use in bst.c only */
void ugly_print(bst_node_t *N, int level, int policy);
int bst_debug_validate_rec(bst_node_t *N, int min, int max, int *count);
int rec_height(bst_node_t *N);
int children(bst_node_t *N);
void pretty_print(bst_t *T);
// Added helper functions
void bst_destruct_nodes(bst_node_t *root);
bst_node_t* insert_node(bst_node_t *node, bst_key_t key, data_t elem_ptr, int policy);
bst_node_t* rotate_right(bst_node_t* node);
bst_node_t* rotate_right(bst_node_t* node);


/* Finds the tree element with the matching key and returns the data that is
 * stored in this node in the tree.
 *
 * T - tree to search in key - key to find inside T
 *
 * RETURNS pointer to the data stored in the found node or NULL if no match is
 * found
 */
data_t bst_access(bst_t *T, bst_key_t key)
{
	// Initialize loop variables
    CompCalls = 0;
	bst_node_t *node = bst_t->root;

	// Loop until reaching a NULL node (child of leaf)
	while (node != NULL)
	{
		// Check if the key is found at the current node
		CompCalls++;
		if (key == node->key)
		{
			// If found, return the data pointer in this node
			return node->data_ptr; // FIXME data pointer?
		}
		// If we need to keep searching, compare keys
		CompCalls++;
		if (key < node->key)
		{
			// key is less than current node, go left
			node = node->left;
		}
		else
		{
			// key is greater than current node, go right
			node = node->right;
		}
	}
	// Update tree stats
	T->num_recent_key_comparisons = CompCalls;
	// If matching key was not found, return NULL
    return NULL;
}

/* Creates the header block for the tree with the provided management policy,
 * and initializes it with default 'blank' data.
 *
 * tree_policy - tree management policy to use either AVL or BST.
 *
 * RETURNS pointer to the newly created tree
 */
bst_t *bst_construct(int tree_policy)
{
	// Check that tree_policy is an acceptable value
	assert(tree_policy == AVL || tree_policy == BST);

	// Allocate memory for tree header
	bst_t *tree = (bst_t*) malloc(sizeof(bst_t));
	// Set root to NULL
	tree->root = NULL;
	// Set policy
	tree->policy = tree_policy;
	// Set all other info to 0
	tree->size = 0;
	tree->num_recent_rotations = 0;
	tree->num_recent_key_comparisons = 0;
	// Return pointer to new tree
	return tree;
}


/* Free all items stored in the tree including the memory block with the data
 * and the bst_node_t structure.  Also frees the header block.  
 *
 * T - tree to destroy
 */

void bst_destruct(bst_t *T)
{
	// Recursively destroy all nodes with helper function
	bst_destruct_nodes(T->root);
	// Free bst header
	free(T);
}

/* Destroy the tree that has the node passed in at its root. So, we are
 * destroying the given node and every child that can be reached from it.
 *
 * root - the root of the tree being destroyed
 */
void bst_destruct_nodes(bst_node_t *root)
{
	// If root is NULL, do nothing
	if (root == NULL)
	{
		return;
	}
	// Recusively destroy an children
	bst_destruct_nodes(root->left);
	bst_destruct_nodes(root->right);
	// Destroy the data in the node
	free(root->data_ptr);
	root->data_ptr = NULL;
	// Remove dangling pointers from children
	root->left = NULL;
	root->right = NULL;
	// Free root memory
	free(root);
}

/* Insert data_t into the tree with the associated key. Insertion MUST
 * follow the tree's property (i.e., AVL or BST)
 *
 * T - tree to insert into
 * key - search key to determine if key is in the tree
 * elem_ptr - data to be stored at tree node indicated by key
 *
 * RETURNS 0 if key is found and element is replaced, and 1 if key is not found
 * and element is inserted
 */

int bst_insert(bst_t *T, bst_key_t key, data_t elem_ptr)
{
    CompCalls = 0;
    NumRotations = 0;
	int insertion = -1;
	
	// Check if key is already in tree
	bst_node_t *node = T->root;
	while (node != NULL)
	{
		CompCalls++;
		if (node->key = key)
		{
			// replace with data given
			node->data_ptr = elem_ptr;
			return 0;
		}
		// Move to appropriate child
		CompCalls++;
		if (node->key < key)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}

	// If key not found, insert new node
	if (insertion == -1)
	{
		// For avl property, go to avl insertion
		if (T->policy == AVL)
		{
			insertion = bst_avl_insert(T,key,elem_ptr);
		}
		// Otherwise, use normal insertion
		else
		{
			insertion = 1;
			T->root = insert_node(T->root, key, elem_ptr, T->policy); // FIXME set to root?????
		}
		// Update tree size
		(T->size)++;
	}

	// Update tree stats
	T->num_recent_rotations = NumRotations;
	T->num_recent_key_comparisons = CompCalls;

#ifdef VALIDATE
        bst_debug_validate(T);
#endif
    return insertion;
}

/* Insert data_t into the tree with the associated key. Insertion MUST
 * follow the tree's property AVL. This function should be called from
 * bst_insert for AVL tree's inserts.
 *
 * T - tree to insert into
 * key - search key to determine if key is in the tree
 * elem_ptr - data to be stored at tree node indicated by key
 *
 * Precondition: there is not already a node in tree T with the given key
 *
 * RETURNS 0 if key is found and element is replaced, and 1 if key is not found
 * and element is inserted
 */
int bst_avl_insert(bst_t *T, bst_key_t key, data_t elem_ptr)
{
	// Attmempt 2 ********* FIXME FIXME 
	T->root = insert_node(T->root, key, elem_ptr, T->policy);
    return 1;
}

/* Insert data_t into the tree with the associated key.
 * 
 * This function supports the bst_insert function, adding a new node to the tree
 * when one with the desired key is not already present.
 *
 * node - the current node position in the tree, if NULL this is where the
 *	new node will be added
 * key - key to be added to the tree
 * elem_ptr - data to be stored at tree node indicated by key
 * policy - the avl policy of the tree being inserted into
 *
 * Precondition: there is not already a node in the tree with the given key
 *
 * RETURNS node, if node is NULL, then returns a pointer to a newly added node
 */
bst_node_t* insert_node(bst_node_t *node, bst_key_t key, data_t elem_ptr, int policy)
{
	// Attempt 2********************FIXME FIXME
	// If NULL construct a new node
	if (node == NULL)
	{
		bst_node_t *new_node = (bst_node_t*) malloc(sizeof(bst_node_t));
		new_node->data_ptr = elem_ptr;
		new_node->key = key;
		new_node->height = 0;
		new_node->left = NULL;
		new_node->right = NULL;
		return new_node;
	}

	// Otherwise, search down the tree
	if (key < node->key)
	{
		node->left = insert(node->left, key, elem_ptr);
	}
	else
	{
		node->right = insert(node->right, key, elem_ptr);
	}

	// Update height of current node
	int left_height, right_height;
	if (node->left = NULL)
		left_height = 0;
	else
		left_height = node->left->height;
	if (node->right == NULL)
		right_height = 0;
	else
		right_height = node->right->height;
		
	node->height = 1 + max(left_height, right_height);

	// Check AVL property if tree has AVL policy
	if (policy == AVL)
	{
		// Check for 4 rotation cases
		int balance = left_height - right_height;
		// Left-Left
		if (balance > 1 && key < node->left->key)
			return rotate_right(node);
		// Right-Right
		if (balance < -1 && key > node->right->key)
			return rotate_left(node);
		// Left-Right
		if (balance > 1 && key > node->left->key)
		{
			node->left = rotate_left(node->left);
			return rotate_right(node);
		}
		// Right-Left
		if (balance < -1 && key < node->left->key)
		{
			node->right = rotate_right(node->right);
			return rotate_left(node);
		}
	}

	// Return current node
	return node;
}

/* AVL right rotation function. Takes node, its right child, and that child's
 * right child, and rotates so that the right child is the root and node is its
 * left child.
 *
 * node - the node that violates the AVL property
 *
 * Returns: a pointer to the root node after the rotation.
 */
bst_node_t* rotate_right(bst_node_t* node)
{

}

/* AVL left rotation function. Takes node, its left child, and that child's
 * left child, and rotates so that the left child is the root and node is its
 * right child.
 *
 * node - the node that violates the AVL property
 *
 * Returns: a pointer to the root node after the rotation.
 */
bst_node_t* rotate_right(bst_node_t* node)
{

}

/* DO NOT NEED TO IMPLEMENT FOR REGULAR ASSIGNMENT. ONLY FOR EXTRA ASSIGNMENT.
 *
 * Removes the item in the tree with the matching key.
 * 
 * T - pointer to tree
 * key - search key for particular node in the tree 'T'
 *
 * RETURNS the pointer to the data memory block and free the bst_node_t memory
 * block.  If the key is not found in the tree, return NULL.  If the tree's 
 * policy is AVL, then ensure all nodes have the AVL property.
 *
 */

data_t bst_remove(bst_t *T, bst_key_t key)
{
    data_t dp = NULL;
    CompCalls = 0;
    NumRotations = 0;
    if (T->policy == AVL)
	    dp = NULL; /*TODO: AVL remove */
    else
	    dp = NULL; /*TODO: BST remove */

    /*TODO: update tree stats*/

#ifdef VALIDATE
        bst_debug_validate(T);
#endif
    return dp;
}


/* RETURNS the number of keys in the tree */
int bst_size(bst_t *T)
{
    return -1; /*TODO */
}

/* RETURNS the number of key comparisons  */
int bst_key_comps(bst_t *T)
{
    return -1; /*TODO */
}

/* RETURNS the computed internal path length of the tree T */
int bst_int_path_len(bst_t *T)
{
    return -1; /*TODO */
}

/* RETURNS the number of rotations from the last remove*/
int bst_rotations(bst_t *T)
{
    return -1; /*TODO */
}


/* prints the tree T */
void bst_debug_print_tree(bst_t *T)
{
    ugly_print(T->root, 0, T->policy);//XTRA
    printf("\n");
    if (T->size < 64)
	pretty_print(T);
}

/* basic print function for a binary tree */
void ugly_print(bst_node_t *N, int level, int policy)
{
    int i;
    if (N == NULL) return;
    ugly_print(N->right, level+1, policy);
    if (policy == AVL) {
	    for (i = 0; i<level; i++) printf("       ");
	        printf("%5d-%d\n", N->key, N->height);
    } else {
	    for (i = 0; i<level; i++) printf("     ");
	        printf("%5d\n", N->key);
    }
    ugly_print(N->left, level+1, policy);
}


/* Basic validation function for tree T */
void bst_debug_validate(bst_t *T)
{
    int size = 0;
    assert(bst_debug_validate_rec(T->root, INT_MIN, INT_MAX, &size) == TRUE);
    assert(size == T->size);
    if (T->policy == AVL)
	    rec_height(T->root);
}


/* A tree validation function
 */
int bst_debug_validate_rec(bst_node_t *N, int min, int max, int *count)
{
    if (N == NULL)
        return TRUE;
    if (N->key <= min || N->key >= max)
        return FALSE;
    assert(N->data_ptr != NULL);
    *count += 1;
    return bst_debug_validate_rec(N->left, min, N->key, count) &&
        bst_debug_validate_rec(N->right, N->key, max, count);
}

/* Verifies AVL tree properties */

int rec_height(bst_node_t *N)
{
    if (N == NULL)
	    return 0;
    int lh = rec_height(N->left);
    int rh = rec_height(N->right);
    int lean = lh - rh;
    assert(lean == 0 || lean == 1 || lean == -1);
    return 1 + MYMAX(lh, rh); 

}





/* Recursive function to count children */
int children(bst_node_t *N)
{
    if (N == NULL) return 0;
    return 1 + children(N->left) + children(N->right);
}



/* Prints the tree to the terminal in ASCII art*/
void pretty_print(bst_t *T)
{
    typedef struct queue_tag {
	    bst_node_t *N;
	    int level;
	    int list_sum;
    } queue_t;

    queue_t Q[T->size];
    int q_head = 0;
    int q_tail = 0;
    int i, j;
    int current_level = 0;
    int col_cnt = 0;
    bst_node_t *N;

    Q[q_tail].N = T->root;
    Q[q_tail].level = 0;
    Q[q_tail].list_sum = 0;
    q_tail++;
    for (i = 0; i < T->size; i++)
    {
	assert(q_head < T->size);
	N = Q[q_head].N;
	if (Q[q_head].level > current_level) {
	    printf("\n");
	    current_level++;
	    col_cnt = 0;
	}
	int left_ch = children(N->left);
	int my_pos = 1 + left_ch + Q[q_head].list_sum;
	int left_child_pos = my_pos;
	if (N->left != NULL)
	    left_child_pos = 1 + Q[q_head].list_sum + children(N->left->left);
	int right_child_pos = my_pos;
	if (N->right != NULL)
	    right_child_pos = my_pos + 1 + children(N->right->left);
	for (j = col_cnt + 1; j <= right_child_pos; j++)
	{
	    if (j == my_pos)
		if (left_child_pos < my_pos)
		    if (N->key < 10)
			printf("--%d", N->key);
		    else if (N->key < 100)
			printf("-%d", N->key);
		    else
			printf("%d", N->key);
		else
		    printf("%3d", N->key);
	    else if (j == left_child_pos)
		//printf("  |");
		printf("  /");
	    else if (j > left_child_pos && j < my_pos)
		printf("---");
	    else if (j > my_pos && j < right_child_pos)
		printf("---");
	    else if (j == right_child_pos)
		//printf("--|");
		printf("-\\ ");
	    else
		printf("   ");
	}
	col_cnt = right_child_pos;

	if (N->left != NULL) {
	    Q[q_tail].N = N->left;
	    Q[q_tail].level = Q[q_head].level + 1;
	    Q[q_tail].list_sum = Q[q_head].list_sum;
	    q_tail++;
	}
	if (N->right != NULL) {
	    Q[q_tail].N = N->right;
	    Q[q_tail].level = Q[q_head].level + 1;
	    Q[q_tail].list_sum = Q[q_head].list_sum + left_ch + 1;
	    q_tail++;
	}
	q_head++;
    }
    printf("\n");
}

/* vi:set ts=8 sts=4 sw=4 et: */
