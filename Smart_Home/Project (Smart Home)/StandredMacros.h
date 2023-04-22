#ifndef StandredMacros_h
#define StandredMacros_h
#define readbit(reg,bit)    ((reg>>bit)&1)
#define togglebit(reg,bit)  reg^=(1<<bit)             //(!(reg>>bit))
#define setbit(reg,bit)     reg|=(1<<bit)            //((reg>>bit)=1)
#define clearbit(reg,bit)   reg&=(~(1<<bit))        //((reg>>bit)=0)

#endif // StandredMacros
