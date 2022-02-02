#include "SimpleDB.h"
SimpleDB dataBase;

bool SDB_isFull(void){
    //Check if the data base counter reached it's maximum value
    return ( dataBase.entryCount == MAXIMUM_COUNT) ? true : false ;
}
uint8_t SDB_GetUsedSize(void){
    //return data base counter value
    return dataBase.entryCount;
}
bool SDB_AddEntry(uint8_t id, uint8_t year, uint8_t* subjects, uint8_t* grades){
    //Check if the Data Base is Full
    if(SDB_isFull()){
        printf("Data Base is Full !\n");
        return false;
    }
    //Create New Entry
    Entry* newEntry=(Entry*)malloc(sizeof(Entry));

    uint32_t i;
    //Check if the entry allocated successfully
    if(newEntry == NULL){
        printf("Unable to allocate new Entry !\n");
        return false;
    }else{
        //initialize the new entry next and prev pointers values
        newEntry->next = NULL;
        newEntry->prev = NULL;
    }
    //Assign the provided data to the new entry
    newEntry->studentData.ID = id;
    newEntry->studentData.Year = year;
    for( i=0 ; i<3 ; i++){
        newEntry->courseData.courseID[i] = subjects[i];
        newEntry->courseData.courseGrade[i] = grades[i];
    }
    //Check if the data base is empty
    if(dataBase.entryCount == 0){
        dataBase.header = newEntry;
        dataBase.tail = newEntry;
    }else{
        //Add the new entry at last of the data base
        dataBase.tail->next = newEntry;
        newEntry->prev = dataBase.tail;
        dataBase.tail = newEntry;
    }
    //Increment the data base counter
    dataBase.entryCount++;
    return true;


}
void SDB_DeleteEntry(uint8_t id){
    if(SDB_IsIdExist(id)){
    //Create a pointer to Entry pointing to the data base header
    Entry* current = dataBase.header;
    while(current != NULL){
        //Delete the entry matching the target ID
        if(current->studentData.ID == id){
            //Check if only one entry exists
            if(SDB_GetUsedSize() == 1){
                dataBase_init(&dataBase);
            //check if the deleted entry is the header
            }else if(current == dataBase.header){
                dataBase.header = dataBase.header->next;
                dataBase.header->prev = NULL;
            //check if the deleted entry is the tail
            }else if(current == dataBase.tail){
                dataBase.tail = dataBase.tail->prev;
                dataBase.tail->next = NULL;
            }else{
            //check if a next entry exists
            if(current->next != NULL)
            current->next->prev = current->prev;
            //check if a previous entry exist
            if(current->prev != NULL)
            current->prev->next = current->next;
            }
            //Delete the entry
            free(current);
            //Decrement the data base counter after successfully deleting the target entry
            dataBase.entryCount--;
            //Output format in case of success
            printf("Deleted successfully !\n");
            return;
        }
        else{
            //move to the next entry in the data base
            current = current->next;
        }
    }}
    //Output format in case of failure
    printf("Target Does Not Exist In Data Base !\n");
    return;
}
bool SDB_ReadEntry(uint8_t id, uint8_t* year, uint8_t* subjects, uint8_t* grades){
    //Check If ID Exists
    if(SDB_IsIdExist(id)){
    //Create Pointer to Entry Pointing to header of the data base
    Entry* current = dataBase.header;
    while(current != NULL){
        //Read the data for the matched id
        if(current->studentData.ID == id){
            *year = current->studentData.Year;
            for(uint8_t i=0 ; i<3 ; i++){
                subjects[i] = current->courseData.courseID[i];
                grades[i] = current->courseData.courseGrade[i];
            }

            return true;
        }
        else{
            //move to the next entry
            current = current->next;
        }
    }
    }
    return false;
}
void SDB_GetIdList(uint8_t* count, uint8_t* list){
    *count = dataBase.entryCount;
    if((*count) == 0){
        list = NULL;
        return;
    }
    Entry* current = dataBase.header;
    uint8_t i = 0;
    //store ID of every entry in data base
    while(current != NULL){
        list[i]= current->studentData.ID;
        i++;
        current = current->next;
        }
}
bool SDB_IsIdExist(uint8_t ID){
    Entry* current = dataBase.header;
    while(current != NULL){
        //Check for a matching for the target
        if(current->studentData.ID == ID)
            return true;
        else
            current = current->next;
    }
    return false;
}
void dataBase_init(SimpleDB* DB){
    //initialize the Data Base
    DB->header = NULL;
    DB->tail = NULL;
    DB->entryCount = 0;
}
void menu(void){

    puts("             Simple Data Base");
    puts("===========================================");
    puts(" 1- Add New Entry");
    puts(" 2- Print ID List");
    puts(" 3- Read Entry");
    puts(" 4- Delete Entry");
    puts(" 5- Search for ID");
    puts(" 6- Data Base Size");
    puts(" 7- Check if Data Base is Full");
    puts(" 8- Quit");
    puts("===========================================");
}

