#include <stdio.h>


int main();
void find_window(int mirror_room[30][30], char dir, int ww, int dd, int w, int d);

int main()
{
        int w, d;
        int mirror_room[30][30] = {{0}};
        scanf("%d", &w);
        scanf("%d", &d);

        int i, j;
        for (i = 1; i <= d; ++i) {
                for (j = 1; j <= w; ++j) {
                        scanf("%d", &mirror_room[i][j]);
                }
        }

        int ww, dd;

        /* down side */
        ww = 1;
        for (i = 0; i < w; ++i) {
                mirror_room[d + 1][ww] = i;
                ++ww;
        }

        /* right side */
        dd = d;
        for (i = w; i < w + d; ++i) {
                mirror_room[dd][w + 1] = i;
                --dd;
        }

        /* top side */
        ww = w;
        for (i = w + d; i < 2 * w + d; ++i) {
                mirror_room[0][ww] = i;
                --ww;
        }

        /* left side */
        dd = 1;
        for (i = 2 * w + d; i < 2 * (w + d); ++i) {
                mirror_room[dd][0] = i;
                ++dd;
        }

        printf("\n");

        /* Print mirror room */
        printf("Mirror room:\n");
        for (i = 0; i <= d + 1; ++i) {
                for (j = 0; j <= w + 1; ++j) {
                        printf("%d ", mirror_room[i][j]);
                }
                printf("\n");
        }
        printf("\n");

        printf("Window no:\n");
        /* down side: find window no */
        char dir = 't';
        dd = d;
        for (i = 1; i <= w; ++i) {
                ww = i;
                find_window(mirror_room, dir, ww, dd, w, d);
        }

        /* right side: find window no */
        dir = 'l';
        ww = w;
        for (i = d; i >= 1; --i) {
                dd = i;
                find_window(mirror_room, dir, ww, dd, w, d);
        }

        /* top side: find window no */
        dir = 'd';
        dd = 1;
        for (i = w; i >= 1; --i) {
                ww = i;
                find_window(mirror_room, dir, ww, dd, w, d);
        }

        /* left side: find window no */
        dir = 'r';
        ww = 1;
        for (i = 1; i <= d; ++i) {
                dd = i;
                find_window(mirror_room, dir, ww, dd, w, d);
        }
        printf("\n");

        return 0;
}

void find_window(int mirror_room[30][30], char dir, int ww, int dd, int w, int d)
{
        while (ww >= 1 && ww <= w && dd >= 1 && dd <= d) {
                if (mirror_room[dd][ww] == 0) {
                        switch (dir) {
                        case 't':
                                --dd;
                                break;
                        case 'd':
                                ++dd;
                                break;
                        case 'r':
                                ++ww;
                                break;
                        case 'l':
                                --ww;
                                break;
                        }
                } else if (mirror_room[dd][ww] == 1) {
                        switch (dir) {
                        case 't':
                                dir = 'r';
                                ++ww;
                                break;
                        case 'd':
                                dir = 'l';
                                --ww;
                                break;
                        case 'r':
                                dir = 't';
                                --dd;
                                break;
                        case 'l':
                                dir = 'd';
                                ++dd;
                                break;
                        }
                } else if (mirror_room[dd][ww] == 2) {
                        switch (dir) {
                        case 't':
                                dir = 'l';
                                --ww;
                                break;
                        case 'd':
                                dir = 'r';
                                ++ww;
                                break;
                        case 'r':
                                dir = 'd';
                                ++dd;
                                break;
                        case 'l':
                                dir = 't';
                                --dd;
                                break;
                        }
                }
                /* printf("now %d %d, mirror: %d, dir: %c\n", dd, ww, mirror_room[dd][ww], dir); */
        }
        /* printf("ooh\n"); */
        printf("%d ", mirror_room[dd][ww]);
}
