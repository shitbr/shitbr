#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 50
#define MAX_TEXT_LENGTH 10000

// 分词函数
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

// 计算相似度
double calculate_similarity(char *original_text, char *copied_text) {
    char *stop_words[] = {
        "的", "是", "我", "要", "去", "看", "电影" // 示例中的简单停用词
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
    FILE *f2 = fopen(copied_f
