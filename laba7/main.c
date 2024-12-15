#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

// Функція для перегляду вмісту файлу
void view_file_content(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

// Функція для заміни слова у файлі
void replace_word_in_file(const char* filename, const char* old_word, const char* new_word) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    // Створення тимчасового файлу
    FILE* temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL) {
        perror("Failed to create temporary file");
        fclose(file);
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char* pos;
        // Заміна всіх входжень old_word на new_word у рядку
        while ((pos = strstr(line, old_word)) != NULL) {
            // Запис частини рядка до old_word
            *pos = '\0'; // Завершуємо рядок на позиції old_word
            fprintf(temp_file, "%s%s", line, new_word);
            // Переміщуємо вказівник після old_word
            strcpy(line, pos + strlen(old_word));
        }
        // Запис залишку рядка
        fprintf(temp_file, "%s", line);
    }

    fclose(file);
    fclose(temp_file);

    // Замінюємо оригінальний файл на тимчасовий
    remove(filename);
    rename("temp.txt", filename);
}

int main() {
    const char* filename = "text.txt"; // Назва файлу для роботи
    char old_word[50], new_word[50];

    printf("Enter a replacement word: ");
    scanf("%s", old_word);
    printf("Enter a new word: ");
    scanf("%s", new_word);

    // Перегляд вмісту файлу
    printf("\nFile contents before replacement:\n");
    view_file_content(filename);

    // Заміна слів у файлі
    replace_word_in_file(filename, old_word, new_word);

    // Перегляд вмісту файлу після заміни
    printf("\nFile contents after replacement:\n");
    view_file_content(filename);

    return 0;
}