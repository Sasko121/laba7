#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

// ������� ��� ��������� ����� �����
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

// ������� ��� ����� ����� � ����
void replace_word_in_file(const char* filename, const char* old_word, const char* new_word) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    // ��������� ����������� �����
    FILE* temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL) {
        perror("Failed to create temporary file");
        fclose(file);
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char* pos;
        // ����� ��� �������� old_word �� new_word � �����
        while ((pos = strstr(line, old_word)) != NULL) {
            // ����� ������� ����� �� old_word
            *pos = '\0'; // ��������� ����� �� ������� old_word
            fprintf(temp_file, "%s%s", line, new_word);
            // ��������� �������� ���� old_word
            strcpy(line, pos + strlen(old_word));
        }
        // ����� ������� �����
        fprintf(temp_file, "%s", line);
    }

    fclose(file);
    fclose(temp_file);

    // �������� ����������� ���� �� ����������
    remove(filename);
    rename("temp.txt", filename);
}

int main() {
    const char* filename = "text.txt"; // ����� ����� ��� ������
    char old_word[50], new_word[50];

    printf("Enter a replacement word: ");
    scanf("%s", old_word);
    printf("Enter a new word: ");
    scanf("%s", new_word);

    // �������� ����� �����
    printf("\nFile contents before replacement:\n");
    view_file_content(filename);

    // ����� ��� � ����
    replace_word_in_file(filename, old_word, new_word);

    // �������� ����� ����� ���� �����
    printf("\nFile contents after replacement:\n");
    view_file_content(filename);

    return 0;
}