#include <stdio.h>

int main()
{
        int a = 117;
        int b = 203;
        int c = 151;
        int d = 29;
        int e = 37;

        int vol_total = a * b * c;
        int ap = a - 2 * e;
        int bp = b - 2 * e;
        int cp = c - 2 * e;
        int vol = vol_total - d * 2 * (ap * bp + ap * cp + bp * cp);
        printf("Volume: %d\n", vol);

        int sa = 2 * (a * b + a * c + b * c) + 8 * d * (ap + bp + cp);
        printf("Surface area: %d\n", sa);

        return 0;
}
