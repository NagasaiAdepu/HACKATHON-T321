#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define DAILY_GOAL_STEPS 10000
#define DAILY_GOAL_MINUTES 30
#define MAX_WORKOUT_NAME_LEN 50
#define MAX_CUSTOM_WORKOUTS 10

// Struct to store user's fitness data
typedef struct {
    char name[MAX_NAME_LEN];
    int steps_today;
    int workout_minutes_today;
    int total_steps;
    int total_workout_minutes;
    int custom_workouts_minutes[MAX_CUSTOM_WORKOUTS];
    char custom_workout_names[MAX_CUSTOM_WORKOUTS][MAX_WORKOUT_NAME_LEN];
} FitnessTracker;

// Function to display motivational messages
void displayMotivation(int minutes, int goal, const char* activity) {
    if (minutes >= goal) {
        printf("\nGreat job! You've reached your daily %s goal!\n", activity);
    } else if (minutes >= goal * 0.75) {
        printf("\nYou're doing great! Keep going to reach your %s goal!\n", activity);
    } else {
        printf("\nYou can do it! Stay active and keep moving towards your %s goal!\n", activity);
    }
}

// Function to set up user data
void setUpUserData(FitnessTracker *user) {
    printf("Enter your name: ");
    fgets(user->name, MAX_NAME_LEN, stdin);
    user->name[strcspn(user->name, "\n")] = 0;  // Remove the newline character

    user->steps_today = 0;
    user->workout_minutes_today = 0;
    user->total_steps = 0;
    user->total_workout_minutes = 0;
    
    for (int i = 0; i < MAX_CUSTOM_WORKOUTS; i++) {
        user->custom_workouts_minutes[i] = 0;
    }

    printf("\nWelcome %s! Let's start tracking your fitness journey.\n", user->name);
}

// Function to log daily steps
void logSteps(FitnessTracker *user) {
    int steps;
    printf("\nEnter the number of steps you took today: ");
    scanf("%d", &steps);
    user->steps_today = steps;
    user->total_steps += steps;
    
    displayMotivation(steps, DAILY_GOAL_STEPS, "steps");
}

// Function to log daily workout time
void logWorkout(FitnessTracker *user, const char* workoutType) {
    int minutes;
    printf("\nEnter the number of minutes you spent on %s today: ", workoutType);
    scanf("%d", &minutes);
    user->workout_minutes_today += minutes;
    user->total_workout_minutes += minutes;
    
    displayMotivation(minutes, DAILY_GOAL_MINUTES, workoutType);
}

// Function to log custom workout
void logCustomWorkout(FitnessTracker *user) {
    int workoutIndex;
    printf("\nChoose a custom workout to log (0 to %d):\n", MAX_CUSTOM_WORKOUTS - 1);
    for (int i = 0; i < MAX_CUSTOM_WORKOUTS; i++) {
        if (user->custom_workouts_minutes[i] > 0) {
            printf("%d. %s (Time: %d minutes)\n", i, user->custom_workout_names[i], user->custom_workouts_minutes[i]);
        }
    }
    printf("\nEnter your choice: ");
    scanf("%d", &workoutIndex);

    if (workoutIndex >= 0 && workoutIndex < MAX_CUSTOM_WORKOUTS && user->custom_workouts_minutes[workoutIndex] > 0) {
        int minutes;
        printf("\nEnter the number of minutes you spent on %s today: ", user->custom_workout_names[workoutIndex]);
        scanf("%d", &minutes);
        user->custom_workouts_minutes[workoutIndex] += minutes;
        user->total_workout_minutes += minutes;

        displayMotivation(minutes, 30, user->custom_workout_names[workoutIndex]);  // Assuming 30 min is the target for custom workouts
    } else {
        printf("\nInvalid workout selection!\n");
    }
}

// Function to create a custom workout
void createCustomWorkout(FitnessTracker *user) {
    if (user->custom_workouts_minutes[MAX_CUSTOM_WORKOUTS - 1] > 0) {
        printf("\nMaximum number of custom workouts reached.\n");
        return;
    }

    char workoutName[MAX_WORKOUT_NAME_LEN];
    int workoutDuration;
    printf("\nEnter the name of your custom workout: ");
    getchar();  // To clear the input buffer
    fgets(workoutName, MAX_WORKOUT_NAME_LEN, stdin);
    workoutName[strcspn(workoutName, "\n")] = 0;  // Remove newline

    printf("Enter the number of minutes for this workout: ");
    scanf("%d", &workoutDuration);

    for (int i = 0; i < MAX_CUSTOM_WORKOUTS; i++) {
        if (user->custom_workouts_minutes[i] == 0) {
            strcpy(user->custom_workout_names[i], workoutName);
            user->custom_workouts_minutes[i] = workoutDuration;
            printf("\nCustom workout \"%s\" added with %d minutes.\n", workoutName, workoutDuration);
            break;
        }
    }
}

// Function to display the list of available workout categories
void displayWorkoutCategories() {
    printf("\nChoose a workout category:\n");
    printf("1. Stretching\n");
    printf("2. Bodyweight Exercises\n");
    printf("3. Yoga\n");
    printf("4. Custom Workout\n");
    printf("5. Back to Main Menu\n");
}

// Function to view progress
void viewProgress(FitnessTracker *user) {
    printf("\n%s's Fitness Progress:\n", user->name);
    printf("Today's Steps: %d (Goal: %d)\n", user->steps_today, DAILY_GOAL_STEPS);
    printf("Today's Workout Minutes: %d (Goal: %d)\n", user->workout_minutes_today, DAILY_GOAL_MINUTES);
    printf("Total Steps: %d\n", user->total_steps);
    printf("Total Workout Minutes: %d\n", user->total_workout_minutes);

    for (int i = 0; i < MAX_CUSTOM_WORKOUTS; i++) {
        if (user->custom_workouts_minutes[i] > 0) {
            printf("Custom Workout: %s - Total Time: %d minutes\n", user->custom_workout_names[i], user->custom_workouts_minutes[i]);
        }
    }
}

// Function to track workouts from the main menu
void trackWorkouts(FitnessTracker *user) {
    displayWorkoutCategories();
    int workoutChoice;
    printf("Enter your choice: ");
    scanf("%d", &workoutChoice);
    
    switch (workoutChoice) {
        case 1:
            logWorkout(user, "Stretching");
            break;
        case 2:
            logWorkout(user, "Bodyweight Exercises");
            break;
        case 3:
            logWorkout(user, "Yoga");
            break;
        case 4:
            logCustomWorkout(user);
            break;
        case 5:
            return;  // Back to the main menu
        default:
            printf("\nInvalid choice!\n");
            break;
    }
}
void showMenu() {
    printf("\nFitness Tracker :-\n");
    printf("1. Log Steps\n");
    printf("2. Track Workouts\n");
    printf("3. View Progress\n");
    printf("4. Create Custom Workout\n");
    printf("5. Exit\n");
}
int main() {
    FitnessTracker user;
    int choice;
    setUpUserData(&user);
    while (1) {
        showMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                logSteps(&user);
                break;
            case 2:
                trackWorkouts(&user);
                break;
            case 3:
                viewProgress(&user);
                break;
            case 4:
                createCustomWorkout(&user);
                break;
            case 5:
                printf("\nThank you for using Fitness Tracker! Stay fit!\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please select again.\n");
                break;
        }
    }
    return 0;
}
