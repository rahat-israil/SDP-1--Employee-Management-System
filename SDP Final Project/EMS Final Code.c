#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define FILE_NAME "employees.txt"

struct date {
    int day;
    int month;
    int year;
};

struct employee {
    int employee_id;
    char employee_name[50];
    char rank[50];
    float salary;
    char phone_no[20];
    struct date joining_date;
};

struct employee employees[MAX_EMPLOYEES];
int key = 0;

void add_employee();
void delete_employee(int id);
void search_employee(int id);
void update_employee(int id);
void search_name(char name[]);
void save_employees();
void load_employees();

int main() {
    int choice;
    int id;
    char name[50];

    load_employees();

    while (1) {
        printf("\n---------------------------[ Employee Management System ]--------------------------\n");
        printf("1. Add Employee\n");
        printf("2. Delete Employee\n");
        printf("3. Search Employee by ID\n");
        printf("4. Update Employee Info\n");
        printf("5. Search Employee by Name\n");
        printf("6. Save Employee Data\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_employee();
                break;
            case 2:
                printf("Enter the ID of the employee to delete: ");
                scanf("%d", &id);
                delete_employee(id);
                break;
            case 3:
                printf("Enter the ID of the employee to search: ");
                scanf("%d", &id);
                search_employee(id);
                break;
            case 4:
                printf("Enter the ID of the employee to update: ");
                scanf("%d", &id);
                update_employee(id);
                break;
            case 5:
                printf("Enter the name: ");
                getchar();
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                search_name(name);
                break;
            case 6:
                save_employees();
                break;
            case 7:
                save_employees();
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void add_employee() {
    struct employee employee;

    printf("Employee ID: ");
    scanf("%d", &employee.employee_id);

    printf("Name of the employee: ");
    getchar();
    fgets(employee.employee_name, sizeof(employee.employee_name), stdin);
    employee.employee_name[strcspn(employee.employee_name, "\n")] = '\0';

    printf("Designation of the employee: ");
    fgets(employee.rank, sizeof(employee.rank), stdin);
    employee.rank[strcspn(employee.rank, "\n")] = '\0';

    printf("Salary of the employee: ");
    scanf("%f", &employee.salary);

    printf("Phone number of the employee: ");
    getchar();
    fgets(employee.phone_no, sizeof(employee.phone_no), stdin);
    employee.phone_no[strcspn(employee.phone_no, "\n")] = '\0';

    printf("Joining date of the employee (dd-mm-yyyy): ");
    scanf("%d-%d-%d", &employee.joining_date.day,
          &employee.joining_date.month, &employee.joining_date.year);

    employees[key++] = employee;

    printf("Employee added successfully.\n");
}

void delete_employee(int id) {
    int i, j;
    int flag = 0;

    for (i = 0; i < key; i++) {
        if (employees[i].employee_id == id) {
            flag = 1;

            for (j = i; j < key - 1; j++) {
                employees[j] = employees[j + 1];
            }

            key--;
            printf("Employee with ID %d deleted successfully.\n", id);
            break;
        }
    }

    if (flag == 0) {
        printf("No employee found with ID %d.\n", id);
    }
}

void search_employee(int id) {
    int i;
    int flag = 0;

    for (i = 0; i < key; i++) {
        if (employees[i].employee_id == id) {
            printf("ID: %d\n", employees[i].employee_id);
            printf("Name: %s\n", employees[i].employee_name);
            printf("Designation: %s\n", employees[i].rank);
            printf("Salary: %.2f\n", employees[i].salary);
            printf("Phone: %s\n", employees[i].phone_no);
            printf("Joining Date: %d-%d-%d\n",
                   employees[i].joining_date.day,
                   employees[i].joining_date.month,
                   employees[i].joining_date.year);
            flag = 1;
            break;
        }
    }

    if (flag == 0) {
        printf("No employee found with ID %d.\n", id);
    }
}

void update_employee(int id) {
    int i;
    int flag = 0;

    for (i = 0; i < key; i++) {
        if (employees[i].employee_id == id) {
            printf("Employee with ID %d found. Enter the new details:\n", id);

            printf("Name of the employee: ");
            getchar();
            fgets(employees[i].employee_name, sizeof(employees[i].employee_name), stdin);
            employees[i].employee_name[strcspn(employees[i].employee_name, "\n")] = '\0';

            printf("Designation of the employee: ");
            fgets(employees[i].rank, sizeof(employees[i].rank), stdin);
            employees[i].rank[strcspn(employees[i].rank, "\n")] = '\0';

            printf("Salary of the employee: ");
            scanf("%f", &employees[i].salary);

            printf("Phone number of the employee: ");
            getchar();
            fgets(employees[i].phone_no, sizeof(employees[i].phone_no), stdin);
            employees[i].phone_no[strcspn(employees[i].phone_no, "\n")] = '\0';

            printf("Joining date of the employee (dd-mm-yyyy): ");
            scanf("%d-%d-%d", &employees[i].joining_date.day,
                  &employees[i].joining_date.month, &employees[i].joining_date.year);

            printf("Employee with ID %d updated successfully.\n", id);
            flag = 1;
            break;
        }
    }

    if (flag == 0) {
        printf("No employee found with ID %d.\n", id);
    }
}

void search_name(char name[]) {
    int i;
    int flag = 0;

    for (i = 0; i < key; i++) {
        if (strcmp(employees[i].employee_name, name) == 0) {
            printf("ID: %d\n", employees[i].employee_id);
            printf("Name: %s\n", employees[i].employee_name);
            printf("Designation: %s\n", employees[i].rank);
            printf("Salary: %.2f\n", employees[i].salary);
            printf("Phone: %s\n", employees[i].phone_no);
            printf("Joining Date: %d-%d-%d\n",
                   employees[i].joining_date.day,
                   employees[i].joining_date.month,
                   employees[i].joining_date.year);
            flag = 1;
        }
    }

    if (flag == 0) {
        printf("No employee found with name '%s'.\n", name);
    }
}

void save_employees() {
    FILE *file = fopen(FILE_NAME, "w");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%d\n", key);

    for (int i = 0; i < key; i++) {
        fprintf(file, "%d\n", employees[i].employee_id);
        fprintf(file, "%s\n", employees[i].employee_name);
        fprintf(file, "%s\n", employees[i].rank);
        fprintf(file, "%.2f\n", employees[i].salary);
        fprintf(file, "%s\n", employees[i].phone_no);
        fprintf(file, "%d-%d-%d\n", employees[i].joining_date.day,
                employees[i].joining_date.month,
                employees[i].joining_date.year);
    }

    fclose(file);

    printf("Employee data saved to file.\n");
}

void load_employees() {
    FILE *file = fopen(FILE_NAME, "r");

    if (file == NULL) {
        printf("No existing employee data found.\n");
        return;
    }

    fscanf(file, "%d\n", &key);

    for (int i = 0; i < key; i++) {
        fscanf(file, "%d\n", &employees[i].employee_id);
        fgets(employees[i].employee_name, sizeof(employees[i].employee_name), file);
        employees[i].employee_name[strcspn(employees[i].employee_name, "\n")] = '\0';
        fgets(employees[i].rank, sizeof(employees[i].rank), file);
        employees[i].rank[strcspn(employees[i].rank, "\n")] = '\0';
        fscanf(file, "%f\n", &employees[i].salary);
        fgets(employees[i].phone_no, sizeof(employees[i].phone_no), file);
        employees[i].phone_no[strcspn(employees[i].phone_no, "\n")] = '\0';
        fscanf(file, "%d-%d-%d\n", &employees[i].joining_date.day,
               &employees[i].joining_date.month,
               &employees[i].joining_date.year);
    }

    fclose(file);

    printf("Employee data loaded from file.\n");
}

