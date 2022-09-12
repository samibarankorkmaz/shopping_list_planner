/*
Sami Baran KORKMAZ
1306191447
Shopping List Planner

Description of the project:

-----You are able to do these things:
1- Create lists.
2- Assign a name for your list.
3- Insert listings into your lists.
4- Mark as done(bought) your listings and undo this if you like.
5- Create a new list, show your lists and delete one if you like. (after any operation)
6- Edit listings(change name or amount, mark as done, remove(delete) it from the list.)
7- Exit the program.
*/


#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;


class ShoppingList
{
public:

	int list_id = 0;
	string listname;

};
class Products : public ShoppingList
{
public:
	int amount = 0;
	string name;
	bool done = false;

};
bool validName(string name)
{
	if (name.length() == 0)
	{
		cout << "You did not insert anything! ";
		return false;
	}



	if (name[0] >= '0' && name[0] <= '9' && name.length() < 2) //So i programmed this function as i supposed that no one enter more then 3-digit number because my one product list can has max 200 products.
	{

		return false;
	}
	return true;
}


int main() {

	vector<ShoppingList> List(10);
	vector<Products> P(200);
	vector<vector<Products>> Product(10);

	bool first_time = true;
	int index_l = 0;
	int index_p = 0;

	/* BeeCay is kind of an abbreviation/nickname for "BK" which are the first letters of my name&surname.So just wanted to set my planner's name up as it is.*/
ListsMenu:
	if (first_time) {
		cout << "Welcome to your beloved shopping list BeeCay!\n";


		cout << "Before creating any list, type the name you would like to assign for your list:\n";

		string list_name;



		getline(cin, list_name);
		cin.clear();
		cout << "\n\n";
		cout << "Your list's name: " << list_name << "\n\n";
		List[index_l].listname = list_name;
		List[index_l].list_id = index_l + 1;
		first_time = false;
	}
	else {
		int counter = 0;
		cout << "List Id" << "	|	" << "List Name \n";
		for (std::vector<ShoppingList>::iterator it = List.begin(); it != List.end(); ++it) {
			if (List[counter].list_id == 0)
			{
				break;
			}
			cout << counter + 1 << "	|	" << List[counter].listname << "	   | \n";

			counter++;
		}
		cout << "-If you would like to create a new list, type 'new'.\n";


		cout << "-If you would like to show a list, type its name.\n";

		cout << "-If you would like to delete a list, please type 'delete' and program will ask you its name.\n";
		cout << "-To exit, please type exit.\n";
		cout << "-->Your command:\n";
		string list_name;
		string says;

		getline(cin, says, '\n');

		cin.clear();

		if (says == "New" || says == "new")
		{
			index_l++;
			cout << "Please type your list's name: ";

			getline(cin, list_name, '\n');

			cout << "Your list's name: " << list_name << "\n";
			List[index_l].listname = list_name;
			List[index_l].list_id = index_l + 1;
			P.clear();
			P.resize(200);
		}
		else if (says == "Delete" || says == "delete")
		{
			string id_delete;
			cout << "Type your list's id: ";
			cin >> id_delete;
			cin.ignore();
			int digits2 = 1;
			int sum2 = 0;
			for (int a = id_delete.length(); a > 0; a--) //This loop is for turning string to a number . Digit is the length of the string. the variable 'digits' is the numbers on the digits. Not the digit of id.
			{
				digits2 = (id_delete[id_delete.length() - a] - '0');
				for (int x = 1; x < a; x++)
				{
					digits2 *= 10;
				}
				sum2 += digits2;
			}
			List.erase(List.begin() + sum2 - 1);
			index_l--;

			goto ListsMenu;
		}
		else if (says == "Exit" || says == "exit")
		{
			return 0;
		}
		else
		{

			bool flag = false;
			cout << "\nYou entered the list: " << says << "\n";
			int ii = 0;
			for (std::vector<ShoppingList>::iterator it = List.begin(); it != List.end(); ++it) {
				if (List[ii].listname == says)
				{
					P = Product[List[ii].list_id - 1];

					flag = true;
					break;
				}
				ii++;

			}
			if (!flag)
			{
				cout << "There is no list with this name.\n\n";
				goto ListsMenu;
			}

		}


	}
InListMenu:
	cout << "Now you could insert products into your list or edit them if you like.\n\n-To insert one, please type its name then program will ask you about some other information.\n-To edit one, type its id number and you will see the further instructions there.\n-To go back to the lists menu, please type 'back'.\n-To exit, please type 'exit'.\n";

	string product_in = "";
	int aa = -1;
	while (1) {


		for (std::vector<Products>::iterator it = P.begin(); it != P.end(); ++it) {
			aa++;
			if (P[aa].amount == 0)
			{
				break;
			}



		}
		string status1;
		int print = 0;
		for (std::vector<Products>::iterator it = P.begin(); it != P.end(); ++it) {
			status1 = P[print].done ? "(X)" : "( )";
			if (P[print].amount == 0)
			{
				break;
			}
			cout << print + 1 << "	|	" << P[print].name << "	   |		" << status1 << "	|		" << P[print].amount << "		| 		 \n";

			print++;
		}
		index_p = aa;

		getline(cin, product_in, '\n');

		P[index_p].list_id = index_l + 1;
		P[index_p].name = product_in;
		if (product_in == "Exit" || product_in == "exit") {
			return 0;
		}
		if (validName(product_in) && product_in != "Exit")
		{

			if (product_in == "Back" || product_in == "back") {
				Product[P[0].list_id - 1] = P;
				goto ListsMenu;

			}





			cout << "\nWhat is the amount of your product: ";
			cin >> P[index_p].amount;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			index_p++;
		}



		else if (product_in.length() > 0) {
			string decision;
			int digits = 1;
			int sum = 0;
			for (int a = product_in.length(); a > 0; a--) //This loop is for turning string to a number with ASCII representatives. Digit is the length of the string. the variable 'digits' is the numbers on the digits. Not the digit of id.
			{
				digits = (product_in[product_in.length() - a] - '0');
				for (int x = 1; x < a; x++)
				{
					digits *= 10;
				}
				sum += digits;
			}
			index_p = sum - 1; //This is the index for vector P and that is the vector of products in a list.




			cin.clear();
			string status;
			status = P[index_p].done ? "(X)" : "( )";
			cout << "This is your product:\n";
			cout << "Name	 |		Done	|		Amount		| 		 " << "\n";



			cout << "\nWhat would you like to edit in this product?\n1.Change Name\n2.Mark as Bought\n3.Change Amount\n4.Delete It\n";
			cin >> decision, '\n';

			if (decision == "1")
			{
				cout << "Type the new name you'd like to assign: ";
				cin >> P[index_p].name;


			}
			else  if (decision == "2") {

				cout << "The item has checked.\n";
				P[index_p].done = true;

			}
			else if (decision == "3") {

				cout << "Type the amount you would like: ";
				cin >> P[index_p].amount;

			}
			else if (decision == "4")
			{
				P.erase(P.begin() + index_p);
				cout << "The listing has deleted from list.\n";
			}
			else {

				cout << "You typed something wrong. Please check it out!\n\n";

			}

		}
		else { 
			cout << "You typed wrong command!\n";
			goto InListMenu;
		}
	}
	cout << "\n\n";
	cout << "This is what you get:\n";
	cout << "Id" << "	|	" << "Name	   |		Category	|		Amount		| 		 " << "\n";
	int i = 0;



	string status1;
	for (std::vector<Products>::iterator it = P.begin(); it != P.end(); ++it) {
		status1 = P[i].done ? "(X)" : "( )";
		if (P[i].amount == 0)
		{
			break;
		}
		cout << i + 1 << "	|	" << P[i].name << "	   |		" << status1 << "	|		" << P[i].amount << "		| 		 \n";

		i++;
	}

	Product[P[0].list_id - 1] = P;
	goto InListMenu;

	return 0;
}

