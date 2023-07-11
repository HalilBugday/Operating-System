//Gamze Nur Madan - 260201084
//Halil İbrahim Buğday - 280201094
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LENGTH 500
#define MONTHLENGTH 23

int student_price = 6;
int academic_price = 16;
int admin_price = 12;

struct menu
{
    char date[LENGTH];
    char soup[LENGTH];
    char main_dish[LENGTH];
    char side_dish[LENGTH];
    char extra[LENGTH];
    int sale_count[3];
};

typedef struct menu NormalMenu;
typedef struct menu VeganMenu;
typedef struct menu VegetarianMenu;

typedef struct
{
    char *month;
    NormalMenu *NormalMenuPTR[MONTHLENGTH];
    VeganMenu *VeganMenuPTR[MONTHLENGTH];
    VegetarianMenu *VegetarianMenuPTR[MONTHLENGTH];
} Cafeteria;

Cafeteria cafeteria = {NULL, NULL, NULL, NULL}; // initially NULL

void initialize_menus(Cafeteria *cafeteria, char *csv_file_name)
{
    FILE *csv_file = fopen(csv_file_name, "r");
    if (csv_file == NULL)
    {
        printf("Error: File does not exist! %s\n", csv_file_name);
        exit(1);
    }

    NormalMenu normal_menu = {.sale_count = {0, 0, 0}}; // Student_Academic_Admin
    VeganMenu vegan_menu = {.sale_count = {0, 0, 0}};
    VegetarianMenu vegetarian_menu = {.sale_count = {0, 0, 0}};

    // Read each line with tokenizer
    char line[1000];
    int normal_i = 0;
    int vegan_i = 0;
    int veg_i = 0; // row counters
    while (fgets(line, 500, csv_file) != NULL)
    {
        char *menu_type = strtok(line, ",");
        char *date = strtok(NULL, ",");
        char *soup = strtok(NULL, ",");
        char *main_dish = strtok(NULL, ",");
        char *side_dish = strtok(NULL, ",");
        char *extra = strtok(NULL, ",");

        if (strcmp(menu_type, "\"Normal\"") == 0)
        {
            strcpy(cafeteria->NormalMenuPTR[normal_i]->date, date);
            strcpy(cafeteria->NormalMenuPTR[normal_i]->soup, soup);
            strcpy(cafeteria->NormalMenuPTR[normal_i]->main_dish, main_dish);
            strcpy(cafeteria->NormalMenuPTR[normal_i]->side_dish, side_dish);
            strcpy(cafeteria->NormalMenuPTR[normal_i]->extra, extra);
            normal_i++;
        }

        else if (strcmp(menu_type, "\"Vegan\"") == 0)
        {
            strcpy(cafeteria->VeganMenuPTR[vegan_i]->date, date);
            strcpy(cafeteria->VeganMenuPTR[vegan_i]->soup, soup);
            strcpy(cafeteria->VeganMenuPTR[vegan_i]->main_dish, main_dish);
            strcpy(cafeteria->VeganMenuPTR[vegan_i]->side_dish, side_dish);
            strcpy(cafeteria->VeganMenuPTR[vegan_i]->extra, extra);
            vegan_i++;
        }

        else
        {
            strcpy(cafeteria->VegetarianMenuPTR[veg_i]->date, date);
            strcpy(cafeteria->VegetarianMenuPTR[veg_i]->soup, soup);
            strcpy(cafeteria->VegetarianMenuPTR[veg_i]->main_dish, main_dish);
            strcpy(cafeteria->VegetarianMenuPTR[veg_i]->side_dish, side_dish);
            strcpy(cafeteria->VegetarianMenuPTR[veg_i]->extra, extra);
            veg_i++;
        }
    }
}

void record_customer_counts(Cafeteria *cafeteria){
  srand(time(NULL)); //initializing the random number generator
 
  for (int i = 0; i<MONTHLENGTH+1 ; i++){
    for (int j=0; j<3 ; j++){
      int random_number = rand() % 51; //to choose number between 0 and 50, everytime.
      int random_vegan_number = rand() % 51;
      int random_vegetarian_number = rand() % 51;
      cafeteria->NormalMenuPTR[i]->sale_count[j] = random_number;
      cafeteria->VeganMenuPTR[i] ->sale_count[j] = random_vegan_number;
      cafeteria->VegetarianMenuPTR[i] ->sale_count[j] = random_vegetarian_number;
    }
  }
}

void calc_and_show_income(Cafeteria*cafeteria){
    int normal_income=0;
    int vegan_income=0;
    int vegeterian_income=0;
    int student_income=0;
    int academic_income=0;
    int admin_income=0;
    int total_sale=0;
    for (int i=0; i< MONTHLENGTH+1; i++){

        normal_income += cafeteria->NormalMenuPTR[i]->sale_count[0] * student_price + cafeteria->NormalMenuPTR[i]->sale_count[1] * 
        academic_price + cafeteria->NormalMenuPTR[i]->sale_count[2] * admin_price; //normal  incomes

        vegan_income += cafeteria->VeganMenuPTR[i]->sale_count[0] * student_price + cafeteria->VeganMenuPTR[i]->sale_count[1] * 
        academic_price + cafeteria->VeganMenuPTR[i]->sale_count[2] * admin_price; //vegan  incomes
       
        vegeterian_income += cafeteria->VegetarianMenuPTR[i]->sale_count[0] * student_price + cafeteria->VegetarianMenuPTR[i]->sale_count[1] * 
        academic_price + cafeteria->VegetarianMenuPTR[i]->sale_count[2] * admin_price; //vegan  incomes
    }
    for(int j=0; j<MONTHLENGTH+1; j++){

        student_income += cafeteria->NormalMenuPTR[j]->sale_count[0] * student_price + cafeteria->VeganMenuPTR[j]->sale_count[0] * 
        student_price + cafeteria->VegetarianMenuPTR[j]->sale_count[0] * student_price; //student  incomes 

        academic_income += cafeteria->NormalMenuPTR[j]->sale_count[1] * academic_price + cafeteria->VeganMenuPTR[j]->sale_count[1] * 
        academic_price  + cafeteria->VegetarianMenuPTR[j]->sale_count[1] *  academic_price; //academic  incomes 

        admin_income += cafeteria->NormalMenuPTR[j]->sale_count[2] * admin_price + cafeteria->VeganMenuPTR[j]->sale_count[2] * 
        admin_price + cafeteria->VegetarianMenuPTR[j]->sale_count[2] * admin_price; //admin  incomes    
        
    }
    total_sale=normal_income+vegan_income+vegeterian_income;
    // total_sale = student_income + academic_income + admin_income ----> alternatively!
    printf("~~~~Sales Results in a month\n");
    printf("Normal Menu sales in a month:  %d\n", normal_income);
    printf("Vegan Menu sales in a month:  %d\n", vegan_income);
    printf("vegeterian Menu sales in a month: %d\n", vegeterian_income);
    printf("Income from Students in a month: %d\n",student_income);
    printf("Income from Academic Personel in a month: %d\n",academic_income);
    printf("Income from Administrative Personel in a month: %d\n",admin_income);
    printf("Total Sale in a month: %d\n", total_sale);
    }

void fill_menu_arrays(Cafeteria *cafeteria) //helper function for filling the arrays
{
    for (int i = 0; i < MONTHLENGTH+1; i++)
    {
        cafeteria->NormalMenuPTR[i] = malloc(sizeof(NormalMenu));
        cafeteria->VeganMenuPTR[i] = malloc(sizeof(VeganMenu));
        cafeteria->VegetarianMenuPTR[i] = malloc(sizeof(VegetarianMenu));
    }
}
void free_menu_arrays(Cafeteria *cafeteria) //to empty out the arrays created with malloc
{
    for (int i = 0; i < MONTHLENGTH; i++)
    {
        free(cafeteria->NormalMenuPTR[i]);
        free(cafeteria->VeganMenuPTR[i]);
        free(cafeteria->VegetarianMenuPTR[i]);
    }
}

void print_menu_contents_counts(Cafeteria *cafeteria) {
    NormalMenu *cafeteria_normal_menu_first = cafeteria->NormalMenuPTR[0];
    NormalMenu *cafeteria_normal_menu_last = cafeteria->NormalMenuPTR[22];
    VeganMenu *cafeteria_vegan_menu_first = cafeteria->VeganMenuPTR[0];
    VeganMenu *cafeteria_vegan_menu_last = cafeteria->VeganMenuPTR[22];
    VegetarianMenu *cafeteria_vegetarian_menu_first = cafeteria->VegetarianMenuPTR[0];
    VegetarianMenu *cafeteria_vegetarian_menu_last = cafeteria->VegetarianMenuPTR[22];

    printf("~~~~Normal menu for the first day and the last day of the month:\n");
    printf("Date: %s\n", cafeteria_normal_menu_first->date);
    printf("Soup: %s\n", cafeteria_normal_menu_first->soup);
    printf("Main dish: %s\n", cafeteria_normal_menu_first->main_dish);
    printf("Side dish: %s\n", cafeteria_normal_menu_first->side_dish);
    printf("Extra: %s\n", cafeteria_normal_menu_first->extra);
    
    printf("Date: %s\n", cafeteria_normal_menu_last->date);
    printf("Soup: %s\n",  cafeteria_normal_menu_last->soup);
    printf("Main dish: %s\n",  cafeteria_normal_menu_last->main_dish);
    printf("Side dish: %s\n",  cafeteria_normal_menu_last->side_dish);
    printf("Extra: %s\n",  cafeteria_normal_menu_last->extra);
    printf("\n");

    printf("~~~~Vegan menu for the first day and the last day of the month:\n");
    printf("Date: %s\n", cafeteria_vegan_menu_first->date);
    printf("Soup: %s\n", cafeteria_vegan_menu_first->soup);
    printf("Main dish: %s\n", cafeteria_vegan_menu_first->main_dish);
    printf("Side dish: %s\n", cafeteria_vegan_menu_first->side_dish);
    printf("Extra: %s\n", cafeteria_vegan_menu_first->extra);

    printf("Date: %s\n", cafeteria_vegan_menu_last->date);
    printf("Soup: %s\n", cafeteria_vegan_menu_last->soup);
    printf("Main dish: %s\n", cafeteria_vegan_menu_last->main_dish);
    printf("Side dish: %s\n", cafeteria_vegan_menu_last->side_dish);
    printf("Extra: %s\n", cafeteria_vegan_menu_last->extra);
    printf("\n");

    printf("~~~~Vegetarian menu for the first day and the last day of the month:\n");
    printf("Date: %s\n",cafeteria_vegetarian_menu_first->date);
    printf("Soup: %s\n", cafeteria_vegetarian_menu_first->soup);
    printf("Main dish: %s\n", cafeteria_vegetarian_menu_first->main_dish);
    printf("Side dish: %s\n", cafeteria_vegetarian_menu_first->side_dish);
    printf("Extra: %s\n", cafeteria_vegetarian_menu_first->extra);

    printf("Date: %s\n", cafeteria_vegetarian_menu_last->date);
    printf("Soup: %s\n", cafeteria_vegetarian_menu_last->soup);
    printf("Main dish: %s\n", cafeteria_vegetarian_menu_last->main_dish);
    printf("Side dish: %s\n", cafeteria_vegetarian_menu_last->side_dish);
    printf("Extra: %s\n", cafeteria_vegetarian_menu_last->extra);
    printf("\n");

    printf("First day Normal Menu counts---->\n");
    printf("Student count: %d\n", cafeteria_normal_menu_first->sale_count[0]);
    printf("Akademic count: %d\n", cafeteria_normal_menu_first->sale_count[1]);
    printf("Admin count: %d\n", cafeteria_normal_menu_first->sale_count[2]);
    printf("\n");

    printf("Last day Normal counts--->\n");
    printf("Student count: %d\n", cafeteria_normal_menu_last->sale_count[0]);
    printf("Akademic count: %d\n", cafeteria_normal_menu_last->sale_count[1]);
    printf("Admin count: %d\n", cafeteria_normal_menu_last->sale_count[2]);
    printf("\n");

    printf("First day Vegan counts---->\n");
    printf("Student count: %d\n", cafeteria_vegan_menu_first->sale_count[0]);
    printf("Akademic count: %d\n", cafeteria_vegan_menu_first->sale_count[1]);
    printf("Admin count: %d\n", cafeteria_vegan_menu_first->sale_count[2]);
    printf("\n");

    printf("Last day Vegan counts--->\n");
    printf("Student count: %d\n", cafeteria_vegan_menu_last->sale_count[0]);
    printf("Akademic count: %d\n", cafeteria_vegan_menu_last->sale_count[1]);
    printf("Admin count: %d\n", cafeteria_vegan_menu_last->sale_count[2]);
    printf("\n");

    printf("First day Vegan counts---->\n");
    printf("Student count: %d\n", cafeteria_vegetarian_menu_first->sale_count[0]);
    printf("Akademic count: %d\n", cafeteria_vegetarian_menu_first->sale_count[1]);
    printf("Admin count: %d\n", cafeteria_vegetarian_menu_first->sale_count[2]);
    printf("\n");

    printf("Last day Vegan counts--->\n");
    printf("Student count: %d\n", cafeteria_vegetarian_menu_last->sale_count[0]);
    printf("Akademic count: %d\n", cafeteria_vegetarian_menu_last->sale_count[1]);
    printf("Admin count: %d\n", cafeteria_vegetarian_menu_last->sale_count[2]);
    printf("\n");
}



int main()
{
    Cafeteria *cafeteria = malloc(sizeof(Cafeteria));
    fill_menu_arrays(cafeteria);
    initialize_menus(cafeteria, "cafeteria_march_menu.csv");
    record_customer_counts(cafeteria);
    print_menu_contents_counts(cafeteria);
    calc_and_show_income(cafeteria);

    free_menu_arrays(cafeteria);
    free(cafeteria);
    return (0);
}