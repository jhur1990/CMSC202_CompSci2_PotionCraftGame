#include "Game.h"

using namespace std;

// Game
// Default constructor
Game::Game() {
}

// LoadIngredients
// Loads data from a .txt file
void Game::LoadIngredients() {
    ifstream inFile; // Declares and opens a file
    int numIngredientsAdded = 0; // The current number of ingredients accessed from the data .txt file
    string name, type, ingOne, ingTwo; // Ingredient's name, type, and two combination ingredients
    Ingredient newIngredient; // Ingredient array

    // Opens data file
    inFile.open(PROJ2_DATA);
    
    // Pops error messages if a file can't be loaded
    if (!inFile){
        cout << "Error opening file " << PROJ2_DATA << endl;
        cout << "No ingredients loaded." << endl;
        cout << "\n" << endl;

    } else {
        
        // Reads the data file and store each ingredient by name, type, and combination recipe
        while ((numIngredientsAdded < PROJ2_SIZE) && inFile) {
            getline(inFile, name, ',');
            getline(inFile, type, ',');
            getline(inFile, ingOne, ',');
            getline(inFile, ingTwo);
            
            newIngredient.m_name = name;
            newIngredient.m_type = type;
            newIngredient.m_ingredient1 = ingOne;
            newIngredient.m_ingredient2 = ingTwo;
            
            m_myShop.AddIngredient(newIngredient);
            numIngredientsAdded++;
        }
        
        cout << numIngredientsAdded << " ingredients loaded." << endl;
        cout << "\n" << endl;//
        
        //Asks for the player's shop name
        cout << "What is the name of your shop?" << endl;
        getline(cin, name);
        cout << "\n" << endl;
        m_myShop.SetName(name);
    }
    
    inFile.close();
}

// StartGame
// Game initial setup includes the shop's name
void Game::StartGame() {
    string name; // Shop name
    int mainMenuChoice = 0; // Player's input on the main menu

    // Game initial title and loads game data .txt file
    GameTitle();
    LoadIngredients();
    
    // Keeps displaying the main menu unless the player enters 5 to exit the game or presses 4 when the winning condition meets while in the main menu
    while (mainMenuChoice <= 3 || (mainMenuChoice == 4 && m_myShop.GetRank() != 'S')) {
        mainMenuChoice = MainMenu();
    }
}

// DisplayIngredients
// Displays the entire list of ingredients loaded from the file
void Game::DisplayIngredients() {
    cout << "\n" << endl;
    
    // Displays the ingredients list with its quantity
    for (int i = 0; i < PROJ2_SIZE; i++) {
        if (m_myShop.GetIngredient(i).m_name != "") {
            cout << i + 1 << ". " << m_myShop.GetIngredient(i).m_name << " " << m_myShop.GetIngredient(i).m_quantity << endl;
        }
    }
    
    cout << "\n" << endl;
}

// MainMenu
// Lets the player chooses in-game activities from the menu; display list, search and merge ingredients, score, and quit the game
int Game::MainMenu() {
    int mainMenuChoice = 0; // Player's input on the main menu
    
    cout << "What would you like to do in " << m_myShop.GetName() << "'s shop?" << endl;
    cout << "1. Display your Shop's Ingredients" << endl;
    cout << "2. Search for Natural Ingredients" << endl;
    cout << "3. Attempt to Merge Ingredients" << endl;
    cout << "4. See Score" << endl;
    cout << "5. Quit" << endl;
    
    cin >> mainMenuChoice;
    
    // Input validation for the main menu - asks the player to only enter between 1 and 5
    while (mainMenuChoice < 1 || mainMenuChoice > 5) {
        cout << "Invalid Input. Please enter a number between 1 and 5." << endl;
        cin >> mainMenuChoice;
    }
    
    // Main menu
    switch (mainMenuChoice) {
        case 1:
            
            // Displays the entire list of ingredients
            DisplayIngredients();
            break;
            
        case 2:
            
            // Searches for a random natural typed ingredient
            SearchIngredients();
            break;
            
        case 3:
            
            // Merges two ingredients into another ingredient
            CombineIngredients();
            break;
            
        case 4:
            
            // Shows the current shop's score
            m_myShop.ShopScore();
            break;
            
        case 5:
            
            // Exit game
            cout << "\n" << endl;
            cout << "Thanks for playing UMBC Potion Craft!" << endl;
            break;
    }
    
    return mainMenuChoice;
}

// SearchIngredients
// Lets the player searches a random natural typed ingredients
void Game::SearchIngredients() {
    string searchType = "natural"; // Declares natural typed ingredients
    int count = 0; // The number of natural typed ingredients
    
    // Counts how many natural typed ingredients are available in the ingredient list
    for (int i = 0; i < PROJ2_SIZE; i++) {
        if (m_myShop.GetIngredient(i).m_type == searchType) {
            count++;
        }
    }
    
    int randomIndex = rand() % count + 1; // Assigns a random index
    count = 0; // Resets the count
    
    for (int i = 0; i < PROJ2_SIZE; i++) {
        
        // Re-counts the natural typed ingredients in the ingredient list
        if (m_myShop.GetIngredient(i).m_type == searchType) {
            count++;

            // Adds a quantity of a random indexed natural typed ingredient
            if (count == randomIndex) {
                m_myShop.IncrementQuantity(m_myShop.GetIngredient(i));
                cout << "You found " << m_myShop.GetIngredient(i).m_name << "!" << endl;
                cout << "\n" << endl;
                break;
            }
        }
    }
}

// CombineIngredients
// Merges two ingredients into another ingredient
void Game::CombineIngredients() {
    int choiceOne = 0, choiceTwo = 0; // Two ingredient choices of the player to merge
    
    cout << "\n" << endl;
    cout << "Select two ingredients to combine: " << endl;
    
    // Re-asks for a combined ingredient when the player enters -1 (converted to -2) to see a list of ingredients
    do {
        cout << "** Ingredient 1 **" << endl;
        RequestIngredient(choiceOne);
    } while (choiceOne == -2);
    
    cout << "\n" << endl;

    do {
        cout << "** Ingredient 2 **" << endl;
        RequestIngredient(choiceTwo);
    } while (choiceTwo == -2);
    
    
    // Searches the player's choices in the ingredient recipe
    int recipeIndex = SearchRecipes(m_myShop.GetIngredient(choiceOne).m_name, m_myShop.GetIngredient(choiceTwo).m_name);
 
    // Proceeds when there is a recipe of two ingredients the player entered
    if (recipeIndex != -1) {
        
        // Checks if both of the ingredients are greater than 0
        if (m_myShop.CheckQuantity((m_myShop.GetIngredient(choiceOne)), (m_myShop.GetIngredient(choiceTwo))) == true) {
            
            // Checks if the ingredient is two when the player chooses the same ingredient twice
            if ((choiceOne == choiceTwo) && (m_myShop.GetIngredient(choiceOne).m_quantity >= 2 || m_myShop.GetIngredient(choiceTwo).m_quantity >= 2)) {
                bool choiceOneDecrement = m_myShop.DecrementQuantity(m_myShop.GetIngredient(choiceOne));
                bool choiceTwoDecrement = m_myShop.DecrementQuantity(m_myShop.GetIngredient(choiceTwo));
                m_myShop.IncrementQuantity(m_myShop.GetIngredient(recipeIndex));
                
                // If the quantity of each ingredient exceeds 0, then decrease the quantity
                if (choiceOneDecrement == true && choiceTwoDecrement == true) {
                    cout << m_myShop.GetIngredient(choiceOne).m_name << " combined with " << m_myShop.GetIngredient(choiceTwo).m_name << " to make " << m_myShop.GetIngredient(recipeIndex).m_name << "!" << endl;
                    cout << "You have made " << m_myShop.GetIngredient(recipeIndex).m_name << " for your shop." << endl;
                    cout << "\n" << endl;
                }
                
            // Checks if each ingredient is one when the player chooses the two different ingredient
            } else if ((choiceOne != choiceTwo) && (m_myShop.GetIngredient(choiceOne).m_quantity >= 1 && m_myShop.GetIngredient(choiceTwo).m_quantity >= 1)) {
                bool choiceOneDecrement = m_myShop.DecrementQuantity(m_myShop.GetIngredient(choiceOne));
                bool choiceTwoDecrement = m_myShop.DecrementQuantity(m_myShop.GetIngredient(choiceTwo));
                m_myShop.IncrementQuantity(m_myShop.GetIngredient(recipeIndex));
                
                if (choiceOneDecrement == true && choiceTwoDecrement == true) {
                    cout << m_myShop.GetIngredient(choiceOne).m_name << " combined with " << m_myShop.GetIngredient(choiceTwo).m_name << " to make " << m_myShop.GetIngredient(recipeIndex).m_name << "!" << endl;
                    cout << "You have made " << m_myShop.GetIngredient(recipeIndex).m_name << " for your shop." << endl;
                    cout << "\n" << endl;
                }
            
            // If none of the above conditions are met, do not combine anything
            } else {
                cout << "You do not have enough " << m_myShop.GetIngredient(choiceOne).m_name << " or " << m_myShop.GetIngredient(choiceTwo).m_name << " to attempt that merge." << endl;
                cout << "\n" << endl;
            }
        
        // If both of the ingredients are equal to 0, do not combine anything
        } else {
            cout << "You do not have enough " << m_myShop.GetIngredient(choiceOne).m_name << " or " << m_myShop.GetIngredient(choiceTwo).m_name << " to attempt that merge." << endl;
            cout << "\n" << endl;
        }
    
    // When there is no available recipe in the data file, do not combine anything
    } else {
        cout << "No recipe found using " << m_myShop.GetIngredient(choiceOne).m_name << " and " << m_myShop.GetIngredient(choiceTwo).m_name <<"." << endl;
        cout << "\n" << endl;
    }
}

// RequestIngredient
// Asks the player which ingredients to be merged
void Game::RequestIngredient(int &choice) {
    cout << "Enter the number of the ingredient you want to select: " << endl;
    cout << "To list known ingredients enter -1" << endl;
    cin >> choice;
    
    // Converts the player's choice to the actual index of the array
    choice -= 1;
    
    // Displays the ingredient list during the combination process when -1 entered
    if (choice == -2) {
        DisplayIngredients();
        
    } else {
        
        // Input validation - asks the player to enter 1 to 32
        while (choice == -1 || choice < -2 || choice >= PROJ2_SIZE){
            cout << "Invalid choice. Please select an available ingredient: " << endl;
            cin >> choice;
            choice -= 1;
        }
    }
}

// SearchRecipes
// Searches a recipe of two entered ingredients
int Game::SearchRecipes(string ingredientOneName, string ingredientTwoName) {
    for (int i = 0; i < PROJ2_SIZE; i++) {
        
        // Finds a correct recipe regardless of the order
        if (m_myShop.GetIngredient(i).m_ingredient1 == ingredientOneName && m_myShop.GetIngredient(i).m_ingredient2 == ingredientTwoName){
            return i;
                
        } else if (m_myShop.GetIngredient(i).m_ingredient1 == ingredientTwoName && m_myShop.GetIngredient(i).m_ingredient2 == ingredientOneName) {
            return i;
        }
    }
    
    return -1;
}

