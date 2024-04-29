#include <stdio.h>
#include <unistd.h>

// void intToBinary(int num)
// {
//     if (num == 0)
// 	{
//         write(1, "00000000000000000000000000000000\n", 32);
//         return;
//     }

// 	int i = 31;
//     while (i >= 0)
// 	{
//         if (1 == ((num >> i) & 1)) 
//             write(1, "1", 1);
//         else
//             write(1, "0", 1);
// 		i--;
//     }
//     write(1, "\n", 1);
// }
// int binaryToInt(char bit)
// {
//     static int result = 0;
//     static int i = 31;
// 	int res;

//     if (bit == '1')
//         result |= (1 << i);
//     i--;

//     if (i < 0)
// 	{
//         res = result;
//         result = 0;
//         i = 31;
//         return res;
//     }
//     return -1;
// }

// int main() {
//     int num = 1000;
//     printf("Integer: %d\n", num);
//     printf("Binary representation: ");
//     intToBinary(num);

//     const char *binary = "00000000000000000000001111101000";
//     printf("\nBinary string: %s\n", binary);

//     printf("Converted back to integer: ");
//     for (int i = 0; i < 32; i++) {
//         int result = binaryToInt(binary[i]);
//         if (result != -1) {
//             printf("%d ", result);
//         }
//     }
//     printf("\n");

//     return 0;
// }

void converter_int(int num)
{
	printf("ja");
	int i;
    if (num == 0)
	{
		i = 0;
		while (i < 32)
		{
            printf("0");
			usleep(300);
			i++;
		}
        return;
    }

	i = 31;
    while (i >= 0)
	{
        if (1 == ((num >> i) & 1))
		{
			printf("1");
		}
        else
		{
			printf("0");
		}
		usleep(300);
		i--;
    }
}

int main(void)
{
    converter_int(1000);
}