#ifndef _SALT2D_UTILS_ASSERT_HPP
#define _SALT2D_UTILS_ASSERT_HPP

#define ASSERT(COND, THROW) do { if(!(COND)) { throw(THROW); } } while(false)

#endif