#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define HASH_TABLE_SIZE 50
#define ERROR_MORSE_CODE "........"

const char* morse_code[] = 
{
    //A-Z: 0-25
    ".-",   "-...", "-.-.", 
    "-..",  ".",    "..-.", 
    "--.",  "....", "..",  
    ".---", "-.-",  ".-..", 
    "--",   "-.",   "---",  
    ".--.", "--.-", ".-.", 
    "...",  "-",    "..-",  
    "...-", ".--",  "-..-", 
    "-.--", "--..",   
    //0-9 26-35:
    "-----", ".----", "..---", 
    "...--", "....-", ".....", 
    "-....", "--...", "---..", 
    "----.",   
    //Một số dấu câu: 36-46
    ".-.-.-", "--..--", "..--..", 
    "-.-.--", "-....-", ".----.", 
    "-..-.",  "-.-.-.", ".-.-.", 
    "---...", "-.-.-",  ".-..-.", 
    "-...-",  ".--.-." 
};

const char* alpha_code = "abcdefghijklmnopqrstuvwxyz0123456789.,?!-'\"=;:";

typedef struct HashNode {
    char morse[10];  
    char alpha;      
    struct HashNode* next; // xử lý collision
} HashNode;

HashNode* hash_table[HASH_TABLE_SIZE];

int hash_function(const char* key) {
    int index = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        index = (index + key[i]) % HASH_TABLE_SIZE;
    }
    return index;
}

void insert_hash(const char* morse, char alpha) {
    int index = hash_function(morse);
    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
    strcpy(new_node->morse, morse);
    new_node->alpha = alpha;
    new_node->next = hash_table[index];
    hash_table[index] = new_node;
}

char search_hash_morse_code(const char* morse) {
    int index = hash_function(morse);
    HashNode* current_pointer = hash_table[index];
    while (current_pointer != NULL) {
        if (strcmp(current_pointer->morse, morse) == 0) {
            return current_pointer->alpha;
        }
        current_pointer = current_pointer->next;
    }
    return '?'; // Ký tự không tìm thấy
}

void initialize_morse_hash() {
    memset(hash_table, 0, sizeof(hash_table));
    int number_morse_code = sizeof(morse_code) / sizeof(morse_code[0]);
    for (int i = 0; i < number_morse_code; i++) {
        insert_hash(morse_code[i], alpha_code[i]);
    }
}

void text_to_morse(FILE *inputFile, FILE* outputFile) {
    char ch;
    int line_num = 1;
    while ((ch = fgetc(inputFile)) != EOF) {
        ch = tolower(ch); 
        if (ch >= 'a' && ch <= 'z') {
            fprintf(outputFile, "%s ", morse_code[ch - 'a']);
        }
        else if (ch >= '0' && ch <= '9') {
            fprintf(outputFile, "%s ", morse_code[ch - '0' + 26]);
        }
        else if (ch == ' ') {
            fprintf(outputFile, "/ ");
        }
        else if (ch == '.') {
            fprintf(outputFile, "%s ", morse_code[36]);
        }
        else if (ch == ',') {
            fprintf(outputFile, "%s ", morse_code[37]);
        }
        else if (ch == '?') {
            fprintf(outputFile, "%s ", morse_code[38]);
        }
        else {
            printf("Error: Unrecognised character %c on line %d.\n", ch, line_num);
        }
    }
}

int isMorseCodeFile(const char* fileName) {
    FILE* inputFile = fopen(fileName, "r");
    if (inputFile == NULL) {
        printf("ERROR: %s could not be opened\n", fileName);
        return 0;
    }
    char character;
    while ((character = fgetc(inputFile)) != EOF) {
        if (character != '.' && character != '-' && character != ' ' && character != '\n' && character != '/') {
            fclose(inputFile);
            return 0;
        }
    }
    fclose(inputFile);
    return 1;
}

void morse_to_text(FILE* inputFile, FILE* outputFile) {
    char morse_buffer[50]; 
    int buffer_index = 0;
    char ch;
    int line_num = 1;
    while ((ch = fgetc(inputFile)) != EOF) 
    {
        if (ch == '.' || ch == '-') {
            morse_buffer[buffer_index++] = ch;
        } 
        else if (ch == ' ') 
        {
            morse_buffer[buffer_index] = '\0';
            if (buffer_index > 0) 
            {
                char* result = strstr(morse_buffer, ERROR_MORSE_CODE);
                if(result != NULL )
                {
                    int i = 0;
                    while(i < result - morse_buffer)
                    {
                        fprintf(outputFile, "%c", morse_buffer[i]);
                        i++;
                    }
                    fprintf(outputFile, "#");
                    
                }
                else
                {
                    char result = search_hash_morse_code(morse_buffer);
                    if (result == '?') {  
                        fprintf(stderr, "Error: Invalid Morse code '%s' on line %d.\n", morse_buffer, line_num);
                        fprintf(outputFile, "*");  
                    } else {
                        fprintf(outputFile, "%c", result);  
                    }
                }
                
            }
            buffer_index = 0; // reset lưu từ mới
        } else if (ch == '/') 
        {  
            fprintf(outputFile, " ");
        } else if (ch == '\n') 
        {  
            fprintf(outputFile, "\n");
            line_num++;  
        }
    }

    // Xử lý trường hợp có mã Morse còn lại trong buffer
    if (buffer_index > 0) 
    {
        morse_buffer[buffer_index] = '\0';
        char result = search_hash_morse_code(morse_buffer);
        if (result == '?') {
            fprintf(stderr, "Error: Invalid Morse code '%s' on line %d.\n", morse_buffer, line_num);
            fprintf(outputFile, "*");
        } else {
            fprintf(outputFile, "%c", result);
        }
    }
}



void overwrite_check(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        char user_input;
        printf("Warning: %s already exists. Do you wish to overwrite (y,n)? ", filename);
        scanf(" %c", &user_input);
        if (user_input != 'y') {
            exit(0);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("ERROR: Number of input arguments is not satisfied\n");
        return 1;
    }

    FILE* inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("Error: %s could not be opened\n", argv[1]);
        return 1;
    }

    overwrite_check(argv[2]);
    FILE* outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        printf("Cannot create output file %s\n", argv[2]);
        fclose(inputFile);
        return 1;
    }

    if (isMorseCodeFile(argv[1])) {
        printf("File input is Morse Code\n");
        initialize_morse_hash();
        morse_to_text(inputFile, outputFile);
        printf("Conversion complete: %s\n", argv[2]);
    } else {
        printf("File input is Text File\n");
        initialize_morse_hash();
        text_to_morse(inputFile, outputFile);
        printf("Conversion complete: %s\n", argv[2]);
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
