#ifndef SERCVER_STRUCTURES_H
#define SERCVER_STRUCTURES_H

struct public_key_class
{
  long long modulus;
  long long exponent;
};

typedef struct
{
  char **arr;
  size_t cnt;
} array_t;

typedef struct
{
  char **arr;
} json_t;

typedef struct
{
  char *ch_id;
  char *ch_name;
  char *ch_avatar;
  char *u_login;
  char *u_lastSeen;
  char *u_avatar;
} chat_t;

typedef struct
{
  char *ch_id;
  char *ms_id;
  char *u_id;
  char *u_name;
  char *ms_text;
  char *ms_datetime;
  char *ms_isedited;
  char *ms_isforwarded;
  char *ms_ismedia;
  char *ms_isreply;
  char *ms_isseen;
} message_t;

typedef struct
{
  char *c_id;
  char *u_name;
  char *u_avatar;
  char *u_status;
} contact_t;

typedef struct
{
  char *u_name;
  char *u_surname;
  char *u_avatar;
  char *u_status;
} user_t;

#endif
