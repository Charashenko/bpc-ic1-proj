#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STORE_PATH "store"

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
    while (fscanf(fp, "%s %s", key, value) != EOF) {
      rows++;
    }
    fclose(fp);
    char **keys = calloc(rows - 1, sizeof(char *));
    for (int i = 0; i < rows - 1; i++) {
      keys[i] = calloc(
          1, sizeof(char) * 255); // Basically it is MY_STRING_LENGTH as
                                  // sizeof(char) is almost always one, but it's
                                  // there only for the readability of the code.
    }
    char **values = calloc(rows - 1, sizeof(char *));
    for (int i = 0; i < rows - 1; i++) {
      values[i] = calloc(
          1, sizeof(char) * 255); // Basically it is MY_STRING_LENGTH as
                                  // sizeof(char) is almost always one, but it's
                                  // there only for the readability of the code.
    }
    fp = fopen(STORE_PATH, "r");
    int i = 0;
    while (fscanf(fp, "%s %s", key, value) != EOF) {
      if (strcmp(key, keyToDel) != 0) {
        strcpy(keys[i], key);
        strcpy(values[i], value);
        i++;
      }
    }
    fclose(fp);
    fp = fopen(STORE_PATH, "w");
    for (int i = 0; i < rows - 1; i++) {
      fprintf(fp, "%s %s\n", keys[i], values[i]);
    }
    fclose(fp);
  }
}

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
    while (fscanf(fp, "%s %s", key, value) != EOF) {
      rows++;
    }
    fclose(fp);
    char **keys = calloc(rows, sizeof(char *));
    for (int i = 0; i < rows; i++) {
      keys[i] = calloc(
          1, sizeof(char) * 255); // Basically it is MY_STRING_LENGTH as
                                  // sizeof(char) is almost always one, but it's
                                  // there only for the readability of the code.
    }
    char **values = calloc(rows, sizeof(char *));
    for (int i = 0; i < rows; i++) {
      values[i] = calloc(
          1, sizeof(char) * 255); // Basically it is MY_STRING_LENGTH as
                                  // sizeof(char) is almost always one, but it's
                                  // there only for the readability of the code.
    }
    fp = fopen(STORE_PATH, "r");
    int i = 0;
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
    for (int i = 0; i < rows; i++) {
      fprintf(fp, "%s %s\n", keys[i], values[i]);
    }
    fclose(fp);
  }
}

void menu() {
  system("clear");
  printf("Welcome to your secure key value store.\n");
  int choice = 0;
  while (1) {
    printf("Available actions:\n");
    printf("[1] Add new record\n");
    printf("[2] Delete record\n");
    printf("[3] Edit record\n");
    printf("[4] Show all records\n");
    printf("[5] Quit\n");
    scanf("%d", &choice);
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
    default:
      exit(EXIT_SUCCESS);
      break;
    }
  }
}

void pwnd() { printf("\npwnd\n"); }

int login() {
  char pass[10];
  char ctrl[] = "ibe";
  printf("Enter your password: ");
  scanf("%s", pass);
  return strcmp(pass, ctrl) == 0;
}

int main() {
  int login_valid = 0;
  login_valid = login();

  if (login_valid) {
    menu();
  }
}
