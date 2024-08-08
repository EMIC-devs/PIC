int8_t compare(char* string_1, char* string_2)
{
    int8_t result = strcmp(string_1, string_2);

    if (result > 0)
        return 1;
    else if (result == 0)
        return 0;
    else
        return -1;
}