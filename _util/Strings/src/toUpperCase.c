void toUpperCase(char* string)
{
    for(char* i = string; *i != '\0'; i++)
    {
        if (*i >= 97 && *i<=122)
        {
            *i -= 32;
        }
    }
}