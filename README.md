# AdvancedC_project_25013464
&lt;Smart Meal Advisor> is a C-based console application that recommends meal recipes based on the user’s dietary preferences, fitness goals, allergies, and available ingredients.

# Features

Find recipes matching your available ingredients

Filter by dietary goals (weight loss, muscle gain, maintenance)

Support for dietary restrictions (vegan, halal, gluten-free)

Exclude recipes with allergens

Add and browse recipes

# Compilation
gcc main.c userinput.c recipes.c -o SMA

./SMA

# Recipe File Format
Create allrecipes.txt with this format:

Name; ingredients; instructions; tags; prepTime; calories

Example:

Pasta; chicken breast, onion, mushrooms; fry chicken and mix with pasta; maintenance; 40; 500

Soup; chicken legs; cook for 40 mins; Halal, Weight-loss; 40; 100

# How It Works
Enter your details (ingredients, goal, dietary restrictions, allergies)

Find matching recipes - shows recipes with:

ANY of your ingredients

Your specified goal

Compatible dietary restrictions

NO allergens


# Project Structure
├── main.c              # Main program controller and menu system

├── recipes.c           # Recipe management and matching logic

├── recipes.h           # Header file with struct definitions and function declarations

├── userinput.c         # User input handling functions

└── allrecipes.txt      # Recipe database (text file)

# Key Functions
recipes.c:

showAllRecipes() - Display all recipes from database

addNewRecipe() - Add new recipe to database

findMatchingRecipes() - Match recipes to user preferences

contains() - Case-insensitive substring search for comma-separated values

strdupToLower() - Convert string to lowercase

trim() - Remove leading/trailing whitespace

normalize() - convert tolower and remove spaces,tabs in string



userinput.c:

enterDetails() - Collect user preferences

displayUserSummary() - Show user details


# Expected Output / User Interface
The program will display a menu-based console interface with options such as:
1. Entering Details to get meal advice
2. Show ALL recipes
3. Add a new recipe
4. Find Matching Recipes
5. Show User Details Summary
6. Exit
   
Output will show a list of recommended recipes matching the user’s criteria, displayed in the terminal, and data will be stored in files for future use.
