#ifndef _SALT2D_UTILS_BUFFER_H
#define _SALT2D_UTILS_BUFFER_H

#include <stdint.h>

/** Обертка над C-строкой.
  * Содержит размер строки, чтобы избежать 
  * переполнения буфера.
*/

typedef struct buffer {

    char   *buf; /**< C-строка */
    size_t size; /**< Размер C-строки */

};

#endif
