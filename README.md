# AdvancedC_project_25013464
&lt;Smart Meal Advisor> is a C-based console application that recommends meal recipes based on the user’s dietary preferences, fitness goals, allergies, and available ingredients.
Project Description:
The program will allow users to select their diet type (e.g., vegan, halal, lactose-free), specify allergies, and choose their goal — weight loss, maintenance, or muscle gain.
Based on this information, it will suggest suitable recipes from a saved recipe database.
Users can also add new recipes to the database and save them for future use.
Main Features / Functionalities
User input for diet type, goal (lose/maintain/gain weight), and allergies.
Add and store available food ingredients.
Suggest recipes matching the user’s dietary restrictions and fitness goal.
Add, view, and save new recipes to a file database.
Display results through a menu-driven text interface.
C Programming Concepts to Be Used
File Handling: Reading and writing recipes to a text file (e.g., recipes.txt).
Dynamic Memory Allocation: Storing recipe data and user inputs dynamically using malloc and realloc.
Structures: Defining struct Recipe and struct User to organize program data.
Pointers and Functions: Using pointers for data manipulation and modular function design.
Modular Programming: Code divided into multiple .c and .h files for organization.
Expected Output / User Interface
The program will display a menu-based console interface with options such as:
1. Enter personal detailsEntering Details to get meal advice\n");
2.Show ALL recipes
        printf("3.Add a new recipe\n");
        printf("4.Find Matching Recipes\n");
        printf("5.Show User Details Summary\n");
        printf("6.Exit
Output will show a list of recommended recipes matching the user’s criteria, displayed in the terminal, and data will be stored in files for future use.
