/********************************************************************************
HashData class for a linked list of ticket objects; used to form hash table mapping
lottery numbers to past tickets with those winning numbers
*********************************************************************************/

// implementation for HashData class, a linked list class to form hashtables in main
#include "HashData.h"

// constructor
HashData::HashData()
{
	head = NULL;
	ballNum = frequency = 0;
	isRegNum = true;
}

// constructs a new ticket and places it at the front of the list
void HashData::prepend(int num[], int numSize, string dates[], int datesSize, int mega, int draw) {
	Ticket *ticket = new Ticket(num, numSize, dates, datesSize, mega, draw, NULL);
	ticket->setNextTicket(head);
	head = ticket;
	frequency++;
}

// constructs a new ticket and places it at the front of the list
void HashData::insert(int num[], int numSize, string dates[], int datesSize, int mega, int draw) {
	if (head == NULL)
		prepend(num, numSize, dates, datesSize, mega, draw);
	else if(head->getDrawNum() < draw)
		prepend(num, numSize, dates, datesSize, mega, draw);
	else {
		Ticket *ticket = head;
		while (ticket->getNextTicket() != NULL && ticket->getNextTicket()->getDrawNum() > draw) {
			ticket = ticket->getNextTicket();
		}
		Ticket * temp = new Ticket(num, numSize, dates, datesSize, mega, draw, NULL);
		temp->setNextTicket(ticket->getNextTicket());
		ticket->setNextTicket(temp);
		frequency++;
	}	
}

// accessor
int HashData::getFrequency() {
	return frequency;
}

// mutators
void HashData::setBallNum(int b) {
	ballNum = b;
}

void HashData::setFrequency(int f) {
	frequency = f;
}

void HashData::setRegNum(bool r) {
	isRegNum = r;
}

// construcs a new ticket and places it in the list in such a position that tickets
// will be listed by order of descending draw number
void HashData::display()
{
	Ticket *ptr = head;
	int ticketCount = 0;

	//print in pink for regular numbers or in green for mega numbers
	if(isRegNum == true)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << "BALL NUMBER: " << ballNum << "     FREQUENCY: " << frequency << endl;

	//ticket data heading
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "Draw" << "          Date          ";
	if(isRegNum == true)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	cout << " Lucky Numbers";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	if(isRegNum == false)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << "     Mega" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "_____________________________________________________" << endl << endl;

	// print first 10 tickets
	while (ptr != NULL && ticketCount < 10) 
	{
		// reconstruct arrays from Ticket class
		int nums[5] = { ptr->getN1(), ptr->getN2(), ptr->getN3(), ptr->getN4(), ptr->getN5() };
		string date[4] = { ptr->getDayOfWeek(), ptr->getMonth(), ptr->getDayOfMonth(), ptr->getYear() };


		cout << ptr->getDrawNum() << "    ";
		
		for (int i = 0; i < 4; i++)
			cout << date[i] << " ";
		
		cout << "    ";

		// print regular numbers
		// If this HashData represents a regular number, that number will be printed in pink.
		for (int i = 0; i < 5; i++)
		{
			if (nums[i] == ballNum && (isRegNum == true))
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
			cout << nums[i] << " ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
	
		// print mega number
		// If this HashData object is a mega number, the mega number will be printed in green.
		if(isRegNum == false)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout << "       " << ptr->getMegaNum() << endl;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		ptr = ptr->getNextTicket();
		ticketCount++;
	}
}

// two HashData objects are not equal if they don't share the same frequency
bool operator!=(HashData & h1, HashData & h2) {
	if (h1.getFrequency() != h2.getFrequency())
		return true;
	else
		return false;
}

// searches a HashData object for a ticket containing a given draw number
Ticket * HashData::search(int drawNumber)
{
	Ticket *ptr = head;
	while (ptr != NULL)
	{
		if (ptr->getDrawNum() == drawNumber)
		{
			return ptr;
		}
		ptr = ptr->getNextTicket();
	}
	cout << "There are no tickets with that Draw Number!" << endl;
	return nullptr;
}
