#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 

#define SUCCESS             1 
#define TRUE                1 
#define FALSE               0 
#define LIST_INVALID_DATA   2 
#define LIST_EMPTY          3 

struct node
{
    int data; 
    struct node* prev;
    struct node* next; 
}; 

/* Interface functions */
struct node* create_list(void); 

int insert_start(struct node* p_head_node, int new_data); 
int insert_end(struct node* p_head_node, int new_data); 
int insert_after(struct node* p_head_node, int e_data, int new_data); 
int insert_before(struct node* p_head_node, int e_data, int new_data); 

int get_start(struct node* p_head_node, int* p_start_data); 
int get_end(struct node* p_head_node, int* p_end_data); 
int pop_start(struct node* p_head_node, int* p_start_data); 
int pop_end(struct node* p_head_node, int* p_end_data); 

int remove_start(struct node* p_head_node); 
int remove_end(struct node* p_head_node); 
int remove_data(struct node* p_head_node, int r_data); 

int find(struct node* p_head_node, int search_data); 
int is_list_empty(struct node* p_head_node); 
int get_length(struct node* p_head_node); 
void show_list(struct node* p_head_node, char* msg); 

int destroy_list(struct node** pp_head_node); 

struct node* concat_lists(struct node* p_head_node_1, struct node* p_head_node_2); 
void append(struct node* p_head_node_1, struct node** pp_head_node_2); 
struct node* get_reversed_list(struct node* p_list);
struct node* merge_lists(struct node* p_head_1, struct node* p_head_2); 

/* Helper functions */
void generic_insert(struct node* p_start, struct node* p_mid, struct node* p_end); 
void generic_delete(struct node* p_delete_node); 
struct node* search_node(struct node* p_head_node, int search_data); 
struct node* get_node(int new_data); 
void* xmalloc(size_t size_in_bytes); 

int main(void){
    struct node* p_list = NULL; 
    int data; 
    int status; 
    int length; 

    puts("DOUBLE CIRCULAR LINKED LIST:"); 

    p_list = create_list(); 
    assert(p_list != NULL); 

    assert(get_start(p_list, &data) == LIST_EMPTY); 
    assert(pop_start(p_list, &data) == LIST_EMPTY); 
    assert(get_end(p_list, &data) == LIST_EMPTY); 
    assert(pop_end(p_list, &data) == LIST_EMPTY); 
    assert(remove_start(p_list) == LIST_EMPTY); 
    assert(remove_end(p_list) == LIST_EMPTY); 
    assert(get_length(p_list) == 0); 
    assert(is_list_empty(p_list) == TRUE); 
    puts("testing, get_start(), pop_start(), get_end(), pop_end(), remove_start(), remove_end() on empty list...OK"); 
    puts("testing, get_length() on empty list ... ok ");
    puts("testing, is_list_empty() on empty list ... ok"); 
    show_list(p_list, "testing, empty list"); 

    for(data = 0; data <= 40; data = data + 10)
        insert_start(p_list, data); 

    show_list(p_list, "testing, insert_start()"); 

    for(data = 50; data <= 100; data = data + 10)
        insert_end(p_list, data); 

    show_list(p_list, "testing, insert_end()"); 

    puts("testing, insert_after() for false case"); 
    status = insert_after(p_list, -300, 500); 
    assert(status == LIST_INVALID_DATA); 
    puts("testing, insert_after() false case... ok"); 

    puts("testing insert_before() for false case"); 
    status = insert_before(p_list, 8976, 500); 
    assert(status == LIST_INVALID_DATA); 
    puts("testing, insert_before() false case ... ok"); 

    puts("testing insert_after() and insert_before() for valid data"); 
    status = insert_after(p_list, 0, 1000); 
    assert(status == SUCCESS); 
    status = insert_before(p_list, 0, 2000); 
    assert(status == SUCCESS); 

    show_list(p_list, "test, insert_after(), insert_before()... ok"); 

    status = get_start(p_list, &data); 
    assert(status == SUCCESS); 
    printf("START OF LIST = %d\n", data); 
    show_list(p_list, "showing list after get_start()"); 

    status = get_end(p_list, &data); 
    assert(status == SUCCESS); 
    printf("END OF LIST = %d\n", data); 
    show_list(p_list, "showing list after get_end()"); 

    status = pop_start(p_list, &data); 
    assert(status == SUCCESS); 
    printf("START OF LIST = %d\n", data); 
    show_list(p_list, "showing list after pop_start()"); 

    status = pop_end(p_list, &data); 
    assert(status == SUCCESS); 
    printf("END OF LIST = %d\n", data); 
    show_list(p_list, "showing list after pop_end()"); 

    status = remove_start(p_list); 
    assert(status == SUCCESS); 
    show_list(p_list, "showing list after remove_start()"); 

    status = remove_end(p_list); 
    assert(status == SUCCESS); 
    show_list(p_list, "showing list after remove_end()"); 

    puts("testing, get_start(), pop_start(), get_end(), pop_end(), remove_start(), remove_end() on non-empty list...OK"); 

    length = get_length(p_list); 
    printf("length = %d\n", length); 

    puts("testing remove_data() for false case"); 
    status = remove_data(p_list, 1234); 
    assert(status == LIST_INVALID_DATA); 
    puts("testing remove data for false case ... ok"); 

    puts("testing remove_data() for success case"); 
    status = remove_data(p_list, 0); 
    assert(status == SUCCESS); 
    puts("testing remove data for success case ... ok"); 
    show_list(p_list, "showing list after removing 0"); 

    assert(is_list_empty(p_list) == FALSE); 
    puts("testing, is_list_empty() for non-empty list...ok"); 

    status = destroy_list(&p_list); 
    assert(status == SUCCESS && p_list == NULL); 

    struct node* p_list_1 = create_list(); 
    struct node* p_list_2 = create_list(); 

    for(data = 10; data <= 50; data += 10)  
        insert_end(p_list_1, data); 

    for(data = 15; data <= 85; data += 10)
        insert_end(p_list_2, data); 

    struct node* p_concat_list = concat_lists(p_list_1, p_list_2); 

    show_list(p_list_1, "List 1:"); 
    show_list(p_list_2, "List 2:"); 
    show_list(p_concat_list, "Concatenated list"); 

    struct node* p_reversed_list = get_reversed_list(p_list_2); 
    show_list(p_reversed_list, "Reversed version of list 2"); 

    append(p_list_1, &p_list_2); 
    assert(p_list_2 == NULL); 
    show_list(p_list_1, "After appending list 2 to list 1"); 

    assert(destroy_list(&p_list_1) == SUCCESS && p_list_1 == NULL); 
    assert(destroy_list(&p_concat_list) == SUCCESS && p_concat_list == NULL); 
    assert(destroy_list(&p_reversed_list) == SUCCESS && p_concat_list == NULL); 


    puts("exiting from application:SUCCESS"); 
    return (EXIT_SUCCESS); 
}

struct node* create_list(void)
{
    struct node* p_head_node = NULL; 

    p_head_node = get_node(0); 
    p_head_node->prev = p_head_node; 
    p_head_node->next = p_head_node; 

    return (p_head_node); 
}

int insert_start(struct node* p_head_node, int new_data)
{
    generic_insert(p_head_node, get_node(new_data), p_head_node->next); 
    return (SUCCESS); 
}

int insert_end(struct node* p_head_node, int new_data)
{
    generic_insert(p_head_node->prev, get_node(new_data), p_head_node); 
    return (SUCCESS); 
}

int insert_after(struct node* p_head_node, int e_data, int new_data)
{
    struct node* e_node = NULL; 

    e_node = search_node(p_head_node, e_data); 
    if(e_node == NULL)
        return (LIST_INVALID_DATA); 

    generic_insert(e_node, get_node(new_data), e_node->next); 
    return (SUCCESS); 
}

int insert_before(struct node* p_head_node, int e_data, int new_data)
{
    struct node* e_node = NULL; 

    e_node = search_node(p_head_node, e_data); 
    if(e_node == NULL)
        return (LIST_INVALID_DATA); 

    generic_insert(e_node->prev, get_node(new_data), e_node); 
    return (SUCCESS); 
}

int get_start(struct node* p_head_node, int* p_start_data)
{
    if(p_head_node->prev == p_head_node && p_head_node->next == p_head_node)
        return (LIST_EMPTY); 

    *p_start_data = p_head_node->next->data; 
    return (SUCCESS); 
}

int get_end(struct node* p_head_node, int* p_end_data)
{
    if(p_head_node->prev == p_head_node && p_head_node->next == p_head_node)
        return (LIST_EMPTY); 

    *p_end_data = p_head_node->prev->data; 
    return (SUCCESS);
}

int pop_start(struct node* p_head_node, int* p_start_data)
{
    if(p_head_node->prev == p_head_node && p_head_node->next == p_head_node)
        return (LIST_EMPTY); 

    *p_start_data = p_head_node->next->data; 
    generic_delete(p_head_node->next); 

    return (SUCCESS); 
}

int pop_end(struct node* p_head_node, int* p_end_data)
{
    if(p_head_node->prev == p_head_node && p_head_node->next == p_head_node)
        return (LIST_EMPTY); 

    *p_end_data = p_head_node->prev->data; 
    generic_delete(p_head_node->prev); 
    return (SUCCESS);
}

int remove_start(struct node* p_head_node)
{
    if(p_head_node->prev == p_head_node && p_head_node->next == p_head_node)
        return (LIST_EMPTY); 

    generic_delete(p_head_node->next); 

    return (SUCCESS); 
}

int remove_end(struct node* p_head_node)
{
    if(p_head_node->prev == p_head_node && p_head_node->next == p_head_node)
        return (LIST_EMPTY); 

    generic_delete(p_head_node->prev); 
    
    return (SUCCESS);
}

int remove_data(struct node* p_head_node, int r_data)
{
    struct node* r_node = NULL; 

    r_node = search_node(p_head_node, r_data);
    if(r_node == NULL)
        return (LIST_INVALID_DATA); 
    
    generic_delete(r_node); 

    return (SUCCESS); 
}

int find(struct node* p_head_node, int search_data)
{
    struct node* f_node = NULL; 

    f_node = search_node(p_head_node, search_data); 

    return (f_node != NULL); 
}

int is_list_empty(struct node* p_head_node)
{
    return (p_head_node->next == p_head_node && p_head_node->prev == p_head_node); 
}

int get_length(struct node* p_head_node)
{
    struct node* run = NULL; 
    int n; 

    n = 0; 
    run = p_head_node->next; 
    while(run != p_head_node)
    {
        n += 1; 
        run = run->next; 
    }

    return (n); 
}

void show_list(struct node* p_head_node, char* msg)
{
    struct node* run = NULL; 

    if(msg)
        puts(msg); 

    printf("[START]<->"); 
    run = p_head_node->next; 
    while(run != p_head_node)
    {
        printf("[%d]<->", run->data); 
        run = run->next; 
    }
    puts("[END]"); 
}

int destroy_list(struct node** pp_head_node)
{
    struct node* p_head_node = *pp_head_node; 
    struct node* run = NULL; 
    struct node* run_next = NULL; 

    run = p_head_node->next; 
    while(run != p_head_node)
    {
        run_next = run->next; 
        free(run); 
        run = run_next; 
    }

    free(p_head_node); 
    p_head_node = NULL; 

    *pp_head_node = NULL; 
    return (SUCCESS); 
}


struct node* concat_lists(struct node* p_head_node_1, struct node* p_head_node_2)
{
    struct node* p_concat_head_node = NULL; 
    struct node* run = NULL; 

    p_concat_head_node = create_list(); 
    for(run = p_head_node_1->next; run != p_head_node_1; run = run->next)
        insert_end(p_concat_head_node, run->data);  

    for(run = p_head_node_2->next; run != p_head_node_2; run = run->next)
        insert_end(p_concat_head_node, run->data); 

    return (p_concat_head_node); 
}

void append(struct node* p_head_node_1, struct node** pp_head_node_2)
{
    struct node* p_head_node_2 = *pp_head_node_2; 

    if(p_head_node_2->next != p_head_node_2)
    {
        p_head_node_1->prev->next = p_head_node_2->next; 
        p_head_node_2->next->prev = p_head_node_1->prev; 
        p_head_node_2->prev->next = p_head_node_1; 
        p_head_node_1->prev = p_head_node_2->prev; 
    }

    free(p_head_node_2); 
    p_head_node_2 = NULL; 

    *pp_head_node_2 = NULL; 
}

struct node* get_reversed_list(struct node* p_head_node)
{
    struct node* p_reversed_list = NULL; 
    struct node* run = NULL; 

    p_reversed_list = create_list(); 

    for(run = p_head_node->next; run != p_head_node; run = run->next)
        insert_start(p_reversed_list, run->data); 

    return (p_reversed_list); 
}

struct node* merge_lists(struct node* p_head_1, struct node* p_head_2)
{
    struct node* p_merged_list = NULL; 
    struct node* run1 = NULL; 
    struct node* run2 = NULL; 

    p_merged_list = create_list(); 
    run1 = p_head_1->next; 
    run2 = p_head_2->next; 

    while(TRUE)
    {
        if(run1 == p_head_1)
        {
            while(run2 != p_head_2)
            {
                insert_end(p_merged_list, run2->data); 
                run2 = run2->next; 
            }

            break; 
        }

        if(run2 == p_head_2)
        {
            while(run1 != p_head_1)
            {
                insert_end(p_merged_list, run1->data); 
                run1 = run1->next; 
            }

            break; 
        }

        if(run1->data <= run2->data)
        {
            insert_end(p_merged_list, run1->data); 
            run1 = run1->next; 
        }
        else
        {
            insert_end(p_merged_list, run2->data); 
            run2 = run2->next; 
        }
    }

    return (p_merged_list); 
}

void reverse_list(struct node* p_list)
{
    struct node* original_first_node = NULL; 
    struct node* run = NULL; 
    struct node* run_next = NULL; 

    if(p_list->next == p_list || p_list->next->next == p_list)
        return; 

    original_first_node = p_list->next; 

    run = p_list->next->next; 
    while(run != p_list)
    {
        run_next = run->next;

        run->next = p_list->next; 
        run->prev = p_list; 
        p_list->next->prev = run; 
        p_list->next = run; 

        run = run_next; 
    }

    original_first_node->next = p_list; 
    p_list->prev = original_first_node; 
}


/* Helper functions */

/* 
generic_insert() -> PRECONDITION: 
(condition(s) which input arguments must satisfy at the time of the call)

C1 : p_start and p_end must be the adjecent nodes in some linked list. 
p_start, p_end or both p_start & p_end can be p_head_node. 

C2: p_mid must be a newly allocated node with data member filled by value 
    and its prev and next are NULL. 

Programmatically speaking: 
    p_start->next == p_end 
    p_end->prev == p_start 

    p_mid->next == p_mid->prev == NULL 

*/
void generic_insert(struct node* p_start, struct node* p_mid, struct node* p_end)
{
    p_mid->next = p_end; 
    p_mid->prev = p_start; 
    p_start->next = p_mid; 
    p_end->prev = p_mid; 
}

/* 
PRECONDITION: 
@p_delete_node: is any node with data in any linked list 
*/
void generic_delete(struct node* p_delete_node)
{
    p_delete_node->prev->next = p_delete_node->next; 
    p_delete_node->next->prev = p_delete_node->prev; 
    free(p_delete_node); 
    p_delete_node = NULL;
}

struct node* search_node(struct node* p_head_node, int search_data)
{
    struct node* run = NULL; 

    run = p_head_node->next; 
    while(run != p_head_node)
    {
        if(run->data == search_data)
            return (run); 
        run = run->next; 
    }

    return (NULL); 
}

struct node* get_node(int new_data)
{
    struct node* p_node = NULL; 

    p_node = (struct node*)xmalloc(sizeof(struct node)); 
    p_node->data = new_data; 
    p_node->prev = NULL; 
    p_node->next = NULL; 

    return (p_node); 
}

void* xmalloc(size_t size_in_bytes)
{
    void* ptr = NULL; 

    ptr = malloc(size_in_bytes); 
    if(ptr == NULL)
    {
        puts("AllocationError:malloc() failed"); 
        exit(EXIT_FAILURE); 
    }

    return (ptr); 
}