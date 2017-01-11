#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

/*
TEST CASES
CASE 1:
Input: 1, 4, 1, 2, Bob's Shop, 5, 3, Pho Plus, 5, 2, 2, 2, 2, 2, 2, 2
Expected Result: List rest., List shuffled rest., add Bob's Shop, tourney won't start, remove Pho Plus, run tourney, winner is announced
Actual Result: List rest., List shuffled rest., add Bob's Shop, tourney won't start, remove Pho Plus, run tourney, winner is announced

CASE 2:
Input: 4, 5, 2, 1, 2, 2, 1, 2, 1
Expected Result: Shuffle rest., run tourney, announce winner
Actual Result: Shuffle rest., run tourney, announce winner

CASE 3:
Input: 3, Chick-fil-a, 4, 5, 2, Burger King, 5, 2, 2, 2, 2, 2, 2, 2
Expected Result: Remove Chick-fil-a, shuffle rest., tourney can't run, add Burger King, run tourney, display winner
Actual Result: Remove Chick-fil-a, shuffle rest., tourney can't run, add Burger King, run tourney, display winner
*/

//Global Constants
const int OFFSET_FACTOR = 1;
const int DIVIDING_FACTOR = 2;
const int DISPLAY_RESTAURANT_LIST = 1;
const int ADD_RESTAURANT_TO_LIST = 2;
const int REMOVE_RESTAURANT_FROM_LIST = 3;
const int SHUFFLE_RESTAURANT_LIST = 4;
const int START_TOURNAMENT = 5;
const int END_PROGRAM = 6;

//Displays options for user input
void displayMainMenu()
{
	cout << "Please select one of the following options:" << endl << endl;
	cout << "1 - Display all restaurants" << endl;
	cout << "2 - Add a restaurant" << endl;
	cout << "3 - Remove a restaurant" << endl;
	cout << "4 - Shuffle the vector" << endl;
	cout << "5 - Begin the tournament" << endl;
	cout << "6 - Quit the program" << endl << endl;
}

//Initializes restaurant list with 8 restaurants
void initializeRestaurants(vector<string>& restaurants)
{
	restaurants.push_back("Chick-Fil-A");
	restaurants.push_back("McDonald's");
	restaurants.push_back("KFC");
	restaurants.push_back("Wendy's");
	restaurants.push_back("Pho Plus");
	restaurants.push_back("Black Sheep");
	restaurants.push_back("Sonic");
	restaurants.push_back("Arby's");
}

//Displays list of restaurants
void displayAllRestaurants(vector<string>& restaurants)
{
	int lastRestaurant = (restaurants.size() - OFFSET_FACTOR);
	int firstRestaurant = 0;

	for (firstRestaurant; firstRestaurant < lastRestaurant; firstRestaurant++)
	{
		cout << restaurants[firstRestaurant] << ", ";
	}

	cout << restaurants[lastRestaurant];
}

//Locates restaurant if it exists in the list
int findRestaurant(vector<string>& restaurants, string input)
{
	int ifFoundValue;

	for (int restaurantIndex = 0; restaurantIndex < restaurants.size(); restaurantIndex++)
	{
		if (input == restaurants[restaurantIndex])
		{
			ifFoundValue = restaurantIndex;
			break;
		}
		else
		{
			ifFoundValue = -1;
		}
	}

	return ifFoundValue;
}

//Adds restaurant to the list
void addRestaurant(vector<string>& restaurants, string restaurantToAdd)
{
	restaurants.push_back(restaurantToAdd);
}

//Erases restaurant from the list if it exists on the list
void removeRestaurant(vector<string>& restaurants, string restaurantToRemove)
{
	for (int restaurantIndex = 0; restaurantIndex < restaurants.size(); restaurantIndex++)
	{
		if (restaurants[restaurantIndex] == restaurantToRemove)
		{
			restaurants.erase(restaurants.begin() + restaurantIndex);
		}
	}
}

//Randomizes the restaurant in the list
void shuffleRestaurant(vector<string>& restaurants)
{
	srand(0);

	for (int restaurantIndex = 0; restaurantIndex < restaurants.size(); restaurantIndex++)
	{
		int random = rand() % 8;
		string temporaryPlacement = restaurants[restaurantIndex];
		restaurants[restaurantIndex] = restaurants[random];
		restaurants[random] = temporaryPlacement;
	}
}

//Determines if the number of restaurants in the list is a power of 2
bool isPowerOfTwo(int sizeOfVector)
{
	return ((sizeOfVector > 0) && ((sizeOfVector & (sizeOfVector - OFFSET_FACTOR)) == 0));
}

//Determines which restaurants advance in tournament based on user input
void startTournament(vector<string>& restaurants, vector<string>& winners, vector<string>& originalRestaurants, int roundNumber)
{
	int matchNumber = 1;

	for (int restaurantIndex = 0; restaurantIndex < restaurants.size(); restaurantIndex = restaurantIndex + 2)
	{
		string chooseRestaurant;

		do
		{
			int totalMatches = (restaurants.size() / DIVIDING_FACTOR);
			int totalRounds = (log10(originalRestaurants.size())) / (log10(DIVIDING_FACTOR));


			cout << "Match " << matchNumber << "/" << totalMatches << ", Round " << roundNumber << "/" << totalRounds << " --- ";
			cout << "1: " << restaurants[restaurantIndex] << " or 2: " << restaurants[restaurantIndex + OFFSET_FACTOR] << "? ";
			cin >> chooseRestaurant;

			if (chooseRestaurant != "1" && chooseRestaurant != "2")
			{
				cout << "Invalid response (" << chooseRestaurant << ")" << endl;
			}
			if (chooseRestaurant == "1")
			{
				winners.push_back(restaurants[restaurantIndex]);
				matchNumber += OFFSET_FACTOR;
			}
			if (chooseRestaurant == "2")
			{
				winners.push_back(restaurants[restaurantIndex + OFFSET_FACTOR]);
				matchNumber += OFFSET_FACTOR;
			}

		} while (chooseRestaurant != "1" && chooseRestaurant != "2");
	}
}

int main()
{
	vector<string> restaurants;
	initializeRestaurants(restaurants);

	int userSelection;

	//Menu continues to display unless a winner is determined or option 6 is selected
	do
	{
		displayMainMenu();

		cin >> userSelection;
		cout << endl;

		if (userSelection == DISPLAY_RESTAURANT_LIST)
		{
			displayAllRestaurants(restaurants);
			cout << endl << endl;
		}
		else if (userSelection == ADD_RESTAURANT_TO_LIST)
		{
			string restaurantToAdd;
			cin.ignore();

			cout << "Enter the restaurant you want to add to the list: ";
			getline(cin, restaurantToAdd);
			cout << endl;

			int determineValidRestaurant = findRestaurant(restaurants, restaurantToAdd);

			if (determineValidRestaurant != -1)
			{
				cout << "That restaurant is already on the list. " << endl << endl;
				userSelection = 1;
			}
			else
			{
				addRestaurant(restaurants, restaurantToAdd);
				cout << restaurantToAdd << " was added to the list. " << endl << endl;
				userSelection = 1;
			}
		}
		else if (userSelection == REMOVE_RESTAURANT_FROM_LIST)
		{
			string restaurantToRemove;
			cin.ignore();

			cout << "Enter the restaurant you want to remove from the list: ";
			getline(cin, restaurantToRemove);
			cout << endl;

			int determineValidRestaurant = findRestaurant(restaurants, restaurantToRemove);

			if (determineValidRestaurant != -1)
			{
				removeRestaurant(restaurants, restaurantToRemove);
				cout << restaurantToRemove << " was removed from the list. " << endl << endl;
				userSelection = 1;
			}
			else
			{
				cout << "That restaurant cannot be removed because it is not on the list. " << endl << endl;
				userSelection = 1;
			}
		}
		else if (userSelection == SHUFFLE_RESTAURANT_LIST)
		{
			shuffleRestaurant(restaurants);
			cout << "The list of restaurants has been shuffled." << endl << endl;
		}
		else if (userSelection == START_TOURNAMENT)
		{
			bool testForPowerOfTwo = isPowerOfTwo(restaurants.size());

			if (testForPowerOfTwo == false) //Don't start tournament unless the number of restaurants is a power of 2
			{
				cout << "The tournament can't begin because the number of restaurants is not a power of two. " << endl << endl;
			}
			else
			{
				vector<string> winners; //Winners of each round will be stored in new vector
				vector<string> originalRestaurants = restaurants; //Keeps original vector data

				int factorsOfTwo = (log10(restaurants.size())) / (log10(DIVIDING_FACTOR)); //Determines the number of Rounds

				int roundNumber = 1;

				for (int factorIndex = 0; factorIndex < factorsOfTwo; factorIndex++)
				{
					startTournament(restaurants, winners, originalRestaurants, roundNumber);
					restaurants = winners;
					winners.clear();
					roundNumber += OFFSET_FACTOR;
				}

				//Displays winner; ends program
				cout << endl;
				displayAllRestaurants(restaurants);
				cout << " is the winner!" << endl << endl;
				break;
			}
		}
	} while (userSelection != END_PROGRAM);

	system("pause");
	return 0;
}
