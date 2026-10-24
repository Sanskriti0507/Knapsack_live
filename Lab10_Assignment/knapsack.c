#include <stdio.h>
#include <windows.h>

int main() {
    FILE *in = fopen("data.txt", "r");
    FILE *out = fopen("result.txt", "w");
    char tag[20];
    int testNo = 0;

    while (fscanf(in, "%s", tag) == 1) {
        int n, W, wt[20], val[20], dp[20][100];
        fscanf(in, "%d %d", &n, &W);
        for (int i = 1; i <= n; i++)
            fscanf(in, "%d %d", &wt[i], &val[i]);
        testNo++;

        for (int w = 0; w <= W; w++)
            dp[0][w] = 0;

        for (int i = 1; i <= n; i++) {
            for (int w = 0; w <= W; w++) {
                dp[i][w] = dp[i - 1][w];
                if (wt[i] <= w) {
                    int take = dp[i - 1][w - wt[i]] + val[i];
                    if (take > dp[i][w])
                        dp[i][w] = take;
                }

                printf("\033[H\033[J");
                printf("Test %d  (n=%d, W=%d)   computing row %d, capacity %d\n\n", testNo, n, W, i, w);
                printf("item    ");
                for (int c = 0; c <= W; c++)
                    printf("%5d", c);
                printf("\n");
                for (int r = 0; r <= n; r++) {
                    printf("%-8d", r);
                    for (int c = 0; c <= W; c++) {
                        if (r == i && c == w)
                            printf(" [%2d]", dp[r][c]);
                        else if (r < i || (r == i && c < w) || r == 0)
                            printf("%5d", dp[r][c]);
                        else
                            printf("%5s", ".");
                    }
                    printf("\n");
                }
                Sleep(50);
            }
        }

        printf("\nTest %d answer = %d\n", testNo, dp[n][W]);
        Sleep(1000);
        fprintf(out, "#Test%d %d %d %d\n", testNo, n, W, dp[n][W]);
    }

    fclose(in);
    fclose(out);
    return 0;
}