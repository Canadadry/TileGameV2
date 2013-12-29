#ifndef ASSERt_H
#define ASSERt_H


#ifndef NDEBUG

#define ASSERT(condition) do{ if(!(condition)){ fprintf(stderr,"ASSERT FAILED: " #condition " @ " __FILE__  " (" __LINE__ ")/n"); } }while(0)

#else

#define ASSERT(condition) do{}while(0)

#endif

#endif /* ASSERt_H */
