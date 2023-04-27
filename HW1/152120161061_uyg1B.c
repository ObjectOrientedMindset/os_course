#include <stdio.h>
#include <stdbool.h>

// Sayının asallığını kontrol eder.
// Asal ise True değilse False döndürür.
bool check_if_prime(int num)
{
    int i = 0;
    int m = 0;

    // Bölen sayısını hesapla.
    for (i = 1; i <= num; i++)
    {
        if (num % i == 0)
        {
            m++;
        }
    }
    // Sayının 2 böleni varsa asaldır.
    if (m == 2)
    {
        return true;
    }

    return false;
}

int main()
{
    int number = 0;
    int bigger_prime = 0;
    int smaller_prime = 0;
    int temp = 0;

    // Kullanıcıdan sayı alınır.
    // Sayı 3 den küçükse kendinden küçük asal sayı olmadığı için hata verir.
    printf("Bir Sayı Giriniz: ");
    scanf("%d", &number);
    if (number < 3)
    {
        printf("Hatalı input 2 den büyük sayı giriniz!");

        return 11;
    }

    temp = number;
    // While loop büyük ve küçük asal sayı bulunana kadar döner.
    // Temp değişkeni arttırılarak veya azaltılarak check_if_prime
    // fonksiyonuna parametre olarak verilir.
    // Önce büyük sayı bulunur temp değişkeni resetlenir küçük sayı bulunur.
    while (bigger_prime == 0 || smaller_prime == 0)
    {
        if (bigger_prime == 0)
        {
            ++temp;
            if (check_if_prime(temp))
            {
                bigger_prime = temp;
                temp = number;
            }
        }
        else if (smaller_prime == 0)
        {
            --temp;
            if (check_if_prime(temp))
            {
                smaller_prime = temp;
                temp = number;
            }
        }
    }
    // Sonuç printf fonksiyonuna gönderilir.
    printf("Küçük Asal: %d , Büyük Asal: %d \n", smaller_prime, bigger_prime);

    return 0;
}