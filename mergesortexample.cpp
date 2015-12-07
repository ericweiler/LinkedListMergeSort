#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <time.h>
using std::cin;
using std::cout;
using std::ofstream;
using std::string;
struct node{
	int data;
	node* next;
};

node* generate(int size){				//creates linked list filled with random integers
	srand(time(NULL));
	node* head = NULL;
	for (int i = 0; i < size; i++){
		node* temp = new node;
		if (size < RAND_MAX)
			temp->data = rand() % size;
		else
			temp->data = rand();
		temp->next = head;
		head = temp;
	}
	return head;
}

void printToFile(ofstream& out, node* head){	//prints list to output file
	int newLine = 1;
	for (node* temp = head; temp != NULL; temp = temp->next, newLine++){
		out << temp->data << "\t";
		if (newLine % 15 == 0) 
			out << "\n";
	}
}

node* getMiddle(node* head){		//gets the middle of a linked list, returns pointer to the middle
	if (head == NULL) return head;	//if the linked list is empty return the head pointer
	node* slow = head;				//two pointers store the beginning of the linked list, one will traverse twice as fast as the other, when the faster one reaches the end, the slower one will be at the middle
	node* fast = head;
	while (fast->next != NULL && fast->next->next != NULL) {		//traverse the linked list
		slow = slow->next; fast = fast->next->next;					//traverse using the two pointers at different speeds
	}
	return slow;													//return the middle of the list
}

node * merge(node * lower, node * upper){							//merges the lists taking the head pointer for each list
	node* head = new node;											//create a new head to store the sorted list
	node* current;													//create a current pointer for traversal
	current = head;													//set the current to the head
	while (lower != NULL && upper != NULL){							//while both lists have not reached the end, continue traversing both and searching for the smallest item
		if (lower->data > upper->data){								//if the first list's next item is greater than the second's
			current->next = upper;									//add the second's next item to the new list
			upper = upper->next;									//move the first link on the second list to the next link, thereby reducing the size of the second list because the old first item has been taken
		}
		else{														//same logic, opposite conditions
			current->next = lower;
			lower = lower->next;
		}
		current = current->next;									//move to the next item on the new list
	}
	if (lower == NULL)												//when one list runs out, place the remaining nodes from the other list onto the end of the new list while preserving order
	for (node* temp = upper; temp != NULL; temp = temp->next){
		current->next = temp;
		current = current->next;
	}
	else
	for (node* temp = lower; temp != NULL; temp = temp->next){
		current->next = temp;
		current = current->next;
	}
	return head->next;
}

node * sort(node * head){											//main mergesort function
	if (head == NULL || head->next == NULL) return head;			//if the list is empty or the list only contains one element the linked list is already sorted, return the head
	node* middle = getMiddle(head);									//calls get middle function to get the middle of the list
	node* half = middle->next;										//set the middle's next pointer to null, thus breaking the link between the first half and the second half, divides the list into two
	middle->next = NULL;
	return merge(sort(head), sort(half));							//recursively break the linked list down until they are individual elements and then merge them together in sorted order
}

int main(){
		int size;
		printf("Enter the desired size of the list:\n");
		cin >> size;
		ofstream unsorted("unsorted.txt");
		ofstream sorted("sorted.txt");
		printf("\nGenerating List...\n");
		node* head = generate(size);
		printf("Saving List...\n");
		printToFile(unsorted, head);
		printf("Sorting List...\n");
		head = sort(head);
		printf("Saving List...\n");
		printToFile(sorted, head);
}