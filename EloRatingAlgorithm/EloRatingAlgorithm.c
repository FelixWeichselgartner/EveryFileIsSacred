#include <stdio.h>
#include <math.h>


float probability(float r1, float r2) {
    return (1.0/(1.0 + pow(10, ((r2 - r1)/400))));
}

void updateRating(float *rating, int win, float p) {
    const int K = 30;
    *rating = *rating + K * (win - p);
}

void EloRating(float *r1, float *r2, int win) {
    float p1, p2;
    int winp1, winp2;

    if (win == 0) {
        winp1 = 1;
        winp2 = 0;
    } else {
        winp1 = 0;
        winp2 = 1;
    }

    p1 = probability(*r1, *r2);
    p2 = probability(*r2, *r1);
    printf("p1 = %f, p2 = %f, p1+p2 = %f\n", p1, p2, p1+p2);
    updateRating(r1, winp1, p1);
    updateRating(r2, winp2, p2);
}

void main() {
    float ratingPlayer1, ratingPlayer2;
    int winner;

    printf("rating of Player1: ");
    scanf("%f", &ratingPlayer1);
    printf("rating of Player2: ");
    scanf("%f", &ratingPlayer2);

    //loop
    while (1) {
        printf("who is the winner?:\n0 = player1, 1 = player2?: ");
        scanf("%d", &winner);
        EloRating(&ratingPlayer1, &ratingPlayer2, winner);
        printf("player1's new rating is %f\n", ratingPlayer1);
        printf("player2's new rating is %f\n", ratingPlayer2);
    }
}