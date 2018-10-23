#ifndef Time_h
#define Time_h

struct Time {
    Time() {
        current_time = 0;
        delta_time = 0;
        last_frame = 0;
        
        time_multiplier = 1;
    }
    
    float current_time;
    float delta_time;
    float last_frame;
    
    float time_multiplier;
};

extern Time g_Time;

#endif
