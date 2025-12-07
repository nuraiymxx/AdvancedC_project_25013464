#ifndef Recipes_H
#define Recipes_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct UserDetails{
    char ingredients[256];
    char goal[50];
    char dietaryRestrictions[100];
    char allergies[100];
};

struct Recipe{
    char name[100];
    char ingredients[256];
    char instructions[512];
    char tags[100];                                     
    int prepTime; 
    int calories;
};

void enterDetails(struct UserDetails* uDet);// from userinput.c
void displayUserSummary(const struct UserDetails* uDet);

void showAllRecipes(); // from recipes.c
void addNewRecipe();

void findMatchingRecipes(struct UserDetails* uDet);
int contains(const char* haystack, const char* csv_words);

#endif 

