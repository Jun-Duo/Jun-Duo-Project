#ifndef __field_H__
#define __field_H__

#define NUM_FIELDS 2
#define MAX_LEN_FIELD_NAME 30

// enum of field
enum Field {
    PyeongBong_Field,
    Hiddink_Futsal_Field
};

// Array of field name strings
const char fieldName[NUM_FIELDS + 1][MAX_LEN_FIELD_NAME] = {
    "",
    "평봉필드",
    "히딩크풋살장"};

/*
    Function Declarations
*/
void PrintFieldList();

/*
    Function Definitions
*/
// Print List of fields
void PrintFieldList() {
    for (int i = 1; i <= NUM_FIELDS; i++) {
        printf("%d - %s\n", i, fieldName[i]);
    }
}

#endif