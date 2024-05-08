/*
** EPITECH PROJECT, 2024
** count char
** File description:
** count_char
*/

int count_char_in_str(char *str, char c, int limit)
{
    int result = 0;

    for (int i = 0; str[i] && i != limit; i++) {
        if (str[i] == c) {
            result += 1;
        }
    }
    return result;
}
