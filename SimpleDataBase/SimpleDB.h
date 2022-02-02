#ifndef SIMPLEDB_H_INCLUDED
#define SIMPLEDB_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

#define MAXIMUM_COUNT 10
#define MAXIMUM_UINT8_SIZE 255
typedef struct student
{
    uint8_t ID, Year;
}student;

typedef struct course
{
    uint8_t courseID[3],courseGrade[3];
}course;

typedef struct Entry
{
    student studentData;
    course courseData;
    struct Entry *next,*prev;
}Entry;

typedef struct SimpleDB
{
    Entry *header,*tail;
    uint8_t entryCount;
}SimpleDB;

/**
*   SDB_IsFull : Check if the data base is full
*
*   bool (return): Return 1 if the data base is full, otherwise 0
*/
bool SDB_isFull(void);

/**
*   SDB_GetUsedSize : Get the numbers of entries in the data base
*
*   uint8_t (return): Return number of entries
*/
uint8_t SDB_GetUsedSize(void);

/**
*   SDB_AddEntry : Add new entry to data base
*
*   uint8_t id: Input student ID
*   uint8_t year: Input student year
*   uint8_t *subjects: Pointer to 3 subjects IDs, each subject id is uint8_t id
*   uint8_t *grades: Pointer to 3 grades, each grade is uint8_t id (from 0 to 100)
*
*   bool (return): Return 1 if the new entry is added sucessfully, otherwise 0
*/
bool SDB_AddEntry(uint8_t id, uint8_t year, uint8_t* subjects, uint8_t* grades);

/**
*   SDB_DeleteEntry : Delete the entry for a targeted id
*
*   uint8_t id: Input target student ID
*/
void SDB_DeleteEntry(uint8_t id);

/**
*   SDB_ReadEntry : Read an entry matching the provided id
*
*   uint8_t id: Input student ID
*   uint8_t* year: Output year for a matching ID
*   uint8_t* subjects: Output pointer for 3 subjects ID matching the student ID
*   uint8_t* grades: Output pointer for 3 grades matching the student ID
*
*   bool (return): Return 1 if the entry exists, otherwise 0
*/
bool SDB_ReadEntry(uint8_t id, uint8_t* year, uint8_t* subjects, uint8_t* grades);

/**
*   SDB_GetIdList : Get the list of the IDs of the student
*
*   uint8_t* count: Pointer to the number of entries currently exists in the data base
*   uint8_t* list: Pointer to the list of IDs
*
*/
void SDB_GetIdList(uint8_t* count, uint8_t* list);

/**
*   SDB_IsIdExist : Check if the provided ID of student exist
*
*   uint8_t id: Input student ID
*
*   bool (return): Return 1 if ID exists in the data base, otherwise 0
*/
bool SDB_IsIdExist(uint8_t ID);

/**
*   dataBase_init : Initialize the entry counter, next entry pointer and previous entry pointer
*
*   SimpleDB* DB: Pointer to SimpleDB type represents the address of the data base
*
*/
void dataBase_init(SimpleDB* DB);

/**
*   menu : Menu interface for the application
*
*/
void menu(void);
void test(void);

///SimpleDb dataBase as a Global variable
SimpleDB dataBase;
#endif // SIMPLEDB_H_INCLUDED
