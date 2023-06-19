#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

void initList(List *list) {
	*list = NULL;
}

List newList() {
	List list = NULL;
    return list;
}

NodeType createNode(DATA data) {
	NodeType *newNode = (NodeType *)malloc(sizeof(NodeType));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return *newNode;
}

void displayList(List list) {
	printf("List: ");
    while (list != NULL) {
        printf("%d ", list->data);
        list = list->next;
    }
    printf("\n");
}

bool insertFront(List *list, DATA item) {
	NodePtr newNode = (NodePtr)malloc(sizeof(NodeType));
    if (newNode == NULL) {
        return false;  // Failed to allocate memory for the new node
    }

    newNode->data = item;
    newNode->next = *list;
    *list = newNode;

    return true;
}

bool insertRear(List *list, DATA item) {
	NodePtr newNode = (NodePtr)malloc(sizeof(NodeType));
    if (newNode == NULL) {
        return false;  // Failed to allocate memory for the new node
    }

    newNode->data = item;
    newNode->next = NULL;

    if (*list == NULL) {
        // The list is empty, make the new node the head of the list
        *list = newNode;
    } else {
        // Traverse to the last node and append the new node
        NodePtr currentNode = *list;
        while (currentNode->next != NULL) {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
    }

    return true;
}

bool insertAt(List *list, DATA item, int loc) {
	NodePtr newNode = (NodePtr)malloc(sizeof(NodeType));
    if (newNode == NULL) {
        return false;  // Failed to allocate memory for the new node
    }

    newNode->data = item;

    if (loc == 1 || *list == NULL) {
        // Insert at the front of the list or the list is empty
        newNode->next = *list;
        *list = newNode;
    } else {
        NodePtr currentNode = *list;
        int currentPosition = 1;

        while (currentNode != NULL && currentPosition < loc - 1) {
            currentNode = currentNode->next;
            currentPosition++;
        }

        if (currentNode == NULL) {
            // Invalid location, cannot insert
            free(newNode);
            return false;
        }

        newNode->next = currentNode->next;
        currentNode->next = newNode;
    }

    return true;
}

bool insertSorted(List *list, DATA data){
	NodePtr newNode = (NodePtr)malloc(sizeof(NodeType));
    if (newNode == NULL) {
        return false;  // Failed to allocate memory for the new node
    }

    newNode->data = data;

    if (*list == NULL || data < (*list)->data) {
        // Insert at the front of the list or the list is empty
        newNode->next = *list;
        *list = newNode;
    } else {
        NodePtr currentNode = *list;

        while (currentNode->next != NULL && data > currentNode->next->data) {
            currentNode = currentNode->next;
        }

        newNode->next = currentNode->next;
        currentNode->next = newNode;
    }

    return true;
}

bool searchItem(List list, DATA key) {
	NodePtr currentNode = list;

    while (currentNode != NULL) {
        if (currentNode->data == key) {
            return true;  // Item found
        }

        currentNode = currentNode->next;
    }

    return false;  // Item not found
}

int getItem(List list, DATA key) {
	NodePtr currentNode = list;
    int index = 0;

    while (currentNode != NULL) {
        if (currentNode->data == key) {
            return index;  // Item found, return the index
        }

        currentNode = currentNode->next;
        index++;
    }

    return -1;  // Item not found, return -1
}

bool deleteFront(List *list) {
	if (*list == NULL) {
        return false;  // List is empty, cannot delete front item
    }

    NodePtr frontNode = *list;
    *list = frontNode->next;  // Update the list head to the next node
    free(frontNode);  // Free the memory of the front node

    return true;  // Front item deleted successfully
}

bool deleteRear(List *list) {
	if (*list == NULL) {
        return false;  // List is empty, cannot delete rear item
    }

    if ((*list)->next == NULL) {
        // Only one node in the list, delete it
        free(*list);
        *list = NULL;
        return true;
    }

    NodePtr current = *list;
    NodePtr previous = NULL;

    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }

    // Now current points to the last node
    previous->next = NULL;
    free(current);

    return true;  // Rear item deleted successfully
}

int deleteAt(List *list, int loc) {
	if (*list == NULL || loc < 0) {
        return -1;  // List is empty or invalid location
    }

    NodePtr current = *list;
    NodePtr previous = NULL;

    int count = 0;

    while (current != NULL && count < loc) {
        previous = current;
        current = current->next;
        count++;
    }

    if (current == NULL) {
        return -1;  // Location exceeds the list size
    }

    if (previous == NULL) {
        // Deleting the first node
        *list = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);

    return loc;  // Return the position of the deleted item
}

bool deleteItem(List *list, DATA key) {
	if (*list == NULL) {
        return false;  // List is empty
    }

    NodePtr current = *list;
    NodePtr previous = NULL;

    while (current != NULL) {
        if (current->data == key) {
            if (previous == NULL) {
                // Deleting the first node
                *list = current->next;
            } else {
                previous->next = current->next;
            }

            free(current);
            return true;  // Item deleted successfully
        }

        previous = current;
        current = current->next;
    }

    return false;  // Item not found in the list
}

int deleteAllItem(List *list, DATA key) {
	if (*list == NULL) {
        return 0;  // List is empty
    }

    int count = 0;
    NodePtr current = *list;
    NodePtr previous = NULL;

    while (current != NULL) {
        if (current->data == key) {
            if (previous == NULL) {
                // Deleting the first node
                *list = current->next;
            } else {
                previous->next = current->next;
            }

            NodePtr temp = current;
            current = current->next;
            free(temp);
            count++;  // Increment the count of deleted items
        } else {
            previous = current;
            current = current->next;
        }
    }

    return count;
}
