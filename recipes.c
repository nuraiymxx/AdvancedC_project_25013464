#define _GNU_SOURCE

#include <ctype.h>
#include <stdio.h>
#include "recipes.h"

static char *strdupToLower(const char *s){
    if(!s) return NULL;
    char *copy = strdup(s);
    if(!copy) return NULL;
    for(size_t i=0; copy[i]; i++){
        copy[i] = (char)tolower(copy[i]);
    }
    return copy;
}

static void trim(char *s){
    if(!s) return;
    size_t len = strlen(s);
    while(len>0 && (s[len-1] == '\n' || s[len-1] == '\r' || s[len-1] == ' ' || s[len-1] == '\t')){
        s[len-1] = '\0';
        len--;
    }

    char *start = s;
    while(*start == ' '|| *start == '\t') start++;
    if(start != s) memmove (s, start, strlen(start)+1);
}

static void normalize(char *s) {
    char *src = s, *dst = s;
    while (*src) {
        if (*src != ' ' && *src != '-') {
            *dst++ = (char)tolower(*src);
        }
        src++;
    }
    *dst = '\0';
}

int contains(const char* haystack , const char* csv_words){
    if(!csv_words|| strlen(csv_words) == 0) return 0;
    if(!haystack) return 0;

    char *h = strdup(haystack);
    char *n = strdup(csv_words);
    if(!h || !n) {
        free(h); 
        free(n); 
        return 0; }
    normalize(h);
    int found = 0;
    char *token = strtok(n, ",");
    while(token){
        trim(token);
        normalize(token);
        if(strlen(token) >0){
            if(strstr(h, token) != NULL){
                found = 1;
                break;
            }
        }
        token = strtok(NULL, ",");
    }
    free(h);
    free(n);
    return found;
}

void showAllRecipes(){
    FILE *file = fopen("allrecipes.txt", "r");
    if (file == NULL) {
        printf("Error opening allrecipes.txt file.\n");
        return;
    }   

    printf("\n\tShowing all recipes available in the database:\n");

    struct Recipe r;
    char line[1024];

    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        trim(line);
        if (strlen(line) == 0) continue;
        // Parse the line into the Recipe structure
        int scanned = sscanf(line, "%99[^;]; %255[^;]; %511[^;]; %99[^;]; %d; %d",
               r.name, r.ingredients, r.instructions, r.tags, &r.prepTime, &r.calories);
        if (scanned < 6) {
            continue;} 
        trim(r.name); trim(r.ingredients); trim(r.instructions); trim(r.tags);   
        // Display the recipe details
        printf("\nRecipe %d:\n", ++count);
        printf("Name: %s\n", r.name);
        printf("Ingredients: %s\n", r.ingredients);
        printf("Instructions: %s\n", r.instructions);
        printf("Tags: %s\n", r.tags);
        printf("Preparation Time: %d minutes\n", r.prepTime);
        printf("Calories: %d kcal\n", r.calories);
    }

    if (count == 0) {
        printf("No recipes found in the database.\n");
    }

    fclose(file);
}

void addNewRecipe(){
    struct Recipe r;

    printf("\n\tAdding a new recipe to the database:\n");

    printf("Enter recipe name: ");
    fgets(r.name, sizeof(r.name), stdin);
    r.name[strcspn(r.name, "\n")] = 0; // Remove newline character
    trim(r.name);

    printf("Enter ingredients (comma-separated): ");
    fgets(r.ingredients, sizeof(r.ingredients), stdin);
    r.ingredients[strcspn(r.ingredients, "\n")] = 0;         
    trim(r.ingredients);

    printf("Enter instructions: ");
    fgets(r.instructions, sizeof(r.instructions), stdin);
    r.instructions[strcspn(r.instructions, "\n")] = 0;   
    trim(r.instructions);

    printf("Enter tags (comma-separated): ");
    fgets(r.tags, sizeof(r.tags), stdin);
    r.tags[strcspn(r.tags, "\n")] = 0;              
    trim(r.tags);
    
    printf("Enter preparation time (in minutes): ");
    scanf("%d", &r.prepTime);
    getchar(); // Clear newline character from input buffer 

    printf("Enter calories: ");
    scanf("%d", &r.calories);
    getchar();

    FILE *file = fopen("allrecipes.txt", "a");
    if (file == NULL) {
        printf("Error opening allrecipes.txt file for writing.\n");
        return; 
    }

    fprintf(file, "\n%s; %s; %s; %s; %d; %d\n", r.name, r.ingredients, r.instructions, r.tags, r.prepTime, r.calories);
    fclose(file);   

    printf("Recipe was added successfully!\n");

    
}


void findMatchingRecipes(struct UserDetails* uDet) {
    if (!uDet) return;
    FILE *file = fopen("allrecipes.txt", "r");
    if (file == NULL) {
        printf("Error opening allrecipes.txt file.\n");
        return;
    }   

    printf("\n\tFinding matching recipes based on your details:\n");

    struct Recipe r;
    char line[1024];
    int found = 0;

    // Normalize user input fields for robust matching
    char userIngredients[256], userDiet[100], userGoal[50], userAllergies[100];
    strncpy(userIngredients, uDet->ingredients, sizeof(userIngredients));
    strncpy(userDiet, uDet->dietaryRestrictions, sizeof(userDiet));
    strncpy(userGoal, uDet->goal, sizeof(userGoal));
    strncpy(userAllergies, uDet->allergies, sizeof(userAllergies));
    trim(userIngredients); normalize(userIngredients);
    trim(userDiet); normalize(userDiet);
    trim(userGoal); normalize(userGoal);
    trim(userAllergies); normalize(userAllergies);

    while (fgets(line, sizeof(line), file)) {
        trim(line);
        if (strlen(line) == 0) continue;
    
        int scan = sscanf(line, "%99[^;]; %255[^;]; %511[^;]; %99[^;]; %d; %d",
               r.name, r.ingredients, r.instructions, r.tags, &r.prepTime, &r.calories);
        if (scan < 6) {
            continue;}
        trim(r.name); trim(r.ingredients); trim(r.instructions); trim(r.tags);
        char *recIng = strdupToLower(r.ingredients);
        char *recTags = strdupToLower(r.tags);
        if(!recIng) recIng = strdup(""); 
        if(!recTags) recTags = strdup("");
        trim(recIng); normalize(recIng);
        trim(recTags); normalize(recTags);

        int ingMatch = 0;
        if(strlen(userIngredients)>0){
            if(contains(recIng, userIngredients)){
                ingMatch = 1;
            }
        } else {
            ingMatch = 1; 
        }

        int dietMatch = 1;
        if (strlen(userDiet)>0 && strcasecmp(userDiet, "none") !=0){
            dietMatch = contains(r.tags, userDiet);
        }

        int goalMatch = 0;
        if(strlen(userGoal)>0&& strcasecmp(userGoal, "standart") !=0&& strcasecmp(userGoal, "none") !=0){
            goalMatch = contains(r.tags, userGoal);
        } else {
            goalMatch = 1; 
        }

        int allergMatch = 0;
        if(strcasecmp(userAllergies, "none") !=0 && strlen(userAllergies)>0){
           allergMatch = contains(r.ingredients, userAllergies);
        }

        if (ingMatch && dietMatch && goalMatch && !allergMatch) {
            found = 1;
            // Display the matching recipe details
            printf("\nRecipe Name: %s\n", r.name);
            printf("Ingredients: %s\n", r.ingredients);
            printf("Instructions: %s\n", r.instructions);
            printf("Tags: %s\n", r.tags);
            printf("Preparation Time: %d minutes\n", r.prepTime);
            printf("Calories: %d kcal\n", r.calories);
            
        }
        free(recIng);
        free(recTags);
        
    }

    if (!found) {
        printf("No matching recipes found based on your details.\n");
    }

    fclose(file);
}
