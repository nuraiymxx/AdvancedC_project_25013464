
#include "recipes.h"
// main menu and program controlling
// user interaction ans connecting modules
int main(){
    struct UserDetails currentUser;
    int choice = 0;

    printf("\t\tWELCOME TO SMART MEAL ADVISER!\n");
    while(1){
        printf("\n\tMain menu\n");
        printf("1.Entering Details to get meal advice\n");
        printf("2.Show ALL recipes\n");
        printf("3.Add a new recipe\n");
        printf("4.Find Matching Recipes\n");
        printf("5.Show User Details Summary\n");
        printf("6.Exit\n");
        printf("\nEnter your choice: ");

        scanf("%d", &choice);
        getchar();  // Clear newline character from input buffer

    switch(choice){
        case 1:
            enterDetails(&currentUser);
            break;
        case 2:
            showAllRecipes();
            break;
        case 3:
            addNewRecipe();
            break;
        case 4:
            findMatchingRecipes(&currentUser);
            break;
        case 5:
            displayUserSummary(&currentUser);
            break;
        case 6:
            printf("Exiting the program. Thank you for using Smart meal Adviser. Goodbye!\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
    }
}

    return 0;

}




// To compile and run the program, use the following commands in your terminal:
// cd SmartMealAdviser // cd SmartMealAdv // ls 
// gcc main.c userinput.c recipes.c -o SMA
// ./SMA