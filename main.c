#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

PROGRAM: Inventory Management System (Final Project)

Features:
1. Add Product
2. View Products
3. Search Product
4. Delete Product
5. Update Product
6. Count Products
7. Clear All Records

File: inventory.dat

*/

struct Product {
    char name[50];
    int quantity;
};


/*
CHECK DUPLICATE PRODUCT
*/

int is_duplicate(char name[])
{
    FILE *fp = fopen("inventory.dat", "rb");
    if (fp == NULL) return 0;

    struct Product p;

    while (fread(&p, sizeof(p), 1, fp) == 1)
    {
        if (strcmp(p.name, name) == 0)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

/*
ADD PRODUCT
*/

void add_product()
{
    FILE *fp = fopen("inventory.dat", "ab");

    if (fp == NULL) {
        printf("File error\n");
        return;
    }

    struct Product p;

    printf("Enter Product Name: ");
    scanf(" %[^\n]", p.name);

    if (is_duplicate(p.name))
    {
        printf("Product already exists!\n");
        fclose(fp);
        return;
    }

    printf("Enter Quantity: ");
    if (scanf("%d", &p.quantity) != 1 || p.quantity < 0)
    {
        printf("Invalid quantity\n");
        fclose(fp);
        return;
    }

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);

    printf("Product added successfully\n");
}

/*
VIEW PRODUCTS
*/

void view_products()
{
    FILE *fp = fopen("inventory.dat", "rb");

    if (fp == NULL) {
        printf("No records found\n");
        return;
    }

    struct Product p;

    printf("\n--- Inventory ---\n");

    while (fread(&p, sizeof(p), 1, fp) == 1)
    {
        printf("Product: %-20s Quantity: %d\n", p.name, p.quantity);
    }

    fclose(fp);
}

/*
SEARCH PRODUCT
*/

void search_product()
{
    FILE *fp = fopen("inventory.dat", "rb");

    if (fp == NULL) {
        printf("File not found\n");
        return;
    }

    char name[50];
    int found = 0;

    printf("Enter product name: ");
    scanf(" %[^\n]", name);

    struct Product p;

    while (fread(&p, sizeof(p), 1, fp) == 1)
    {
        if (strcmp(p.name, name) == 0)
        {
            printf("Found: %s | Quantity: %d\n", p.name, p.quantity);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Product not found\n");

    fclose(fp);
}

/*
DELETE PRODUCT
*/

void delete_product()
{
    FILE *fp = fopen("inventory.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("File error\n");
        return;
    }

    char name[50];
    int found = 0;

    printf("Enter product to delete: ");
    scanf(" %[^\n]", name);

    struct Product p;

    while (fread(&p, sizeof(p), 1, fp) == 1)
    {
        if (strcmp(p.name, name) != 0)
        {
            fwrite(&p, sizeof(p), 1, temp);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("inventory.dat");
    rename("temp.dat", "inventory.dat");

    if (found)
        printf("Product deleted\n");
    else
        printf("Product not found\n");
}

/*
UPDATE PRODUCT
*/

void update_product()
{
    FILE *fp = fopen("inventory.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("File error\n");
        return;
    }

    char name[50];
    int found = 0;

    printf("Enter product to update: ");
    scanf(" %[^\n]", name);

    struct Product p;

    while (fread(&p, sizeof(p), 1, fp) == 1)
    {
        if (strcmp(p.name, name) == 0)
        {
            printf("Enter new quantity: ");
            scanf("%d", &p.quantity);
            found = 1;
        }

        fwrite(&p, sizeof(p), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("inventory.dat");
    rename("temp.dat", "inventory.dat");

    if (found)
        printf("Product updated\n");
    else
        printf("Product not found\n");
}

/*
COUNT PRODUCTS
*/

void count_products()
{
    FILE *fp = fopen("inventory.dat", "rb");

    if (fp == NULL) {
        printf("No records found\n");
        return;
    }

    int count = 0;
    struct Product p;

    while (fread(&p, sizeof(p), 1, fp) == 1)
    {
        count++;
    }

    printf("Total products: %d\n", count);

    fclose(fp);
}

/*
CLEAR ALL RECORDS
*/

void clear_all()
{
    char confirm;

    printf("Are you sure you want to delete ALL records? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y')
    {
        remove("inventory.dat");
        printf("All records cleared\n");
    }
    else
    {
        printf("Operation cancelled\n");
    }
}

/*
MAIN MENU
*/

int main()
{
    int choice;

    while (1)
    {
        printf("\n========== INVENTORY SYSTEM ==========\n");
        printf("1. Add Product\n");
        printf("2. View Products\n");
        printf("3. Search Product\n");
        printf("4. Delete Product\n");
        printf("5. Update Product\n");
        printf("6. Count Products\n");
        printf("7. Clear All Records\n");
        printf("8. Exit\n");

        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input\n");
            return 1;
        }

        switch (choice)
        {
            case 1: add_product(); break;
            case 2: view_products(); break;
            case 3: search_product(); break;
            case 4: delete_product(); break;
            case 5: update_product(); break;
            case 6: count_products(); break;
            case 7: clear_all(); break;
            case 8: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice\n");
        }
    }
}
