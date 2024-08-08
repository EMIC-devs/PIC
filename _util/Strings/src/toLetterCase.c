void toLetterCase(char* string)
{
    for(char* i = string; *i != '\0'; i++)
    {
        if (*i >= 65 && *i<=90)
        {
            *i += 32;
        }
    }
}