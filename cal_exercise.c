//
//  cal_exercise.c
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise


// To declare the structure of the exercises
static Exercise exercise_list[MAX_EXERCISES];
int exercise_list_size = 0;


/*
    description : read the information in "excercises.txt"
*/

void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen(EXERCISEFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
    // EOF까지 exercist.txt 읽어서 exercise_list에 저장
    printf("List of exercises\n");

    while (!feof(file)) {

        fscanf(file,"%50s %d",
                exercise_list[exercise_list_size].exercise_name,&exercise_list[exercise_list_size].calories_burned_per_minute);
                
        printf("%-50s %-5d\n",
            exercise_list[exercise_list_size].exercise_name,exercise_list[exercise_list_size].calories_burned_per_minute);
        
        exercise_list_size++;            
    
        if (exercise_list_size >= MAX_EXERCISES){
                break;
            }
    }

    fclose(file);
}


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

//health_data 구조체에 저장
void inputExercise(HealthData* health_data) {
    int choice, duration, calories_burned;
    int i;
    // ToCode: to provide the options for the exercises to be selected
    // database에 저장된 운동 list 출력
    printf("The list of exercises: \n");
    for(i=0;i<exercise_list_size;i++){
            printf("%d %-50s %d\n",i+1, exercise_list[i].exercise_name, exercise_list[i].calories_burned_per_minute);
        }

    
    // ToCode: to enter the exercise to be chosen with exit option
    // do-while 문 활용해서 숫자 0 or 인덱스 밖의 숫자 입력시 -> loop 종료
    do {
        printf("Select an exercise (Enter 0 to exit): ");
        scanf("%d", &choice);

        if(choice > 0){
            printf("Enter the duration of the exercise (in min.): ");
            scanf("%d", &duration);

            // ToCode: to enter the selected exercise and total calcories burned in the health data
            // 사용자가 선택한 운동을 HealthData 구조체의 exercises 배열에 추가하고, 총 소모 칼로리를 업데이트

            //입력한 운동의 소모 칼로리 계산
            calories_burned = exercise_list[choice - 1].calories_burned_per_minute * duration;

            //입력한 운동 정보와 소모 칼로리를 exercises 배열에 저장
            health_data->exercises[health_data->exercise_count] = exercise_list[choice - 1];
            health_data->exercises[health_data->exercise_count].calories_burned_per_minute = calories_burned;

            //누적 운동 개수 업데이트
            health_data->exercise_count++;

            //누적 소모 칼로리 업데이트
            health_data->total_calories_burned += calories_burned;
        }

    } while(choice != 0);
    

    

}
