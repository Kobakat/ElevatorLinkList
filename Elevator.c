#include <stdio.h>
#include <stdlib.h>

struct Node 
{
	int data;
	struct Node* next;
	struct Node* previous;
};

void append(struct Node** head, int new_data)
{
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

	struct Node* last = *head;

	//the arrow here is dereferencing AND setting equal to *(new_node).data = new_data;
	new_node->data = new_data;
	new_node->next = NULL;

	//If the LL is empty, the first item added becomes the head
	if (*head == NULL)
	{
		*head = new_node;
		return;
	}

	//Traverse the list until the end
	while (last->next != NULL)
	{
		last = last->next;
	}

	//Once at the end of the LL, add the new node
	last->next = new_node;
	
	//New node's previous pointer points to the now second to last node.
	new_node->previous = last;
}

void print_list(struct Node* n)
{
	while (n != NULL) {
		printf("%d\n", n->data);
		n = n->next;
	}
}

/*void ChangeFloor(int start, int size, struct Node* head, int * list)
{
	for(int i = 0; i < size; i++)
	{
		int difference = *(list + i) - start;
		
		//decrease if change in floors is negative
		if (difference < 0) 
		{
			for(int k = start; k > *(list + i); k--) 
			{
				printf("%d, ", floors[k-2]);
			}
			printf("Ding!\n");
		}	
	
		//increase if change in floors is positive
		else if (difference > 0)
		{
			for(int k = start; k < *(list + i); k++)
			{
				printf("%d, ", floors[k]);
			}
			printf("Ding!\n");
		}

		//If no net floor change occurs
		else
		{
			printf("Oops! You're already on that floor!\n");
		}
		
		start = *(list + i);
	}	
}*/


//Places the desired floors into a link list
struct Node * AssignFloors(struct Node* head, int numOfFloors) 
{
	struct Node* userList = NULL;
	
	for(int j = 0; j < numOfFloors; j++) 
	{
		int chosenFloor = 0;
		
		printf("Enter floor number #%d\n", j+1);
		scanf("%d", &chosenFloor);

		//incorrect floor chosen
		if(chosenFloor > 15 || chosenFloor < 1) 
		{
			printf("That is not a valid floor! Choose between 1-15.\n");
			j--;
		}
		
		//proper floor chosen
		else
		{	
			struct Node* headref = head;
			while (head->data != chosenFloor) 
			{
				head = head->next;
			}
			append(&userList, chosenFloor);
			head = headref;
		}
	}

	return userList;
}

struct Node* OrganizeFloors(struct Node* userList) 
{
	struct Node* headref = userList;
	while (userList->next != NULL) 
	{
		if (userList->data > userList->next->data) 
		{
			int temp = userList->data;
			userList->data = userList->next->data;
			userList->next->data = temp;

			userList = userList->next;
		}
	}
	userList = headref;

	return userList;
}

int main() 
{
	//Create empty doubly linked list
	struct Node* floors = NULL;

	//Add 15 nodes each with a floor to the list
	for(int q = 1; q < 16; q++) 
	{
		append(&floors, q);
	}

	
	char again = 'y';
	int currentFloor = floors->data;
	
	do
	{
		int numOfFloors = 0;

		printf("You are currently on floor %d. The top floor is 15.\n", currentFloor);
		printf("How many floors would you like to move between? ");

		//Used to determine the size of the array
		scanf("%d", &numOfFloors);

		//floorList points to an array of size numOfFloors
		struct Node* rawUser = AssignFloors(floors, numOfFloors);
		printf("\nRaw: ");
		print_list(rawUser);
		struct Node* refinedUser = OrganizeFloors(rawUser);
		printf("\nRefined: ");
		print_list(refinedUser);
		printf("\nHere we go!\n\n");

		//Text showing the changing of floors

		/*ChangeFloor(currentFloor, numOfFloors, floors, floorList);

		currentFloor = *(floorList + numOfFloors - 1);

		free(floorList);
		floorList = NULL;

		//ride again if input is 'y'
		printf("Would you like to change floors? Enter y if yes or any other key if not.\n");


		scanf("%s", &again);


		printf("\n");*/

	} while(again == 'y'); 
	
	return 0;
}
