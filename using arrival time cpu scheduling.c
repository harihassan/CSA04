#include <stdio.h>

#define MAX_REQUESTS 10

// Structure to represent a disk request
typedef struct {
    int track;
    int arrival_time;
} Request;

// Function to simulate C-SCAN disk scheduling
void c_scan(Request requests[MAX_REQUESTS], int num_requests, int initial_track) {
    int total_head_movement = 0;
    int current_track = initial_track;
    int index = 0;

    // Sort requests by track number
    for (int i = 0; i < num_requests - 1; i++) {
        for (int j = i + 1; j < num_requests; j++) {
            if (requests[i].track > requests[j].track) {
                Request temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    // Move from initial track to highest track
    printf("Track movement sequence: %d", current_track);
    for (int i = 0; i < num_requests; i++) {
        if (requests[i].track >= current_track) {
            total_head_movement += abs(requests[i].track - current_track);
            current_track = requests[i].track;
            index = i;
            break;
        }
    }
    for (int i = index + 1; i < num_requests; i++) {
        printf(" -> %d", requests[i].track);
        total_head_movement += abs(requests[i].track - current_track);
        current_track = requests[i].track;
    }

    // Move from highest track to lowest track
    printf(" -> 199"); // Assuming maximum track number is 199
    total_head_movement += abs(199 - current_track);
    current_track = 0;
    printf(" -> 0");
    total_head_movement += abs(0 - current_track);
    current_track = 0;

    // Move from lowest track to initial track
    for (int i = 0; i <= index; i++) {
        printf(" -> %d", requests[i].track);
        total_head_movement += abs(requests[i].track - current_track);
        current_track = requests[i].track;
    }
    printf("\nTotal head movement: %d\n", total_head_movement);
}

int main() {
    Request requests[MAX_REQUESTS] = {
        {100, 0},
        {50, 1},
        {200, 2},
        {30, 3},
        {150, 4},
        {80, 5},
        {120, 6},
        {20, 7},
        {10, 8},
        {60, 9}
    };
    int num_requests = 10;
    int initial_track = 50;

    c_scan(requests, num_requests, initial_track);

    return 0;
}

OUTPUT

Track movement sequence: 50 -> 60 -> 80 -> 100 -> 120 -> 150 -> 200 -> 199 -> 0 -> 10 -> 20 -> 30 -> 50
Total head movement: 201
