#ifndef CONFIG_H_
#define CONFIG_H_

#define DEBUG           ///< Enables debug mode
#define CANARY_PROTECT  ///< Enables canary protection
#define HASH_PROTECT    ///< Enables hash protection


typedef int Elem_t;                                              //< stack elements type
static const Elem_t ELEM_T_POISON = __INT_MAX__ - 13;            //< poison value for stack
#define ELEM_T_PRINTF   "%d"                                     //< Elem_t printf specificator

typedef unsigned long long Canary_t;                             //< canary type
static const Canary_t CANARY_VAL = 0x8BADF00DDEADDEAD;           //< canary protect value
#define CANARY_T_PRINTF "%llX"                                   //< Canary_t printf specificator


#endif /// #ifndef CONFIG_H_
