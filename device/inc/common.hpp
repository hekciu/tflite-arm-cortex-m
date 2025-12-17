

#ifndef COMMON_HPP
#define COMMON_HPP

#define BIT(i) (1UL << (i))
#define IS_FLAG_SET(reg, n) (((reg) & BIT(n)) >> n == 1)

#endif
