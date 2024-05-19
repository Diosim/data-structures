// #####################################################################################################
// #####################################################################################################
//  _____       _______          _____ _______ _____  _    _  _____ _______ _    _ _____  ______  _____
// |  __ \   /\|__   __|/\      / ____|__   __|  __ \| |  | |/ ____|__   __| |  | |  __ \|  ____|/ ____|
// | |  | | /  \  | |  /  \    | (___    | |  | |__) | |  | | |       | |  | |  | | |__) | |__  | (___
// | |  | |/ /\ \ | | / /\ \    \___ \   | |  |  _  /| |  | | |       | |  | |  | |  _  /|  __|  \___ \
// | |__| / ____ \| |/ ____ \   ____) |  | |  | | \ \| |__| | |____   | |  | |__| | | \ \| |____ ____) |
// |_____/_/    \_\_/_/    \_\ |_____/   |_|  |_|  \_\\____/ \_____|  |_|   \____/|_|  \_\______|_____/
// #####################################################################################################
// Data Structures assignment
// University of Pireaus
// April 2024
//
// #####################################################################################################

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to clear the screen
// ok on linux/online compilers
// on clion windows it requires to edit projects configuration: Emulate terminal in the output console [X]
void clearScreen(){
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}

void clearInputBuffer() {
    printf("\nPress Enter to continue...");
    while (getchar() != '\n'); // Clear input buffer
    getchar(); // Wait for Enter key
}

// ####################################################################################
// ############################## EXERCISE 1 START ####################################
// ############************************************************************############

// Function to retrieve the value at a given index from a matrix
float retrieve(float *matrix, int index) {
    return matrix[index];
}

// Function to update the value at a given index in a matrix
void update(float *matrix, int index, float value) {
    matrix[index] = value;
}

// Function to add two matrices B and C and store the result in matrix a
void add_matrices(float *B, float *C, float *a, int size) {
    for (int i = 0; i < size; i++) {
        a[i] = B[i] + C[i];
    }
}

// Function to demonstrate matrix operations
void matrix_operations() {
    // Assuming B, C, and a are arrays containing real numbers
    float B[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    float C[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    float a[10];

    // Retrieve values from B and C matrices
    float B_val = retrieve(B, 5);  // Get value from matrix B at index 5
    float C_val = retrieve(C, 5);  // Get value from matrix C at index 5
    printf("Values retrieved from matrices B and C: %.2f %.2f\n", B_val, C_val);

    // Update values in matrices B and C
    update(B, 5, 20);  // Update value in matrix B at index 5
    update(C, 5, 30);  // Update value in matrix C at index 5
    printf("Updated matrices B and C:\n");
    for (int i = 0; i < 10; i++) {
        printf("%.2f ", B[i]);
    }
    printf("\n");
    for (int i = 0; i < 10; i++) {
        printf("%.2f ", C[i]);
    }
    printf("\n");

    // Add matrices B and C to obtain matrix a
    add_matrices(B, C, a, 10);
    printf("Resultant matrix a:\n");
    for (int i = 0; i < 10; i++) {
        printf("%.2f ", a[i]);
    }
    printf("\n");
}
// ############************************************************************############
// ############################### EXERCISE 1 END #####################################
// ####################################################################################


// ####################################################################################
// ############################## EXERCISE 2 START ####################################
// ############************************************************************############


// ############************************************************************############
// ############################### EXERCISE 2 END #####################################
// ####################################################################################


// ####################################################################################
// ############################### EXERCISE 3 START ###################################
// ############************************************************************############
// to do:
// - Test changing scanf() with fgets(), to properly handle spaces in user input
// - Find out how to input space " " characters (i.e. name, address)
// - Fix code for VScode erros with buffer overflow on addCourse addStudent

struct studentCourseLink {
    struct student *student;
    struct studentCourseLink *next;
};

struct course {
    char courseName[30];
    struct course *next;
    struct studentCourseLink *studentsHead; // New field
};

struct student {
    int am;
    char firstName[30];
    char lastName[30];
    char patronym[30];
    char matronym[30];
    char address[30];
    int phoneNumber;
    int mobileNumber;
    struct student *next;
    struct course *enrolledCourse; // Directly link to the single course
};

struct student *head;
struct course* courseHead = NULL;

// ############################## COURSE MANAGEMENT - START ################################
struct course* createCourse(const char *courseName) {
    struct course* newCourse = (struct course*) malloc(sizeof(struct course));
    strcpy(newCourse->courseName, courseName);
    newCourse->next = NULL;
    newCourse->studentsHead = NULL; // Initialize the list of students enrolled in the course
    return newCourse;
}
struct course* findOrCreateCourse(const char *courseName) {
    struct course* currentCourse = courseHead; // Assume courseHead is a global pointer to the first course
    struct course* lastCourse = NULL;
    while (currentCourse != NULL) {
        if (strcmp(currentCourse->courseName, courseName) == 0) {
            return currentCourse;
        }
        lastCourse = currentCourse;
        currentCourse = currentCourse->next;
    }

    // Course not found, create new
    struct course* newCourse = createCourse(courseName);
    if (lastCourse != NULL) {
        lastCourse->next = newCourse;
    } else {
        courseHead = newCourse; // Set as head if first course
    }
    return newCourse;
}

void addCourse(struct student* student, const char *courseName) {
    struct course* course = findOrCreateCourse(courseName);
    student->enrolledCourse = course; // Directly link student to this course
}
// ############################## COURSE MANAGEMENT - END ################################

// ############################# STUDENT MANAGEMENT - START ###############################
void addStudent(int am, const char *firstName, const char *lastName, const char *patronym, const char *matronym, const char *address, int phoneNumber, int mobileNumber, const char *courseName) {
    struct student *pts;
    pts = (struct student*) malloc(sizeof(struct student));
    if (pts == NULL) {
        // Handle memory allocation failure
        printf("Memory allocation failed\n");
        return;
    }
    pts->am = am;
    strcpy(pts->firstName, firstName);
    strcpy(pts->lastName, lastName);
    strcpy(pts->patronym, patronym);
    strcpy(pts->matronym, matronym);
    strcpy(pts->address, address);
    pts->phoneNumber = phoneNumber;
    pts->mobileNumber = mobileNumber;
    pts->enrolledCourse = NULL; // Initialize the enrolledCourse pointer to NULL

    // Now add the course to the student
    // This will set the enrolledCourse pointer to the appropriate course
    addCourse(pts, courseName);

    if(head == NULL){
        pts->next = NULL;
        head = pts;
    } else{
        pts->next = head;
        head = pts;
    }
}

void displayAllStudents() {
    clearScreen();
    struct student *temp = head;

    printf("Student directory:\n");

    if (temp == NULL) {
        printf("List is empty...\n");
        clearInputBuffer();
        return;
    }
    while (temp != NULL) {
        printf("Student: AM: %d, Name: %s %s, Patronym: %s, Matronym: %s, Address: %s, Phone Number: %d, Mobile Number: %d, Course: %s\n",
               temp->am, temp->firstName, temp->lastName, temp->patronym, temp->matronym, temp->address, temp->phoneNumber, temp->mobileNumber,
               temp->enrolledCourse ? temp->enrolledCourse->courseName : "Not enrolled in any course");
        temp = temp->next;
    }
    clearInputBuffer();
}

void displayStudentsByCourse() {
    clearScreen();

    printf("UNIPI - Data Structures  23-24\n");

    char courseName[30];
    printf("Enter course name to display students: ");
    scanf("%s", courseName);
    //scanf("%29s", courseName); // Suggestion to use %29s to prevent buffer overflow

    int found = 0;
    struct student *temp = head;
    printf("Students enrolled in course %s:\n", courseName);
    while (temp != NULL) {
        if (temp->enrolledCourse != NULL && strcmp(temp->enrolledCourse->courseName, courseName) == 0) {
            printf("StudentID: %d, Name: %s %s, Patronym: %s, Matronym: %s, Address: %s, Phone Number: %d, Mobile Number: %d\n",
                   temp->am, temp->firstName, temp->lastName, temp->patronym, temp->matronym, temp->address, temp->phoneNumber, temp->mobileNumber);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("No students found for course: %s\n", courseName);
    }
    clearInputBuffer();
}

void handleaddStudent() {
    clearScreen();
    int am, phoneNumber, mobileNumber;
    char firstName[30], lastName[30], patronym[30], matronym[30], address[30], courseName[30];
    printf("UNIPI - Data Structures  23-24\n");
    printf("Add student data below:\n");
    printf("Enter am: ");
    scanf("%d", &am);
    printf("Enter first name: ");
    scanf("%s", firstName);
    printf("Enter last name: ");
    scanf("%s", lastName);
    printf("Enter patronym: ");
    scanf("%s", patronym);
    printf("Enter matronym: ");
    scanf("%s", matronym);
    printf("Enter address: ");
    scanf("%s", address);
    printf("Enter phone number: ");
    scanf("%d", &phoneNumber);
    printf("Enter mobile number: ");
    scanf("%d", &mobileNumber);
    printf("Enter course name: ");
    scanf("%s", courseName);
    addStudent(am, firstName, lastName, patronym, matronym, address, phoneNumber, mobileNumber, courseName);
}

void studentExamplePreloader() {
    // Import sample students for exercise 3 - START
    addStudent(1, "Diogenis", "Papadopoulos", "Marios", "Maria", "Aristotelous25", 21012344, 69696969, "data");
    addStudent(2, "Ioannis", "Efstratiou", "Kostas", "Kaiti", "panormou1", 24101223, 69696969, "math");
    addStudent(3, "Orestis", "Giannou", "Marios", "Maria", "epaminonda", 21012344, 69696969, "data");
    addStudent(4, "Nopi", "Afroxilanthou", "Takis", "Efterpi", "kekropos2", 241012323, 69696969, "math");
    addStudent(5, "Ian", "Afroxilanthou", "Sakis", "Jane", "anaximandrou5", 241012323, 69696969, "physics");
    addStudent(6, "Sandra", "Panagiotou", "Lakis", "Mary", "kekropos2", 241012323, 69696969, "network");
    addStudent(7, "Ifigenia", "Yates", "John", "Emily", "kekropos2", 241012323, 69696969, "network");
    addStudent(8, "Stavros", "Yates", "Jack", "Emily", "kekropos2", 241012323, 69696969, "network");
    printf("Student directory sample is loaded.\n");
    clearInputBuffer();
    // Import sample students for exercise 3 - END
}
// ############################ STUDENT MANAGEMENT - END ##############################

// ############************************************************************############
// ############################### EXERCISE 3 END #####################################
// ####################################################################################

// ####################################################################################
// ############################## EXERCISE 4 START ####################################
// ############************************************************************############
#define MAX 10 // for exerise 4

void push(int stack[], int *top, int value) {
    if (*top < MAX) {
        *top = *top + 1;
        stack[*top] = value;
        printf("%d pushed to stack\n", value);
    } else {
        printf("The stack is full\n");
        exit(EXIT_FAILURE);
    }
}

int pop(int stack[], int *top) {
    if (*top >= 0) {
        int value = stack[*top];
        *top = *top - 1;
        return value;
    } else {
        printf("The stack is empty\n");
        exit(EXIT_FAILURE);
    }
}

void performLIFOStackOperations() {
    int stack[MAX];
    int top = -1;
    int num;

    printf("Enter numbers to push onto the stack (enter -1 to stop):\n");

    do {
        printf("Enter number: ");
        scanf("%d", &num);
        if (num != -1)
            push(stack, &top, num);
    } while (num != -1);

    if (top >= 0) {
        int value = pop(stack, &top);
        printf("Popped value: %d\n", value);
    } else {
        printf("The stack is empty\n");
    }
}
// ############************************************************************############
// ############################### EXERCISE 4 END #####################################
// ####################################################################################


// ####################################################################################
// ############################## EXERCISE 5 START ####################################
// ############************************************************************############
typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void pushNode(Node** top_ref, int new_data) {
    Node* new_node = newNode(new_data);
    new_node->next = *top_ref;
    *top_ref = new_node;
    //printf("%d pushed to stack\n", new_data);
}

int popNode(Node** top_ref) {
    if (*top_ref == NULL) {
        printf("The stack is empty\n");
        exit(EXIT_FAILURE);
    }
    Node* temp = *top_ref;
    *top_ref = (*top_ref)->next;
    int popped = temp->data;
    free(temp);
    return popped;
}

void performLIFOlinkedStackOperations() {
    Node* top = NULL;
    int data;

    printf("Enter numbers to push onto the stack (enter -1 to stop): \n");
    while (1) {
        printf("Enter number: ");
        scanf("%d", &data);
        if (data == -1) break; // Stop if the user enters -1
        pushNode(&top, data);
    }

    printf("Popping all elements from the stack:\n");
    while (top != NULL) {
        printf("%d ", popNode(&top));
    }
}
// ############************************************************************############
// ############################### EXERCISE 5 END #####################################
// ####################################################################################

// ####################################################################################
// ############################## EXERCISE 6 START ####################################
// ############************************************************************############
// Function to evaluate the expression [(10+2) x (8-3)] + 2

typedef struct {
    int *data;
    int top;
    int capacity;
} Stack;

// Stack initialization
Stack* createStack(int capacity) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    stack->capacity = capacity;
    stack->top = -1;
    stack->data = (int *)malloc(capacity * sizeof(int));
    if (stack->data == NULL) {
        printf("Memory allocation failed\n");
        free(stack);
        exit(1);
    }
    return stack;
}

// Function to push an element onto the stack
void pushStack(Stack *stack, int value) {
    if (stack->top == stack->capacity - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->data[++stack->top] = value;
    printf("Pushed %d, Stack: ", value);
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->data[i]);
    }
    printf("\n");
}

// Function to pop an element from the stack
int popStack(Stack *stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        return -1;
    }
    int value = stack->data[stack->top--];
    printf("Popped %d, Stack: ", value);
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->data[i]);
    }
    printf("\n");
    return value;
}

void evaluateExpression() {
    Stack *stack = createStack(10);

    pushStack(stack, 10);
    pushStack(stack, 2);
    int val2 = popStack(stack);
    int val1 = popStack(stack);
    int result1 = val1 + val2;
    pushStack(stack, result1);

    pushStack(stack, 8);
    pushStack(stack, 3);
    val2 = popStack(stack);
    val1 = popStack(stack);
    int result2 = val1 - val2;
    pushStack(stack, result2);

    val2 = popStack(stack);
    val1 = popStack(stack);
    int result3 = val1 * val2;
    pushStack(stack, result3);

    pushStack(stack, 2);
    val2 = popStack(stack);
    val1 = popStack(stack);
    int finalResult = val1 + val2;
    pushStack(stack, finalResult);

    // Print final result
    printf("Final result: %d\n", popStack(stack));
}

// ############************************************************************############
// ############################### EXERCISE 6 END #####################################
// ####################################################################################



// ####################################################################################
// ################################# MENU START #######################################
// ############************************************************************############
void menuHeader(int exercise){
    printf("UNIPI - Data Structures  23-24\n");
    if (exercise == 1) {
        printf("Matrix Operations:\n");
    } else if (exercise == 2) {
        printf("Exercise 2 dummy placeholder\n");
    } else if (exercise == 3) {
        printf("Student directory management options:\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Display Students by Course\n");
        printf("4. Preload sample student data\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
    } else if (exercise == 4) {
        printf("Exercise 4 LIFO stack \n");
    } else if (exercise == 5) {
        printf("Exercise 5 LIFO linked list stack \n");
    } else if (exercise == 6) {
        printf("Exercise 6 dummy placeholder \n");
    }
}

void handleMenuChoice(int choice) {
    clearScreen();
    switch (choice) {
        case 1:
            clearScreen();
            menuHeader(1);
            matrix_operations();
            clearInputBuffer();
            break;
        case 2:
            clearScreen();
            menuHeader(2);
            clearInputBuffer();
            break;
        case 3:
            while (1) {
                int subChoice;
                clearScreen();
                menuHeader(3);
                scanf("%d", &subChoice);
                switch (subChoice) {
                    case 1:
                        handleaddStudent();
                        break;
                    case 2:
                        displayAllStudents();
                        break;
                    case 3:
                        displayStudentsByCourse();
                        break;
                    case 4:
                        studentExamplePreloader();
                        break;
                    case 5:
                        return;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
            }
        case 4:
            clearScreen();
            menuHeader(4);
            performLIFOStackOperations();
            clearInputBuffer();
            break;
        case 5:
            clearScreen();
            menuHeader(5);

            performLIFOlinkedStackOperations();
            clearInputBuffer();
            break;
        case 6:
            clearScreen();
            menuHeader(6);
            evaluateExpression();
            clearInputBuffer();
            break;
        case 7:
            clearScreen();
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
    }
}

int getMenuChoice() {
    clearScreen();
    int choice;
    printf("UNIPI - Data Structures  23-24\n");
    printf("Exercise directory \n");
    printf("1. Exercise 1 - Matrix Operations\n");
    printf("2. Exercise 2 - ------------------\n");
    printf("3. Exercise 3 - Student Directory\n");
    printf("4. Exercise 4 - LIFO stack (simple)\n");
    printf("5. Exercise 5 - LIFO stack (linked lists)\n");
    printf("6. Exercise 6 - Expression evaluation\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
    clearInputBuffer();
}
// ############************************************************************############
// ################################## MENU END ########################################
// ####################################################################################

int main() {

    //int choice;
    while (1){
        //choice = getMenuChoice();
        //handleMenuChoice(choice);
        handleMenuChoice(getMenuChoice());
    }
    return 0;
}
