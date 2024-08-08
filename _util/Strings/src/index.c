char index(char * string, uint8_t position)
{
    if (position <= strlen(string))
    {
        return string[position];
    }
    else
        return 0;
}