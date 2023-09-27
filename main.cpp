#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    string s;
    input >> s;
    int n = s.length();

    // Создаем двумерный вектор dp для хранения результатов подзадач
    // dp[i][j] будет содержать длину наибольшей палиндромной подпоследовательности
    // для подстроки s[i..j]
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Инициализируем диагональные элементы, они всегда будут равны 1
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }

    // Начинаем заполнять таблицу dp, начиная с более коротких подстрок и постепенно увеличивая длину
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1; // Конечный индекс текущей подстроки
            if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2; // Длина увеличивается на 2, если символы совпадают
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]); // В противном случае берем максимум из двух соседних подстрок
            }
        }
    }

    int length = dp[0][n - 1]; // Длина наибольшей палиндромной подпоследовательности

    // Создаем строку для хранения самой палиндромной подпоследовательности
    string palindrome(length, ' ');
    int i = 0, j = n - 1; // Индексы для поиска палиндромной подпоследовательности
    int pal1 = 0, pal2 = length - 1; // Индексы для заполнения строки palindrome

    while (i <= j) {
        if (s[i] == s[j]) {
            palindrome[pal1++] = s[i];
            if (i != j) {
                palindrome[pal2--] = s[j];
            }
            i++;
            j--;
        } else if (dp[i + 1][j] > dp[i][j - 1]) {
            i++; // Переходим к следующему символу в строке s
        } else {
            j--; // Переходим к предыдущему символу в строке s
        }
    }

    output << length << endl;
    output << palindrome << endl;

    return 0;
}
