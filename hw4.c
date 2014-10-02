/* 統一發票兌獎 */

#include <stdio.h>

int prize(int specialPrizeNumbers[3], int firstPrizeNumbers[3], int myNumber);

int main()
{
        int i;
        int specialPrizeNumbers[3];
        int firstPrizeNumbers[3];
        int myNumber;
        int totalPrize = 0;

        for (i = 0; i < 3; i++)
                scanf("%d", &(specialPrizeNumbers[i]));
        for (i = 0; i < 3; i++)
                scanf("%d", &(firstPrizeNumbers[i]));

        while (scanf("%d", &myNumber) != EOF)
                totalPrize += prize(specialPrizeNumbers, firstPrizeNumbers, myNumber);

        printf("%d\n", totalPrize);
        return 0;
}

int prize(int specialPrizeNumbers[3], int firstPrizeNumbers[3], int myNumber)
{
        int i, j, ans;
        int ndigit = 8;
        int myNumbers[ndigit];
        int prize_no = 0;
        int ndigit_prized;
        int get_prize;

        for (i = ndigit - 1; i >= 0; --i) {
                myNumbers[i] = myNumber % 10;
                myNumber /= 10;
        }

        for (i = 0; i < 3; ++i) {
                get_prize = 1;
                ans = specialPrizeNumbers[i];
                for (j = ndigit - 1; j >= 0; --j) {
                        if (ans % 10 != myNumbers[j]) {
                                get_prize = 0;
                                break;
                        }
                        ans /= 10;
                }
                if (get_prize)
                        return 2000000;
        }

        for (i = 0; i < 3; ++i) {
                ndigit_prized = 0;
                ans = firstPrizeNumbers[i];
                for (j = ndigit - 1; j >= 0; --j) {
                        if (ans % 10 == myNumbers[j])
                                ++ndigit_prized;
                        else
                                break;
                        ans /= 10;
                }

                switch (ndigit_prized) {
                case 8:
                        return 200000;
                case 7:
                        prize_no = 2;
                        break;
                case 6:
                        if (prize_no == 0 || prize_no > 3)
                                prize_no = 3;
                        break;
                case 5:
                        if (prize_no == 0 || prize_no > 4)
                                prize_no = 4;
                        break;
                case 4:
                        if (prize_no == 0 || prize_no > 5)
                                prize_no = 5;
                        break;
                case 3:
                        if (prize_no == 0)
                                prize_no = 6;
                        break;
                }
        }

        switch (prize_no) {
        case 2:
                return 40000;
        case 3:
                return 10000;
        case 4:
                return 4000;
        case 5:
                return 1000;
        case 6:
                return 200;
        }

        return 0;
}
