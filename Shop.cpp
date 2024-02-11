#include "Shop.h"

using namespace std;

// Shop
// Default constructor that has default values
Shop::Shop() {
    
    // The initial shop setup
    m_shopName = "Test";
    m_numIngredients = 0;
    m_shopRank = 'F';
}

// Shop
// Overloaded constructor that has default values
Shop::Shop(string name) {
    
    // The initial shop setup
    m_shopName = name;
    m_numIngredients = 0;
    m_shopRank = 'F';
}

// GetName
// Returns the name of the player's shop
string Shop::GetName() {
    return m_shopName;
}

// SetName
// Lets the player chooses and assigns the name of the player's shop
void Shop::SetName(string name) {
    m_shopName = name;
}

// CheckIngredient
// Givens a list of ingredients and returns the index of a specific ingredient
int Shop::CheckIngredient(Ingredient ingredient) {
    
    // Checks if the ingredient is in the current loaded shop list
    for (int i = 0; i < m_numIngredients; i++) {
        if (m_myIngredients[i].m_name == ingredient.m_name) {
            return i;
        }
    }
    return -1;
}

// AddIngredient
// Givens a list of ingredients and adds the initial setup of each loaded ingredient
void Shop::AddIngredient(Ingredient ingredient) {
    
    // Adds the initial setup of each loaded ingredient to the ingredient list from the data file
    ingredient.m_quantity = 0;
    m_myIngredients[m_numIngredients] = ingredient;
    m_numIngredients++;
}

// IncrementQuantity
// Givens a list of ingredients and increases the quantity of an asked ingredient
void Shop::IncrementQuantity(Ingredient ingredient) {
    int assignedIndex = CheckIngredient(ingredient); // Index of an asked ingredient
    
    // Increases the quantity of an asked ingredient in the current shop list
    if (assignedIndex != -1) {
        m_myIngredients[assignedIndex].m_quantity++;
    }
}

// DecrementQuantity
// Givens a list of ingredients and decreases the quantity of an asked ingredient
// Decreases only when its quantity is greater than 0 and returns true. Otherwise, returns false
bool Shop::DecrementQuantity(Ingredient ingredient) {
    int assignedIndex = CheckIngredient(ingredient); // Index of an asked ingredient
    
    // Decreases the quantity of an asked ingredient in the current shop list
    if (assignedIndex != -1) {
        if (m_myIngredients[assignedIndex].m_quantity > 0) {
            m_myIngredients[assignedIndex].m_quantity--;
            return true;
        }
    }
    return false;
}

// CheckQuantity
// Givens two same lists of ingredients and assigns two different ingredients
// Returns true when the quantities of both ingredients are greater than 0
// Otherwise, returns false
bool Shop::CheckQuantity(Ingredient ingredientOne, Ingredient ingredientTwo) {
    int ingOneIndex = CheckIngredient(ingredientOne); // Index of Ingredient one to merge
    int ingTwoIndex = CheckIngredient(ingredientTwo); // Index of Ingredient two to merge
    
    // Checks if each ingredient is greater than 0 in the current shop list
    if (ingOneIndex != -1 && ingTwoIndex != -1) {
        if (m_myIngredients[ingOneIndex].m_quantity > 0 && m_myIngredients[ingTwoIndex].m_quantity > 0) {
            return true;
        }
    }
    return false;
}

// GetIngredient
// Returns a specific index of an asked ingredient
Ingredient Shop::GetIngredient(int assignedIndex) {
    
    // Checks if the shop has the specific ingredient
    // If it has, returns the specific index in the current shop list
    if (assignedIndex < m_numIngredients) {
        return m_myIngredients[assignedIndex];
    }
    
    return Ingredient();
}

// CalcRank
// Calculates the player's achievement in the game and their ingredient collection percentage
void Shop::CalcRank() {
    int totalIngredients = IngredientCount(); // Total ingredients that are greater than 0 in the current shop list
    int percentage = (totalIngredients * 100) / PROJ2_SIZE; // Accomplished percentage of collected ingredient
    
    if (percentage >= 0 && percentage < RANK_D) {
        m_shopRank = 'F';
        
    } else if (percentage >= RANK_D && percentage < RANK_C) {
        m_shopRank = 'D';
        
    } else if (percentage >= RANK_C && percentage < RANK_B) {
        m_shopRank = 'C';
        
    } else if (percentage >= RANK_B && percentage < RANK_A) {
        m_shopRank = 'B';
        
    } else if (percentage >= RANK_A && percentage < RANK_S) {
        m_shopRank = 'A';
        
    } else if (percentage == RANK_S) {
        m_shopRank = 'S';
    }
}

// GetRank
// Returns the character of the current player's shop rank
char Shop::GetRank() {
    return m_shopRank;
}

// IngredientCount
// Returns the number of ingredients currently greater than 0 in the ingredient list
int Shop::IngredientCount() {
    int count = 0; // The number of ingredients
    
    for (int i = 0; i < PROJ2_SIZE; i++) {
        if(m_myIngredients[i].m_quantity > 0) {
            count++;
        }
    }
    
    return count;
}

// ShopScore
// Displays the player's score in the game
void Shop::ShopScore() {
    float percentage = (float)IngredientCount() / PROJ2_SIZE * 100; // Accomplished percentage of collected ingredient

    CalcRank();
    cout << "\n" << endl;
    cout << "***The Potion Shop***" << endl;
    cout << "Owned by: " << m_shopName << endl;
    cout << "There are " << PROJ2_SIZE << " available products" << endl;
    cout << "This shop has " << IngredientCount() << " products in stock." << endl;
    cout << "Which is " << percentage << "%" << endl;
    cout << "Shop rank: " << GetRank() << endl;
    
    // End game condition message
    if (GetRank() == 'S') {
        cout << "Congratulations! Your shop reaches S rank and you won the game!" << endl;
    }
    
    cout << "*********************" << endl;
    cout << "\n" << endl;
}
