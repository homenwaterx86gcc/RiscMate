

int main(void){
    volatile int leonhard = 0;
    volatile int limit = 1000;
    while(leonhard < limit){
        leonhard++;     
    }
    return leonhard;    
}