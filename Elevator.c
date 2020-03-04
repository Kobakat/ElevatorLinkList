#include <stdio.h>
#include <stdlib.h>

//Linked List

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

void DeleteList(struct Node** head_ref)
{
	struct Node* current = *head_ref;
	struct Node* next;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}

	*head_ref = NULL;
}

void print_list(struct Node* n)
{
	while (n != NULL) {
		printf("%d\n", n->data);
		n = n->next;
	}
}







//Project methods

//Places the desired floors into a link list
struct Node* AssignFloors(struct Node* head, int numOfFloors)
{
	struct Node* userList = NULL;

	for (int j = 0; j < numOfFloors; j++)
	{
		int chosenFloor = 0;

		printf("Enter floor number #%d\n", j + 1);
		scanf("%d", &chosenFloor);

		//bad input
		if (chosenFloor > 15 || chosenFloor < 1)
		{
			printf("That is not a valid floor! Choose between 1-15.\n");
			j--;
		}

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

//Arranges the data contained by smallest to biggest
struct Node* OrganizeFloors(struct Node* userList)
{
	//holds a reference to the original list
	struct Node* headref = userList;

	while (userList->next != NULL)
	{
		//holds a temporary reference of a temporary list..
		struct Node* temp = userList;
		while (userList->next != NULL)
		{
			//Swaps elements
			if (userList->data > userList->next->data)
			{
				int temp = userList->data;
				userList->data = userList->next->data;
				userList->next->data = temp;
			}
			userList = userList->next;
		}
		//Restore semi-temporary list
		userList = temp;
		userList = userList->next;
	}

	//Restore the original list with updated data
	userList = headref;

	DeleteList(&headref);

	return userList;
}

//Returns the last data value from the refinedUser link list
int ChangeFloor(struct Node* refinedUser)
{
	struct Node* headref = refinedUser;
	while (refinedUser->next != NULL)
	{
		refinedUser = refinedUser->next;
	}

	int newFloor = refinedUser->data;
	refinedUser = headref;

	return newFloor;
}







int main()
{
	//Create empty doubly linked list
	struct Node* floors = NULL;

	//Add 15 nodes each with a floor to the list
	for (int q = 1; q < 16; q++)
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
		scanf("%d", &numOfFloors);

		//Places desired floors into a list, then sorts them by size
		struct Node* rawUser = AssignFloors(floors, numOfFloors);
		struct Node* refinedUser = OrganizeFloors(rawUser);

		printf("\nHere we go!\n");
		print_list(refinedUser);
		printf("Ding!\n\n");

		currentFloor = ChangeFloor(refinedUser);



		//ride again if input is 'y'
		printf("Would you like to change floors? Enter y if yes or any other key if not.\n");

		scanf("%s", &again);

		printf("\n");

	} while (again == 'y');

	return 0;
}
