#include <stdio.h>
#include "recipes.h"
//collecting user detais 
void enterDetails(struct UserDetails* u){
    printf("\tEnter your details to get Meal Advice\n");

    printf("\nEnter the ingridients you currently have(using coma): ");
    if (fgets(u->ingredients, sizeof(u->ingredients), stdin) != NULL) u->ingredients[strcspn(u->ingredients, "\n")] = '\0';
    

    printf("\nEnter your goal (e.g., Weight loss / Muscle gain / Maintenance): ");
    if (fgets(u->goal, sizeof(u->goal), stdin) != NULL) u->goal[strcspn(u->goal, "\n")] = '\0';


    printf("\nEnter any dietary restrictions (e.g., Halal / Vegan / Gluten-free/ High-Protein/Low-calorie etc.; or 'none' for no restrictions): ");
    if (fgets(u->dietaryRestrictions, sizeof(u->dietaryRestrictions), stdin) != NULL) u->dietaryRestrictions[strcspn(u->dietaryRestrictions, "\n")] = '\0';

    printf("\nEnter your allergies (if any, using coma; or 'none'): ");
    if (fgets(u->allergies, sizeof(u->allergies), stdin) != NULL) u->allergies[strcspn(u->allergies, "\n")] = '\0';

    printf("\n Your detais have been recorded successfully!\n");

}

void displayUserSummary(const struct UserDetails *u){
    printf("\n\tUser Details Summary:\n");
    printf("Ingredients: %s\n", u->ingredients);
    printf("Goal: %s\n", u->goal);
    printf("Dietary Restrictions: %s\n", u->dietaryRestrictions);
    printf("Allergies: %s\n", u->allergies);
}
