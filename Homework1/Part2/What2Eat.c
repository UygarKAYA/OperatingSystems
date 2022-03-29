#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[]) {

    	int numberOfPeople;
    	int threshold = 8;
    	int count, index, value = 0;
    	int peopleChoice[5] = {0, 0, 0, 0, 0};
    	int winnerPeopleChoice[5] = {0, 0, 0, 0, 0};
    	int winnerIndex = -1;
    	char foodList[5][10];

    	strcpy(foodList[0], "Kebab");
    	strcpy(foodList[1], "Burger");
    	strcpy(foodList[2], "Pasta");
    	strcpy(foodList[3], "Lahmacun");
    	strcpy(foodList[4], "Salad");

    	printf("Please Enter the Number of People: ");
    	scanf("%d", &numberOfPeople);

    	printf("|---------|----------|---------|------------|---------|\n");
    	printf("| 1-Kebab | 2-Burger | 3-Pasta | 4-Lahmacun | 5-Salad |\n");
    	printf("|---------|----------|---------|------------|---------|\n");
    	printf("Please Sort the Above Menu According to Your Choices\n");

    	for(int i=0; i<numberOfPeople; i++) {    
        	for(int j=0; j<5; j++) {
            		int choice;
            		printf("People %d Preferences %d Choice: ", (i+1), (j+1));
            		scanf("%d", &choice);
            		peopleChoice[choice-1] += (5-j);
        	}
    	}
	
	for(int i=0; i<5; i++) {
		if(threshold < peopleChoice[i]) {
			peopleChoice[i] = peopleChoice[i];
        	} else if(threshold > peopleChoice[i]) {
            		peopleChoice[i] = 0;
        	} if(peopleChoice[i] != 0) {
			count++;
			index=i;
		}
	}
	
	if(count == 0) {
        	printf("\nYou Are Eating At Home/Dorm Today!");
    	} else {
		printf("\nAt the End of the First Round, the Short List is: ");
		for(int i = 0; i<5; i++) {
			if(peopleChoice[i] != 0) {
				printf("%d, ", (i+1));
			}
		}
		
		printf("\nPlease Re-Order the Above Food According to Your Choices\n");
		for(int i=0; i<numberOfPeople; i++) {
			int preferences = 1;
			for(int j=5; j>0; j--) {
				if(peopleChoice[j-1] == 0) { continue; }
                		int choice;
				printf("People %d Preferences %d Choice: ", (i+1), (preferences++));
        	    		scanf("%d", &choice);
	            		winnerPeopleChoice[choice-1] += j;
			}
		}
		
		for(int i=0; i<5; i++) {
			if(peopleChoice[i] != 0 && winnerPeopleChoice[i] > value) {
				value = winnerPeopleChoice[i];
				winnerIndex = i;
			}
		}
		printf("As a Result of Your Choices, You Will Eat %s Food", foodList[winnerIndex]);
	}

	return 0;
}
