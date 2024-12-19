//
//  cal_diets.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_DIETS 100      			// Maximum number of diets
#define MAX_FOOD_NAME_LEN 50		// Maximum length of the name of food


// list of diets 
static Diet diet_list[MAX_DIETS];
static int diet_list_size = 0;


/*
    description : read the information in "diets.txt"
*/

void loadDiets(const char* DIETFILEPATH) {
    FILE *file = fopen(DIETFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for diets! \n");
        return;
    }

     // ToCode: to read a list of the diets from the given file
     // EOF까지 diets.txt 읽어서 diet_list 구조체에 저장
    while (!feof(file)) {

        fscanf(file,"%50s %d",
            diet_list[diet_list_size].food_name,&diet_list[diet_list_size].calories_intake);

        printf("%-50s %-5d\n",
        diet_list[diet_list_size].food_name,diet_list[diet_list_size].calories_intake);

        diet_list_size++;
    	
        if (diet_list_size >= MAX_DIETS){
        	break;
		}
    }
    fclose(file);
}

/*
    description : to enter the selected diet and the total calories intake in the health data
    input parameters : health_data - data object to which the selected diet and its calories are added 
    return value : No
    
    operation : 1. provide the options for the diets to be selected
    			2. enter the selected diet and the total calories intake in the health data
*/

void inputDiet(HealthData* health_data) {
    int choice, calories;
    int i;
    
    // ToCode: to provide the options for the diets to be selected
    // database에 저장된 운동 list 출력
    printf("The list of diets:\n");
    for(i=0;i<diet_list_size;i++){
        printf("%d %-50s %d\n",i+1, diet_list[i].food_name, diet_list[i].calories_intake);
    }    
    
	// ToCode: to enter the diet to be chosen with exit option
    // do-while 문 활용해서 숫자 0 입력시 -> loop 종료
    do {
        printf("Select an diet (Enter 0 to exit): ");
        scanf("%d", &choice);

        if(choice > 0){
            
            // ToCode: to enter the selected diet in the health data
            // 사용자가 선택한 운동을 HealthData 구조체의 diet 배열에 추가하고, 총 섭취 칼로리를 업데이트

            //입력한 음식의 칼로리 계산
            calories = diet_list[choice - 1].calories_intake;

            //입력한 음식 정보를 diet 배열에 저장
            health_data->diet[health_data->diet_count] = diet_list[choice - 1];

            //누적 음식 개수 업데이트
            health_data->diet_count++;

            //누적 섭취 칼로리 업데이트
            // ToCode: to enter the total calories intake in the health data
            health_data->total_calories_intake += calories;

        }

    } while(choice != 0);
        

}

