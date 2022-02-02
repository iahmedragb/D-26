 /**
 Author      : Ahmed Ragab
 Assignment  : C-Programming Project
 Group       : D-26
 ========================================================
 *Simple Data Base

 ============================================================================
*/

#include "SimpleDB.h"

int main(){

    uint8_t choice;
    bool quit = false;

    uint8_t id,year;
    uint8_t* subjects = (uint8_t*)malloc(3*sizeof(uint8_t));
    uint8_t* grades = (uint8_t*)malloc(3*sizeof(uint8_t));

    uint8_t i,counter;
    uint8_t *listPtr = (uint8_t*)malloc(MAXIMUM_COUNT*sizeof(uint8_t));

    dataBase_init(&dataBase);

    while(!quit){
    system("cls");
    menu();
    printf("Please Enter Your Choice : ");
    scanf("%hhu",&choice);
    switch(choice){

        case 1 :printf("Enter The Student ID : ");
                scanf("%hhu",&id);
                if(SDB_IsIdExist(id)){
                    printf("ID Already Exists in Data Base !\n");
                    break;
                }
                printf("Enter The Student Year : ");
                scanf("%hhu",&year);
                for(i = 0 ; i < 3 ; i++){
                    printf("Course_%hhu ID : ",i+1);
                    scanf("%hhu",&(subjects[i]));
                   do{ printf("Course_%hhu Grade (0~100) : ",i+1);
                    scanf("%hhu",&(grades[i]));
                    }while(grades[i] >100 && grades[i] < 0);
                }
                if(SDB_AddEntry(id, year, subjects, grades)){
                    printf("Entry Successfully Added\n");
                }else{
                    printf("Failed To Add Entry !\n");
                }
                break;

        case 2 :SDB_GetIdList(&counter ,listPtr );
                if(counter == 0){
                    printf("ID List is Empty\n");
                }else{
                printf("ID List :\n");
                for(i=0 ; i<counter ; i++){
                    printf("ID_%hhu : %hhu\n",i+1,listPtr[i]);
                }
                }
                break;

        case 3 :printf("Enter The Student ID : ");
                scanf("%hhu",&id);
                if(SDB_ReadEntry(id, &year, subjects, grades)){
                    printf("Student ID : %hhu\n",id);
                    printf("Student Year : %hhu\n",year);
                    for(i=0 ; i<3 ;i++){
                    printf("Course_%hhu ID : %hhu\n",i+1,subjects[i]);
                    printf("Course_%hhu Grade (0~100) : %hhu\n",i+1,grades[i]);
                    }
                }else{
                    printf("ID not Found !\n");
                }
                break;

        case 4 :printf("Enter The Student ID : ");
                scanf("%hhu",&id);
                SDB_DeleteEntry(id);
                break;

        case 5 :printf("Enter The Student ID : ");
                scanf("%hhu",&id);
                if(SDB_IsIdExist(id))
                    printf("ID Exists\n");
                else
                    printf("ID Not Found !\n");
                break;

        case 6 :printf("Data Base Size Is : %hhu\n",SDB_GetUsedSize());
                break;

        case 7 :if(SDB_isFull())
                    printf("Data Base Is Full\n");
                else
                    printf("Data Base Is Not Full \n");
                break;

        case 8 :    quit=true;
                break;
        default : printf("Invalid Choice \n");
                break;
    }
    system("pause");
    }
    return 0;
}
