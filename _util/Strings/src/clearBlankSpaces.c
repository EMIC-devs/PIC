void clearBlankSpaces(char* string)
{
    char* i;
    uint8_t leftMove = 0;
    for (i = string; *i != '\0'; i++)
    {
        if (*i == ' ' || *i == '\t')
        {
            leftMove++;
        }
        else
        {
            *(i-leftMove) = *i;
        }
    }
    *(i-leftMove) = *i;
}