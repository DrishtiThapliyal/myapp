#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// List of C keywords
const char *keywords[] = {
    "int", "float", "char", "double", "if", "else", "while",
    "for", "return", "void", "break", "continue", "switch",
    "case", "struct", "typedef", "include", "define", NULL
};

int isKeyword(char *word) {
    for (int i = 0; keywords[i] != NULL; i++)
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    return 0;
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
            ch == '=' || ch == '<' || ch == '>' || ch == '!' ||
            ch == '&' || ch == '|' || ch == '%');
}

int isDelimiter(char ch) {
    return (ch == ';' || ch == ',' || ch == '(' || ch == ')' ||
            ch == '{' || ch == '}' || ch == '[' || ch == ']');
}

void analyze(FILE *fp) {
    char ch, buffer[100];
    int i;

    while ((ch = fgetc(fp)) != EOF) {

        // Skip whitespace
        if (isspace(ch)) continue;

        // Skip single-line comments
        if (ch == '/') {
            char next = fgetc(fp);
            if (next == '/') {
                while ((ch = fgetc(fp)) != '\n' && ch != EOF);
                continue;
            } else {
                ungetc(next, fp);
            }
        }

        // Skip string literals
        if (ch == '"') {
            while ((ch = fgetc(fp)) != '"' && ch != EOF);
            continue;
        }

        // Keywords and Identifiers
        if (isalpha(ch) || ch == '_') {
            i = 0;
            buffer[i++] = ch;
            while ((ch = fgetc(fp)) != EOF && (isalnum(ch) || ch == '_'))
                buffer[i++] = ch;
            buffer[i] = '\0';
            ungetc(ch, fp);

            if (isKeyword(buffer))
                printf("%-20s --> KEYWORD\n", buffer);
            else
                printf("%-20s --> IDENTIFIER\n", buffer);
        }

        // Numbers
        else if (isdigit(ch)) {
            i = 0;
            buffer[i++] = ch;
            while ((ch = fgetc(fp)) != EOF && (isdigit(ch) || ch == '.'))
                buffer[i++] = ch;
            buffer[i] = '\0';
            ungetc(ch, fp);
            printf("%-20s --> NUMBER\n", buffer);
        }

        // Operators
        else if (isOperator(ch)) {
            buffer[0] = ch; buffer[1] = '\0';
            printf("%-20s --> OPERATOR\n", buffer);
        }

        // Delimiters
        else if (isDelimiter(ch)) {
            buffer[0] = ch; buffer[1] = '\0';
            printf("%-20s --> DELIMITER\n", buffer);
        }

        // Hash (preprocessor)
        else if (ch == '#') {
            printf("%-20s --> PREPROCESSOR\n", "#");
        }
    }
}

int main() {
    char filename[100];
    printf("Enter the C source file name: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: Cannot open file '%s'\n", filename);
        return 1;
    }

    printf("\n%-20s --> %s\n", "TOKEN", "TYPE");
    printf("-------------------------------------\n");
    analyze(fp);
    fclose(fp);
    return 0;
}