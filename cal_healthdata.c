//
//  cal_healthdata.c
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


/*
    description : enter the exercise and diet history in "health_data.txt" 
    input parameters : health_data - data object in which the selected exercise and diet is stored
    return value : No
    
    operation : 1. save the chosen exercise and total calories burned 
    			2. save the chosen diet and total calories intake 
    			3. save the total remaining calrories
*/

void saveData(const char* HEALTHFILEPATH, const HealthData* health_data) {

	int remain_calories, calories_burned, calories;

    calories_burned = health_data->total_calories_burned;
    calories = health_data->total_calories_intake;

    remain_calories = DAILY_CALORIE_GOAL - (calories - (BASAL_METABOLIC_RATE + calories_burned));

    FILE* file = fopen(HEALTHFILEPATH, "w");
    if (file == NULL) {
        printf("There is no file for health data.\n");
        return;
    }

    // ToCode: to save the chosen exercise and total calories burned 
    fprintf(file, "[Exercises] \n");
    //운동, 소비한 칼로리 저장
    for(int i=0;i<health_data->exercise_count;i++){
        fprintf(file,"%s - %d kcal\n",health_data->exercises[i].exercise_name,
            health_data->exercises[i].calories_burned_per_minute);
    }
    //전체 소비한 칼로리 저장
    fprintf(file, "Total calories burned: %d kcal\n",calories_burned);

    // ToCode: to save the chosen diet and total calories intake 
    // 음식, 섭취한 칼로리 저장
    fprintf(file, "\n[Diets] \n");
    for(int i=0; i<health_data->diet_count;i++){
        fprintf(file, "%s - %d kcal\n", health_data->diet[i].food_name,health_data->diet[i].calories_intake);
    }
    //전체 섭취한 칼로리 저장
    fprintf(file, "Total calories intake: %d kcal\n", calories);

    // ToCode: to save the total remaining calrories
    fprintf(file, "\n[Total] \n");
    fprintf(file, "Basal Metabolic rate - %d kcal\n",BASAL_METABOLIC_RATE);
    fprintf(file, "The remaining calories - %d kcal\n", remain_calories);

    fclose(file);
    
}

/*
    description : print the history of exercised and diets
    input parameters : health_data - data object in which the history of the exercise and diet is to be printed
    return value : No
    
    operation : 1. print out the saved history of exercises
    			2. print out the saved history of diets
    			3. print out the saved history of calories
*/

void printHealthData(const HealthData* health_data) {
	int calories_burned, calories,remain_calories;
    int i,k;
	
	// ToCode: to print out the saved history of exercises
    // health_data 구조체에 저장된 운동 이름, 소모 칼로리 출력
	printf("=========================== History of Exercise =======================\n");

    for(i=0;i<health_data->exercise_count;i++){
        printf("Exercise: %s , Calories burned: %d kcal\n",
        health_data->exercises[i].exercise_name,health_data->exercises[i].calories_burned_per_minute);      
    }
  
    printf("=======================================================================\n");

    // ToCode: to print out the saved history of diets
    // health_data 구조체에 저장된 음식 이름, 섭취 칼로리 출력
    printf("============================= History of Diet =========================\n");

    for(k=0;i<health_data->diet_count;i++){
        printf("Food: %s , Calories intake: %d kcal\n",
        health_data->diet[k].food_name,health_data->diet[k].calories_intake);
    }

    printf("=======================================================================\n");


	// ToCode: to print out the saved history of calories including basal metabolic rate, 
	// total calories burned, total calories intake, and the remaining calories
	printf("============================== Total Calories =========================\n");
    //기초 대사량 출력
    printf("Basal Metabolic Rate: %d kcal\n",BASAL_METABOLIC_RATE);
    //소모 칼로리 출력
    calories_burned = health_data->total_calories_burned;
    printf("Total calories burned: %d kacl\n",calories_burned);
    //섭취 칼로리 출력
    calories = health_data->total_calories_intake;
    printf("Total calories intake: %d kcal\n",calories);
    //남은 칼로리 출력
    remain_calories = DAILY_CALORIE_GOAL - (calories - (BASAL_METABOLIC_RATE + calories_burned));
    printf("The remaining calories: %d kcal\n",remain_calories);
 
    printf("=======================================================================\n \n");
    
	
	// ToCode: to print out the recommendtaion depending on the current total calories burned and intake    
    // 남은 칼로리에 따른 조건문 실행
    if(remain_calories > 0) {
        printf("Please exercise for your health!\n");
        if(calories==DAILY_CALORIE_GOAL){
            printf("Your total calorie intake for today has reached your goal!\n");
        }else {
            printf("Your total calorie intake for today has not reached your goal, remember to eat more!!\n");
        }
    }else {
        printf("[Warning]Too few calories!\n");
        if(calories==DAILY_CALORIE_GOAL){
            printf("Your total calorie intake for today has reached your goal!\n");
        }else if(calories < DAILY_CALORIE_GOAL){
            printf("Your total calorie intake for today has not reached your goal, remember to eat more!!\n");
        }else{
            printf("You have eaten more calories than planned today, but you have exercised too much!\n");
        }
    }
    
	 printf("=======================================================================\n");
}
