#include <stdio.h>

int main()
{
        int a, b, c, d, e;
        scanf("%d", &a);
        scanf("%d", &b);
        scanf("%d", &c);
        scanf("%d", &d);
        scanf("%d", &e);

        int vol_total = a * b * c;
        int ap = a - 2 * e;
        int bp = b - 2 * e;
        int cp = c - 2 * e;
        int vol = vol_total - d * 2 * (ap * bp + ap * cp + bp * cp);
        int sa = 2 * (a * b + a * c + b * c) + 8 * d * (ap + bp + cp);

        printf("\n");
        printf("Surface area, Volume:\n");
        printf("%d %d\n", sa, vol);

        return 0;
}
