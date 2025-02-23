/* RISC processors have THREE types
of load instructions (and three stores).  First, we have a LW
(32-bit), LH, and LB (8-bit).  Our bus is 32-bits wide, the
memory is 32-bits wide, our internal register is 32-bits wide
... why just move 8-bits around each instruction?  I can tell
the compiler to move WORDS if the pointers point to words instead
of bytes, so here's a first attempt at being faster...
*/
#include <stdio.h>
#include <stdint.h>
char buf[] = "...ABCDEFxy.........." ;
int main () {
    uint32_t    *src = (uint32_t*)(buf+4) ;
    uint32_t    *dest = (uint32_t*)(buf+13) ;

    *dest++ = *src++ ;  // 4 bytes
    *dest++ = *src++ ;  // 4 bytes
    // display string to show it overlapped itself
    printf("[%s]\n",buf) ;
    return 0 ;
}
/*theoretically, this is just four memory instructions: LDW, STW,
LDW, STW but in reality LDW only works if the address is on
a 4-byte (32-bit word) aligned boundary.  So if the compiler
cannot guarantee that buf+4 and buf+13 are both word aligned
then it can't use LDW!  In fact, you can guarantee that not
both are ... so we are screwed.
*/
