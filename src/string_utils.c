#include "chat.h"

char *trim_white_space_unicode(char *str)
{
  char *end;

  while(  g_unichar_isspace((unsigned char)*str)) str++;

  if(*str == 0) 
    return str;

  end = str + strlen(str) - 1;
  while(end > str && g_unichar_isspace((unsigned char)*end)) end--;

  end[1] = '\0';

  return str;
}
