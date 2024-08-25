#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#define saleOff 0.2

int orders = 0, login, logout;

/*******************************************/
// Define struct

struct FOOD{
    int ID;
    char name[100];
    double price;
    double amount;
    double total;
};

typedef struct FOOD *Food;

struct MENU{
    int count;
    int max_size;
    Food list;
    double discount; // Discount amount
    double subtotal; // Total before discount
    double payment;  // Total after discount
};

typedef struct MENU *Menu;

/*******************************************/
// Create a menu

Menu createMenu(int max_size) {
    Menu mn = malloc(sizeof(struct MENU));
    mn->count = 0;
    mn->max_size = max_size;
    mn->list = malloc(max_size * sizeof(struct FOOD));
    mn->discount = 0;
    mn->subtotal = 0;
    mn->payment = mn->subtotal - mn->discount;
    return mn;
}

/*******************************************/
// Create a food item

Food createFood(int ID, char name[100], double price, double amount) {
    Food food = malloc(sizeof(struct FOOD));
    food->ID = ID;
    strcpy(food->name, name);
    food->amount = amount;
    food->price = price;
    food->total = food->amount * food->price;
    return food;
}

/*******************************************/
// Add food to menu

void addFoodToMenu(Menu mn, Food f, int p) {
    int current = mn->count;
    if(current == mn->max_size || p > current) return;
    for(int i = 0; i < current; i++){
        if(mn->list[i].ID == f->ID){
            mn->list[i].amount += f->amount;
            mn->list[i].total = mn->list[i].amount * mn->list[i].price;
            mn->payment += f->price * f->amount;
            return;
        }
    }
    while(p != current) {
        mn->list[current] = mn->list[current - 1];
        current--;
    }
    mn->list[current] = *f;
    mn->payment += f->price * f->amount;
    mn->count++;
}

/*******************************************/
// Delete food from menu

void deleteFoodOutMenu(Menu mn, int p) {
    mn->payment -= mn->list[p].total;
    for (int i = p; i < mn->count - 1; i++) {
        mn->list[i] = mn->list[i + 1];
    }
    mn->count--;
}

/*******************************************/
// Print menu

void printMenu(Menu mn, int option) {
    if(option == 1){
    	TextColor(3);
        printf("\n\t\t\t\t\t\t    MENU TIEM BANH NGOT\n\n");
        TextColor(9);
        printf("\t\t\t%c", 201);
        for (int i = 0; i <= 70; i++)
            printf("%c", 205);
        printf("%c\n\n", 187);
        TextColor(3);
        printf("\t\t\t\t\t   MON \t\t\t\t    GIA TIEN(vnd)\n\n");
        for (int i = 0; i < mn->count; i++)
            printf("\t\t\t\t %-3d: %-30s\t\t%-10.0f\n", mn->list[i].ID, mn->list[i].name, mn->list[i].price);
        TextColor(9);
        printf("\n\t\t\t%c", 200);
        for (int i = 0; i <= 70; i++)
            printf("%c", 205);
        printf("%c\n", 188);
    } 
	else if(option == 2){
        printf("STT|\t\t FOOD NAME \t\t|\tQuantity\t\n");
		for (int i = 0; i < mn->count; i++)
            printf("%-d  |\t%-30s  |\t%-8.1f\t\n", i + 1, mn->list[i].name, mn->list[i].amount);
    } 
	else if(option == 3){
        printf("\n%c", 201);
        for (int i = 0; i <= 90; i++)
            printf("%c", 205);
        printf("%c", 187);
        printf("\n   \t    FOOD NAME   \t  |\tPrice\t|\tQuantity\t|\tTotal\t\n");
        for (int i = 0; i < mn->count; i++)
            printf("  %-30s  |\t%.0f\t|\t%-8.1f\t|\t%-10.1f\n", mn->list[i].name, mn->list[i].price, mn->list[i].amount, mn->list[i].total);
        printf("%c", 200);
        for (int i = 0; i <= 90; i++)
            printf("%c", 205);
        printf("%c\n", 188);
    }
}


/*******************************************/
// Calculate payment

void payment(Menu mn) {
    printf("Invoice\n");
    printf("Invoice No. %d\n", orders);
    printf("Date: ");
    today();
    printMenu(mn, 3);
    printf("\t\t\t\t\t\t\t\t\tSubtotal: %7.0f VND\n", mn->payment);
    if (mn->payment >= 2000000) mn->discount = saleOff * mn->payment;
    printf("\t\t\t\t\t\t\t\t\tDiscount: %7.0f VND\n", mn->discount);
    printf("\t\t\t\t\t\t\t\t\tPayment : %7.0f VND\n", mn->payment - mn->discount);
}

/*******************************************/
// Change selected dishes

void change(Menu foodList, Menu order) {
	printf("%c", 201);
	for(int i = 0; i <= 23; i++)
        printf("%c", 205);
    printf("%c\n", 187);
    printf("   1. Change the amount.");
    printf("\n   2. Delete the food");
    printf("\n   3. Add dishes.\n");
    printf("%c", 200);
        for(int i = 0; i <= 23; i++)
    printf("%c", 205);
    printf("%c\n", 188);
    int choice;
    printf("\nYour Select:");
    scanf("%d", &choice);
    //printf("\n");
    switch (choice) {
    case 1: {
        // Change amount
        printf("Enter the dish you want to change (ID - amount): ");
        int select, num;
        scanf("%d", &select);
        scanf("%d", &num);
        sleep(3);
        if (select >= 1 && select <= order->count && num > 0) { // Check if selection is valid
        	order->payment += order->list[select - 1].price * (num - order->list[select - 1].amount);
            order->list[select - 1].amount = num;
            order->list[select - 1].total = order->list[select - 1].amount * order->list[select - 1].price;
            printf("\nDish changed successfully.\n\n");
        } 
		else if(num > 0){
            printf("\n\nInvalid dish selection!\n\n");
        }
        else{
        	printf("\nInvalid amount!\n\n");
		}
        break;
    }
    case 2: {
        // Cancel the food
        printf("Enter the dish you want to cancel: ");
        int cancel_select;
        scanf("%d", &cancel_select);
        sleep(3);
        if (cancel_select >= 1 && cancel_select <= order->count) { // Check if the selected dish index is valid
            deleteFoodOutMenu(order, cancel_select - 1);
            printf("\nDish canceled successfully.\n\n");
        } else {
            printf("\nInvalid dish selection!\n\n");
        }
        break;
    }
    case 3: {
        // Add dishes
        if (order->count == order->max_size) {
            printf("\nThe list has reached its limit!\n\n");
            break;
        }
        sleep(3);
        selectFood(foodList, order); // Add the selected dishes to the menu
        printf("\nDishes added successfully.\n\n");
        break;
    }
    default:
        printf("\nInvalid choice!\n\n");
    }
}
/*******************************************/
// Read menu from file

void readMenu(Menu list) {
    char line[150];
    FILE *file = fopen("./input/menu.dat", "r");
    if (file == NULL) {
        printf("Cannot open file menu.dat!\n");
        return;
    }
    while (fgets(line, sizeof(line), file) != NULL) {
        int ID;
        char name[100];
        double price;
        sscanf(line, "%d. %99[^0-9] %lf", &ID, name, &price);
        Food f = createFood(ID, name, price, 0);
        addFoodToMenu(list, f, list->count);
        free(f);
    }
    fclose(file);
}

/*******************************************/
// Select food

void selectFood(Menu foodList, Menu order){
    int i;
    printMenu(foodList, 1);
    TextColor(11);
    printf("\n");
    printf("%c\t%c\n",213, 184);
    printf(" Order %d \n", orders);
    printf("%c\t%c\n",212, 190);
    TextColor(7);
    printf("\n");
    printf("Enter your orders (ID - amount): ");
    do {
        int choice;
        i = order->count;
        double amount;
        scanf("%d", &choice);
        if (choice == 0) break;
        scanf("%lf", &amount);
        if (choice <= foodList->count && choice > 0 && amount > 0){
            Food f = createFood(foodList->list[choice - 1].ID,
                            foodList->list[choice - 1].name,
                            foodList->list[choice - 1].price,
                            amount);
            addFoodToMenu(order, f, i);
        	free(f);
		}
		else{
			if(amount <= 0){
				printf("%.0lf is invalid amount!\n",amount);
			}
			else{
				printf("%d is invalid ID!\n", choice);
			} 
			printf("The order (%d - %.0lf) is not accepted!\n", choice, amount);
		}        
    } while (order->count != order->max_size);
}

void printfwelcome(){
	char temp[100];
	FILE *File;
	File = fopen("./input/display.dat","r");
	if(File == NULL){
		printf("Cannot open file display.dat!");
		return;
	}
	while (fgets(temp, sizeof(temp), File) != NULL) {
        printf("%s",temp);
    }
    fclose(File);
}
void TextColor(int x)//X là mã màu
{
     HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}

/*******************************************/
// Login


void signin() {
    FILE *file = fopen("./input/user.dat", "r");
    if (file == NULL) {
        printf("Cannot open file user.dat\n");
        return;
    }
    int userId;
    int check = 1;
    TextColor(3);
    printf("***************************************************\n");
    printf("*                                                 *\n");
    printf("*                   LOGIN TO SYSTEM               *\n");
    printf("*                                                 *\n");
    printf("***************************************************\n");
    sleep(3);
    TextColor(7);
	do {
        printf("\nEnter your number: ");
        scanf("%d", &login);
        rewind(file); // Move file pointer to the beginning
        while (fscanf(file, "%9d", &userId) != EOF) {
            if (login == userId) {
                check = 0;
                break;
            }
        }
        if (check != 0)
        	printf("Invalid user ID. Please try again.\n");
    } while (check);
    sleep(3);
    printf("Login successful...\n");
    sleep(3);
    fclose(file);
    system("cls");
    TextColor(3);
    printfwelcome();
    sleep(3);
    printf("\ec");
    TextColor(7);
}

/*******************************************/
// Logout

void signout(){
    system("cls");
    TextColor(3);
    printf("***************************************************\n");
    printf("*                                                 *\n");
    printf("*                   LOGOUT TO SYSTEM              *\n");
    printf("*                                                 *\n");
    printf("***************************************************\n");
    sleep(3);
    TextColor(7);
    do {
        printf("Enter your number: ");
        scanf("%d", &logout);
        sleep(3);
        if(login != logout) printf("Invalid user ID! Please try again!\n");
    } while (login != logout);
    sleep(3);
    printf("Logout successful.\n");
}

/*******************************************/
// Get current date and time
void today() {
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[50];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
    printf("%s", buffer);
}
void day(char *now) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(now, 11, "%d-%m-%Y", tm_info);
}

/*******************************************/
//ham ghi du lieu vao file

void writeToFile(Menu mn) {
    char now[11];
    day(now);
    char filePath[50];
    sprintf(filePath, "./bill/%d-%s.dat", login, now);
    FILE *file = fopen(filePath, "a"); // Open file in append mode
    if (file == NULL) {
        printf("Cannot open file %s.\n", filePath);
        return;
    }
    fprintf(file, "%d:", orders);
    for (int p = 0; p < mn->count; p++) {
        fprintf(file, " %d - %0.1lf : ", mn->list[p].ID, mn->list[p].amount);
    }
    if (mn->count < mn->max_size) {
        for (int p = mn->count + 1; p < mn->max_size; p++) {
            fprintf(file, " 0 - 0 : ");
        }
    }
    fprintf(file, "%0.0f : %0.0f : %0.0lf\n", mn->payment, mn->discount, mn->payment - mn->discount);
    fclose(file);
    sleep(3);
    printf("\nOrder has been completed.\n");
}

/*******************************************/
// Main function

int main() {
    do {
        signin();
        start: orders ++;
        Menu foodList = createMenu(100);
        Menu order = createMenu(5);
        readMenu(foodList);
        selectFood(foodList, order);
        system("cls");
        char a;
        do {
            printMenu(order, 2);
            printf("Do you want to change anything? (y/n)? ");
            scanf(" %c", &a);
            if (a == 'y') change(foodList, order);
            printf("Loading...");
            sleep(3);
            printf("\ec");
        } while (a == 'y');
        system("cls");
        payment(order);
        writeToFile(order);
        free(foodList->list);
        free(foodList);
        free(order->list);
        free(order);
        printf("%c", 201);
        for(int i = 0; i <= 30; i++)
        printf("%c", 205);
    	printf("%c\n", 187);
        printf("   Press 00 to logout\n");
        printf("   Enter any number to continue\n");
        printf("%c", 200);
        for(int i = 0; i <= 30; i++)
    	printf("%c", 205);
    	printf("%c\n", 188);
        scanf("%s", &a);
        if (a == '0') {
            signout();
        } else {
            system("cls");
            goto start;
        }
    } while (login != logout);
    return 0;
}