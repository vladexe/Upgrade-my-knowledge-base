#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/list.h>

#define MAX_SIZE 10

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vladyslav Andrishko");
MODULE_DESCRIPTION("Linked List Example using list_head and container_of");

static int amount = 0;
static int numbers[MAX_SIZE];

module_param_array(numbers, int, &amount, 0644);
MODULE_PARM_DESC(numbers, "Array of numbers");

// Define our structure that includes list_head
struct my_node {
    int data;
    struct list_head list;  // Linked list pointer
};

// Initialize head of the linked list
static LIST_HEAD(my_list);

// Function to add an element to the linked list
static void add_node(int value) {
    struct my_node *new_node;

    // Allocate memory for the new node
    new_node = kmalloc(sizeof(struct my_node), GFP_KERNEL);
    if (!new_node) {
        pr_err("Memory allocation failed!\n");
	return ;
    }

    // Set data and add to the list
    new_node->data = value;
    list_add_tail(&new_node->list, &my_list);
    pr_info("Added node with value: %d\n", value);
}

static void remove_node(int value){
    struct my_node *node, *temp;
    int count = 0;

    list_for_each_entry_safe(node, temp, &my_list, list) {
        if (node->data == value){
            pr_info("Node %d will be deleted\n", node->data);
	    list_del(&node->list);
	    kfree(node);
	    count++;
         }
    }
    if (count == 0)
        pr_info("There is no %d value node in the list\n", value);
}

// Function to iterate and print the linked list
// if reversed is 0 normal printing if non-0 value
// reversed option is enabled
static void print_list(int reversed) {
    struct my_node *entry;
    int counter = 0;

    pr_info("Linked List Contents:\n");

    if (reversed == 0){
        list_for_each_entry(entry, &my_list, list) {
            pr_info("Node data: %d\n", entry->data);
	    counter++;
        }
    } else {
        list_for_each_entry_reverse(entry, &my_list, list){
            pr_info("Reversed List node: [%d]\n", entry->data);
	    counter++;
        }
    }
    pr_info("Current node amount is %d\n", counter);
}

// Function to remove all nodes from the list
static void cleanup_list(void) {
    struct my_node *entry, *temp;

    list_for_each_entry_safe(entry, temp, &my_list, list) {
        pr_info("Removing node with value: %d\n", entry->data);
        list_del(&entry->list); // Remove node from list
        kfree(entry); // Free memory
    }
}

// Module initialization function
static int __init my_module_init(void) {
    pr_info("Loading Linked List Module...\n");

    add_node(10);
    add_node(20);
    add_node(30);
    add_node(3);
    add_node(1495);
    
    print_list(0);

    remove_node(20);

    print_list(1);
		

    for(int i = 0; i < amount; i++){
    	add_node(numbers[i]);
    }
    print_list(0);
    return 0;
}

// Module exit function
static void __exit my_module_exit(void) {
    pr_info("Unloading Linked List Module...\n");
    cleanup_list();
}

module_init(my_module_init);
module_exit(my_module_exit);
