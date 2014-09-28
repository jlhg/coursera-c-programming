#include <stdio.h>


int main()
{
        int x = 0;
        int y = 0;

        int p_time = 0;
        char dir = 't';
        int time;
        int signal;
        int distance;

        while (1) {
                scanf("%d", &time);
                scanf("%d", &signal);
                distance = (time - p_time) * 10;

                switch (dir) {
                case 't':
                        y += distance;
                        break;
                case 'd':
                        y -= distance;
                        break;
                case 'l':
                        x -= distance;
                        break;
                case 'r':
                        x += distance;
                        break;
                }

                if (signal == 1) {
                        switch (dir) {
                        case 't':
                                dir = 'l';
                                break;
                        case 'd':
                                dir = 'r';
                                break;
                        case 'l':
                                dir = 'd';
                                break;
                        case 'r':
                                dir = 't';
                                break;
                        }
                } else if (signal == 2) {
                        switch (dir) {
                        case 't':
                                dir = 'r';
                                break;
                        case 'd':
                                dir = 'l';
                                break;
                        case 'l':
                                dir = 't';
                                break;
                        case 'r':
                                dir = 'd';
                                break;
                        }

                } else if (signal == 3) {
                        break;
                }
                p_time = time;
        }
        printf("\n");
        printf("Position:\n");
        printf("%d %d\n", x, y);

        return 0;
}
