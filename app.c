#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char STORE_PATH[256] = "store";

// Checks if the store is empty
int is_empty() {
  FILE *fp;
  char key[255];
  char value[255];
  fp = fopen(STORE_PATH, "r");
  int empty = 1;
  while (fscanf(fp, "%s %s", key, value) != EOF) {
    empty = 0;
  }
  fclose(fp);
  return empty;
}

// Checks if store contains specified key
int contains_key(char searched_key[255]) {
  FILE *fp;
  char key[255];
  char value[255];
  fp = fopen(STORE_PATH, "r");
  int contains = 0;
  while (fscanf(fp, "%s %s", key, value) != EOF) {
    if (strcmp(searched_key, key) == 0)
      contains = 1;
  }
  fclose(fp);
  return contains;
}

// Prints all key value pairs from "store" file
void print_records() {
  FILE *fp;
  char key[255];
  char value[255];
  fp = fopen(STORE_PATH, "r");
  while (fscanf(fp, "%s %s", key, value) != EOF) {
    printf("Key: %s, Value: %s\n", key, value);
  }
  fclose(fp);
}

// Adds new key value pair to "store" file
void add_record() {
  FILE *fp;
  char key[255];
  char value[255];
  printf("Key: ");
  scanf("%s", key);
  printf("Value: ");
  scanf("%s", value);
  fp = fopen(STORE_PATH, "a+");
  fprintf(fp, "%s %s\n", key, value);
  fclose(fp);
}

// Deletes chosen record
void delete_record() {
  char keyToDel[255];
  printf("Choose key to delete:\n");
  print_records();
  scanf("%s", keyToDel);
  if (contains_key(keyToDel)) {
    FILE *fp;
    char key[255];
    char value[255];
    int rows = 0;
    fp = fopen(STORE_PATH, "r");
    // count rows in file
    while (fscanf(fp, "%s %s", key, value) != EOF) {
      rows++;
    }
    fclose(fp);
    // allocate memory for number of rows - 1
    char **keys = calloc(rows - 1, sizeof(char *));
    // allocate memory for string in each row
    for (int i = 0; i < rows - 1; i++) {
      keys[i] = calloc(1, sizeof(char) * 255);
    }
    // allocate memory for number of rows - 1
    char **values = calloc(rows - 1, sizeof(char *));
    // allocate memory for string in each row
    for (int i = 0; i < rows - 1; i++) {
      values[i] = calloc(1, sizeof(char) * 255);
    }
    fp = fopen(STORE_PATH, "r");
    int i = 0;
    // copy old key-value pair to allocated memory if not equal to "keyToDel"
    while (fscanf(fp, "%s %s", key, value) != EOF) {
      if (strcmp(key, keyToDel) != 0) {
        strcpy(keys[i], key);
        strcpy(values[i], value);
        i++;
      }
    }
    fclose(fp);
    fp = fopen(STORE_PATH, "w");
    // write all key value pairs to file
    for (int i = 0; i < rows - 1; i++) {
      fprintf(fp, "%s %s\n", keys[i], values[i]);
    }
    fclose(fp);
  }
}

// Edits value of the chosen record
void edit_record() {
  char keyToEdit[255];
  char newValue[255];
  printf("Choose key to edit:\n");
  print_records();
  scanf("%s", keyToEdit);
  printf("Input new value:\n");
  scanf("%s", newValue);
  if (contains_key(keyToEdit)) {
    FILE *fp;
    char key[255];
    char value[255];
    int rows = 0;
    fp = fopen(STORE_PATH, "r");
    // count rows in file
    while (fscanf(fp, "%s %s", key, value) != EOF) {
      rows++;
    }
    fclose(fp);
    // allocate memory for number of rows
    char **keys = calloc(rows, sizeof(char *));
    // allocate memory for string in each row
    for (int i = 0; i < rows; i++) {
      keys[i] = calloc(1, sizeof(char) * 255);
    }
    // allocate memory for number of rows
    char **values = calloc(rows, sizeof(char *));
    // allocate memory for string in each row
    for (int i = 0; i < rows; i++) {
      values[i] = calloc(1, sizeof(char) * 255);
    }
    fp = fopen(STORE_PATH, "r");
    int i = 0;
    // copy old key value pairs, if key equal to keyToEdit, copy edited pair
    while (fscanf(fp, "%s %s", key, value) != EOF) {
      strcpy(keys[i], key);
      if (strcmp(key, keyToEdit) == 0) {
        strcpy(values[i], newValue);
      } else {
        strcpy(values[i], value);
      }
      i++;
    }
    fclose(fp);
    fp = fopen(STORE_PATH, "w");
    // write new pairs to file
    for (int i = 0; i < rows; i++) {
      fprintf(fp, "%s %s\n", keys[i], values[i]);
    }
    fclose(fp);
  }
}

// Deletes all recors
void delete_all() {
  FILE *fp;
  fp = fopen(STORE_PATH, "w");
  fclose(fp);
}

// Main menu
void menu() {
  system("clear");
  printf("Welcome to your secure key value store.\n");
  int choice = 0;
  while (1) {
    if (!is_empty()) {
      printf("Available actions:\n");
      printf("[1] Add new record\n");
      printf("[2] Delete record\n");
      printf("[3] Edit record\n");
      printf("[4] Show all records\n");
      printf("[5] Delete all records\n");
      printf("[6] Quit\n");
    } else {
      printf("Available actions: (Store is empty)\n");
      printf("[1] Add new record\n");
      printf("[2] Quit\n");
    }
    scanf("%d", &choice);
    if (is_empty()) {
      switch (choice) {
      case 1:
        add_record();
        break;
      default:
        exit(EXIT_SUCCESS);
        break;
      }
    } else {
      switch (choice) {
      case 1:
        add_record();
        break;
      case 2:
        delete_record();
        break;
      case 3:
        edit_record();
        break;
      case 4:
        print_records();
        break;
      case 5:
        delete_all();
        break;
      default:
        exit(EXIT_SUCCESS);
      }
    }
  }
}

// Admin mode aka buffer overflow exploit
void admin() {
  int choice = 0;
  char edit_cmd[256];
  printf("Welcome to admin mode:\n");
  while (1) {
    choice = 0;
    printf("Available actions:\n");
    printf("[1] Open store in editor\n");
    printf("[2] Change store path\n");
    printf("[3] Print store path\n");
    printf("[4] Exit\n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      strcpy(edit_cmd, "sudo python scripts/syntaxchecker.py ");
      strcat(edit_cmd, STORE_PATH);
      system(edit_cmd);
      break;
    case 2:
      printf("Input new path: ");
      scanf("%s", STORE_PATH);
      break;
    case 3:
      printf("Store path: %s\n", STORE_PATH);
      break;
    default:
      exit(EXIT_SUCCESS);
    }
  }
}

// Login "menu"
int login() {
  char pass[256];
  char ctrl[] = "ibe";
  printf("Enter your password: ");
  scanf("%s", pass);
  return strcmp(pass, ctrl) == 0;
}

int main(int argc, char *argv[]) {
  int admin_mode = 0;
  char admin_input[10];
  char admin_pass[] = "admin";

  if (argc > 1) {
    strcpy(admin_input, argv[1]);
  }
  if (admin_mode) {
    admin();
  } else {
    if (login())
      menu();
  }
}
