#ifndef CONFIG_H_
#define CONFIG_H_

#define DEBUG ///< Enables debug mode

typedef int Elem_t;                                              //< stack elements type
static const Elem_t ELEM_T_POISON = __INT_MAX__ - 13;            //< poison value for stack
static const unsigned long long CANARY_VAL = 0x8BADF00DDEADDEAD; //< canary protect value
#define ELEM_T_PRINTF "%d"                                       //< printf specificator

#endif /// #ifndef CONFIG_H_
