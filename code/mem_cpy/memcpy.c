#include <stdio.h>
char buf[] = "....ABCDEFxy.........." ;
int main () {
    char    *src = buf+4 ;
    char    *dest = buf+13 ;
    int     len = 6 ;

    *dest++ = *src++ ;
    *dest++ = *src++ ;
    *dest++ = *src++ ;
    *dest++ = *src++ ;
    *dest++ = *src++ ;
    *dest++ = *src++ ;
    // display buffer
    printf("[%s]\n",buf) ;
    return 0 ;
}

/*can we do better?  RISC processors have THREE types
of load instructions (and three stores).  First, we have a LW
(32-bit), LH, and LB (8-bit).  Our bus is 32-bits wide, the
memory is 32-bits wide, our internal register is 32-bits wide
... why just move 8-bits around each instruction?  I can tell
the compiler to move WORDS if the pointers point to words instead
of bytes, so here's a first attempt at being faster...
*/