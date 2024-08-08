int16_t isContainedIn(char* substring, char* string)
{
    char* absolute_position = strstr(string, substring);

    if (absolute_position)
    {
        return (int16_t)(absolute_position - string);
    }
    return -1;
}