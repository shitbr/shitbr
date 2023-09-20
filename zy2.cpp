#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 50
#define MAX_TEXT_LENGTH 10000

// �ִʺ���
void tokenize(char *text, char **words, int *word_count, char *stop_words[], int stop_word_count) {
    char *token = strtok(text, " ");
    while (token != NULL) {
        int is_stop_word = 0;
        for (int i = 0; i < stop_word_count; i++) {
            if (strcmp(token, stop_words[i]) == 0) {
                is_stop_word = 1;
                break;
            }
        }
        if (!is_stop_word) {
            words[*word_count] = token;
            (*word_count)++;
        }
        token = strtok(NULL, " ");
    }
}

// �������ƶ�
double calculate_similarity(char *original_text, char *copied_text) {
    char *stop_words[] = {
        "��", "��", "��", "Ҫ", "ȥ", "��", "��Ӱ" // ʾ���еļ�ͣ�ô�
    };
    int stop_word_count = sizeof(stop_words) / sizeof(stop_words[0]);

    char *original_words[MAX_TEXT_LENGTH];
    char *copied_words[MAX_TEXT_LENGTH];
    int original_word_count = 0;
    int copied_word_count = 0;

    tokenize(original_text, original_words, &original_word_count, stop_words, stop_word_count);
    tokenize(copied_text, copied_words, &copied_word_count, stop_words, stop_word_count);

    int common_word_count = 0;
    for (int i = 0; i < original_word_count; i++) {
        for (int j = 0; j < copied_word_count; j++) {
            if (strcmp(original_words[i], copied_words[j]) == 0) {
                common_word_count++;
                break;
            }
        }
    }

    double similarity = (double)common_word_count / original_word_count * 100;
    return similarity;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: ./plagiarism_checker <original_file> <copied_file> <output_file>\n");
        return 1;
    }

    char *original_file = argv[1];
    char *copied_file = argv[2];
    char *output_file = argv[3];

    FILE *f1 = fopen(original_file, "r");
    FILE *f2 = fopen(copied_file, "r");
    if (f1 == NULL || f2 == NULL) {
        printf("Error opening input files.\n");
        return 1;
    }

    char original_text[MAX_TEXT_LENGTH];
    char copied_text[MAX_TEXT_LENGTH];

    fgets(original_text, sizeof(original_text), f1);
    fgets(copied_text, sizeof(copied_text), f2);

    fclose(f1);
    fclose(f2);

    double similarity = calculate_similarity(original_text, copied_text);

    FILE *f = fopen(output_file, "w");
    if (f == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }

    fprintf(f, "%.2f", similarity);
    fclose(f);

    printf("Similarity: %.2f%%\n", similarity);

    return 0;
}

